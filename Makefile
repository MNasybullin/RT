NAME		=	RT


CC			=	gcc

uname_S		:= $(shell uname -s)


FLAGS		= -Ofast -Wall -Wextra -Werror

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

SRC_DIR		=	sources/
INC_DIR		=	includes -I frameworks/SDL2.framework/Headers

OBJ_DIR		=	.objs/

SRC_BASE	=	main.c \
	vec_math.c \
	vec.c \
	color.c \
	read_config.c \
	get_mem.c \
	matrix.c \
	transformation.c \
	ray.c \
	sphere.c \
	light.c \
	world.c \
	camera.c \
	shape.c \
	plane.c \
	patterns.c \
	reflect.c \
	schlick.c \
	cube.c \
	cylinder.c \
	cone.c \
	triangle.c \
	camera_pos.c \
	vec_math_operations.c \
	transform_shape.c \
	render.c \
	color_op.c \
	patterns_at.c \
	patterns_shape.c \
	light_type.c \
	set_cone_cube.c \
	render_color_at.c \
	matrix_op.c \
	matrix_inv_test.c \
	patterns_maps.c \
	patterns_cube.c \
	patterns_cube_tex.c \
	mem_lst.c \
	parse.c \
	libft_func.c \
	init.c \
	make_plane.c \
	make_sphere.c \
	make_cone.c \
	make_cyl.c \
	make_cube.c \
	make_triangle.c \
	parse_lights.c \
	parse_cameras.c \
	error.c \
	utils.c \
	count.c \
	making_stuff.c \
	ifs.c \
	pushing.c \
	utils2.c \
	light_utils.c \
	cone_utils.c \
	cone_patterns.c \
	cube_patterns.c \
	cube_utils.c \
	ifs_2.c \
	cyl_patterns.c \
	cyl_utils.c \
	plane_patterns.c \
	plane_utils.c \
	sphere_patterns.c \
	sphere_utils.c \
	init_tri.c \
	tri_utils.c \
	tri_utils_2.c \
	error_2.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB		=	$(words $(SRC_BASE))
INDEX		=	0

SDL2_F		= -framework SDL2 -F ./frameworks/

SDL2_P		= -rpath @loader_path/frameworks/

all:
	@make -j $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)			\
	-I $(INC_DIR)\
	$(FLAGS) $(SDL2_P) $(SDL2_F)
	@strip -x $@
	@printf "\r\033[48;5;15;38;5;25m✅   MAKE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m\033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) -MMD -c $< -o $@\
		-I $(INC_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖  clean $(NAME)\033[0m\033[K\n"

fclean:		clean
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME)\033[0m\033[K\n"

re:		fclean all

-include $(OBJS:.o=.d)
