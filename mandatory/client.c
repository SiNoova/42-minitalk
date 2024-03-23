/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:03:45 by akoutate          #+#    #+#             */
/*   Updated: 2024/03/23 05:31:21 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(char c, pid_t pid)
{
	int	shift;
	int	mask;

	shift = 7;
	while (shift >= 0)
	{
		mask = 1 << shift;
		if (mask & c)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(400);
		shift--;
	}
}

int	main(int ac, char **av)
{
	int	i;

	if (ac == 3)
	{
		if (my_atoi(av[1]) <= 0 || my_atoi(av[1]) > 99998)
		{
			write(2, "bad pid\n", 8);
			return (0);
		}
		i = 0;
		while (av[2][i])
		{
			send_signal(av[2][i], my_atoi(av[1]));
			i++;
		}
		send_signal(av[2][i], my_atoi(av[1]));
	}
	else
		write(1, "syntax error: ./client <pid> <message>\n", 46);
	return (0);
}
