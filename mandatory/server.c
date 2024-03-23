/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:13:43 by akoutate          #+#    #+#             */
/*   Updated: 2024/03/23 05:33:32 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_i = 0;

void	usr_handler(int sig, siginfo_t *info, void *context)
{
	static pid_t	pid1;
	static char		c;

	if (pid1 != info->si_pid)
	{
		pid1 = info->si_pid;
		c = 0;
		g_i = 0;
	}
	if (sig == SIGUSR1)
		c = c << 1;
	else if (sig == SIGUSR2)
		c = (c << 1) + 1;
	g_i++;
	if (g_i == 8)
	{
		write(1, &c, 1);
		if (!c)
			write(1, "\n", 1);
		c = 0;
		g_i = 0;
	}
	(void)context;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = usr_handler;
	pid = getpid();
	write(1, "The process ID is ", 19);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
