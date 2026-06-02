#ifndef VIDEO_H
#define VIDEO_H

#include <stddef.h>
#include <stdint.h>
#include <lcom/xpm.h>


#define VIDEO_INTNO 0x10
#define VBE_CALL_AH 0x4F
#define VBE_SET_MODE_FUNCTION 0x02
#define SUPPORTED_FUNCTION 0x4F
#define FUNCTION_CALL_SUCCESS 0x00

/**
 * @brief Initializes the video card in a VBE graphics mode.
 *
 * Maps VRAM, stores mode information internally, and switches to the requested
 * VBE mode using a linear frame buffer.
 *
 * @param mode VBE mode to initialize.
 * @return 0 on success, non-zero otherwise.
 */
int(init_video_card)(uint16_t mode);

/**
 * @brief Returns the video card to Minix text mode.
 *
 * @return 0 on success, non-zero otherwise.
 */
int(switch_text_mode)(void);

/**
 * @brief Draws an XPM image at the given screen coordinates.
 *
 * The XPM is loaded using the color format of the current VBE mode.
 *
 * @param xpm XPM map to draw.
 * @param x Left coordinate of the image.
 * @param y Top coordinate of the image.
 * @return 0 on success, non-zero otherwise.
 */
int(draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Maps the frame buffer for the given VBE mode.
 *
 * Retrieves VBE mode information and stores relevant
 * information internally.
 *
 * @param mode VBE mode whose frame buffer should be mapped.
 * @return 0 on success, non-zero otherwise.
 */
int(config_Vram)(uint16_t mode);

/**
 * @brief Switches the video card to a VBE graphics mode.
 *
 *
 * @param mode VBE mode to set.
 * @return 0 on success, non-zero otherwise.
 */
int(vg_set_mode)(uint16_t mode);

/**
 * @brief Draws one pixel in the current frame buffer.
 *
 *
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param color Pixel color encoded for the current VBE mode.
 * @return 0 on success, non-zero otherwise.
 */
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line in the current frame buffer.
 *
 * @param x Horizontal coordinate of the first pixel.
 * @param y Vertical coordinate of the line.
 * @param len Line length in pixels.
 * @param color Pixel color encoded for the current VBE mode.
 * @return 0 on success, non-zero otherwise.
 */
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);


/**
 * @brief Clears the back buffer that will be used for 
 * double buffering
 * @return 0 on success, non-zero otherwise.
 */
int(clear_back_buffer)(void);


void vg_flip_buffer();

#endif
