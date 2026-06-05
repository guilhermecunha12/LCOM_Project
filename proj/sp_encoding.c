#include "sp_encoding.h"


uint8_t encode_animatronic_data(AnimatronicName name, CameraID position) {
   
    uint8_t animatronic_data = 0;
    uint8_t camera_number = 0;
    uint8_t camera_letter = 0;

    switch (name) {
        case FREDDY:
            animatronic_data = ENC_FREDDY;
            break;
        case BONNIE:
            animatronic_data = ENC_BONNIE;
            break;
        case CHICA:
            animatronic_data = ENC_CHICA;
            break;
        case FOXY:
            animatronic_data = ENC_FOXY;
            break;
    }

    switch (position) {
        case CAM_1A:
            camera_number = CAMERA_1;
            camera_letter = CAMERA_A;
            break;
        case CAM_1B:
            camera_number = CAMERA_1;
            camera_letter = CAMERA_B;
            break;
        case CAM_2A:
            camera_number = CAMERA_2;
            camera_letter = CAMERA_A;
            break;
        case CAM_2B:
            camera_number = CAMERA_2;
            camera_letter = CAMERA_B;
            break;
        case CAM_1C:
            camera_number = CAMERA_1;
            camera_letter = CAMERA_C;
            break;
        case CAM_3:
            camera_number = CAMERA_3;
            camera_letter = CAMERA_NO_LETTER;
            break;
        case CAM_4A:
            camera_number = CAMERA_4;
            camera_letter = CAMERA_A;
            break;
        case CAM_4B:
            camera_number = CAMERA_4;
            camera_letter = CAMERA_B;
            break;
        case CAM_5:
            camera_number = CAMERA_5;
            camera_letter = CAMERA_NO_LETTER;
            break;
        case CAM_6:
            camera_number = CAMERA_6;
            camera_letter = CAMERA_NO_LETTER;
            break;
        case CAM_7:
            camera_number = CAMERA_7;
            camera_letter = CAMERA_NO_LETTER;
            break; 
        case RIGHT_DOOR:
            camera_number = DOOR;
            camera_letter = CAMERA_B;
            break; 
        case LEFT_DOOR:
            camera_number = DOOR;
            camera_letter = CAMERA_A;
            break;
    }

    return (animatronic_data << 6) | (camera_number << 2) | (camera_letter & 0x03);
}
