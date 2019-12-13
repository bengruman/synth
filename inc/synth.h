#ifndef SYNTH_H
#define SYNTH_H

#include <math.h>

#include <iostream>

#include "al_api.h"

#define KEY2FREQ(key) ((ALfloat)(27.5 * exp2f(((ALfloat)key)/12.0)))

#define DEBUG std::cout << "DEBUG" << std::endl;

class Voice
{
public:
    Voice(Context * context, ALfloat frequency);
    ~Voice();
private:
    Buffer * buffer;
    Source * source;
};

#endif