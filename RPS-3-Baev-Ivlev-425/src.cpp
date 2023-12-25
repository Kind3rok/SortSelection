#include <cstdlib> // Включение заголовочного файла для стандартных функций C, таких как srand
#include <ctime> // Включение заголовочного файла для работы с временем (для инициализации генератора случайных чисел)
#include <iostream>
#include <Windows.h> // Для кодировки
#include <QtWidgets/QApplication>
#include "main_window.h"
#include "database.h"


int main(int argc, char* argv[]) {
	// Установка кодировки ввода-вывода UTF-8, для поддержки кириллицы (универсальный вариант)
	setlocale(LC_ALL, ".UTF8");

	/* Установка начального значения для генератора псевдослучайных чисел, с использованием текущего времени,
	для обеспечения различных последовательностей при каждом запуске программы */
	srand(static_cast<unsigned int>(time(nullptr)));

	// Создание объекта приложения
	QApplication a(argc, argv);
	// Создание объекта главной графической формы
	MainWindow w;

	// Вывод графической формы
	w.show();

	return a.exec();
}
