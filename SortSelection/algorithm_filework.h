#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <io.h>
#include <limits>
#include <vector>

const int Quantity_Reserved_Names = 22; //Значение константа, так как используется в качестве размера массива.
const int Quantity_Forbidden_Characters = 9; //Значение константа, так как используется в качестве размера массива.

int Check_Int();

bool Is_Reserved_Filename(std::string FileName);

bool Txt_Check(const std::string& filename);

bool Filename_Forbidden_Characters_Check(const std::string& filename);

bool File_Exists(std::string FileName);

bool Only_Read(std::string Filename);

std::string Get_File_Name(const std::string& path);

std::string Read_String_Without_Whitespace();
