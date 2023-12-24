#include <stdlib.h>
#include <iostream>
#include "input.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


std::string getCurrentDateAndTime() {
    // Получение текущего времени
    auto now = std::chrono::system_clock::now();
    std::string current{};

    // Преобразование времени в строку
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&now_c);

    // std::ostringstream служит в данном контексте как промежуточный буфер для форматирования и преобразования данных в строку. Здесь дает возможность, задать формат строки.
    std::ostringstream oss{};
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    // Получение строки из объекта std::ostringstream
    current = oss.str();

    return current;
}

std::string getArrayType(std::vector<int>& array) {
    // Инициализация пустой строки, которая будет содержать тип массива
    std::string array_type{};

    // Проверка, отсортирован ли массив
    if (std::is_sorted(std::begin(array), std::end(array))) {
        // Если отсортирован, устанавливаем тип "sorted"
        array_type = "sorted";
    }
    else {
        // Если не отсортирован, устанавливаем тип "unsorted"
        array_type = "unsorted";
    }

    // Возвращаем полученный тип массива
    return array_type;
}

int initializeDB(std::vector<std::vector<int>>& arrays) {
    // Объекты для работы с базой данных
    sql::Driver* driver{};
    sql::Connection* con{};
    sql::PreparedStatement* pstmt{};

    // Переменные для хранения данных
    std::string array{}, change_date{}, type{};

    // Счетчик успешно загруженных массивов
    int array_loading_count(0);

    try {
        // Инициализация драйвера и соединения с базой данных
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        // Подготовка запроса на вставку данных в таблицу arrays
        pstmt = con->prepareStatement("INSERT INTO arrays (array, change_date, type) VALUES (?, ?, ?)");

        // Итерация по всем массивам
        for (size_t i = 0; i < arrays.size(); ++i) {
            // Определение типа массива (сортированный или несортированный)
            type = getArrayType(arrays[i]);

            // Формирование строки с данными для вставки
            for (size_t j = 0; j < arrays[i].size(); ++j) {
                array = array + std::to_string(arrays[i][j]) + ' ';
            }

            // Получение текущей даты и времени
            change_date = getCurrentDateAndTime();

            // Установка значений в подготовленный запрос
            pstmt->setString(1, array);
            pstmt->setString(2, change_date);
            pstmt->setString(3, type);

            // Выполнение запроса на вставку данных
            pstmt->execute();

            // Очистка строки и увеличение счетчика загруженных массивов
            array.clear();
            array_loading_count = i + 1;
        }

        // Освобождение ресурсов
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException e) {
        // Обработка исключения при ошибке подключения к серверу
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
    }

    // Возвращение количества успешно загруженных массивов
    return array_loading_count;
}


void loadDataFromDB(std::vector<std::vector<int>>& arrays, std::vector<std::string>& change_dates) {
    // Объекты для работы с базой данных
    sql::Driver* driver{};
    sql::Connection* con{};
    sql::Statement* stmt{};
    sql::ResultSet* res{};

    try {
        // Инициализация драйвера и соединения с базой данных
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        // Выборка данных из таблицы arrays (столбец array)
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT array FROM arrays");

        // Обработка результатов запроса
        while (res->next()) {
            // Получение строки с данными массива
            std::string array_string = res->getString("array");
            std::vector<int> array;

            // Разбор строки с числами в вектор
            std::istringstream iss(array_string);
            int number;
            while (iss >> number) {
                array.push_back(number);
            }

            // Добавление массива в вектор массивов
            arrays.push_back(array);
        }

        // Выборка данных из таблицы arrays (столбец change_date)
        res = stmt->executeQuery("SELECT change_date FROM arrays");

        // Обработка результатов запроса
        while (res->next()) {
            // Получение строки с датой изменения
            std::string change_date = res->getString("change_date");

            // Добавление даты в вектор дат
            change_dates.push_back(change_date);
        }

        // Освобождение ресурсов
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException e) {
        // Обработка исключения при ошибке подключения к серверу
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
    }
}


bool clearTable() {
    // Объекты для работы с базой данных
    sql::Driver* driver{};
    sql::Connection* con{};
    sql::Statement* stmt{};
    bool is_cleared = false;

    try {
        // Инициализация драйвера и соединения с базой данных
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(database);

        // Удаление всех записей из таблицы arrays
        stmt = con->createStatement();
        stmt->execute("DELETE FROM arrays");

        // Сброс AUTO_INCREMENT для таблицы arrays
        stmt->execute("ALTER TABLE arrays AUTO_INCREMENT = 1");

        // Установка флага очистки в true
        is_cleared = true;

        // Освобождение ресурсов
        delete stmt;
        delete con;
    }
    catch (sql::SQLException e) {
        // Обработка исключения при ошибке подключения к серверу
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
    }

    return is_cleared;
}
