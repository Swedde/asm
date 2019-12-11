#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef union   u_test
{
    unsigned a;
    struct{
    unsigned char c1:8;
    unsigned char c2:8;
    unsigned char c3:8;
    unsigned char c4:8;
    }ch;
}               uni_t;

void	set_srt_hex(char s[9], int i, unsigned a)
{
	char str[16] = "0123456789abcdef";

	if (a >= 16)
	{
		set_srt_hex(s, i + 1, a / 16);
	}
	s[i] = str[a % 16];
}

uni_t	read_to_uni_t(int fd, int *f, int *f2)
{
	unsigned char	c;
	uni_t			a;

	if (read(fd, &c, 1) < 1)
	{
		*f = 0;
		*f2 = 0;
		c = 0;
	}
	a.ch.c4 = c;
	if (read(fd, &c, 1) < 1)
	{
		*f = 0;
		c = 0;
	}
	a.ch.c3 = c;
	if (read(fd, &c, 1) < 1)
	{
		*f = 0;
		c = 0;
	}
	a.ch.c2 = c;
	if (read(fd, &c, 1) < 1)
	{
		*f = 0;
		c = 0;
	}
	a.ch.c1 = c;
	return a;
}

int main(int ac, char **av)
{
    int				fd;
	char			s[9];
	uni_t			a;
	int				f_r;
	int				f2;
	int				j = 0;
	
	f_r = 1;
	f2 = 1;
	fd = open(av[1], O_RDONLY);
	s[8] = '\0';
	while (f_r)
	{
		j++;
		memset(s, '0', 8);
		a = read_to_uni_t(fd, &f_r, &f2);
		set_srt_hex(s, 0, a.a);
		if (f2)
		{
			for (int i = 7; i > -1; i--)
			{
				if (i == 3 || i ==7)
					printf(" ");
				printf("%c", s[i]);
			}
		}
		if (j == 4)
		{
			printf("\n");
			j = 0;
		}
	}
	printf("\n");
	close(fd);
    return 0;
}