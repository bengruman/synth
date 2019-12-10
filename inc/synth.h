#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include "al_api.h"
#include "synth_err.h"

#define KEYBOARD "/dev/input/event4"

#define KEY2FREQ(key) ((ALfloat)(27.5 * exp2f(((ALfloat)key)/12.0)))

#define DEBUG std::cout << "DEBUG" << std::endl;
