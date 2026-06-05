#include "processor.h"
#include "../../devices/serial_port/sp_encoding.h"
#include "../../devices/serial_port/serial_port.h"

void handle_receiving_data_keyboard(GameState* state, const GameEvent* event) {
    if (event->data.key == KEY_ESCAPE) {
        state->type = EXIT;
    }
}

void handle_receiving_data_serial_port(GameState* state, const GameEvent* event) {
    Queue* data_queue = event->data.serial_port_data;
    process_animatronic_movements(state, data_queue);
}
