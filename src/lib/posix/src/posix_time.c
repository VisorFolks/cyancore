#include <lib/posix/include/time.h>
#include <lib/posix/include/unistd.h>

unsigned sleep( unsigned seconds )
{
	return (unsigned) usleep(MICROSECONDS_PER_SECOND * seconds);
}

int usleep( useconds_t usec )
{

}
