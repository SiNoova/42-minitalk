/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:35:45 by akoutate          #+#    #+#             */
/*   Updated: 2024/03/23 05:36:29 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_i = 0;

void	print_and_reset(unsigned char *buffer,
	int *bytes_to_receive, pid_t pid, unsigned char c)
{
	int	i;

	i = 0;
	if (!c)
	{
		kill(pid, SIGUSR1);
		write(1, "\n", 1);
	}
	write(1, buffer, *bytes_to_receive);
	*bytes_to_receive = 0;
	while (i < 4)
		buffer[i++] = 0;
}

void	filler_and_bytes2receive(unsigned char *buffer,
	unsigned char c, int *buffer_index, int *bytes_to_receive)
{
	buffer[(*buffer_index)++] = c;
	if (*buffer_index == 1)
	{
		if (c <= 127)
			*bytes_to_receive = 1;
		else if (c <= 223)
			*bytes_to_receive = 2;
		else if (c <= 239)
			*bytes_to_receive = 3;
		else
			*bytes_to_receive = 4;
	}
}

int	pid_checker(pid_t current_pid, unsigned char *c,
	unsigned char *buffer, int *buffer_index)
{
	static pid_t	pid1;
	int				i;

	i = 0;
	if (pid1 != current_pid)
	{
		pid1 = current_pid;
		*c = 0;
		g_i = 0;
		*buffer_index = 0;
		while (i < 4)
			buffer[i++] = 0;
		return (1);
	}
	return (0);
}

void	usr_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static unsigned char	buffer[4];
	static int				buffer_index;
	static int				bytes_to_receive;

	if (pid_checker(info->si_pid, &c, buffer, &buffer_index))
		bytes_to_receive = 0;
	c = c << 1;
	if (sig == SIGUSR2)
		c += 1;
	if (++g_i == 8)
	{
		filler_and_bytes2receive(buffer, c, &buffer_index, &bytes_to_receive);
		if (buffer_index == bytes_to_receive)
		{
			print_and_reset(buffer, &bytes_to_receive, info->si_pid, c);
			buffer_index = 0;
		}
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
