#include "processor.h"

void handle_receiving_data_keyboard(GameState* state, const GameEvent* event) {
    if (event->data.key == KEY_ESCAPE) {
        state->type = EXIT;
    }
}

void handle_receiving_data_serial_port(GameState* state, const GameEvent* event) {
    // TODO: encodings
    state->type = WAITING_FOR_DATA;
}
