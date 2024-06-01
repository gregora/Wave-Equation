#include <iostream>
#include <vector>
#include "Field.h"

int main(){

    Field field(100, 100, 1);

    for(uint y = 0; y < field.height; y++){
        for(uint x = 0; x < field.width; x++){
            field.get(x, y)->u = 0.0f;
            field.get(x, y)->du = 0.0f;
            field.get(x, y)->c = 1.0f;
        }
    }

    field.get(50, 50)->u = 0.5f;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Wave Equation");

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
         }

        field.physics(0.01f, 10);

        window.clear();
        window.draw(field);
        window.display();

    }

}