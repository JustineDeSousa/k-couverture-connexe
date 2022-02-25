#include "Loop.hpp"

#include <string>

#include <iostream>
#include <fstream>

int Loop::loop()
{

    if (init())
        return -1;

    if (abortCondition())
        return 0;

    createWindows();
    std::cerr << "Resolution = (" << w << " , " << h << ")" << std::endl;

    std::cerr << std::endl << "Loop " << name << std::endl;
    while (window.isOpen() && notdone())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gesEvent();
        }
        update();
        draw();
    }

    finish();

    std::cerr << std::endl << "exit loop " << name << std::endl << std::endl;
    return 0;
}

/*================Loop================*/
//Constucteur
Loop::Loop() : window(), h(200), w(200), name("default"), event() {}
Loop::Loop(uint height, uint width, std::string title) :
    window(), h(height), w(width), name(title), event() {}
//Destructeur
Loop::~Loop() {}

void Loop::gesEvent() {}
void Loop::update() {}
void Loop::draw() {}

bool Loop::notdone() const { return true; }
bool Loop::abortCondition() const { return false; }

void Loop::finish() { window.close(); };
int Loop::init() { return 0; }
void Loop::createWindows()
{
    window.create(sf::VideoMode(w, h), name, sf::Style::Default);
    window.setFramerateLimit(30);
}
