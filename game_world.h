#ifndef game_world_h
#define game_world_h

#include "particle.h"

#include <vector>

class Game_World{
public:

    uint32_t field_width;
    uint32_t field_height;

    //km^3
    double field_size;

    //s
    double elapsed_time;

    std::vector< std::vector<Vector> > field;
    std::vector< std::vector<Vector> > field_show;

    std::vector<Particle> particles;

    Game_World();

    void clear_world();
    void generate_world();

    void tick();
    void ai();
    void movement();
    void events();
    void animate();
    void render();

    void update_background();
    void render_background();
};

#endif
