#include <iostream>
#include <vector>
#include "Field.h"
#include "math.h"
#include <chrono>

class Boat {
    public:
    float x = 200;
    float y = 200;

    float v = 0;

    float ang = 0;

    void physics(float dt){
        x += dt * cos(ang) * v;
        y += dt * sin(ang) * v;
    }

    void updateField(Field& field){
        field.get(x + (int) cos(ang)*10, y + (int) sin(ang)*10) -> u = v*0.1;
        field.get(x - (int) cos(ang)*10, y - (int) sin(ang)*10) -> u = -v*0.1;


    }

};

int main(){

    Boat boat;

    Field field(1000, 1000, 1.0f);
    field.scale = 1.0f;
    field.dx = 0.1f;

    bool analytics = true;

    float dt = 0.05f;

    for(uint y = 0; y < field.height; y++){
        for(uint x = 0; x < field.width; x++){
            field.get(x, y)->u = 0.0f;
            field.get(x, y)->du = 0.0f;
            field.get(x, y)->c = 1.0f;
        }
    }


    for(uint y = 395; y < 405; y++){
        for(uint x = 495; x < 505; x++){
            field.get(x, y)->u = 1.0f;
        }
    }


    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Wave Equation");
    float time = 0;

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
         }


        // source 1
        for(uint y = 395; y < 405; y++){
            for(uint x = 495; x < 505; x++){
                field.get(x, y)->u = sin(time*0.5)*0.1;
            }
        }

        // source 2
        for(uint y = 595; y < 605; y++){
            for(uint x = 395; x < 405; x++){
                field.get(x, y)->u = sin(time*0.4)*0.1;
            }
        }


        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        field.physics(dt, 1);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        
        window.clear();
        window.draw(field);
        window.display();

        std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

        if (analytics){
           std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);


            std::cout << "Physics: " << time_span1.count() << " seconds" << std::endl;
            std::cout << "Render: " << time_span2.count() << " seconds" << std::endl;
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            boat.v += 0.1;
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            boat.v += -0.1;
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            boat.ang += -0.1;
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            boat.ang += 0.1;
        }

        boat.physics(dt);
        boat.updateField(field);



        time += dt;
    }

}