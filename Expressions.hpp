
#ifndef EXPRESSIONS_HPP 
#define EXPRESSIONS_HPP
#include "Conditions.hpp"
using namespace std;
struct expr{
    value *a;
    value *b;
    string type;
};
expr *generateExpr(value *ta,value*tb,string type);
list<string>* TIMESc(value *a,value *b,int noLine,string reg);
list<string>* PLUSc(value *a,value *b,int noLine,string r);
list<string>* MINUSc(value *a,value *b,int noLine,string r);
list<string>* DIVc(value *a,value *b,int noLine,string r);
list<string>* calculateExprToReg(expr *ex,long long int noLine);
list<string>* MODc(value *a,value *b,int noLine,string r);
#endif