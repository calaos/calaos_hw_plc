#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/poll.h>
#include <sys/time.h>

void
hal_system_init()
{
	
}

void
hal_serial_set_baudrate(int baudrate)
{
	
}

int
hal_serial_puts(const char *str)
{
	puts(str);

	return 0;
}


int
hal_dbg_log(const char *str)
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
		read(0, c, 1);
		return 1;
        } else {
		return 0;
	}
}

void
hal_panic(void)
{
	while (1) {
		sleep(1);
	};
}

unsigned long long
hal_get_micro(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);

	return 1000000 * tv.tv_sec + tv.tv_usec;
}

unsigned long long
hal_get_milli(void)
{
	return hal_get_micro() / 1000;
}



const char *
hal_get_filesystem_prefix()
{
	return "./";
}

static pthread_mutex_t g_crit_mutex = PTHREAD_MUTEX_INITIALIZER;

void
hal_critical_enter()
{
	pthread_mutex_lock(&g_crit_mutex);
}

void
hal_critical_exit() {
	pthread_mutex_unlock(&g_crit_mutex);
}
