/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 10:26:07 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>

/*
** --------------------------------------------------------------
** include de fichiers entête 'externe'
** --------------------------------------------------------------
*/
//#include <sys/types.h>
#include <stdbool.h>

/*
** [Put some explanations]
*/
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "error_messages.h"

/*
** fichier entête du sujet corewar (ressources)
*/
#include "op.h"
//#include "op_tab.h"

/*
** --------------------------------------------------------------
** Macros des auteurs, des structures et prototypes des fonctions
** --------------------------------------------------------------
*/

# define RELATIVE 10
# define DUMP_SIG -20

/*
** structure pour exploiter le fichier op.c
*/

typedef struct					s_op
{
	char				*name;
	size_t				n_arg;
	size_t				type[MAX_ARGS_NUMBER];
	size_t				code;
	size_t				cycle;
	char				*desc;
	size_t				encod;
	size_t				direct_size;
}								t_op;

/*
** Définition des structures de la partie vm (parsing etc...)
*/

typedef struct		s_options
{
	bool			dump;
	ssize_t			dump_cycle;
	bool			n;
	bool			aff;
	bool			verbose;
	u_int8_t		v_lvl;

}					t_options;

typedef struct		s_champ
{
	int				id;
	char			*champ_file;
	char			*name;
	char			*comment;
	int				l_bytecode;
	char			*bytecode;
	int				mem_pos;
}					t_champ;

typedef struct		s_parse
{
	int				nb_champ;
	int				id_champ;
	int				*id_table;
	t_options		*options;
	t_list			*lst_champs;
	char			**error;
}					t_parse;

typedef struct		s_process
{
	int				id;				// unique to each process
	bool			carry;			// flag carry= which can be changed by certain operations and which affects zjmp operation, initialised with value false.
	int				opcode;			// operation code, before the battle starts it is not initialised. use define and table of correspondance to stock the opcode read and to find the info in op_tab[17]
	int				n_lives;		// number of lives the process performed DURING THE CURRENT CYCLE_TO_DIE period, meaning that when cw->cycle_to_die becomes 0, value is reset to 0.
	int				wait_cycles;	// amount of cycles to wait before operation execution.
	int				i;				// i is the index of the process in the cw->arena
	int				jump;			// amount of bytes cursor must jump to get to the next operation
	int				pc;				// program counter = register that load the next opcode address that will be executed for the current process
	int				*registers;		// 16 registers for a process/cursors of 4 bytes each.
	t_champ			*champ;
}					t_process;

typedef struct		s_corewar
{
	char			*arena;			// memory area where champion will fight until death
	int				*id_arena;		// memory area where id champion are placed on the arena to keep a track of which champion occuped which bytes.id des champs a chaque case.
	t_list			*process;		// "incarnation of the champion", part which will read & execute the champion code (~ish, not exactly)
	int				cycle_to_die;	// 
	int				tot_lives;		// If the number of lives performed by the processes reachs nb-lives, cycle_to_die is decreased by delta_cycle. (total)
	int				n_champ;		// number of champions in the arena = to nb_champ of parse structure.
	int				champ_lives[4];	// Cumulated number of lives for each champion.
	int				i_check;		// Number of check to perform before cycle_to_die is decreased (no matter if nb_lives is reached or not)
	int				i_cycle;
	t_options		options;			// struct with options
}					t_cw;

/*
**
*/

