#pragma once
#include <string>
using namespace std;

//описание класса пассажира
class Passenger_t
{
    string PasportNum;//номер паспорта
    string PlaceOfIssue;//место выдачи
    string DateOfIssue;//дата выдачи
    string FIO;//‘»ќ
    string Birthday;//день рождени€
public:
    Passenger_t();//прототип конструктора по умолчанию
    Passenger_t(const string& pas, const string& place, const string& date, const string& name, const string& birth);//прототип констректора с параметрами
    string GetFIO();//прототип метода получени€ имени
    string GetPasportNum();//прототип метода получени€ номера пасспорта
};