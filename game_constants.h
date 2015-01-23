#ifndef game_constants_h
#define game_constants_h

#include <string>
#include <stdint.h>

extern double ZOOM_RATE;
extern double ZOOM_MIN;
extern double ZOOM_MAX;

extern double TIME_SCALE;

extern double GRAVITY;

extern double SOLAR_MASS;
extern double SOLAR_DENSITY;
extern double EARTH_MASS;
extern double EARTH_DENSITY;
extern double MOON_MASS;
extern double MOON_DENSITY;

void set_game_constant(std::string name,std::string value);

#endif