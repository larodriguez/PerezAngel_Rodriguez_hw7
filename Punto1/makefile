#este es el make para correr los datos, si se quiere cambiar la densidad de la cuerda tiene que modificar los renglones que tengan la siguiente notacion: cambio**
all: string.x string_0.010000.dat string_0.010000_3D.pdf #cambio** si se queire otra densidad en el nombre del archivo

string.x: Punto1.c
	cc Punto1.c -lm -o string.x

string_0.010000.dat: string.x
	./string.x 0.01 #cambio** si se quiere otra densidad en el 0.01 cambiar por otro numero

string_0.010000_3D.pdf: string_0.010000.dat grafica_cuerda.py #cambio** el nombre de los archivos que contienen la densidad.
	python grafica_cuerda.py string_0.010000.dat
