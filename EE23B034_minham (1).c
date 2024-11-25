#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Roll no. : EE23B034

int min_hamming_dist;
int location_of_min_hamming_dist;

int main(int argc, char **argv)
{
    int N, Nseed, M, Mseed;
    
    if ((M>N)||(M=N)) {
        printf("ERROR");
        exit(1);
    }
    
    
    
    N = atoi(argv[1]);
    Nseed = atoi(argv[2]);
    M = atoi(argv[3]);
    Mseed = atoi(argv[4]);
    int* ptr1 = malloc( M*sizeof(int));
    int* ptr2 = malloc( N*sizeof(int));
    int nbits[],mbits[];
    ptr1 = mbits;
    ptr2 = nbits;
    
    for (int i=0; i<M ; i++) {
        mbits[i] = srand((unsigned) Mseed)%2;
        }
        
        
    for (int j=0;j<N ; j++) {
        nbits[j] = srand((unsigned) Nseed)%2;
    }
    
    FILE *f1 = fopen("Mfile.dat", "w");
    for (int k=0; k<M; k++) {
        int a;
        mbits[k] = a;
        fprintf(Mfile.dat,"%d ",a);
        }
        FILE *f2 = fopen("Nfile.dat", "w");
    for (int l=0; l<N; l++) {
        int b;
        mbits[k] = b;
        fprintf(Nfile.dat,"%d ",b);
    }
    
    hammingdist(mbits,nbits, int M, int N);
    printf("%d ",hamdist);
         
    
    
   

    return 0;
}

//Calculating the hamming distance using pointers
int hammingdist(int* x, int* y, int M, int N) {
    int hammingdist;
    for (int j = 0; j<N ; j = j + N) {
    for (int i= 0; i< M; i++) {
        if ((*(x + i) == '0'&& *(y + i + j) == '1' )||(*(x + i) == '1'&& *(y + i + j) == '0')) {
               
               hamdist++;
           
        }
        
    }
    }
    
    min_hamming_dist = hamdist;
    
    
    
}

 