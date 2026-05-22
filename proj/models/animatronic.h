#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include "../state.h"
#include <stdbool.h>

#define UPDATE_INTERVAL 4628 // 31800 ticks = 7 hours in game, so every 4628 ticks (approximately every hour) the animatronics will update their AI level and maybe their path.
#define HOUR_0 GAME_TIME - 4628 * 1
#define HOUR_1 GAME_TIME - 4628 * 2
#define HOUR_2 GAME_TIME - 4628 * 3
#define HOUR_3 GAME_TIME - 4628 * 4
#define HOUR_4 GAME_TIME - 4628 * 5
#define HOUR_5 GAME_TIME - 4628 * 6

void initialize_animatronic(Animatronic* anim);
void move_animatronic(Animatronic* anim);
bool should_animatronic_move(Animatronic* anim);
void update_AIanimatronic(Animatronic* anim, GameState* state, const GameEvent* event);


#endif /* ANIMATRONIC_H */