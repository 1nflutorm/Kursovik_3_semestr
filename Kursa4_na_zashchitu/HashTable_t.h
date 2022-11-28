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
    Passenger_t* Table[SIZE];//массивуказателей на пассажиров
    int Size;//количество заполненных ячеек

    int HashFunc(const string& key, const int& i);//прототип метода получения хэша
    int IsMatch(const string& key, const int& hash);//прототип метода стравнения
    int LineTest(const string& key);//прототип метода линейного опробования
public:
    HashTable_t();//прототип конструктора
    ~HashTable_t();//прототип деструкторв
    int Push(const string& pas, const string& place, const string& date, const string& name, const string& birth);//прототип метода заполнения
    int Find(const string& key);//прототип метода поиска в таблице
    int DelOne(const string& key);//прототип метода удаления 
    int IsFull();//прототип метода проверки на заполненность табицы
    int IsEmpty();////прототип метода проверки на отсутствие заполненности
    int FindByFIO(const string& fio);//прототип метода поиска по ФИО
    int FindAndPrintByPassportNum(const string& fio);//прототип метода поиска и вывода по номеру паспорта
    void Clear();//прототип метода очистки таблицы
    void PrintOne(const int& index);//прототип метода вывода на экран данныъ об одном пассажире
    void PrintAll();//прототип метода вывода на экран всех пассажиров
    int PrintAllPassengersByAirFlight(TicketList_t& List_, const string& key);
};