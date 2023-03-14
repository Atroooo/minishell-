/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:30 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 12:38:00 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_list(t_env_var *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		if (env_list->name && env_list->value[0] != 0)
			ft_printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}

void	ft_env(char **cmd, t_env_var *env_list, t_env_main *main_env)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "env") != 0)
		return ;
	print_list(env_list);
	main_env->last_cmd_status = 0;
}
