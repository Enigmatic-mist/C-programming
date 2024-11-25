#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int fac(int x);
float mysin(int y, float z);
int main(int argc, char* argv[])
{
   int i = atoi(argv[1]);
   float j = atof(argv[2]);
   float s = sin(j);
    float ms = mysin(i,j);
   printf("%.3f,%.3f",ms,s-ms);

    return 0;
}
int fac(int x) {
    int y = 1;
    for(;x>0;x-=1) {
        y = y*x;
    }
 return y;
 
}
float mysin(int i, float z) {
    float ex=0;
    for (int ct=1;ct<=i;ct++) {
        ex = ex + (pow(-1,ct-1))* (pow(z,2*ct-1))/fac(2*ct - 1);
    }
    return ex;
}
