#include "get_next_line.h"
#include <fcntl.h>  // open
#include <stdio.h>  // printf
#include <stdlib.h> // free

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;

	if (argc < 2)
	{
		printf("Erreur : Donnez un fichier à lire.\nUsage: %s <test.txt>\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture (fd -1)");
		return (1);
	}

	printf("--- Début de la lecture ---\n");
	line_count = 0;
	
	// La boucle continue tant que GNL ne renvoie pas NULL
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("\n[GNL a renvoyé NULL] : Fin de fichier ou erreur atteinte.\n");
			break ;
		}
		line_count++;
		printf("Ligne %d: %s", line_count, line);
		free(line); // Obligatoire pour éviter les leaks
	}

	printf("--- Fin de la lecture (Total: %d lignes) ---\n", line_count);
	close(fd);
	return (0);
}