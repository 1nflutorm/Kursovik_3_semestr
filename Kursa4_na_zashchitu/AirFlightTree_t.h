#pragma once
#include "AirFlight_t.h"
#include <iostream>
#include <string>
using namespace std;

class AirFlightTree_t
{
	struct node
	{
		AirFlight_t* Flight;
		int Height;
		node* Left;
		node* Right;
		node(AirFlight_t* flight);
	};
	node* Head;

	int GetHeight(node*& head);
	int Balance(node*& head);
	int FindByAirFlightNum(node*& head, const int& key, int& count);
	void HeightCalc(node*& head);
	void Clear(node*& head);
	void PrintFlights(node*& head);
	void FindAndPrintBySubstr(node*& head, const string& substr, int& count);
	node* RotationRight(node*& NodeToRotate);
	node* RotationLeft(node*& NodeToRotate);
	node* BalanceNode(node*& head);
	node* FindMin(node*& head);
	node* Remove(node* head, AirFlight_t*& flight);
	node* RemoveMin(node*& head);
	node* Insert(node*& head, AirFlight_t*& flight);
	AirFlight_t* Find(node*& head, const string& key);
public:
	AirFlightTree_t();
	~AirFlightTree_t();
	int IsEmpty();
	node* GetHead();
	void Clear();
	void SetHead(node*& head);
	void PrintFlights();
	void FindAndPrintBySubstr(const string& substr, int& count);
	void Insert(const string& flightNum, const string& company, const string& departure, const string& arrive, const string& date, const string& time, const int& seats);
	void Remove(const string& key);
	AirFlight_t* Find(const string& key);
	int FindByAirFlightNum(const int& key);
	void SetDefault(node* head);
	void SetDefault();
	

};