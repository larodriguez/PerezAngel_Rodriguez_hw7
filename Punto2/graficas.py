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
l=list(datos)
n=len(l)
l[n-4:n]=[]
nombredatos="".join(l)


#Graficar


plt.figure()
plt.subplot(131, aspect='equal')
plt.plot(x,v)
plt.xlabel('Distancia')
plt.ylabel('Velocidad')
plt.title('Estado viscosidad')
plt.subplot(132, aspect='equal')
plt.plot(x,p)
plt.xlabel('Distancia')
plt.ylabel('Presion')
plt.title('Estado Presion')
plt.subplot(133, aspect='equal')
plt.plot(x,d)
plt.xlabel('Distancia')
plt.ylabel('Densidad')
plt.title('Estado Densidad')
plt.show()
plt.savefig(str(datos)+'.pdf')
