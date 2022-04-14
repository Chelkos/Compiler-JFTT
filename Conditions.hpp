#ifndef CONDITIONS_HPP 
#define CONDITIONS_HPP 
#include "Values.hpp"
using namespace std;
struct cond{
    value *a;
    value *b;
    long long int ind;
    string rel;
    list<string> commandsUndCond;
};
list<string>* FORDc(value *i,value *a,value *b,long long int noLine,list<string>* commandsFor);
list<string>* FORTc(value *i,value *a,value *b,long long int noLine,list<string>* commandsFor);
list<string>* IFc(cond *a,list<string>* commandsIf,long long int noLine);
list<string>* IFELSEc(cond *a,list<string>* commandsIf,list<string>* commandsElse,long long int noLine);
list<string>* REPEATc(cond *a,list<string>* commandsWhile,long long int noLine);
cond *genCondEQ(value *a,value *b);
cond *genCondNEQ(value *a,value *b);
cond *genCondLEQ(value *a,value *b);
cond *genCondGEQ(value *a,value *b);
cond *genCondLE(value *a,value *b);
cond *genCondGE(value *a,value *b);
list<string>* WHILEc(cond *a,list<string>* commandsWhile,long long int noLine);
#endif