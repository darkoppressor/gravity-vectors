#include "game.h"
#include "world.h"

using namespace std;

void Game::prepare_for_input(){
    if(in_progress){
        command_states.clear();

        display_scoreboard=false;
    }
}

void Game::handle_command_states_multiplayer(){
    if(in_progress){
        if(network.status=="server"){
            network.prepare_server_input_states();

            for(int i=0;i<network.clients.size();i++){
                if(!paused){
                    //Example multiplayer command state
                    /**if(network.clients[i].game_command_state("some_command")){
                        ///Deal with command state here
                    }*/
                }
            }
        }
    }
}

void Game::handle_game_commands_multiplayer(){
    if(in_progress){
        if(network.status=="server"){
            for(int i=0;i<network.clients.size();i++){
                for(int j=0;j<network.clients[i].command_buffer.size();j++){
                    string command_name=network.clients[i].command_buffer[j];

                    if(!paused){
                        //Example multiplayer command
                        /**if(command_name=="some_command"){
                            ///Deal with command here
                        }*/
                    }
                }

                network.clients[i].command_buffer.clear();
            }
        }
    }
}

bool Game::move_input(string direction){
    if(engine_interface.game_command_state(direction)){
        return true;
    }

    if(direction=="up" && engine_interface.game_command_state("move_stick_vertical")<-engine_interface.controller_dead_zone){
        return true;
    }
    else if(direction=="down" && engine_interface.game_command_state("move_stick_vertical")>engine_interface.controller_dead_zone){
        return true;
    }
    else if(direction=="left" && engine_interface.game_command_state("move_stick_horizontal")<-engine_interface.controller_dead_zone){
        return true;
    }
    else if(direction=="right" && engine_interface.game_command_state("move_stick_horizontal")>engine_interface.controller_dead_zone){
        return true;
    }

    return false;
}

void Game::handle_input_states_gui(){
    int mouse_x=0;
    int mouse_y=0;
    engine_interface.get_mouse_state(&mouse_x,&mouse_y);

    if(in_progress){
        if(engine_interface.game_command_state("scoreboard")){
            display_scoreboard=true;
        }

        //Move the camera
        if(move_input("left")){
            cam_state="left";
        }
        if(move_input("up")){
            cam_state="up";
        }
        if(move_input("right")){
            cam_state="right";
        }
        if(move_input("down")){
            cam_state="down";
        }
        if(move_input("left") && move_input("up")){
            cam_state="left_up";
        }
        if(move_input("up") && move_input("right")){
            cam_state="right_up";
        }
        if(move_input("right") && move_input("down")){
            cam_state="right_down";
        }
        if(move_input("down") && move_input("left")){
            cam_state="left_down";
        }
        if(move_input("left") && move_input("right")){
            cam_state="left";
        }
        if(move_input("up") && move_input("down")){
            cam_state="up";
        }
        if(move_input("left") && move_input("up") && move_input("right")){
            cam_state="left_up";
        }
        if(move_input("left") && move_input("down") && move_input("right")){
            cam_state="left_down";
        }
        if(move_input("left") && move_input("up") && move_input("down")){
            cam_state="left_up";
        }
        if(move_input("up") && move_input("right") && move_input("down")){
            cam_state="right_up";
        }
        if(move_input("left") && move_input("up") && move_input("right") && move_input("down")){
            cam_state="left_up";
        }
        if(!move_input("left") && !move_input("up") && !move_input("right") && !move_input("down")){
            cam_state="none";
        }
    }
}

void Game::handle_input_states(){
    int mouse_x=0;
    int mouse_y=0;
    engine_interface.get_mouse_state(&mouse_x,&mouse_y);

    if(in_progress){
        if(!paused){
            //Example multiplayer command state
            /**if(engine_interface.game_command_state("some_command")){
                command_states.push_back("some_command");
            }*/
        }
    }
}

