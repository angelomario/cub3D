
#include "../includes/get_next_line.h"

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	close(fd);
	return (0);
}
