#include <iostream>
#include <vector>
#include "Field.h"
#include "math.h"
#include <chrono>

int main(){

    Field field(1000, 1000, 1.0f);
    field.scale = 1.0f;
    field.dx = 0.1f;

    bool analytics = true;

    for(uint y = 0; y < field.height; y++){
        for(uint x = 0; x < field.width; x++){
            field.get(x, y)->u = 0.0f;
            field.get(x, y)->du = 0.0f;
            field.get(x, y)->c = 0.5f;
        }
    }


    for(uint y = 395; y < 405; y++){
        for(uint x = 495; x < 505; x++){
            field.get(x, y)->u = 1.0f;
        }
    }


    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Wave Equation");

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
         }


        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        field.physics(1.0f, 10);
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
        
    }

}