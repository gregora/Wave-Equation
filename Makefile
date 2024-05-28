all: main

Particle.o: Particle.cpp Particle.h
	g++ -c Particle.cpp

Field.o: Field.cpp Field.h
	g++ -c Field.cpp

main: main.cpp Particle.h Field.h Particle.o Field.o
	g++ -o main main.cpp Particle.o Field.o

