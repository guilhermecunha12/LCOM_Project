#include <lcom/lcf.h>

#include "controller.h"
#include "handlers/processor.h"

void process_event(GameState* state, const GameEvent* event) {
    EventHandler handler = get_event_handler(state->type, event->type);

    if (handler) {
        handler(state, event);
    }
}
