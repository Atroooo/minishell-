/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:20:10 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/27 13:22:18 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	get_dup_single_done(t_env_pipe *st)
{
	if (st->nbr_cmd == 1)
	{
		if (dup2(st->infile, STDIN_FILENO) == -1)
			return (quit_function(st, 0));
		if (dup2(st->outfile, STDOUT_FILENO) == -1)
			return (quit_function(st, 0));
		return (1);
	}
	return (0);
}

static int	get_first_dup_done(t_env_pipe *st)
{
	if (dup2(st->infile, STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	close(st->infile);
	return (1);
}

static int	get_last_dup_done(t_env_pipe *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->outfile, STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	close(st->outfile);
	return (1);
}

static int	get_dup_done(t_env_pipe *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	return (1);
}

int	dup_manager(t_env_pipe *st)
{
	if (get_dup_single_done(st) == 1)
		return (1);
	else
	{
		if (st->actual_pipe == 0)
		{
			if (!get_first_dup_done(st))
				return (0);
		}
		else if (st->actual_pipe == st->nbr_cmd - 1)
		{
			if (!get_last_dup_done(st))
				return (0);
		}
		else
		{
			if (!get_dup_done(st))
				return (0);
		}
	}
	close_function(st);
	return (1);
}
