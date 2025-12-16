/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:21:36 by rzimaeva          #+#    #+#             */
/*   Updated: 2025/12/12 18:25:38 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define PINK "\033[38;5;218m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void	test_file(int fd)
{
	char	*line;
	int		i;

	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(PINK "Ligne %d: " RESET "%s", i, line);
		free(line);
		i++;
	}
	close(fd);
}

void	test_alternating(int fd1, int fd2)
{
	char	*line1;
	char	*line2;
	int		i;

	i = 1;
	while (1)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf(PINK "FD%d (L%d): " RESET "%s", fd1, i, line1);
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf(PINK "FD%d (L%d): " RESET "%s", fd2, i, line2);
			free(line2);
		}
		if (!line1 && !line2)
			break ;
		i++;
	}
	close(fd1);
	close(fd2);
}

int	main(void)
{
	int fd1;
	int fd2;
	int fd3;
	int fd4;

	fd1 = open("tests/file1.txt", O_RDONLY);
	fd2 = open("tests/file2.txt", O_RDONLY);
	fd3 = open("tests/file3.txt", O_RDONLY);
	fd4 = open("tests/empty.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1)
	{
		printf(RED "Erreur: Impossible d'ouvrir un ou plusieurs fichiers de test.\n" RESET);
		return (1);
	}
	test_file(fd1);
	fd1 = open("tests/file1.txt", O_RDONLY);
	if (fd1 == -1)
		return (1);
	test_alternating(fd1, fd2);
	test_file(fd3);
	test_file(fd4);
	return (0);
}