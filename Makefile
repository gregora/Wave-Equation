CUDA_PATH = /usr/local/cuda

all: main.out mainCUDA.out

Particle.o: Particle.cpp Particle.h
	g++ -c Particle.cpp

Field.o: Field.cpp Field.h
	g++ -c Field.cpp

main.out: main.cpp Particle.h Field.h Particle.o Field.o
	g++ -o main.out main.cpp Particle.o Field.o -lsfml-graphics -lsfml-window -lsfml-system

FieldCUDA.o: FieldCUDA.cu Field.h
	nvcc -c FieldCUDA.cu

mainCUDA.out: main.cpp Particle.h Field.h Particle.o FieldCUDA.o
	g++ -o mainCUDA.out main.cpp Particle.o FieldCUDA.o -lsfml-graphics -lsfml-window -lsfml-system -L$(CUDA_PATH)/lib64 -lcudart

