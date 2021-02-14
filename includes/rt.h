/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:41 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 15:08:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "SDL.h"
# include "mem_lst.h"

# define THREADS 40
# define WIN_W 400
# define WIN_H 400
# define EPSILON 0.00001
# define KEY sdl->e.key.keysym.sym
# define BUFF_SIZE 8
# define ENDL '\n'
# define MAX_LONG_LONG 9223372036854775807
# define IS_E 0
# define IS_R 1
# define IS_W 2
# define IS_X 4
# define IS_D 8

typedef struct				s_disc
{
	double					disc;
	double					a;
	double					b;
	double					c;
	double					temp;
	double					t1;
	double					t0;
	double					y0;
	double					y1;
	double					min;
	double					max;
	int						obj_n;
}							t_disc;

typedef struct				s_arr
{
	int						*arr;
	int						size;
}							t_arr;

typedef struct				s_matrix
{
	double					m[4][4];
}							t_matrix;

typedef struct				s_vec
{
	double					c[4];
}							t_vec;

typedef struct				s_inter_trian
{
	double					det;
	double					f;
	t_vec					p1_to_origin;
	double					u;
	double					v;
}							t_inter_trian;

typedef struct				s_color
{
	double					r;
	double					g;
	double					b;
}							t_color;

typedef struct				s_lighting
{
	t_color					effective_color;
	t_vec					light_v;
	t_color					ambient;
	double					light_dot_normal;
	t_color					diffuse;
	t_color					specular;
	t_vec					reflect_v;
	double					reflect_dot_eye;
	double					factor;
	t_vec					point;
	t_color					sum;
}							t_lighting;

typedef struct s_pattern	t_pattern;
typedef struct s_texturemap	t_texturemap;

struct						s_pattern
{
	int						width;
	int						height;
	double					u;
	double					v;
	t_color					a;
	t_color					b;
	t_matrix				transform;
	SDL_Surface				*cube_texture[6];
	t_color					main[6];
	t_color					ul[6];
	t_color					ur[6];
	t_color					bl[6];
	t_color					br[6];
};

struct						s_texturemap
{
	t_pattern				uv_pattern;
	t_vec					(*uv_map)(t_vec p);
};

typedef struct s_material	t_material;

/*
** int tex;   1 - yes, 0 - no
*/

struct						s_material
{
	t_color					color;
	double					ambient;
	double					diffuse;
	double					specular;
	double					shininess;
	double					reflective;
	int						pattern;
	double					transparency;
	double					refractive_index;
	int						shadow;
	t_color					(*pattern_at)(t_material m, t_vec pos);
	t_texturemap			texturemap;
	t_pattern				p;
	int						tex;
	SDL_Surface				*texture;
};

typedef struct				s_t_h
{
	double					t1;
	double					t2;
	int						obj;
	int						count;

}							t_t_h;

typedef struct				s_t_o
{
	double					t;
	int						obj;
	int						count;

}							t_t_o;

typedef struct				s_camera
{
	int						hsize;
	int						vsize;
	double					fov;
	t_matrix				transform;
	double					half_width;
	double					half_height;
	double					pixel_size;
	int						aliasing;
	int						sepia;
}							t_camera;

typedef struct				s_x_t
{
	t_t_o					*t;
	int						max_obj;
}							t_x_t;

typedef struct				s_uv_check
{
	int						width;
	int						height;
	t_color					color_a;
	t_color					color_b;
}							t_uv_check;

typedef struct				s_sp
{
	t_vec					c;
	double					r;
	t_matrix				transform;
	t_material				m;
	int						pattern;
	char					*texture;
	int						is_tex;
	int						width;
	int						height;
	t_color					color_a;
	t_color					color_b;
	int						pattern_type;
	t_uv_check				check;
}							t_sp;

