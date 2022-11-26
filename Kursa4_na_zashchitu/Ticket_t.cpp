#include "Ticket_t.h"

//���������� ������������ �� ���������
Ticket_t::Ticket_t()
{
	PasportNum = "";
	AirFligthNum = "";
	TicketNum = "";
}
//���������� ������������ � �����������
Ticket_t::Ticket_t(const string& pas, const string& flight, const string& ticket)
{
	PasportNum = pas;
	AirFligthNum = flight;
	TicketNum = ticket;
}
//���������� ������ ������ �� ����� ������ �� ����� ������
void Ticket_t::PrintOne()
{
	cout << "����� ��������: " << PasportNum << endl;
	cout << "����� ���������: " << AirFligthNum << endl;
	cout << "����� ������: " << TicketNum << endl;
	cout << endl;
}
//���������� ������ ��������� ������ ��������
string Ticket_t::GetPasportNum()
{
	return PasportNum;
}
//���������� ������ ��������� ������ ����������
string Ticket_t::GetTicketNum()
{
	return TicketNum;
}
//���������� ������ ��������� ������ ���������
string Ticket_t::GetAirFligthNum()
{
	return AirFligthNum;
}
