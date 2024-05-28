#include "Field.h"

Field::Field(uint width, uint height){
    this->width = width;
    this->height = height;
    this->particles = new Particle[width*height];
}

Field::~Field(){
    delete[] particles;
}

Particle* Field::get(uint x, uint y){
    return &particles[y*width + x];
}
