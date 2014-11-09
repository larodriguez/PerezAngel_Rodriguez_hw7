#Este programa grafica los resultados del archivo string.c
import sys
import matplotlib.gridspec as gridspec
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D

#recogemos el nombre del archivo.dat que entra como parametro
data= sys.argv[1]

#cargar datos del archivo
datos = np.loadtxt(data)

#pagina de referencia para hacer la grafica: http://jakevdp.github.io/mpl_tutorial/tutorial_pages/tut5.html


x = np.zeros(shape=(121,101))
t= np.zeros(shape=(121,101))

contador=0
contador1=0


for i in range (0,101):
    for j in range(0,121):
        x[j][i]=contador
    contador+=1
for i in range (0,121):
    for j in range(0,101):
        t[i][j]=contador1
    contador1+=1


#definir arreglos para hacer una matriz 3d y poder graficar
#t_all = np.ones(121)
#x_all = np.ones(101)
#t_space = np.linspace(0,120,121)
#x_space = np.linspace(0,100,101)

#creamos cada una de las componentes de la grafica y sacamos todos los datos dentro del archivo 'datos' y se lo asignamos a una sola variable
#x = np.outer(t_all, x_space)
#t = np.outer(t_space, x_all)
u = datos[:]


letra=list(data)
n=len(letra)
letra[n-4:n]=[]
nombre_datos="".join(letra)


#Gracia 3D de la trayectoria en el plano x, y, z
figura = plt.figure()
tp = plt.axes(projection='3d')
tp.set_xlabel("$X$",fontsize=15)
tp.set_ylabel("$Time$",fontsize=15)
tp.set_zlabel("$U$",fontsize=15)
tp.set_title("$\mathrm{Cuerda}$", fontsize=25)
tp.plot_surface(t, x, u, cmap=plt.cm.jet, rstride=1, cstride=1, linewidth=0)
plt.savefig(str(nombre_datos)+'_3D_'+'.pdf')
