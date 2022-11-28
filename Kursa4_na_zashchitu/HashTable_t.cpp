#pragma once
#include "HashTable_t.h"
using namespace std;

//реализация конструктора
HashTable_t::HashTable_t()
{
    for (int i = 0; i < SIZE; i++)
        Table[i] = nullptr;//все ячейки заполняем 0
    Size = 0;
}
//реализация деструктора
HashTable_t::~HashTable_t()
{
    Clear();//очищение таблицы
}
//реализация метода получения хэша
int HashTable_t::HashFunc(const string& key, const int& i)
{
    int temp = key.find('-'), hash = 0;
    string result = key.substr(temp + 1);//вырезаем "-"
    hash = stoi(result) + i;//приводим к целому числу и сдвигаем на количество шагов линейного опробования
    return hash % SIZE;//возвращаем остаток от делания на размер таблицы
}
//реализация метода заполнения таблицы
int HashTable_t::Push(const string& pas, const string& place, const string& date, const string& name, const string& birth)
{
    if (IsFull())//если таблица полная
        return 1;//возвращаем 1 - таблица переполнена
    Passenger_t* passanger = new Passenger_t{ pas, place, date, name, birth };//еоси есть место, создаем нового пассажира
    int hash = HashFunc(passanger->GetPasportNum(), 0);//получаем хэш с начальнвм смещением 0
    if (Table[hash])//если ячейка с тамм хэшем заполнена
    {
        if (IsMatch(pas, hash))//проверяем на совпадение по паспотру
        {
            return 2;//возвращаем 2 - пользователь с такими пасспортными данными уже существует
        }
        else//если совпадения нет
        {
            int index = LineTest(pas);//линейным опробованием ищем свободную ячейку
            Table[index] = passanger;//записываем туда нашего пассажира
        }
    }
    else
    {
        Table[hash] = passanger;//если изначально яцейка пустая то просто записываем туда пассажира
    }
    Size++;//увеличиваем счетчик заполненных ячеек
    return 0;
}
//реализация метода проверки на совпадение
int HashTable_t::IsMatch(const string& key, const int& hash)
{
    if (!Table[hash])
        return 0;
    if (Table[hash]->GetPasportNum() == key)//если номер паспорта совпадает с ключом
        return 1;//то возвразаем 1
    return 0;//иначе 0
}
//реализация метода линейного опробования
int HashTable_t::LineTest(const string& key)
{
    int shift = 0;//индекс смщение
    int start = HashFunc(key, 0);//полуяаем исходный индекс
    for (int i = start + 1; i < SIZE; i++)//идем от начального индекса до конца
    {
        shift++;//увеличиваем смещение
        int index = HashFunc(key, shift);//получаем новый индекс
        if (!Table[index])//если ячейка не занята
            return index;//возвращяем ее индекс
    }
    for (int i = 0; i < start; i++)//идем он начала таблицы до исходного индекса
    {
        shift++;//увеличиваем смещение
        int index = HashFunc(key, shift);//получаем новый индекс
        if (!Table[index])//если яцейка сободна
            return index;//возвращаем ее индекс
    }
    return -1;
}
//реализация метода поиска
int HashTable_t::Find(const string& key)
{
    int start = HashFunc(key, 0), shift = 0, hash = 0;
    if (!Table[start])//если ячейка с нужным индексом свободна, очевидно, что такого пассажира нет
        return -1;//выходим с индексом -1
    if (IsMatch(key, start))//иначе проверяем на совпадение 
    {
        return start;//в случае совпадения возвращаем этот индекс
    }
    else//если не совпали
    {
        for (int i = start; i < SIZE; i++)//идем по таблтце аналогично функции линейного опробования
        {
            shift++;//увеличиваем смещение
            hash = HashFunc(key, shift);//получаем новый индекс
            if (IsMatch(key, i))//если совпадает
                return i;//возвращаем индекс
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
//реализация метода удалени одного пасажира
int HashTable_t::DelOne(const string& key)
{
    int index = Find(key);//получаем индекс с помощью функции поиска
    if (index != -1)//если индекс равен -1, то такого пассажира нет
    {
        delete Table[index];//удаляем пассажира под нужным индексом
        Table[index] = nullptr;//присваеваем этому индексу 0, для перестраховки
        Size--;//уменьшаем размер
        return 1;
    }
    return 0;
}
//реализация метода проверки на переполненность таблицы
int HashTable_t::IsFull()
{
    if (Size == SIZE)//если размер равен максимальному размеру
        return 1;//выходим
    return 0;
}
//реализация метода проверки на не заполненность таблицы
int HashTable_t::IsEmpty()
{
    if (Size == 0)
        return 1;
    return 0;
}
//реализация метода поиска по ФИО
int HashTable_t::FindByFIO(const string& fio)
{
    int CountOfOutputed = 0;//счетчик выведеных на экран
    for (int i = 0; i < SIZE; i++)
    {
        if (!Table[i])//если индекс не заполнен, переходим на стредующую итерацию цикла
            continue;
        if (Table[i]->GetFIO() == fio)//если данные по индесом совпадают с тем, что нужно
        {
            PrintOne(i);//выводим данные об этом пассажире
            CountOfOutputed++;//увеличиваем счетчик выведенных на экран
        }
    }
    if (!CountOfOutputed)//если никого не вывели
        return -1;//возвращаем -1
    else
        return 0;
}
//реализация метода вывода данных о пассажире по его паспорту
int HashTable_t::FindAndPrintByPassportNum(const string& key)
{
    int index = Find(key);//находим нужного рассажира
    if (index == -1)//если его индекс равен -1, значит такого пассажира нет
    {
        return index;
    }
    else//иначе
    {
        PrintOne(index);//выводим данные о нем
        return 0;
    }
}
//реализация метода вывода на экран данных о пассажирах, купивших билет на определенный авиарейс
int HashTable_t::PrintAllPassengersByAirFlight(TicketList_t& List_, const string& key)
{
    int count = 0;
    auto current = List_.GetHead();
    string FlightNum = key;
    for (int i = 0; i < List_.GetSize() - 1; i++)//цикл по размеру списка
    {
        if (current->ticket->GetAirFligthNum() == FlightNum)//если совпадает авиарейс
        {
            int index = Find(current->ticket->GetPasportNum());//находим пассажира
            PrintOne(index);
            count++;//увеличиваем счетчик
        }
        current = current->pNext;//продвигаемся по списку
    }
    return count;
}
//реализация метода очиски списка
void HashTable_t::Clear()
{
    for (int i = 0; i < SIZE; i++)//цикл по размеру таблицы
    {
        if (Table[i])//если индекс заполенен
        {
            delete Table[i];//удаляем его
            Table[i] = nullptr;//приравниваем 0 для перестраховки
        }
    }
    Size = 0;//размер, соответсвенно, становится 0
}
//реализация метода вывода данных об одном рассажире
void HashTable_t::PrintOne(const int& index)
{
    cout << "Имя пассажира: " << Table[index]->GetFIO() << endl;
    cout << "Номер паспорта пассажира: " << Table[index]->GetPasportNum() << endl;
    cout << "Место выдачи паспорта: " << Table[index]->GetPlaceOfIssue() << endl;
    cout << "Дата выдачи паспорта: " << Table[index]->GetDateOfIssue() << endl;
    cout << "Дата рождения пассажира: " << Table[index]->GetBirthday() << endl << endl;
}
//реализация метода вывода всех пассажиров на экран
void HashTable_t::PrintAll()
{
    for (int i = 0; i < SIZE; i++)//цикл по размеру таблицы
    {
        if (!Table[i])//если индекс не заполнен
            continue;//переходим на следующую итерацию цикла
        PrintOne(i);//иначе выводим даные о пассажире
    }
}