bool Game::handle_game_command_gui(string command_name){
    //Pause the game.
    if(command_name=="pause"){
        toggle_pause();

        return true;
    }

    else if(command_name=="zoom_in"){
        zoom_camera_in(camera);

        return true;
    }
    else if(command_name=="zoom_out"){
        zoom_camera_out(camera);

        return true;
    }

    else if(command_name=="delete_particles"){
        world.particles.clear();

        return true;
    }

    //Example multiplayer pause
    /**if(command_name=="pause"){
        if(network.status=="server"){
            toggle_pause();

            network.send_paused();
        }

        return true;
    }*/

    return false;
}

bool Game::handle_game_command(string command_name){
    const uint8_t* keystates=SDL_GetKeyboardState(NULL);

    ///DEV COMMANDS
    if(engine_interface.option_dev && keystates[SDL_SCANCODE_F1]){
        //Example dev command
        /**if(command_name=="some_dev_command"){
            ///Dev command here.

            return true;
        }*/
    }
    ///END OF DEV COMMANDS

    if(!paused){
        //Example command
        /**if(command_name=="some_command"){
            ///Command here

            return true;
        }*/

        //Example multiplayer command input
        /**if(command_name=="some_command"){
            network.add_command(command_name);

            return true;
        }*/
    }

    return false;
}

bool Game::handle_input_events_gui(){
    bool event_consumed=false;

    if(in_progress){
        for(int i=0;i<engine_interface.game_commands.size() && !event_consumed;i++){
            if((event.type==SDL_CONTROLLERBUTTONDOWN && engine_interface.game_commands[i].button==event.cbutton.button) ||
               (event.type==SDL_KEYDOWN && event.key.repeat==0 && engine_interface.game_commands[i].key==event.key.keysym.scancode)){
                event_consumed=handle_game_command_gui(engine_interface.game_commands[i].name);
            }
        }
    }

    return event_consumed;
}

bool Game::handle_input_events(){
    bool event_consumed=false;

    if(in_progress){
        int mouse_x=0;
        int mouse_y=0;
        engine_interface.get_mouse_state(&mouse_x,&mouse_y);

        for(int i=0;i<engine_interface.game_commands.size() && !event_consumed;i++){
            if((event.type==SDL_CONTROLLERBUTTONDOWN && engine_interface.game_commands[i].button==event.cbutton.button) ||
               (event.type==SDL_KEYDOWN && event.key.repeat==0 && engine_interface.game_commands[i].key==event.key.keysym.scancode)){
                event_consumed=handle_game_command(engine_interface.game_commands[i].name);
            }
        }

        if(event.type==SDL_MOUSEWHEEL){
            if(!event_consumed && event.wheel.y>0){
                zoom_camera_in(camera);

                event_consumed=true;
            }
            else if(!event_consumed && event.wheel.y<0){
                zoom_camera_out(camera);

                event_consumed=true;
            }
        }
        else if(event.type==SDL_MOUSEBUTTONDOWN){
            double mouse_real_x=(game.camera.x+(double)mouse_x)/game.camera_zoom;
            double mouse_real_y=(game.camera.y+(double)mouse_y)/game.camera_zoom;

            if(!event_consumed && event.button.button==SDL_BUTTON_LEFT){
                game.world.particles.push_back(Particle(MOON_MASS,MOON_DENSITY,mouse_real_x,mouse_real_y,Vector(0.0,0.0)));

                event_consumed=true;
            }
            else if(!event_consumed && event.button.button==SDL_BUTTON_RIGHT){
                /**for(int i=0;i<4;i++){
                    double x=rng.random_range(0,(world.field_width-1)*(uint32_t)world.field_size);
                    double y=rng.random_range(0,(world.field_height-1)*(uint32_t)world.field_size);

                    game.world.particles.push_back(Particle(MOON_MASS*0.5*(double)rng.random_range(1,8),MOON_DENSITY,x,y,Vector(0.1*rng.random_range(0,300),rng.random_range(0,359))));
                }*/

                game.world.particles.push_back(Particle(MOON_MASS*10.0,MOON_DENSITY,mouse_real_x,mouse_real_y,Vector(0.0,0.0)));

                event_consumed=true;
            }
        }
    }

    return event_consumed;
}