typedef struct				s_cyl
{
	t_vec					c;
	double					r;
	double					min;
	double					max;
	int						closed;
	t_matrix				transform;
	t_material				m;
	int						width;
	int						height;
	int						is_tex;
	char					*texture;
	int						pattern;
	int						pattern_type;
	t_color					color_a;
	t_color					color_b;
	t_uv_check				check;
}							t_cyl;

typedef struct				s_cone
{
	t_vec					c;
	double					r;
	double					min;
	double					max;
	int						closed;
	t_matrix				transform;
	t_material				m;
	int						width;
	int						height;
	char					*texture;
	int						pattern;
	int						pattern_type;
	t_color					color_a;
	t_color					color_b;
	int						is_tex;
	t_uv_check				check;
}							t_cone;

typedef struct				s_plane
{
	t_vec					c;
	t_matrix				transform;
	t_material				m;
	int						width;
	int						height;
	int						pattern;
	int						pattern_type;
	char					*texture;
	t_color					color_a;
	t_color					color_b;
	int						is_tex;
}							t_plane;

typedef struct				s_cube
{
	t_vec					c;
	t_matrix				transform;
	t_material				m;
	int						pattern;
	int						tex;
	int						tex_num;
	char					*right;
	char					*left;
	char					*up;
	char					*down;
	char					*front;
	char					*back;
	int						pattern_type;
}							t_cube;

typedef struct				s_trian
{
	t_vec					p1;
	t_vec					p2;
	t_vec					p3;
	t_vec					e1;
	t_vec					e2;
	t_vec					norm;
	t_material				m;
	t_matrix				transform;
	int						pattern;
	int						width;
	int						height;
	int						pattern_type;
	char					*texture;
	t_color					color_a;
	t_color					color_b;
	int						is_tex;
	t_uv_check				check;
}							t_trian;

typedef struct				s_comps
{
	double					t;
	int						obj;
	t_vec					point;
	t_vec					eyev;
	t_vec					normalv;
	t_vec					reflectv;
	int						inside;
	double					shadow;
	t_vec					over_point;
	t_vec					under_point;
	double					n1;
	double					n2;
}							t_comps;

typedef struct				s_t_minmax
{
	double					min;
	double					max;
}							t_t_minmax;

typedef struct				s_light
{
	t_color					intensity;
	t_vec					corner;
	t_vec					uvec;
	int						usteps;
	t_vec					vvec;
	int						vsteps;
	int						samples;
}							t_light;

/*
** o - Origin; d - Direction
*/

typedef struct				s_ray
{
	t_vec					o;
	t_vec					d;
}							t_ray;

typedef struct s_world		t_world;
typedef struct s_shape		t_shape;

struct						s_shape
{
	void					*obj;
	int						(*loc_norm)(void *obj, t_vec world_point, t_vec *n);
	void					(*loc_intersect)(void *obj, t_ray r, t_x_t *x,
												int obj_n);
	t_material				*m;
	t_matrix				*transform;
};

/*
** light_count && light_obj - MULTI LIGHT
*/

struct						s_world
{
	t_light					*light;
	t_sp					*s;
	t_plane					*pl;
	t_cube					*cub;
	t_cyl					*cyl;
	t_cone					*cone;
	t_trian					*trian;
	t_shape					*obj_ar;
	t_camera				c;
	int						light_count;
	int						light_obj;
	int						trian_obj;
	int						s_obj;
	int						cone_obj;
	int						cyl_obj;
	int						cub_obj;
	int						pl_obj;
	int						max_obj;
	int						ar_count;
	int						effective_render;
	int						aquadisco;
	double					from_x;
	double					from_y;
	double					from_z;
	double					to_x;
	double					to_y;
	double					to_z;
	double					up_x;
	double					up_y;
	double					up_z;
};

typedef union				u_argb
{
	struct
	{
		u_int8_t			b;
		u_int8_t			g;
		u_int8_t			r;
		u_int8_t			a;
	}						parts;
	u_int32_t				color;
}							t_argb;

