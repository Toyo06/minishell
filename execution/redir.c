#include "../minishell.h"

void	redirection(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	i = 0;
	setvaluered(lst);
	while (tmp)
	{
		if (tmp->data == 4)
		{
			g_base.redir.fdout[i] = open(tmp->next->arg, O_WRONLY | O_TRUNC | O_CREAT , 0644);
			i++;	
			tmp->next->data = 13;
		}
		else if (tmp->data == 3)
		{
			g_base.redir.fdout[i] = open(tmp->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
			tmp->next->data = 13;
			i++;
		}
		tmp = tmp->next;
	}
}

void	setvaluered(t_list **lst)
{
	g_base.redir.totalred = countredir(lst);
	g_base.redir.fdout = malloc(sizeof(int) * g_base.redir.totalred);
	g_base.redir.fdcount = 0;
}

int	countredir(t_list	**lst)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 3 || tmp->data == 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	countredirinpipe(t_list **lst)
{
	t_list *tmp;
	int		i;

	i = 0;
	tmp = (*lst);
	while (tmp && tmp->data != 6)
	{
		if (tmp->data == 3 || tmp->data == 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}