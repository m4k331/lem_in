NAME = visu

CC = gcc

#BIN_DIR = ../resources
BIN_DIR ?= .

CDIR = srcs
HDIR = includes
ODIR = objects

LBDIRS = minilibx_macos ../libft
LBNAMES = libft.a libmlx.a

FRAMEWORKS = -framework OpenGL -framework AppKit

LDFLAGS += $(addprefix -L , $(LBDIRS)) $(FRAMEWORKS)
LDLIBS += $(addprefix -l , $(LBNAMES:lib%.a=%))

INCDIRS = $(HDIR) $(LBDIRS) $(addsuffix /includes, $(LBDIRS))

DBCFLAGS =
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
			visu.c				\
			init_utils.c		\
			parse_rooms.c		\
			parse_connections.c	\
			parse_traces.c		\
			parse_utils.c		\
			parse_destroy.c

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

norm:
	norminette $(addprefix $(CDIR)/, $(SOURCES)) $(HDIR) 

MAKEOVERRIDES =
libs:
	@for i in $(LBDIRS); do \
		make -C $$i 2> /dev/null ; \
	done

objects/bresenham.o: srcs/bresenham.c includes/draw.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/utils.h includes/put.h
objects/clipping.o: srcs/clipping.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/draw_no_line.o: srcs/draw_no_line.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/draw_utils.o: srcs/draw_utils.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/utils.h
objects/error_handling.o: srcs/error_handling.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/event_handling.o: srcs/event_handling.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/projections.h includes/event_handling.h \
  includes/key_bindings.h includes/draw.h includes/matrix.h \
  minilibx_macos/mlx.h
objects/init_utils.o: srcs/init_utils.c includes/utils.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/initialize.o: srcs/initialize.c includes/projections.h \
  includes/visu.h ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/draw.h includes/utils.h includes/parse.h includes/matrix.h \
  minilibx_macos/mlx.h
objects/loops.o: srcs/loops.c includes/loops.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  minilibx_macos/mlx.h includes/matrix.h includes/render.h
objects/main.o: srcs/main.c includes/visu.h ../libft/includes/libft.h \
  ../libft/includes/vector.h ../libft/includes/list.h \
  ../libft/includes/dlist.h ../libft/includes/dict.h \
  ../libft/includes/fib.h ../libft/includes/get_next_line.h \
  ../libft/includes/tstr.h includes/matrix.h includes/event_handling.h \
  includes/draw.h includes/loops.h includes/render.h \
  minilibx_macos/mlx.h
objects/matrix.o: srcs/matrix.c includes/matrix.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/mouse_handling.o: srcs/mouse_handling.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/key_bindings.h minilibx_macos/mlx.h includes/render.h
objects/parse.o: srcs/parse.c includes/parse.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/parse_connections.o: srcs/parse_connections.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/parse.h
objects/parse_destroy.o: srcs/parse_destroy.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/parse_rooms.o: srcs/parse_rooms.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/parse.h
objects/parse_traces.o: srcs/parse_traces.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/parse.h
objects/parse_utils.o: srcs/parse_utils.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/parse.h
objects/point.o: srcs/point.c includes/visu.h ../libft/includes/libft.h \
  ../libft/includes/vector.h ../libft/includes/list.h \
  ../libft/includes/dlist.h ../libft/includes/dict.h \
  ../libft/includes/fib.h ../libft/includes/get_next_line.h \
  ../libft/includes/tstr.h
objects/projections.o: srcs/projections.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/projections.h includes/matrix.h
objects/put.o: srcs/put.c includes/draw.h includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/utils.h minilibx_macos/mlx.h
objects/render.o: srcs/render.c includes/visu.h ../libft/includes/libft.h \
  ../libft/includes/vector.h ../libft/includes/list.h \
  ../libft/includes/dlist.h ../libft/includes/dict.h \
  ../libft/includes/fib.h ../libft/includes/get_next_line.h \
  ../libft/includes/tstr.h includes/projections.h includes/render.h \
  includes/utils.h includes/put.h minilibx_macos/mlx.h
objects/render_info.o: srcs/render_info.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/render.h minilibx_macos/mlx.h
objects/render_info_utils.o: srcs/render_info_utils.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/utils.h includes/render.h includes/put.h minilibx_macos/mlx.h
objects/transform.o: srcs/transform.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h
objects/visu.o: srcs/visu.c includes/visu.h ../libft/includes/libft.h \
  ../libft/includes/vector.h ../libft/includes/list.h \
  ../libft/includes/dlist.h ../libft/includes/dict.h \
  ../libft/includes/fib.h ../libft/includes/get_next_line.h \
  ../libft/includes/tstr.h includes/key_bindings.h \
  includes/event_handling.h includes/projections.h includes/draw.h \
  includes/loops.h includes/render.h minilibx_macos/mlx.h
objects/xiolin_wu.o: srcs/xiolin_wu.c includes/visu.h \
  ../libft/includes/libft.h ../libft/includes/vector.h \
  ../libft/includes/list.h ../libft/includes/dlist.h \
  ../libft/includes/dict.h ../libft/includes/fib.h \
  ../libft/includes/get_next_line.h ../libft/includes/tstr.h \
  includes/utils.h includes/draw.h includes/put.h minilibx_macos/mlx.h
