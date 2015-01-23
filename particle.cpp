#include "particle.h"
#include "world.h"
#include "render.h"

using namespace std;

Particle::Particle(double get_mass,double get_density,double x,double y,Vector get_velocity){
    mass=get_mass;
    density=get_density;

    //km^3
    double volume=mass/density;

    //km
    double radius=pow(volume*(3.0/(4.0*PI)),1.0/3.0);

    circle=Collision_Circ(x,y,radius);
    velocity=get_velocity;
}

int Particle::get_range(){
    ///return (int)ceil(circle.r/game.world.field_size)+(int)ceil(GRAVITY*mass*0.00005018043318142525260368403544)+1;
    ///return (int)ceil(circle.r/game.world.field_size)+10;
    return game.world.field_width*2;
}

void Particle::check_field(const vector< vector<Vector> >& field){
    int range=get_range();

    int pos_x=(int)floor(circle.x/game.world.field_size);
    int pos_y=(int)floor(circle.y/game.world.field_size);

    for(int x=pos_x-range;x<pos_x+range;x++){
        for(int y=pos_y-range;y<pos_y+range;y++){
            if(x>=0 && x<game.world.field_width && y>=0 && y<game.world.field_height){
                double distance=distance_between_points(circle.x,circle.y,(double)x*game.world.field_size+game.world.field_size/2.0,(double)y*game.world.field_size+game.world.field_size/2.0);

                if(distance==0.0){
                    distance=0.00000000000001;
                }

                Vector effect=field[x][y];

                effect.magnitude*=mass/pow(distance,2.0);

                force+=effect;
            }
        }
    }
}

void Particle::accelerate(){
    acceleration=force/mass;

    velocity+=acceleration;

    force*=0.0;
}

void Particle::movement(){
    Vector_Components vc=velocity.get_components();

    circle.x+=vc.a*TIME_SCALE/UPDATE_RATE;
    circle.y+=vc.b*TIME_SCALE/UPDATE_RATE;

    for(int i=0;i<game.world.particles.size();i++){
        Particle* particle=&game.world.particles[i];

        if(this!=particle && collision_check_circ(circle,particle->circle)){
            Vector collision(particle->circle.r+circle.r,get_angle_to_circ(particle->circle,circle,game.camera));
            Vector_Components vc_coll=collision.get_components();
            circle.x=particle->circle.x+vc_coll.a;
            circle.y=particle->circle.y+vc_coll.b;
        }
    }

    /**if(circle.x-circle.r<0.0){
        circle.x=circle.r;
    }
    if(circle.y-circle.r<0.0){
        circle.y=circle.r;
    }

    if(circle.x+circle.r>=(double)game.world.field_width*game.world.field_size){
        circle.x=(double)game.world.field_width*game.world.field_size-circle.r;
    }
    if(circle.y+circle.r>=(double)game.world.field_height*game.world.field_size){
        circle.y=(double)game.world.field_height*game.world.field_size-circle.r;
    }*/
}

void Particle::modify_field(vector< vector<Vector> >& field,vector< vector<Vector> >& field_show){
    int range=get_range();

    int pos_x=(int)floor(circle.x/game.world.field_size);
    int pos_y=(int)floor(circle.y/game.world.field_size);

    for(int x=pos_x-range;x<pos_x+range;x++){
        for(int y=pos_y-range;y<pos_y+range;y++){
            if(x>=0 && x<game.world.field_width && y>=0 && y<game.world.field_height){
                double distance=distance_between_points(circle.x,circle.y,(double)x*game.world.field_size+game.world.field_size/2.0,(double)y*game.world.field_size+game.world.field_size/2.0);

                if(distance==0.0){
                    distance=0.00000000000001;
                }

                Vector effect(GRAVITY*mass,
                              get_angle_to_rect(circle,Collision_Rect((double)x*game.world.field_size,(double)y*game.world.field_size,game.world.field_size,game.world.field_size),game.camera));

                field[x][y]+=effect.opposite();
                ///field_show[x][y]+=effect.opposite();
                field_show[x][y]+=effect.opposite()/pow(distance,2.0);
            }
        }
    }
}

void Particle::render(){
    if(collision_check_circ_rect(circle*game.camera_zoom,game.camera)){
        render_circle(circle.x*game.camera_zoom-game.camera.x,circle.y*game.camera_zoom-game.camera.y,circle.r*game.camera_zoom,1.0,"red");

        ///engine_interface.get_font("small")->show(circle.x*game.camera_zoom-game.camera.x,circle.y*game.camera_zoom-game.camera.y,Strings::num_to_string(velocity.magnitude),"white");
    }
}
