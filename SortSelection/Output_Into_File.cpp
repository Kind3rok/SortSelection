#include "Output_Into_File.h"
#include "Algorithm_Filework.h"

/// <summary>
/// Функция вывода результата работы программы в отдельный файл
/// </summary>
/// <param name="vect"> исходный вектор </param>
/// <param name="vect2"> сортированная вектор-копия </param>
void Output_Into_File(std::vector<int>& vect, std::vector<int>& vect2)
{
	std::string fileName;
	std::ofstream file;
	int saveChoise = 0; //Переменная, хранящая выбор 'сохранить или нет' пользователя
	int saveMethod = 0; //Метод сохранения (добавление в конце, перезапись, выбор другого файла) после ввода пути
	int fileMethod = 0; //Переменная, хранящая выбор "создать ли файл или нет", если введённого файла не существует.

	do {
		std::cout << "1 - Сохранить в файл." << std::endl << "2 - Продолжить без сохранения." << std::endl << "> ";
		saveChoise = Check_Int();
		switch (saveChoise) {
		case Save:

			while (true) {
				std::cout << "Введите путь к файлу для сохранения:" << std::endl << "> ";
				fileName = Read_String_Without_Whitespace();
				//Внутри условия цикла имя файла проверяется на наличие расширения .txt, является ли имя файла зарезервированным и есть ли в имени файла недопустимые символы
				while (Is_Reserved_Filename(Get_File_Name(fileName)) || Filename_Forbidden_Characters_Check(Get_File_Name(fileName)) || !Txt_Check(Get_File_Name(fileName))) {
					std::cout << "Недопустимое название или формат файла. Попробуйте еще раз." << std::endl << "> ";
					fileName = Read_String_Without_Whitespace();
				}
				//Проверка существования файла. Если файл существует, его предлагается запустить в одном из двух режимов, либо выбрать другой файл.
				if (File_Exists(fileName)) {

					do {
						std::cout << "Файл уже существует. Выберите режим ввода: " << std::endl << "1 - Перезаписать файл" << std::endl << "2 - Записать в конец файла" << std::endl << "3 - Выбрать другой файл" << std::endl << "> ";
						saveMethod = Check_Int();
						switch (saveMethod) {
							//В зависимости от выбора пользователя, файл открывается, и содержимое стирается, файл открывается,
							//и к содержимому в конец добавляются полученные данные
						case RewriteFile:
							file.open(fileName, std::ios::trunc);
							break;
						case WriteToTheEndOfTheFile:
							file.open(fileName, std::ios::app);
							file << '\n';
							break;
						case SelectAnotherFile:
							break;
						default:
							std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
							break;
						}
					} while (saveMethod != RewriteFile && saveMethod != WriteToTheEndOfTheFile && saveMethod != SelectAnotherFile);

				}

				else if (Only_Read(fileName)) {
					std::cout << "Ошибка доступа к файлу. Файл доступен только для чтения." << std::endl;
					break;
				}

				//Если файла не существует, выходим из внешнего цикла while.
				if (saveMethod == RewriteFile || saveMethod == WriteToTheEndOfTheFile || !File_Exists(fileName)) {
					break;
				}

			}

			if (!File_Exists(fileName)) { //Если файла не существует, предлагаем создать его или продолжить без сохранения

				do {
					std::cout << "Файла по данному пути не найдено, хотите создать его?" << std::endl
						<< "1 - Создать файл." << std::endl << "2 - Продолжить без сохранения." << std::endl << "> ";
					fileMethod = Check_Int();
					switch (fileMethod) {
					case CreateFile:
						file.open(fileName);
						break;
					case ContunueWithoutCreatingFile:
						break;
					default:
						std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
						break;
					}
				} while (fileMethod != CreateFile && fileMethod != ContunueWithoutCreatingFile);

			}

			//Проверяем проставлены ли параметры метода сохранения (перезапись или добавление) 
			// и выбрана ли опция сохранения в файл или продолжения без сохранения 
			//Перед записью вектора в файл.
			if (saveMethod == RewriteFile || saveMethod == WriteToTheEndOfTheFile || fileMethod == CreateFile) {
				file << "Исходный вектор: " << '\n';

				for (int i = 0; i < vect.size(); i++) {
					file << vect[i] << ' ';
					if (i == vect.size() - 1) file << '\n';
				}

				file << '\n' << "Сортированный вектор:" << '\n';

				for (int i = 0; i < vect2.size(); i++) {
					file << vect2[i] << ' ';
				}

			}

			file.close();
			break;
		case ContinueWithoutSaving:
			break;
		default:
			std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
			break;
		}

	} while (saveChoise != Save && saveChoise != ContinueWithoutSaving);
}
