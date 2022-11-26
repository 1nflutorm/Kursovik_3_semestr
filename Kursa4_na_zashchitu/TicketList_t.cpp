#include "TicketList_t.h"

//���������� ������������ ���� ������
TicketList_t::node::node(Ticket_t* tick, node* next)
{
	ticket = tick;
	pNext = next;
}
//���������� ������������ �� ���������
TicketList_t::TicketList_t()
{
	Head = nullptr;
	Size = 0;
}
//���������� �����������
TicketList_t::~TicketList_t()
{
	Clear();
}
//���������� ���������� ���������
TicketList_t::node* TicketList_t::operator[](const int& index)
{
	node* current = Head;//��������� ����������, �������� �������� ������ ������
	for (int i = 0; i < index; i++)//���� �� 0 ��� ������������ �������
		current = current->pNext;//������� � ���������� ��������
	return current;//����������� ��������, ��������� ������ �� ������ ��������
}
//���������� ������ �������� �� �������
string TicketList_t::FindAirFlightByIndex(const int& index)
{
	if (index == -1)
		return "";
	node* current = Head;
	for (int i = 0; i < index; i++)
		current = current->pNext;
	return current ? current->ticket->GetAirFligthNum() : "";
}
//���������� �������� ���� ������� � ������� �����
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
//���������� ������ ��������� ������
void TicketList_t::PrintLastTicket()
{
	node* current = Head;
	while (current->pNext)
		current = current->pNext;
	current->ticket->PrintOne();
}
//���������� ������ ���������
int TicketList_t::IsMatch(node* current, const string& key)
{
	if (current->ticket->GetPasportNum() == key)//���� ����� �������� ��������� � ������
		return 1;//���������� 1
	return 0;//����� 0
}
//���������� ������ �������� ������ �� ����� ���������
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
//���������� ������ ������ �� �������� ���������
int TicketList_t::Find(const string& key)
{
	node* current = Head;//��������� �� ������� �������, ���������� ����� ������
	for (int i = 0; i < Size; i++)//���� �� ���������� ��������� � ������
	{
		if (IsMatch(current, key))//���� �����
			return i;//���������� ������
		current = current->pNext;//���� ���, ��������� � ���������� ��������
	}
	return -1;//���� �� ����� ���������� -1
}
//���������� ������ ��������� ������� ������
int TicketList_t::GetSize()
{
	return Size;
}
//���������� ������ ��������������� ������ ������ � ����� �����
int TicketList_t::ConvertToInt(node* current)
{
	return stoi(current->ticket->GetTicketNum());
}
//���������� ������ ������ �� ����� ���� �������, ��������� ����������
int TicketList_t::PrintAllPassengerTickets(const string& pas)
{
	node* current = Head;//��������� �� ������� �������, ���������� ����� ������
	int count = 0;//�������, ���������� �� ���������� ���������� �� �����
	for (int i = 0; i < Size; i++)//���� �� ���������� ��������� � ������
	{
		if (current->ticket->GetPasportNum() == pas)//���� ������� � ������
		{
			current->ticket->PrintOne();//������� �� �����
			count++;//����������� �������
		}
		current = current->pNext;//���� ���, �� ��������� � ���������� ��������
	}
	if (count)//���� ������� �� ����� 0, ���������� 1
		return 1;
	return 0;//����� 0
}
//���������� ������ ������ ������ �� ��� ������
int TicketList_t::FindByTicketNum(const string& key)
{
	node* current = Head;//��������� ����������, ���������� ������ ������
	for (int i = 0; i < Size; i++)//���� �� ������� ������
	{
		if (current->ticket->GetTicketNum() == key)//���� ��������� � ������, ������ �����
			return 1;
		current = current->pNext;//���� ���, ���� ������ �� ������
	}
	return 0;
}
//���������� ������ ������ ������ �� ������ �������� � ����������
int TicketList_t::FindTicket(const string& pas, const string& flightnum)
{
	//int index = 0;//������ � ������
	node* current = Head;
	for (int i = 0; i < Size; i++)//���� �� ������� ������
	{
		if (current->ticket->GetPasportNum() == pas && current->ticket->GetAirFligthNum() == flightnum)//���� �������
			return i;//���������� ������ ������� ��������
		current = current->pNext;//���� ���, �� ���� ������ �� ������
		//index++;
	}
	return -1;//���������� -1, ���� �� �����
}
//���������� ������ ���������� ������
void TicketList_t::PushBack(const string& pas, const string& flight, const string& tick)
{
	Ticket_t* NewTicket = new Ticket_t{ pas , flight, tick };
	node* temp = new node{ NewTicket, nullptr };//�� ��������� ���������� ������ ��������� �������
	if (!Head)
	{
		Head = temp;//���� ��������� ��� ���, �� ��������� ��� ��� ������
	}
	else
	{
		node* current = Head;//���� �������� ����, �� ������� ��������� �������, ������� ����� ������
		while (current->pNext)//� ���� ����� ���� ���������� �������
			current = current->pNext;//����� ���������� ����� � current ����� ������ ������������� �������(������������ ������)
		current->pNext = temp;//��������� ����� � ����� ���������
	}
	Size++;//����������� ������ ������
}
//���������� ������ �������� ���������� ��������
void TicketList_t::PopBack()
{
	if (!Head)//���� ������ ������
		return;//������ �������
	node* current = Head;//����� ������� ��������� ����������, ������ ������
	for (int i = 0; i < Size - 1; i++)//���� ��������� �������
		current = current->pNext;
	delete current;//������� ���
	current = nullptr;//��� ������������� ������������ ��� nullptr ��� ��������� ���������� ������
	Size--;//��������� ������ ������
}
//���������� ������ ������� ������
void TicketList_t::Clear()
{
	for (int i = 0; i < Size; i++)//���� �� ������� ������
		PopBack();//������� ��������� �������
}
//���������� ������ �������� ���-�� ������ ������
void TicketList_t::DelInside(const int& index)
{
	if (index == -1)//���� �� ���� ������ ������ -1, �������
		return;
	node* previous = nullptr;//��������� ��������� �� ���������� �������
	node* current = Head;//��������� ��������� �� ������� �������
	if (index == 0)//���� ���� ������� ������ �������
	{
		Head = current->pNext;//��������� ������
		delete current;//������� "������" ������
		Size--;//��������� ������ ������
		return;//�������
	}
	for (int i = 0; i < index; i++)//���� ������ ������ 0, ���� �� ������ ������� �������� ���������� � ������� ���������
	{
		previous = current;//���������� ���������� �������
		current = current->pNext;//������� ����������� ���������
	}
	previous->pNext = current->pNext;//���������� ����� ����� ���������
	delete current;//�������� �������� ��������
	Size--;//���������� ������� ������
}
//���������� ������ ������� � ������ ��� ���������� ������� ���������
void TicketList_t::Insert(node* NodeToInsert, node* NodeBeforeInsert)
{
	if (NodeBeforeInsert == Head)//���� ���� �������� ����� ������ ���������
	{
		Head = NodeToInsert;//��������� ������
		NodeToInsert->pNext = NodeBeforeInsert;//��������� �� ������ ���������� "������" ������ 
	}
	else//� ����� ������ ������
	{
		node* temp = FindPref(NodeBeforeInsert);//����� ���������� ������� �� ����, ����� ������� ���� ��������
		temp->pNext = NodeToInsert;//��������� �����
		NodeToInsert->pNext = NodeBeforeInsert;//��������� ����� �� ���������
	}
}
//���������� ������ ������ ������ �� �����
void TicketList_t::PrintList()
{
	node* current = Head;//��������� ����������, ���������� ������ ������
	while (current)//���� �� ����� �� ����� ������
	{
		current->ticket->PrintOne();//������� ������ � ������ �������� ��������
		current = current->pNext;//��������� � ���������� �������� � ������
	}

}
//���������� ������ ���������� ���������
void TicketList_t::InsertSortList(TicketList_t& List)
{
	for (int i = 1; i < Size; i++)//���� �� ������� ������
	{
		int j = i;//��������� ����������, ������ ��������� �����
		while (ConvertToInt(List[j]) < ConvertToInt(List[j - 1]) && j > 0)//���� ������� ������ �����������
		{
			Swap(List[j], List[j - 1]);//������ �� �������
			j--;
		}
	}

}
//���������� ������ ����� ������� ���� ���������
void TicketList_t::Swap(node* current, node* prev)
{
	if (prev == Head)//���� ���������� ����� ������
	{
		//node* PrefNext = FindPref(next);
		Head = current;//������ ����������� �������
		prev->pNext = current->pNext;//��������� �� ����������� ����������� ��������� �� ��������
		current->pNext = prev;//��� �������� ��������� ���������� ����������
	}
	else
	{
		node* PrevPrevious = FindPref(prev);//��������� ����������, �������� ���������� �� �����������
		PrevPrevious->pNext = current;//��� ���� ��������� ���������� �������
		prev->pNext = current->pNext;// � ����������� ��������� ���������� ��������� �� ��������
		current->pNext = prev;//� �������� ��������� ����������� ����������
	}

}
//���������� ������ ��������� ������
TicketList_t::node* TicketList_t::GetHead()
{
	return Head;
}
//���������� ������ ������ ����������� 
TicketList_t::node* TicketList_t::FindPref(node* current)
{
	node* pref = Head;//��������� ����������, �������� � ���� ������
	if (current == Head)//���� ����� ���������� �� ������
		return nullptr;//���������� 0
	while (pref->pNext != current)//���� ���� ��������� �� ������ �������, ����� ����� ���� �����
		pref = pref->pNext;//��������� � ���������� �������� ������
	return pref;//���������� ���� �������
}