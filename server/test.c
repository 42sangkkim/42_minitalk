#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h> // have to remove
#include <stdlib.h>

void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler);

int	main(void)
{
	struct sigaction	sigusr_action;

	printf("server is runnig\nserver pid : %d\n", getpid());
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	sigaction(SIGUSR1, &sigusr_action, NULL);
	sigaction(SIGUSR2, &sigusr_action, NULL);
	while (1)
		;
	return (0);
}

void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler)
{
	if (sig == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (sig == SIGUSR2)
		printf("received SIGUSR2\n");
}
