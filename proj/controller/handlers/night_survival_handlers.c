#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"

void handle_night_survival_mouse_click(GameState* state, const GameEvent* event) {

    int mouse_x = state->global_data.mouse_x;
    int mouse_y = state->global_data.mouse_y;

    if (state->data.night.camera_monitor_up) {
        // If the camera monitor is up, check if the click was on a camera feed to switch to it
        if (mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1A_X,
            NIGHT_CAMERA_1A_Y,
            NIGHT_CAMERA_1A_W,
            NIGHT_CAMERA_1A_H)) {

            state->data.night.viewing_camera = CAM_1A;
        }
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1B_X,
            NIGHT_CAMERA_1B_Y,
            NIGHT_CAMERA_1B_W,
            NIGHT_CAMERA_1B_H)) {

            state->data.night.viewing_camera = CAM_1B;
        }
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2A_X,
            NIGHT_CAMERA_2A_Y,
            NIGHT_CAMERA_2A_W,
            NIGHT_CAMERA_2A_H)) {

            state->data.night.viewing_camera = CAM_2A;
        }
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2B_X,
            NIGHT_CAMERA_2B_Y,
            NIGHT_CAMERA_2B_W,
            NIGHT_CAMERA_2B_H)) {

            state->data.night.viewing_camera = CAM_2B;
        }

    } else { // not checking the cameras
        
        // Clicked to close left door
        if (mouse_inside(mouse_x, mouse_y,
            NIGHT_LEFT_DOOR_BUTTON_X,
            NIGHT_LEFT_DOOR_BUTTON_Y,
            NIGHT_LEFT_DOOR_BUTTON_W,
            NIGHT_LEFT_DOOR_BUTTON_H)) {

            state->data.night.left_door_closed = !state->data.night.left_door_closed; // switch
        }

        // Clicked to close right door
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_RIGHT_DOOR_BUTTON_X,
            NIGHT_RIGHT_DOOR_BUTTON_Y,
            NIGHT_RIGHT_DOOR_BUTTON_W,
            NIGHT_RIGHT_DOOR_BUTTON_H)) {

            state->data.night.right_door_closed = !state->data.night.right_door_closed; // switch
        }

        // Clicked to turn on/off left light
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_LEFT_LIGHT_BUTTON_X,
            NIGHT_LEFT_LIGHT_BUTTON_Y,
            NIGHT_LEFT_LIGHT_BUTTON_W,
            NIGHT_LEFT_LIGHT_BUTTON_H)) {

            state->data.night.left_light_on = !state->data.night.left_light_on; // switch
        }

        // Clicked to turn on/off right light
        else if (mouse_inside(mouse_x, mouse_y,
            NIGHT_RIGHT_LIGHT_BUTTON_X,
            NIGHT_RIGHT_LIGHT_BUTTON_Y,
            NIGHT_RIGHT_LIGHT_BUTTON_W,
            NIGHT_RIGHT_LIGHT_BUTTON_H)) {

            state->data.night.right_light_on = !state->data.night.right_light_on; // switch
        }
    }
}