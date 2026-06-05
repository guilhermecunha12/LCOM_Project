#ifndef SP_ENCODING_H
#define SP_ENCODING_H

#include "models/animatronic.h"
#include "game_constants.h"

#include <stdint.h>

#define ENDED_NIGHT_SURVIVAL 0x00
#define STARTED_NIGHT_SURVIVAL 0x01

#define ENC_FREDDY 0x0
#define ENC_BONNIE 0x1
#define ENC_CHICA 0x2
#define ENC_FOXY 0x3

#define DOOR 0x0
#define CAMERA_1 0x1
#define CAMERA_2 0x2
#define CAMERA_3 0x3
#define CAMERA_4 0x4
#define CAMERA_5 0x5
#define CAMERA_6 0x6
#define CAMERA_7 0x7

#define CAMERA_NO_LETTER 0x0
#define CAMERA_A 0x1
#define CAMERA_B 0x2
#define CAMERA_C 0x3

#define EXTRACT_ANIMATRONIC(data) ((data >> 6) & 0x03)
#define EXTRACT_CAMERA_NUMBER(data) ((data >> 2) & 0x0F)
#define EXTRACT_CAMERA_LETTER(data) (data & 0x03)

uint8_t encode_animatronic_data(AnimatronicName name, CameraID position);


#endif // SP_ENCODING_H