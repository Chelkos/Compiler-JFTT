#include "Values.hpp"
using namespace std;
list<string>* generateValueOfValueToReg(value *a,int noLine,string r){
    list<string> *com = new list<string>;
    if(!a->type.compare("VAL")){
        com->splice(com->end(),*genNum(a->ifValValue,r));
    }else{  
        com->splice(com->end(),*loadValueFromMemory(a,r,noLine));
        
    }
    return com;
}

list<string>* generateAdressToReg(value *a,int noLine,string r){
    list<string> *com = new list<string>;
    if(!a->type.compare("VAR")){
        mVar *temp = findEl(a->ifVarName);
        long long int addr = temp->listIndex;
        com = genNum(addr,r);


    }else if(!a->type.compare("ARRV")){
        mVar *temp = findEl(a->ifArrName);
        long long int basicAdrr = temp->listIndex;
        long long int firstIndex = temp->startIndex;
       
        com = loadValueFromMemory(genVAR(a->ifArrVarPtr,noLine),"d",noLine);
        long long int addr = basicAdrr-firstIndex+1;
        com->push_back("RESET c");
        com->splice(com->end(),*genNum(addr,"c"));

        com->push_back("SWAP c");
        com->push_back("ADD d");
        com->push_back("SWAP "+r);
    }else if(!a->type.compare("ARRC")){
        mVar *temp = findEl(a->ifArrName);
        long long int addr = temp->listIndex+a->ifArrValVal-temp->startIndex+1;
 
        com = genNum(addr,r);

    }else{
        string errMsg="Probujesz pobrac miejsce w pamieci stalej wartosci";
        printErr(noLine,errMsg);

    }
    return com;



}
value *genVAL(long long int num, int noLine){
    value *val = new value;
    val->type ="VAL";
    val->ifValValue = num;
    return val;
}
value *genVAR(string name,int noLine){
    value *val = new value;
    mVar *a = findEl(name);
    if(a!=nullptr){
        val->type = "VAR";
        val->ifVarName = name;
        return val;
    }else{
        string errMsg="Zmienna "+name+" nie zostala zadeklarowana";
        printErr(noLine,errMsg);
    }
}
value *genARRC(string arrName,long long int index, int noLine){
    value *val = new value;
    mVar *a = findEl(arrName);
    if(a->type.compare("ARR")){
        string errMsg="Zmienna "+arrName+" nie jest tablicowa";
        printErr(noLine,errMsg);
    }
   val->type = "ARRC";
   val->ifArrName = arrName;
   val->ifArrValVal = index;
   return val;
}
value *genARRV(string arrName,string varName, int noLine){ 
    value *val = new value;
    mVar *tab = findEl(arrName);
    if(tab!=nullptr){
        if(tab->type.compare("ARR"))
        {
        string errMsg="Zmienna "+arrName+" nie jest tablicowa";
        printErr(noLine,errMsg);
        }
        val->type = "ARRV";
        val->ifArrName = arrName;
        mVar *ptr = findEl(varName);
        if(ptr!=nullptr){
            // if(ptr->type.compare("VAR")){
            //     string errMsg="Zmienna " +varName+" nie jest typu VAR";
            //     printErr(noLine,errMsg);
            // }
            // if(!ptr->init){
            //     string errMsg="Zmienna " +varName+" nie zostala zainicjalizowana";
            //     printErr(noLine,errMsg);
            // }
            val->ifArrVarPtr = varName;
            return val;
        }
        else{
        string errMsg="Zmienna "+varName+" nie zostala zadeklarowana";
        printErr(noLine,errMsg);
        }
        
    }else{
        string errMsg="Zmienna "+arrName+" nie zostala zadeklarowana";
        printErr(noLine,errMsg);
    }
    return val;
}




list<string>* saveValueToMemory(value *a,string reg,int noLine){ // Wrzuć w zmienną wartość z rejestru
    list<string>* commands = new list<string>;
    if(!reg.compare("a")){
        commands->push_back("SWAP "+reg); // teraz w rejestrze a mamy wartość z podanego rejestru 
        
    }
    list<string>* generateIndex = generateAdressToReg(a,noLine,"h");
    commands->splice(commands->end(), *generateIndex);
    commands->push_back("SWAP "+reg);
    commands->push_back("STORE h");
    return commands;
    


}
list<string>* loadValueFromMemory(value *a,string reg,int noLine){
    list<string> *commands = new list<string>;
    ;
    if(!reg.compare("a")){
        commands->push_back("SWAP "+reg); // teraz w rejestrze a mamy wartość z podanego rejestru 
    }
    commands->push_back("SWAP g"); // teraz mamy w rejestrze g tą wartość
    list<string>* generateIndex = generateAdressToReg(a,noLine,"h");
    commands->splice(commands->end(),*generateIndex);
    commands->push_back("LOAD h");
    commands->push_back("SWAP "+reg);
    return commands;

}
list<string>* genNum(long long num, string reg){
    list<string>  *currCom= new list<string>;
    string secReg = "b";
    bool isNegative = false;
    if(num<0){
        isNegative=true;
        num = num*(-1);
    }
    string binNum = bitset<120>(num).to_string();
    const char* binTab =binNum.c_str();
    long long len =0;
    currCom->push_back("RESET a");
    currCom->push_back("RESET "+secReg);
    currCom->push_back("INC "+secReg);
    while(binTab[len]=='0')
        len++;
    for(long long int n = len;n<binNum.length();n++)
    {
        if(binTab[n]=='1'){
            if(isNegative){
                currCom->push_back("DEC a");
            }else{
                currCom->push_back("INC a");
            }

        }
            currCom->push_back("SHIFT "+secReg);
            
    }
    currCom->pop_back();
    if(reg.compare("a"))
    {
       
        currCom->push_back("SWAP "+reg);
    }
    return currCom;
}
