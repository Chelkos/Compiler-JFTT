#ifndef TAB_HPP 
#define TAB_HPP
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <string>
#include <list>
#include<iterator>
#include <regex>
#include "../Values.hpp"
#include "../errorHandler.hpp"
using namespace std;
struct value;
struct mVar{
    string name;
    string type; //czy elemnet jest w tablicy czy jest zmienną VAR,ARR, IT
    long long int endIndex; //jeżeli tab to jaka dł
    long long int startIndex; //
    long long int ifInArrayWhatIndex;
    long long int listIndex; //jaki indeks zmiennej w tablicy
    bool init; //zainicjalizowany 0-nie 1-tak
};
void deleteEndIt(long long int noLine,value* b);
void createEndIt(long long int noLine,string* elNamee);
void insertIt(string eName,long long int eLen, long long int eStart, string eType );
void insertEl(string,long long int, long long int, string );
mVar* findEl(string);
void createEl(long long int , string );
void createArr(long long int ,long long int , long long int , string);
long long int checkIfElInit(long long int ,string );
void initializeEl(long long int ,string);
void reserveSpace(long long int);
long long int adrName(string);
long long int adrArrName(string,string);
long long int adrArrConst(string,long long int);
long long int getLen();
bool checkForLettersOnly(string s);
mVar* getArrayElement(long long int noLine,string arrName,long long int index);
void createIt(long long int noLine,string *elName);
void deleteIt(long long int noLine,value* b);
#endif