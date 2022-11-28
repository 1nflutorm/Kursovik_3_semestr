#include "AirFlightTree_t.h"
#include "MainFunctions.h"

//реализация конструктора узла
AirFlightTree_t::node::node(AirFlight_t* flight)
{
	Flight = flight;
	Height = 1;
	Left = Right = nullptr;
}
//реализация конструктора дерева
AirFlightTree_t::AirFlightTree_t()
{
	Head = nullptr;
}
//реализация деструктора дерева
AirFlightTree_t::~AirFlightTree_t()
{
	Clear(Head);
}
//реализация метода получения высоты узла
int AirFlightTree_t::GetHeight(node*& head)
{
	return head ? head->Height : 0;//если есть голова, возвращаем ее высоту, иначе 0
}
//реализация метода вычисления баланс фактора для узла
int AirFlightTree_t::Balance(node*& head)
{
	return GetHeight(head->Right) - GetHeight(head->Left);//возвращаем разницу высот двух соответсвующих поддеревьев
}
//реализация метода проверки на пустоту дерева
int AirFlightTree_t::IsEmpty()
{
	if (!Head)//если нет головы
		return 1;//дерево пустое
	return 0;
}
//реализация метода поиска узда по номеру рейса
int AirFlightTree_t::FindByAirFlightNum(node*& head, const int& key, int& count)
{
	if (head)//если есть голова
	{
		if (head->Flight->CovertTo() == key)//проверяем на совпадение конвертированных значений
			return ++count;//увеличиваем счетчих нахождения
		if (head->Flight->CovertTo() > key)//если значение больше ключа
			FindByAirFlightNum(head->Left, key, count);//идем в левое поддерево
		if (head->Flight->CovertTo() < key)//если меньше 
			FindByAirFlightNum(head->Right, key, count);//идем в правое поддерево
	}
	return count;//возвращаем количество совпадений
}
//реализация метода расчета высоты дерева
void AirFlightTree_t::HeightCalc(node*& head)
{
	int HeightLeft = GetHeight(head->Left);//считаем высоту левого поддерева
	int HeightRight = GetHeight(head->Right);//считаем высоту правеого поддерева
	head->Height = (HeightLeft > HeightRight ? HeightLeft : HeightRight) + 1;//в засисимости от того, что больше присвыем большее + 1
}
//реализация метода очистки дерева
void AirFlightTree_t::Clear(node*& head)
{
	if (head)//если есть голова
	{
		Clear(head->Left);//рекурсивно доходим до конечных узлов и удаляем
		Clear(head->Right);
		delete head;
		head = nullptr;//приравниваем nullptr для перестраховки
	}
}
//реализация метода печати полетов
void AirFlightTree_t::PrintFlights(node*& head)
{
	if (head)//если есть голова
	{
		PrintFlights(head->Left);//рекурсивно доходим до каждого узла и выводм из него даные о полете
		PrintFlights(head->Right);
		head->Flight->Print();
	}
}
//реализация метода поиска и печати полетов по части строки "аэропот прибытия"
void AirFlightTree_t::FindAndPrintBySubstr(node*& head, const string& substr, int& count)
{
	if (head)//если есть голова
	{
		if (BouerAndMoor(head->Flight->GetArriveAirport(), substr))//с помощью алгоритма боуэраи мура ищем подстроку в строке
		{
			head->Flight->Print();//если нашли печетаем 
			count++;//увеличиваем количество найденных
		}
		FindAndPrintBySubstr(head->Left, substr, count);//если не нашли рекурсивно проверяем каждый узел
		FindAndPrintBySubstr(head->Right, substr, count);
	}
}
//реализация метода правого поворота
AirFlightTree_t::node* AirFlightTree_t::RotationRight(node*& NodeToRotate)
{
	node* RotationNode = NodeToRotate->Left;//перекидываем узлы для правого поворота(сложно описать сломи адекватно)
	NodeToRotate->Left = RotationNode->Right;
	RotationNode->Right = NodeToRotate;
	HeightCalc(NodeToRotate);//пересчитываем высоту для каждого затронутого узла
	HeightCalc(RotationNode);
	return RotationNode;
}
//реализация метода левого поворта
AirFlightTree_t::node* AirFlightTree_t::RotationLeft(node*& NodeToRotate) // левый поворот вокруг q
{
	node* RotationNode = NodeToRotate->Right;//перекидываем узлы (опять же, очень сложно это описать словами)
	NodeToRotate->Right = RotationNode->Left;
	RotationNode->Left = NodeToRotate;
	HeightCalc(NodeToRotate);//пересчитываем высоту каждого поддерева
	HeightCalc(RotationNode);
	return RotationNode;
}
//реализация метода балансировки узла
AirFlightTree_t::node* AirFlightTree_t::BalanceNode(node*& head)
{
	HeightCalc(head);
	int BalanceFactor = Balance(head);//расчитываем разницу высот левого и правого поддерева
	if (BalanceFactor == 2)//если разбалансировка в левом поддереве
	{
		if (Balance(head->Right) < 0)//если узел, который разбалансировал пришел с внутренней части дерева
			head->Right = RotationRight(head->Right);//делаем большой левый поворот(сначала малый правый, потом левый)
		return RotationLeft(head);//если узед пришел с внешней строны, то просто делвем левый поворот
	}
	if (BalanceFactor == -2)//если разбалансровка в правом поддереве
	{
		if (Balance(head->Left) > 0)//если узел приел с внетренней стороны дерева
			head->Left = RotationLeft(head->Left);//делаем большой правй поворот по аналогии с верхним болоком кода
		return RotationRight(head);//если узед пришел с внешней строны, то просто делвем правый поворот
	}
	return head;
}
//реализация метода вставки узла
AirFlightTree_t::node* AirFlightTree_t::Insert(node*& head, AirFlight_t*& flight) // вставка ключа k в дерево с корнем p
{
	if (!head)//если нет голоый
	{
		head = new node(flight);//создаем ее
		return head;
	}
	//если голова есть
	if (flight->CovertTo() < head->Flight->CovertTo())//если ключ меньше
		head->Left = Insert(head->Left, flight);//идем влево
	else//иначе вправо
		head->Right = Insert(head->Right, flight);
	return BalanceNode(head);//балансируем каждый узел после вставки узла
}
//реализация метода поиска мнинимального
AirFlightTree_t::node* AirFlightTree_t::FindMin(node*& head) // поиск узла с минимальным ключом в дереве p 
{
	return head->Left ? FindMin(head->Left) : head;
}
//реализация метода поиска
AirFlight_t* AirFlightTree_t::Find(node*& head, const string& key)
{
	if (!head)//если нет головы
		return nullptr;//значит не нашли
	else if (head->Flight->GetAirFlightNum() == key)//если ключи совпати
		return head->Flight;//нашли, возвращаем полет
	else if (head->Flight->GetAirFlightNum() > key)//если ключ меньше, идем влево
		Find(head->Left, key);
	else
		Find(head->Right, key);//если больше идем вправо
}
//реализация метода очистки дерева
void AirFlightTree_t::Clear()
{
	Clear(Head);//вызываем clear от головы
}
//реализация метода вывода на экрвн полетов
void AirFlightTree_t::PrintFlights()
{
	PrintFlights(Head);//вызываем перегруженный метод от головы
}
//реализация метода поиска и печати полетов по части строки "аэропот прибытия"
void AirFlightTree_t::FindAndPrintBySubstr(const string& substr, int& count)
{
	FindAndPrintBySubstr(Head, substr, count);//вызываем аналогичный метод от головы
}
//реализация метода вставки
void AirFlightTree_t::Insert(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats)
{
	AirFlight_t* node = new AirFlight_t{ flightNum, company, departure, arrive, date, time, seats };//созданм новый полет
	Head = Insert(Head, node);//голове приравниваем сбалансированное дерево после процедуры вставки
}
//реализация метода удаления
void AirFlightTree_t::Remove(const string& key)
{
	AirFlight_t* node = Find(Head, key);//нахоим нужный узел
	Head = Remove(Head, node);//голове приравниваем отбалансированное дерево после уделения
}
//реализация метода поиска
AirFlight_t* AirFlightTree_t::Find(const string& key)
{
	return Find(Head, key);//вызываем аналогичный метода от головы и переданного ключа
}
//реализация метода поиска по номеру рейса
int AirFlightTree_t::FindByAirFlightNum(const int& key)
{
	int count = 0;//счетчик нахождения
	int res = FindByAirFlightNum(Head, key, count);//вызываем аналогичный метода от головы, полученного ключа и счетчика, записываемм результкт в переменную res
	return res;
}
//реализация метода установки дефолтных значений количества мест
void AirFlightTree_t::SetDefault(node* head)
{
	if (head)
	{
		SetDefault(head->Left);//рекурсивно проходим все полеты
		SetDefault(head->Right);
		int NumberOfSeats = head->Flight->GetNumberOfSeats();//получаем количество мест в полете
		head->Flight->SetNumberOfSeats(NumberOfSeats);//задаем количество свободных мест как общее количество мест
	}
}
//реализация метода установки дефолтных значений количества мест
void AirFlightTree_t::SetDefault()
{
	SetDefault(Head);//вызываем аналогичный метод от головы
}
//реализация метода удаления узла с минимальным ключом
AirFlightTree_t::node* AirFlightTree_t::RemoveMin(node*& head)
{
	if (!head->Left)//если нет левого поддерева
		return head->Right;//возвращаем правоке
	head->Left = RemoveMin(head->Left);//ищем дальше в левом поддевере
	return BalanceNode(head);//
}
//реализация метода удаления
AirFlightTree_t::node* AirFlightTree_t::Remove(node* head, AirFlight_t*& flight) // удаление ключа k из дерева p
{
	if (!head)//если нет головый то удалять ничего нк надо 
		return nullptr;

	if (flight->CovertTo() < head->Flight->CovertTo())//если ключ меньше
	{
		head->Left = Remove(head->Left, flight);//идем влево
	}
	else if (flight->CovertTo() > head->Flight->CovertTo())//если больше
	{
		head->Right = Remove(head->Right, flight);// идем вправо
	}
	else
	{
		node* pLeft = head->Left;//сохраняем левое и правое поддерево
		node* pRight = head->Right;
		delete head;//удаляем голову
		head = nullptr;
		if (!pRight)//если нет правого поддерева
			return pLeft;//возвращаем левое поддерево
		node* min = FindMin(pRight);//если правое есть, находим мнинимальный узел
		min->Right = RemoveMin(pRight);//правым поддеревом становится дерев посел удаления мнимаьного узла
		min->Left = pLeft;//левым остает левое поддерево
		return BalanceNode(min);//балансируем узел
	}
	return BalanceNode(head);//балансируем каждый узел
}
