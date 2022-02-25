#pragma once

#ifndef Loop_h
#define Loop_h

#include "Header.hpp"

class Loop
{
    public:
        //Constucteur
        Loop();
        Loop(uint width, uint height, std::string title);
        //Destructeur
        ~Loop();

        int loop();

        virtual void gesEvent();
        virtual void update();
        virtual void draw();

        virtual bool notdone() const;
        virtual bool abortCondition() const;

        virtual void finish();
        virtual int init();
        virtual void createWindows();

        std::string name;
        sf::RenderWindow window;
        uint w, h;
        sf::Event event;
};

#endif
