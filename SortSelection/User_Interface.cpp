#include "User_Interface.h"
#include "Input_From_File.h"
#include "Output_Into_File.h"
#include "Sort.h"
#include "Algorithm_Filework.h"

/// <summary>
/// Функция выводит начальное текстовое меню с ФИ, номером группы, номером лабораторной работы, вариантом лабораторной работы,
/// названием сортировки, номерами пунктов меню
/// </summary>
void Print_Menu()
{
	system("cls");
	std::cout << "Баев Кирилл, Ивлев Максим. 425 группа." << std::endl << "Лабораторная работа №2. Вариант 12." << std::endl;
	std::cout << "Сортировка выбором/Selection sort." << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Выберите нужный пункт меню:" << std::endl << "1 - Начать работу программы." << std::endl << "2 - Завершить работу программы" << std::endl << "> ";
}

/// <summary>
/// Функция ввода значений вектора из файла, сортировки вектора, вывода результата, затем вывода результата работы программы в отдельный файл
/// </summary>
/// <param name="vect"> исходный вектор, из которого копируются значения </param>
/// <param name="copyVect"> вектор-копия, который будет сортироваться </param>
void Start_Programm(std::vector <int>& vect, std::vector <int>& copyVect) {

	Input_From_File(vect);
	copyVect = vect; //копируем вектор
	SelectionSort(copyVect); //сортируем копию

	std::cout << "Исходный вектор: " << std::endl;
	for (int i = 0; i < vect.size(); i++) {
		std::cout << vect[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "Сортированный вектор: " << std::endl;
	for (int i = 0; i < copyVect.size(); i++) {
		std::cout << copyVect[i] << ' ';
	}
	std::cout << std::endl;

	Output_Into_File(vect, copyVect);
}

/// <summary>
/// Функция выводит главное меню
/// </summary>
void Main_Menu()
{
	//Функция реализует главное зацикленное меню
	std::vector <int> vect;
	std::vector <int> copyVect;
	setlocale(LC_ALL, "RU");
	int userСhoise = 0;

	do {
		system("cls"); //очищение консоли
		Print_Menu();
		userСhoise = Check_Int();
		switch (userСhoise) {
		case StartProgramm:
			Start_Programm(vect, copyVect);
			break;
		case StopProgramm:
			break;
		default:
			std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
			break;
		}

		if (userСhoise != StopProgramm)	system("pause");

	} while (userСhoise != StopProgramm);
}
