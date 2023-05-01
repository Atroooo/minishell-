/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/01 08:43:44 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd, t_env_main *main_env)
{
	char	cwd[4096];


	if (cmd[1])
	{
		main_env->exit_status = 1;
		if (cmd[1][0] == '-')
		{
			ft_putendl_fd("pwd: -p: invalid option", 2);
			return ;
		}
		ft_putendl_fd("pwd: too many argument", 2);
		return ;
	}
	main_env->exit_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
}
