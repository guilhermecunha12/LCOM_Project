#include "processor.h"
#include "../../devices/serial_port/sp_encoding.h"

void handle_waiting_for_data_keyboard(GameState* state, const GameEvent* event) {
    if (event->data.key == KEY_ESCAPE) {
        state->type = EXIT;
    }

    else if (event->data.key == KEY_SPACE) {
        state->type = RECEIVING_DATA; // TODO: REMOVE
    }
}

void handle_waiting_for_data_serial_port(GameState* state, const GameEvent* event) {
    uint8_t data;
    Queue* data_queue = event->data.serial_port_data;
    dequeue(data_queue, &data); // Get the first byte of data received

    if (data == STARTED_NIGHT_SURVIVAL) {
        init_receiving_data_state(state, data_queue);
    }
}
