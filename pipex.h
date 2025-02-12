/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:13:57 by aharder           #+#    #+#             */
/*   Updated: 2025/02/12 01:56:58 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

// Function prototypes
int     checkargs(int argc);
void    executecommand(char *cmd, char **args, char **envp);
int    createpipes(int argc, char **argv, char **envp);
#endif // PIPEX_H
