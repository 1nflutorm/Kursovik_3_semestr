#pragma once
#include <string>
using namespace std;

//�������� ������ ���������
class Passenger_t
{
    string PasportNum;//����� ��������
    string PlaceOfIssue;//����� ������
    string DateOfIssue;//���� ������
    string FIO;//���
    string Birthday;//���� ��������
public:
    Passenger_t();//�������� ������������ �� ���������
    Passenger_t(const string& pas, const string& place, const string& date, const string& name, const string& birth);//�������� ������������ � �����������
    string GetFIO();//�������� ������ ��������� �����
    string GetPasportNum();//�������� ������ ��������� ������ ���������
};