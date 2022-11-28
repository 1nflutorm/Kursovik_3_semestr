#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Passenger_t.h"
#include "TicketList_t.h"
#include "AirFlight_t.h"
#define SIZE 100
using namespace std;

class HashTable_t
{
    Passenger_t* Table[SIZE];//���������������� �� ����������
    int Size;//���������� ����������� �����

    int HashFunc(const string& key, const int& i);//�������� ������ ��������� ����
    int IsMatch(const string& key, const int& hash);//�������� ������ ����������
    int LineTest(const string& key);//�������� ������ ��������� �����������
public:
    HashTable_t();//�������� ������������
    ~HashTable_t();//�������� �����������
    int Push(const string& pas, const string& place, const string& date, const string& name, const string& birth);//�������� ������ ����������
    int Find(const string& key);//�������� ������ ������ � �������
    int DelOne(const string& key);//�������� ������ �������� 
    int IsFull();//�������� ������ �������� �� ������������� ������
    int IsEmpty();////�������� ������ �������� �� ���������� �������������
    int FindByFIO(const string& fio);//�������� ������ ������ �� ���
    int FindAndPrintByPassportNum(const string& fio);//�������� ������ ������ � ������ �� ������ ��������
    void Clear();//�������� ������ ������� �������
    void PrintOne(const int& index);//�������� ������ ������ �� ����� ������ �� ����� ���������
    void PrintAll();//�������� ������ ������ �� ����� ���� ����������
    int PrintAllPassengersByAirFlight(TicketList_t& List_, const string& key);
};