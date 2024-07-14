#include "Field.h"

Field::Field(uint width, uint height, float dx){
    this->width = width;
    this->height = height;
    this->particles = new Particle[width*height];
}

Field::~Field(){
    delete[] particles;
}

Particle* Field::get(uint x, uint y) const {
    return &particles[y*width + x];
}

void Field::physics(float dt, uint substeps){

    dt /= substeps;


    for(uint i = 0; i < substeps; i++){
        Particle* new_particles = new Particle[width*height];
        
        for(uint y = 1; y < height - 1; y++){
            for(uint x = 1; x < width - 1; x++){
                Particle& p = *get(x, y);
                Particle& p_new = new_particles[y*width + x];

                Particle& pL = *get(x - 1, y);
                Particle& pR = *get(x + 1, y);
                Particle& pU = *get(x, y - 1);
                Particle& pD = *get(x, y + 1);

                float alpha = p.c * dt / dx;
                float u_new = -(p.u - dt*p.du) + 2*p.u + alpha*alpha*(pL.u + pR.u + pU.u + pD.u - 4*p.u);

                p_new.c = p.c;
                p_new.du = (u_new - p.u) / dt;
                p_new.u = u_new * pow(0.995, dt);

            }
        }

        delete[] particles;
        particles = new_particles;

    }

}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::Uint8 texture[width*height*4];

    for(uint y = 0; y < height; y++){
        for(uint x = 0; x < width; x++){
            const Particle& p = *get(x, y);

            float u = p.u;

            if(u < -0.5f) u = -0.5f;
            if(u > 0.5f) u = 0.5f;

            u = u + 0.5f;

            texture[(y*width + x)*4 + 0] = 255*u;
            texture[(y*width + x)*4 + 1] = 255*u;
            texture[(y*width + x)*4 + 2] = 255*u;
            texture[(y*width + x)*4 + 3] = 255;

        }
    }


    sf::Texture tex;

    tex.create(width, height);
    tex.update(texture, width, height, 0, 0);

    sf::Sprite sprite(tex);
    sprite.setScale(scale, scale);

    target.draw(sprite, states);
}