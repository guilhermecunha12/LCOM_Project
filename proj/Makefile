# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = main.c \
       controller/controller.c \
       controller/handlers/main_menu_handlers.c \
       controller/handlers/night_survival_handlers.c \
       controller/handlers/processor.c \
       models/assets.c \
       models/sprite.c \
       view/ui_utils.c \
       view/view.c \
       view/handlers/renderer.c

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
