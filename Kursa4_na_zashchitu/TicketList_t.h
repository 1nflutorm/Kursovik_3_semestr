#pragma once
#include <fstream>
#include <iostream>
#include "AirFlight_t.h"
#include "Ticket_t.h"
#include "AirFlightTree_t.h"
using namespace std;

class TicketList_t
{
	struct node//описание структуры узла списка
	{
		Ticket_t* ticket;//указатель на билет
		node* pNext;//указатель на следующий элемент
		node(Ticket_t* tick, node* next);//конструктор с параметрами
	};
	int Size;//размер списка
	node* Head;//указатель на голову
	//приватные методы 
	int ConvertToInt(node* current);//прототип метода конвертирования
	void Swap(node* current, node* next);//прототип метода смены местави двух элементов списка
	node* FindPref(node* current);//прототип метода поиска предыдущего элемента
public:
	TicketList_t();//прототип конструктора 
	~TicketList_t();//прототип деструктора
	int IsMatch(node* current, const string& key);//прототип метода сравнения
	int DelInfoPassenger(const string& key);//прототип метода удаления данных об одном пассажире
	int Find(const string& key);//прототип метода поиска
	int FindByTicketNum(const string& key);//прототип метода поиска по номеру билета
	int GetSize();//прототип метода получания размера списка
	int FindTicket(const string& pas, const string& flightnum);//прототип метода поиска билета
	int PrintAllPassengerTickets(const string& pas);//прототип метода вывода на экран всех билетов пассажира
	void PushBack(const string& pas, const string& flight, const string& tick);//прототип метода заполнения
	void PopBack();//прототип метода удаления последнего элемента
	void Clear();//прототип метода очистки списка
	void DelInside(const int& index);//прототип метода удаления где то внутри списка
	void Insert(node* NodeToInsert, node* NodeBeforeInsert);//прототип метода вставки
	void PrintList();//прототип метода вывода на экран всех элементов
	void InsertSortList(TicketList_t& List);////прототип метода сортиовки вставками
	node* GetHead();//прототип метода получания указателя на голову
	node* operator[](const int& index);//прототип перегрузки оператора квадратные скобки
	string FindAirFlightByIndex(const int& index);
	void DeleteTicketsByFlightNum(const string& flightnum);
	void PrintLastTicket();
};