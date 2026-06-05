#ifndef SOUND_H
#define SOUND_H
/**
 * @brief Plays a sound effect based on the provided sound name.
 * @details This function writes the sound name to the sound device file to trigger the corresponding sound effect.
 * @param sound_name The name of the sound effect to play.
 */
void play_sound(const char *sound_name);

/**
 * @brief Stops any currently playing sound effect.
 * @details This function writes a stop command to the sound device file to halt any ongoing sound effects.
 */
void stop_sound(void);

#endif // SOUND_H
