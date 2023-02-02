#include "fonctions.h"

jeu init_jeu(bool misere){
	jeu j;
	int taille;
	do{
		printf("Nombre de lignes ?\n>");
		scanf("%d", &taille);
	} while(taille < 1);
	j.taille = taille;
	j.misere = misere;
	j.max = 0;

	j.lignes = malloc(taille*sizeof(int));
	if(!j.lignes) exit(1);

	int allumettes;
	for(int i = 0; i < taille; i++){
		do{
			printf("Combien d'allumettes sur la ligne %d ?\n>", i);
			scanf("%d", &allumettes);
		} while (allumettes < 1);
		j.lignes[i] = allumettes;
		if(allumettes > j.max) j.max = allumettes;
	}

	return j;
}

jeu init_jeu_defaut(bool misere){
	jeu j = {4, misere, NULL, 7};

	j.lignes = malloc(4*sizeof(int));
	if(!j.lignes) exit(1);

	for(int i = 1; i <= 7; i+=2) j.lignes[i/2] = i; //on remplit chaque ligne par le double +1 d'allumettes (0*2+1, 1*2+1...)

	return j;
}

void print_jeu(jeu j){
	int blank;
	printf("\n");
	for(int i = 0; i < j.taille; i++){
		printf("%d) ", i);
		blank = (j.max - j.lignes[i]); //le nombre de caractères blancs requis
		for(int b = 0; b <= blank; b++) printf(" ");
		for(int n = 0; n < j.lignes[i]; n++) printf("| ");
		printf("\n");
	}
	printf("\n");
}

void free_jeu(jeu j){
	free(j.lignes);
}

void tour_humains(jeu* j){
	int ligne, n;
	do{
		printf("Sur quelle ligne allez-vous prendre des allumettes ?\n>");
		scanf("%d", &ligne);
	} while (ligne < 0 || ligne >= j->taille || j->lignes[ligne] < 1);
	
	do{
		printf("Combien d'allumettes allez-vous prendre ?\n>");
		scanf("%d", &n);
	} while (n < 1 || n > j->lignes[ligne]);

	j->lignes[ligne] -= n;
	check_max(j);
	print_jeu(*j);
}

bool check_victoire(jeu j){
	for(int i = 0; i < j.taille; i++) if(j.lignes[i]) return false;
	return true;
}

void jeu_humains(){
	jeu j = param_jeu();
	int joueur = 0;


	do{ //la boucle principale du jeu, avec les joueurs qui alternent entre 0 et 1
		printf("\nJoueur %d :\n", joueur+1);
		tour_humains(&j);
		joueur = !joueur;
	} while(!check_victoire(j));

	if(!j.misere) joueur = !joueur; //si il y a misere, le dernier joueur à n'avoir pas joué gagne

	printf("\n\nVictoire du joueur %d !\n", joueur+1);

	free_jeu(j);
}

void check_max(jeu* j){
	j->max = j->lignes[0];
	if(j->taille == 1) return;
	for(int i = 1; i < j->taille; i++) if(j->lignes[i] > j->max) j->max = j->lignes[i];
}

jeu param_jeu(){
	int choix, misere =  {0};

	printf("Partie par défaut (1) ou partie personnalisée (2) ?\nEntrez votre choix : ");
	do{scanf("%d", &choix);} while(choix != 1 && choix != 2);
	printf("Misère ? Oui (1) ou non (2)\nEntrez votre choix : ");
	do{scanf("%d", &misere);} while(misere != 1 && misere != 2);

	return ((choix == 1) ? init_jeu_defaut(misere%2) : init_jeu(misere%2));
}