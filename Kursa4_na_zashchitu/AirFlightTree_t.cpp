#include "AirFlightTree_t.h"
#include "MainFunctions.h"

AirFlightTree_t::node::node(AirFlight_t* flight)
{
	Flight = flight;
	Height = 1;
	Left = Right = nullptr;
}

AirFlightTree_t::AirFlightTree_t()
{
	Head = nullptr;
}

AirFlightTree_t::~AirFlightTree_t()
{
	Clear(Head);
}

int AirFlightTree_t::GetHeight(node*& head)
{
	return head ? head->Height : 0;
}

int AirFlightTree_t::Balance(node*& head)
{
	return GetHeight(head->Right) - GetHeight(head->Left);
}

int AirFlightTree_t::IsEmpty()
{
	if (!Head)
		return 1;
	return 0;
}

int AirFlightTree_t::FindByAirFlightNum(node*& head, const int& key, int& count)
{
	if (head)
	{
		if (head->Flight->CovertTo() == key)
			return ++count;
		if (head->Flight->CovertTo() > key)
			FindByAirFlightNum(head->Left, key, count);
		if (head->Flight->CovertTo() < key)
			FindByAirFlightNum(head->Right, key, count);
	}
	return count;
}

void AirFlightTree_t::HeightCalc(node*& head)
{
	int HeightLeft = GetHeight(head->Left);
	int HeightRight = GetHeight(head->Right);
	head->Height = (HeightLeft > HeightRight ? HeightLeft : HeightRight) + 1;
}

void AirFlightTree_t::SetHead(node*& head)
{
	Head = head;
}

void AirFlightTree_t::Clear(node*& head)
{
	if (head)
	{
		Clear(head->Left);
		Clear(head->Right);
		delete head;
		head = nullptr;
	}
}

void AirFlightTree_t::PrintFlights(node*& head)
{
	if (head)
	{
		PrintFlights(head->Left);
		PrintFlights(head->Right);
		head->Flight->Print();
	}
}

void AirFlightTree_t::FindAndPrintBySubstr(node*& head, const string& substr, int& count)
{
	if (head)
	{
		if (BouerAndMoor(head->Flight->GetArriveAirport(), substr))
		{
			head->Flight->Print();
			count++;
		}
		FindAndPrintBySubstr(head->Left, substr, count);
		FindAndPrintBySubstr(head->Right, substr, count);
	}
}

AirFlightTree_t::node* AirFlightTree_t::RotationRight(node*& NodeToRotate) // правый поворот вокруг p
{
	node* RotationNode = NodeToRotate->Left;
	NodeToRotate->Left = RotationNode->Right;
	RotationNode->Right = NodeToRotate;
	HeightCalc(NodeToRotate);
	HeightCalc(RotationNode);
	return RotationNode;
}

AirFlightTree_t::node* AirFlightTree_t::RotationLeft(node*& NodeToRotate) // левый поворот вокруг q
{
	node* RotationNode = NodeToRotate->Right;
	NodeToRotate->Right = RotationNode->Left;
	RotationNode->Left = NodeToRotate;
	HeightCalc(NodeToRotate);
	HeightCalc(RotationNode);
	return RotationNode;
}

AirFlightTree_t::node* AirFlightTree_t::BalanceNode(node*& head)
{
	HeightCalc(head);
	if (Balance(head) == 2)
	{
		if (Balance(head->Right) < 0)
			head->Right = RotationRight(head->Right);
		return RotationLeft(head);
	}
	if (Balance(head) == -2)
	{
		if (Balance(head->Left) > 0)
			head->Left = RotationLeft(head->Left);
		return RotationRight(head);
	}
	return head;
}

AirFlightTree_t::node* AirFlightTree_t::Insert(node*& head, AirFlight_t*& flight) // вставка ключа k в дерево с корнем p
{
	if (!head)
	{
		head = new node(flight);
		return head;
	}

	if (flight->CovertTo() < head->Flight->CovertTo())
		head->Left = Insert(head->Left, flight);
	else
		head->Right = Insert(head->Right, flight);
	return BalanceNode(head);
}

AirFlightTree_t::node* AirFlightTree_t::FindMin(node*& head) // поиск узла с минимальным ключом в дереве p 
{
	return head->Left ? FindMin(head->Left) : head;
}

AirFlight_t* AirFlightTree_t::Find(node*& head, const string& key)
{
	if (!head)
	{
		return nullptr;
	}
	else if (head->Flight->GetAirFlightNum() == key)
	{
		return head->Flight;
	}
	else if (head->Flight->GetAirFlightNum() > key)
	{
		Find(head->Left, key);
	}
	else
	{
		Find(head->Right, key);
	}

}

void AirFlightTree_t::Clear()
{
	Clear(Head);
}

void AirFlightTree_t::PrintFlights()
{
	PrintFlights(Head);
}

void AirFlightTree_t::FindAndPrintBySubstr(const string& substr, int& count)
{
	FindAndPrintBySubstr(Head, substr, count);
}

void AirFlightTree_t::Insert(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats)
{
	AirFlight_t* node = new AirFlight_t{ flightNum, company, departure, arrive, date, time, seats };//созданм новый полет
	Head = Insert(Head, node);
}

void AirFlightTree_t::Remove(const string& key)
{
	AirFlight_t* node = Find(Head, key);
	Head = Remove(Head, node);
}

AirFlight_t* AirFlightTree_t::Find(const string& key)
{
	return Find(Head, key);
}

int AirFlightTree_t::FindByAirFlightNum(const int& key)
{
	int count = 0;
	int res = FindByAirFlightNum(Head, key, count);
	return res;
}

void AirFlightTree_t::SetDefault(node* head)
{
	if (head)
	{
		SetDefault(head->Left);
		SetDefault(head->Right);
		int NumberOfSeats = head->Flight->GetNumberOfSeats();
		head->Flight->SetNumberOfSeats(NumberOfSeats);
	}
}

void AirFlightTree_t::SetDefault()
{
	SetDefault(Head);
}

AirFlightTree_t::node* AirFlightTree_t::RemoveMin(node*& head) // удаление узла с минимальным ключом из дерева p
{
	if (!head->Left)
		return head->Right;
	head->Left = RemoveMin(head->Left);
	return BalanceNode(head);
}

AirFlightTree_t::node* AirFlightTree_t::Remove(node* head, AirFlight_t*& flight) // удаление ключа k из дерева p
{
	if (!head)
		return 0;
	if (flight->CovertTo() < head->Flight->CovertTo())
		head->Left = Remove(head->Left, flight);
	else if (flight->CovertTo() > head->Flight->CovertTo())
		head->Right = Remove(head->Right, flight);
	else
	{
		node* pLeft = head->Left;
		node* pRight = head->Right;
		delete head;
		if (!pRight)
			return pLeft;
		node* min = FindMin(pRight);
		min->Right = RemoveMin(pRight);
		min->Left = pLeft;
		return BalanceNode(min);
	}
	return BalanceNode(head);
}

AirFlightTree_t::node* AirFlightTree_t::GetHead()
{
	return Head;
}
