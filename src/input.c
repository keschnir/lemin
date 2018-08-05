/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 16:47:40 by fablin       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 09:52:01 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"

int		valid_ants(char *ants)
{
	int valid;

	valid = 1;
	if (!ft_isdigit(ants[0]))
		valid = 0;
	return (valid);
}

int		valid_nodes(char *node)
{
	int		valid;
	char	**split;

	valid = 0;
	if (node)
	{
		valid = 1;
		if (node[0] == '#')
			return (1);
		split = ft_strsplit(node, ' ');
		if (split && split[0] && split[1] && split[2] && !split[3])
		{
			if (!ft_isalnum(split[0][0]) ||
				(!ft_isdigit(split[1][0])) ||
				(!ft_isdigit(split[2][0])))
				valid = 0;
		}
		else
			valid = 0;
		ft_delstrsplit(&split);
	}
	return (valid);
}

int		valid_links(char *link)
{
	int 	valid;
	char	**split;

	valid = 0;
	if (link)
	{
		valid = 1;
		if (link[0] == '#')
			return (1);
		split = ft_strsplit(link, '-');
		if (split && split[0] && split [1] && !split[2])
		{
			if (!ft_isalnum(split[0][0]) ||
				!ft_isalnum(split[1][0]))
				valid = 0;
		}
		ft_delstrsplit(&split);
	}
	return (valid);
}

int		valid_start_end(char *file)
{
	int		valid;
	char	*start;
	char	*end;
	char	**split;

	valid = 0;
	if (file)
	{
		valid = 1;
		start = ft_strstr(file, "##start\n");
		end = ft_strstr(file, "##end\n");
		if (start && end)
		{
			split = ft_strsplit(start + 8, '\n');
			if (!valid_nodes(*split))
				valid = 0;
			ft_delstrsplit(&split);
			split = ft_strsplit(end + 6, '\n');
			if (!valid_nodes(*split))
				valid = 0;
			ft_delstrsplit(&split);
		}
	}
	return (valid);
}

int		valid_file(char *file)
{
	int		valid;
	char	**split;
	int		i;

	valid = 0;
	if (file)
	{
		valid = 1;
		split = ft_strsplit(file, '\n');
		i = 1;
		if (valid && !valid_start_end(file))
			valid = 0;
		if (valid && !valid_ants(split[0]))
			valid = 0;
		while (valid && split[i])
		{
			valid = valid_nodes(split[i]);
			if (valid == 0)
				valid = valid_links(split[i]);
			i++;
		}
		while (valid && split[i])
		{
			valid = valid_links(split[i]);
			i++;
		}
		ft_delstrsplit(&split);
	}
	return (valid);
}

int		get_input(t_env *env)
{
	char	*line;
	int		gnl;

	while ((gnl = get_next_line(0, &line)) > 0)
	{
		if (!(env->file = ft_strjoinfree(env->file, line)) ||
			!(env->file = ft_strjoinfree(env->file, ft_strdup("\n"))))
			return (-1);
	}
	if (gnl == -1 || !valid_file(env->file))
		exit_lemin(&env, "Invalid file.");
	return (gnl);
}
