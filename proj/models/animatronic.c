#include "animatronic.h"

#include <stdlib.h>
#include <stdio.h>

static CameraID FREDDY_PATH[] = {CAM_1A, CAM_1B, CAM_7, CAM_6, CAM_4B, RIGHT_DOOR};
static CameraID BONNIE_PATH[] = {CAM_1A, CAM_1B, CAM_5, CAM_3, CAM_2A, CAM_2B, LEFT_DOOR};
static CameraID CHICA_PATH[]  = {CAM_1A, CAM_1B, CAM_7, CAM_6, CAM_4A, CAM_4B, RIGHT_DOOR};
static CameraID FOXY_PATH[]   = {CAM_1C, CAM_2A, CAM_2B, LEFT_DOOR};

// Initialize paths
static CameraID *PATHS[4] = {
    [FREDDY] = FREDDY_PATH,
    [BONNIE] = BONNIE_PATH,
    [CHICA]  = CHICA_PATH,
    [FOXY]   = FOXY_PATH,
};

// Calculate dynamically the lengths of the paths
static const int ANIMATRONIC_PATH_LENGTHS[4] = {
    [FREDDY] = sizeof(FREDDY_PATH) / sizeof(FREDDY_PATH[0]),
    [BONNIE] = sizeof(BONNIE_PATH) / sizeof(BONNIE_PATH[0]),
    [CHICA]  = sizeof(CHICA_PATH) / sizeof(CHICA_PATH[0]),
    [FOXY]   = sizeof(FOXY_PATH) / sizeof(FOXY_PATH[0]),
};


static const int INITIAL_AI_LEVELS[4][5] = {
    [FREDDY] = {20, 0, 1, 2, 13},
    [BONNIE] = {20, 3, 0, 2, 9},
    [CHICA] = {20, 1, 5, 5, 8},
    [FOXY] = {0, 1, 2, 6, 9}
};

static const int MOVE_INTERVALS[4] = {
    [FREDDY] = 3 * FPS,
    [BONNIE] = 5 * FPS -1,
    [CHICA] = 5 * FPS,
    [FOXY] = 2 * FPS,
};

// Single-entry path for special no-battery Freddy state
//static const CameraID FREDDY_NO_BATTERY_PATH[1] = { CAM_1A };
//static const int FREDDY_NO_BATTERY_AI_LEVEL = 5; // 20% chance to attack
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_1 = 5*FPS; // 5 seconds
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_2 = 2*FPS; // 2 seconds

static void initialize_animatronic(Animatronic* animatronic, AnimatronicName name, int night_number){
    animatronic->name = name;
    animatronic->current_position_index = 0;
    animatronic->path = PATHS[name];
    animatronic->path_length = ANIMATRONIC_PATH_LENGTHS[name];
    animatronic->time_to_move_opportunity = MOVE_INTERVALS[name];
    animatronic->AI_level = INITIAL_AI_LEVELS[name][night_number - 1];
}

static void move_animatronic(Animatronic* animatronic) {
    animatronic->current_position_index++;
    if(animatronic->current_position_index >= animatronic->path_length) {
        // Loop back to the start of the path if it reaches the end.
        animatronic->current_position_index = 0;
    }
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
    if((current_position == LEFT_DOOR && !left_door_closed) || 
       (current_position == RIGHT_DOOR && !right_door_closed)) {
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

void initialize_animatronics(Animatronic* animatronics, int night_number) {
    for(AnimatronicName name = 0; name < NUM_ANIMATRONICS; name++) {
        initialize_animatronic(&animatronics[name], name, night_number);
    }
}

bool update_animatronic(Animatronic* animatronic, int time_left, bool left_door_closed, bool right_door_closed) {
    update_AI_level(animatronic, time_left);

    animatronic->time_to_move_opportunity--;

    if (animatronic->time_to_move_opportunity <= 0) {
        bool should_move = should_animatronic_move(animatronic);
        animatronic->time_to_move_opportunity = MOVE_INTERVALS[animatronic->name];
        if (should_move) {
            if (should_animatronic_attack(animatronic, left_door_closed, right_door_closed)) {
                return true;
            }
            move_animatronic(animatronic);
        }
    }

    return false;
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
