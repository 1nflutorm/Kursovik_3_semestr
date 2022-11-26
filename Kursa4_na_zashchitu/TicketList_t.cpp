#include "TicketList_t.h"

//реализация конструктора узла списка
TicketList_t::node::node(Ticket_t* tick, node* next)
{
	ticket = tick;
	pNext = next;
}
//реализация конструктора по умолчанию
TicketList_t::TicketList_t()
{
	Head = nullptr;
	Size = 0;
}
//реализация деструктора
TicketList_t::~TicketList_t()
{
	Clear();
}
//реализация перегрузки оператора
TicketList_t::node* TicketList_t::operator[](const int& index)
{
	node* current = Head;//временная переменная, начально хранящая голову списка
	for (int i = 0; i < index; i++)//цикл от 0 доо необходимого индекса
		current = current->pNext;//переход к следующему элементу
	return current;//вохвращение элемента, хранящего данные по нужным индексом
}
//реализация поиска перелета по индексу
string TicketList_t::FindAirFlightByIndex(const int& index)
{
	if (index == -1)
		return "";
	node* current = Head;
	for (int i = 0; i < index; i++)
		current = current->pNext;
	return current ? current->ticket->GetAirFligthNum() : "";
}
//реализация удаления всех билетов с номером рейса
void TicketList_t::DeleteTicketsByFlightNum(const string& flightnum)
{
	int index = 0;
	string Pas;
start:
	node* current = Head;
	for (int i = 0; i < Size; i++)
	{
		if (current->ticket->GetAirFligthNum() == flightnum)
		{
			DelInside(i);
			goto start;
		}
		current = current->pNext;
	}
}
//реализация вывода посленего билета
void TicketList_t::PrintLastTicket()
{
	node* current = Head;
	while (current->pNext)
		current = current->pNext;
	current->ticket->PrintOne();
}
//реализация метода сравнения
int TicketList_t::IsMatch(node* current, const string& key)
{
	if (current->ticket->GetPasportNum() == key)//если номер паспорта совпадает с ключом
		return 1;//возвращаем 1
	return 0;//иначе 0
}
//реализация метода удаления данных об одном пассажире
int TicketList_t::DelInfoPassenger(const string& key)
{
	node* current = Head;//
	while (current)
	{
		int index = Find(key);
		if (index != -1)
			DelInside(index);
	}
	return 0;
}
//реализация метода поиска по паспорту пассажира
int TicketList_t::Find(const string& key)
{
	node* current = Head;//указатель на текущий элемент, изначально равен голове
	for (int i = 0; i < Size; i++)//цикл по количеству элементов в списке
	{
		if (IsMatch(current, key))//если нашли
			return i;//возвращаем индекс
		current = current->pNext;//если нет, переходим к следующему элементу
	}
	return -1;//если не нашли возвращаем -1
}
//реализация метода получения размера списка
int TicketList_t::GetSize()
{
	return Size;
}
//реализация метода конвертирования номера билета в целое число
int TicketList_t::ConvertToInt(node* current)
{
	return stoi(current->ticket->GetTicketNum());
}
//реализация метода вывода на экран всех билетов, купленных пассажиром
int TicketList_t::PrintAllPassengerTickets(const string& pas)
{
	node* current = Head;//указатель на текущий элемент, изначально равен голове
	int count = 0;//счетчик, отвечающий за количество выведенных на экран
	for (int i = 0; i < Size; i++)//цикл по количеству элементов в списке
	{
		if (current->ticket->GetPasportNum() == pas)//если совпали с ключом
		{
			current->ticket->PrintOne();//выводим на экран
			count++;//увеличиваем счетчик
		}
		current = current->pNext;//если нет, то переходим к следующему элементу
	}
	if (count)//если счетчик не равен 0, возвращаем 1
		return 1;
	return 0;//иначе 0
}
//реализация метода поиска билета по его номеру
int TicketList_t::FindByTicketNum(const string& key)
{
	node* current = Head;//верменная переменная, изначально равная голове
	for (int i = 0; i < Size; i++)//цикл по размеру списка
	{
		if (current->ticket->GetTicketNum() == key)//если совпадаем с ключом, значит нашли
			return 1;
		current = current->pNext;//если нет, идем дальше по списку
	}
	return 0;
}
//реализация метода поиска билета по номеру паспорта и авиареййса
int TicketList_t::FindTicket(const string& pas, const string& flightnum)
{
	//int index = 0;//индекс в списке
	node* current = Head;
	for (int i = 0; i < Size; i++)//цикл по размеру списка
	{
		if (current->ticket->GetPasportNum() == pas && current->ticket->GetAirFligthNum() == flightnum)//если совпали
			return i;//возвращаем индекс нужного элемента
		current = current->pNext;//если нет, то идем дальше оп списку
		//index++;
	}
	return -1;//возвращаем -1, если не нашли
}
//реализация метода заполнения списка
void TicketList_t::PushBack(const string& pas, const string& flight, const string& tick)
{
	Ticket_t* NewTicket = new Ticket_t{ pas , flight, tick };
	node* temp = new node{ NewTicket, nullptr };//во временную переменную кладем созданный элемент
	if (!Head)
	{
		Head = temp;//если элементов еще нет, то заполняем его как первый
	}
	else
	{
		node* current = Head;//если элементы есть, то создаем временный элемент, который равен голове
		while (current->pNext)//в этом цикле ищем предыдущий элемент
			current = current->pNext;//после отеработки цикла в current будет ледать предпоследний элемент(относительно нового)
		current->pNext = temp;//формируем связь с новым элементом
	}
	Size++;//увеличиваем размер списка
}
//реализация метода удаления последнего элемента
void TicketList_t::PopBack()
{
	if (!Head)//если список пустой
		return;//просто выходим
	node* current = Head;//иначе создаем временную переменную, равную голове
	for (int i = 0; i < Size - 1; i++)//ищем последний элемент
		current = current->pNext;
	delete current;//удаляем его
	current = nullptr;//для перестраховки приравниваем его nullptr для избежания дальнейших ошибок
	Size--;//уменьшаем развер списка
}
//реализация метода очистки списка
void TicketList_t::Clear()
{
	for (int i = 0; i < Size; i++)//цикл по размеру списка
		PopBack();//удаляем последний элемент
}
//реализация метода удаления где-то вгутри списка
void TicketList_t::DelInside(const int& index)
{
	if (index == -1)//если на вход подали индекс -1, выходим
		return;
	node* previous = nullptr;//временный указатель на предыдущий элемент
	node* current = Head;//временный указатель на текущий элемент
	if (index == 0)//если надо удалить первый элемент
	{
		Head = current->pNext;//обновляем голову
		delete current;//удаляем "старую" голову
		Size--;//уменьшаем размер списка
		return;//выходим
	}
	for (int i = 0; i < index; i++)//если индекс больше 0, идем по списку попарно обновляя предыдущий и текущий указатели
	{
		previous = current;//предыдущий становится текущим
		current = current->pNext;//текущий страновится слудующим
	}
	previous->pNext = current->pNext;//сохранения связи перед удалением
	delete current;//удаление текущего элемента
	Size--;//уменьшение размера списка
}
//реализация метода вставки в список для сортировки методом вставками
void TicketList_t::Insert(node* NodeToInsert, node* NodeBeforeInsert)
{
	if (NodeBeforeInsert == Head)//если надо вставить перед первым элементом
	{
		Head = NodeToInsert;//обновляем голову
		NodeToInsert->pNext = NodeBeforeInsert;//следующим от головы станосится "старая" голова 
	}
	else//в любом другом случае
	{
		node* temp = FindPref(NodeBeforeInsert);//нахом предыдущий элемент от того, перед которым надо вставить
		temp->pNext = NodeToInsert;//вставляем новый
		NodeToInsert->pNext = NodeBeforeInsert;//сохраняем связь со следующим
	}
}
//реализация метода вывода списка на экран
void TicketList_t::PrintList()
{
	node* current = Head;//временная переменная, изначально равная голове
	while (current)//пока не дощлт до конца списка
	{
		current->ticket->PrintOne();//выводим данные о билете текущего элемента
		current = current->pNext;//переходим к следкющему элементу в списке
	}

}
//реализация метода сортировки вставками
void TicketList_t::InsertSortList(TicketList_t& List)
{
	for (int i = 1; i < Size; i++)//цикл по размеру списка
	{
		int j = i;//временная переменная, равная итератору цикла
		while (ConvertToInt(List[j]) < ConvertToInt(List[j - 1]) && j > 0)//если текуший меньше предыдущего
		{
			Swap(List[j], List[j - 1]);//меняем их местами
			j--;
		}
	}

}
//реализация метода смены местами двух элементов
void TicketList_t::Swap(node* current, node* prev)
{
	if (prev == Head)//если предыдущий равен голове
	{
		//node* PrefNext = FindPref(next);
		Head = current;//голова становиться текущим
		prev->pNext = current->pNext;//следующий от предыдущего становиться следующий от текущего
		current->pNext = prev;//для текущего следующим становится предыдущий
	}
	else
	{
		node* PrevPrevious = FindPref(prev);//временная переменная, хранящая предыдущий от предыдущего
		PrevPrevious->pNext = current;//для него следующим становится текущий
		prev->pNext = current->pNext;// у предыдущего следующим становится следующий от текущего
		current->pNext = prev;//у текущего следующим становиться предыдущий
	}

}
//реализация метода получения головы
TicketList_t::node* TicketList_t::GetHead()
{
	return Head;
}
//реализация метода поиска предыдущего 
TicketList_t::node* TicketList_t::FindPref(node* current)
{
	node* pref = Head;//временная переменная, хранящая в себе голову
	if (current == Head)//если нужен предыдущий от головы
		return nullptr;//возвращаем 0
	while (pref->pNext != current)//цикл пока следующим не станет элемент, перед корым надо найти
		pref = pref->pNext;//переходим к следующему элементу списка
	return pref;//возвращаем этот элемент
}