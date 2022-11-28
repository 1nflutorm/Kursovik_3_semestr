#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "HashTable_t.h"
#include "Passenger_t.h"
#include "AirFlight_t.h"
#include "TicketList_t.h"
#include "Ticket_t.h"
#include "AirFlightTree_t.h"
#include "MainFunctions.h"
#define MAIN
#define DEBUG
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HashTable_t Table;
    TicketList_t List;
    AirFlightTree_t Tree;
    string PasportNum = "";
    string PlaceOfIssue = "";
    string DateOfIssue;
    string FIO = "";
    string Name = "";
    string Surname = "";
    string Lastname = "";
    string Birthday = "";
    string AirFligthNum = "";
    string Company = "";
    string DepartureAirport = "";
    string ArriveAirport = "";
    string DepartureDate = "";
    string DepartureTime = "";
    string TicketNum = "";
    int NumberOfSeats = 0;
    int NumberOfAvailableSeats = 0;
    int choice = 0;
    int TicketNumber = 100000000;

#ifdef DEBUG//входные данные для проверки
    PushPassengers(Table, "Passengers.txt");
    PushAirFlights(Tree, "AirFlight.txt");
    PushTickets(Tree, List, "tickets.txt");
    List.InsertSortList(List);
#endif // DEBUG


#ifdef MAIN
    while (true)
    {
        PrintMenu();
        cin >> choice;
        if (choice == 0)
            break;
        switch (choice)
        {
        case 1:
        {
            if (Table.IsFull())//проверка на заполненность таблицы
            {
                cout << "\nТаблица переполнена, невозможно зарегистрировать нового пассажира!\n" << endl;
                break;
            }
            cout << "\nРегистрация нового пассажира: " << endl;
            cout << "Введите фамилию пассажира: ";
            cin >> Surname;
            cout << "Введите имя пассажира: ";
            cin >> Name;
            cout << "Введите отчество пассажира: ";
            cin >> Lastname;
            cout << "Введите номер паспорта пассажира: ";
            cin >> PasportNum;
            if (!IsCorrectPas(PasportNum))//проверка на корректность введенных паспортных данных
            {
                cout << "\nЧеловека с таким номером паспорта не существует!\nРегистрация невозможна!\n"<< endl;
                break;
            }
            cout << "Введите место выдачи паспорта пассажира: ";
            _flushall();
            cin.ignore();
            getline(cin, PlaceOfIssue);
            cout << "Введите дату выдачи паспорта пассажира: ";
            cin >> DateOfIssue;
            cout << "Введите дату рождения пассажира: ";
            cin >> Birthday;
            FIO = Surname + " " + Name + " " + Lastname;
            int result = Table.Push(PasportNum, PlaceOfIssue, DateOfIssue, FIO, Birthday);//заполнение данных о пассажире
            if (result == 2)//если функция заполнения вернула код 2, то такой пассажир уже был зарегестрирован
                cout << "\nТакой пассажир уже существует!\n" << endl;
            else
                cout << "\nПассажир успешно зарегестрирован!\n" << endl;
            break;
        }
        case 2:
        {
            if (Table.IsEmpty())//проверка на переполненность таблицы
            {
                cout << "Список пассажиров пуст!" << endl;
                break;
            }
            cout << "\nВведите номер паспорта пассажира: ";
            cin >> PasportNum;
            if (!IsCorrectPas(PasportNum))//проверка на коррмектность веденных паспортных данных
            {
                cout << "Человека с таким номером паспорта не существует!\n" << endl;
                break;
            }
            int index = Table.Find(PasportNum);//поиск пассажира с такими номером паспорта
            if (index == -1)//код -1 соответствует отсутствию такого пассажира
            {
                cout << "Такой пассажир не зарегестрирован!\n" << endl;
            }
            else//любой другой код 
            {
                cout << "Пассажир c таким номером пасспорта найден!\n" << endl;
                Table.PrintOne(index);//выводим данные об этом пассажире
                cout << "Вы хотите его удалить?\n1. Да\n2. Нет" << endl;
                cout << "Ваш выбор: ";
                cin >> choice;//получаем выбор пользователя удалять/не удалять
                if (choice == 1)//1 - удаляем, любой другой - не удаляем
                {
                    Table.DelOne(PasportNum);//удаляем пассажира с таким номером паспорта
                    do
                    {
                        index = List.Find(PasportNum);//находим билет зарегестрированный на этот паспорт
                        List.DelInside(index);//удаляем его 
                        AirFligthNum = List.FindAirFlightByIndex(index);//находим номер авиарейса
                        if (AirFligthNum == "") 
                            continue;
                        AirFlight_t* NodeToFind = Tree.Find(AirFligthNum);//ищем такой узел в дереве
                        NodeToFind->IncrementNumberOfAvailableSeats();//увеличиваем количество свободных мест в рейсе
                    } while (index != -1);
                    cout << "\nДанные о купленных пассажиром билетах удалены!" << endl;
                    cout << "Пассажир удален!\n" << endl;
                    break;
                }
                cout << "\nУдаление отменено!\n" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Все зарегестрированные пассажиры:\n" << endl;
            if (Table.IsEmpty())//если таблица пустая
                cout << "Зарегестрированных пассажиров нет!\n" << endl;
            else
                Table.PrintAll();//иначе выводим всех пассажиров
            break;
        }
        case 4:
        {
            cout << "Удаление данных о всех пассажирах:" << endl;
            if (Table.IsEmpty())//если таблица пустая
            {
                cout << "\nСписок пассажиров пуст!\n" << endl;
            }
            else//иначе оцищаем таблицу и список
            {
                Table.Clear();//очищаем таблицу
                List.Clear();//очицаем список билетов
                Tree.SetDefault();//возвращаем количество свободных мест в начальное значение
                cout << "\nДанные о пассажирах и купленных ими билетах удалены!\n" << endl;
            }
            break;
        }
        case 5:
        {
            if (Table.IsEmpty())//если таблица пустая
            {
                cout << "\nСписок пассажиров пуст! Вывод данных невозможен!\n" << endl;
                break;
            }
            cout << "\nПоиск пассжира по номеру паспорта." << endl;

            cout << "Введите номер паспорта пассажира: ";
            cin >> PasportNum;
            if (!IsCorrectPas(PasportNum))//проверка на корректность введенных паспортных данных
            {
                cout << "\nЧеловека с таким номером паспорта не существует!\n" << endl;
                break;
            }
            else
            {
                cout << "\nДанные о найденом пассажире: " << endl;
            }
            if (Table.FindAndPrintByPassportNum(PasportNum) == -1)//поиск и вывод на экран данных о пассажире, если таковой найден
            {
                cout << "Такого пассажира еще не было зарегестрировано!\n" << endl;
                break;
            }
            cout << "Все билеты данного пассажира: " << endl;
            if (!List.PrintAllPassengerTickets(PasportNum))//если пассажир был найден вывод всех билетов на экран, если они были куплены
                cout << "Данный пассажир еще не покупал билетов!\n" << endl;
            break;
        }
        case 6:
        {
            if (Table.IsEmpty())//если таблица пустая 
            {
                cout << "\nСписок пассажиров пуст! Вывод данных невозможен!\n" << endl;
                break;
            }
            cout << "\nПоиск пассажира по ФИО." << endl;
            cout << "Введите фамилию пассажира: ";
            cin >> Surname;
            cout << "Введите имя пассажира: ";
            cin >> Name;
            cout << "Введите отчество пассажира: ";
            cin >> Lastname;
            FIO = Surname + " " + Name + " " + Lastname;
            cout << endl;
            if (Table.FindByFIO(FIO) == -1)//ищем пассажира по ФИО
            {
                cout << "Пассажиров с таким именем не найдено!\n" << endl;
            }
            break;
        }
        case 7:
        {
            cout << "\nВведите номер авиарейса: ";
            cin >> AirFligthNum;
            if (AirFligthNum == "0")
                break;
            if (!IsCorrectFlight(AirFligthNum))//проверяем корректность номера авиаполета
            {
                cout << "Такого рейса не существует. Повторите попытку ввода!\n" << endl;
                continue;
            }
            int flightNum = Convert(AirFligthNum);
            if (Tree.FindByAirFlightNum(flightNum))//проверяем на совпадение
            {
                cout << "Такой рейс уже зарегистрирован!\n" << endl;
                continue;
            }
            cout << "Введите авиакомпанию: ";
            _flushall();
            cin.ignore();
            getline(cin, Company);
            cout << "Введите аэропорт отправления ";
            _flushall();
            cin.ignore();
            getline(cin, DepartureAirport);
            cout << "Введите аэропорт прибытия: ";
            _flushall();
            cin.ignore();
            getline(cin, ArriveAirport);
            cout << "Введите дату отправления: ";
            cin >> DepartureDate;
            cout << "Введите время отправления: ";
            cin >> DepartureTime;
            cout << "Введите количество мест: ";
            cin >> NumberOfSeats;
            Tree.Insert(AirFligthNum, Company, DepartureAirport, ArriveAirport, DepartureDate, DepartureTime, NumberOfSeats);//заполняем дерево
            cout << "\nАвиарейс зарегестрирован!\n" << endl;
            break;
        }
        case 8:
        {
            if (Tree.IsEmpty())
            {
                cout << "\nАвиарейсы еще не зарегестрированы. Удаление невозможно.\n" << endl;
                break;
            }
            cout << "\nВведите номер авиарейса: ";
            cin >> AirFligthNum;
            if (AirFligthNum == "0")
                break;
            if (!IsCorrectFlight(AirFligthNum))//проверяем на правильность введенных данных
            {
                cout << "Такого рейса не существует. Повторите попытку ввода!\n" << endl;
                continue;
            }
            int flightNum = Convert(AirFligthNum);//конвертируем номер авиарейса в целое число
            if (Tree.FindByAirFlightNum(flightNum))//проверяем на существование такого рейса
            {//если существует
                Tree.Remove(AirFligthNum);//удаляем его
                List.DeleteTicketsByFlightNum(AirFligthNum);//удаляем все билеты, купленные на этот рейс
                cout << "\nАвиарейс удален!\n" << endl;
            }            
            break;
        }
        case 9:
        {
            if (Tree.IsEmpty())//проверяем заполненность дерева
            {
                cout << "\nАвиарейсы еще не были зарегестрированы. Просмотр невозможен!\n" << endl;
                break;
            }
            cout << "\nВсе зарегестрированные авиарейсы:\n" << endl;
            Tree.PrintFlights();//выводим всю информацию на экран
            break;
        }
        case 10:
        {
            if (Tree.IsEmpty())//проверяем заполненность дерева
            {
                cout << "\nАвиарейсы еще не были зарегестрированы!\n" << endl;
                break;
            }
            Tree.Clear();//очищаем
            cout << "\nДанные об авиарейсах удалены!\n" << endl;
            break;
        }
        case 11:
        {
            if (Tree.IsEmpty())//проверяем заполненность дерева
            {
                cout << "\nАвиарейсы еще не были зарегестрированы. Просмотр невозможен!\n" << endl;
                break;
            }
            cout << "\nВведите номер авиарейса, данные о которм хотите найти: ";
            cin >> AirFligthNum;
            if (!IsCorrectFlight(AirFligthNum))//проверяем правильность ввода
            {
                cout << "Такого рейса не существует!\n" << endl;
                break;
            }
            AirFlight_t* flight = Tree.Find(AirFligthNum);//находим такой рейс
            if (!flight)//если не нашли
            {
                cout << "Такой авиарейс не найден!\n" << endl;
                break;
            }
            cout << "\nДанные о найденом авирейсе: \n" << endl;
            flight->Print();//если нашли, выводим на экран
            cout << "Данные о всех пассажирах, купивших билет на этот рейс: " << endl;
            if (!Table.PrintAllPassengersByAirFlight(List, AirFligthNum))//выводим все билеты купленные на этот рейс
                cout << "На этот рейс еще не покупались билеты!\n";//если таких нет, выводим соответствующее сообщение
            cout << endl;
            break;
        }
        case 12:
        {
            if (Tree.IsEmpty())//проверяем заполненность дерева
            {
                cout << "\nАвиарейсы еще не были зарегестрированы. Просмотр невозможен!\n" << endl;
                break;
            }
            cout << "\nПоиск авиарейса по фрагментам названия аэропорта прибытия." << endl;
            cout << "\nВведите фрвгмент названия аэропорта прибытия: ";
            cin >> ArriveAirport;
            cout << "\nДанные о найденых авиарейсах: " << endl;
            int count = 0;
            Tree.FindAndPrintBySubstr(ArriveAirport, count);//выводим на экран найденные рейсы
            if (!count)//если таких нет, то выводим соответсвуюее сообщение
                cout << "Авиарейсов с таким аэропором прибытия не найдено!\n" << endl;
            break;
        }
        case 13:
        {
            if (Table.IsEmpty())//проверяем заполненность таблицы с пассажирами
            {
                cout << "\nПассажиры еще не зарегестрированы!\n" << endl;
                break;
            }
            if (Tree.IsEmpty())//проверяем заполненность дерева
            {
                cout << "\nАвиарейсы еще не зарегестрированы!\n" << endl;
                break;
            }
            cout << "\nВведите номер паспорта пассажира: ";
            cin >> PasportNum;
            if (!IsCorrectPas(PasportNum))//проверяем корректность паспортных данных
            {
                cout << "\nЧеловека с таким номером паспорта не существует!\n" << endl;
                continue;
            }
            if (Table.Find(PasportNum) == -1)//ищем пассажира в таблице
            {
                cout << "\nТакой пассажир еще не зарегестрирован!\n" << endl;
                continue;
            }
            cout << "\nВсе зарегестрированные авиарейсы:\n" << endl;
            Tree.PrintFlights();//печатаем зарегестрированные рейсы
            AirFlight_t* NodeToFind;
            cout << "Введите номер авиарейса: ";
            cin >> AirFligthNum;
            if (!IsCorrectFlight(AirFligthNum))//проверяем корректность номера рейса
            {
                cout << "\nТакого рейса не существует. Повторите попытку ввода!\n" << endl;
                break;
            }
            else
            {
                NodeToFind = Tree.Find(AirFligthNum);//ищем этот рейс
            }
            if (!NodeToFind)//если не нашли
            {
                cout << "Такой рейс еще не зарегестрирован!\n" << endl;//выводим соответствующее сообщение
                break;
            }
            if (List.FindTicket(PasportNum, AirFligthNum) != -1)//проверяем, покупал ли пассажир билет на этот же рейс
            {
                cout << "\nПассажир не может иметь два билета на один и тот же рейс!\n" << endl;
                break;
            }
            if (NodeToFind->GetAvailableSeats())//проверяем количество свободных меси
            {
                NodeToFind->DecrementNumberOfAvailableSeats();//если оно больше нуля, то вычитаем 1, т.к. был куплен новый билет
            }
            else//если оно равно 0
            {
                cout << "\nНа данный авиарейс нет свободных мест!\n" << endl;//выводим соответсвующее сообшение
                continue;
            }
            TicketNum = to_string(++TicketNumber);//формируем номер билета
            List.PushBack(PasportNum, AirFligthNum, TicketNum);//заполнем список
            cout << "\nБилет продан! \nДанные о купленом билете: \n" << endl;
            List.PrintLastTicket();//выводим только созданный билет
            List.InsertSortList(List);//делаем сортировку списка методом вставки
            cout << endl;   
            break;
        }
        case 14:
        {
            if (!List.GetSize())//проверяем покупались ли битеты
            {
                cout << "\nСписок билетов пуст! Возврат невозможен!\n" << endl;
                break;
            }
            cout << "\nВведите номер паспорта пассажира: ";
            cin >> PasportNum;
            if (!IsCorrectPas(PasportNum))//проверяем корректность паспортных данных
            {
                cout << "\nЧеловека с таким номером паспорта не существует!\n" << endl;
                continue;
            }
            if (Table.Find(PasportNum) == -1)//ищем пассажира с таким паспортом в таблице
            {
                cout << "\nТакой пассажир еще не зарегестрирован!\n" << endl;
                break;
            }
            cout << "\nВсе купленные пассажиром билеты:" << endl;
            if (!List.PrintAllPassengerTickets(PasportNum))//выводим все билеты пассажира
            {
                cout << "\nДанный пассажир еще не покупал билетов!\n" << endl;//если он их еще не покупал, выводим соответствующее сообщение
                break;
            }
            AirFlight_t* NodeToFind;
            cout << "Введите номер авиарейса: ";
            cin >> AirFligthNum;
            if (!IsCorrectFlight(AirFligthNum))//проверяем корректность номера рейса
            {
                cout << "\nТакого рейса не существует. Повторите попытку ввода!\n" << endl;
                break;
            }
            NodeToFind = Tree.Find(AirFligthNum);//находим нужный авиарейс
            int index = List.FindTicket(PasportNum, AirFligthNum);//ищем билет
            if (index != -1)//если такой билей найден
            {
                List.DelInside(index);//удаляем его 
                NodeToFind->IncrementNumberOfAvailableSeats();//увеличиваем количество свободных мест
                cout << "\nБилет удален!\n" << endl;
                break;
            }
            else
            {
                cout << "\nПассажир не покупл билет на этот авиарейс!\n" << endl;
                break;
            }
            break;
        }
        default:
            cout << "Введено некорректное значение. Повторите попытку." << endl;
            break;
        }
    }
#endif // MAIN
	return 0;
}