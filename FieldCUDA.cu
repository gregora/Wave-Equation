#include "Field.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

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

__global__
void physics_CUDA(float dt, float dx, Particle* particles, Particle* new_particles, uint width){

    uint x = blockIdx.x + 1;
    uint y = threadIdx.x + 1;


    Particle& p = particles[y*width + x];
    Particle& p_new = new_particles[y*width + x];

    Particle& pL = particles[y*width + x - 1];
    Particle& pR = particles[y*width + x + 1];
    Particle& pU = particles[(y - 1)*width + x];
    Particle& pD = particles[(y + 1)*width + x];


    float alpha = p.c * dt / dx;
    float u_new = -(p.u - dt*p.du) + 2*p.u + alpha*alpha*(pL.u + pR.u + pU.u + pD.u - 4*p.u);

    p_new.c = p.c;
    p_new.du = (u_new - p.u) / dt;
    p_new.u = u_new * pow(0.995, dt);


}

void Field::physics(float dt, uint substeps){

    dt /= substeps;

    Particle* device_particles1;
    Particle* device_particles2;

    cudaMalloc(&device_particles1, width*height*sizeof(Particle));
    cudaMalloc(&device_particles2, width*height*sizeof(Particle));

    cudaMemcpy(device_particles1, particles, width*height*sizeof(Particle), cudaMemcpyHostToDevice);

    for(uint i = 0; i < substeps; i++){

        physics_CUDA<<<width - 2, height - 2>>>(dt, dx, device_particles1, device_particles2, width);
        cudaDeviceSynchronize();

        Particle *temp = device_particles1;
        device_particles1 = device_particles2;
        device_particles2 = temp;

    }
    cudaMemcpy(particles, device_particles1, width*height*sizeof(Particle), cudaMemcpyDeviceToHost);

    cudaFree(device_particles1);
    cudaFree(device_particles2);

}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    sf::RectangleShape rect(sf::Vector2f(scale, scale));

    for(uint y = 0; y < height; y++){
        for(uint x = 0; x < width; x++){
            const Particle& p = *get(x, y);

            float u = p.u;

            if(u < -0.5f) u = -0.5f;
            if(u > 0.5f) u = 0.5f;

            u = u + 0.5f;

            rect.setPosition(x*scale, y*scale);
            rect.setFillColor(sf::Color(255*u, 255*u, 255*u));

            target.draw(rect);
        }
    }
}