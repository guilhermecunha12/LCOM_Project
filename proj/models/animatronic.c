#include "animatronic.h"
#include "../state.h"

#define MAX_PATH_LENGTH 10 // TODO: review this value

void initialize_animatronic(Animatronic* anim, int night_number){
    // TODO
}

void move_animatronic(Animatronic* anim) {
    if(anim->current_position_index == anim->MAX_PATH_LENGTH) {
        // Loop back to the start of the path if it reaches the end.
        anim->current_position_index = 0;
    }
    anim->current_position_index++;
}

bool should_animatronic_move(Animatronic* anim) {
    if(anim->time_to_move_opportunity <= 0) {
        // Generate a random number between 1 and 20
        int random_number = (rand() % 20) + 1;

        // Check if the random number is less than or equal to the AI_level
        if(random_number <= anim->AI_level) {
            return true; // The animatronic should move
        }
    }
    return false;
}

void update_AI_level(Animatronic* anim, int time_left_ticks) {
    if(time_left_ticks % UPDATE_INTERVAL == 0) {
        if(time_left_ticks == UPDATE_INTERVAL * 1) {
            if(anim->name == FOXY) {
                anim->AI_level++;
            }
        }
        else if(time_left_ticks == UPDATE_INTERVAL * 2) {
            if(anim->name == BONNIE) {
                anim->AI_level++;
            }
            else if(anim->name == FOXY) {
                anim->AI_level++;
            }
        }
        else if(time_left_ticks == UPDATE_INTERVAL * 3) {
            if(anim->name == BONNIE) {
                anim->AI_level++;
            }
            else if(anim->name == CHICA) {
                anim->AI_level++;
            }
            else if(anim->name == FOXY) {
                anim->AI_level += 2;
            }
        }
        else if(time_left_ticks == UPDATE_INTERVAL * 4) {
            if(anim->name == BONNIE) {
                anim->AI_level++;
            }
            else if(anim->name == CHICA) {
                anim->AI_level++;
            }
            else if(anim->name == FREDDY) {
                anim->AI_level++;
            }
        }
        else if(time_left_ticks == UPDATE_INTERVAL * 5) {
            if(anim->name == CHICA) {
                anim->AI_level++;
            }
            else if(anim->name == FREDDY) {
                anim->AI_level += 2;
            }
        }
    }
}
