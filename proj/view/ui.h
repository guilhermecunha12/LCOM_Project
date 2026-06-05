#ifndef UI_H
#define UI_H

// Screen resolutions for mode 0x14C (instead of having getters for the values in
//the lab5 header file, as they are static for the whole project)
#define VBE_MODE 0x14C
#define BYTES_PER_PIXEL 4
#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 864

#define BACKGROUND_MOVE_VELOCITY (int) (8 * 60.0f / FPS) // For lower fps, the number of updates is lower so we want to increase the velocity to make the movement smoother and consistent for different fps values.
#define BACKGROUND_MAX_OFFSET 300
#define CAMERA_MAX_OFFSET 200
#define CAMERA_MOVE_VELOCITY (int) (2 * 60.0f / FPS)
#define CAMERA_MOVEMENT_WAIT_TIME 1 * FPS
#define CENTER_BACKGROUND_OFFSET -150

////// MAIN MENU UI //////////////////////////
  #define GAME_TITLE_X 86
  #define GAME_TITLE_Y 117
  #define NEW_GAME_SEL_X 75
  #define NEW_GAME_SEL_Y 407
  #define CONTINUE_SEL_X 75
  #define CONTINUE_SEL_Y 485
  #define NEW_GAME_X 153
  #define NEW_GAME_Y 405
  #define CONTINUE_X 153
  #define CONTINUE_Y 485
  #define EXIT_GAME_SEL_X 90
  #define EXIT_GAME_SEL_Y 588
  #define EXIT_GAME_X 153
  #define EXIT_GAME_Y 588
  #define NIGHT_TEXT_X 144
  #define NIGHT_TEXT_Y 525

// Use this for both exit game and new game 
  #define BOX_NORMAL_WIDTH 320
  #define BOX_NORMAL_HEIGHT 70

  #define BOX_CONTINUE_WIDTH 300
  #define BOX_CONTINUE_HEIGHT 80
//////////////////////////////////////////////////////


//////////////////// CAMERA UI ////////////////////////////
// The night text is defined as (Button.x + 3, Button.y -3)
#define NIGHT_TEXT_POS(x,y) (x + 5), (y + 4)

// Map layout position
#define MAP_LAYOUT_X 736
#define MAP_LAYOUT_Y 488

// Size of each of the night cam buttons (selected or normal ones, as they have the same size)
#define BUTTON_SIZE_WIDTH 59
#define BUTTON_SIZE_HEIGHT 40

// Text saying which cam is selected
#define SELECTED_CAM_TEXT_X 736
#define SELECTED_CAM_TEXT_Y 419

// Positions of each button in the map layout
  #define NIGHT_CAMERA_1A_X 833
  #define NIGHT_CAMERA_1A_Y 477

  #define NIGHT_CAMERA_1B_X 815
  #define NIGHT_CAMERA_1B_Y 528

  #define NIGHT_CAMERA_1C_X 777
  #define NIGHT_CAMERA_1C_Y 608

  #define NIGHT_CAMERA_3_X 748
  #define NIGHT_CAMERA_3_Y 702

  #define NIGHT_CAMERA_5_X 709
  #define NIGHT_CAMERA_5_Y 550

  #define NIGHT_CAMERA_7_X 1048
  #define NIGHT_CAMERA_7_Y 556

  #define NIGHT_CAMERA_6_X 1037
  #define NIGHT_CAMERA_6_Y 685

  #define NIGHT_CAMERA_2A_X 834
  #define NIGHT_CAMERA_2A_Y 725

  #define NIGHT_CAMERA_2B_X 834
  #define NIGHT_CAMERA_2B_Y 769

  #define NIGHT_CAMERA_4A_X 940
  #define NIGHT_CAMERA_4A_Y 725

  #define NIGHT_CAMERA_4B_X 940
  #define NIGHT_CAMERA_4B_Y 769

// Record symbol
#define REC_SYMBOL_X 56
#define REC_SYMBOL_Y 48
////////////////////////////////////////////////////////

//////// GAME START UI /////////////////////////////////

// Maybe clear screen first and then draw these sprites on top (upon selecting our night)
#define SCREEN_TEXT_X 450
#define SCREEN_TEXT_Y 384

//////////////////////////////////////////////////////////

//////////// OFFICE LAYOUT UI ////////////////////////////

// Camera flip button
  #define CAMERA_FLIP_BUTTON_X 280
  #define CAMERA_FLIP_BUTTON_Y 780

  #define CAMERA_FLIP_BUTTON_WIDTH 482
  #define CAMERA_FLIP_BUTTON_HEIGHT 57

// Text describing current night and hours

  #define NIGHT_HOURS_TEXT_X 967
  #define NIGHT_HOURS_TEXT_Y 53

  #define AM_TEXT_X 1028
  #define AM_TEXT_Y 53

  #define NIGHT_COUNT_TEXT_X 980
  #define NIGHT_COUNT_TEXT_Y 101

// Battery details and usage

  // Usage
  #define USAGE_TEXT_X 44
  #define USAGE_TEXT_Y 797

  #define INDICATOR_USAGE_X 150
  #define INDICATOR_USAGE_Y 799
  // Percentage
  #define POWER_LEFT_TEXT_X 44
  #define POWER_LEFT_TEXT_Y 758

  #define I_DIGIT_POWER_X 213
  #define I_DIGIT_POWER_Y 760

  #define II_DIGIT_POWER_X 233
  #define II_DIGIT_POWER_Y 760

  #define PERCENTAGE_SIGN_X 255
  #define PERCENTAGE_SIGN_Y 764

//////////// RECEIVER MAP ////////////////////////////

#define MAP_CAM_1A_X 135
#define MAP_CAM_1A_Y 93
#define MAP_CAM_1B_X 320
#define MAP_CAM_1B_Y 140
#define MAP_CAM_1C_X 235
#define MAP_CAM_1C_Y 319
#define MAP_CAM_2A_X 359
#define MAP_CAM_2A_Y 601
#define MAP_CAM_2B_X 359
#define MAP_CAM_2B_Y 702
#define MAP_CAM_3_X 162
#define MAP_CAM_3_Y 548
#define MAP_CAM_4A_X 605
#define MAP_CAM_4A_Y 601
#define MAP_CAM_4B_X 605
#define MAP_CAM_4B_Y 702
#define MAP_CAM_5_X 81
#define MAP_CAM_5_Y 189
#define MAP_CAM_6_X 833
#define MAP_CAM_6_Y 302
#define MAP_CAM_7_X 859
#define MAP_CAM_7_Y 199

#define ID_OFFSET_X 13
#define FREDDY_ID_OFFSET_Y 12
#define BONNIE_ID_OFFSET_Y 29
#define CHICA_ID_OFFSET_Y 49
#define FOXY_ID_OFFSET_Y 67

#endif /* UI_H */
