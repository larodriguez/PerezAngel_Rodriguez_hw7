/*LINA PEREZ - ALEJANDRO RODRIGUEZ*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define gamma 1.4
#define n_points 1000.0
float etotal (float p, float rho, float u);

int main (int argc, char **argv){

  FILE *data;
  float t;
  float* U;
  float* F;
  float rho_l = 1.0; // Kg/m3 densidad inicial del lado izquierdo
  float rho_d = 0.125; // Kg/m3 densidad inicial del lado derecho
  float p_l = 100000.0; //N/m2 presion inicial del lado izquierdo
  float p_d = 10000.0; //N/m2 presion inicial del lado derecho
  float v_o = 0.0; // m/s2 velocidad inicial en ambos lados
  float* u1;
  float* u2;
  float* u3;
  float* f1;
  float* f2;
  float* f3;
  float* u1_presente;
  float* u2_presente;
  float* u3_presente;
  float* f1_presente;
  float* f2_presente;
  float* f3_presente;
  float* u1_futuro;
  float* u2_futuro;
  float* u3_futuro;
  int i;
  int j;
  float delta_x = 20.0/n_points; 
  float delta_t = delta_x;


  //Se debe entrar un solo valor por parametro
  if(argc!=2){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  } 
  
  t  = atof(argv[1]);

  // creando la memoria de los punteros
  U = malloc(3*sizeof(float));
  F = malloc(3*sizeof(float));
  u1 = malloc((20.0/delta_x)*sizeof(float));
  u2 = malloc((20.0/delta_x)*sizeof(float));
  u3 = malloc((20.0/delta_x)*sizeof(float));
  f1 = malloc((20.0/delta_x)*sizeof(float));
  f2 = malloc((20.0/delta_x)*sizeof(float));
  f3 = malloc((20.0/delta_x)*sizeof(float));
  u1_presente = malloc((20.0/delta_x)*sizeof(float));
  u2_presente = malloc((20.0/delta_x)*sizeof(float));
  u3_presente = malloc((20.0/delta_x)*sizeof(float));
  f1_presente = malloc((20.0/delta_x)*sizeof(float));
  f2_presente = malloc((20.0/delta_x)*sizeof(float));
  f3_presente = malloc((20.0/delta_x)*sizeof(float));
  u1_futuro = malloc((20.0/delta_x)*sizeof(float)); 
  u2_futuro = malloc((20.0/delta_x)*sizeof(float));
  u3_futuro = malloc((20.0/delta_x)*sizeof(float));

  //para generar el archivo 
  char n[150];
  sprintf(n,"estado_%f.dat",t);
  data = fopen(n, "w"); 
  
  //asignar las condiciones iniciales en el tubo
  for (i=0; i<=n_points; i++){
     if(i<=n_points*0.5){
       u1[i]= rho_l;
       u2[i]= rho_l*v_o;
       u3[i]=rho_l*etotal(p_l, rho_l, v_o);
       f1[i]=rho_l*v_o;
       f2[i]=(rho_l*(pow(v_o,2))) + p_l;
       f3[i]=((rho_l*etotal(p_l, rho_l, v_o))+p_l)*v_o;
    }
    else{
       u1[i]= rho_d;
       u2[i]= rho_d*v_o;
       u3[i]=rho_d*etotal(p_d, rho_d, v_o);
       f1[i]=rho_d*v_o;
       f2[i]=(rho_d*(pow(v_o,2))) + p_d;
       f3[i]=((rho_d*etotal(p_d, rho_d, v_o))+p_d)*v_o;
    } 
  }

  
  for (i=0; i<=t; i+(delta_t)){
    for (j=2; j<=(n_points-2); j++){
      u1_presente[j+1] = ((1/2)*(u1[j+2] + u1[j]) - ((delta_t/(2*delta_x))*(f1[j+2] - f1[j])));
      u2_presente[j+1] = ((1/2)*(u2[j+2] + u2[j]) - ((delta_t/(2*delta_x))*(f2[j+2] - f2[j])));
      u3_presente[j+1] = ((1/2)*(u3[j+2] + u3[j]) - ((delta_t/(2*delta_x))*(f3[j+2] - f3[j])));

      f1_presente[j+1] = u2_presente[j+1];
      f2_presente[j+1] = (((pow(u2_presente[j+1],2))/u1_presente[j+1]) + ((gamma-1)*(u3_presente[j+1] - ((1/2)*((pow(u2_presente[j+1],2))/u1_presente[j+1])))));
      f3_presente[j+1] = ((u3_presente[j+1] + ((gamma-1)*(u3_presente[j+1] - ((1/2)*((pow(u2_presente[j+1],2))/u1_presente[j+1])))))*(u2_presente[j+1]/u1_presente[j+1]));


      u1_presente[j-1] = ((1/2)*(u1[j-2] + u1[j]) - ((delta_t/(2*delta_x))*(f1[j-2] - f1[j])));
      u2_presente[j-1] = ((1/2)*(u2[j-2] + u2[j]) - ((delta_t/(2*delta_x))*(f2[j-2] - f2[j])));
      u3_presente[j-1] = ((1/2)*(u3[j-2] + u3[j]) - ((delta_t/(2*delta_x))*(f3[j-2] - f3[j])));

      f1_presente[j-1] = u2_presente[j-1];
      f2_presente[j-1] = (((pow(u2_presente[j-1],2))/u1_presente[j-1]) + ((gamma-1)*(u3_presente[j-1] - ((1/2)*((pow(u2_presente[j-1],2))/u1_presente[j-1])))));
      f3_presente[j-1] = ((u3_presente[j-1] + ((gamma-1)*(u3_presente[j-1] - ((1/2)*((pow(u2_presente[j-1],2))/u1_presente[j-1])))))*(u2_presente[j-1]/u1_presente[j-1]));


      u1_futuro[j] = (u1[j] - ((delta_t/delta_x)*(f1_presente[j+1] - f1_presente[j-1])));
      u2_futuro[j] = (u2[j] - ((delta_t/delta_x)*(f2_presente[j+1] - f2_presente[j-1])));
      u3_futuro[j] = (u2[j] - ((delta_t/delta_x)*(f3_presente[j+1] - f3_presente[j-1])));
    } 
    for(j=0; j<=n_points; j++){
      u1[j] =  u1_futuro[j];
      u2[j] =  u2_futuro[j];
      u3[j] =  u3_futuro[j];
    }
  }

  for(i=0; i<=n_points; j++){
    fprintf(data, " %d %f %f \n", i, (u2_futuro[i]/u1_futuro[i]) ,u1_futuro[i]); // FALTA LA PRESION
  }
  
  


  fclose(data);
  return 0; 

}

float etotal (float p, float rho, float u){
  float e;
  float etotal;
  e = p/((gamma-1)*rho);
  etotal = e + ((1/2)*pow(u,2));

  return etotal; 
}
