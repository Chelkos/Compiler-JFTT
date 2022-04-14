#include "lookupTab.hpp"
using namespace std;
long long int nextFree=0;
list<mVar*> lookupTab;
auto l_front = lookupTab.begin();
void insertElInArray(string eName,long long int eLen, long long int eStart, string eType, int arrIndex ){
    mVar *newy = new mVar();
    newy->name=eName;
    newy->type=eType;
    newy->endIndex=eLen;
    newy->ifInArrayWhatIndex=arrIndex;
    newy->startIndex=eStart;
    newy->listIndex=nextFree;
    newy->init=false;
    lookupTab.push_back(newy);  


}
void insertEl(string eName,long long int eLen, long long int eStart, string eType ){
    mVar *newy = new mVar();
    newy->name=eName;
    newy->type=eType;
    newy->endIndex=eLen;
    newy->ifInArrayWhatIndex=0;
    newy->startIndex=eStart;
    newy->init=false;
    newy->listIndex=nextFree;
    lookupTab.push_back(newy);
}
void insertIt(string eName,long long int eLen, long long int eStart, string eType ){
    mVar *newy = new mVar();
    newy->name=eName;
    newy->type=eType;
    newy->endIndex=eLen;
    newy->ifInArrayWhatIndex=0;
    newy->startIndex=eStart;
    newy->init=true;
    newy->listIndex=nextFree;
    lookupTab.push_back(newy);
}
bool checkForLettersOnly(string s){
    bool flag =false;
    for(char c : s){
        flag =false;
        if(c=='_')
            continue;
        for(char a='a';a<='z';a++){
            if(c==a){
                flag=true;
                break;
            }
        }
        if(flag==true){
            continue;
        }
        return false;
    }
    return true;
}
mVar *findEl(string eName){
    for(mVar *el : lookupTab){
        if(!el->name.compare(eName)){
            return el;
        }
    }
    return nullptr;
}
long long int getLen(){
    return lookupTab.size();
}
void deleteEndIt(long long int noLine,value* b){
mVar *a = findEl(b->ifVarName+"1");
a->name="";
}
void deleteIt(long long int noLine,value* b){
mVar *a = findEl(b->ifVarName);
a->name="";
}
void createEndIt(long long int noLine,string* elNamee){
    string elName = *elNamee;
    string one = "1";
    elName = elName+one;
    insertIt(elName,1,1,"IT");
    nextFree++;
    
    
    }
void createIt(long long int noLine,string* elNamee){
    string elName = *elNamee;
    if(!checkForLettersOnly(elName))
        {
            string errMsg="Zmienna "+elName+" zawiera niedozwolone znaki";
            printErr(noLine,errMsg);
        }
    mVar *findy = findEl(elName); 
   if(findy==0){
    
            insertIt(elName,1,1,"IT");
            nextFree++;
   }else{
       string errMsg="Zmienna "+elName+" zostala juz zainicjalizowana";
       printErr(noLine,errMsg);
   }
    
    
    }
void createEl(long long int noLine, string elName){
    if(!checkForLettersOnly(elName))
        {
            string errMsg="Zmienna "+elName+" zawiera niedozwolone znaki";
            printErr(noLine,errMsg);
        }
   mVar *findy = findEl(elName); 
   if(findy==0){
    
            insertEl(elName,1,1,"VAR");
            nextFree++;
   }else{
       string errMsg="Zmienna "+elName+" zostala juz zainicjalizowana";
       printErr(noLine,errMsg);
   }
}

void initializeEl(long long int noLine,string elName){
    mVar *findy = findEl(elName);
    if(findy == nullptr){
        string errMsg="Zmienna "+elName+" nie istnieje";
       printErr(noLine,errMsg);
       return;
    }else{
        findy->init=true;
    }
}

void insertToArrayByNum(long long int noLine,string arrName,long long int index){
    mVar *arrBegin = findEl(arrName);
    if(arrBegin == nullptr){
        string errMsg="Zmienna "+arrName+" nie istnieje";
       printErr(noLine,errMsg);
       return;
    }else if(arrBegin->endIndex< index || arrBegin->startIndex>index){
        string errMsg="Probujesz dostac sie do zmiennej poza zakresem tablicy";
        printErr(noLine,errMsg);
    }else{
        auto arrIt = lookupTab.begin();
        long long int shift = abs(arrBegin->startIndex-index);
        advance(arrIt,arrBegin->listIndex+shift);
        mVar *newy = *arrIt;
        newy->init = true;

        
    }

}
long long int checkIfElInit(long long int noLine,string elName){
    mVar *findy = findEl(elName);
    if(findy == nullptr){
        string errMsg="Zmienna "+elName+" nie istnieje";
       printErr(noLine,errMsg);
       return -1;
    }else{
        return findy->init;
    }
}

void createArr(long long int stIndx,long long int endIndx, long long int noLine, string elName){
    if(!checkForLettersOnly(elName))
        {
            string errMsg="Zmienna "+elName+" zawiera niedozwolone znaki";
            printErr(noLine,errMsg);
        }
   mVar *newy; 
   newy = findEl(elName);
   long long int posLen = endIndx-stIndx+1;
   if(newy!=nullptr){
       string errMsg="Zmienna "+elName+" zostala juz zainicjalizowana";
       printErr(noLine,errMsg);
       return;
   }
    if(posLen<=0){
        string errMsg="Bledny zakres tablicy. Miales moze na mysli "+elName+"["+to_string(endIndx)+":"+to_string(stIndx)+"]";
       printErr(noLine,errMsg);
       return;
    }
    insertEl(elName,endIndx,stIndx,"ARR");
    nextFree+=posLen+(int)lookupTab.size();
}
mVar* getArrayElement(long long int noLine,string arrName,long long int index){
    mVar *arrBegin = findEl(arrName);
    if(arrBegin == nullptr){
        string errMsg="Zmienna "+arrName+" nie istnieje";
       printErr(noLine,errMsg);
       return nullptr;
    }else if(arrBegin->endIndex< index || arrBegin->startIndex>index){
        string errMsg="Probujesz dostac sie do zmiennej poza zakresem tablicy";
        printErr(noLine,errMsg);
    }else{
        auto arrIt = lookupTab.begin();
        int shift = abs(arrBegin->startIndex-index+1);
        advance(arrIt,arrBegin->listIndex+shift);
        mVar *newy = *arrIt;
        // if(newy->init==false){
        //     string errMsg="Zmienna "+arrName+"["+to_string(index)+"]"+" nie zostala zainicjalizowana";
        //      printErr(noLine,errMsg);
            
        // }
        return  newy; 

        
    }

}
long long int adrName(string name){
    mVar* a = findEl(name);
    if(a!=nullptr){
        return a->listIndex;
    }

}
long long int adrArrName(string na,string nb){
    mVar* a = findEl(na);
    mVar* b = findEl(nb);


}
long long int adrArrConst(string,long long int){


}