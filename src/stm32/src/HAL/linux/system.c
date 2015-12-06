#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

void
hal_system_init()
{
	
}

int
hal_serial_puts(const char *str)
{
	puts(str);

	return 0;
}


int
hal_debug_puts(const char *str)
{
	puts(str);

	return 0;
}

int
hal_serial_getc(char *c)
{
	
	struct pollfd fds;
	int ret;
	fds.fd = 0; /* this is STDIN */
	fds.events = POLLIN;
	fds.revents = 0;
	ret = poll(&fds, 1, 0);
        if(ret == 1) {
		read(0, &c, 1);
		printf("Got char\n");
		return 1;
        } else {
		return 0;
	}
}

void
hal_panic(void)
{
	fprintf(stderr, "PANIC PANIC PANIC !!!!!\n");
	while (1) {
		sleep(1);
	};
}
