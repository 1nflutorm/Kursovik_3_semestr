#include "MainFunctions.h"

numbers::numbers(char symb, int position)
{
	this->position = position;
	this->symb = symb;
}
//���������� ������� �������� ������������ ���������� ������
int IsCorrectPas(const string& key)
{
	if (key.length() != 11 || key.find('-') != 4)
		return 0;
	return 1;
}
//���������� ������� �������� ������������ ������ ���������
int IsCorrectFlight(const string& key)
{
	if (key.length() != 7 || key.find('-') != 3)
		return 0;
	return 1;
}
//���������� ������� ���������������
int Convert(const string& key)
{
	int temp = key.find('-');
	char Letter;
	string ConvertFlight;
	string PartToConvert = key.substr(0, temp);
	for (int i = 0; i < 3; i++)
	{
		Letter = PartToConvert[i];
		int symbol = (int)(tolower(Letter)) - 50;
		ConvertFlight += to_string(symbol);
	}
	ConvertFlight += key.substr(temp + 1);
	return stoi(ConvertFlight);
}
//���������� ������� ���������� �������� � �����
int Shift(vector<numbers*> vec, char symb)
{
	for (int itr = 0; itr < vec.size(); itr++)
	{
		if (vec[itr]->symb == symb)//���� ����� ������ � �������
			return vec[itr]->position;//���������� ��� ��������
	}
	return vec[vec.size() - 1]->position;//���� �� ����� ���������� �������� ������������ �������
}
//���������� ������� ������ ����� � ������ ������ � ����
int BouerAndMoor(const string& str, const string& substr)
{
	int lensubstr = substr.length();
	if (str.length() < lensubstr)
		return 0;
	vector<numbers*> vec = CutString(substr);//�������� ������ ���������
	int CountOfSame = 0;//������� ����������
	for (int i = 0; i < str.length(); i++)//���� �� ����� ������
	{
		for (int j = lensubstr - 1; j >= 0; j--)//������� �� ������� �������� � ���������� ��������
		{
			if (i + j > str.length() - 1)//���� ����� �� ����� ������� �� ������ �� �������
				return 0;
			if (str[i + j] != substr[j])//���� ������ �� ������
			{
				i += Shift(vec, str[i + j]) - 1;//���� �������� � ������� 
				break;
			}
			else//���� ������ �� ����������� ������� ����������
			{
				CountOfSame++;
			}
			//if (CountOfSame == lensubstr)
				//return 1;
		}
		if (CountOfSame == lensubstr)//���� ������� ���������� ����� ����� ��������� �� ������ ����� ����� � ������ ����
			return 1;
		CountOfSame = 0;
	}
	return 0;
}
//���������� ������� ��������� �� ������ ��������� ��������
vector<numbers*> CutString(const string& substr)
{
	vector<numbers*> vec;
	int lensubstr = substr.length();//������� ����� ������
	bool repeat = 0;//���������� ��������
	int count = 1;//���������� ����� �������
	for (int i = lensubstr - 2; i >= 0; i--)//���� �� �������������� ������� � ��������� �� �������(��������) 
	{
		for (int itr = 0; itr < vec.size(); itr++)//���� �� ����� �������
		{
			if (vec[itr]->symb == substr[i])//���� ����� ������ ��� ����
			{
				repeat = 1;//�� ���������� ���������� 1
				break;
			}
		}
		if (!repeat)//���� �� ���� ����������
		{
			numbers* temp = new numbers{ substr[i], count };//��������� ����� �������
			vec.push_back(temp);//������������ � ������
		}
		count++;//���������� ����� ������������� � ����� ������
		repeat = 0;//���������� ����������
	}
	for (int itr = 0; itr < vec.size(); itr++)//������ ������ ��� ���������� �������� ���������
	{
		if (vec[itr]->symb == substr[lensubstr - 1])//����� �� ������� � ���� ���� ������
		{
			numbers* temp = new numbers{ vec[itr]->symb, vec[itr]->position };//���� ����� ���������� ����� ������� � ������ � ���������� ������� ���������� ��������
			repeat = 1;//���������� ����� 1
			vec.push_back(temp);
			break;
		}
	}
	if (!repeat)//���� �� ���� ����������
	{
		numbers* temp = new numbers{ substr[lensubstr - 1], count };//������� ����� �������
		vec.push_back(temp);//���������� ��� � ������
	}
	numbers* temp = new numbers{ '~', count };//� ��������� ������� ���������� ����������� ������ � ������ ���������� ������� �� ��� ������, ���� �� ���� ������ �� ��������� �� ������
	vec.push_back(temp);//���������� ��� � �����
	return vec;//���������� ������� ������
}
//���������� ������� ������ ����
void PrintMenu()
{
	cout << "���� ������ ��������: " << endl;
	cout << "0. ��������� ������ ���������" << endl;
	cout << "1. ���������������� ������ ���������" << endl;
	cout << "2. ������� ������ � ���������" << endl;
	cout << "3. ������� ������ � ���� ������������������ ����������" << endl;
	cout << "4. ��������� ������ � ����������" << endl;
	cout << "5. ����� ��������� �� ������ ���������" << endl;
	cout << "6. ����� ��������� �� ��� ���" << endl;
	cout << "7. ���������� ������ ���������" << endl;
	cout << "8. �������� �������� �� ���������" << endl;
	cout << "9. ������� ������ � ���� ����������" << endl;
	cout << "10. ��������� ������ �� ����������" << endl;
	cout << "11. ����� ��������� �� ��� ������" << endl;
	cout << "12. ����� ��������� �� ���������� �������� ��������� ��������" << endl;
	cout << "13. ����������� ������� ��������� ����������" << endl;
	cout << "14. ����������� �������� ���������� ����������" << endl;
	cout << "��� �����: ";
}

