/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:13 by aharder           #+#    #+#             */
/*   Updated: 2025/02/12 02:20:43 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void free_split(char **split)
{
    int i = 0;

    while (split[i])
        free(split[i++]);
    free(split);
}

int	checkargs(int argc)
{
	if (argc < 5)
		return (0);
	return (1);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub) + 1) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(ft_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_split(s_cmd);
			return (exec);
		}
		free(exec);
	}
	free_split(allpath);
	free_split(s_cmd);
	return (cmd);
}

void	executecommand(char *cmd, char **args, char **envp)
{
	pid_t	p;
	char	*full_cmd;
	int	pipe_fd[2];

	pipe(pipe_fd);
	p = fork();
	if (p == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 3) == -1)
		{
			perror("dup2 failed");
			exit(1);
		}
		//ft_printf("test");
		close(pipe_fd[1]);
		full_cmd = get_path(cmd, envp);
		//ft_printf("%s\n", full_cmd);
		execve(full_cmd, args, envp);
		perror("execve failed");
		free(full_cmd);
		exit(1);
	}
	else if (p == -1)
		ft_printf("fork error");
	else
	{
		//ft_printf("test");
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(p, NULL, 0);
	}
}

int	createpipes(int	argc, char **argv, char **envp)
{
	int	inout_fd[2];
	int	i;
	char	**args;

	if ((inout_fd[0] = open(argv[1], O_RDONLY)) < 0)
		return (ft_printf("Error opening infile"));
	if ((inout_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (ft_printf("Error opening outfile"));
	i = 2;
	dup2(inout_fd[0], 0);
	close(inout_fd[0]);
	while (i < argc - 1)
	{
		//ft_printf("test");
		args = ft_split(argv[i], ' ');
		if (i == argc - 2)
			dup2(inout_fd[1], STDOUT_FILENO);
		executecommand(args[0], args, envp);
		free_split(args);
		i++;
	}
	close(inout_fd[1]);
	return (1);
}
int	main(int argc, char *argv[], char *envp[])
{
	//ft_printf("test");
	if (!checkargs(argc))
		return (ft_printf("Erreur : args\n"));
	createpipes(argc, argv, envp);
}
