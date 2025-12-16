Definitions importantes :
	- buffer = stockage temporaire pour manipuler ce dont on a besoin
	- stash = stockage qui permet d'accumuler, grande place, va stocker 
	  les differents buffer


Fontion read() :
	ssize_t read(int fd, void *buf, size_t nbyte);
	read() renvoie un size_t,  on lui envoie un fd (int entier), 
	un pointeur sur void et un 2eme size_t nombre de bytes "nbyte".
	read() va lire le nombre de bytes qu'on lui a envoye avec nbyte dans le fd 
	vers le buffer qui est pointe par *buf.

	Si tout est bon, renvoie le nbyte qu'elle a lu, sinon -1.


Exemples :
	"|bonjour monsieur" si je mets nbyte a 5, ca va faire "bonjo|ur monsieur"
	read() va stocker "bonjo" dans le buffer, return (5) et non "bonjo" en toutes lettres.
	Quand on rappelle read() plus tard, elle va partir de son dernier arret, donc apres le 'o',
	"bonjo"5 puis "ur mo"5 puis "nsieu"5 puis "r"1 car rencontre '\n', quand elle a fini,
	elle renvoie 0 car plus aucun bytes a return.

	"read() RETURN (5)", quand elle repasse 72 fois elle ecrase le buffer
	(lit 5 par 5 mais perd les valeurs precedentes au fur et a mesure), cree alors
	une STASH pour STOCKER ce qui est necessaire plus longtemps (en utilisant ici des static char).

	On regarde dans la stash si on arrive au bout de la ligne (\n), sinon rappeler read et
	continuer a lire 5 par 5 (car nbyte = 5) puis stocker dans la stash petit a petit
	toujours en verifiant s'il n'y a pas '\n'.
	
	Si plus rien a lire, la premiere ligne est lue jusqu'a '\n' OU si y'a erreur, return (NULL).


	Si par ex :
	hello|(5)$/*'\n'*/
	byeb|(5)ye|(2)


	On va stocker les infos dans la stash, par ex "hello$byeb", sauf qu'on a pris le $/*'\n'*/.
	Pour extraire la ligne "hello$", on va creer une variable "line".

	On degage le "hello$" de la stash parce qu'on veut renvoyer cette premiere ligne
	et on va la free puis "return(line)".

	Normalement, apres avoir return la ligne, la stash a ete videe avec "byeb", sauf QUE!, 
	vu que j'ai utilise des static char pour ma stash, elle sera inchangee donc le "byeb" 
	sera toujours la et on pourra continuer et refaire la meme chose qu'avec "hello$".


Fonctions que je peux utiliser :
	- ft_strjoin(pour mettre les line qu'on a lu a la suite (concatener), elle va construire la stash)
	- ft_strdup (je vais l'utiliser pour initialiser une string vide(a la place de NULL pour securiser) 
	- ft_strchr (pour trouver le saut de ligne '\n')
	- ft_strlen (calculer la longueur)
	- ft_substr (pour extraire la ligne que l'on veut)
	- utiliser free, malloc, BUFFER_SIZE, static char etc
	- On va definir la size du buffer dans le fichier.h(eader)
	"# define BUFFER_SIZE 42", doit pouvoir etre modifiable lors de la compilation.
	Pour le main, utiliser un open fd, close fd, etc.

	normal input = 0
	normal output = 1
	error = 2
