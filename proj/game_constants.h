#ifndef SHARED_GAME_CONSTANTS_H
#define SHARED_GAME_CONSTANTS_H

#define FPS 30
#define NIGHT_TIME (532 * FPS)
#define HOUR_DURATION (NIGHT_TIME / 7) // Duration of each hour in ticks

#define HOUR_0 NIGHT_TIME - HOUR_DURATION * 1
#define HOUR_1 NIGHT_TIME - HOUR_DURATION * 2
#define HOUR_2 NIGHT_TIME - HOUR_DURATION * 3
#define HOUR_3 NIGHT_TIME - HOUR_DURATION * 4
#define HOUR_4 NIGHT_TIME - HOUR_DURATION * 5
#define HOUR_5 NIGHT_TIME - HOUR_DURATION * 6

#define DRAIN_RATE_NIGHT_1 (10 * FPS) // 10 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_2 (6 * FPS) // 6 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_3 (5 * FPS) // 5 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_4 (4 * FPS) // 4 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_5 (3 * FPS) // 3 seconds per 1% battery drain

// TODO: CHANGE
static const int DRAIN_RATE_PER_NIGHT[] = {
    DRAIN_RATE_NIGHT_1,
    DRAIN_RATE_NIGHT_2,
    DRAIN_RATE_NIGHT_3,
    DRAIN_RATE_NIGHT_4,
    DRAIN_RATE_NIGHT_5
};

// TODO: CHANGE to balance the game
#define DEFAULT_POWER_LEVEL 100

// Adjust this to balance difficulty
#define BATTERY_DRAIN_RATE_DOOR 3 
#define BATTERY_DRAIN_RATE_LIGHT 2
#define BATTERY_DRAIN_RATE_CAMERA 2

#define TICKS_PER_CAMERA_ANIMATION_FRAME (int) (0.034f * FPS) 
#define TICKS_PER_JUMPSCARE_FRAME (int) (0.067f * FPS)  // ~66ms per frame at 60Hz (~15fps animation)

#define NUM_JUMSCARE_FOXY 21
#define NUM_JUMPSCARE_BONNIE 11
#define NUM_JUMPSCARE_CHICA 16
#define NUM_JUMPSCARE_FREDDY_NORMAL 21
#define NUM_JUMPSCARE_FREDDY_LIGHTOUT 28


#define NEWSPAPER_DURATION (8 * FPS)
#define NIGHT_INTRO_DURATION (5 * FPS)
#define NIGHT_6AM_DURATION (5 * FPS)
#define WIN_SCREEN_DURATION (5 * FPS)
#define STATIC_SCREEN_DURATION (5 * FPS)

#define NO_BATTERY_PHASE_DURATION (20 * FPS) // 20 seconds for both phases

#define NUM_NIGHTS 6


typedef enum { CAM_1A, CAM_1B, CAM_2A, CAM_2B, CAM_1C, CAM_3, CAM_4A, CAM_4B, CAM_5, CAM_6, CAM_7, RIGHT_DOOR, LEFT_DOOR } CameraID;

#endif //SHARED_GAME_CONSTANTS_H
