#include "main_window.h"
#include <iostream>
#include "database.h"
#include "main_algorithms.h"
#include "input.h"
#include <qmessagebox.h>
#include <QIntValidator>
#include <iostream>
#include <qfiledialog.h>
#include <QPlainTextEdit>

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
	connect(_ui->load_from_file_btn, &QPushButton::clicked, this, &MainWindow::load_from_file_btn_clicked);
	//connect(_ui->output_table, &QTableWidget::cellEntered, this, &MainWindow::showFullArrayDialog);
	connect(_ui->output_table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

	// Установка ширины столбцов в QTableWidget
	_ui->output_table->setColumnWidth(Array_data, 650);
	_ui->output_table->setColumnWidth(Change_date, 160);
	_ui->output_table->setColumnWidth(Type, 150);

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

	QMessageBox::information(this, "Информация", "Данные массива сохранены");
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

	QMessageBox::information(this, "Информация", "Данные массива загружены");

	// Включаем кнопку
	_ui->load_btn->setEnabled(true);
}

void MainWindow::random_btn_clicked() {
	bool all_good = true;
	QString number_of_elements = _ui->number_of_arrays->text();

	if (!_ui->save_in_table->isChecked()) {
		clearTableWidget(); // Очистка данных в таблице перед новой загрузкой данных
		_arrays.clear(); // Очистка массива, т.к. новые данные добавляются через push_back
		_change_dates.clear();
	}

	clearTableWidget();
	// Проверка, введено ли количество элементов в массиве
	if (number_of_elements.isEmpty()) {
		all_good = false;
		QMessageBox::critical(this, "Ошибка", "Количество элементов в массиве не введено!");
	}
	else {
		int elements = number_of_elements.toInt();
		if (elements <= 0) {
			all_good = false;
			QMessageBox::critical(this, "Ошибка", "Количество элементов в массиве не может быть отрицательным!");
		}
		else if (elements > 100) {
			all_good = false;
			QMessageBox::critical(this, "Ошибка", "Количество элементов в массиве не может быть больше 100!");
		}
	}

	if (all_good) {
		generateRandomArray(_arrays, _change_dates, 1, number_of_elements.toInt());

		QString array_string{};
		for (int i = 0; i < _arrays.back().size(); ++i) {
			array_string += QString::number(_arrays.back()[i]) + ' ';
		}

		int row = _ui->output_table->rowCount(); // количество строк
		_ui->output_table->insertRow(row); // вставка новой строки

		_ui->output_table->setItem(row, Array_data, new QTableWidgetItem(array_string));

		if (!_change_dates.empty()) {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(_change_dates.back())));
		}
		else {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(getCurrentDateAndTime())));
		}

		_ui->output_table->setItem(row, Type, new QTableWidgetItem(QString::fromStdString(getArrayType(_arrays.back()))));
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

	QMessageBox::information(this, "Информация", "Массивы отсортированы");

	// Включаем кнопку
	_ui->sort_btn->setEnabled(true);
}

void MainWindow::load_from_file_btn_clicked() {
	// Открываем диалог выбора файла
	QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл с массивами", "", "Текстовые файлы (*.txt)");

	if (filePath.isEmpty()) {
		// Пользователь отменил выбор файла
		return;
	}

	// Открываем файл для чтения
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
		return;
	}

	// Очищаем данные перед загрузкой
	clearTableWidget();
	_arrays.clear();
	_change_dates.clear();

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList stringList = line.split(" ", Qt::SkipEmptyParts);

		// Проверяем, что в массиве минимум 3 элемента
		if (stringList.size() < 3) {
			QMessageBox::critical(this, "Ошибка", "Массив содержит менее 3 элементов");
			return;
		}

		std::vector<int> array;

		for (const QString& numStr : stringList) {
			bool ok;
			int num = numStr.toInt(&ok);

			// Проверяем, что числа в массиве в допустимом диапазоне
			if (!ok || num < -1000 || num > 1000) {
				QMessageBox::critical(this, "Ошибка", "Числа в массиве должны быть в диапазоне от -1000 до 1000");
				return;
			}

			array.push_back(num);
		}

		_arrays.push_back(std::move(array));
	}

	file.close();

	// Загрузка данных в таблицу
	int row = 0;
	for (const auto& array : _arrays) {
		QString arrayStr;
		for (int num : array) {
			arrayStr = arrayStr + QString::number(num) + ' ';
		}

		_ui->output_table->insertRow(row);
		_ui->output_table->setItem(row, Array_data, new QTableWidgetItem(arrayStr));

		if (!_change_dates.empty()) {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(_change_dates[row])));
		}
		else {
			_ui->output_table->setItem(row, Change_date, new QTableWidgetItem(QString::fromStdString(getCurrentDateAndTime())));
		}

		_ui->output_table->setItem(row, Type, new QTableWidgetItem(QString::fromStdString(getArrayType(_arrays[row]))));

		row++;
	}

	QMessageBox::information(this, "Информация", "Данные массива из файла загружены");
}

void MainWindow::clear_database_btn_clicked() {
	// Выключаем кнопку
	_ui->clear_database_btn->setEnabled(false);

	// Очистка базы данных
	clearTable();
	QMessageBox::information(this, "Информация", "База данных очищена");

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

void MainWindow::showFullArrayDialog(const QString& arrayStr) {
	QDialog* fullArrayDialog = new QDialog(this);
	fullArrayDialog->setWindowTitle("Полный массив");
	fullArrayDialog->setMinimumWidth(300);

	QVBoxLayout* layout = new QVBoxLayout(fullArrayDialog);
	QLabel* arrayLabel = new QLabel(arrayStr, fullArrayDialog);
	arrayLabel->setWordWrap(true);
	layout->addWidget(arrayLabel);

	fullArrayDialog->exec();
}

void MainWindow::onCellClicked(int row, int column) {
	QTableWidgetItem* item = _ui->output_table->item(row, column);
	if (item) {
		QString arrayStr = item->text();
		showFullArrayDialog(arrayStr);
	}
}

