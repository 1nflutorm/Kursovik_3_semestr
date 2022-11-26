#pragma once
#include <fstream>
#include <iostream>
#include "AirFlight_t.h"
#include "Ticket_t.h"
#include "AirFlightTree_t.h"
using namespace std;

class TicketList_t
{
	struct node//�������� ��������� ���� ������
	{
		Ticket_t* ticket;//��������� �� �����
		node* pNext;//��������� �� ��������� �������
		node(Ticket_t* tick, node* next);//����������� � �����������
	};
	int Size;//������ ������
	node* Head;//��������� �� ������
	//��������� ������ 
	int ConvertToInt(node* current);//�������� ������ ���������������
	void Swap(node* current, node* next);//�������� ������ ����� ������� ���� ��������� ������
	node* FindPref(node* current);//�������� ������ ������ ����������� ��������
public:
	TicketList_t();//�������� ������������ 
	~TicketList_t();//�������� �����������
	int IsMatch(node* current, const string& key);//�������� ������ ���������
	int DelInfoPassenger(const string& key);//�������� ������ �������� ������ �� ����� ���������
	int Find(const string& key);//�������� ������ ������
	int FindByTicketNum(const string& key);//�������� ������ ������ �� ������ ������
	int GetSize();//�������� ������ ��������� ������� ������
	int FindTicket(const string& pas, const string& flightnum);//�������� ������ ������ ������
	int PrintAllPassengerTickets(const string& pas);//�������� ������ ������ �� ����� ���� ������� ���������
	void PushBack(const string& pas, const string& flight, const string& tick);//�������� ������ ����������
	void PopBack();//�������� ������ �������� ���������� ��������
	void Clear();//�������� ������ ������� ������
	void DelInside(const int& index);//�������� ������ �������� ��� �� ������ ������
	void Insert(node* NodeToInsert, node* NodeBeforeInsert);//�������� ������ �������
	void PrintList();//�������� ������ ������ �� ����� ���� ���������
	void InsertSortList(TicketList_t& List);////�������� ������ ��������� ���������
	node* GetHead();//�������� ������ ��������� ��������� �� ������
	node* operator[](const int& index);//�������� ���������� ��������� ���������� ������
	string FindAirFlightByIndex(const int& index);
	void DeleteTicketsByFlightNum(const string& flightnum);
	void PrintLastTicket();
};