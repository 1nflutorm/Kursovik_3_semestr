#pragma once
#include <iostream>
#include <string>
using namespace std;

class AirFlight_t
{
    string AirFlightNum;//номер авиарейса
    string Company;//авиакомпани€
    string DepartureAirport;//аэропорт отправлени€
    string ArriveAirport;//аэропорт прибыти€
    string DepartureDate;//дата отправлени€
    string DepartureTime;//врем€ отправлени€
    int NumberOfSeats;//количество мест на борту
    int NumberOfAvailableSeats;//количество свободных мест на борту
public:
    AirFlight_t();//прототип конструктора по умолчанию
    AirFlight_t(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats);//прототип конструктора с параметрами€Є
    int GetAvailableSeats();//прототип метода получани€ количества свободных мест
    int GetNumberOfSeats();
    int CovertTo();//прототип метода конвертировани€ номера авиарейса
    void Print();//прототип метода вывода на экран
    void DecrementNumberOfAvailableSeats();//прототип метода уменьшени€ количества свободных мест
    void IncrementNumberOfAvailableSeats();//прототип метода увеличени€ количества свободных мест
    void SetNumberOfSeats(const int& seats);
    string GetArriveAirport();//прототип метода получени€ аэропорта прибыти€
    string GetAirFlightNum();//прототип метода получени€ номера авиарейса
};

