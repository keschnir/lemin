/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 16:44:41 by fablin       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/29 20:28:45 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"

t_list	*set_ants(t_env *env)
{
	t_list	*ants;
	t_list	*tmp;
	t_ant	*ant;
	int		i;

	ants = NULL;
	ant = NULL;
	i = 0;
	while (i < env->nbant)
	{
		ant = newant(ft_itoa(i), NULL, 0);
		tmp = ft_lstnew(NULL, 0);
		tmp->content = ant;
		ft_lstpush(&ants, tmp);
		delant(ant, sizeof(t_ant));
		i++;
	}
	return (ants);
}

t_list	*set_nodes(t_env *env)
{
	t_list	*nodes;
	char	**split;
	char	**line;
	t_ntree	*node;
	int		i;

	nodes = NULL;
	node = NULL;
	split = ft_strsplit(env->file, '\n');
	i = 1;
	while (split[i] && valid_nodes(split[i]))
	{
		line = ft_strsplit(split[i], ' ');
		node = ft_newntree(ft_strdup(line[0]),
						ft_newpoint(ft_atoi(line[1]), ft_atoi(line[2])),
						0,
						NULL);
		ft_lstpush(&nodes, ft_lstnew(node, sizeof(t_ntree)));
		ft_delntree(&node);
		ft_delstrsplit(&line);
		i++;
	}
	ft_delstrsplit(&split);
	return (nodes);
}

int		init_env(t_env *env)
{
	char	**split;

	if (env && env->file)
	{
		split = ft_strsplit(env->file, '\n');
		env->nbant = ft_atoi(split[0]);
		env->ants = set_ants(env);
		//env->nodes = set_nodes(env, split);
		//env->links = set_links(env, split);
	}
	ft_delstrsplit(&split);
	return (1);
}
