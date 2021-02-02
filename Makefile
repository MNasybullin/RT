# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: out-nasybullin-mr <out-nasybullin-mr@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 10:40:08 by aannara           #+#    #+#              #
#    Updated: 2021/02/02 10:19:45 by out-nasybul      ###   ########.fr        #
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
	./src/triangle.c \
	./src/camera_pos.c \
	./src/vec_math_operations.c \
	./src/transform_shape.c \
	./src/render.c \
	./src/color_op.c \
	./src/patterns_at.c \
	./src/patterns_shape.c \
	./src/light_type.c \
	./src/set_cone_cube.c \
	./src/render_color_at.c \
	./src/matrix_op.c \
	./src/matrix_inv_test.c \
	./src/patterns_maps.c \
	./src/patterns_cube.c \
	./src/patterns_cube_tex.c \
	./src/mem_lst.c \
	./src/parse.c \
	./src/libft_func.c \
	./src/init.c \
	./src/make_plane.c \
	./src/make_sphere.c \
	./src/make_cone.c \
	./src/make_cyl.c \
	./src/make_cube.c \
	./src/make_triangle.c \
	./src/parse_lights.c \
	./src/parse_cameras.c \
	./src/error.c \
	./src/utils.c \
	./src/count.c \
	./src/making_stuff.c \
	./src/ifs.c \
	./src/pushing.c \
	./src/utils2.c \
	./src/light_utils.c \
	./src/cone_utils.c \
	./src/cone_patterns.c \
	./src/cube_patterns.c \
	./src/cube_utils.c \
	./src/ifs_2.c \
	./src/cyl_patterns.c \
	./src/cyl_utils.c \
	./src/plane_patterns.c \
	./src/plane_utils.c \
	./src/sphere_patterns.c \
	./src/sphere_utils.c \
	./src/init_tri.c \
	./src/tri_utils.c \
	./src/tri_utils_2.c \
	./src/error_2.c

OBJ = $(SRC:.c=.o)

FLAGS = -O2 -Wall -Wextra -Werror


SDL_FLAGS = -I SDL_lib/SDL2.framework/Headers

SDL2 = -framework SDL2 -F ./SDL_lib/

SDL2_LOAD = -rpath @loader_path/SDL_lib/

INCLUDES = ./include

HEADERS = $(INCLUDES)/rt.h $(INCLUDES)/mem_lst.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	gcc $(FLAGS) $(SRC) $(SDL_FLAGS) $(SDL2_LOAD) $(SDL2) -o $(NAME)
.c.o: $(HEADERS)
	gcc $(FLAGS) $(SDL_FLAGS) -c $< -o $@
clean:
	rm -fr ./src/*.o

fclean: clean
	rm -fr $(NAME)

re: fclean all
