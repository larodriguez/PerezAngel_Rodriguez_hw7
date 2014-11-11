import sys
import matplotlib.pyplot as plt
import numpy as np


#recogemos el nombre del archivo.dat que entra como parametro
data= sys.argv[1]

#cargar datos del archivo
datos = np.loadtxt(data)

#definir arreglos para graficar
x = datos[:,0]
v = datos[:,1]
p = datos[:,2]
d = datos[:,3]

      
   
  
        
#saber cuales fueron las condiciones iniciales
l=list(data)
n=len(l)
l[n-4:n]=[]
nombre_datos="".join(l)


#Graficar

a1 = plt.subplot(3,1,1)
plt.plot(x,v)
plt.xlabel('Distancia')
plt.ylabel('Velocidad')

plt.subplot(3,1,2, sharex=a1)
plt.plot(x,p)
plt.xlabel('Distancia')
plt.ylabel('Presion')

plt.subplot(3,1,3, sharex=a1)
plt.plot(x,d)
plt.xlabel('Distancia')
plt.ylabel('Densidad')

plt.savefig(str(nombre_datos)+'.pdf')