typedef struct				s_sdl
{
	SDL_Window				*win;
	SDL_Event				e;
	SDL_Renderer			*ren;
	SDL_Texture				*text;
	SDL_Surface				*icon;
	int						*img;
	int						run;
	int						progress;
	int						blur;
	int						stereo;
	int						cartoon;
}							t_sdl;

typedef struct				s_screenshot
{
	char					file_name[10];
	int						width;
	int						height;
	SDL_Texture				*target;
	SDL_Surface				*surface;
}							t_screenshot;

typedef struct				s_treads
{
	t_sdl					*sdl;
	t_camera				*camera;
	t_world					*world;
	int						start;
	int						finish;
}							t_treads;

typedef struct				s_forlight
{
	double					a;
	double					b;
	double					c;
	double					w;
	double					r;
	double					g;
	double					bl;
	int						type;
	t_vec					corner;
	t_vec					v1;
	t_vec					v2;
	int						usteps;
	int						vsteps;
}							t_forlight;

typedef struct				s_forcam
{
	t_vec					from;
	t_vec					to;
	t_vec					up;
	double					fov;
}							t_forcam;

typedef struct				s_data
{
	int						obj_n;
	int						fd;
	int						pl_num;
	int						sp_num;
	int						cone_num;
	int						cyl_num;
	int						cube_num;
	int						tri_num;
	int						lights_num;
	int						pl_i;
	int						sp_i;
	int						cone_i;
	int						cyl_i;
	int						cube_i;
	int						tri_i;
	int						light_i;
	char					**tab;
	char					*line;
	int						cam_num;
	int						tri_vect;
	t_forlight				*h;
	t_forcam				c;
}							t_data;

typedef struct				s_list
{
	void					*content;
	size_t					content_size;
	struct s_list			*next;
}							t_list;

int							ft_check_file(const char *file, unsigned check);
int							ft_open_file(const char *path);

t_vec						add(t_vec a1, t_vec a2);
t_vec						set_v_p(double a, double b, double c, double d);
t_vec						sub(t_vec a1, t_vec a2);
t_vec						neg(t_vec a);
t_vec						mult(t_vec a, double b);
t_vec						divi(t_vec a, double b);
double						magnitude(t_vec a);
t_vec						normalize(t_vec v);
double						dot(t_vec a, t_vec b);
t_vec						cross(t_vec a, t_vec b);
t_color						color(double r, double g, double b);
t_color						add_col(t_color a1, t_color a2);
t_color						sub_col(t_color a1, t_color a2);
t_color						mult_col(t_color a, double b);
t_color						divide_col(t_color a, int b);
t_color						hadamard_prod(t_color a1, t_color a2);
int							identic_m_4(t_matrix a, t_matrix b);
t_matrix					matrix_mult(t_matrix a, t_matrix b);
t_vec						matrix_mult_v_p(t_matrix a, t_vec b);
t_matrix					matrix_identity(t_matrix a);
t_vec						matrix_identity_v_p(t_vec a);
t_matrix					matrix_transposing(t_matrix a);
double						matrix_determinant_2(t_matrix a);
t_matrix					matrix_submatrix(t_matrix m, int a, int b,
int size);
double						matrix_minor(t_matrix m, int a, int b, int size);
double						matrix_cofactor(t_matrix m, int a, int b, int size);
double						matrix_determinant_3(t_matrix m);
double						matrix_determinant_4(t_matrix m);
int							matrix_inverse_test(t_matrix m);
t_matrix					matrix_inverse(t_matrix m);
t_matrix					matrix_nul();
t_matrix					translation(double x, double y, double z);
t_matrix					scaling(double x, double y, double z);
t_matrix					rotation_x(double r);
t_matrix					rotation_y(double r);
t_matrix					rotation_z(double r);

/*
** sphere
*/
t_ray						set_ray(t_vec or, t_vec di);
t_vec						position(t_ray r, double t);
t_sp						set_sphere();
void						intersect_sp(void *v_s, t_ray r, t_x_t *x,
int obj_n);
int							normal_at_sp(void *v_s, t_vec world_point,
t_vec *n);

