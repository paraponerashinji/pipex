/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:13 by aharder           #+#    #+#             */
/*   Updated: 2025/02/07 14:44:11 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	checkargs(int argc, char **argv)
{
	if (argc != 5)
		return (0);
}

void	executecommand(char *cmd, char **args, char **envp)
{
	int	fd[2];
	pid_t	p;

	pipe(fd);
	p = fork();
	if (p == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(ft_strjoin("/bin/", cmd), args, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(p, NULL, 0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	char	***args;

	if (checkargs(argc, argv))
		return (print_error("args"));
	args = malloc((argc + 1) * sizeof(**args));
	i = 2;
	while (i < argc)
	{
		args[i] = ft_split(argv[i], " ");
		executecommand(args[i][0], &args[i][1], envp);
		i++;
	}
	free_triple(args);
}
