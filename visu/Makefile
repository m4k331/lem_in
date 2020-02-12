NAME = visu

CC = gcc

#BIN_DIR = ../resources
BIN_DIR ?= .

CDIR = srcs
HDIR = includes
ODIR = objects

LBDIRS = minilibx_macos libft
LBNAMES = libft.a libmlx.a

FRAMEWORKS = -framework OpenGL -framework AppKit

LDFLAGS += $(addprefix -L , $(LBDIRS)) $(FRAMEWORKS)
LDLIBS += $(addprefix -l , $(LBNAMES:lib%.a=%))

INCDIRS = $(HDIR) $(LBDIRS) $(addsuffix /includes, $(LBDIRS))

DBCFLAGS = -Wno-error -g
CFLAGS = -Wall -Wextra -Werror -O3 $(addprefix -I , $(INCDIRS)) $(DBCFLAGS)

SOURCES =	main.c				\
			initialize.c		\
			parse.c				\
			point.c				\
			matrix.c			\
			bresenham.c			\
			put.c				\
			projections.c		\
			event_handling.c	\
			xiolin_wu.c			\
			draw_utils.c		\
			error_handling.c	\
			mouse_handling.c	\
			loops.c				\
			draw_no_line.c		\
			render.c			\
			render_info_utils.c	\
			render_info.c		\
			transform.c			\
			clipping.c			\
			visu.c

OBJECTS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))

.PHONY: all libs clean clean_name fclean re

all: libs $(ODIR) $(BIN_DIR) $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/$(NAME): $(OBJECTS)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(CDIR)/%.c includes/visu.h
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm -rf $(ODIR)
	@for i in $(LBDIRS); do \
		if ! $(MAKE) -C $$i fclean 2> /dev/null; then \
			$(MAKE) -C $$i clean; \
		fi; \
	done

clean_name:
	rm -f $(BIN_DIR)/$(NAME)

fclean: clean clean_name

re: fclean all

MAKEOVERRIDES =
libs:
	@for i in $(LBDIRS); do \
		make -C $$i; \
	done
