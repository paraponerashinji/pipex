/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:13 by aharder           #+#    #+#             */
/*   Updated: 2025/02/12 16:04:20 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
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

void	executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp)
{
	pid_t	p;
	char	*full_cmd;

	p = fork();
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		full_cmd = get_path(cmd, envp);
		execve(full_cmd, args, envp);
		perror("execve failed");
		free(full_cmd);
		exit(1);
	}
	else if (p == -1)
		ft_printf("fork error");
	else
		waitpid(p, NULL, 0);
}

int	createpipes(int argc, char **argv, char **envp)
{
	int	inout_fd[2];
	int	i;
	char	**args;
	int	p_fd[2];

	inout_fd[0] = open(argv[1], O_RDONLY);
	inout_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 2;
	while (i < argc - 1)
	{
		args = ft_split(argv[i], ' ');
		if (i < argc - 2)
			pipe(p_fd);
		else
			p_fd[1] = inout_fd[1];
		executecommand(args[0], args, inout_fd[0], p_fd[1], envp);
		free_split(args);
		if (i < argc - 2)
			close(p_fd[1]);
		if (inout_fd[0] != 0)
			close(inout_fd[0]);
		inout_fd[0] = p_fd[0];
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (!checkargs(argc))
		return (ft_printf("Erreur : args\n"));
	createpipes(argc, argv, envp);
}
