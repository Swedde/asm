#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
    int				fd;
	unsigned char	c;
	char 			s[16] = "0123456789abcdef";
	int i;
	int j;

	fd = open(av[1], O_RDONLY);
	i = 0;
	j = 0;
	while (read(fd, &c, 1) == 1)
	{
		if (j == 2)
		{
			j = 0;
			printf(" ");
		}
		if (i == 16)
		{
			i = 0;
			printf("\n");
		}
		printf("%c%c", s[c / 16 % 16], s[c % 16]);
		i++;
		j++;
	}
	printf("\n");
	close(fd);
	return (0);
}
