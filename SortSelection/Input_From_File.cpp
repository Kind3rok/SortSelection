#include "Input_From_File.h"
#include "Algorithm_Filework.h"
/// <summary>
/// Функция для ввода значений вектора из файла
/// </summary>
/// <param name="vect"> вектор, заполняемый значениями из файла </param>
void Input_From_File(std::vector<int>& vect)
{
	bool isPathCorrect = false; //флаг проверки корректности введённого пути 
	bool isFileCorrect = true; //флаг проверки корректности файла
	int elements = 0; //кол-во элементов, которые будут переданы в вектор
	int intTmp; //переменная для временного хранения элемента из файла
	std::string path;
	std::string filename;
	std::ifstream file; //переменная для открытия файла и записи из него

	do {
		std::cout << "Введите путь файла:" << std::endl << "> ";
		path = Read_String_Without_Whitespace(); //читаем введённый путь без пробелов.

		while (!isPathCorrect) {

			//проверяем существует ли файл, введено ли имя с запрещёнными символами или введён ли формат пустой или отличный от .txt
			if (!File_Exists(path)) {
				std::cout << "Файл не существует, попробуйте ввести другой путь." << std::endl;
				std::cout << "Введите путь:";
				path = Read_String_Without_Whitespace();
				continue;
			}

			filename = Get_File_Name(path);

			if (!Txt_Check(filename)) {
				std::cout << "Введите другой путь:";
				std::cin >> path;
				continue;
			};

			if (Filename_Forbidden_Characters_Check(filename)) {
				std::cout << "В имени файла не должно содержаться недопустимых символов." << std::endl;
				std::cout << "Введите другой путь:";
				std::cin >> path;
				continue;
			};

			isPathCorrect = true;
		}
		filename = Get_File_Name(path);
		file.open(path); //открываем файл
		std::cout << "Файл успешно открыт!" << std::endl;

		if (file.peek() == std::ifstream::traits_type::eof()) { //peek() возвращает либо следующий символ в файловом потоке
																//либо EOF. Если следующий символ сразу после открытия файла
																//является EOF, то можно заключить, что файл пуст
																//и начать цикл заново после сообщения об ошибке.
			std::cout << "Файл пуст. Заполните файл и попробуйте еще раз." << std::endl;
		}

		else {

			while (!file.eof()) { //Проверяем тип значений в файле, пока не дойдём до EOF.
				file >> intTmp;

				if (file.fail()) { //Если тип переданного значения не соответсвует типу переменной, то
					file.clear(); //будет проставлен флаг ошибки как 1. Очищаем все флаги
					isFileCorrect = false; //И проставляем свой собственный флаг проверки корректности файла как false
					break;
				}
			}

			file.clear();
			file.seekg(0); //Переставляем курсор в начало файла после проверки всех значений.

			if (isFileCorrect) { //Заполняем вектор значениями, если файл корректный.

				file >> elements; //Берём кол-во элементов из файла.

				for (int i = 0; i < elements; i++) {
					file >> intTmp;
					vect.push_back(intTmp);
				}

			}

			if (!isFileCorrect) { //Если файл некорректный, то возвращаем сообщение об ошибке и закрываем файл.
				std::cout << "В файле содержится некорректно заполненный массив. Исправьте файл и попробуйте еще раз." << std::endl;
				file.close();
			}
		}
		file.close();
	} while (!isFileCorrect); //В цикле вводится путь файла до тех пор, пока введённый файл не окажется корректно заполненным
}