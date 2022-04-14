#include "Conditions.hpp"
using namespace std;
cond *genCondEQ(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="EQ";
    return newy;
}
cond *genCondNEQ(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="NEQ";
return newy;
}
cond *genCondLE(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="LE";
return newy;
}
cond *genCondGE(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="GE";
return newy;
}
cond *genCondLEQ(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="LEQ";
return newy;
}
cond *genCondGEQ(value *a,value *b){
 cond* newy = new cond;
 newy->a = a;
 newy->b = b;
newy->rel="GEQ";
return newy;
}
list<string>* FORDc(value *i,value *a,value *b,long long int noLine,list<string>* commandsFor){ 
    list<string> *gen = new list<string>;
    list<string> *com = new list<string>;
    string endName = i->ifVarName+"1";
    gen->splice(gen->end(),*generateValueOfValueToReg(a,noLine,"e"));
    gen->splice(gen->end(),*generateAdressToReg(i,noLine,"d"));
    gen->push_back("SWAP e");
    gen->push_back("INC a");
    gen->push_back("STORE d");
    gen->splice(gen->end(),*generateValueOfValueToReg(b,noLine,"e"));
    gen->splice(gen->end(),*generateAdressToReg(genVAR(endName,noLine),noLine,"d"));
    gen->push_back("SWAP e");
    gen->push_back("STORE d");
    com->splice(com->end(),*generateAdressToReg(i,noLine,"e"));
    com->push_back("LOAD e");
    com->push_back("DEC a");
    com->push_back("STORE e");
    com->push_back("SWAP e");
    com->splice(com->end(),*generateValueOfValueToReg(genVAR(endName,noLine),noLine,"f"));
    com->push_back("SWAP e");
    com->push_back("SUB f");
    com->push_back("JNEG "+to_string(commandsFor->size()+2));
    commandsFor->push_back("JUMP -"+to_string(commandsFor->size()+com->size()));
    gen->splice(gen->end(),*com);
    gen->splice(gen->end(),*commandsFor);
    return gen;




}
list<string>* FORTc(value *i,value *a,value *b,long long int noLine,list<string>* commandsFor){


    list<string> *gen = new list<string>;
    list<string> *com = new list<string>;
    string endName = i->ifVarName+"1";
    gen->splice(gen->end(),*generateValueOfValueToReg(a,noLine,"e"));
    gen->splice(gen->end(),*generateAdressToReg(i,noLine,"d"));
    gen->push_back("SWAP e");
    gen->push_back("DEC a");
    gen->push_back("STORE d");
    gen->splice(gen->end(),*generateValueOfValueToReg(b,noLine,"e"));
    gen->splice(gen->end(),*generateAdressToReg(genVAR(endName,noLine),noLine,"d"));
    gen->push_back("SWAP e");
    gen->push_back("STORE d");
    com->splice(com->end(),*generateAdressToReg(i,noLine,"e"));
    com->push_back("LOAD e");
    com->push_back("INC a");
    com->push_back("STORE e");
    com->push_back("SWAP e");
    com->splice(com->end(),*generateValueOfValueToReg(genVAR(endName,noLine),noLine,"f"));
    com->push_back("SWAP e");
    com->push_back("SUB f");
    com->push_back("JPOS "+to_string(commandsFor->size()+2));
    commandsFor->push_back("JUMP -"+to_string(commandsFor->size()+com->size()));
    gen->splice(gen->end(),*com);
    gen->splice(gen->end(),*commandsFor);
    return gen;




}
list<string>* REPEATc(cond *a,list<string>* commandsWhile,long long int noLine){
     list<string> *com = new list<string>;
    if(!a->rel.compare("EQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
    }
    else if(!a->rel.compare("NEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JPOS 3");
        com->push_back("JNEG 2");
     
        com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
    }
    else if(!a->rel.compare("LE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
          com->push_back("JZERO 2");
        com->push_back("JNEG 2");
       com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
    }
    else if(!a->rel.compare("GE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JPOS 2");
        com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
    }
    else if(!a->rel.compare("LEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JNEG 2");
        com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
    }
    else if(!a->rel.compare("GEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JPOS 2");
       com->push_back("JUMP -"+to_string(com->size()+commandsWhile->size()));
        }
    list<string>* com2 =new list<string>;
    com2->splice(com2->end(),*commandsWhile);
    com2->splice(com2->end(),*com);
    return com2;
}
list<string>* WHILEc(cond *a,list<string>* commandsWhile,long long int noLine){
        list<string> *com = new list<string>;
    if(!a->rel.compare("EQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");

        com->push_back("JPOS "+to_string(commandsWhile->size()+3));
        com->push_back("JNEG "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
    }
    else if(!a->rel.compare("NEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
    }
    else if(!a->rel.compare("LE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JPOS "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
    }
    else if(!a->rel.compare("GE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO "+to_string(commandsWhile->size()+3));
        com->push_back("JNEG "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
    }
    else if(!a->rel.compare("LEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JPOS "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
    }
    else if(!a->rel.compare("GEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JNEG "+to_string(commandsWhile->size()+2));
        commandsWhile->push_back("JUMP -"+to_string(commandsWhile->size()+com->size()));
        }   
     com->splice(com->end(),*commandsWhile);
    return com;
}
list<string>* IFELSEc(cond *a,list<string>* commandsIf,list<string>* commandsElse,long long int noLine){
    list<string> *com = new list<string>;
    if(!a->rel.compare("EQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JPOS "+to_string(commandsIf->size()+2));
        com->push_back("JNEG "+to_string(commandsIf->size()+1));
  
        
        
    }
    else if(!a->rel.compare("NEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JZERO "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("LE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JZERO "+to_string(commandsIf->size()+2));
        com->push_back("JPOS "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("GE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JZERO "+to_string(commandsIf->size()+2));
        com->push_back("JNEG "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("LEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JZERO 2");
        com->push_back("JPOS "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("GEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        commandsIf->push_back("JUMP "+to_string(commandsElse->size()+1));
        com->push_back("JZERO 2");
        com->push_back("JNEG "+to_string(commandsIf->size()+1));}
     com->splice(com->end(),*commandsIf);
     com->splice(com->end(),*commandsElse);
    return com;
}
list<string>* IFc(cond *a,list<string>* commandsIf,long long int noLine){
    list<string> *com = new list<string>;
    if(!a->rel.compare("EQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");

        com->push_back("JPOS "+to_string(commandsIf->size()+2));
        com->push_back("JNEG "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("NEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("LE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO "+to_string(commandsIf->size()+2));
        com->push_back("JPOS "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("GE")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO "+to_string(commandsIf->size()+2));
        com->push_back("JNEG "+to_string(commandsIf->size()+1));
    }
    else if(!a->rel.compare("LEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JPOS "+to_string(commandsIf->size()+2));
    }
    else if(!a->rel.compare("GEQ")){
         com->splice(com->end(),*generateValueOfValueToReg(a->a,noLine,"e"));
         com->splice(com->end(),*generateValueOfValueToReg(a->b,noLine,"f"));
        com->push_back("SWAP e");
        com->push_back("SUB f");
        com->push_back("JZERO 2");
        com->push_back("JNEG "+to_string(commandsIf->size()+2));}
     com->splice(com->end(),*commandsIf);
    return com;
}