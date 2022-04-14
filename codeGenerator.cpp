#include "codeGenerator.hpp"
using namespace std;
string fileName;
void setValInit(value *a){
    if(!a->type.compare("ARRC")){
        
    }
    

}
list<string> *connectCommandLists(list<string> *commands,list<string> *command){

    commands->splice(commands->end(),*command);
    return commands;
}
list<string> *createCommandList(list<string>* a){
    list<string>* com = new list<string>;
    for(string s:*a){
        com->push_back(s);
    }
    return com;

}
void writeItDown(list<string> *cmds){
    ofstream file;
    file.open(fileName);
    for(string VMLine : *cmds){
        file<<VMLine<<endl;
    }
    cmds->clear();
    
}
bool checkIfValueInit(value *a,int noLine){
    if(!a->type.compare("VAR")){
        mVar *temp= findEl(a->ifVarName);
        if(temp->init){
            return true;
        }else{
            return false;
        }
    }
    else if(!a->type.compare("VAL")){
        return true;
    }
    else if(!a->type.compare("ARRC")){
        mVar *temp= getArrayElement(noLine,a->ifArrName,a->ifArrValVal);
        if(temp->init){
            return true;
        }else{
            return false;
        }

    }
    else if(!a->type.compare("ARRV")){
        return true;
    }


}
void setValueInit(value *a,int noLine){
    if(!a->type.compare("VAR")){
        mVar *temp= findEl(a->ifVarName);
        temp->init = true;
    }
    else if(!a->type.compare("VAL")){
        string errMsg = "Nie wolno przypisywac ani wczytywac stalych";
        printErr(noLine,errMsg);
    }
    else if(!a->type.compare("ARRC")){
        mVar *temp= getArrayElement(noLine,a->ifArrName,a->ifArrValVal);
        temp->init = true;

    }
    else if(!a->type.compare("ARRV")){
    }


}
list<string>* WRITEc(value *a,long long int noLine){
    list<string>* com = new list<string>;

    if(!checkIfValueInit(a,noLine)){
        string errMsg = "Zmienna nie zostala wczesniej zainicjalizowana ";
        printErr(noLine,errMsg);
    }
    mVar *temp = findEl(a->ifVarName);
    if(temp!=nullptr){
    if(!temp->type.compare("ARR")){
            string errMsg = "Niewlasciwe uzycie zmiennej tablicowej "+a->ifVarName;
        printErr(noLine,errMsg);
    }}
    com = generateValueOfValueToReg(a,noLine,"g");
    com->push_back("SWAP g");
    com->push_back("PUT");
    return com;

}
list<string>* READc(value *a,long long int noLine){
    if(!a->type.compare("VAL")){
        string errMsg = "Probujesz zapisac wartosc do stalej";
        printErr(noLine,errMsg);
    }
    if(!a->type.compare("VAR")){
        mVar *temp = findEl(a->ifVarName);
        if(temp!=nullptr){
        if(!temp->type.compare("IT")){
            string errMsg = "Probujesz zmienic iterator "+a->ifVarName;
        printErr(noLine,errMsg);
        }
        if(!temp->type.compare("ARR")){
            string errMsg = "Niewlasciwe uzycie zmiennej tablicowej "+a->ifVarName;
        printErr(noLine,errMsg);
        }}
    }
    list<string>* com =generateAdressToReg(a,noLine,"e");
    com->push_back("GET");
    com->push_back("STORE e");
    setValueInit(a,noLine);
    return com;



}
list<string>* ASSIGNc(value *a,expr *expr,int noLine){
    list<string>* com = new list<string>;
    if(!checkIfValueInit(expr->a,noLine)){
        mVar *temp = findEl(a->ifVarName);
        string errMsg = "Zmienna "+expr->a->ifVarName+" nie  zostala wczesniej zainicjalizowana";
        printErr(noLine,errMsg);
    }
    
   if(!a->type.compare("VAR")){
        mVar *temp = findEl(a->ifVarName);
        if(temp!=nullptr){
        if(!temp->type.compare("IT")){
            string errMsg = "Probujesz zmienic iterator "+a->ifVarName;
        printErr(noLine,errMsg);
        }
        if(!temp->type.compare("ARR")){
            string errMsg = "Niewlasciwe uzycie zmiennej tablicowej "+a->ifVarName;
        printErr(noLine,errMsg);
        }
        }
    }
    com = calculateExprToReg(expr,noLine);
    setValueInit(a,noLine);
    com->splice(com->end(),*generateAdressToReg(a,noLine,"g"));
    
    com->push_back("SWAP f");
    com->push_back("STORE g");
    
    return com;
}





