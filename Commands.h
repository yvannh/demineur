#ifndef _COMMANDS_
#define _COMMANDS_

#include <iostream>
#pragma warning(disable:4996)
#include "Container.h"
using namespace std;

/**
 * @brief Crée un problème
 * @param[in] grid : conteneur de cases
 */
void createProblem(Grid& grid);

/**
 * @brief Choisit des index aléatoires pour les mines
 * @param[in] grid : conteneur de cases
 * @param[in] capa : index à ne pas dépasser
 * @return l'index choisi
 */
int randomMines(Grid& grid, unsigned int capa);

/**
 * @brief Place les mines aux index choisis
 * @param[in] grid : le conteneur de cases
 * @param[in] m : nombre de mines à générer
 * @param[in] capa : index maximal
 * @param[in] index : index voulu
 */
void setMines(Grid& grid, unsigned int m, unsigned int capa, int index);

/**
 * @brief Met à jour les cases autour d'une mine
 * @param[in] grid : le conteneur de cases
 * @param[in] index : l'index de la mine
 */
void updateCases(Grid& g, unsigned int index);

/**
 * @brief Vérifie qu'un index ne soit pas hors de la grille
 * @param[in] index : index à vérifier
 * @param[in] mod : modulo de la grille
 * @param[in] capa : index maximal
 * @param[in] idxMine : index de la mine
 * @return index n'est pas hors de bordure
 */
bool isOutOfBorder(int index, int mod, int capa, int idxMine);

/**
 * @brief Initialise toutes les cases de la grille
 * @param[in] grid : le conteneur de cases
 * @param[in] loop : nombre de cases de la grille
 */
void setAllCases(Grid& g, int loop);

/**
 * @brief Crée une grille
 * @param[in] grid : le conteneur de cases
 */
void createGrid(Grid& grid);

/**
 * @brief Met à jour les cases selon le coup joué
 * @param[in] grid : le conteneur de cases
 * @param[in] stroke : l'entrée console
 */
void strokeHistory(Grid& grid, char& stroke);

/**
 * @brief Affiche la grille
 * @param[in] grid : le conteneur de cases
 * @param[in] x : nombre de colonnes
 * @param[in] y : nombre de lignes
 */
void display(Grid& grid, unsigned int x, unsigned int y);

/**
 * @brief Vérifie quelle commande exécuter
 * @param[in] grid : le conteneur de cases
 * @param[in] command : numéro d'entrée de la commande
 */
void commandCheck(Grid& grid, int command);

#endif