typedef struct		s_visu
{
	SDL_Window		*screen;
	SDL_Renderer	*r;
	int				isquit;
	SDL_Event		event;
	Mix_Music		*musique;
/*
**Menu data
*/
	SDL_RendererFlip	flip;
	TTF_Font		*font_menu;
	SDL_Rect		menu_pos;
	TTF_Font		*menu_font;
	SDL_Surface		*menu_txt;
	SDL_Texture		*menu_vt;
	SDL_Color		menu_color;
	SDL_Point		center;
	int				menu_loop;
	double			angle;
/*
**Title data
*/
	TTF_Font		*font_title;
	SDL_Surface		*text_title;		//window title;
	SDL_Texture		*texture_title;	
	SDL_Rect		position;		//Coo for title rect
	SDL_Color		color_title;
/*
**Chp data
*/
	SDL_Color		color_chp[4];
    SDL_Color		chp_color;
	SDL_Rect		chp_id[4];	//Rect for champion info
	SDL_Rect		chp_info[36];
	TTF_Font		*font_p;
	SDL_Surface		*chp_name[4];
	SDL_Texture		*chp_vn[4];
	SDL_Rect		chp_cs[4];
	SDL_Surface		*chp_size[4];
	SDL_Texture		*chp_vs[4];

/*
**Arena data
*/
	SDL_Color		color_arena;
	SDL_Color		color_process;
	TTF_Font		*arena_font;
	SDL_Rect		arena_rect;
	SDL_Rect		arena_pos[MEM_SIZE];
	SDL_Surface		*arena_txt[MEM_SIZE];
	SDL_Texture		*arena_vs[MEM_SIZE];
	char			*dst;   //prep arena in SDL(malloc);
	char 			*final; //arena in SDL(malloc);
	int				count;  //go to next line in arena;
	int				chp_n; //champion id for color;
/*
**process data
*/
	SDL_Color		color_id;
	TTF_Font		*font_process;
	SDL_Rect		process_id;  //Rect for process id info
	SDL_Rect		process_rect;
	SDL_Rect		process_coo[3];
	SDL_Rect		process_tc[3];
	SDL_Surface		*process_name[3];
	SDL_Surface		*process_title[3];
	SDL_Texture		*process_vn[3];
	SDL_Texture		*process_vt[3];
/*
**Render data
*/
	int				i;

}					t_visu;

/*
** Prototypes de fonctions temporaires, à retirer avant de push sur la vogsphere.
*/
void				tool_print_parsing(t_parse *p);										// a retirer
void				tool_print_champ(t_champ *champ);									// a retirer
void				tool_print_champ_list(t_list *lst_champs);							// a retirer
void				tool_print_arena(char *arena, size_t mem_size, t_parse *p);			// a retirer
void				tool_print_id_arena(int *id_arena, size_t mem_size, t_parse *p);	// a retirer
void				tool_print_processor(t_process *process, int nb);					// a retirer
void				tool_print_all_processors(t_list *processes);						// a retirer
void				tool_print_short_processors(t_cw *cw);								// a retirer

/*
** Prototypes des fonctions du manager d'erreurs [vm_error_manager.c]
*/
int					vm_error_manager(int code_error, char **error);
int					vm_init_parse_error(int code_error, t_parse **p);	// print error message if memory allocation issue at initialization
int					vm_init_cw_error(int cd_error, t_cw **cw);

/*
** Prototypes des fonctions de parsing des arguments en STDIN
*/
int					vm_parsing(char **av, t_parse *p);
int					vm_init_parse(t_parse **p);
int					vm_create_champion(t_list **lst_champs, char *av, t_parse *p);
int 				is_valid_champ_filename(char* filename);

/*
** Prototypes des fonctions de parsing des fichiers des champions
*/
int					vm_champ_parse(t_list **lst_champs, char **error);
int					get_champ_magic_key(int fd);
char				*get_champ_name(int fd);
char				*get_champ_comment(int fd);
int					get_champ_l_bcode(int fd);
char				*get_champ_bcode(int fd, int l_bcode);

/*
** Prototypes des fonctions [initialization et chargement] de l'arene et des cursors
*/
int					vm_cw_arena_init(t_cw **cw, t_parse **p);
void				copy_options(t_cw *cw, t_parse *p);

/*
** Lancement et déroulement de corewar.
*/
void				vm_champion_introduction(t_list *lst_champs);
int					vm_execution(t_cw *cw, t_parse *p);
void				vm_exec_init_pc(t_cw *cw);
bool				is_valid_encoding(u_int8_t opcode, u_int8_t encoding);
int					instruction_width(unsigned char encoding, size_t dir_s);

/*
** Fonctions outils concernant les opcode
*/
bool				is_valid_opcode(char *arena, t_process *cur_proc);
int					arg_size_opcode_no_encode(u_int8_t opcode);
bool				opcode_no_encoding(u_int8_t opcode);
int					addr_next_opcode(char *arena, int mem_pos);
void				perform_opcode(t_cw *cw, t_process *cur_proc);

/*
** Fonctions outils concernant l'octet d'encodage
*/
int					get_nb_arg_b_encoding(u_int8_t encoding);
bool				is_valid_encoding(unsigned char opcode, unsigned char encoding);
bool				is_valid_reg(char *arena, t_process *p);

