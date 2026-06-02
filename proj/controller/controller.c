#include <lcom/lcf.h>

#include "controller.h"
#include "../state.h"
#include "handlers/processor.h"

void process_event(GameState* state, GameEvent* event) {
    EventHandler handler = get_event_handler(state->type, event->type);

    if (handler) {
        handler(state, event);
    }
}
