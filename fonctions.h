#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Contient un entier taille qui représente le nombre de lignes, un booléen misère qui représente les règles du jeu,
 *  et un tableau d'entiers qui représente le nombre d'allumettes par ligne, 
 * ainsi qu'un entier max, qui représente le nombre d'allumettes de la ligne la plus chargée
 * 
 * @param taille;
 * @param misere;
 * @param lignes;
 * @param max
 * 
 */
typedef struct jeu {
    int taille;
    bool misere;
    int* lignes;
    int max;
} jeu;

/**
 * @brief Initialise un tableau de taille taille, et le remplit ensuite ligne par ligne en demandant au joueur le nombre d'allumettes qu'il veut
 * 
 * @param taille
 * @param misere
 * 
 * @return char** 
 */
jeu init_jeu(bool misere);

/**
 * @brief Renvoie un jeu configuré en 5 lignes de respectivement 1, 3, 5 et 7 allumettes, en appliquant la règle misère si précisé
 * 
 * @param misere 
 * @return jeu 
 */
jeu init_jeu_defaut(bool misere);

/**
 * @brief affiche le jeu dans le terminal
 * 
 * @param jeu
 * 
 */
void print_jeu(jeu j);

/**
 * @brief libère la mémoire allouée pour le jeu
 * 
 * @param jeu 
 */
void free_jeu(jeu j);

/**
 * @brief demande au joueur sur quelle ligne il veut retirer des allumettes, puis combien
 * 
 * @param grille 
 * @param joueur 
 * @return char 
 */
void tour_humains(jeu* j);

/**
 * @brief vérifie qu'un des joueurs a gagné
 * 
 * @param grille 
 * @return true 
 * @return false 
 */
bool check_victoire(jeu j);

/**
 * @brief appelle toutes les fonctions précédentes pour faire une partie
 * 
 */
void jeu_humains();

/**
 * @brief Trouve le nombre d'allumettes de la ligne la plus chargée, et met à jour j->max
 * 
 * @param j 
 */
void check_max(jeu* j);

/**
 * @brief Demande au joueur le type de partie qu'il veut jouer (défaut ou autre, misère ou non), la crée et la renvoie
 * 
 * @return jeu 
 */
jeu param_jeu();

#endif