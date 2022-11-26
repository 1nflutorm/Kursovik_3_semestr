#include "AirFlight_t.h"

//���������� ������������ �� ���������
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
//���������� ������������ � �����������
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
//���������� ������ ��������������� ������ ���������
int AirFlight_t::CovertTo()
{
    int temp = AirFlightNum.find('-');
    char Letter;//������ ��� �������� ���� ������������
    string ConvertFlight;//������-����� ������� ����� ����������������� ����� ���������
    string PartToConvert = AirFlightNum.substr(0, temp);//����� ��� ��������������� (��� ������������)
    for (int i = 0; i < 3; i++)
    {
        Letter = PartToConvert[i];//�������� �����
        int c = (int)(tolower(Letter)) - 50;//�������� � ������� ������� � �������� 50 ��� ���������������� ��������� 2-� �������� ����� 
        ConvertFlight += to_string(c);//��������� � �������� ������
    }
    ConvertFlight += AirFlightNum.substr(temp + 1);//��������� ���������� �����
    return stoi(ConvertFlight);//���������� ������, ��������������� � int
}
//���������� ������ ��������� ��������� ����
int AirFlight_t::GetAvailableSeats()
{
    return NumberOfAvailableSeats;
}
int AirFlight_t::GetNumberOfSeats()
{
    return NumberOfSeats;
}
//���������� ������ ������
void AirFlight_t::Print()
{
    cout << "����� ���������: " << AirFlightNum << endl;
    cout << "������������: " << Company << endl;
    cout << "�������� �����������: " << DepartureAirport << endl;
    cout << "�������� ��������: " << ArriveAirport << endl;
    cout << "���� �����������: " << DepartureDate << endl;
    cout << "����� �����������: " << DepartureTime << endl;
    cout << "���������� ���� � ��������: " << NumberOfSeats << endl;
    cout << "���������� ��������� ����: " << NumberOfAvailableSeats << endl << endl;
}
//���������� ������ ���������� ���������� ��������� ����
void AirFlight_t::DecrementNumberOfAvailableSeats()
{
    NumberOfAvailableSeats--;
}
//���������� ������ ���������� ���������� ��������� ����
void AirFlight_t::IncrementNumberOfAvailableSeats()
{
    NumberOfAvailableSeats++;
}

void AirFlight_t::SetNumberOfSeats(const int& seats)
{
    NumberOfAvailableSeats = seats;
}
//���������� ������ ��������� ��������� ��������
string AirFlight_t::GetArriveAirport()
{
    return ArriveAirport;
}
//���������� ������ ��������� ������ ���������
string AirFlight_t::GetAirFlightNum()
{
    return AirFlightNum;
}