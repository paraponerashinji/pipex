/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:13 by aharder           #+#    #+#             */
/*   Updated: 2025/02/02 18:35:44 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	checkargs(int argc, char **argv)
{
	if (argc != 5)
		return (0);
}

int	createchildren(int argc, char **argv, char **envp)
{
	pid_t	p;

	p = fork();
	if (p == 0)
		
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];

	if (checkargs(argc, argv)
		return (print_error("args"));
	pipe(fd);
	createchildren(argc, argv, envp);
}
