#include <stdio.h>
#include <stdlib.h>
typedef void* RTN_Handle;
extern RTN_Handle RTN_CreateRational(int MyNum, int MyDeNum, int MyIntNum);
extern void RTN_DestroyRational(RTN_Handle rat);

extern void RTN_SetInt(RTN_Handle a, int x);
extern int RTN_GetInt(RTN_Handle a);
extern void RTN_SetFract(RTN_Handle a, int y, int z);
extern int RTN_GetFract(RTN_Handle a);

extern void RTN_AddRational(RTN_Handle a, RTN_Handle b, RTN_Handle res);
extern void RTN_SubRational(RTN_Handle a, RTN_Handle b, RTN_Handle res);
extern void RTN_DivRational(RTN_Handle a, RTN_Handle b, RTN_Handle res);
extern void RTN_MultRational(RTN_Handle a, RTN_Handle b, RTN_Handle res);

extern int GCD(RTN_Handle a, RTN_Handle b);
extern int LCM(RTN_Handle a, RTN_Handle b);



