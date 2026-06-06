#ifndef RENDERER_H
#define RENDERER_H

#include "../../state.h"

/**
 * @brief Type alias for render handler functions (return void and take a pointer to GameState))
 */
typedef void (*RenderHandler)(const GameState*);

/**
 * @brief Get the appropriate render handler for the given GameState
 * @details Internally, the implementation uses a array indexed with GameState to retrieve the correct handler function. If no handler is defined for the given state, it returns NULL.
 * @param state The current state of the game, used to determine which set of event handlers to use.
 * @return The appropriate function pointer to a render handler function.
 */
RenderHandler get_render_handler(const StateType state);

/**
 * @brief Draws the mouse sprite on the screen.
 * @details This function draws the mouse in the coordinates given by the global game state and is called after everything else was drawn on the screen.
 * @param state The current GameState, since the mouse is drawn in certain states.
 */
void draw_mouse(const GameState* state);

/**
 * @brief Handler for rendering the Main Menu on the screen.
 * @param state The current GameState.
 */
void render_main_menu(const GameState* state);

/**
 * @brief Handler for rendering the newspaper when a new game is started.
 * @param state The current GameState.
 */
void render_newspaper(const GameState* state);

/**
 * @brief Handler for rendering each night intro, which is shown at the beginning of each night and introduces it.
 * @param state The current GameState.
 */
void render_night_intro(const GameState* state);

/**
 * @brief Handler for rendering the night survival screen, which is the main gameplay screen during each night.
 * @param state The current GameState.
 */
void render_night_survival(const GameState *state);

/**
 * @brief Handler for rendering the jumpscare screen.
 * @param state The current GameState.
 */
void render_jumpscare(const GameState *state);

/**
 * @brief Handler for rendering the static screen, which is after a jumpscare occurs.
 * @param state The current GameState.
 */
void render_static_screen(const GameState *state);

/**
 * @brief Handler for rendering the 6 AM screen, which is shown when the player successfully survives a night.
 * @param state The current GameState.
 */
void render_night_6am(const GameState *state);

/**
 * @brief Handler for rendering the Win screen, which is shown when the player successfully survives all five nights.
 * @param state The current GameState.
 */
void render_win_screen(const GameState* state);

/**
 * @brief Handler for rendering the Game Over screen, which is after the static Screen, when the player loses.
 * @param state The current GameState.
 */
void render_game_over(const GameState *state);

/**
 * @brief Handler for rendering the night no battery screen.
 * @param state The current GameState.
 */
void render_night_no_battery(const GameState* state);

/**
 * @brief Handler for rendering the Waiting for Data screen, which is shown in the receiver's perspective while waiting for data from the sender to start the night survival mode.
 * @param state The current GameState.
 */
void render_waiting_for_data(const GameState* state);

/**
 * @brief Handler for rendering the Receiving Data screen, which is shown in the receiver's perspective during the night survival mode, while receiving data from the sender about the animatronic movements. This handler draws the cameras and animatronics in their respective positions based on the data received from the sender through the serial port.
 * @param state The current GameState.
 */
void render_receiving_data(const GameState* state);

#endif /* RENDERER_H */
