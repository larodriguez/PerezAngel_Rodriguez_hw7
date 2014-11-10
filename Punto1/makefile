all: string.x string_0.010000.dat string_0.010000_3D.pdf

string.x: Punto1.c
	cc Punto1.c -lm -o string.x

string_0.010000.dat: string.x
	./string.x 0.01

string_0.010000_3D.pdf: string_0.010000.dat grafica_cuerda.py
	python grafica_cuerda.py string_0.010000.dat
