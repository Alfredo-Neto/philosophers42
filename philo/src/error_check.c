/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:10:34 by ade-agui          #+#    #+#             */
/*   Updated: 2022/09/04 12:10:36 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	error(char *message)
{
	printf("%s\n", message);
	return (false);
}

static bool	is_out_of_range(double number)
{
	if (number > INT_MAX || number == 0)
		return (true);
	return (false);
}

static bool	only_digits(char **argv, int i, int j)
{
	while (argv[i][++j])
		if (!ft_isdigit(argv[i][j]))
			return (false);
	return (true);
}

static	bool	only_unsigned_integers(int argc, char **argv, int i)
{
	while (++i < argc)
	{
		if (!only_digits(argv, i, -1))
			return (false);
		if (is_out_of_range(philos_atoi(argv[i])))
			return (false);
	}
	return (true);
}

bool	error_check(int argc, char **argv)
{
	if (argc < MIN_ARGS || argc > MAX_ARGS)
		return (error(USAGE));
	if (!only_unsigned_integers(argc, argv, 0))
		return (error(NOT_UNINT));
	return (true);
}
