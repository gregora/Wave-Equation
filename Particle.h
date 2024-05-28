typedef unsigned int uint;

class Particle {
    public:
    float u = 0.0f;
    float v = 0.0f;
    float du = 0.0f;
    float dv = 0.0f;

    Particle(float u = 0.0f, float v = 0.0f, float du = 0.0f, float dv = 0.0f);
};
