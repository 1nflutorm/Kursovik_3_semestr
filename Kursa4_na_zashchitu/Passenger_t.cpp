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
//реализация метода получения места выдачи
string Passenger_t::GetPlaceOfIssue()
{
    return PlaceOfIssue;
}
//реализация метода получения даты выдачи паспорта
string Passenger_t::GetDateOfIssue()
{
    return DateOfIssue;
}
//реализация метода получения даты рождения
string Passenger_t::GetBirthday()
{
    return Birthday;
}
