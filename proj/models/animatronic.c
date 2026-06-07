#include "animatronic.h"
#include "../devices/serial_port/serial_port.h"
#include "../devices/serial_port/sp_encoding.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Paths that the animatronics follow to get to the player.
 */
static CameraID FREDDY_PATH[] = {CAM_1A, CAM_1B, CAM_7, CAM_6, CAM_4B, RIGHT_DOOR};
static CameraID BONNIE_PATH[] = {CAM_1A, CAM_1B, CAM_5, CAM_3, CAM_2A, CAM_2B, LEFT_DOOR};
static CameraID CHICA_PATH[]  = {CAM_1A, CAM_1B, CAM_7, CAM_6, CAM_4A, CAM_4B, RIGHT_DOOR};

/*
    first CAM1_C -> Closed
    second CAM1_C -> Peeking
    third CAM1_C -> fully out,
    3 -> empty, which is the CAM_2A
*/
static CameraID FOXY_PATH[]   = {CAM_1C, CAM_1C, CAM_1C, CAM_2A, CAM_2B, LEFT_DOOR};
// Maybe chang the foxy path to make it easier

/**
 * @brief Array of pointers to the paths, indexed by the AnimatronicName enum. This allows us to easily assign the correct path to each animatronic during initialization.
 */
static CameraID *PATHS[4] = {
    [FREDDY] = FREDDY_PATH,
    [BONNIE] = BONNIE_PATH,
    [CHICA] = CHICA_PATH,
    [FOXY] = FOXY_PATH,
};

/**
 * @brief Array of the lengths of each animatronic's path, indexed by the AnimatronicName enum. This allows us to easily assign the correct path length to each animatronic during initialization.
 */
static const int ANIMATRONIC_PATH_LENGTHS[4] = {
    [FREDDY] = sizeof(FREDDY_PATH) / sizeof(FREDDY_PATH[0]),
    [BONNIE] = sizeof(BONNIE_PATH) / sizeof(BONNIE_PATH[0]),
    [CHICA] = sizeof(CHICA_PATH) / sizeof(CHICA_PATH[0]),
    [FOXY] = sizeof(FOXY_PATH) / sizeof(FOXY_PATH[0]),
};

/**
 * @brief Initial AI levels for each animatronic for each night.
 */
static const int INITIAL_AI_LEVELS[4][5] = {
    [FREDDY] = {0, 0, 1, 2, 3},
    [BONNIE] = {0, 3, 0, 2, 9},
    [CHICA] = {0, 1, 5, 5, 8},
    [FOXY] = {0, 1, 2, 6, 9}
};

/**
 * @brief Time intervals for each animatronic to have an opportunity to move.
 */
static const int MOVE_INTERVALS[4] = {
    [FREDDY] = 3 * FPS,
    [BONNIE] = (5 * FPS) - 1,
    [CHICA] = 5 * FPS,
    [FOXY] = 5 * FPS,
};

static const int FOXY_FAST_MOVE_INTERVAL = 3 * FPS;

// Single-entry path for special no-battery Freddy state
/**
 * @brief Time intervals and AI level for Freddy in the not battery scenario.
 */
//static const CameraID FREDDY_NO_BATTERY_PATH[1] = { CAM_1A };
//static const int FREDDY_NO_BATTERY_AI_LEVEL = 5; // 20% chance to attack
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_1 = 5*FPS; // 5 seconds
static const int FREDDY_NO_BATTERY_MOVE_INTERVAL_PHASE_2 = 2*FPS; // 2 seconds

/**
 * @brief Function to initialize a specific animatronic's data.
 * @details This function initializes the animatronic's name, current position, path, path length, time to move opportunity and AI level based on the animatronic's name and the current night number.
 * @param animatronic The animatronic to be initialized.
 * @param name The name of the animatronic, used to determine its path, path length, and initial AI level.
 * @param night_number The current night number, used to determine the initial AI level of the animatronic based on the INITIAL_AI_LEVELS array.
 */
static void initialize_animatronic(Animatronic* animatronic, AnimatronicName name, int night_number){
    animatronic->name = name;
    animatronic->current_position_index = 0;
    animatronic->path = PATHS[name];
    animatronic->path_length = ANIMATRONIC_PATH_LENGTHS[name];
    animatronic->time_to_move_opportunity = MOVE_INTERVALS[name];
    animatronic->AI_level = INITIAL_AI_LEVELS[name][night_number - 1];
    animatronic->saved_AI_level = 0;

    // Send initial animatronic data through serial port
    uint8_t encoded_data = encode_animatronic_data(animatronic->name, animatronic->path[animatronic->current_position_index]);
    send_sp_data(encoded_data);
}

