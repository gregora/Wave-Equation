#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <math.h>

typedef unsigned int uint;

class Field : public sf::Transformable, public sf::Drawable {

    public:
    
    uint width;
    uint height;
    float dx = 1.0f;
    Particle* particles;

    // device particles are used for CUDA
    Particle* device_particles1;
    Particle* device_particles2;
    
    float scale = 1.0f;

    Field(uint width, uint height, float dx = 1.0f);
    ~Field();

    Particle* get(uint x, uint y) const;

    void physics(float dt, uint substeps = 1);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
