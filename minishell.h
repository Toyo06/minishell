/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:57:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/11 17:27:40 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define CRESET "\e[0m"

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_path
{
	char	**preppath;
	char	*finalpath;
	char	**envtab;
	char	**cmdfull;
	int		fdout;
	int		fdin;
	int		tmpfile;
	int		totalpipe;
	int		pipefd[2];
	int		forkparent;
	int		forkchild;
	int		nbpath;
}				t_path;

typedef struct s_retval
{
	int	code;
}			t_retval;

typedef struct s_sig
{
	char	*str;
}			t_sig;

typedef struct s_list
{
	int				data;
	char			*arg;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_env
{
	char			*content;
	char			*name;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_op
{
	int		i;
	int		j;
	char	quote;
}				t_op;

typedef struct s_quote
{
	int		quote;
	int		simplequote;
	int		doublequote;
	char	nextquote;
	int		returnvalue;
}				t_quote;

typedef struct s_export
{
	t_env	*tmpenv;
	t_list	*tmp;
	int		count;
}				t_export;

typedef struct s_parsing
{
	char	**tab;
}				t_parsing;

typedef struct s_pwd
{
	char	buf[2048];
	char	*pwd;
}				t_pwd;

typedef struct s_exec
{
	int		fd[2];
	int		cpid;
	char	**cmds;
}				t_exec;

typedef struct s_base
{
	t_pwd		pwd;
	t_list		list;
	t_parsing	parsing;
	t_quote		quote;
	t_env		env;
	t_op		op;
	t_export	xport;
	t_exec		pl;
	t_sig		sig;
	t_retval	retval;
	t_path		path;
}				t_base;

/*	-----	Minilib	-----	*/
int		ft_atoi(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isprint(char *str);

/*	-----	Utils	-----	*/
/*	list_utils.c	*/
void	add_node(t_list **head, int nb, char *str);
void	add_next_node(t_list **head, t_list *new_node);
int		count_list(t_list **head);
t_list	*free_list(t_list *lst);
/*	list_prep.c	*/
int		set_lst_data(char *str);
int		double_char(char *str);
int		single_char(char *str);
int		list_prep(t_list **list, char **arr, t_env **env);
/*	va_env.c	*/
void	va_env(t_list **lst, t_env **env);
char	*va_convert(char *str, t_env **env);
char	*va_search(char *new_str, t_env **env, char **arr);
char	*cpy_until_dollar(char *str);
char	*cpy_after_dollar(char *str);
/*	error_msg.c	*/
void	error_msg(int i);
/*	env_utils.c	*/
t_env	*create_node_env(char *name, char *content);
void	add_next_node_env(t_env **head, t_env *new_node);
/*	env_prep.c	*/
void	env_prep(char **envp, t_env **env);
/*	ft_free_arr.c	*/
void	ft_free_arr(char **arr);
/*	ft_getenv.c	*/
char	*ft_getenv(t_env **env, char *str);
/*	ft_update_env.c	*/
void	ft_update_env(t_env **env, char *name, char *content);

/*	-----	Parsing	-----	*/
/*	parsing.c	*/
int		check_sym_err(t_list **lst);
int		err_management(t_list **lst);
/*	parsing_check.c	*/
int		op_count(char *str);
int		op_check(char *str);
int		op_check_bis(char *str);
int		pipe_check(char *str);
/*	forbidden_char_check.c	*/
int		check_forbidden_char(char *str);
/*	quotes_check.c	*/
int		check_quotes(char *str);
int		check_quote_state(void);
/*	quotes_prep.c	*/
char	*prep_quotes(char *str);
char	*revert_nl_to_sp(char *str);
char	**revert_quotes(char **arr);
char	*rm_quote(char *str);
/*	lexer.c	*/
int		check_prompt(char *str, t_list **lst, t_env **env);

/*	-----	Builtins	-----	*/
/*	builtin_env.c	*/
void	ft_printenv(t_env **env);
void	ft_env(t_env **env, t_list **lst);
/*	builtin_echo.c	*/
void	ft_echo(t_list	**lst, int fd);
int		ft_checkoption(char *str);
/*	builtin_exit.c	*/
void	ft_exit(t_list **lst);
int		base_check(int nb);
int		check_nb(char *str);
void	display_exit(int nb, int choice);
int		check_pipes(t_list **lst);
/*	builtin_export.c	*/
void	ft_update_export(t_env **env, char *name, char *content, int eq_flag);
void	ft_export(t_list **lst, t_env **env);
void	ft_printexport(t_env **env);
/*	builtin_export_utils.c	*/
char	*get_arg(char *equal);
char	*ft_trim(char *str);
int		count_quotes(char *str);
int		check_export_arg(char *str);
int		eq_check(char *str);
/*	builtin_unset.c	*/
void	ft_unset(t_env **env, char *str);
void	check_unset(t_list **lst, t_env **env);
int		check_alnum(char *str);
/*	builtin_pwd.c	*/
void	register_pwd(void);
void	ft_pwd(t_list **lst);
/*	dispatch_builtins.c	*/
void	dispatch_builtins(t_list **lst, t_env **env);
/*	builtin_cd.c	*/
void	ft_cd(t_list **lst, t_env **env);

/*	-----	Execution	-----	*/
/*	pipes_utils.c	*/
void	freeforpipe(void);
int		checkpipes(t_list **lst);
void	mallocforthetabtoenv(t_env **env);
void	convertenvtotab(t_env **env);
/*	pipes.c	*/
void	execution(t_list **lst, t_env **env);
int		isitabuiltin(t_list	**lst, t_env **env);
/*	single_pipe.c	*/
void	execonepipe(t_list **lst, t_env **env);
void	singlepipeaction(t_list **tmpb, t_env **env);
void	execone(void);
void	exectwo(void);
/*	single_cmd.c	*/
void	execsimglecmd(t_list **lst, t_env **env);
/*	path_prep.c	*/
void	preparepathforexec(t_env **env, t_list **lst);
void	tabforcmd(t_list **lst);
void	checkaccess(t_list	**lst);
void	checkaccessbis(t_list **lst);
/*	signals.c	*/
void	sig_handler(int sig);
void	sig_block_handler(int sig);
/*	pipeline.c	*/
void	pipeline(t_env **env, t_list **lst);
/*	Extras	*/
void	rl_replace_line(char *str, int i);

extern	t_base g_base;
#endif
