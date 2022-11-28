#include "Passenger_t.h"

//���������� ������������ �� ���������
Passenger_t::Passenger_t()
{
    PasportNum = "";
    PlaceOfIssue = "";
    DateOfIssue = "";
    FIO = "";
    Birthday = "";
}
//���������� ������������ � �����������
Passenger_t::Passenger_t(const string& pas, const string& place, const string& date, const string& name, const string& birth)
{
    PasportNum = pas;
    PlaceOfIssue = place;
    DateOfIssue = date;
    FIO = name;
    Birthday = birth;
}
//���������� ������ ��������� ���
string Passenger_t::GetFIO()
{
    return FIO;
}
//���������� ������ ��������� ������ ���������
string Passenger_t::GetPasportNum()
{
    return PasportNum;
}
//���������� ������ ��������� ����� ������
string Passenger_t::GetPlaceOfIssue()
{
    return PlaceOfIssue;
}
//���������� ������ ��������� ���� ������ ��������
string Passenger_t::GetDateOfIssue()
{
    return DateOfIssue;
}
//���������� ������ ��������� ���� ��������
string Passenger_t::GetBirthday()
{
    return Birthday;
}
