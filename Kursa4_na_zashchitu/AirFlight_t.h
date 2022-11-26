#pragma once
#include <iostream>
#include <string>
using namespace std;

class AirFlight_t
{
    string AirFlightNum;//����� ���������
    string Company;//������������
    string DepartureAirport;//�������� �����������
    string ArriveAirport;//�������� ��������
    string DepartureDate;//���� �����������
    string DepartureTime;//����� �����������
    int NumberOfSeats;//���������� ���� �� �����
    int NumberOfAvailableSeats;//���������� ��������� ���� �� �����
public:
    AirFlight_t();//�������� ������������ �� ���������
    AirFlight_t(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats);//�������� ������������ � �������������
    int GetAvailableSeats();//�������� ������ ��������� ���������� ��������� ����
    int GetNumberOfSeats();
    int CovertTo();//�������� ������ ��������������� ������ ���������
    void Print();//�������� ������ ������ �� �����
    void DecrementNumberOfAvailableSeats();//�������� ������ ���������� ���������� ��������� ����
    void IncrementNumberOfAvailableSeats();//�������� ������ ���������� ���������� ��������� ����
    void SetNumberOfSeats(const int& seats);
    string GetArriveAirport();//�������� ������ ��������� ��������� ��������
    string GetAirFlightNum();//�������� ������ ��������� ������ ���������
};

