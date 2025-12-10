#include <unistd.h>

//RACCOURCIR ENLEVER ACCOLADES
//nettoie ce quon a pris dans la stash jusuquau '\n' et prend tou ce qui suit
char	*clean_stash(char *stash)
{
	char	*new_stash; //stock ce qui est alloué par substr, après '\n'
	char	*newline_pos; //pos de départ, à partir de'\n'
	size_t	len_read; //longueur qui a été lue + '\n',  doit être dégagé
	size_t	len_to_keep;

	if (!stash || ft_strlen(stash) == 0)
	{
		free (stash); //au cas où elle a ete allouée avant
		return (NULL);
	}
	newline_pos = ft_strchr(stash, '\n'); //nvl ligne, adresse de '\n'
	if (!newline_pos) //si on trouve pas'\n' car EOF ou jsp, on stop tout
	{
		free(stash);
		return (NULL);
	}
	len_read = (newline_pos - stash) + 1; //chars du debut jusquau '\n' inclus (+1) Exemple : Si stash est "Bonjour\nLeReste" (longueur 15), le \n est après l'index 7. len_read sera $7 + 1 = 8$. L'index 8 correspond au 'L' de "LeReste".
	len_to_keep = ft_strlen(stash) - len_read; //les nv chars qui doivent etre conserves (15-8= 7)
	if (len_to_keep == 0) //0 ='\n'
	{
		free(stash);
		return (NULL);
	}
	//ft_substr(char const *s, unsigned int start, size_t len)
	new_stash = ft_substr(stash, len_read, len_to_keep); // len_read = apres '\n, on démarre de ce quon a déjà lu //nbr de char à copier
	free(stash); //libere l'ancien stash
	if (!new_stash) //gestion des erreurs
        	return (NULL);
	return (new_stash);
}

char	*get_line(char	*stash)
{
	char	*line
	char	*new_pos;
	size_t	len_line;

	if (!stash || ft_strlen(stash) == 0)
		free(stash);
		return (NULL);
	new_pos = ft_strchr(stash, '\n');
	if (new_pos)
		len_line = (new_pos - stash) + 1 //'\n' //distance entre début stash et  new_pos
	else
		len_line = ft_strlen(stash);
	//ft_substr(char const *s, unsigned int start, size_t len)
	line = ft_substr(stash, 0, len_line);
	return (line); //on return le resultat donc la line
}

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#define MAX_FD 4096

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	//assurer que le stash contient une ligne complète ou que l'EOF a été atteint
	if (fill_stash(fd, &stash[fd]) == 0)
		return (NULL);
	// récupère la ligne qui va être return
	line = get_line(stash[fd]);
	//maj de static char
	if (!line)
	{
		free(stash[fd])
		stash[fd] = NULL;
		return (NULL);
	}
	//return nv pointeur et free l'ancien
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
