#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "HashTable_t.h"
#include "Passenger_t.h"
#include "AirFlight_t.h"
#include "TicketList_t.h"
#include "Ticket_t.h"
#include "AirFlightTree_t.h"
using namespace std;

struct numbers
{
	char symb;
	int position;
	numbers(char symb, int position);
};

void PrintMenu();//�������� ������� ������ ����

int IsCorrectPas(const string& key);//�������� ������� �������� ������������ ���������� ������

int IsCorrectFlight(const string& key);//�������� ������� �������� ������������ ������ ���������

int Convert(const string& key);//�������� ������� ���������������

int Shift(vector<numbers*> vec, char symb);//�������� ������� ���������� �������� � �����

int BouerAndMoor(const string& str, const string& substr);//�������� ������� ������ ����� � ������ ������ � ����

vector<numbers*> CutString(const string& substr);//�������� ������� ��������� �� ������ ��������� ��������

void PushPassengers(HashTable_t& Table, const string& pas);

void PushAirFlights(AirFlightTree_t& Tree, const string& pas);

void PushTickets(AirFlightTree_t& Tree, TicketList_t& List, const string& pas);