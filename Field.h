#include "Particle.h"
typedef unsigned int uint;

class Field {

    public:
    
    uint width;
    uint height;
    Particle* particles;

    Field(uint width, uint height);
    ~Field();

    Particle* get(uint x, uint y);
};
