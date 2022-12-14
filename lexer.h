/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:49:35 by sroggens          #+#    #+#             */
/*   Updated: 2022/12/01 13:27:02 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

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
}			t_op;

typedef struct s_quote
{
	int		quote;
	int		simplequote;
	int		doublequote;
	char	nextquote;
}				t_quote;

typedef struct s_parsing
{
	char	**tab;
}				t_parsing;

typedef struct s_pwd
{
	char	*pwd;
}				t_pwd;

typedef struct s_exec
{
	int	fd[2];
	int	cpid;
} t_exec;

typedef struct s_base
{
	t_pwd		pwd;
	t_list		list;
	t_parsing	parsing;
	t_quote		quote;
	t_env		env;
	t_op		op;
	t_exec		pl;
}				t_base;
void	ft_env(t_env **env, t_list **lst);
void	ft_printenv(t_env **env);
void	ft_pwd(t_list **lst);
void	ft_exit(t_list **lst);
void	checkredir(t_list **lst);
void	registerpwd(t_env **env);
int		errormanagement(t_list **lst);
//**************************************************
//*************lexer_opcheck.c**********************
//**************************************************
int		lexercheckcond(char *str);
void	setvalueforop(void);
int		countmallocstr(char *str);
char	*addspace_be_foreop(char *str);
//**************************************************
//**************Tool_bis.c**************************
//**************************************************
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//**************************************************
//*************Prepa_env.c**************************
//**************************************************
void	ft_setenv(char **env);
void	prepaenv(char **envp, t_env **env);
//**************************************************
//************Tool_list_env.c***********************
//**************************************************
void	unsetonlistenv(t_env **env, char *str);
void	printthelistenv(t_env **head);
void	addnodeenv(t_env **head, char	*name, char *content);
void	addnextnodeenv(t_env **head, t_env *new_node);
//**************************************************
//**************Lexer.c*****************************
//**************************************************
char	*removequote(char *str);
int		checkthestart(char *str, t_list **lst);
//***************************************************
//***************Tool_list.c*************************
//***************************************************
int		countlist(t_list **head);
void	printthelist(t_list **head);
void	addnextnode(t_list **head, t_list *new_node);
t_list	*freelist(t_list *lst);
void	addnode(t_list **head, int nb, char *str);
//***************************************************
//**************Ft_split.c***************************
//***************************************************
char	**ft_split(char const *s, char c);
//***************************************************
//**************Tool.c*******************************
//***************************************************
char	*ft_strdup(char *src);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
//***************************************************
//******************Printf_part1.c*******************
//***************************************************
void	ft_putcharprintf(char c, int *counter);
int		ft_printf(const char *txt, ...);
//***************************************************
//******************Printf_part2.c*******************
//***************************************************
void	ft_selectnextwords(va_list params, char txt, int *count);
//***************************************************
//*************Quote_detector.c**********************
//***************************************************
int		checkquote(char *str);
int		closeornot(void);
//***************************************************
//**************Forbidencharact.c********************
//***************************************************
int		checkforbiden(char *str);
//***************************************************
//*****************Prepalist.c***********************
//***************************************************
char	*addspace(char *oldstr);
char	*mallocstrneeded(char *oldstr);
//***************************************************
//*************Prepa_list.c**************************
//***************************************************
void	prepalist(t_list **list, char **tab);
int		selectforlist(char *str);
//***************************************************
//****************spacebeforeoperateur*tobenorn*.c***
//***************************************************
char	*addspace(char *oldstr);
char	*mallocstrneeded(char *oldstr);
//***************************************************
//***************entrecote*tobenorm*.c***************
//***************************************************
char	**mallocnewtab(char **tab);
char	**ifquoteordoublequote(char **tab);
//***************************************************
//*************removelesstabs.c**********************
//***************************************************
char	*removeuslesstabandspace(char *oldstr);
char	*mallocwithouttab(char *oldstr);
//***************************************************
//*************errormess.c***************************
//***************************************************
void	errormess(int i);
void	ft_putstr_fd(char *s, int fd);
//***************************************************
//************Quote_preparateur.c********************
//***************************************************
char	**rechangebetweenquote(char **tab);
char	*changebetweenquote(char *str);
char	*replacebetweenquote(char *str);
//***************************************************
//************ft_strcmp.c****************************
//***************************************************
int		ft_strcmp(const char *s1, const char *s2);
//***************************************************
//************exec_cmds.c****************************
//***************************************************
int		execcmd(t_list **lst, t_env **env);
void	cprocess(t_list **lst, t_env **env);
void	ft_exec(char *arg, t_env **env);
char	*get_path(char *cmd, t_env **env);
char	*check_path(char *cmd, char *envp_path);
//***************************************************
//************parsing.c******************************
//***************************************************
int		check_heredoc(t_list **lst);
#endif
