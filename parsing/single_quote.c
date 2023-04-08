#include "../minishell.h"

char	*checkdol(char *str, t_env **env)
{
	int	i;
	char	*retstr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			{
				if (str[i + 1] == '\0')
					return (str);
				i++;
				while (str[i] != '\'')
				i++;
			}
		if (str[i] && str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
			{
				printf("here\n");
				retstr = finalstringdol(str, env);
				return (retstr);
			}
		if (str[i] != '\0')
			i++;
	}
	return (str);
}

int	countbefdol(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	return (i);
}

void	afterdol(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (countmallocend(str) > 0)
		g_base.dol.end = malloc(sizeof(char) * (countmallocend(str) + 1));
	while (str[i] != '$')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	if (str[i] == '\0')
	{
		g_base.dol.end = NULL;
		return ;
	}
	while (str[i])
	{
		g_base.dol.end[j] = str[i];
		i++;
		j++;
	}
	g_base.dol.end[j] = '\0';
}

int	countmallocend(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

void	beforedol(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (countbefdol(str) > 0)
		g_base.dol.beforedol = malloc(sizeof(char) * (countbefdol(str) + 1));
	while (str[i])
	{
		if (str[i] == '$')
				break ;
		g_base.dol.beforedol[j] = str[i];
		i++;
		j++;
	}
	if (countbefdol(str) > 0)
		g_base.dol.beforedol[j] = '\0';
	else
		g_base.dol.beforedol = NULL;
}

void	replacedol(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (countdolmal(str) > 0)
		g_base.dol.strret = malloc(sizeof(char) * (countdolmal(str) + 1));
	while (str[i] != '$')
		i++;
	if (str[i + 1] == '\0')
	{
		g_base.dol.strret = NULL;
		return;
	}
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	{
		g_base.dol.strret[j] = str[i];
		i++;
		j++;
	}
	g_base.dol.strret[j] = '\0';
}

int	countdolmal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
		{
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (j);
}

char	*finalstringdol(char *str, t_env **env)
{
	char	*strnew;
	char	*tmp;

	beforedol(str);
	replacedol(str);
	checkenvdol(env);
	tmp = ft_strjoin(g_base.dol.beforedol, g_base.dol.strret);
	afterdol(str);
	strnew = ft_strjoin(tmp, g_base.dol.end);
	//free(tmp);
	if (strnew == NULL)
		return (NULL);
	free(str);
	return (strnew);
}

void	checkenvdol(t_env **env)
{
	int	i;
	t_env	*tmp;
	char	*stra;

	i = 0;
	tmp = (*env);
	if (g_base.dol.strret == NULL)
		return ;
	stra = ft_strdup(g_base.dol.strret);
	free(g_base.dol.strret);
	while (tmp)
	{
		if (ft_strcmp(stra, tmp->name) == 0)
		{
			free(stra);
			g_base.dol.strret = ft_strdup(tmp->content);
			return ;
		}
		tmp = tmp->next;
	}
	if (stra != NULL)
		free(stra);
	g_base.dol.strret = NULL;
}