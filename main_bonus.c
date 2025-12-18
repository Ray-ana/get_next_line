//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:21:36 by rzimaeva          #+#    #+#             */
/*   Updated: 2025/12/18 14:46:18 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

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

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	fd3 = open("file3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf(RED "Erreur: Impossible d'ouvrir un ou plusieurs fichiers (file1.txt, file2.txt, file3.txt).\n" RESET);
		return (1);
	}

	printf(PINK "--- TEST SIMPLE (FILE 1) ---\n" RESET);
	test_file(fd1);

	fd1 = open("file1.txt", O_RDONLY);
	if (fd1 == -1)
		return (1);

	printf(PINK "\n--- TEST ALTERNÉ (FD1 & FD2) ---\n" RESET);
	test_alternating(fd1, fd2);

	printf(PINK "\n--- TEST SIMPLE (FILE 3) ---\n" RESET);
	test_file(fd3);

	return (0);
}
