#pragma once
#include <vector>
enum PrintMenu {
	StartProgramm = 1,
	StopProgramm
};

void Print_Menu();
void Main_Menu();
void Start_Programm(std::vector <int>& vect, std::vector <int>& copyVect);