/*
** transfrom
*/
t_matrix					set_transform(t_matrix s, t_matrix m);
int							check_transform_matrix(t_matrix *transform,
t_matrix *pattern_transform, int pattern);
t_ray						transform(t_ray r, t_matrix m);
t_matrix					identity_matrix(void);

/*
** light
*/
t_vec						reflect(t_vec in, t_vec normal);
t_light						point_light(t_color color, t_vec pos);
t_material					default_material(void);
t_color						lighting(t_material *m, t_world w, t_comps c);
int							col_to_int(t_color c);

/*
** world
*/
void						intersect_world(t_world *w, t_ray r, t_x_t *x);
t_comps						prepare_computations(int hit_obj, t_ray r,
t_world *w, t_x_t xs);
t_t_o						*alloc_tto(int size);
void						free_tto(t_t_o *tto);
int							*alloc_int(int size);
void						free_int(int *i);

/*
** shade
*/
t_color						color_at(t_world *w, t_ray r, int remaining);
int							hit(t_x_t x);
t_color						effective_shade_hit(t_world w, t_material *m);
t_arr						removenull(t_arr arr, int stack_size);

/*
** view transform
*/
t_matrix					view_transform(t_vec from, t_vec to, t_vec up);

/*
** camera
*/
t_camera					camera(double hsize, double vsize, double fov);
t_ray						ray_for_pixel(t_camera *camera, double px,
double py);
void						render(t_sdl *sdl, t_camera camera, t_world world);
t_color						sepia(t_color color);
void						check_camera_position(t_sdl *sdl, t_world *w);

/*
** shape
*/
void						push_obj(void *obj,
int (*loc_norm)(void *, t_vec, t_vec*),
void (*loc_intersect)(void *, t_ray, t_x_t *, int), t_world *w);
void						push_obj_conf(t_world *w, t_material *m,
t_matrix *transform);

/*
** plane
*/
int							normal_at_pl(void *v_s, t_vec world_point,
t_vec *n);
t_plane						set_plane();
void						intersect_pl(void *v_s, t_ray r, t_x_t *x,
int obj_n);

/*
** patterns
*/
void						stripe_pattern_shape(t_color a, t_color b,
t_material *m);
void						gradient_pattern_shape(t_color a, t_color b,
t_material *m);
void						ring_pattern_shape(t_color a, t_color b,
t_material *m);
void						checker_pattern_shape(t_color a, t_color b,
t_material *m);
t_color						stripe_at(t_material m, t_vec point);
double						realmod(double x, double p);
t_color						gradient_at(t_material m, t_vec point);
t_color						ring_at(t_material m, t_vec point);
t_color						checker_at(t_material m, t_vec point);

/*
** reflect
*/
t_color						reflected_color(t_world w, t_comps c,
int remaining);

/*
** refract
*/
t_sp						glass_sp(t_sp s);
t_color						refracted_color(t_world w, t_comps c,
int remaining);

/*
** Fresnel effect
*/
double						schlick(t_comps c);

/*
** cylinder
*/
t_cyl						set_cylinder();
void						intersect_cyl(void *v_s, t_ray r, t_x_t *x,
int obj_n);
int							normal_at_cyl(void *v_s, t_vec world_point,
t_vec *n);
void						intersect_caps(t_cyl *cyl, t_ray r, t_x_t *x,
int obj_n);
void						disc_cyl_cone(t_disc d, t_ray ray2, t_x_t *x,
int obj_n);

/*
** cone
*/
t_cone						set_cone();
void						intersect_cone(void *v_s, t_ray r, t_x_t *x,
int obj_n);
void						intersect_caps_cone(t_cone *cone, t_ray r, t_x_t *x,
int obj_n);
int							check_cap_cone(t_ray r, double t, double y);
int							normal_at_cone(void *v_s, t_vec world_point,
t_vec *n);

