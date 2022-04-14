#ifndef VALUES_HPP 
#define VALUES_HPP
#include "errorHandler.hpp"
#include "Memory/lookupTab.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <list>
#include<bitset>

using namespace std;
struct value{
    string type; //VAR or VAL or ARRV or ARRC
    long long int ifValValue;
    string ifVarName;
    string ifArrName;
    string ifArrVarPtr;
    long long int ifArrValVal;

};

list<string>* generateAdressToReg(value *a,int noLine,string r);
value *genVAL(long long int num, int noLine);
value *genVAR(string name,int noLine);
value *genARRC(string arrName,long long int index, int noLine);
value *genARRV(string arrName,string varName, int noLine);
list<string>* saveValueToMemory(value *a,string reg,int noLine);
list<string>* loadValueFromMemory(value *a,string reg,int noLine);
list<string>* genNum(long long  num, string reg);
list<string>* generateValueOfValueToReg(value *a,int noLine,string r);
#endif