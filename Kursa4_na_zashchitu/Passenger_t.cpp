#include "Passenger_t.h"

//реализация конструктора по умолчанию
Passenger_t::Passenger_t()
{
    PasportNum = "";
    PlaceOfIssue = "";
    DateOfIssue = "";
    FIO = "";
    Birthday = "";
}
//реализация конструктора с параметрами
Passenger_t::Passenger_t(const string& pas, const string& place, const string& date, const string& name, const string& birth)
{
    PasportNum = pas;
    PlaceOfIssue = place;
    DateOfIssue = date;
    FIO = name;
    Birthday = birth;
}
//реализация метода получения ФИО
string Passenger_t::GetFIO()
{
    return FIO;
}
//реализация метода получения номера пасспорта
string Passenger_t::GetPasportNum()
{
    return PasportNum;
}