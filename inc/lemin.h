/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fablin <fablin@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 16:57:37 by fablin       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/03 17:01:24 by fablin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <string.h>
# include <errno.h>

typedef struct	s_env
{
	char	*file;
	int		nbant;
	t_list	*ants;
	t_list	*nodes;
	t_ntree	*start;
	t_ntree	*end;
	char	*output;
}				t_env;

typedef struct	s_ant
{
	char	*name;
	t_list	*path;
	int		start_turn;
}				t_ant;

void			exit_lemin(t_env **env, char *msg);
int				get_input(t_env *env);
int				init_env(t_env *env);
int				solve(t_env *env);
int				output(t_env *env);
t_env			*newenv(void);
void			delenv(t_env **env);
t_ant			*newant(char *name, t_list *path, int	start_turn);
void			delantlst(void *ant, size_t size);
void			ft_delstrsplit(char ***split);
int				valid_nodes(char *node);
int				valid_links(char *link);
void			ft_putlst(t_list *lst);
t_ntree			*get_ntree_in_lst(char *name, t_list *lst);
t_ntree			*get_ntree_in_ntree(char *name, t_ntree *t);
void			ft_putntreelst(t_list *lst);
void			ft_putantlst(t_list *lst);
void			ft_put_start_end(t_env *env);
void 			delntreelst(void *node, size_t size);
#endif
