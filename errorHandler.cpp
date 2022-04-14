#include "errorHandler.hpp"
void printErr(int noLine,string errMsg){
    cerr<<"Error at line "<<noLine<<endl;
    cerr<<"Error message: "<<errMsg<<endl;
    exit(-1);
}