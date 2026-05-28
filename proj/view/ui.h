#ifndef UI_H
#define UI_H

// Screen resolutions for mode 0x14C (instead of having getters for the values in
//the lab5 header file, as they are static for the whole project)
#define VBE_MODE 0x14C
#define BYTES_PER_PIXEL 4
#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 864

// Step offset value (offset applied to background for movement, change this beforehand)
#define BACKGROUND_STEP_OFFSET 5
#define BACKGROUND_MAX_OFFSET 100

// Main Menu UI

#define GAME_TITLE_X 86
#define GAME_TITLE_Y 117
#define NEW_GAME_SEL_X 75
#define NEW_GAME_SEL_Y 476
#define CONTINUE_SEL_X 75
#define CONTINUE_SEL_Y 572
#define NEW_GAME_X 153
#define NEW_GAME_Y 476
#define CONTINUE_X 153
#define CONTINUE_Y 572  
#define NIGHT_TEXT_X 162
#define NIGHT_TEXT_Y 627

#define BOX_NEW_GAME_WIDTH 300
#define BOX_NEW_GAME_HEIGHT 70

#define BOX_CONTINUE_WIDTH 300
#define BOX_CONTINUE_HEIGHT 90


// Night Survival UI (doors, cameras, power display, etc.)

#define NIGHT_CAMERA_1A_X 150
#define NIGHT_CAMERA_1A_Y 100
#define NIGHT_CAMERA_1A_W 30
#define NIGHT_CAMERA_1A_H 30

#define NIGHT_CAMERA_1B_X 250
#define NIGHT_CAMERA_1B_Y 100
#define NIGHT_CAMERA_1B_W 30
#define NIGHT_CAMERA_1B_H 30

#define NIGHT_CAMERA_2A_X 350
#define NIGHT_CAMERA_2A_Y 100
#define NIGHT_CAMERA_2A_W 30
#define NIGHT_CAMERA_2A_H 30

#define NIGHT_CAMERA_2B_X 450
#define NIGHT_CAMERA_2B_Y 100
#define NIGHT_CAMERA_2B_W 30
#define NIGHT_CAMERA_2B_H 30

#define NIGHT_LEFT_DOOR_BUTTON_X 50
#define NIGHT_LEFT_DOOR_BUTTON_Y 300
#define NIGHT_LEFT_DOOR_BUTTON_W 40
#define NIGHT_LEFT_DOOR_BUTTON_H 40

#define NIGHT_RIGHT_DOOR_BUTTON_X 730
#define NIGHT_RIGHT_DOOR_BUTTON_Y 300
#define NIGHT_RIGHT_DOOR_BUTTON_W 40
#define NIGHT_RIGHT_DOOR_BUTTON_H 40

#define NIGHT_LEFT_LIGHT_BUTTON_X 150
#define NIGHT_LEFT_LIGHT_BUTTON_Y 300
#define NIGHT_LEFT_LIGHT_BUTTON_W 40
#define NIGHT_LEFT_LIGHT_BUTTON_H 40

#define NIGHT_RIGHT_LIGHT_BUTTON_X 650
#define NIGHT_RIGHT_LIGHT_BUTTON_Y 300
#define NIGHT_RIGHT_LIGHT_BUTTON_W 40
#define NIGHT_RIGHT_LIGHT_BUTTON_H 40

#endif /* UI_H */