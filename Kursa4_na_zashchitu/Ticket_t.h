#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ticket_t
{
    string PasportNum;//номер паспорта
    string AirFligthNum;//номер авиарейса
    string TicketNum;//номер авиабитела
public:
    Ticket_t();//прототип конструктора по умолчанию
    Ticket_t(const string& pas, const string& flight, const string& ticket);//прототип конструктора с параметрами
    void PrintOne();//прототип метода вывода даннах об одном билете
    string GetPasportNum();//прототип метода получения номера пасспорта
    string GetTicketNum();//прототип метода получения номера билета
    string GetAirFligthNum();//прототип метода получения номера авиарейса
};