void PushPassengers(HashTable_t& Table, const string& pas)
{
	string PasportNum;//����� ��������
	string PlaceOfIssue;//����� ������
	string DateOfIssue;//���� ������
	string FIO;//���
	string Birthday;//���� ��������
	string str;
	fstream fin;
	fin.open(pas);
	if (!fin.is_open())
	{
		cout << "error" << endl;
	}
	else
	{
		while (!fin.eof())
		{
			getline(fin, PasportNum);
			getline(fin, PlaceOfIssue);
			getline(fin, DateOfIssue);
			getline(fin, FIO);
			getline(fin, Birthday);
			getline(fin, str);
			Table.Push(PasportNum, PlaceOfIssue, DateOfIssue, FIO, Birthday);
		}
	}
}

void PushAirFlights(AirFlightTree_t& Tree, const string& pas)
{
	string AirFlightNum;//����� ���������
	string Company;//������������
	string DepartureAirport;//�������� �����������
	string ArriveAirport;//�������� ��������
	string DepartureDate;//���� �����������
	string DepartureTime;//����� �����������
	int NumberOfSeats;//���������� ���� �� �����
	string str;
	fstream fin;
	fin.open(pas);
	if (!fin.is_open())
	{
		cout << "error" << endl;
	}
	else
	{
		while (!fin.eof())
		{
			getline(fin, AirFlightNum);
			getline(fin, Company);
			getline(fin, DepartureAirport);
			getline(fin, ArriveAirport);
			getline(fin, DepartureDate);
			getline(fin, DepartureTime);
			getline(fin, str);
			NumberOfSeats = stoi(str);
			getline(fin, str);
			Tree.Insert(AirFlightNum, Company, DepartureAirport, ArriveAirport, DepartureDate, DepartureTime, NumberOfSeats);
		}
	}
}

void PushTickets(AirFlightTree_t& Tree, TicketList_t& List, const string& pas)
{
	string PasportNum;//����� ��������
	string AirFligthNum;//����� ���������
	string TicketNum;//����� ����������
	string str;
	fstream fin;
	fin.open(pas);
	if (!fin.is_open())
	{
		cout << "error" << endl;
	}
	else
	{
		while (!fin.eof())
		{
			getline(fin, PasportNum);
			getline(fin, AirFligthNum);
			getline(fin, TicketNum);
			getline(fin, str);
			auto node = Tree.Find(AirFligthNum);
			node->DecrementNumberOfAvailableSeats();
			List.PushBack(PasportNum, AirFligthNum, TicketNum);
		}
	}
}
