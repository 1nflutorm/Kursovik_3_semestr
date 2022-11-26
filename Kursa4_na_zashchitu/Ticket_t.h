#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ticket_t
{
    string PasportNum;//����� ��������
    string AirFligthNum;//����� ���������
    string TicketNum;//����� ����������
public:
    Ticket_t();//�������� ������������ �� ���������
    Ticket_t(const string& pas, const string& flight, const string& ticket);//�������� ������������ � �����������
    void PrintOne();//�������� ������ ������ ������ �� ����� ������
    string GetPasportNum();//�������� ������ ��������� ������ ���������
    string GetTicketNum();//�������� ������ ��������� ������ ������
    string GetAirFligthNum();//�������� ������ ��������� ������ ���������
};

