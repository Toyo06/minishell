/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:24:17 by sroggens          #+#    #+#             */
/*   Updated: 2023/03/19 17:51:59 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_base	g_base;
//tobefinish
//need to creat a struct with g_base.heredoc.counthere
//need to add to this struct g_base.heredoc.totalheredoc

/*void	heredocthing(t_list **lst)
{
	g_base.heredoc.counthere = countheredoc(lst);
	g_base.heredoc.totalheredoc = g_base.heredoc.counthere;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	while ((*lst)->prev)
	{
		if ((*lst)->prev == 1)
			ft_readline((*lst)->arg);
		(*lst) = (*lst)->prev;
	}
}

void	ft_readline(char *end)
{
	char	*line;
	char	*fulline;
	int 	fdfile;
	int		i;
	char	*fdname;
	char	*nb;
	fulline = NULL;
	nb[0] = g_base.heredoc.counthere + '0';
	nb[1] = '\0';
	fdfile = open(".tmp0", O_CREAT |  O_WRONLY, 0644);
	while (1)
	{
		fdname = ft_strjoin(".tmp", nb);
		fdfile = open(fdname, O_CREAT | O_WRONLY, 0644);
		line = readline("> ");
		if (ft_strcmp(line, end) == 0)
			break ;
		if (fulline == NULL)
		{
			fulline = ft_strdup(line);
			fulline = ft_strjoin(fulline, "\n");
			free(line);
		}
		else
		{
			fulline = ft_strjoin(fulline, line);
			fulline = ft_strjoin(fulline, "\n");
			free(line);
		}
		ft_putstr_fd(fulline, fdfile);
	}
	//unlink(".tmp0");
	free(fdname);
	free(line);
	free(fulline);
	close(fdfile);
	g_base.heredoc.counthere--;
}

int	countheredoc(t_list **lst)
{
	t_list *tmp;
	int	i;

	tmp = (*lst);
	i = 0;
	while (tmp)
	{
		if (tmp->data == 1)
			i++;
		tmp = tmp->next;
	}
	g_base.heredoc.total = i;
}

void	closeheredoc(void)
{
	char	*closerightfd;
	char	*nb;
	while (g_base.heredoc.counthere <= g_base.heredoc.totalheredoc)
	{
		nb[0] = g_base.heredoc.counthere + '0';
		nb[1] = '\0';
		closerightfd = ft_strjoin(".tmp", nb);
		unlink(closerightfd);
}*/

void	countheredoc(t_list **lst)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 1)
			i++;
		tmp = tmp->next;
	}
	g_base.heredoc.countheredoc = 1;
	g_base.heredoc.totalheredoc = i;
	g_base.heredoc.processhere = 0;
	g_base.heredoc.fdout = malloc(sizeof(int) * g_base.heredoc.totalheredoc);
	g_base.heredoc.filename = malloc(sizeof(char *) * g_base.heredoc.totalheredoc);
}

int	counthereinpipe(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	i = 0;
	while (tmp != NULL && tmp->data != 6)
	{
		if (tmp->data == 11)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	heredoc(t_list **lst)
{
	t_list	*tmp;
	char	*line;

	tmp = (*lst);
	while (tmp->next != NULL && tmp->data != 1)
		tmp = tmp->next;
	if (tmp->data == 1)
	{
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(tmp->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		g_base.heredoc.filename[g_base.heredoc.countheredoc] = ft_strdup(tmp->next->arg);
		while (1)
		{
			line = readline("heredoc > ");
			if (ft_strcmp(line, tmp->next->arg) == 0)
				break ;
			ft_putstr_fd(line, g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			ft_putstr_fd("\n", g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			free(line);
		}
		close(g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(tmp->next->arg, O_RDONLY);
		free(tmp->arg);
		tmp->arg = ft_strdup(tmp->next->arg);
		removenextnode(&tmp);
		tmp->data = 11;
		g_base.heredoc.countheredoc++;
		return (0);
	}
	g_base.heredoc.filename[g_base.heredoc.countheredoc] = NULL;
	return (1);
}

void	unlinkheredoc(void)
{
	int	i;

	i = 0;
	while (i <= g_base.heredoc.countheredoc)
		{
			unlink(g_base.heredoc.filename[i]);
			free(g_base.heredoc.filename[i]);
			i++;
		}
	free(g_base.heredoc.filename);
}

void	removenextnode(t_list	**lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp && tmp->data != 1)
		tmp = tmp->next;
	if (tmp->next != NULL && tmp->data == 1)
		{
			tmp = tmp->next;
			if (tmp->next == NULL)
				{
					tmp->prev->next = NULL;
					tmp->next = NULL;
					tmp->next = NULL;
					free(tmp->arg);
					free(tmp);
				}
			else
			{
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp->next;
				tmp->prev = NULL;
				tmp->next = NULL;
				free(tmp->arg);
				free(tmp);
			}				
		}
}