#include "AI.h"
#include <time.h>
 
 void menu(){
	printf("Bienvenue ! Voulez-vous jouer seul (1) ou contre un autre joueur (2) ?\n>");
    int choix = 0;
    while(choix < 1 || choix > 2){
        printf("Entrez 1 ou 2:\n>");
        scanf("%d", &choix);
    }

    if(choix == 2) jeu_humains();
    else {
        printf("Voulez-vous jouer contre une IA basique (1) ou dure (2) ?\n");
		choix = 0;
		while(choix < 1 || choix > 2){
			printf("Entrez 1 ou 2\n>");
			scanf("%d", &choix);
		}
		if(choix == 1) jeu_ia(choix_tour(), tour_ia_simple);
		else if(choix == 2) jeu_ia(choix_tour(), tour_ia_hard);
    }
 }

 void tour_ia_simple(jeu* j){
	int ligne;
	do{
		ligne = rand()%j->taille;
	} while(!j->lignes[ligne]); //on ne peut pas piocher sur une ligne vide
	int n = rand()%j->lignes[ligne];
	n++; //on ne peut pas retirer 0 allumettes
	j->lignes[ligne] -= n;
	
	printf("L'ordinateur a pris %d allumettes à la ligne %d :\n", n, ligne);
	check_max(j);
 }

void jeu_ia(int ia, void(*tour)(jeu*)){
	jeu j = param_jeu();
	int joueur = 0;
	print_jeu(j);

	do{
		if(joueur == ia) tour(&j);
		else(tour_humains(&j));
		joueur = !joueur;
		print_jeu(j);
	} while(!check_victoire(j));

	if((j.misere && (joueur == ia)) || (!j.misere && (joueur != ia))) printf("\nPerdu...\n"); //si l'IA a joué le dernier coup en misère ou que le joueur a joué le dernier coup sans misère, il gagne
	else printf("\nFélicitations !\n"); //sinon il perd

	free_jeu(j);
 }

int choix_tour(){
	printf("Voulez-vous jouer en premier (1), en deuxième(2), ou n'importe (3) ?\n>");
	int choix;
	do {scanf("%d", &choix);} while(choix < 1 && choix > 3);
	if(choix == 3) return rand()%2;
	return choix%2; //si le joueur joue en premier, l'ia joue en deuxième (on renvoie 1), et inverserment (on renvoie 0)
}


void tour_ia_hard(jeu* j){
	int nim = nim_sum(*j);

	if(!nim || (j->max == 1)) { //si la somme est nulle ou qu'il ne reste que des lignes à 1 allumette, l'ordinateur perd forcément (ou le coup est forcé), et joue donc un coup au hasard
		tour_ia_simple(j);
		return; 
	}

	if(j->misere && check_lines_at_one(*j)){ //si toutes les lignes sauf une sont à 1 et qu'on joue en misère, il faut laisser un nombre impair de lignes
		for(int i = 0; i < j->taille; i++){// on parcourt toutes les lignes jusqu'à trouver celle qui a plus d'une allumette
			if(j->lignes[i] > 1) {
				nim = j->lignes[i]; //on retire toutes les allumettes de la ligne
				j->lignes[i] = 0;
				if(!nim_sum(*j)) { //si ça fait perdre l'ordinateur, on remet une allumette sur la ligne
					j->lignes[i] = 1;
					nim--;
				}
				printf("L'ordinateur a pris %d allumettes à la ligne %d :\n", nim, i);
				check_max(j);
				return;
			}
		}
	}

	//si la somme de nim est positive et que plusieurs lignes sont remplies, on bruteforce la bonne solution
	for(int i = 0; i < j->taille; i++){ //on parcourt toutes les lignes jusqu'à trouver un bon coup
		if(j->lignes[i]){ //on vérifie déjà qu'on peut retirer des allumettes
			for(int n  = 1; n <= j->lignes[i]; n++){
				j->lignes[i] -= n; 
				if(nim_sum(*j)) j->lignes[i] += n; //si le coup n'était pas bon, on remet les allumettes
				else { //si le coup était bon, on termine le tour
					printf("L'ordinateur a pris %d allumettes à la ligne %d :\n", n, i);
					check_max(j);
					return;
				}
			}
		}
	}

	printf("nim = %d, l'ia passe son tour (et ce n'est pas normal)\n", nim);
}


int nim_sum(jeu j){
	int sum = 0;
	for(int i = 0; i < j.taille; i++) sum = sum ^ j.lignes[i]; //on XOR toutes les lignes en binaire
	return sum;
}

bool check_lines_at_one(jeu j){
	int count = 0;
	for(int i = 0; i < j.taille; i++){
		if(j.lignes[i] > 1) count++;
		if(count > 1) return false; //si plus d'une ligne a plus d'une allumette, on renvoie false
	}

	return true;
}