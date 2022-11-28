#pragma once
#include <string>
using namespace std;

//описание класса пассажира
class Passenger_t
{
    string PasportNum;//номер паспорта
    string PlaceOfIssue;//место выдачи
    string DateOfIssue;//дата выдачи
    string FIO;//ФИО
    string Birthday;//день рождения
public:
    Passenger_t();//прототип конструктора по умолчанию
    Passenger_t(const string& pas, const string& place, const string& date, const string& name, const string& birth);//прототип констректора с параметрами
    string GetFIO();//прототип метода получения имени
    string GetPasportNum();//прототип метода получения номера пасспорта
    string GetPlaceOfIssue();//прототип метода получения места выдачи паспорта
    string GetDateOfIssue();//прототип метода получения даты выдачи паспорта
    string GetBirthday();//прототип метода получения даты рождения
};