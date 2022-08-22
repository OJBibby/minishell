#include "minishell.h"

int		execution(t_mini *mini)
{
	printf("HERE\n");
	int	fd[2];

	int	pid1;
	
	if (pipe(fd) == -1)
	{
		return (1);
	}
	if ((pid1 = fork() < 0))
		perror("fork1");
	if (pid1 < 0)
	{
		return (0);
	}
	if (pid1 == 0)
	{

		//child (ping)
		dup2(fd[0], STDIN_FILENO);



		close(fd[0]);
		close(fd[1]);
		if(execve(mini->tokens->path, mini->tokens->cmd_args, mini->tmp_env) < 0)
			perror("execve 1");



	}
	mini->tokens = mini->tokens->next;
	int	pid2 = fork();
	if (pid2 < 0)
	{
		return (1);
	}
	if (pid2 == 0)
	{
		// dup2(fd[0], STDIN_FILENO);
		if(dup2(fd[1], STDOUT_FILENO) < 0)
			perror("dup2");
		close(fd[0]);
		close(fd[1]);
		if(execve(mini->tokens->path, mini->tokens->cmd_args, mini->tmp_env) < 0)
			perror("execve 1");
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("out\n");

	return (0);
}