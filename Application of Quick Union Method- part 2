/* Connecting realms using weighted quick union
Name: Keerthi Vasukhi Kamaraju
Roll no. : EE23B034

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//Creating a structure for planet
struct Planet {
  int planet_no;
  int weight;
  struct Planet *parent;
};
//Finding the root
int find_root(struct Planet *A, int i)
{
 	if(A[i].planet_no != i){
 		A[i].planet_no = find_root(A, A[i].planet_no);
 		}
	return A[i].planet_no; 		
}

//Building a road between the two realms
void setunion(struct Planet *parent, int x, int y){
	int rx = find_root(parent, x);
	int ry = find_root(parent, y);
    //Using weighted union
	if(rx!=ry){
		if(parent[rx].weight<parent[ry].weight){
			parent[rx].planet_no = ry;
			}
		else if(parent[ry].weight<parent[rx].weight){
		        parent[ry].planet_no = rx;
		        }
		else{
		         parent[ry].planet_no = rx;
		         parent[rx].weight++;
		         }
		         }
		         }          
int main(int argc, char **argv) {
  clock_t start, end;
  start = clock();
  double time;
  int int_time;

  int N, M;
  FILE *fp, *fp_out;
  fp = fopen(argv[1], "r");
  fp_out = fopen("EE23B034_quiz2_q3.txt", "w");
  //taking input
  fscanf(fp, "%d %d", &N, &M);

  struct Planet *A = (struct Planet *)malloc(N*sizeof(struct Planet));
  int p, q;
  int rp, rq;
  int wp, wq;
  //Initialising each realm
  for (int i = 0; i < N; i++) {
    A[i].planet_no = i;
    A[i].weight = 0;
  }
  int *result = (int*)malloc(M*sizeof(int));
  for(int i=0; i<M; i++)
    {
      fscanf(fp,"%d %d", &p, &q);
      if (find_root(A, p) != find_root(A, q))
      {
        result[i] = 1;
        setunion(A, p, q);
        }
      else{
        result[i] = 0; 
    }
    fprintf(fp_out, "%d", result[i]);
    }
  fprintf(fp_out, "\n");
  fclose(fp);
    
  end = clock();
  time = ((double)(end - start)) / CLOCKS_PER_SEC;
  int_time = ceil(time*1000);
  fprintf(fp_out, "%d ms\n", int_time);
  fclose(fp_out);
  free(A);
  return 0;
}



