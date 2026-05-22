#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include "../state.h"
#include <stdbool.h>

#define UPDATE_INTERVAL 4628 // 31800 ticks = 7 hours in game, so every 4628 ticks (approximately every hour) the animatronics will update their AI level and maybe their path.

void initialize_animatronic(Animatronic* anim);
void move_animatronic(Animatronic* anim);
bool should_animatronic_move(Animatronic* anim);
void update_AI_level(Animatronic* anim, int time_left_ticks);


#endif /* ANIMATRONIC_H */