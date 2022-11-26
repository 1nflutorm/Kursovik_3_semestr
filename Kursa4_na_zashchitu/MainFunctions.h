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

void PrintMenu();//прототип функции печати меню

int IsCorrectPas(const string& key);//прототип функции проверки корректности поспотрных данных

int IsCorrectFlight(const string& key);//прототип функции проверки корректности номера авиарейса

int Convert(const string& key);//прототип функции конвертирования

int Shift(vector<numbers*> vec, char symb);//прототип функции вычисления смещения в слове

int BouerAndMoor(const string& str, const string& substr);//прототип функции поиска слова в тексте Боуэра и Мура

vector<numbers*> CutString(const string& substr);//прототип функции выделения из строки отдельных символов

void PushPassengers(HashTable_t& Table, const string& pas);

void PushAirFlights(AirFlightTree_t& Tree, const string& pas);

void PushTickets(AirFlightTree_t& Tree, TicketList_t& List, const string& pas);