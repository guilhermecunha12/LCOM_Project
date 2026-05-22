#include "animatronic.h"
#include "../state.h"

void initialize_animatronic(Animatronic* anim, int night_number){
    if(anim->name == FREDDY) {
        if(night_number == 1) anim->AI_level = 0;
        else if(night_number == 2) anim->AI_level = 0;
        else if(night_number == 3) anim->AI_level = 1;
        else if(night_number == 4) anim->AI_level = 2;
        else if(night_number == 5) anim->AI_level = 13;

    } else if(anim->name == BONNIE) {
        if(night_number == 1) anim->AI_level = 0;
        else if(night_number == 2) anim->AI_level = 3;
        else if(night_number == 3) anim->AI_level = 0;
        else if(night_number == 4) anim->AI_level = 2;
        else if(night_number == 5) anim->AI_level = 9;

    } else if(anim->name == CHICA) {
        if(night_number == 1) anim->AI_level = 0;
        else if(night_number == 2) anim->AI_level = 1;
        else if(night_number == 3) anim->AI_level = 5;
        else if(night_number == 4) anim->AI_level = 5;
        else if(night_number == 5) anim->AI_level = 8;

    } else if(anim->name == FOXY) {
        if(night_number == 1) anim->AI_level = 0;
        else if(night_number == 2) anim->AI_level = 1;
        else if(night_number == 3) anim->AI_level = 2;
        else if(night_number == 4) anim->AI_level = 6;
        else if(night_number == 5) anim->AI_level = 9;
    }
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
    if(time_left_ticks % UPDATE_AI_INTERVAL == 0) {
        if(time_left_ticks == HOUR_0) {
            if(anim->name == FOXY) {
                anim->AI_level++;
            }
        }
        else if(time_left_ticks == HOUR_1) {
            if(anim->name == BONNIE) {
                anim->AI_level++;
            }
            else if(anim->name == FOXY) {
                anim->AI_level++;
            }
        }
        else if(time_left_ticks == HOUR_2) {
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
        else if(time_left_ticks == HOUR_3) {
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
        else if(time_left_ticks == HOUR_4) {
            if(anim->name == CHICA) {
                anim->AI_level++;
            }
            else if(anim->name == FREDDY) {
                anim->AI_level += 2;
            }
        }
    }
}