/*
** triangle
*/
void	set_trian(t_vec p1, t_vec p2, t_vec p3, t_trian	*t);
int							normal_at_trian(void *v_s, t_vec world_point,
t_vec *n);
void						intersect_trian(void *v_s, t_ray r, t_x_t *x,
int obj_n);

/*
** soft shadow
*/
double						intensity_at(t_world w, t_vec p);
t_light						area_light(t_vec corner, t_vec full_uvec,
int usteps, t_vec full_vvec, int vsteps, t_color color);
t_vec						point_on_light(t_light *l, int u, int v);

/*
** texuture mapping
*/
void						uv_checkers(t_uv_check c, t_pattern *p);
t_color						uv_patter_at(t_pattern checkers, double u,
double v);
t_vec						spherical_map(t_vec p);
t_texturemap				texture_map(t_pattern checkers,
t_vec (*spherical_map)(t_vec));
t_color						pattern_at(t_material m, t_vec point);
t_vec						planar_map(t_vec p);
t_vec						cylindrical_map(t_vec p);

/*
** cube
*/
t_cube						set_cube();
void						intersect_cube(void *v_s, t_ray r, t_x_t *x,
int obj_n);
double						min(double x, double y, double z);
double						max(double x, double y, double z);
t_t_minmax					check_axis(double origin, double direction);
int							normal_at_cube(void *v_s, t_vec world_point,
t_vec *n);
t_color						uv_pattern_at_cube(t_pattern pattern, double u,
double v, int face);
t_pattern					uv_align_check(t_color main, t_color ul, t_color ur,
t_color bl, t_color br, int face);
int							face_from_point(t_vec point);
t_vec						cube_uv_front(t_vec point);
t_vec						cube_uv_back(t_vec point);
t_vec						cube_uv_left(t_vec point);
t_vec						cube_uv_right(t_vec point);
t_vec						cube_uv_up(t_vec point);
t_vec						cube_uv_down(t_vec point);
t_color						pattern_at_cube(t_material m, t_vec point);
t_color						uv_patter_at_texture(SDL_Surface *texture, double u,
double v);

/*
** texture
*/
t_color						get_color_tex(SDL_Surface *texture, int x, int y);
t_color						pattern_at_cube_texture(t_material m, t_vec point);

/*
** screenshot
*/
void						save_texture(SDL_Renderer	*renderer,
SDL_Texture	*texture);

