#include "Algorithm_Filework.h"

/// <summary>
/// Функция, проверяющая есть ли в введённых данных пробелы
/// </summary>
/// <returns> Возвращает введённые данные или сообщение об ошибке, если введённые данные содержат пробел </returns>
std::string Read_String_Without_Whitespace() {
	std::string input; //переменная для хранения пользовательского ввода

	while (true) {
		std::getline(std::cin, input); //ввод строки
		std::istringstream iss(input); //копирование строки в input в переменную iss, в которой хранится строка без пробелов
		//будут введены все символы до первого пробела.

		if (iss >> input && !isspace(input[0])) { //перемещаем значение iss в input и проверяем не идёт ли первым символом
			return input;                         //в input пробел. Если пробела нет, то возвращаем input, завершаем работу фукнции
		}
		else {
			std::cout << "Ошибка: входные данные не должны содержать пробелов. Повторите попытку ввода." << std::endl; //если пробел есть,
		} //возвращаем сообщение об ошибке.
	}
}

/// <summary>
/// Функция проверяет тип введённого значения
/// </summary>
/// <returns> Возвращает введённое значение, если оно целочисленное </returns>
int Check_Int() {
	int tmp = 0;
	std::cin >> tmp; //Ввод значения в целочисленную переменную

	while (std::cin.fail() || tmp < 0) { //Если будет введено не целочисленное значение, то поток ввода проставит
		std::cout << "Введено некорректное значение, попробуйте еще раз: "; //флаг ошибки как 1, по которому проверяется 
		std::cin.clear(); //Правильность типа введённого значения. Затем мы снимаем флаг
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //очищаем буфер
		std::cin >> tmp; //вновь вводим значение
	}

	std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n'); //очищаем буфер
	return tmp;
}

/// <summary>
/// Функция-предикат проверяет существует ли файл
/// </summary>
/// <param name="FileName"> Название файла</param>
/// <returns> Функция возвращает 1, если файл существует, и 0, если файл не существует </returns>
bool File_Exists(std::string FileName) //Функция возвращает true или false в зависимости от того
{									   //существует файл или нет.
	const char* path = FileName.c_str(); //присваиваем значение переменной нуль-терминированной строки
	//Для того, чтобы избежать непредвиденного чтения другой памяти.
	int a = 0;
	a = _access(path, 0);

	return  (!a ? true : false);//тернарный оператор с помощью переменной
}

/// <summary>
/// Функция-предикат проверяет доступен ли файл только для чтения
/// </summary>
/// <param name="FileName"> Название файла</param>
/// <returns>Функция возвращает 1, если файл доступен только для чтения, и 0, если файл не доступен только для чтения</returns>
bool Only_Read(std::string FileName) { //Функция возвращает true или false в зависимости от того
	const char* path = FileName.c_str();//Доступен ли файл только для чтения.
	if (_access(path, 2) == -1) {
		return true;
	}
	else
		return false;
}

/// <summary>
/// Функция-предикат сравнивает название файла со списком зарезервированных названий, отбрасывая файловое расширение
/// </summary>
/// <param name="FileName"> Название файла </param>
/// <returns> Функция возвращает 1, если название файла зарезервирванно, и 0, если название файла незарезервированно </returns>
bool Is_Reserved_Filename(std::string FileName) {
	std::string Reserved_Names[Quantity_Reserved_Names] = { "con", "prn" , "aux" , "nul" , "com1" , "com2" , "com3" , "com4" , "com5" , "com6" , "com7" , "com8" , "com9" ,
	"lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9" };
	//Зарезервированные имена используются системой для названия портов или контроллеров, их нельзя использовать
	//Как названия файлов.
	size_t pos = FileName.find_first_of("."); //Находим положение точки в названии файла
	if (pos != std::string::npos) { //Если в имени файла есть точка
		FileName = FileName.substr(0, pos); //То мы отбрасываем формат файла, чтоб оставить только название
	}

	for (int i = 0; i < Quantity_Reserved_Names; i++) { //В цикле проверяем название файла
		if (_stricmp(FileName.c_str(), Reserved_Names[i].c_str()) == 0) { //со списком запрещённых названий
			return true; //Если названия совпадают, то возвращается ноль, а функция возвращает true
		} //что значит, что название файла - зарезервированное
	}
	return false; //Если название незарезервированное, то возвращается false
}

/// <summary>
/// Функция-предикат проверяет текстовое ли расширение у файла
/// </summary>
/// <param name="filename"> Название файла </param>
/// <returns> Возвращает 1, если .txt есть в названии файла, и 0, если этого расширения нет у файла </returns>
bool Txt_Check(const std::string& filename) {
	std::string extension = ".txt";
	size_t strLength = filename.length(); //длина передаваемого названия файла
	size_t extLength = extension.length(); //длина .txt

	if (strLength < extLength) { //если длина названия файла меньше, чем .txt
		std::cout << "Файл должен быть текстового расширения." << std::endl; //то можно предположить, что
		return false; //файл не текстового расширения.
	}

	if (strLength == extLength) { //Если длины равны, то можно предположить,
		std::cout << "Пустой формат файла!" << std::endl; //что пользователь ввёл только название.
		return false;
	}

	std::string end = filename.substr(strLength - extLength, extLength); //возвращаем концовку названия файла,
	//которая начинается с позиции длина строки минус длина формата,
	//и берём столько символов на концовку, сколько требует длина .txt

	return end.compare(extension) == 0; //возвращаем значение сравнения .txt и концовки файла. Когда они идентичны
	//функция возвращает 0.
	//сравнение значения 0 с 0 вернёт 1
}

/// <summary>
/// Функция-предикат проверяет содержится ли в названии файлов запрещённый символ
/// </summary>
/// <param name="filename"> Название файла</param>
/// <returns> Возвращает 1, если в названии файла содержится запрещённый символ, и 0, если запрещённых символов в названии не содержится </returns>
bool Filename_Forbidden_Characters_Check(const std::string& filename) {//проверка названия на запрещённые символы
	std::string Reserved_Characters[Quantity_Forbidden_Characters] = { "/", "\\", "|", ":", "*", "?", "\"", "<", ">" };

	for (int i = 0; i < Quantity_Forbidden_Characters; i++) { //в цикле находим позицию запрещённого символа в переданном параметре

		if (filename.find(Reserved_Characters[i]) != std::string::npos) { //Если позиция будет найдена
			return true; //возвращаем true
		}
	}
	return false; //если запрещённых символов не найдено в названии файла возвращаем false
}

/// <summary>
/// Функция возвращает строку название файла из введённого пути файла.
/// </summary>
/// <param name="path"> Путь к файлу </param>
/// <returns> Название файла</returns>
std::string Get_File_Name(const std::string& path) {
	size_t pos = path.find_last_of("\\"); // Ищем последний символ '/' или '\'

	if (pos != std::string::npos) { // Если символ найден
		return path.substr(pos + 1); // Возвращаем имя файла после найденного символа
	}
	return path; // Если символ не найден, возвращаем исходный путь
}