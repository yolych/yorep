#include <stdio.h>
#include <stdlib.h>
#include "Qlib.h"
#include <math.h.>

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
    RTN_Num* res = malloc(sizeof(RTN_Num));

   while (f->DeNum != s->DeNum) {
      if (f->DeNum > s->DeNum) f->DeNum -= s->DeNum;
      else s->DeNum -= f->DeNum;
   }
  return f->DeNum;
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

void RTN_GetFract(RTN_Handle a){
    RTN_Num* NewNum = a;
    double tmp,fract;
    tmp = (double)((double)NewNum->Num / (double)NewNum->DeNum);
    tmp = modf(tmp,&fract);
    printf("%0.3f", tmp);
}




int main(){
    RTN_Num* Num1 = RTN_CreateRational(2, 5, 4);
    RTN_Num* Num2 = RTN_CreateRational(4, 9, 5);
    RTN_Num* NumR = RTN_CreateRational(0, 0, 0);

    /*printf("First Q Number: %d \n", RTN_GetInt(Num1));
    printf("Second Q Number: %d \n", RTN_GetInt(Num2));*/
    printf("First Q integer part: %d\n", RTN_GetInt(Num1));
    printf("Second Q integer part: %d\n", RTN_GetInt(Num2));
    printf("First Q fraction part: "); RTN_GetFract(Num1);
    printf("\nSecond Q fraction part: "); RTN_GetFract(Num2);

    RTN_AddRational(Num1, Num2, NumR);
    printf("\nadd : %d", RTN_GetInt(NumR)); RTN_GetFract(NumR);

    RTN_SubRational(Num1, Num2, NumR);
    printf("\nsub : %d", RTN_GetInt(NumR));  RTN_GetFract(NumR);

    RTN_MultRational(Num1, Num2, NumR);
    printf("\nmult : %d", RTN_GetInt(NumR));  RTN_GetFract(NumR);

    RTN_DivRational(Num1, Num2, NumR);
    printf("\ndiv : %d", RTN_GetInt(NumR));  RTN_GetFract(NumR);



return 0;
}


