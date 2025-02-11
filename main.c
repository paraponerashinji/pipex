/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:13 by aharder           #+#    #+#             */
/*   Updated: 2025/02/11 18:15:58 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	checkargs(int argc, char **argv)
{
	if (argc != 5)
		return (0);
}

void	executecommand(int *inout_fd, char *cmd, char **args, char **envp)
{
	int	fd[2];
	pid_t	p;

	pipe(fd);
	p = fork();
	if (p == 0)
	{
		close(fd[0]);
		dup2(inout_fd[0], STDIN_FILENO)
		dup2(fd[1], STDOUT_FILENO);
		full_cmd = ft_strjoin("/bin/", cmd);
		execve(full_cmd, args, envp);
		free(full_cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], inout_fd[1]);
		waitpid(p, NULL, 0);
	}
}

void	createpipes(int	argc, char **argv, char **envp)
{
	int	inout_fd[2];
	int	i;
	char	**args;

	if (access(argv[1], F_OK) == 0)
		inout_fd[0] = open(argv[1], O_RDONLY);
	if (access(argv[argc - 1], F_OK) == 0)
		inout_fd[1] = open(argv[argc - 1], O_WRONLY);
	i = 2;
	while (i < argc - 1)
	{
		args = ft_split(argv[i], " ");
		executecommand(inout_fd, args[0], args, envp);
		free(args);
		i++;
	}
}
int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	char	***args;
	char	*infile;
	char	*outfile;
	if (checkargs(argc, argv))
		return (print_error("args"));
	createpipes(argc, argv, envp);
	free_triple(args);
}
