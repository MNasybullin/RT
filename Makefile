# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 10:40:08 by aannara           #+#    #+#              #
#    Updated: 2020/10/07 19:35:37 by sdiego           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC = ./src/main.c \
	./src/vec_math.c \
	./src/vec.c \
	./src/color.c \
	./src/matrix.c \
	./src/transformation.c \
	./src/ray.c \
	./src/sphere.c \
	./src/light.c \
	./src/world.c \
	./src/camera.c \
	./src/shape.c \
	./src/plane.c \
	./src/patterns.c \
	./src/reflect.c \
	./src/schlick.c \
	./src/cube.c \
	./src/cylinder.c \
	./src/cone.c \
	./src/triangle.c

OBJ = $(SRC:.c=.o)

FLAGS = -pthread -O2 -Wall -Wextra -Werror


SDL_FLAGS = -Iinclude -I SDL_lib/SDL2.framework/Headers

SDL2 = -framework SDL2 -F ./SDL_lib/

SDL2_LOAD = -rpath @loader_path/SDL_lib/

INCLUDES = ./include

HEADERS = $(INCLUDES)/rt.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	gcc $(FLAGS) $(SRC) $(SDL_FLAGS) $(SDL2_LOAD) $(SDL2) -o $(NAME)
.c.o: $(HEADERS)
	gcc $(FLAGS) $(SDL_FLAGS) -c $< -o $@
clean:
	rm -fr ./src/*.o

fclean: clean
	rm -fr $(NAME)
	rm -fr ./img.bmp

re: fclean all
