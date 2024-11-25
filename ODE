/*
Name:  Keerthi Vasukhi Kamaraju , Priyanka Umasankar
Roll Number: EE23B034, EE23B060
Description: 

    Solves the Landau-Lifshitz-Gilbert Equation using Euler, Heun and RK45 Methods
    Assuming RK45 is the most accurate, we calculate the R^2 error for Euler and Heun methods

    Inputs: theta_start theta_stop alpha delta_t
    Output: alpha delta_t R^2_Euler R^2 Heun
    Plot data in EE23B034_trajectory.jpg
    Plot data alpha vs Tau in EE23B034S_tau_vs_alpha.jpg

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI_M 3.141
    
//Function to solve the differential equations using various methods: Heun's, Euler's and RK45
double Heun_method(double alpha, double delta_t, double theta_t, double* phi_t, double gamma, double H, double t, FILE*Euler);
double Euler_method(double alpha, double delta_t, double theta_t, double* phi_t, double gamma, double H, double t, FILE*Heun);
double rk45(double alpha, double theta_t, double* phi_t, double gamma, double H, double t, FILE * rk45);

//Derivatives of theta and phi
double delta_theta(double t, double theta, double alpha, double gamma, double H);
double delta_phi(double t, double theta_t, double alpha, double gamma, double H);


int main(int argc, char** argv) {
    // Parsing command line arguments
    double theta_start = atof(argv[1]);
    double theta_stop = atof(argv[2]);
    double alpha = atof(argv[3]);
    double delta_t = atof(argv[4]);
    double delta_trk = 0.001;
    double theta_t = theta_start;
    double phi_t = 0;
    double t,tau = 0; 
    double H = 2e-11;
    double gamma = 17.6e10;
    double alpha_test;

    //Opening files to store trajectories for various methods used to solve the differential equations
    FILE* Euler = fopen("Euler.txt", "w");
    FILE* Heun = fopen("Heun.txt", "w");
    FILE* rk45p = fopen("rk45p.txt", "w");
    FILE* output = fopen("output.txt", "w");
    FILE* buffer = fopen("buffer.txt", "w");
    FILE* rk45e = fopen("rk45e.txt", "w");
    FILE* rk45h = fopen("rk45h.txt", "w");

    //For finding equidistant alpha values starting from 0 to 0.2 and getting the tau values from the Rk45 solver
    for (int i = 1; i <= 100; i++){
      alpha_test = i*(0.2)/100;
      theta_t = theta_start;
      phi_t=0;
      tau = 0;
      t = 0;
      while (theta_t <= theta_stop) {
        theta_t = rk45(alpha_test,  theta_t,  &phi_t,  gamma,  H,  t,buffer);
        tau += delta_trk;
      } 
      fprintf(output, "%f %f\n", alpha_test, tau);
    }
    // Re-initializing values for theta_t, phi_t and t
    theta_t = theta_start;
    phi_t=0;
    t = 0;
    
    

    //While loops to check for theta_t<=theta_stop and use the three methods
    while (theta_t <= theta_stop) {
        theta_t = Euler_method(alpha, delta_t, theta_t, &phi_t, gamma, H, t, Euler);
        t += delta_t;//Updating time with delta_t

    }
    
    // Re-initializing values for theta_t, phi_t and t
    theta_t = theta_start;
    phi_t=0;
    t = 0;
    

    while (theta_t <= theta_stop) {
        theta_t = Heun_method(alpha, delta_t, theta_t, &phi_t, gamma, H, t, Heun);
        t += delta_t;//Updating time with delta_t
    }

    // Re-initializing values for theta_t, phi_t and t
    theta_t=theta_start;
    phi_t=0;
    t=0;

    while (theta_t <= theta_stop) {
        theta_t =rk45( alpha,  theta_t,  &phi_t,  gamma,  H,  t,rk45p);
        t += delta_trk;//Updating time with delta_t
    }
    //closing the files that I stored the values into
    fclose(Euler);
    fclose(Heun);
    fclose(rk45p);
    fclose(output);
    t=0;
    // Initializing variables to calculate R^2
    float sum_r,sum_m;
    char c1,c2,c3;
    int countE=0;
    int countH=0;
    int countR=0;
    double R2E;
    double R2H;
    double sum_rE = 0.0, sum_rH=0.0;
    double sum_mE = 0.0, sum_mH=0.0;
    double yE,yM=0.0;
    double yR;
    double yH;
    double g,g1,g2,g3,g4,g5,g6,g7,h,r1,r2,r3,eps;
    double countER,countHR;
    double tn=0, tin=0;
    Euler=fopen("Euler.txt", "r");
    Heun=fopen("Heun.txt", "r");
    rk45p=fopen("rk45p.txt", "r");

    // Find minimum number of datapoints
    for (c1 = getc(Euler); c1 !=EOF ; c1 = getc(Euler))
        if (c1=='\n')
            countE = countE + 1;
    for (c2 = getc(Heun); c2 !=EOF ; c2 = getc(Heun))
        if (c2=='\n')
            countH = countH + 1;
    for (c3 = getc(rk45p); c3!=EOF ; c3 = getc(rk45p))
        if (c3=='\n')
            countR = countR + 1;

    rewind(Euler);
    rewind(Heun);
    rewind(rk45p);

    if(countE<countR){
      countER = countE;
    }
    else {
        countER = countR;
    }
    
    for (int e =0; e<countER;e++) {
      fscanf(Euler,"%lf %lf %lf",&tin,&r2,&r3);
      while(t<=tin) {
        fscanf(rk45p,"%lf %lf %lf",&t,&r2,&r3);
      }
      fprintf(rk45e,"%lf %lf %lf\n",tin,r2,r3);
    }
    rewind(rk45p);

    fclose(rk45e);
    rk45e = fopen("rk45e.txt", "r");

    // Calculate R^2 for Euler
    for (int j = 0;j<countER; j++) {
      fscanf(rk45e,"%lf %lf %lf\n",&r1,&yR,&r3);
      yM += yR;

    }
    yM=yM/countER;
    rewind(rk45e);
    rewind(Euler);
    for(int i=0; i<countER; i++){
      fscanf(Euler,"%lf %lf %lf\n",&g1,&yE,&g2);
      fscanf(rk45e,"%*f %lf %*f\n",&yR);
      sum_rE += pow((yR-yE),2);
      sum_mE += pow((yR-yM),2);
    }
    if(sum_mE!=0){
        R2E=1-(sum_rE/sum_mE);
    }
    rewind(rk45p);


    if(countH<countR){
      countHR = countH;
    }
    else {
      countHR = countR; 
    }
    
    
    // Calculate R^2 for Heun
    tn =0;
    t=0;
    tin=0;
    
    for (int h =0; h<countHR;h++) {
      fscanf(Heun,"%lf %lf %lf",&tin,&r2,&r3);
      while(t<=tin) {
        fscanf(rk45p,"%lf %lf %lf",&t,&r2,&r3);

      }
      fprintf(rk45h,"%lf %lf %lf\n",tin,r2,r3);
    }

    fclose(rk45h);
    rk45h = fopen("rk45h.txt", "r");

    for (int j = 0;j<countHR; j++) {
    fscanf(rk45h,"%lf %lf %lf\n",&g4,&yR, &h);
      yM+=yR;
    }
    yM=yM/countHR;
    rewind(rk45h);
    rewind(Heun);
    for(int i=0; i<countHR; i++){
      fscanf(Heun,"%lf %lf %lf\n",&g5,&yH,&g6);
      fscanf(rk45h,"%lf %lf %lf\n",&g7,&yR,&h);

      sum_rH += pow((yR-yH),2);
      sum_mH += pow((yR-yM),2);
    }
    if(sum_mH!=0){
        R2H=1-(sum_rH/sum_mH);
    }

    // Output calculated values of R^2
    printf("%f %f %f %f\n",alpha, delta_t, R2E, R2H);
    return 0;
}
//Function to solve using Euler's method
double Euler_method(double alpha, double delta_t, double theta_t, double* phi_t, double gamma, double H, double t, FILE * Euler) {
    double dtheta_dt = gamma * alpha * (H * sin(theta_t)) / (1 + alpha * alpha);
    double dphi_dt = (dtheta_dt) / (alpha * sin(theta_t));

    theta_t = theta_t + dtheta_dt * delta_t;
    *phi_t = *phi_t + dphi_dt * delta_t;
    fprintf(Euler,"%f %f %f\n",t,theta_t,*phi_t);
    return theta_t;
}
//function to solve using Heun's method
double Heun_method(double alpha, double delta_t, double theta_t, double* phi_t, double gamma, double H, double t,FILE * Heun) {
    double dtheta_dt = gamma * alpha * (H * sin(theta_t)) / (1 + alpha * alpha);
    double dphi_dt = (dtheta_dt) / (alpha * sin(theta_t));

    double theta_t_FS = theta_t + dtheta_dt * delta_t;
    double phi_t_FS = *phi_t + dphi_dt * delta_t;

    double dtheta_dt_FS = gamma * alpha * (H * sin(theta_t_FS)) / (1 + alpha * alpha);
    double dphi_dt_FS = (dtheta_dt_FS) / (alpha * sin(theta_t_FS));

    theta_t = theta_t + (dtheta_dt_FS + dtheta_dt) * delta_t / 2;
    *phi_t = *phi_t + (dphi_dt_FS + dphi_dt) * delta_t / 2;
    fprintf(Heun,"%f %f %f\n",t,theta_t,*phi_t);
    return theta_t;
}
// Function to solve using rk45
double rk45(double alpha,double theta_t, double* phi_t, double gamma, double H, double t,FILE * rk45p)
{
  double delta_t = 0.001;
  double dtheta_dt = gamma * alpha * (H * sin(theta_t)) / (1 + alpha * alpha);
  double c20 = 0.25, c21 = 0.25;
  double c30 = 0.375, c31 = 0.09375, c32 = 0.28125;
  double c40,c41, c42,c43;
  double c51, c52 = -8.0, c53, c54;
  double c60 = 0.5, c61, c62 = 2, c63, c64;
  double c65 = -0.275;
  double a1, a2 = 0, a3, a4, a5 = -0.2;
  double b1, b2 = 0, b3, b4, b5= -0.18, b6;
  double F1, F2, F3, F4, F5, F6, x4, x5;
  double F1phi, F2phi, F3phi, F4phi, F5phi, F6phi;

  c40 = (double) 12/ (double) 13;
  c41 = (double) 1932/(double) 2197;
  c42 = (double) -7200/(double) 2197;
  c43 = (double) 7296/(double) 2197;
  c51 = c53 = (double) 439/ (double) 216;
  c54 = (double) -845/(double) 4104;
  c61 = (double) -8/(double) 27;
  c63 = (double) -3544/(double) 2565;
  c64 = (double) 1859/(double) 4104;
  a1 = (double) 25/(double) 216;
  a3 = (double) 1408/(double) 2565;
  a4 = (double) 2197/(double) 4104;
  b1 = (double) 16/(double) 135;
  b3 = (double) 6656/(double) 12825;
  b4 = (double) 28561/(double) 56430;
  b6 = (double) 2/(double) 55;


  F1 = delta_t * delta_theta(t, theta_t,alpha,gamma,H);
  F2 = delta_t * delta_theta(t + c20 * delta_t, theta_t + c21 * F1,alpha,gamma,H);
  F3 = delta_t * delta_theta(t + c30 * delta_t, theta_t + c31 * F1 + c32 * F2,alpha,gamma,H);
  F4 = delta_t * delta_theta(t + c40 * delta_t, theta_t + c41 * F1 + c42 * F2 + c43 * F3,alpha,gamma,H);
  F5 = delta_t * delta_theta(t + delta_t, theta_t + c51 * F1 + c52 * F2 + c53 * F3 + c54 * F4 ,alpha,gamma,H);
  F6 = delta_t * delta_theta(t + c60 * delta_t, theta_t + c61 * F1 + c62 * F2 + c63 * F3 + c64 * F4 + c65 * F5,alpha,gamma,H);

  F1phi = delta_t * delta_phi(t, theta_t,alpha,gamma,H);
  F2phi = delta_t * delta_phi(t + c20 * delta_t, theta_t + c21 * F1phi,alpha,gamma,H);
  F3phi = delta_t * delta_phi(t + c30 * delta_t, theta_t + c31 * F1phi + c32 * F2phi,alpha,gamma,H);
  F4phi = delta_t * delta_phi(t + c40 * delta_t, theta_t + c41 * F1phi + c42 * F2phi + c43 * F3phi,alpha,gamma,H);
  F5phi = delta_t * delta_phi(t + delta_t, theta_t + c51 * F1phi + c52 * F2phi + c53 * F3phi + c54 * F4phi,alpha,gamma,H);
  F6phi = delta_t * delta_phi(t + c60 * delta_t, theta_t + c61 * F1phi + c62 * F2phi + c63 * F3phi + c64 * F4phi + c65 * F5phi,alpha,gamma,H);

  theta_t += b1 * F1 + b3 * F3 + b4 * F4 + b5 * F5 + b6 * F6;
  *phi_t += b1 * F1phi + b3 * F3phi + b4 * F4phi + b5 * F5phi + b6 * F6phi;

  t += delta_t;

  fprintf(rk45p,"%f %f %f\n",t, theta_t,*phi_t);

  return theta_t;
}


double delta_theta(double t, double theta_t, double alpha, double gamma, double H) {
    double dtheta_dt = gamma * alpha * (H * sin(theta_t)) / (1 + alpha * alpha);
    return dtheta_dt;
}


double delta_phi(double t, double theta_t, double alpha, double gamma, double H) {
    double dphi_dt = gamma * (H) / (1 + alpha * alpha);
    return dphi_dt;
}