/*
** Fonctions concernant le déroulement des processus au sein de la VM
*/
void				vm_proc_cycle(t_cw *cw);
void				vm_proc_perform_opcode(t_cw *cw);
void				vm_proc_mv_proc_pos(t_cw *cw);
int					vm_proc_get_lives(t_cw *cw);
void				vm_proc_set_lives(t_cw *cw, int set);
void				vm_proc_kill_not_living(t_cw *cw);
void				free_one_process(t_list **lst_proc, int id);
bool				vm_proc_only_one_standing(t_cw *cw);

/*
** Fonctions pour effectuer les instructions asm dans l'arene
*/
int					op_alive(t_cw *cw, t_process *cur_proc);
int					op_load(t_cw *cw, t_process *cur_proc);
int					op_store(t_cw *cw, t_process *cur_proc);
int					op_addition(t_cw *cw, t_process *cur_proc);
int					op_soustraction(t_cw *cw, t_process *cur_proc);
int					op_and(t_cw *cw, t_process *cur_proc);
int					op_or(t_cw *cw, t_process *cur_proc);
int					op_xor(t_cw *cw, t_process *cur_proc);
int					op_zerojump(t_cw *cw, t_process *cur_proc);
int					op_load_index(t_cw *cw, t_process *cur_proc);
int					op_store_index(t_cw *cw, t_process *cur_proc);
int					op_fork(t_cw *cw, t_process *cur_proc);
int					op_long_load(t_cw *cw, t_process *cur_proc);
int					op_long_load_index(t_cw *cw, t_process *cur_proc);
int					op_long_fork(t_cw *cw, t_process *cur_proc);
int					op_aff(t_cw *cw, t_process *cur_proc);
int					fork_creation_process(t_cw *cw, t_process *cur_proc, int addr);
int					get_arg_value(char *arena, t_process *cur_proc, int index, int type);

/*
** Fonctions pour la gestion des options de ./corewar
*/
int					dump_memory(char *arena);

/*
**<<<<<<<<<<<<<<<<<<<<<Bonus Functions>>>>>>>>>>>>>>>>>>>>
**
**<<<<<Verbosity>>>>>
*/

int    				init_verbotab(t_cw *cw, void *ptr, int flag);
int     			vprint_essentials(t_cw *cw, void *ptr,int flag);
int     			vprint_lives(t_cw *cw, void *ptr, int flag);
int     			vprint_cycle(t_cw *cw, void *ptr, int flag);
int     			vprint_op(t_cw *cw, void *ptr, int flag);
int     			vprint_deaths(t_cw *cw, void *ptr, int flag);
int     			vprint_pcmv(t_cw *cw, void *ptr, int flag);

/*
**<<<<<Visualizer functions>>>>>
**
**<<<<<Window functions>>>>>
*/

void				init_window(t_visu *v);
t_visu				init_visu(t_visu *v);
void				load_title(t_visu *v);
void     			visualizer(t_parse *p, t_cw *cw);
double    			menu_move(t_visu *v, double angle);
void    			load_menu(t_visu *v);
t_visu  			init_menu(t_visu *v);
void				load_visu(t_visu *v, t_parse *p, t_cw *cw);

/*
**<<<<<Champions functions>>>>>
*/
t_visu				init_id(t_visu *v, t_parse *p);
void				load_chp(t_visu *v, t_parse *p);

/*
**<<<<<Arena functions>>>>>
*/

t_visu				init_arena(t_visu *v);
void				load_arena(t_visu *v, t_cw *cw);

/*
**<<<<<Render functions>>>>>
*/

void				visu_render(t_visu *v, t_parse *p);
void				render_destroy(t_visu *v);
void				render_destroy(t_visu *v);
void				texture_free(t_visu *v);

/*
**<<<<<Process info functions>>>>>
*/

t_visu				init_process(t_visu *v);
void				load_process(t_visu *v, t_cw *cw);

/*
**<<<<<Tools>>>>>
*/

char				*ft_itoa_base2(unsigned long long nb, char *base);
void				main_exe(t_visu *v, t_parse *p, t_cw *cw);
void    			music_launcher(t_visu *v);
t_visu				visu_breaker(t_visu *v);
t_visu				visu_breaker2(t_visu *v);
t_visu				init_details(t_visu *v);

#endif