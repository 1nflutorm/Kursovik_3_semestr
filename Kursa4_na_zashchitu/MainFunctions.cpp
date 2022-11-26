#include "MainFunctions.h"

numbers::numbers(char symb, int position)
{
	this->position = position;
	this->symb = symb;
}
//реализация функции проверки корректности поспотрных данных
int IsCorrectPas(const string& key)
{
	if (key.length() != 11 || key.find('-') != 4)
		return 0;
	return 1;
}
//реализация функции проверки корректности номера авиарейса
int IsCorrectFlight(const string& key)
{
	if (key.length() != 7 || key.find('-') != 3)
		return 0;
	return 1;
}
//реализация функции конвертирования
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
//реализация функции вычисления смещения в слове
int Shift(vector<numbers*> vec, char symb)
{
	for (int itr = 0; itr < vec.size(); itr++)
	{
		if (vec[itr]->symb == symb)//если нашли символ в векторе
			return vec[itr]->position;//возвращаем его смещение
	}
	return vec[vec.size() - 1]->position;//если не нашли возвращаем смещение специального символа
}
//реализация функции поиска слова в тексте Боуэра и Мура
int BouerAndMoor(const string& str, const string& substr)
{
	int lensubstr = substr.length();
	if (str.length() < lensubstr)
		return 0;
	vector<numbers*> vec = CutString(substr);//получаем вектор элементов
	int CountOfSame = 0;//счетчик совпадений
	for (int i = 0; i < str.length(); i++)//идем до длины строки
	{
		for (int j = lensubstr - 1; j >= 0; j--)//сверять со строкой начинаем с последнего элемента
		{
			if (i + j > str.length() - 1)//если вышли за грань массива то строка не найдена
				return 0;
			if (str[i + j] != substr[j])//если символ не совпал
			{
				i += Shift(vec, str[i + j]) - 1;//ищем смещение в векторе 
				break;
			}
			else//если совпал то увеличиваем счетчик совпадений
			{
				CountOfSame++;
			}
			//if (CountOfSame == lensubstr)
				//return 1;
		}
		if (CountOfSame == lensubstr)//если счетчки совпадений равен длине подстроки то значит такое слово в строке есть
			return 1;
		CountOfSame = 0;
	}
	return 0;
}
//реализация функции выделения из строки отдельных символов
vector<numbers*> CutString(const string& substr)
{
	vector<numbers*> vec;
	int lensubstr = substr.length();//находим длину строки
	bool repeat = 0;//повторение символов
	int count = 1;//порятковый номер символа
	for (int i = lensubstr - 2; i >= 0; i--)//цикл от предпоследнего символа в подстроке до первого(нулевого) 
	{
		for (int itr = 0; itr < vec.size(); itr++)//цикл по длине вектора
		{
			if (vec[itr]->symb == substr[i])//если такой символ уже есть
			{
				repeat = 1;//то повторение становится 1
				break;
			}
		}
		if (!repeat)//если не было повторения
		{
			numbers* temp = new numbers{ substr[i], count };//создается новый элемент
			vec.push_back(temp);//записывается в вектор
		}
		count++;//порядковый номер увеличивается в любом случае
		repeat = 0;//повторение обнуляется
	}
	for (int itr = 0; itr < vec.size(); itr++)//теперь случай для последнего элемента подстроки
	{
		if (vec[itr]->symb == substr[lensubstr - 1])//бежим по вектору и ищем этот символ
		{
			numbers* temp = new numbers{ vec[itr]->symb, vec[itr]->position };//если нашли записываем новый элемент в вектор с порядковым номером совпавшего элемента
			repeat = 1;//повторение равно 1
			vec.push_back(temp);
			break;
		}
	}
	if (!repeat)//если не было повторения
	{
		numbers* temp = new numbers{ substr[lensubstr - 1], count };//создаем новый элемент
		vec.push_back(temp);//записываем его в вектор
	}
	numbers* temp = new numbers{ '~', count };//в последнюю очередь записываем специальеый символ с нужным порядковым номером на тот случай, если ни один символ из подстроки не совпал
	vec.push_back(temp);//записываем его в вектр
	return vec;//вохвращаем готовый вектор
}
//реализация функции печати меню
void PrintMenu()
{
	cout << "Меню выбора операции: " << endl;
	cout << "0. Завершить работу программы" << endl;
	cout << "1. Зарегестрировать нового пассажира" << endl;
	cout << "2. Удалить данные о пассажире" << endl;
	cout << "3. Вывести данные о всех зарегистрированных пассажирах" << endl;
	cout << "4. Отчистить данные о пассажирах" << endl;
	cout << "5. Поиск пассажира по номеру пасспорта" << endl;
	cout << "6. Поиск пассажира по его ФИО" << endl;
	cout << "7. Добавление нового авиарейса" << endl;
	cout << "8. Удаление сведений об авиарейсе" << endl;
	cout << "9. Вывести данные о всех авиарейсах" << endl;
	cout << "10. Отчистить данные об авиарейсах" << endl;
	cout << "11. Поиск авиарейса по его номеру" << endl;
	cout << "12. Поиск авиарейса по фрагментам названия аэропорта прибытия" << endl;
	cout << "13. Регистрация продажи пассажиру авиабилета" << endl;
	cout << "14. Регистрация возврата рассажиром авиабилета" << endl;
	cout << "Ваш выбор: ";
}

void PushPassengers(HashTable_t& Table, const string& pas)
{
	string PasportNum;//номер паспорта
	string PlaceOfIssue;//место выдачи
	string DateOfIssue;//дата выдачи
	string FIO;//ФИО
	string Birthday;//день рождения
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
	string AirFlightNum;//номер авиарейса
	string Company;//авиакомпания
	string DepartureAirport;//аэропорт отправления
	string ArriveAirport;//аэропорт прибытия
	string DepartureDate;//дата отправления
	string DepartureTime;//время отправления
	int NumberOfSeats;//количество мест на борту
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
	string PasportNum;//номер паспорта
	string AirFligthNum;//номер авиарейса
	string TicketNum;//номер авиабитела
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
