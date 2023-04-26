/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 17:45:36 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_list(t_env_var *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		printf("declare -x ");
		if (env_list->name && env_list->value)
			printf("%s=%s\n", env_list->name, env_list->value);
		else if (env_list->name && !env_list->value)
			printf("%s=\n", env_list->name);
		env_list = env_list->next;
	}
}

static t_env_var	*add_env_value(char *str, t_env_var *env_list)
{
	char	*name;
	char	*value;
	int		in_env;

	in_env = check_if_in_env(env_list, str);
	if (set_variables_name_and_value(str, &name, &value))
		return (NULL);
	if ((str[0] == '$' && str[1] == '$') || (str[0] == '$' && in_env == 0))
	{
		free_variable_name_and_value(name, value);
		return (env_list);
	}
	if (in_env == 1 && value == NULL)
		return (env_list);
	else if (in_env == 1)
		env_list = remove_similar_variable(name, env_list);
	ft_lst_addback_env(&env_list, ft_lstnew_env(name, value));
	free_variable_name_and_value(name, value);
	return (env_list);
}

static int	check_export_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
	{
		ft_putstr_fd("export: `-", 2);
		ft_putchar_fd(cmd[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (printf("export: `%s': not a valid identifier\n", cmd));
	while (cmd[i] != '\0' && cmd[i] != '=')
	{	
		if (cmd[i] == '!')
			return (printf("%s: event not found\n", &cmd[i]));
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?' \
		|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~' \
		|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{' \
		|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+')
			return (printf("export: `%s': not a valid identifier\n", cmd));
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i] == '!')
			return (printf("%s: event not found\n", &cmd[i]));
		i++;
	}
	return (0);
}

t_env_var	*ft_export(char **cmd, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd[0], "export") != 0)
		return (NULL);
	i = 1;
	if (!cmd[i])
	{
		print_list(main_env->env_list);
		main_env->exit_status = 0;
		return (main_env->env_list);
	}
	while (cmd[i])
	{
		if (check_export_error(cmd[i]) == 0)
			main_env->env_list = add_env_value(cmd[i], main_env->env_list);
		i++;
	}
	main_env->exit_status = 0;
	return (main_env->env_list);
}
