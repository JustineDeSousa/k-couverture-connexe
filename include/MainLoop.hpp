#pragma once

#ifndef MainLoop_h
#define MainLoop_h

//Loop
#include "Loop.hpp"
#include "header.hpp"

#include "Target.h"

class Main : public Loop
{
public:
    //Constucteur
    Main(const Solution* sol);
    //Destructeur
    ~Main();

    virtual void gesEvent();
    virtual void update();
    virtual void draw();

    virtual bool notdone() const;
    virtual bool abortCondition() const;

    virtual int init();
    virtual void createWindows();

private:
    const Instance* instance; 
    const Solution* solution;

    float spacing;
    TargetManager targets;
    static uint ncapture;
};

#endif

/*

    virtual  pair<float, float> getPosition(uint i) const = 0;
    int getRcom() const { return R_com; };
    int getRcapt() const { return R_capt; };


    virtual pair<float, float> getPosition(uint i) const { return cibles[i]; };

*/