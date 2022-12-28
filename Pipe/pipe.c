/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:46:00 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/16 22:17:37 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipex(t_cmd *cmd, char **env)
{
	pid_t	process;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		write(STDERR_FILENO, "parent: Failed to create pipe\n", 30);
		return (-1);
    }
    // Fork a process to run grep
    process = fork();
    if (process == -1)
	{
        write(STDERR_FILENO, "parent: Could not fork process to run grep\n", );
        return -1;
    }
	else if (process == 0)
	{
        fprintf(stdout, "child: grep child will now run\n");

        // Set fd[0] (stdin) to the read end of the pipe
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
            fprintf(stderr, "child: grep dup2 failed\n");
            return (-1);
        }
        // Close the pipe now that we've duplicated it
        close(pipefd[0]);
        close(pipefd[1]);
        // Setup the arguments/environment to call
        char *new_argv[] = { "/bin/grep", argv[2], 0 };
        // Call execve(2) which will replace the executable image of this
        // process
        execve(new_argv[0], &new_argv[0], env);
        // Execution will never continue in this process unless execve returns
        // because of an error
        printf(stderr, "child: Oops, grep failed!\n");
        return (-1);
    }
	// Fork a process to run ls
    pid_ls = fork();
    if (pid_ls == -1)
	{
        fprintf(stderr, "parent: Could not fork process to run ls\n");
        return -1;
    }
	else if (pid_ls == 0)
	{
        fprintf(stdout, "child: ls child will now run\n");
        // Set fd[1] (stdout) to the write end of the pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
            fprintf(stderr, "ls dup2 failed\n");
            return -1;
        }
        // Close the pipe now that we've duplicated it
        close(pipefd[0]);
        close(pipefd[1]);
        // Setup the arguments/environment to call
        char *new_argv[] = { "/bin/ls", "-la", argv[1], 0 };
        char *envp[] = { "HOME=/", "PATH=/bin:/usr/bin", "USER=brandon", 0 };
        // Call execve(2) which will replace the executable image of this
        // process
        execve(new_argv[0], &new_argv[0], envp);
        // Execution will never continue in this process unless execve returns
        // because of an error
        fprintf(stderr, "child: Oops, ls failed!\n");
        return -1;
    }
    // Parent doesn't need the pipes
    close(pipefd[0]);
    close(pipefd[1]);
    fprintf(stdout, "parent: Parent will now wait for children to finish execution\n");
    // Wait for all children to finish
    while (wait(NULL) > 0);
    fprintf(stdout, "---------------------\n");
    fprintf(stdout, "parent: Children has finished execution, parent is done\n");
    return 0;
}