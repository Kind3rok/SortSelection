#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QMainWindow>
#include "ui_main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	/// <summary>
	/// Очищает виджет таблицы в графическом интерфейсе.
	/// </summary>
	void clearTableWidget();

private slots:
	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки save. Сохраняет данные из таблицы в базу.
	/// </summary>
	void save_btn_clicked();

	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки load. Загружает данные из базы в таблицу, и выводит их.
	/// </summary>
	void load_btn_clicked();

	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки генерации случайных массивов. Генерирует случайные массивы и выводит их в таблицу.
	/// </summary>
	void random_btn_clicked();

	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки сортировки массивов. Сортирует массивы в таблице.
	/// </summary>
	void sort_btn_clicked();

	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки очистки базы. Очищает базу данных.
	/// </summary>
	void clear_database_btn_clicked();

	/// <summary>
	/// Слот-функция, реагирующая на нажатие кнопки очистки таблицы. Очищает таблицу массивов.
	/// </summary>
	void clear_table_btn_clicked();

private:
	Ui::MainWindowClass *_ui;
	std::vector<std::vector<int>> _arrays{}; // хранит массивы
	std::vector<std::string> _change_dates{}; // хранит даты
};


#endif