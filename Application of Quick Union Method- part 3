#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void conn(long long p, long long q);
long long root(long long i);
long long isconn(long long p, long long q);
//Declaring the global variables used in the program..
long long *id = NULL;
//id is used to measure the size
long long *iz = NULL;

int main(int argc, char *argv[]) {
    clock_t start, end;
    start = clock();
    long long n, m;
    long long p, q;
    char in[20];
    strcpy(in, argv[1]);
    //Opening the file 
    FILE *fi = fopen(in, "r");
    FILE *fo = fopen("EE23B034_quiz2_q4_output.txt", "w");
    if (fi == NULL || fo == NULL) {
        perror("Error opening files");
        exit(1);
    }
    fscanf(fi, "%lld %lld", &n, &m);
    //Initialising the two arrays, id for planets and iz for the size
    iz = (long long *)(malloc(n * sizeof(long long)));
    id = (long long *)(malloc(n * sizeof(long long)));
    for (long long i = 0; i < n; i++) {
        iz[i] = i;
        id[i] = i;
    }
    //doing the necassary operation for each input: Connecting if they are not connected and printing in the output file about their status of connection..
    for (long long j = 0; j < m; j++) {
        fscanf(fi, "%lld %lld", &p, &q);
        fprintf(fo, "%lld", isconn(p, q));
        if (isconn(p, q)) {
            conn(p, q);
        }
    }
    end = clock();
    int execution_time = ((float)(end - start) / CLOCKS_PER_SEC * 1000);
    fprintf(fo, "\n%d ms\n", execution_time);
    //Closing the files
    fclose(fi);
    fclose(fo);
    //Freeing the dynamically allocated memory
    free(iz);
    free(id);
    return 0;
}

long long root(long long i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
//Checking if the two planets are connected
long long isconn(long long p, long long q) {
    if (root(p) == root(q)) {
        return 0;
    } else {
        return 1;
    }
}
//Connecting the two planets 
void conn(long long p, long long q) {
    long long i = root(p);
    long long j = root(q);
    if (iz[i] < iz[j]) {
        id[i] = j;
        iz[j] += iz[i];
    } else {
        id[j] = i;
        iz[i] += iz[j];
    }
}
