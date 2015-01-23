#ifndef particle_h
#define particle_h

#include "collision.h"
#include "vector.h"

#include <vector>

class Particle{
public:

    //kg
    double mass;

    //kg/km^3
    double density;

    Collision_Circ circle;

    Vector velocity;
    Vector acceleration;
    Vector force;

    Particle(double get_mass,double get_density,double x,double y,Vector get_velocity);

    int get_range();

    void check_field(const std::vector< std::vector<Vector> >& field);

    void accelerate();
    void movement();

    void modify_field(std::vector< std::vector<Vector> >& field,std::vector< std::vector<Vector> >& field_show);

    void render();
};

#endif
