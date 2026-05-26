#include "animatronic.h"
#include "../state.h"

static const CameraID PATHS[4][5] = {
    [FREDDY] = {CAM_1A, CAM_1B, CAM_2A, CAM_2B, CAM_1A},
    [BONNIE] = {CAM_1A, CAM_2A, CAM_2B, CAM_1A, CAM_2A},
    [CHICA] = {CAM_1A, CAM_1B, CAM_1A, CAM_1B, CAM_1A},
    [FOXY] = {CAM_1A, CAM_2A, CAM_1A, CAM_2A, CAM_1A},
};

static const int ANIMATRONIC_PATH_LENGTHS[5] = {
    [FREDDY] = sizeof(PATHS[FREDDY])/sizeof(CameraID),
    [BONNIE] = sizeof(PATHS[BONNIE])/sizeof(CameraID),
    [CHICA] = sizeof(PATHS[CHICA])/sizeof(CameraID),
    [FOXY] = sizeof(PATHS[FOXY])/sizeof(CameraID),
};

static const int INITIAL_AI_LEVELS[4][5] = {
    [FREDDY] = {0, 0, 1, 2, 13},
    [BONNIE] = {0, 3, 0, 2, 9},
    [CHICA] = {0, 1, 5, 5, 8},
    [FOXY] = {0, 1, 2, 6, 9}
};

static const int MOVE_INTERVALS[4] = {
    [FREDDY] = 3*FPS,
    [BONNIE] = 5*FPS-1,
    [CHICA] = 5*FPS,
    [FOXY] = 2*FPS,
};

// Single-entry path for special no-battery Freddy state
static const CameraID FREDDY_NO_BATTERY_PATH[1] = { CAM_1A };
static const int FREDDY_NO_BATTERY_AI_LEVEL = 5; // 20% chance to attack
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_1 = 5*FPS; // 5 seconds
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_2 = 2*FPS; // 2 seconds

static void initialize_animatronic(Animatronic animatronic, AnimatronicName name, int night_number){
    animatronic.name = name;
    animatronic.current_position_index = 0;
    animatronic.path = PATHS[name];
    animatronic.path_length = ANIMATRONIC_PATH_LENGTHS[name];
    animatronic.time_to_move_opportunity = MOVE_INTERVALS[name];
    animatronic.AI_level = INITIAL_AI_LEVELS[name][night_number - 1];
}

static void move_animatronic(Animatronic* animatronic) {
    if(animatronic->current_position_index == animatronic->path_length) {
        // Loop back to the start of the path if it reaches the end.
        animatronic->current_position_index = 0;
    }
    animatronic->current_position_index++;
}

static bool should_animatronic_move(Animatronic* animatronic) {
    if(animatronic->time_to_move_opportunity <= 0) {
        // Generate a random number between 1 and 20
        int random_number = (rand() % 20) + 1;

        // Check if the random number is less than or equal to the AI_level
        if(random_number <= animatronic->AI_level) {
            return true; // The animatronic should move
        }
    }
    return false;
}

static bool should_animatronic_attack(Animatronic* animatronic, bool left_door_closed, bool right_door_closed) {
    CameraID current_position = animatronic->path[animatronic->current_position_index];
    if((current_position == CAM_1A && !left_door_closed) || 
       (current_position == CAM_2A && !right_door_closed)) {
        return true; // The animatronic should attack
    }
    return false;
}

static void update_AI_level(Animatronic* animatronic, int time_left_ticks) {
    if(time_left_ticks % HOUR_DURATION == 0) {
        if(time_left_ticks == HOUR_0) {
            if(animatronic->name == FOXY) {
                animatronic->AI_level++;
            }
        }
        else if(time_left_ticks == HOUR_1) {
            if(animatronic->name == BONNIE) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == FOXY) {
                animatronic->AI_level++;
            }
        }
        else if(time_left_ticks == HOUR_2) {
            if(animatronic->name == BONNIE) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == CHICA) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == FOXY) {
                animatronic->AI_level += 2;
            }
        }
        else if(time_left_ticks == HOUR_3) {
            if(animatronic->name == BONNIE) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == CHICA) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == FREDDY) {
                animatronic->AI_level++;
            }
        }
        else if(time_left_ticks == HOUR_4) {
            if(animatronic->name == CHICA) {
                animatronic->AI_level++;
            }
            else if(animatronic->name == FREDDY) {
                animatronic->AI_level += 2;
            }
        }
    }
}

void initialize_animatronics(Animatronic animatronics[NUM_ANIMATRONICS], int night_number) {
    for(AnimatronicName name = 0; name < NUM_ANIMATRONICS; name++) {
        initialize_animatronic(animatronics[name], name, night_number);
    }
}

bool update_animatronic(Animatronic* animatronic, int time_left, bool left_door_closed, bool right_door_closed) {
    
    update_AI_level(animatronic, time_left);

    if(should_animatronic_move(animatronic)) {
        if (should_animatronic_attack(animatronic, left_door_closed, right_door_closed)) {
            return true;
        }
        move_animatronic(animatronic);
    }
    else {
        animatronic->time_to_move_opportunity--; 
    }

    // Reset time to move counter
    if (animatronic->time_to_move_opportunity <= 0) {
        animatronic->time_to_move_opportunity = MOVE_INTERVALS[animatronic->name]; 
    }

    return false; // Did not attack
}

Animatronic initialize_freddy_no_battery() {
    Animatronic freddy;

    // ---dummy initializations
    freddy.name = FREDDY;
    freddy.current_position_index = 0;
    freddy.path = NULL;
    freddy.path_length = 0;
    // ---
    
    freddy.time_to_move_opportunity = FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_1;
    freddy.AI_level = 5; // 20% chance to attack the player
    return freddy;
}

bool update_freddy_no_battery(Animatronic* freddy, int phase1_duration, int phase2_duration) {

    if (phase1_duration <= 0 && phase2_duration == NO_BATTERY_PHASE_DURATION) { // phase 1 just ended
        freddy->time_to_move_opportunity = FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_2;
    }

    if (should_animatronic_move(freddy)) return true; // a single move is enough for attack
    else freddy->time_to_move_opportunity--;

     if (freddy->time_to_move_opportunity <= 0) {
        if (phase1_duration >= 0) {
            freddy->time_to_move_opportunity = FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_1;
        } else {
            freddy->time_to_move_opportunity = FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_2;
        }
    }

    return false;
}
