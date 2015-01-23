#include "game_constants.h"
#include "world.h"

using namespace std;

double ZOOM_RATE=0.0;
double ZOOM_MIN=0.0;
double ZOOM_MAX=0.0;

double TIME_SCALE=0.0;

double GRAVITY=0.0;

double SOLAR_MASS=0.0;
double SOLAR_DENSITY=0.0;
double EARTH_MASS=0.0;
double EARTH_DENSITY=0.0;
double MOON_MASS=0.0;
double MOON_DENSITY=0.0;

void set_game_constant(string name,string value){
    if(name=="zoom_rate"){
        ZOOM_RATE=Strings::string_to_double(value);
    }
    else if(name=="zoom_min"){
        ZOOM_MIN=Strings::string_to_double(value);
    }
    else if(name=="zoom_max"){
        ZOOM_MAX=Strings::string_to_double(value);
    }
    else if(name=="time_scale"){
        TIME_SCALE=Strings::string_to_double(value);
    }
    else if(name=="gravity"){
        GRAVITY=Strings::string_to_double(value);
    }
    else if(name=="solar_mass"){
        SOLAR_MASS=Strings::string_to_double(value);
    }
    else if(name=="solar_density"){
        SOLAR_DENSITY=Strings::string_to_double(value);
    }
    else if(name=="earth_mass"){
        EARTH_MASS=Strings::string_to_double(value);
    }
    else if(name=="earth_density"){
        EARTH_DENSITY=Strings::string_to_double(value);
    }
    else if(name=="moon_mass"){
        MOON_MASS=Strings::string_to_double(value);
    }
    else if(name=="moon_density"){
        MOON_DENSITY=Strings::string_to_double(value);
    }
}
