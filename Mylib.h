#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>

using std::wstring;
using std::iswalpha;
using std::towlower;
using std::wofstream;
using std::unordered_map;
using std::vector;
using std::setw;
using std::endl;
using std::to_wstring;
using std::ifstream;
using std::cerr;
using std::regex;
using std::string;
using std::getline;
using std::sregex_iterator;
using std::ispunct;
using std::ofstream;
using std::wifstream;
using std::wcerr;
using std::wstringstream;
using std::cout;
using std::cin;
using std::wcout;

wstring cleanWord(const wstring& word);
void printCrossReferenceTable(wofstream& outputFile,
                              const unordered_map<wstring, vector<int>>& wordLines,
                              const unordered_map<wstring, int>& wordCount,
                              int maxWidth);

#endif // MYLIB_H_INCLUDED
