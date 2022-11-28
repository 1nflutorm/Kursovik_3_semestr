#pragma once
#include "AirFlight_t.h"
#include <iostream>
#include <string>
using namespace std;

class AirFlightTree_t
{
	struct node
	{
		AirFlight_t* Flight;//указатель на рейс
		int Height;//выоста данного узла
		node* Left;//указатель на левое поддерево
		node* Right;//указатель на правое поддерево
		node(AirFlight_t* flight);//протоип конструктора
	};
	node* Head;

	int GetHeight(node*& head);//прототип закрытого метода получения высоты узла
	int Balance(node*& head);//прототип закрытого метода вычисления баланс фактора
	int FindByAirFlightNum(node*& head, const int& key, int& count);//прототип закрытого метода поиска узла по номеру рейса
	void HeightCalc(node*& head);//прототип закрытого метода расчета высоты поддерева
	void Clear(node*& head);//прототип закрытого метода очищения дерева
	void PrintFlights(node*& head);//прототип закрытого метода вывода на экран всех рейсов
	void FindAndPrintBySubstr(node*& head, const string& substr, int& count);//прототип закрытого метода поиска и вывода по части поля "аэропорт прибытия"
	void SetDefault(node* head);//прототип закрытого метода задания количества мест по умолчанию
	node* RotationRight(node*& NodeToRotate);//прототип закрытого метода правого поворота
	node* RotationLeft(node*& NodeToRotate);//прототип закрытого метода левого поворота
	node* BalanceNode(node*& head);//прототип закрытого метода балансировки узла
	node* FindMin(node*& head); 
	node* Remove(node* head, AirFlight_t*& flight);
	node* RemoveMin(node*& head);
	node* Insert(node*& head, AirFlight_t*& flight);//прототип закрытого метода вставки узла
	AirFlight_t* Find(node*& head, const string& key);//прототип закрытого метода поиска в дереве
public:
	AirFlightTree_t();//прототип конструктора
	~AirFlightTree_t();//прототип деструктора
	int IsEmpty();//прототип метода проверки на пустоту дерева
	int FindByAirFlightNum(const int& key);//прототип метода поиска узла по номеру рейса
	void SetDefault();//прототип метода задания количества мест по умолчанию
	void Clear();//прототип метода очистки дерева
	void PrintFlights();//прототип метода вывода на экран всех полетов
	void FindAndPrintBySubstr(const string& substr, int& count);//прототип метода поиска и вывода по части поля "аэропорт прибытия"
	void Insert(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats);//прототип метода вставки узла
	void Remove(const string& key);//прототип метода удвления узла 
	AirFlight_t* Find(const string& key);//прототип метода поиска
};