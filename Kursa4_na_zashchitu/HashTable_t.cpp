#pragma once
#include "HashTable_t.h"
using namespace std;

//���������� ������������
HashTable_t::HashTable_t()
{
    for (int i = 0; i < SIZE; i++)
        Table[i] = nullptr;//��� ������ ��������� 0
    Size = 0;
}
//���������� �����������
HashTable_t::~HashTable_t()
{
    Clear();//�������� �������
}
//���������� ������ ��������� ����
int HashTable_t::HashFunc(const string& key, const int& i)
{
    int temp = key.find('-'), hash = 0;
    string result = key.substr(temp + 1);//�������� "-"
    hash = stoi(result) + i;//�������� � ������ ����� � �������� �� ���������� ����� ��������� �����������
    return hash % SIZE;//���������� ������� �� ������� �� ������ �������
}
//���������� ������ ���������� �������
int HashTable_t::Push(const string& pas, const string& place, const string& date, const string& name, const string& birth)
{
    if (IsFull())//���� ������� ������
        return 1;//���������� 1 - ������� �����������
    Passenger_t* passanger = new Passenger_t{ pas, place, date, name, birth };//���� ���� �����, ������� ������ ���������
    int hash = HashFunc(passanger->GetPasportNum(), 0);//�������� ��� � ��������� ��������� 0
    if (Table[hash])//���� ������ � ���� ����� ���������
    {
        if (IsMatch(pas, hash))//��������� �� ���������� �� ��������
        {
            return 2;//���������� 2 - ������������ � ������ ������������ ������� ��� ����������
        }
        else//���� ���������� ���
        {
            int index = LineTest(pas);//�������� ������������ ���� ��������� ������
            Table[index] = passanger;//���������� ���� ������ ���������
        }
    }
    else
    {
        Table[hash] = passanger;//���� ���������� ������ ������ �� ������ ���������� ���� ���������
    }
    Size++;//����������� ������� ����������� �����
    return 0;
}
//���������� ������ �������� �� ����������
int HashTable_t::IsMatch(const string& key, const int& hash)
{
    if (!Table[hash])
        return 0;
    if (Table[hash]->GetPasportNum() == key)//���� ����� �������� ��������� � ������
        return 1;//�� ���������� 1
    return 0;//����� 0
}
//���������� ������ ��������� �����������
int HashTable_t::LineTest(const string& key)
{
    int shift = 0;//������ �������
    int start = HashFunc(key, 0);//�������� �������� ������
    for (int i = start + 1; i < SIZE; i++)//���� �� ���������� ������� �� �����
    {
        shift++;//����������� ��������
        int index = HashFunc(key, shift);//�������� ����� ������
        if (!Table[index])//���� ������ �� ������
            return index;//���������� �� ������
    }
    for (int i = 0; i < start; i++)//���� �� ������ ������� �� ��������� �������
    {
        shift++;//����������� ��������
        int index = HashFunc(key, shift);//�������� ����� ������
        if (!Table[index])//���� ������ �������
            return index;//���������� �� ������
    }
    return -1;
}
//���������� ������ ������
int HashTable_t::Find(const string& key)
{
    int start = HashFunc(key, 0), shift = 0, hash = 0;
    if (!Table[start])//���� ������ � ������ �������� ��������, ��������, ��� ������ ��������� ���
        return -1;//������� � �������� -1
    if (IsMatch(key, start))//����� ��������� �� ���������� 
    {
        return start;//� ������ ���������� ���������� ���� ������
    }
    else//���� �� �������
    {
        for (int i = start; i < SIZE; i++)//���� �� ������� ���������� ������� ��������� �����������
        {
            shift++;//����������� ��������
            hash = HashFunc(key, shift);//�������� ����� ������
            if (IsMatch(key, i))//���� ���������
                return i;//���������� ������
        }
        for (int i = 0; i < start; i++)
        {
            shift++;
            hash = HashFunc(key, shift);
            if (IsMatch(key, i))
                return i;
        }
    }
    return -1;
}
//���������� ������ ������� ������ ��������
int HashTable_t::DelOne(const string& key)
{
    int index = Find(key);//�������� ������ � ������� ������� ������
    if (index != -1)//���� ������ ����� -1, �� ������ ��������� ���
    {
        delete Table[index];//������� ��������� ��� ������ ��������
        Table[index] = nullptr;//����������� ����� ������� 0, ��� �������������
        Size--;//��������� ������
        return 1;
    }
    return 0;
}
//���������� ������ �������� �� ��������������� �������
int HashTable_t::IsFull()
{
    if (Size == SIZE)//���� ������ ����� ������������� �������
        return 1;//�������
    return 0;
}
//���������� ������ �������� �� �� ������������� �������
int HashTable_t::IsEmpty()
{
    if (Size == 0)
        return 1;
    return 0;
}
//���������� ������ ������ �� ���
int HashTable_t::FindByFIO(const string& fio)
{
    int CountOfOutputed = 0;//������� ��������� �� �����
    for (int i = 0; i < SIZE; i++)
    {
        if (!Table[i])//���� ������ �� ��������, ��������� �� ���������� �������� �����
            continue;
        if (Table[i]->GetFIO() == fio)//���� ������ �� ������� ��������� � ���, ��� �����
        {
            PrintOne(i);//������� ������ �� ���� ���������
            CountOfOutputed++;//����������� ������� ���������� �� �����
        }
    }
    if (!CountOfOutputed)//���� ������ �� ������
        return -1;//���������� -1
    else
        return 0;
}
//���������� ������ ������ ������ � ��������� �� ��� ��������
int HashTable_t::FindAndPrintByPassportNum(const string& key)
{
    int index = Find(key);//������� ������� ���������
    if (index == -1)//���� ��� ������ ����� -1, ������ ������ ��������� ���
    {
        return index;
    }
    else//�����
    {
        PrintOne(index);//������� ������ � ���
        return 0;
    }
}
//���������� ������ ������ �� ����� ������ � ����������, �������� ����� �� ������������ ��������
int HashTable_t::PrintAllPassengersByAirFlight(TicketList_t& List_, const string& key)
{
    int count = 0;
    auto current = List_.GetHead();
    string FlightNum = key;
    for (int i = 0; i < List_.GetSize() - 1; i++)//���� �� ������� ������
    {
        if (current->ticket->GetAirFligthNum() == FlightNum)//���� ��������� ��������
        {
            int index = Find(current->ticket->GetPasportNum());//������� ���������
            PrintOne(index);
            count++;//����������� �������
        }
        current = current->pNext;//������������ �� ������
    }
    return count;
}
//���������� ������ ������ ������
void HashTable_t::Clear()
{
    for (int i = 0; i < SIZE; i++)//���� �� ������� �������
    {
        if (Table[i])//���� ������ ���������
        {
            delete Table[i];//������� ���
            Table[i] = nullptr;//������������ 0 ��� �������������
        }
    }
    Size = 0;//������, �������������, ���������� 0
}
//���������� ������ ������ ������ �� ����� ���������
void HashTable_t::PrintOne(const int& index)
{
    cout << "��� ���������: " << Table[index]->GetFIO() << endl;
    cout << "����� �������� ���������: " << Table[index]->GetPasportNum() << endl;
    cout << "����� ������ ��������: " << Table[index]->GetPlaceOfIssue() << endl;
    cout << "���� ������ ��������: " << Table[index]->GetDateOfIssue() << endl;
    cout << "���� �������� ���������: " << Table[index]->GetBirthday() << endl << endl;
}
//���������� ������ ������ ���� ���������� �� �����
void HashTable_t::PrintAll()
{
    for (int i = 0; i < SIZE; i++)//���� �� ������� �������
    {
        if (!Table[i])//���� ������ �� ��������
            continue;//��������� �� ��������� �������� �����
        PrintOne(i);//����� ������� ����� � ���������
    }
}
