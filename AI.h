#ifndef DEF_AI
#define DEF_AI

#include "fonctions.h"

/**
 * @brief affiche le menu du jeu : propose de jouer à un ou deux joueurs, et lance la fonction requise en conséquence
 * 
 */
void menu();

/**
 * @brief prend en entrée le numéro de l'ordinateur (0 ou 1) et joue une partie en utilisant des coups aléatoires
 * 
 * @param ia 
 */
void jeu_ia_simple(int ia);

/**
 * @brief sélectionne une ligne aléatoire, et y retire un nombre aléatoire d'allumettes
 * 
 * @param jeu 
 */
void tour_ia_simple(jeu* j);

/**
 * @brief prend en entrée le numéro de l'ortdinateur (0 ou 1) et joue une partie en utilisant des coups parfaits si possible
 * 
 * @param ia 
 */
void jeu_ia_hard(int ia);

/**
 * @brief joue un coup parfait si possible (en utilisant la somme de NIM), appelle tour_ia_simple() sinon
 * 
 * @param jeu 
 * @param joueur 
 */
void tour_ia_hard(jeu* j);

/**
 * @brief demande au joueur quel s'il veut jouer en premier, en deuxième, ou s'il veut jouer au hasard, et renvoie l'int correspondant *QUI SERA UTILISÉ POUR L'IA !*
 * 
 * @return int 
 */
int choix_tour();

/**
 * @brief Calcule la somme de NIM du jeu (c'est à dire la somme binaire des différentes rangées)
 * 
 * @param j 
 * @return int 
 */
int nim_sum(jeu j);

/**
 * @brief vérifie si toutes les lignes sauf une ont 0 ou 1 allumette
 * 
 * @param j 
 * @return true 
 * @return false 
 */
bool check_lines_at_one(jeu j);

#endif