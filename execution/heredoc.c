/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:24:17 by sroggens          #+#    #+#             */
/*   Updated: 2023/03/09 23:24:49 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "lexer.h"

t_base	g_base;
//tobefinish
//need to creat a struct with g_base.heredoc.counthere
//need to add to this struct g_base.heredoc.totalheredoc

void	heredocthing(t_list **lst)
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