/**
 * @brief Function to move the animatronic forward in its path.
 * @details This function increments the animatronic's current position index to move it forward in its path. If the animatronic reaches the end of its path, it loops back to the start.
 * @param animatronic The animatronic to be moved.
 */
static void move_animatronic(Animatronic* animatronic) {
    animatronic->current_position_index++;
    if(animatronic->current_position_index >= animatronic->path_length) {
        // Loop back to the start of the path if it reaches the end.
        animatronic->current_position_index = 0;
    }
}

/**
 * @brief Function to determine if the animatronic should move to the next positio in its path.
 * @details This function checks if the animatronic's time to move opportunity has reached 0, and if so, generates a random number between 1 and 20. If the random number is less than or equal to the animatronic's AI level, the function return true.
 * @param animatronic The animatronic to be checked.
 * @return True if the animatronic should move, false otherwise.
 */
static bool should_animatronic_move(Animatronic* animatronic) {
    if(animatronic->time_to_move_opportunity <= 0) {
        srand((unsigned int)time(NULL)); // Seed the random number generator with the current time
        // Generate a random number between 1 and 20
        int random_number = (rand() % 20) + 1;

        // Check if the random number is less than or equal to the AI_level
        if(random_number <= animatronic->AI_level) {
            return true; // The animatronic should move
        }
    }
    return false;
}

/**
 * @brief Function to determine if the animatronic should attack the player.
 * @details This function checks the animatronic's current position in its path, and if it's at the left or right door, it checks if the corresponding door is closed. If the animatronic is at a door and that door is not closed, the function returns true, indicating that the animatronic should attack the player.
 * @param animatronic The animatronic to be checked.
 * @param left_door_closed A boolean indicating whether the left door is closed.
 * @param right_door_closed A boolean indicating whether the right door is closed.
 * @return True if the animatronic should attack the player, false otherwise.
 */
static bool should_animatronic_attack(Animatronic* animatronic, bool left_door_closed, bool right_door_closed) {
    CameraID current_position = animatronic->path[animatronic->current_position_index];
    if((current_position == LEFT_DOOR && !left_door_closed) || 
       (current_position == RIGHT_DOOR && !right_door_closed)) {
        return true; // The animatronic should attack
    }
    return false;
}

/**
 * @brief Function to update the animatronic's AI level based on the time left in the night.
 * @details The AI level is updated based on the animatronic's name and the time left in the night. The time left is checked against the HOUR_DURATION constant to determine when to update the AI level, and the specific updates are based on the animatronic's name and the current hour of the night.
 * @param animatronic The animatronic whose AI level is to be updated.
 * @param time_left_ticks The time left in the night, in ticks. This is used to determine when to update the AI level based on the HOUR_DURATION constant, which represents the duration of an hour in ticks.
 */
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

bool update_animatronic(Animatronic* animatronic, int time_left, bool left_door_closed, bool right_door_closed, bool camera_monitor_up, CameraID viewing_camera) {
    update_AI_level(animatronic, time_left);

    animatronic->time_to_move_opportunity--;

    if (animatronic->time_to_move_opportunity <= 0) {
        bool should_move = should_animatronic_move(animatronic);
        if (animatronic->name == FOXY && camera_monitor_up && animatronic->path[animatronic->current_position_index] == CAM_1C && viewing_camera == CAM_1C) should_move = false;
        // CHECK if it's foxy and updates to FOXY_FAST_MOVE_INTERVAL
        if (animatronic->name == FOXY && animatronic->path[animatronic->current_position_index] != CAM_1C){
            animatronic->time_to_move_opportunity = FOXY_FAST_MOVE_INTERVAL;
        }
        else
            animatronic->time_to_move_opportunity = MOVE_INTERVALS[animatronic->name];
        if (should_move) {
            if (should_animatronic_attack(animatronic, left_door_closed, right_door_closed)) {
                return true;
            }
            CameraID prev_position = animatronic->path[animatronic->current_position_index];
            move_animatronic(animatronic);

            if (animatronic->name == FOXY) {
                CameraID new_position = animatronic->path[animatronic->current_position_index];
                if (prev_position == CAM_1C && new_position != CAM_1C) {
                    // Foxy got out of the pirate cove.

                    animatronic->saved_AI_level = animatronic->AI_level;
                    animatronic->AI_level = 20;
                } else if (prev_position == LEFT_DOOR) {
                    // Foxy failed to attack.

                    animatronic->AI_level = animatronic->saved_AI_level;
                }
            }

            // Send animatronic data through serial port
            uint8_t encoded_data = encode_animatronic_data(animatronic->name, animatronic->path[animatronic->current_position_index]);
            send_sp_data(encoded_data);
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
    send_sp_data(encode_animatronic_data(freddy.name, RIGHT_DOOR)); // Freddy is right at the door in this state
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
