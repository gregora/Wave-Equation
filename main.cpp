#include <iostream>
#include <vector>
#include "Field.h"
#include "math.h"

int main(){

    Field field(100, 100, 1.0f);

    for(uint y = 0; y < field.height; y++){
        for(uint x = 0; x < field.width; x++){
            field.get(x, y)->u = 0.0f;
            field.get(x, y)->du = 0.0f;
            field.get(x, y)->c = 0.5f;
        }
    }

    for(uint y = 1; y < field.height - 1; y++){
        for(uint x = 1; x < field.width - 1; x++){
            //field.get(x, y)->u = 0.5f * sin((x + y) / 10.0f);
        }
    }

    //field.get(50, 50)->u = 0.5f;

    for(uint x = 48; x < 52; x++){
        for(uint y = 48; y < 52; y++){
            field.get(x, y)->u = 0.5f;
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