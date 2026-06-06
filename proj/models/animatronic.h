#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include "../game_constants.h"

#include <stdbool.h>

/**
 * @brief Enum with the animatronic names
 */
typedef enum { FREDDY, BONNIE, CHICA, FOXY, NUM_ANIMATRONICS } AnimatronicName;

/**
 * @brief Struct representing an animatronic, which contains information about it.
 */
typedef struct {
    AnimatronicName name;
    int current_position_index; // where the animatronic currently is on the map (pointer to a CameraID in the path)
    int path_length; // length of the path array
    CameraID* path; // where the animatronic is trying to get to (if applicable)

    // This is in ticks
    int time_to_move_opportunity; // counter that determines when the animatronic can move to the next position in its path (when this number reaches 0, a number from [1, 20] is randomly generated and if that number is less than or equal to the IA_level, the animatronic moves to the next position in its path)
    int AI_level; // number that determines the probability of the animatronic to move
    int saved_AI_level; // used by Foxy to restore her AI level after being repelled at the door
} Animatronic;

/**
 * @brief Initializes the animatronic's data for the night based on the night number.
 * @details Initializes the animatronic's name, current position, path, path length, time to move opportunity and AI level.
 * @param animatronics An array of animatronics to be initialized.
 * @param night_number The current night number, used to determine the AI level of the animatronics.
 */
void initialize_animatronics(Animatronic animatronics[NUM_ANIMATRONICS], int night_number);

/**
 * @brief Updates the animatronic's position and checks if it should attack the player.
 * @details This function updates the animatronic's AI level based on the time left in the night, checks if it's time for the animatronic to move, moves the animatronic forward in its path (or reset it to the start) or attacks the player.
 * @param animatronic The animatronic to be updated.
 * @param time_left The time left in the night, used to update the animatronic's AI level.
 * @param left_door_closed Whether the left door is closed, used to determine if the animatronic should attack the player.
 * @param right_door_closed Whether the right door is closed, used to determine if the animatronic should attack the player.
 * @param camera_monitor_up Whether the player has the camera monitor up, used to prevent Foxy from moving.
 * @return true if the animatronic attacks the player, false otherwise.
 */
bool update_animatronic(Animatronic* animatronic, int time_left, bool left_door_closed, bool right_door_closed, bool camera_monitor_up, CameraID viewing_camera);

/**
 * @brief Initializes Freddy's data when the player's battery runs out.
 * @return An initialized Animatronic struct representing Freddy in the no battery scenario. This struct has dummy values for certain fields that are not used in this case.
 */
Animatronic initialize_freddy_no_battery();

/**
 * @brief Updates No-Battery-Freddy's state and checks if he should attack the player in a given frame.
 * @param freddy The No-Battery-Freddy animatronic to be updated.
 * @param phase1_duration The duration left of the first phase.
 * @param phase2_duration The duration left of the second phase.
 * @return true if Freddy attacks the player, false otherwise.
 */
bool update_freddy_no_battery(Animatronic* freddy, int phase1_duration, int phase2_duration);

#endif /* ANIMATRONIC_H */