/*
** parsing
*/
void						read_file(char *file, t_data *p, t_world *w);
void						count_objects(t_data *p, char *line);
int							check_format(char *file);
int							len_tab(char **tab);
int							free_tab(char **tab);
void						alloc_obj_memory(t_data *p, t_world *w);
void						init_parse(t_data *p, t_world *w);
char						**make_plane(t_data *p, t_world *w, char **tab);
char						**make_sphere(t_data *p, t_world *w, char **tab);
void						complex_params_sphere(t_data *p, t_world *w,
char **tab, int flag);
void						make_obj_sphere(t_data *p, t_world *w, char **tab);
void						complex_params_plane(t_data *p, t_world *w,
char **tab, int flag);
void						make_obj_plane(t_data *p, t_world *w, char **tab);
char						**make_cone(t_data *p, t_world *w, char **tab);
void						make_obj_cone(t_data *p, t_world *w, char **tab);
void						complex_params_cone(t_data *p, t_world *w,
char **tab, int flag);
char						**make_cyl(t_data *p, t_world *w, char **tab);
void						make_obj_cyl(t_data *p, t_world *w, char **tab);
void						complex_params_cyl(t_data *p, t_world *w,
char **tab, int flag);
char						**make_cube(t_data *p, t_world *w, char **tab);
void						make_obj_cube(t_data *p, t_world *w, char **tab);
void						complex_params_cube(t_data *p, t_world *w,
char **tab, int flag);
char						**make_tri(t_data *p, t_world *w, char **tab);
void						make_obj_tri(t_data *p, t_world *w, char **tab);
void						complex_params_tri(t_data *p, t_world *w,
char **tab, int flag);
void						parse_lights(t_data *p, t_world *w);
void						lights_color(t_data *p);
void						lights_pos(t_data *p);
void						parse_cameras(t_data *p, t_world *w);
void						complex_params_camera(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_pl(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_sp(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_cyl(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_cone(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_cube(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_tri(t_data *p, t_world *w,
char **tab, int flag);
void						pushing_objects(t_data *p, t_world *w);
int							check_make_obj(char **tab);
void						triangle_sides(t_data *p, t_world *w,
char **tab, int flag);
int							valid_len(char ***tab, int len, t_data *p);
void						start_count_obj(t_data *p, t_world *w);
int							strcmp_v2(char *s1, char *s2);
void						start_count_lights(t_data *p, t_world *w);
void						count_lights(t_data *p, char *line);
void						continue_pushing(t_data *p, t_world *w);
void						write_lights(t_data *p, t_world *w);
void						making_obj(char **tab, t_data *p, t_world *w);
char						**check_type(t_data *p, t_world *w, char **tab);
void						init(t_sdl *sdl);
void						read_config(t_sdl *sdl, t_world *w,
t_data *p, char *path);
void						make_tex_cube(t_data *p, t_world *w);
void						texture_cube(char **tab, t_data *p, t_world *w);
char						*remove_quotes(char *s1);
void						texture_sp(char **tab, t_data *p, t_world *w);
void						help_counting(t_data *p, char **tab);
void						make_light(t_data *p);
void						free_split_tab(char **tab1, char **tab2,
char **tab3);
void						free_split_tab4(char ***tab1, char ***tab2,
char ***tab3, char ***tab4);
void						init_3_tabs(char ***tab1, char ***tab2,
char ***tab3);
void						init_4_tabs(char ***tab1, char ***tab2,
char ***tab3, char ***tab4);
void						making_light(t_data *p, t_world *w, char **tab);
void						making_camera(t_data *p, t_world *w, char **tab);
void						reading(t_data *p, t_world *w, char *file);
void						make_obj_cone_2(t_data *p, t_world *w, char **tab);
void						make_obj_cone_3(t_data *p, t_world *w, char **tab);
void						pattern_color_cone(t_data *p, t_world *w,
char **tab, int flag);
void						cone_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						cone_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_type_cone(t_data *p, t_world *w,
char **tab);
void						cone_patterns(t_data *p, t_world *w);
void						cone_patterns_1(t_data *p, t_world *w);
void						init_cone(t_data *p, t_world *w);
void						cube_patterns(t_data *p, t_world *w);
int							final_if_cube(char **tab);
void						make_obj_cube_2(t_data *p, t_world *w,
char **tab);
void						make_obj_cube_3(t_data *p, t_world *w,
char **tab, char *tmp);
void						make_obj_cube_4(t_data *p, t_world *w,
char **tab, char *tmp);
void						pattern_color_cube(t_data *p, t_world *w,
char **tab, int flag);
void						cube_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						cube_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						cube_crutch_3(t_data *p, t_world *w,
char **tab, int flag);
void						init_cube(t_data *p, t_world *w);
void						cyl_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						cyl_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						cyl_crutch_3(t_data *p, t_world *w,
char **tab, int flag);
void						pattern_color_cyl(t_data *p, t_world *w,
char **tab, int flag);
void						texture_cyl(char **tab, t_data *p, t_world *w);
void						cyl_patterns_1(t_data *p, t_world *w,
t_uv_check check);
void						ft_crash(const char *message);
void						cyl_patterns(t_data *p, t_world *w);
void						init_cyl(t_data *p, t_world *w);
void						complex_params_cyl(t_data *p, t_world *w,
char **tab, int flag);
void						texture_plane(char **tab, t_data *p, t_world *w);
void						pattern_color_pl(t_data *p, t_world *w,
char **tab, int flag);
void						plane_patterns(t_data *p, t_world *w);
void						plane_patterns_1(t_data *p, t_world *w,
t_uv_check check);
void						plane_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						plane_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						complex_params_plane(t_data *p, t_world *w,
char **tab, int flag);
void						sphere_patterns(t_data *p, t_world *w);
void						sphere_patterns_1(t_data *p, t_world *w);
void						texture_sp(char **tab, t_data *p, t_world *w);
void						pattern_type_sphere(t_data *p, t_world *w,
char **tab);
void						pattern_color_sp(t_data *p, t_world *w,
char **tab, int flag);
void						sp_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						sp_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						sp_m_rotation(t_data *p, t_world *w,
char **tab1, char **tab2);
void						cone_m_rotation(t_data *p, t_world *w,
char **tab1, char **tab2);
void						init_tri(t_data *p, t_world *w);
void						tri_patterns_1(t_data *p, t_world *w);
void						tri_patterns(t_data *p, t_world *w);
void						texture_tri(char **tab, t_data *p, t_world *w);
void						tri_m_rotation(t_data *p, t_world *w,
char **tab1, char **tab2);
void						pattern_color_tri(t_data *p, t_world *w,
char **tab, int flag);
void						complex_params_tri(t_data *p, t_world *w,
char **tab, int flag);
void						tri_crutch_1(t_data *p, t_world *w,
char **tab, int flag);
void						tri_crutch_2(t_data *p, t_world *w,
char **tab, int flag);
void						tri_crutch_3(t_data *p, t_world *w,
char **tab, int flag);
void						continue_pushing_2(t_data *p, t_world *w);
void						camera_parsing(t_data *p, t_world *w);
void						cycle_cube(t_data *p, t_world *w);

/*
** libft
*/
void						ft_putendl(char const *s);
double						ft_strtodbl(char *s);
int							tab_length(char **tab);
int							ft_atoi(const char *str);
double						ft_strtodbl(char *s);
void						check_tab_len(char **tab);
int							ft_strequ(char const *s1, char const *s2);
int							get_next_line(const int fd, char **line);
char						**ft_strsplit(char const *s, char c);
int							ft_strcmp(const char *str1, const char *str2);
char						*ft_strdup(const char *src);
size_t						ft_strlen(const char *str);
void						ft_bzero(void *s, size_t n);
void						ft_putchar(char c);
void						*ft_memcpy(void *dest, const void *source,
size_t n);
void						*ft_memalloc(size_t size);
char						*ft_strnew(size_t size);
int							ft_words(char const *s, char c);
char						*ft_strjoin(char const *s1, char const *s2);
t_list						*get_live(int fd, t_list **hist);
char						*ft_strchr(const char *str, int ch);
int							ft_len(char const *s, char c);
char						*ft_strndup(const char *s1, size_t n);
int							line_copy(char **line, char *content, char c);

/*
** errors
*/
int							err_wrong_format(void);
int							err_mem_alloc(void);
int							err_trans_matrix(void);
int							err_invalid_file(void);
int							err_num_tex(void);
int							err_empty_line(void);
int							err_empty_file(void);

/*
** utils
*/
int							len_tab(char **tab);
void						print_parameters(t_world *w);

/*
** for if's
*/
int							check_is_obj(char **tab, t_data *p);
int							check_make_obj(char **tab);
int							check_is_light(char **tab, t_data *p);
int							check_is_camera(char **tab, t_data *p);
int							check_make_light(char **tab);

/*
** sopel
*/
int							*ft_gray(t_sdl *sdl);
int							get_pixel(int *sdl, int i, int j);
int							get_sobel_pix(int *sdl, int i, int j);
int							*sobel_op(t_sdl *sdl);
void						cartoon_filter(t_sdl *sdl);
void						draw_ne_vlezlo(t_treads *treads, int x,
int y, t_color *col);

#endif
