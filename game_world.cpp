#include "game_world.h"
#include "world.h"
#include "render.h"

using namespace std;

Game_World::Game_World(){
    clear_world();
}

void Game_World::clear_world(){
    field_width=0;
    field_height=0;

    field_size=0.0;

    elapsed_time=0.0;

    field.clear();
    field_show.clear();
    particles.clear();
}

void Game_World::generate_world(){
    clear_world();

    game.center_camera(Collision_Circ(0.0,0.0,0.0));

    field_width=100;
    field_height=100;

    field_size=1000.0;

    field.resize(field_width,vector<Vector>(field_height));
    field_show.resize(field_width,vector<Vector>(field_height));

    game.center_camera(Collision_Rect(((double)field_width/2.0)*field_size,((double)field_width/2.0)*field_size,0.0,0.0));
}

void Game_World::tick(){
}

void Game_World::ai(){
}

void Game_World::movement(){
    for(int i=0;i<particles.size();i++){
        particles[i].check_field(field);
    }

    for(int x=0;x<field_width;x++){
        for(int y=0;y<field_height;y++){
            field[x][y].magnitude=0.0;
            field_show[x][y].magnitude=0.0;
        }
    }

    for(int i=0;i<particles.size();i++){
        particles[i].accelerate();
    }

    for(int i=0;i<particles.size();i++){
        particles[i].movement();
    }

    Collision_Rect box_field(0,0,field_width*(uint32_t)field_size,field_height*(uint32_t)field_size);
    for(int i=0;i<particles.size();i++){
        if(!collision_check_circ_rect(particles[i].circle,box_field)){
            particles.erase(particles.begin()+i);
            i--;
        }
    }

    for(int i=0;i<particles.size();i++){
        particles[i].modify_field(field,field_show);
    }
}

void Game_World::events(){
    elapsed_time+=TIME_SCALE/UPDATE_RATE;
}

void Game_World::animate(){
}

void Game_World::render(){
    int camera_x=(int)(game.camera.x/(field_size*game.camera_zoom));
    int camera_y=(int)(game.camera.y/(field_size*game.camera_zoom));
    int end_x=camera_x+(int)(game.camera.w/(field_size*game.camera_zoom))+2;
    int end_y=camera_y+(int)(game.camera.h/(field_size*game.camera_zoom))+2;

    for(int x=camera_x;x<end_x;x++){
        for(int y=camera_y;y<end_y;y++){
            if(x>=0 && x<field_width && y>=0 && y<field_height){
                if(field_show[x][y].magnitude==0.0){
                    render_circle(((double)x*field_size+field_size/2.0)*game.camera_zoom-game.camera.x,((double)y*field_size+field_size/2.0)*game.camera_zoom-game.camera.y,0.5,1.0,"white");
                }
                else{
                    double pos_x=(double)x*field_size+field_size/2.0;
                    double pos_y=(double)y*field_size+field_size/2.0;

                    double magnitude=field_show[x][y].magnitude*500000.0;
                    if(magnitude>field_size){
                        magnitude=field_size;
                    }

                    Vector arrow(magnitude,field_show[x][y].direction);
                    Vector_Components vc=arrow.get_components();

                    render_line(pos_x*game.camera_zoom-game.camera.x,pos_y*game.camera_zoom-game.camera.y,
                                (pos_x+vc.a)*game.camera_zoom-game.camera.x,(pos_y+vc.b)*game.camera_zoom-game.camera.y,1.0,"white");

                    if(game.camera_zoom>ZOOM_MAX*0.75){
                        double arrow_size=1.0/8.0;

                        render_texture((pos_x+vc.a-arrow_size/2.0)*game.camera_zoom-game.camera.x,(pos_y+vc.b-arrow_size/2.0)*game.camera_zoom-game.camera.y,
                                       *image.get_image("arrow"),1.0,arrow_size*game.camera_zoom,arrow_size*game.camera_zoom,field_show[x][y].direction,"white");
                    }
                }
            }
        }
    }

    for(int i=0;i<particles.size();i++){
        particles[i].render();
    }
}

void Game_World::update_background(){
}

void Game_World::render_background(){
    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"ui_black");
}
