/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:57:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 20:32:13 by mayyildi         ###   ########.fr       */
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

# define ECHO_P "/bin/echo"
# define PWD_P "/bin/pwd"
# define ENV_P "/usr/bin/env"
# define CD_P "/usr/bin/cd"

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stddef.h>
# include <termios.h>
# include <sys/ioctl.h>

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
	int	pxit;
	int	pcd;
	int	inp;
	int	pbuilt;
}			t_retval;

typedef struct s_sig
{
	char	*str;
}			t_sig;

typedef struct s_main
{
	int	k;
	int	fd;
}				t_main;

typedef struct s_list
{
	int				data;
	char			*arg;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_redir
{
	int		*fdout;
	int		totalred;
	int		fdcount;
	int		i;
}				t_redir;

typedef struct s_spaceoppipe
{
	int		i;
	int		j;
	int		quote;
	char	*rtv;
}				t_spaceoppipe;

typedef struct s_env
{
	char			*content;
	char			*name;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_strjoin
{
	int		i;
	int		j;
	char	*str;
}				t_strjoin;

typedef struct s_op
{
	int		i;
	int		j;
	char	quote;
	int		liststate;
}				t_op;

typedef struct s_quote
{
	int		quote;
	int		simplequote;
	int		doublequote;
	char	nextquote;
	int		returnvalue;
}				t_quote;

typedef struct s_dol
{
	char	*strret;
	char	*beforedol;
	char	*end;
	int		nullpo;
}			t_dol;

typedef struct s_export
{
	t_env	*tmpenv;
	t_list	*tmp;
	int		count;
	char	*eq;
	int		eq_fl;
	char	*arg;
	int		disp2;
}				t_export;

typedef struct s_echo
{
	int		option;
}				t_echo;

typedef struct s_cd
{
	t_list	*tmp;
	char	*path;
	int		arg_count;
	char	cwd[2048];
}				t_cd;

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

typedef struct s_heredoc
{
	int		*fdout;
	int		totalrealheredoc;
	int		countheredoc;
	int		countalldoc;
	char	**filename;
	int		totalheredoc;
	int		processhere;
	int		countreforset;
	int		countallforset;
	int		sign;
}				t_heredoc;

typedef struct s_rmquote
{
	int		i;
	char	*new_str;
	int		j;
}				t_rmquote;

typedef struct s_sym_err
{
	int		count;
}				t_sym_err;

typedef struct s_multipipe
{
	int		totalpipe;
	int		i;
	int		fdin;
	int		fdout;
	int		j;
	int		k;
	int		l;
	int		status;
	int		**pipefd;
	int		*forkfd;
}				t_multipipe;

typedef struct s_base
{
	t_rmquote		rmquote;
	t_sym_err		err;
	t_main			main;
	t_strjoin		strjoin;
	t_dol			dol;
	t_spaceoppipe	spaceoppipe;
	t_multipipe		multipipe;
	t_redir			redir;
	t_heredoc		heredoc;
	t_pwd			pwd;
	t_list			list;
	t_parsing		parsing;
	t_quote			quote;
	t_env			env;
	t_op			op;
	t_export		xport;
	t_echo			echo;
	t_cd			cd;
	t_exec			pl;
	t_sig			sig;
	t_retval		retval;
	t_path			path;
	sig_atomic_t	sigint_received;
	sig_atomic_t	sigterm_received;
	sig_atomic_t	sigquit_received;
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
char	*ft_strjoin(char *s1, char *s2);
void	setvalueforjoin(void);
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
/*	env_prep.c	*/
void	env_prep(char **envp, t_env **env);
void	err_msg_pwd(int i);
int		checkeight(t_list **tmp);
/*	env_utils.c	*/
t_env	*create_node_env(char *name, char *content);
void	add_next_node_env(t_env **head, t_env *new_node);
/*	error_msg.c	*/
void	error_msg(int i);
void	err_msg_cd(int i);
void	err_msg_exit(int i);
void	err_msg_export(int i);
void	err_msg_unset(int i);
/*	ft_free_arr.c	*/
void	ft_free_arr(char **arr);
/*	ft_getenv.c	*/
char	*ft_getenv(t_env **env, char *str);
/*	ft_update_env.c	*/
void	ft_update_env(t_env **env, char *name, char *content);
/*	list_prep.c	*/
int		set_lst_data(char *str);
int		double_char(char *str);
int		single_char(char *str);
int		list_prep(t_list **list, char **arr);
/*	list_utils.c	*/
void	add_node(t_list **head, int nb, char *str);
void	add_next_node(t_list **head, t_list *new_node);
int		count_list(t_list **head);
t_list	*free_list(t_list *lst);
void	printthelist(t_list **head);
/*	va_env.c	*/
void	va_env(t_list **lst, t_env **env);
void	va_convert(t_list **lst);
char	*va_search(char *new_str, t_env **env, char **arr);
char	*cpy_until_dollar(char *str);
char	*cpy_after_dollar(char *str);

/*	-----	Parsing	-----	*/
/*	forbidden_char_check.c	*/
void	singlequotechecker(char *str);
size_t	countmallocnewstring(char *str);
void	doublequotechecker(char *str);
/*	forbidden_char_checkbis.c	*/
int		check_forbidden_char(char *str);
void	setvalueforquotepipe(void);
void	checkstatusquotepipe(char *str);
char	*addspacewhenneededpipe(char *str);
void	addspacewhenneededbro(void);
/*	lexer.c	*/
int		checkfilecannotbeopen(t_list **lst, char *str);
int		deletenodeforerror(t_list **lst);
void	movelistiferror(t_list **lst);
void	fileerror(t_list **tmp);
int		freestrerror(char *str);
/*	lexerbis.c	*/
int		check_prompt(char *str, t_list **lst, t_env **env);
int		deletenullarg(t_list **lst);
int		freenullargbis(t_list **lst);
int		splitingforquote(char *str);
/*	parsing_check.c	*/
int		op_count(char *str);
int		op_check(char *str);
int		op_check_bis(char *str);
int		pipe_check(char *str);
/*	parsing.c	*/
int		checktwofour(void);
int		checkthree(void);
int		checksix(void);
int		check_sym_err(t_list **lst);
int		err_management(t_list **lst);
/*	quotes_check.c	*/
int		check_quotes(char *str);
int		check_quote_state(void);
int		checkererrorparsing(t_list **lst);
/*	quotes_prep.c	*/
void	sortrm(char *str);
char	*prep_quotes(char *str);
char	*revert_nl_to_sp(char *str);
char	**revert_quotes(char **arr);
char	*rm_quote(char *str);
/*	single_quotebis.c	*/
int		countdolmal(char *str);
char	*finalstringdol(char *str, t_env **env);
int		countmallocend(char *str);
int		countbefdol(char *str);
/*	single_quote.c	*/
void	replacedol(char *str);
char	*checkdol(char *str, t_env **env);
void	beforedol(char *str);
void	afterdol(char *str);
void	checkenvdol(t_env **env);

/*	-----	Builtins	-----	*/
/*	builtin_cd.c	*/
void	ft_cd(t_list **lst, t_env **env);
void	ft_cd_p(t_list **lst);
void	handle_err(int err_code);
/*	builtin_echo.c	*/
void	ft_echo(t_list	**lst, int fd);
int		prepare_echo(t_list **lst, t_list **tmp, int fd);
void	print_echo_output(t_list **tmp, int fd);
/*	builtin_echo_utils.c	*/
int		ft_checkoption(char *str);
void	handle_echo_option(t_list **tmp);
int		check_echo_option(t_list *tmp);
/*	builtin_env.c	*/
void	ft_printenv(t_env **env, int fd);
void	ft_env(t_env **env, t_list **lst, int fd);
/*	builtin_exit.c	*/
void	ft_exit(t_list **lst, int fd);
void	handle_exit_cmd(t_list *tmp, int fd);
void	handle_exit_multiple_args(t_list *tmp, int fd);
void	handle_exit_zero_args(t_list *tmp, int fd);
/*	builtin_exit_utils.c	*/
void	exit_condition(int n);
int		base_check(int nb);
int		check_nb(char *str);
void	display_exit(int nb, int choice, int fd);
int		check_exit_args(t_list **lst);
/*	builtin_export.c	*/
void	ft_update_export(t_env **env, char *name, char *content, int eq_flag);
void	ft_export(t_list **lst, t_env **env, int fd);
void	ft_printexport(t_env **env, int fd);
/*	builtin_export_utils.c	*/
char	*get_env_var(char **arr, t_env **env);
char	*get_arg(char *equal, t_env **env);
char	*ft_trim(char *str);
int		count_quotes(char *str);
void	ft_export_bis(t_list **lst, t_env **env, int fd);
/*	builtin_export_utils_bis.c	*/
int		check_export_arg(char *str);
int		sp_check(char *str);
int		check_env_var(char *str);
int		check_arg_validity(char *str);
void	print_export_condition(t_list *tmp, t_env **env, int fd);
/*	builtin_export_utils_bis2.c	*/
void	update_export_eq(t_list *tmp, t_env **env);
/*	builtin_pwd.c	*/
void	register_pwd(void);
void	print_pwd(int fd);
void	ft_pwd_p(t_list **lst, int fd);
void	ft_pwd(t_list **lst, int fd);
void	ft_pwd_p(t_list **lst, int fd);
/*	builtin_unset.c	*/
int		check_unset_arg(char *str);
void	ft_unset(t_env **env, char *str);
void	check_unset(t_list **lst, t_env **env);
int		check_alnum(char *str);
/*	dispatch_builtins.c	*/
int		isitabuiltin(t_list	**lst, t_env **env, int fd);
int		check_builtin(char *arg);
void	isitabuiltin_bis(t_list **lst, t_env **env, int fd);
void	dispatch2(t_list **lst, t_env **env, int fd);
int		check_dispatch2(t_list **lst, t_env **env, int fd);
int		check_builtin(char *arg);
/*	dispatch_utils_bis.c	*/
int		dispatch(t_list **lst, t_env **env, int fd);
int		check_b_env(t_list **lst, t_env **env, int fd);
int		check_b_cd(t_list **lst, t_env **env);
/*	dispatch_utils.c	*/
int		check_b_unset(t_list **lst, t_env **env);
int		check_b_pwd(t_list **lst, int fd);
int		check_b_export(t_list **lst, t_env **env, int fd);
int		check_b_exit(t_list **lst, int fd);
int		check_b_echo(t_list **lst, int fd);

/*	-----	Execution	-----	*/
/*	heredoc.c	*/
int		controlcheredoc(void);
int		sinplehere(t_list **lst);
int		doubleredir(t_list **lst);
/*	heredocbis.c	*/
void	removenextnode(t_list	**lst);
int		counthereinpipe(t_list **lst);
void	unlinkheredoc(void);
int		heredocexec(t_list *tmp);
/*	heredocbis2.c	*/
int		heredoc(t_list **lst);
void	countheredoc(t_list **lst);
void	countmuchhere(t_list *tmp, t_list **lst);
/*	path_prep.c	*/
void	preparepathforexec(t_env **env, t_list **lst);
void	tabforcmd(t_list **lst);
void	checkaccess(t_list	**lst, t_env **env);
int		mallocfortab(t_list *tmp);
/*	path_prep_utils.c	*/
t_list	*find_next_valid_node(t_list **lst);
void	cutingacessbis(t_list **tmp, int i);
void	free_preppath_from_index(int index);
void	path_not_found(t_list **lst);
void	checkaccessbis(t_list **lst);
/*	pipeline.c	*/
void	pipeline(t_env **env, t_list **lst, int fd);
void	setmultipipeval(t_list **tmp, t_env **env);
void	envofpipeline(void);
/*	pipelinebis.c	*/
void	setvaluemultipipe(t_list **lst);
void	multipipechild(t_list *tmp);
void	multipipesend(void);
void	startingpipe(t_list **tmp, t_env **env);
void	execvething(t_list **lst, t_env **env, int fd);
/*	pipelinebis2.c	*/
void	closeredir(void);
void	closeheredoc(void);
void	mallocpipeline(void);
void	freepipeline(void);
void	actionpipeline(t_list **lst, t_env **env, int fd);
/*	pipes_utils.c	*/
void	freeforpipe(void);
int		checkpipes(t_list **lst);
void	mallocforthetabtoenv(t_env **env);
void	convertenvtotab(t_env **env);
/*	pipes.c	*/
void	execution(t_list **lst, t_env **env, int fd);
int		check_if_empty(t_list **lst);
/*	redir.c	*/
void	setvaluered(t_list **lst);
int		countredir(t_list	**lst);
void	redirection(t_list **lst);
int		countredirinpipe(t_list **lst);
/*	signals.c	*/
void	sig_handler(int sig);
void	sig_block_handler(int sig);
void	sig_heredoc(int sig);
void	simulate_return_key_press(void);
/*	single_cmd.c	*/
void	setsinglecmd(t_list **lst);
void	execsimglecmd(t_list **lst, t_env **env, int fd);
void	execsinglechild(t_list **lst, t_env **env, int fd);
void	closesinglecmd(void);
/*	single_pipe.c	*/
void	impsingle(t_list **tmpb, t_env **env);
void	execonepipe(t_list **lst, t_env **env, int fd);
void	execone(t_list **lst, t_env **env, int fd);
void	execonepipebis(t_list **tmpb, t_env **env, int status, int fd);
void	singlepipesign(int status);
/*	singlepipebis.c	*/
void	singlepipeaction(t_list **tmpb, t_env **env);
void	exectwo(t_list **lst, t_env **env, int fd);

/*	main.c	*/
int		checklinespace(char *str);
int		checklinespace(char *str);
void	freeendofloop(t_list **lst);
void	lunchingexec(t_list **lst, t_env **env);
void	lunchingloopthings(t_list **lst, t_env **env);

/*	Extras	*/
void	executionstart(t_list **lst, t_env **env);
int		isitabuiltinbis(t_list	**lst, t_env **env);
void	accessfree(int i);
void	taberrorprint(t_list **lst);
void	remove_newline(void);
void	rl_replace_line(char *str, int i);
extern t_base	g_base;
#endif
