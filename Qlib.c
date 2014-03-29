#include <stdio.h>
#include <stdlib.h>
#include "Qlib.h"

typedef struct RTN_Num{
    int Num;
    int DeNum;
    int IntNum;} RTN_Num;

RTN_Handle RTN_CreateRational(int MyNum, int MyDeNum, int MyIntNum){
    RTN_Num* NewNum = malloc(sizeof(RTN_Num));     /*переменная-указатель на структуру;*/
    NewNum->Num = MyNum;    // *(NewNum).Num = MyNum */
    NewNum->DeNum = MyDeNum;
    NewNum->IntNum = MyIntNum;
    return (RTN_Num*)NewNum;
    }

void RTN_DestroyRational(RTN_Handle rat){
    RTN_Num* NewNum = rat;
    NewNum->DeNum = 0;
    NewNum->Num = 0;
    NewNum->IntNum = 0;
    free(NewNum);
    }

void RTN_AddRational(RTN_Handle a, RTN_Handle b, RTN_Handle res){
    RTN_Num* f = a;
    RTN_Num* s = b;
    RTN_Num* r = res;

    r->DeNum = LCM(a, b);
    r->IntNum = f->IntNum + s->IntNum;
    r->Num = r->DeNum / f->DeNum * f->Num + r->DeNum / s->DeNum * s->Num;
    if(r->Num >= r->DeNum){
        r->Num %= r->DeNum;
        r->IntNum += (r->Num / r->DeNum);
    }
}

void RTN_SubRational(RTN_Handle a, RTN_Handle b, RTN_Handle res){
    RTN_Num* f = a;
    RTN_Num* s = b;
    RTN_Num* r = res;

    r->DeNum = LCM(a, b);
    if(f->IntNum >= s->IntNum){
        r->IntNum = f->IntNum - s->IntNum;
        r->Num = r->IntNum * f->DeNum +
                r->DeNum / f->DeNum * f->Num -
                r->DeNum / s->DeNum * s->Num;
        r->Num %= r->DeNum;
        r->IntNum += (r->Num / r->DeNum);
    }
    else{
        r->IntNum = s->IntNum - f->IntNum;
        r->Num = r->IntNum * s->DeNum +
                r->DeNum / s->DeNum * s->Num -
                r->DeNum / f->DeNum * f->Num;
        r->Num %= r->DeNum;
        r->IntNum += (r->Num / r->DeNum);
        r->Num = - r->Num;
        r->IntNum = - r->IntNum;
    }
}

void RTN_DivRational(RTN_Handle a, RTN_Handle b, RTN_Handle res){
    RTN_Num* f = a;
    RTN_Num* s = b;
    RTN_Num* r = res;

    f->Num += f->IntNum * f->DeNum;
    s->Num += s->IntNum * s->DeNum;
    r->DeNum = f->DeNum * s->Num;
    r->Num = f->Num * s->DeNum;
    r->Num %= r->DeNum;
    r->IntNum = r->Num / r->DeNum;
}

void RTN_MultRational(RTN_Handle a, RTN_Handle b, RTN_Handle res){
    RTN_Num* f = a;
    RTN_Num* s = b;
    RTN_Num* r = res;

    r->DeNum = LCM(a, b);
    r->Num = f->Num * s->Num + f->IntNum * f->DeNum + s->IntNum * s->DeNum;
    r->Num %= r->DeNum;
    r->IntNum /= r->DeNum;
}



int GCD(RTN_Handle a, RTN_Handle b){  //NOD
    RTN_Num* f = a;
    RTN_Num* s = b;

    while((f->DeNum != 0) && (s->DeNum != 0)){
        if(f->DeNum > 0)
            f->DeNum %= s->DeNum;
        else s->DeNum %= f->DeNum;
    }
    return(f->DeNum + s->DeNum);
}

int LCM(RTN_Handle a, RTN_Handle b){  //NOK
    RTN_Num* f = a;
    RTN_Num* s = b;
    return((f->DeNum * GCD(a, b) * s->DeNum));
    }

void RTN_SetInt(RTN_Handle a, int x){
    RTN_Num* NewNum = a;
    NewNum->IntNum = x;
}

void RTN_SetFract(RTN_Handle a, int y, int z){
    RTN_Num* NewNum = a;
    NewNum->Num = y;
    NewNum->DeNum = z;
}

int RTN_GetInt(RTN_Handle a){
    RTN_Num* NewNum = a;
    return NewNum->IntNum;
}
