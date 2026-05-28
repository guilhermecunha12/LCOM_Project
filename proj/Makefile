# name of the program (Minix service)
PROG=proj

# source code files to be compiled
.PATH: controller controller/handlers controller/handlers/helpers devices models view view/handlers

SRCS = main.c controller.c main_menu_handlers.c night_survival_handlers.c processor.c player_screen_movement_handler.c subscribe.c assets.c sprite.c ui_utils.c view.c renderer.c models/animatronic.c 

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -L../lab2 -ltimer
LDADD += -L../lab3 -lkbc
LDADD += -L../lab4 -lmouse
LDADD += -L../lab5 -lvideo
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
