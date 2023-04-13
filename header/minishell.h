/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/13 12:52:48 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/header/libft.h"

typedef struct s_env_main
{
	char				**env;
	int					last_cmd_status;
	struct s_env_var	*env_list;
	struct termios		*tty;
}	t_env_main;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_env_pipe
{
	int	input;
	int	output;
	int	infile;
	int	outfile;
	int	nbr_cmd;
	int	actual_pipe;
	int	hdoc;
	int	*pid;
	int	**fd;
	int	i;
}	t_env_pipe;

typedef struct t_lst
{
	char			*data;
	struct t_lst	*next;
}	t_lst;

typedef struct t_cmd
{
	char	*cmd;
	t_lst	*flag;
	t_lst	*content;
	t_lst	*infile;
	t_lst	*outfile;
}	t_cmd;

typedef struct t_line
{
	t_cmd	*cmd;
	char	***all_cmd;
	int		nbr_cmd;
	t_lst	*infile;
	t_lst	*outfile;
}	t_line;

typedef enum t_boolean
{
	FALSE = 0,
	TRUE
}	t_boolean;

/*Init*/
void		init_main_env(t_env_main *main_env, char **env);

/*Parsing*/
int			parsing(char *line, t_line *all_cmd, t_env_main *main_env);
int			split_line(char *line, t_line *all_cmd);
int			input_operator_check(char *cmd);
char		*check_if_pipe_error(char *line);
int			get_cmd(char *line, t_cmd *cmd);
int			get_file(char *line, t_cmd *cmd);
int			get_flag(char *line, t_cmd *cmd);
int			get_content(char *line, t_cmd *cmd);
char		*copy_cmd(int size, char *src, char *dest);
int			skip_space(char *line);
int			count_len(char *line, char del, int *nbr_quote);
int			get_size(char *line, int *size);
int			lst_add_back(t_lst **lst, t_lst *new);
t_lst		*lst_new(void *content);
void		print_cmd(int i, t_line all_cmd);
int			convert_in_3d_array(t_line *all_cmd);
void		free_cmd_struct(t_line *all_cmd);
char		*replace_global_variable(char *line, t_env_main *main_env);
int			count_nbr_char(char *line, t_env_var *env_list);
void		skip_simple_quote(int *index, int *nbr_char, char *line);
int			count_alpha(char *line);
void		skip_gobal_variable(int *index, char *line);
void		incrementation(int *index, int *nbr_char, char c);
int			check_if_not_special_case(char *line, int *i_line, \
			char *final_line, t_env_main *main_env);
int			skip_char(char *line, char c);
char		**split_skip_quote(char *str);

/*Signal*/
void		signal_handler(t_env_main *env_main);
void		termios_init(t_env_main *main_env);

/*Exec cmd*/
void		exec_hub(t_line *all_cmd, t_env_main *main_env);
char		**cmd_to_send(t_line *all_cmd);
int			create_outfiles(t_lst *outfile);
int			open_files(t_env_pipe *st, t_line *all_cmd);
int			setup_struct_cmd(t_env_pipe *st, t_line *all_cmd);
int			dup_manager(t_env_pipe *st);
int			get_dup_single_done(t_env_pipe *st);
char		*get_path(char *cmd, char *paths);
void		no_path(t_env_pipe *st, char **cmd);
void		path_is_null(t_env_pipe *st, char **cmd, char *str);
int			execution(t_line *all_cmd, t_env_pipe *st, t_env_main *main_env);
int			get_exec_done(char **cmd, t_env_pipe *st, t_env_main *main_env);
int			error_execve(char **cmd, char *path, t_env_pipe *st);
void		free_env(t_env_pipe *st, int i);
void		free_pipe(t_env_pipe *st);
void		close_function(t_env_pipe *st);
int			quit_function(t_env_pipe *st, int error_code);

/*Heredoc*/
int			setup_heredoc(t_env_pipe *st, t_line *all_cmd);
int			heredoc(t_env_pipe *st, t_line *all_cmd);
char		*get_delimiter(char *str);

/*Builtins*/
void		ft_echo(char **cmd, t_env_main *main_env);
void		ft_cd(char **cmd, t_env_main *main_env);
void		ft_pwd(char **cmd, t_env_main *main_env);
t_env_var	*ft_export(char **cmd, t_env_var *env_list, t_env_main *main_env);
t_env_var	*ft_unset(char **cmd, t_env_var *env_list, t_env_main *main_env);
void		ft_env(char **cmd, t_env_var *env_list, t_env_main *main_env);
void		ft_exit(char **cmd, t_env_main *main_env);

/*Utils lst*/
t_env_var	*ft_lstnew_env(char *name, char *value);
void		ft_lstadd_front_env(t_env_var **lst, t_env_var *new);
void		ft_lst_addback_env(t_env_var **lst, t_env_var *new);
int			ft_lstsize_env(t_env_var *lst);
t_lst		*lst_last(t_lst *lst);
int			ft_lstsize_file(t_lst *lst);

/*Utils*/
int			cmd_size(char **cmd);
int			get_total_cmd(t_line *all_cmd);
char		*setup_file(char *raw_file);

/*Free utils*/
void		free_str(char **str);
void		free_cmd(t_line *all_cmd);
void		free_all_exit(t_env_main *main_env);
void		free_inout_list(t_lst *lst);

/*A DELETE*/
void		print_tab(char **tab);
void		print_list_delete(t_lst *lst);

#endif