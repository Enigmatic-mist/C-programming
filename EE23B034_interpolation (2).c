#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Roll No : EE23B034
Name : Keerthi Vasukhi Kamaraju
Desc :  Lagranges interpolation and Newton-Gaussian
interpolation {
    Using the lagrange function in the newtonian function to find the value of x0 give in the input
    Input : order_polynomial, xstart , xend ,x0
    Output : f(x0)
} */

//Lagrange interpolation function
double lagrange(int a, double *x, double *y, double xx) 
{
 double sum = 0;
 double product;
 for(int i=0; i<a ; i++)
  {
   product = y[i];
   for(int j=0; j<a ; j++)
     { 
      if(i != j)
      {
       product = product * (xx - x[j])/ (x[i] - x[j]);
      }
     }
    sum = sum + product ;
   }  
   return sum;
 } 
 
 //Newton-gaussian interpolation function
void newton(int a, double *x, double *y, double xi) 
{
    // 2 dimensional array initialized
   double** fdd = malloc(sizeof(double*) * a); 
    for (int i = 0; i < a; i++) 
    {
        fdd[i] = malloc(sizeof(double) * a);
    }
    //yint and ea are empty arrays taken to assign value
  double *yint = malloc(a* sizeof(double)); 
  double *ea = malloc(a* sizeof(double));
  
  // Lagrangian data is now our sample data for newton method
  for(int i=0; i<a; i++)
  { 
   fdd[i][0] = lagrange(a, x, y, x[i]) ; 
  }
  
  for(int j=1; j<a; j++)
   { 
    for(int i=0; i<a-j; i++)
    { 
     fdd[i][j] = (fdd[i+1][j-1] - fdd[i][j-1])/(x[i+j] - x[i]);
    }
   }
   
double xterm = 1.0;
double yint2;
 yint[0] = fdd[0][0] ;
 
 for(int order = 1; order <a; order++)
 { 
  xterm = xterm * (xi - x[order - 1]);
  yint2 = yint[order - 1] + fdd[0][order] * xterm ;
  ea[order - 1] = yint2 - yint[order - 1] ;
  yint[order] = yint2;
 }  
  printf("%lf\n", yint[a-1]);
  for(int i=0; i<a; i++)
  {
  free(fdd[i]);
  
  }
   free(yint);
  free(ea);
} 

 // input from command line arguments
 void main (int argc, char** argv) 
 { 
  int order = atoi(argv[1]);
  double x_start = atof(argv[2]);
  double x_end = atof(argv[3]);
  double x0 = atof(argv[4]);
  int n = order + 1;
  
  double *x = malloc(n* sizeof(double));
 double *y = malloc(n* sizeof(double));

  for(int i=0; i<n; i++)
  { 
   x[i] = x_start + (i * (x_end - x_start)/order); 
   //to generate equally spaced x values for sample data pionts 
   y[i] = 1/ (1+(25*x[i]*x[i])) ;
   //to get corresponding y values 
  } 
  
 lagrange(n, x, y, x0);
 newton(n, x, y, x0);
 //free memory
 
  
  free(x);
  free(y);
}  
   
 
