/* Date: 25th August,2023
Name: Keerthi Vasukhi Kamaraju
Roll no.: EE23B034

To generate a random sequence of bits and find the hamming distance between two random bit files*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
int hammingdist(char[20], char[20]);
int genran(int n);
int main(int argc, char **argv)
{
        time_t t;
        int c;
    int n,s;
   
   
    //The below while loop takes the arguments from
   while((c = getopt(argc, argv, "n:s:th:" )) !=-1) {
       switch(c) {
           case 'n' :
           n = atoi (optarg);
           break;
           case 's' :
           s = atoi (optarg);
           srand((unsigned) s);
           break;
           case 't' :
           srand((unsigned) time(&t));
           break;
           case 'h':
           hammingdist(optarg, argv[optind]);
           
       }
   }
   genran(n);
   return(0);
}

//Below is a function used to calculate the hamming distance
//Also the array shown in the line below refers to the name of the file
   int hammingdist(char f1[20], char f2[20]) {
       FILE *file1 = fopen(f1, "r");
       FILE *file2 = fopen(f2, "r");
       
       fseek(file1, 0, SEEK_END);
       fseek(file2, 0, SEEK_END);
       
       int size1 = ftell(file1);
       int size2 = ftell(file2);
       
       fseek(file1, 0, SEEK_SET);
       fseek(file2, 0, SEEK_SET);
       
       int len = size1<size2 ? size1 : size2;
       int hamdist = 0;
       
       for (int i=0;i<len;i++) {
           char bit1, bit2;
fread(&bit1, sizeof(char), 1, file1);
           fread(&bit2, sizeof(char), 1, file2);
           if ((bit1 == '0'&& bit2 == '1' )||(bit1 == '1'&& bit2 == '0')) {
               
               hamdist++;
           }
            
           
           
       }
       printf("Hamming distance is %d\n",hamdist);
       fclose(file1);
       fclose(file2);
       
   }
//Below is the function used to make a file with random bits
int genran(int n) {
        if(n>0){
                FILE * fp = fopen("randbits.txt" , "w");
                for(int i=0;i<n;i++){
                fprintf(fp,"%d",rand()%2);
                }
     }
}