#include "main_window.h"
#include <iostream>
#include "database.h"
#include "main_algorithms.h"
#include "input.h"
#include <qmessagebox.h>
#include <QIntValidator>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), _ui(new Ui::MainWindowClass()) {
	// Инициализация главного окна
	_ui->setupUi(this);

	// Установка флагов размера окна
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint));

	// Подключение сигналов к слотам для кнопок
	connect(_ui->save_btn, &QPushButton::clicked, this, &MainWindow::save_btn_clicked);
	connect(_ui->load_btn, &QPushButton::clicked, this, &MainWindow::load_btn_clicked);
	connect(_ui->random_btn, &QPushButton::clicked, this, &MainWindow::random_btn_clicked);
	connect(_ui->sort_btn, &QPushButton::clicked, this, &MainWindow::sort_btn_clicked);
	connect(_ui->clear_database_btn, &QPushButton::clicked, this, &MainWindow::clear_database_btn_clicked);
	connect(_ui->clear_table_btn, &QPushButton::clicked, this, &MainWindow::clear_table_btn_clicked);

	// Установка ширины столбцов в QTableWidget
	_ui->output_table->setColumnWidth(Array_data, 700);
	_ui->output_table->setColumnWidth(Change_date, 130);
	_ui->output_table->setColumnWidth(Type, 80);

	// Установка режима изменения размеров секций горизонтального и вертикального заголовка
	_ui->output_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	_ui->output_table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	// Создание валидатора для QLineEdit
	QIntValidator* validator = new QIntValidator(_ui->number_of_arrays);
	_ui->number_of_arrays->setValidator(validator);
}

MainWindow::~MainWindow() {
	delete _ui;
}


void MainWindow::save_btn_clicked() {
	// Выключаем кнопку
	_ui->save_btn->setEnabled(false);

	// Проверка чекбокса сохранять ли данные в базе
	if (!_ui->save_in_db->isChecked()) {
		clearTable();
		initializeDB(_arrays);  // Очистка базы и добавление новых данных
	}
	else {
		initializeDB(_arrays); // Добавление новых данных без очистки базы
	}

	QMessageBox::information(this, "Information", "Array data saved");
	// Включаем кнопку
	_ui->save_btn->setEnabled(true);
}

void MainWindow::load_btn_clicked() {
	// Выключаем кнопку
	_ui->load_btn->setEnabled(false);

	// Проверка чекбокса сохранения данных в таблице
	if (!_ui->save_in_table->isChecked()) {
		clearTableWidget(); // Очистка данных в таблице перед новой загрузкой данных
		_arrays.clear(); // Очистка массива, т.к. новые данные добавляются через push_back
		_change_dates.clear();
	}

	clearTableWidget();
	// Загрузка данных из базы
	loadDataFromDB(_arrays, _change_dates);
	
	if (_arrays.empty()) {
		_change_dates.clear();
	}

	int row{};
	// Перебор массивов и их добавление в таблицу
	for (size_t i = 0; i < _arrays.size(); ++i) {
		QString array{};

		// Преобразование массива в строку
		for (size_t j = 0; j < _arrays[i].size(); ++j) {
			array = array + QString::number(_arrays[i][j]) + ' ';
		}

		// Вставка новой строки в таблицу
		int rowC = _ui->output_table->rowCount(); // количество строк
		_ui->output_table->insertRow(row); // вставка новой строки

		// Заполнение ячеек таблицы данными
		_ui->output_table->setItem(row, Array_data, new QTableWidgetItem(array));

		if (!_change_dates.empty()) {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(_change_dates[i])));
		}
		else {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(getCurrentDateAndTime())));
		}

		_ui->output_table->setItem(row, Type, new QTableWidgetItem(QString::fromStdString(getArrayType(_arrays[i]))));
		row++;
	}

	QMessageBox::information(this, "Information", "Array data loaded");

	// Включаем кнопку
	_ui->load_btn->setEnabled(true);
}

