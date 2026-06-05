#include "processor.h"
#include "../../devices/serial_port/sp_encoding.h"
#include "../../devices/serial_port/serial_port.h"

void handle_receiving_data_keyboard(GameState* state, const GameEvent* event) {
    if (event->data.key == KEY_ESCAPE) {
        state->type = EXIT;
    }
}

void handle_receiving_data_serial_port(GameState* state, const GameEvent* event) {
    uint8_t data;
    Queue data_queue = event->data.serial_port_data;

    while (!dequeue(&data_queue, &data)) {
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
