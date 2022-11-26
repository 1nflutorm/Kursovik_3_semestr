#include "Ticket_t.h"

//реализация конструктора по умолчанию
Ticket_t::Ticket_t()
{
	PasportNum = "";
	AirFligthNum = "";
	TicketNum = "";
}
//реализация конструктора с параметрами
Ticket_t::Ticket_t(const string& pas, const string& flight, const string& ticket)
{
	PasportNum = pas;
	AirFligthNum = flight;
	TicketNum = ticket;
}
//реализация метода вывода на экран данных об одном билете
void Ticket_t::PrintOne()
{
	cout << "Номер паспорта: " << PasportNum << endl;
	cout << "Номер авиарейса: " << AirFligthNum << endl;
	cout << "Номер билета: " << TicketNum << endl;
	cout << endl;
}
//реализация метода получения номера паспорта
string Ticket_t::GetPasportNum()
{
	return PasportNum;
}
//реализация метода получения номера авиабилета
string Ticket_t::GetTicketNum()
{
	return TicketNum;
}
//реализация метода получения номера авиарейса
string Ticket_t::GetAirFligthNum()
{
	return AirFligthNum;
}
