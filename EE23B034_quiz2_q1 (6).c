/* Restoring rainbow roads using Quick union method
Name: Keerthi Vasukhi Kamaraju
Roll No. : EE23B034
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Declaring the global variables to be used in the program
long long *id = NULL;
long long isconn(long long p,long long q);
void conn(long long p, long long q);
long long n,m;

int main(int argc, char *argv[]) {
  //Starting the clock to measure the time 
  clock_t start, end;
  start=clock();

    long long p,q;
    char in[20];
    strcpy(in,argv[1]);
    //Opening the input and output file
    FILE *fi = fopen(in , "r");
    FILE *fo = fopen("EE23B034_quiz2_q1_output.txt","w");
    fscanf(fi,"%d %d",&n,&m);
    id = (long long *)(malloc(n*sizeof(long long)));
    //Creating the array for id
    for (long long i=0;i<n;i++) {
    id[i] = i;
    }
    //Taking the input from the file for each file and check if they are connected
    for (long long j=0;j<m;j++) {
      fscanf(fi,"%d %d",&p,&q);
      fprintf(fo, "%d", isconn(p,q));
      if( isconn(p,q)) {
      conn(p,q);
      }
    
    }
    end=clock();
    int execution_time=((float)(end-start)/CLOCKS_PER_SEC*1000);
    //Printing the execution time
    fprintf(fo, "\n%d ms\n", execution_time);
   fclose(fi);
   fclose(fo);
   free(id);
}
//Checking if the planets p and q are connected..
long long isconn(long long p,long long q) {
  
    if (id[p] == id[q])
    return 0;
    else return 1;
    
}
//Connecting the two planets
void conn(long long p, long long q) {
  
  long long pid = id[p];
  long long qid = id[q];
  
       for (long long i=0 ; i<n ; i++) {
        //Changing the id of all the planets which should be connected
       if (id[i] == pid) {
                id[i] = qid;
                
        }
        
    }
}