#ifndef CODEGEN_HPP 
#define CODEGEN_HPP
#include "Expressions.hpp"
#include "errorHandler.hpp"

using namespace std;





list<string>* WRITEc(value *a,long long int noLine);
void writeItDown(list<string> *cmds);
list<string>* ASSIGNc(value *a,expr *expr,int noLine);
list<string>* READc(value *a,long long int noLine);
bool checkIfValueInit(value *a,int noLine);
void setValueInit(value *a,int noLine);
list<string> *createCommandList(list<string>* a);
list<string> *connectCommandLists(list<string> *commands,list<string> *command);
#endif
