#include <iostream>
#include <vector>
#include "Field.h"
#include "math.h"

int main(){

    Field field(200, 200, 1.0f);
    field.scale = 5.0f;

    for(uint y = 0; y < field.height; y++){
        for(uint x = 0; x < field.width; x++){
            field.get(x, y)->u = 0.0f;
            field.get(x, y)->du = 0.0f;
            field.get(x, y)->c = 0.5f;
        }
    }


    for(uint y = 95; y < 105; y++){
        for(uint x = 95; x < 105; x++){
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

        field.physics(1.0f, 1);

        window.clear();
        window.draw(field);
        window.display();

    }

}