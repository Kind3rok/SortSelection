#include "CppUnitTest.h"
#include "..\RPS-3-Baev-Ivlev-425\main_algorithms.h"
#include "..\RPS-3-Baev-Ivlev-425\database.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsForDB {
	TEST_CLASS(TestsForDB) {
	public:
		// Тестирование добавления 100 случайных массивов в базу данных
		TEST_METHOD(t1_addArrays100) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(100);
			int array_loading_counter{};
			generateRandomArrays(arrays, change_dates, static_cast<size_t>(number_of_arrays));
			array_loading_counter = initializeDB(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование добавления 1000 случайных массивов в базу данных
		TEST_METHOD(t4_addArrays1000) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(1000);
			int array_loading_counter{};

			generateRandomArrays(arrays, change_dates, static_cast<size_t>(number_of_arrays));
			array_loading_counter = initializeDB(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование добавления 10000 случайных массивов в базу данных
		TEST_METHOD(t7_addArrays10000) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(10000);
			int array_loading_counter{};

			generateRandomArrays(arrays, change_dates, static_cast<size_t>(number_of_arrays));
			array_loading_counter = initializeDB(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование загрузки 100 массивов из базы данных и их сортировки
		TEST_METHOD(t2_uploadArrays100) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(100);
			int array_loading_counter{};

			loadDataFromDB(arrays, change_dates);
			array_loading_counter = static_cast<int>(arrays.size());
			startSorting(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование загрузки 1000 массивов из базы данных и их сортировки
		TEST_METHOD(t5_uploadArrays1000) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(1000);
			int array_loading_counter{};

			loadDataFromDB(arrays, change_dates);
			array_loading_counter = static_cast<int>(arrays.size());
			startSorting(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование загрузки 10000 массивов из базы данных и их сортировки
		TEST_METHOD(t8_uploadArrays10000) {
			std::vector<std::vector<int>> arrays{};
			std::vector<std::string> change_dates{};
			int number_of_arrays(10000);
			int array_loading_counter{};

			loadDataFromDB(arrays, change_dates);
			array_loading_counter = static_cast<int>(arrays.size());
			startSorting(arrays);

			Assert::AreEqual(number_of_arrays, array_loading_counter);
		}

		// Тестирование очистки базы данных после добавления 100 массивов
		TEST_METHOD(t3_databaseCleaning100) {
			bool success = clearTable();

			Assert::IsTrue(success, L"test failed or the database has already been cleared");
		}

		// Тестирование очистки базы данных после добавления 1000 массивов
		TEST_METHOD(t6_databaseCleaning1000) {
			bool success = clearTable();

			Assert::IsTrue(success, L"test failed or the database has already been cleared");
		}

		// Тестирование очистки базы данных после добавления 10000 массивов
		TEST_METHOD(t9_databaseCleaning10000) {
			bool success = clearTable();

			Assert::IsTrue(success, L"test failed or the database has already been cleared");
		}
	};
}
