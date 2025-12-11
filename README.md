{
ssize_t read(int fd, void *buf, size_t nbyte);
read() renvoie un size_t,  on lui envoie un fd (int entier), 
un ptr sur void et un 2eme size_t nbr de de bytes
read() va lire le nombre de bytes qu'on lui a envoye avec nbyte
dans le fd vers le buffer pointe par *buf

Si tout est bon, renvoie le nbyte qu'elle a lu, sinon -1



"|bonjour monsieur" si je mets nbyte a 5, ca va faire "bonjo|ur monsieur"
read() va stocker "bonjo" dans le buffer, renvoie 5 et pas "bonjo"
quand on rappelle read() plus tard, elle va partir de son dernier checkpoint
"bonjo"5 puis "ur mo"5 puis "nsieu"5 puis "r"1 car \n, quand elle a fini,
elle renvoie 0 car plus aucun bytes a return

"read() RETURN 5/bytes/", quand elle repasse 72 fois elle ecrase
le buffer (lit 5 par 5 mais perd les valeurs precedentes), creer alors
une STASH pour STOCKER (dans une static char)

On regarde dans le stash si on arrive au bout de la ligne (\n), sinon
rappeler read et continuer a lire 5 par 5 (car nbyte = 5) et stocker
dans la stash petit a petit toujours en verifiant si c'est pas "\n"
si plus rien a lire donc premiere ligne de lue jusqu'a \n OU erreur, renvoyer NULL 


Si par ex :
hello|(5)$(\n)
byeb|(5)ye(2)


On va stocker dans stash comme (hello$byeb) sauf qu'on a pris le $(\n)
pour recupere la line "hello$" on va creer une variable LINE pour l'extraire

On degage le "hello$" parce qu'on renvoie notre premiere line et on va le free
get_next_line()RETURN(line)

Normalement, apres avoir return la line, la stash a ete vide avec "byeb", sauf QUE!, 
vu que j'ai utilise des static char pour ma stash elle sera inchangee donc le "byeb" 
est toujours la et on peut continuer et refaire la meme chose qu'avec "hello$"
}


{
Fonctions que je peux potentiellement utiliser : 
- strjoin(pour mettre les line qu'on a lu a la suite, elle va construire la stash + limite)
- strdup (pour copier la line dans ma stash) 
- strchr (pour trouver le saut de ligne '\n')
- utiliser free, malloc, BUFF_SIZE etc
- On va definir la size du buffer dans le fichier.h(eader)
"# define BUFFER_SIZE 42" SINON dans le main directement pour les fnct idvdls,
pour le main on va utiliser un open fd et un close fd
}

{
	normal input = 0
	normal output = 1
	error = 2
	buffer = stockage temporaire pour manipuler
	stash = stockage accumule, grande place
}