void MainWindow::random_btn_clicked() {
	bool all_good = true;
	// Получение значения количества массивов из строки ввода
	QString number_of_arrays = _ui->number_of_arrays->text();

	if (!_ui->save_in_table->isChecked()) {
		clearTableWidget(); // Очистка данных в таблице перед новой загрузкой данных
		_arrays.clear(); // Очистка массива, т.к. новые данные добавляются через push_back
		_change_dates.clear();
	}

	clearTableWidget();
	// Проверка, введено ли количество массивов для генерации
	if (number_of_arrays.isEmpty()) {
		all_good = false;
		QMessageBox::critical(this, "Error", "The number of arrays to generate is not entered!");
	}

	if (all_good) {
		generateRandomArrays(_arrays, _change_dates, number_of_arrays.toInt());

		int row{};
		// Перебор сгенерированных массивов и их добавление в таблицу
		for (size_t i = 0; i < _arrays.size(); ++i) {
			QString array{};

			// Преобразование массива в строку
			for (size_t j = 0; j < _arrays[i].size(); ++j) {
				array = array + QString::number(_arrays[i][j]) + ' ';
			}

			// Вставка новой строки в таблицу
			int rowC = _ui->output_table->rowCount(); // количество строк
			_ui->output_table->insertRow(row); // вставка новой строки

			// Заполнение ячеек таблицы данными
			_ui->output_table->setItem(row, Array_data, new QTableWidgetItem(array));

			if (!_change_dates.empty()) {
				_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(_change_dates[i])));
			}
			else {
				_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(getCurrentDateAndTime())));
			}

			_ui->output_table->setItem(row, Type, new QTableWidgetItem(QString::fromStdString(getArrayType(_arrays[i]))));

			row++;
		}
	}
}

void MainWindow::sort_btn_clicked() {
	// Выключаем кнопку
	_ui->sort_btn->setEnabled(false);

	// Вызов функции для сортировки массивов
	startSorting(_arrays);
	clearTableWidget();
	int row{};
	// Перебор отсортированных массивов и их добавление в таблицу
	for (size_t i = 0; i < _arrays.size(); ++i) {
		QString array{};

		// Преобразование массива в строку
		for (size_t j = 0; j < _arrays[i].size(); ++j) {
			array = array + QString::number(_arrays[i][j]) + ' ';
		}

		// Вставка новой строки в таблицу
		int rowC = _ui->output_table->rowCount(); // количество строк
		_ui->output_table->insertRow(row); // вставка новой строки

		// Заполнение ячеек таблицы данными
		_ui->output_table->setItem(row, Array_data, new QTableWidgetItem(array));
		_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(getCurrentDateAndTime())));
		_ui->output_table->setItem(row, Type, new QTableWidgetItem(QString::fromStdString(getArrayType(_arrays[i]))));

		row++;
	}

	QMessageBox::information(this, "Information", "Arrays have been sorted");

	// Включаем кнопку
	_ui->sort_btn->setEnabled(true);
}

void MainWindow::clear_database_btn_clicked() {
	// Выключаем кнопку
	_ui->clear_database_btn->setEnabled(false);

	// Очистка базы данных
	clearTable();
	QMessageBox::information(this, "Information", "Database has been cleaned");

	// Включаем кнопку
	_ui->clear_database_btn->setEnabled(true);
}

void MainWindow::clear_table_btn_clicked() {
	clearTableWidget();
	_arrays.clear();
	_change_dates.clear();
}

void MainWindow::clearTableWidget() {
	// Очистка содержимого ячеек таблицы
	_ui->output_table->clearContents();

	// Удаление всех строк из таблицы
	while (_ui->output_table->rowCount() > 0) {
		_ui->output_table->removeRow(0);
	}

	// Пересоздание первого столбца с номерами строк
	for (int row = 0; row < _ui->output_table->rowCount(); ++row) {
		// Создание нового элемента таблицы и заполнение номером строки
		QTableWidgetItem* item = new QTableWidgetItem(QString::number(row + 1));
		// Установка элемента в таблицу
		_ui->output_table->setItem(row, 0, item);
	}
}