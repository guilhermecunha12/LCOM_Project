#include <lcom/lcf.h>
#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"

void render_jumpscare(const GameState *state) {
    if (state == NULL) return;
    
    AnimatronicName anim = state->data.jumpscare.animatronic_name;
    int frame = state->data.jumpscare.frame_index;

    int max_frames = get_jumpscare_frame_count(anim, state->data.jumpscare.is_freddy_lightout);
    if (anim >= NUM_ANIMATRONICS || frame >= max_frames) return;

    xpmASSET asset = get_jumpscare_asset(anim, state->data.jumpscare.is_freddy_lightout, frame);
    draw_sprite(get_asset(asset));
}
