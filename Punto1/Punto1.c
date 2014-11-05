/*LINA PEREZ - ALEJANDRO RODRIGUEZ*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define n_points 100

int main (int argc, char **argv){

  FILE *datos;
  float rho; //Kg/m
  float* x;
  float* u_initial;
  int i;
  float delta_x;
  float delta_t;
  float c;
  float T = 40.0; //N//
  float r; 
  float* u_future;
  float* u_past;
  float* u_present;
  float n_time = 120.0;
  int j; 
  int k; 
  int p; 
  
  //Definiendo el valor de la densidad que entra por parametro
  rho = atof(argv[1]);

  char n[150];
  sprintf(n,"string_%f.dat",rho);
  datos = fopen(n, "w"); 

  //Se debe entrar un solo valor por parametro
  if(argc!=2){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  } 

  x = malloc(n_points*sizeof(float));
  u_initial= malloc(n_points*sizeof(float));
  u_future= malloc(n_points*sizeof(float));
  u_past= malloc(n_points*sizeof(float));
  u_present= malloc(n_points*sizeof(float));

  for(i=0; i<=n_points; i++){
    x[i] = i;  
    u_future[i] = 0.0;
  }

  //Condición inicial - cuerda estirada de forma triangular
  for (i=0;i<=n_points;i++){   
    if(i<80){
      u_initial[i] = 0.0125*x[i];
    }
    if (i>=80){
      u_initial[i] = (-x[i]/20.0)+5.0;
    } 
  }
  
  //Definimos las iteraciones de x y t
  c = sqrt(T/rho); 

  delta_x = x[1] - x[0];
  delta_t = 0.0005;

  r = c * (delta_t / delta_x);
  printf("%f \n", r);

  //Condiciones de frontera
  u_initial[0] = 0.0;
  u_initial[n_points-1] = 0.0;
  u_future[0] = 0.0;
  u_future[n_points-1] = 0.0;

  
  //Primera iteración
  for (i=1; i<n_points; i++){
    u_future[i] = u_initial[i] + (((pow(r,2))/2.0) * (u_initial[i+1] - (2.0 * u_initial[i]) + u_initial[i-1]));
  }
  
  //Copiamos u_initial y u_future
  for(i=0; i<=n_points; i++){
    u_past[i] = u_initial[i];
    u_present[i] = u_future[i];
  }

  for(j=0; j<=n_points; j++){
    printf("%f %f %f \n", u_initial[j], u_past[j], u_present[j]);
  }
 

  
  //Segunda iteración
  for(j=0; j<=n_time; j++){
    for(i=1; i<n_points; i++){
      u_future[i] = ((2.0*(1.0-(pow(r,2))))*u_present[i]) - u_past[i] + (pow(r,2)*(u_present[i+1] +  u_present[i-1]));
    }
    for(k=0; k<=n_points; k++){
      u_past[k] = u_present[k];
      u_present[k] = u_future[k];
    }
    for(p=0; p<=n_points; p++){
      fprintf(datos, " %f", u_present[p]);
    }
    fprintf(datos, "\n");
  }
  
  fclose(datos);
  return 0; 
}
