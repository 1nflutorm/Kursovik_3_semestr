#include "AirFlight_t.h"

//реализация конструктора по умолчанию
AirFlight_t::AirFlight_t()
{
    AirFlightNum = "";
    Company = "";
    DepartureAirport = "";
    ArriveAirport = "";
    DepartureDate = "";
    DepartureTime = "";
    NumberOfSeats = 0;
    NumberOfAvailableSeats = 0;
}
//реализация конструктора с параметрами
AirFlight_t::AirFlight_t(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats)
{
    AirFlightNum = flightNum;
    Company = company;
    DepartureAirport = departure;
    ArriveAirport = arrive;
    DepartureDate = date;
    DepartureTime = time;
    NumberOfSeats = seats;
    NumberOfAvailableSeats = seats;
}
//реализация метода конвертирования номера аэропорта
int AirFlight_t::CovertTo()
{
    int temp = AirFlightNum.find('-');
    char Letter;//символ для хранения кода авиакомпании
    string ConvertFlight;//строка-чисто которое храни конвертированноый номер авиарейса
    string PartToConvert = AirFlightNum.substr(0, temp);//часть для конвертирования (код авиакомпании)
    for (int i = 0; i < 3; i++)
    {
        Letter = PartToConvert[i];//выделяем букву
        int c = (int)(tolower(Letter)) - 50;//приводим к нижнему ругитру и вычитаем 50 для гарантированного получения 2-х значного числа 
        ConvertFlight += to_string(c);//добавляем к итоговой строке
    }
    ConvertFlight += AirFlightNum.substr(temp + 1);//добавляем оставшуюся часть
    return stoi(ConvertFlight);//возвращаем строку, преобрпзованную в int
}
//реализация метода получения свободных мест
int AirFlight_t::GetAvailableSeats()
{
    return NumberOfAvailableSeats;
}
int AirFlight_t::GetNumberOfSeats()
{
    return NumberOfSeats;
}
//реализация метода вывода
void AirFlight_t::Print()
{
    cout << "Номер авиарейса: " << AirFlightNum << endl;
    cout << "Авиакомпания: " << Company << endl;
    cout << "Аэропорт отправления: " << DepartureAirport << endl;
    cout << "Аэропорт прибытия: " << ArriveAirport << endl;
    cout << "Дата отправления: " << DepartureDate << endl;
    cout << "Время отправления: " << DepartureTime << endl;
    cout << "Количество мест в самолете: " << NumberOfSeats << endl;
    cout << "Количество свободных мест: " << NumberOfAvailableSeats << endl << endl;
}
//реализация метода уменьшения количества доступных мест
void AirFlight_t::DecrementNumberOfAvailableSeats()
{
    NumberOfAvailableSeats--;
}
//реализация метода увеличения количества доступных мест
void AirFlight_t::IncrementNumberOfAvailableSeats()
{
    NumberOfAvailableSeats++;
}

void AirFlight_t::SetNumberOfSeats(const int& seats)
{
    NumberOfAvailableSeats = seats;
}
//реализация метода получения аэропорта прибытия
string AirFlight_t::GetArriveAirport()
{
    return ArriveAirport;
}
//реализация метода получения номера авиарейса
string AirFlight_t::GetAirFlightNum()
{
    return AirFlightNum;
}