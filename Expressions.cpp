#include "Expressions.hpp"
expr *generateExpr(value *ta,value*tb,string type){
    expr *ex = new expr;
    ex->a=ta;
    ex->b=tb;
    ex->type=type;
    return ex;
}
list<string>* calculateExprToReg(expr *ex,long long int noLine){
    list<string> *com = new list<string>;
    string reg ="f";
    if(!ex->type.compare("VAL")){
        value *a = ex->a;
        if(!a->type.compare("VAL")){
            com = genNum(a->ifValValue,reg);
        }else {
            com = loadValueFromMemory(a,reg,noLine);
        }
    }else if(!ex->type.compare("PLUS")){
        com= PLUSc(ex->a,ex->b,noLine,reg);

    }else if(!ex->type.compare("MINUS")){
        com= MINUSc(ex->a,ex->b,noLine,reg);
        
    }else if(!ex->type.compare("TIMES")){
        com= TIMESc(ex->a,ex->b,noLine,reg);
        
    }else if(!ex->type.compare("DIV")){
        com= DIVc(ex->a,ex->b,noLine,reg);

    }else if(!ex->type.compare("MOD")){
        com= MODc(ex->a,ex->b,noLine,reg);
        
    }
    return com;
}
list<string>* MODc(value *a,value *b,int noLine,string r){
list<string> *com = new list<string>;
    if(!a->type.compare("VAL")){
        com->splice(com->end(),*genNum(a->ifValValue,"c"));
    }else{  
        com->splice(com->end(),*loadValueFromMemory(a,"c",noLine));
        
    }
    if(!b->type.compare("VAL")){
        com->splice(com->end(),*genNum(b->ifValValue,"d"));
    }else{  
        com->splice(com->end(),*loadValueFromMemory(b,"d",noLine));
    }
// com->push_back("SWAP f");
// com->push_back("SWAP d");
// com->push_back("SWAP e");
// com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("RESET e");
com->push_back("RESET f");

com->push_back("SWAP c");
com->push_back("JZERO 62");
com->push_back("JPOS 4");
com->push_back("DEC f");
com->push_back("SWAP c");
com->push_back("SUB c");
com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("SWAP d");
com->push_back("JZERO 54");
com->push_back("JPOS 5");
com->push_back("DEC e");
com->push_back("INC f");
com->push_back("SWAP d");
com->push_back("SUB d");
com->push_back("SWAP d");
com->push_back("RESET a");
com->push_back("RESET b");
com->push_back("RESET h");
com->push_back("RESET g");
com->push_back("INC h");
com->push_back("DEC g");
com->push_back("ADD d");
com->push_back("SWAP b");
com->push_back("RESET a");
com->push_back("SUB c");
com->push_back("ADD b");
com->push_back("JPOS 5");
com->push_back("SWAP b");
com->push_back("SHIFT h");
com->push_back("SWAP b");
com->push_back("JUMP -7");
// com->push_back("RESET a");
// com->push_back("RESET h");
// com->push_back("ADD c");
// com->push_back("SWAP h");
com->push_back("SWAP b");
com->push_back("SHIFT g");
com->push_back("SWAP b");
com->push_back("RESET a");
com->push_back("ADD b");
com->push_back("SUB d");
com->push_back("JNEG 10");
com->push_back("RESET a");
com->push_back("ADD c");
com->push_back("SUB b");
com->push_back("JNEG 2");
com->push_back("SWAP c");
com->push_back("SWAP b");
com->push_back("SHIFT g");
com->push_back("SWAP b");
com->push_back("JUMP -12");
com->push_back("SWAP c");
com->push_back("JZERO 14");
com->push_back("SWAP c");
com->push_back("SWAP f");
com->push_back("JZERO 5");
com->push_back("RESET a");
com->push_back("SUB c");
com->push_back("ADD d");
com->push_back("SWAP c");
com->push_back("SWAP e");
com->push_back("JZERO 4");
com->push_back("RESET a");
com->push_back("SUB c");
com->push_back("SWAP c");
com->push_back("SWAP c");
com->push_back("SWAP "+r);

return com;

}
list<string>* PLUSc(value *a,value *b,int noLine,string r){
    list<string>* com = new list<string>;
    if(!a->type.compare("VAL")){
         com->splice(com->end(),*genNum(a->ifValValue,"e"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(a,"e",noLine));
        
    }
    if(!b->type.compare("VAL")){
         com->splice(com->end(),*genNum(b->ifValValue,"f"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(b,"f",noLine));
    }
    com->push_back("SWAP e");
    com->push_back("ADD f");
    com->push_back("SWAP "+r);
    return com;
}
list<string>* MINUSc(value *a,value *b,int noLine,string r){
    list<string> *com = new list<string>;
    if(!a->type.compare("VAL")){
         com->splice(com->end(),*genNum(a->ifValValue,"e"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(a,"e",noLine));
        
    }
    if(!b->type.compare("VAL")){
         com->splice(com->end(),*genNum(b->ifValValue,"f"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(b,"f",noLine));
    }
    com->push_back("SWAP e");
    com->push_back("SUB f");
    com->push_back("SWAP "+r);
    return com;
}
list<string>* DIVc(value *a,value *b,int noLine,string r){
    list<string>* com = new list<string>;
    if(!a->type.compare("VAL")){
        com->splice(com->end(),*genNum(a->ifValValue,"c"));
    }else{  
        com->splice(com->end(),*loadValueFromMemory(a,"c",noLine));
        
    }
    if(!b->type.compare("VAL")){
        com->splice(com->end(),*genNum(b->ifValValue,"d"));
    }else{  
        com->splice(com->end(),*loadValueFromMemory(b,"d",noLine));
    }
// com->push_back("SWAP f");
// com->push_back("SWAP d");
// com->push_back("SWAP e");
// com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("RESET b");
com->push_back("RESET e");
com->push_back("RESET f");

com->push_back("SWAP c");
com->push_back("JZERO 60");
com->push_back("JPOS 4");
com->push_back("INC e");
com->push_back("SWAP c");
com->push_back("SUB c");
com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("SWAP d");
com->push_back("JZERO 52");
com->push_back("JPOS 4");
com->push_back("DEC e");
com->push_back("SWAP d");
com->push_back("SUB d");
com->push_back("SWAP d");

com->push_back("RESET a");
com->push_back("RESET h");
com->push_back("RESET g");
com->push_back("RESET f");
com->push_back("INC h");
com->push_back("DEC g");

com->push_back("RESET a");
com->push_back("ADD d");
com->push_back("SWAP b");

com->push_back("RESET a");

com->push_back("SUB c");
com->push_back("ADD b");

com->push_back("JPOS 5");
com->push_back("SWAP b");
com->push_back("SHIFT h");
com->push_back("SWAP b");
com->push_back("JUMP -7");
com->push_back("SWAP b");
com->push_back("SHIFT g");
com->push_back("SWAP b");

com->push_back("RESET a");
com->push_back("ADD b");
com->push_back("SUB d");

com->push_back("JNEG 14");
com->push_back("SWAP f");
com->push_back("SHIFT h");
com->push_back("SWAP f");
com->push_back("RESET a");

com->push_back("ADD c");
com->push_back("SUB b");

com->push_back("JNEG 3");
com->push_back("SWAP c");
com->push_back("INC f");
com->push_back("SWAP b");
com->push_back("SHIFT g");
com->push_back("SWAP b");
com->push_back("JUMP -16");
com->push_back("SWAP e");
com->push_back("JZERO 8");
com->push_back("RESET a");
com->push_back("SUB f");
com->push_back("SWAP c");
com->push_back("JZERO 2");
com->push_back("DEC c");
com->push_back("SWAP c");
com->push_back("SWAP f");
com->push_back("SWAP f");
com->push_back("SWAP "+r);

 
    return com;
}

list<string>* TIMESc(value *a,value *b,int noLine,string r){
    list<string>* com = new list<string>;
    if(!a->type.compare("VAL")){
         com->splice(com->end(),*genNum(a->ifValValue,"e"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(a,"e",noLine));
        
    }
    if(!b->type.compare("VAL")){
         com->splice(com->end(),*genNum(b->ifValValue,"f"));
    }else{  
         com->splice(com->end(),*loadValueFromMemory(b,"f",noLine));
    }
com->push_back("SWAP f");
com->push_back("SWAP c");
com->push_back("SWAP e");
com->push_back("SWAP d");
com->push_back("RESET a");
com->push_back("RESET b");
com->push_back("RESET e");
com->push_back("RESET f");
com->push_back("SWAP c");
com->push_back("JZERO 46");
com->push_back("JPOS 4");
com->push_back("INC e");
com->push_back("SWAP c");
com->push_back("SUB c");
com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("SWAP d");
com->push_back("JZERO 38");
com->push_back("JPOS 4");
com->push_back("DEC e");
com->push_back("SWAP d");
com->push_back("SUB d");
com->push_back("SWAP d");
com->push_back("RESET a");
com->push_back("ADD c");
com->push_back("SUB d");
com->push_back("JNEG 4");
com->push_back("SWAP c");
com->push_back("SWAP d");
com->push_back("SWAP c");
com->push_back("RESET a");
com->push_back("RESET h");
com->push_back("RESET g");
com->push_back("RESET f");
com->push_back("INC h");
com->push_back("DEC g");
com->push_back("RESET b");
com->push_back("ADD d");
com->push_back("SHIFT g");
com->push_back("SHIFT h");
com->push_back("SUB d");
com->push_back("JZERO 4");
com->push_back("SWAP f");
com->push_back("ADD c");
com->push_back("SWAP f");
com->push_back("RESET a");
com->push_back("SWAP c");
com->push_back("SHIFT h");
com->push_back("SWAP c");
com->push_back("SWAP d");
com->push_back("SHIFT g");
com->push_back("JZERO 3");
com->push_back("SWAP d");
com->push_back("JUMP -17");
com->push_back("SWAP d");
com->push_back("SWAP e");
com->push_back("JZERO 4");
com->push_back("RESET a");
com->push_back("SUB f ");
com->push_back("SWAP f");
if(r.compare("f")){
    com->push_back("SWAP f");
    com->push_back("SWAP "+r);
}
    return com;
}