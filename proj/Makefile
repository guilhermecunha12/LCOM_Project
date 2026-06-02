# name of the program (Minix service)
PROG=proj

# source code files to be compiled
.PATH: controller controller/handlers controller/handlers/helpers devices input models view view/handlers

SRCS = main.c \
       state.c \
       controller.c \
       main_menu_handlers.c \
       night_intro_handlers.c \
       night_survival_handlers.c \
       night_no_battery_handlers.c \
       night_6am_handlers.c \
       jumpscare_handlers.c \
       static_screen_handlers.c \
       win_handlers.c \
       processor.c \
       player_screen_movement_handler.c \
       subscribe.c \
       event_updater.c \
       assets.c \
       animatronic.c \
       sprite.c \
       ui_utils.c \
       view.c \
       renderer.c \
       main_menu_render.c \
       night_intro_render.c \
       night_survival_render.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

DPADD += ${LIBLCF} ../lab5/libvideo.a ../lab4/libmouse.a ../lab3/libkbc.a ../lab2/libtimer.a
LDADD += -L../lab5 -lvideo
LDADD += -L../lab4 -lmouse
LDADD += -L../lab3 -lkbc
LDADD += -L../lab2 -ltimer
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
