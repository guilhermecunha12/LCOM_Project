#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"
#include "../../devices/serial_port/sp_encoding.h"

// 2D array of event handlers indexed by state and event type (eth - event handler table)
static EventHandler eht[NUM_STATES][NUM_EVENTS] = {

    [MAIN_MENU] = {
        // Guarantees that only presses are registered in the main menu
        [KEYBOARD_PRESS] = handle_main_menu_keyboard,
        [MOUSE_LB_CLICK] = handle_main_menu_mouse_click,
        [MOUSE_MOVE] = handle_main_menu_mouse_move,
    },

    [NEWSPAPER] = {
        [TIMER_TICK] = handle_newspaper_timer,
    },

    [NIGHT_INTRO] = {
        [TIMER_TICK] = handle_night_intro_timer,
    },

    [NIGHT_SURVIVAL] = {
        [KEYBOARD_PRESS] = handle_night_survival_keyboard,
        [MOUSE_LB_CLICK] = handle_night_survival_mouse_click,
        [MOUSE_MOVE] = general_mouse_move,
        [TIMER_TICK] = handle_night_survival_timer,
    },

    [NIGHT_NO_BATTERY] = {
        [KEYBOARD_PRESS] = handle_night_no_battery_keyboard,
        [TIMER_TICK] = handle_night_no_battery_timer,
    },

    [JUMPSCARE] = {
        [TIMER_TICK] = handle_jumpscare_timer,
    },
    
    [STATIC_SCREEN] = {
        [TIMER_TICK] = handle_static_screen_timer,
    },

    [WIN] = {
        [TIMER_TICK] = handle_win_screen_timer,
    },
    [NIGHT_6AM] = {
        [TIMER_TICK] = handle_night_6am_timer,
    },

    [GAME_OVER] = {
        [TIMER_TICK] = handle_game_over_timer,
    },

    [WAITING_FOR_DATA] = {
        [KEYBOARD_PRESS] = handle_waiting_for_data_keyboard,
        [SERIAL_PORT_DATA] = handle_waiting_for_data_serial_port,
    },

    [RECEIVING_DATA] = {
        [KEYBOARD_PRESS] = handle_receiving_data_keyboard,
        [SERIAL_PORT_DATA] = handle_receiving_data_serial_port,
    }

};

void general_mouse_move(GameState* state, const GameEvent* event) {

    if (state->type == MAIN_MENU) {
        state->data.main_menu.selected_option = 0; // deselect main menu keyboard selection on mouse move
    }

    state->global_data.mouse_x += event->data.mouse_coords.delta_x;
    state->global_data.mouse_y -= event->data.mouse_coords.delta_y;

    // Clamp to screen bounds
    if (state->global_data.mouse_x < 0) state->global_data.mouse_x = 0;
    if (state->global_data.mouse_y < 0) state->global_data.mouse_y = 0;
    if (state->global_data.mouse_x > SCREEN_WIDTH-1) state->global_data.mouse_x = SCREEN_WIDTH-1;
    if (state->global_data.mouse_y > SCREEN_HEIGHT-1) state->global_data.mouse_y = SCREEN_HEIGHT-1;
}

EventHandler get_event_handler(const StateType state, const EventType event) {
    if (state >= NUM_STATES || event >= NUM_EVENTS) {
        return NULL; // Invalid state or event
    }
    return eht[state][event];
}

void process_animatronic_movements(GameState* state, Queue* data_queue) {
    uint8_t data;
    while (!dequeue(data_queue, &data)) {
        if (data == ENDED_NIGHT_SURVIVAL) {
            state->type = WAITING_FOR_DATA;
            return;
        }

        uint8_t animatronic_data = EXTRACT_ANIMATRONIC(data);
        uint8_t camera_number = EXTRACT_CAMERA_NUMBER(data);
        uint8_t camera_letter = EXTRACT_CAMERA_LETTER(data);

        AnimatronicName animatronic_name;
        switch (animatronic_data) {
            case ENC_FREDDY:
                animatronic_name = FREDDY;
                break;
            case ENC_BONNIE:
                animatronic_name = BONNIE;
                break;
            case ENC_CHICA:
                animatronic_name = CHICA;
                break;
            case ENC_FOXY:
                animatronic_name = FOXY;
                break;
            default: break;
        }

        CameraID new_cam = NUM_CAMERAS;

        switch (camera_number) {
            case CAMERA_1:
                if (camera_letter == CAMERA_A) new_cam = CAM_1A;
                else if (camera_letter == CAMERA_B) new_cam = CAM_1B;
                else if (camera_letter == CAMERA_C) new_cam = CAM_1C;
                break;

            case CAMERA_2:
                if (camera_letter == CAMERA_A) new_cam = CAM_2A;
                else if (camera_letter == CAMERA_B) new_cam = CAM_2B;
                break;

            case CAMERA_3:
                new_cam = CAM_3;
                break;

            case CAMERA_4:
                if (camera_letter == CAMERA_A) new_cam = CAM_4A;
                else if (camera_letter == CAMERA_B) new_cam = CAM_4B;
                break;

            case CAMERA_5:
                new_cam = CAM_5;
                break;

            case CAMERA_6:
                new_cam = CAM_6;
                break;

            case CAMERA_7:
                new_cam = CAM_7;
                break;

            case DOOR:
                if (camera_letter == CAMERA_B) new_cam = LEFT_DOOR;
                else if (camera_letter == CAMERA_A) new_cam = RIGHT_DOOR;
                break;

            default: break;
        }

        if (new_cam != NUM_CAMERAS) { // valid camera data received

            // Clear previous camera data for this animatronic
            CameraID prev_cam = state->data.receiving_data.animatronic_current_cam[animatronic_name];
            if (prev_cam != NUM_CAMERAS) {
                state->data.receiving_data.animatronics_in_cam[prev_cam][animatronic_name] = false;
            }

            // Update the state with the new camera data for this animatronic
            state->data.receiving_data.animatronics_in_cam[new_cam][animatronic_name] = true;
            state->data.receiving_data.animatronic_current_cam[animatronic_name] = new_cam;
        }
    }
}
