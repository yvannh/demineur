#include <iostream>
#include <cassert>
#include "Container.h"
using namespace std;

/**
 * @brief Cr�e et renvoie une case selon les param�tres souhait�s
 * @param[out] c : la case
 * @param[in] discovered : case d�couverte
 * @param[in] merked : case marqu�e
 * @param[in] type : type de la case
 * @param[in] mineAround : mine autour de la case
 */
Case createCase(bool discovered, bool marked, TYPE type, int mineAround) {
	Case c;
	c.discovered = discovered;
	c.marked = marked;
	c.type = type;
	c.mineAround = mineAround;
	
	return c;
}


/**
 * @brief Initialise un conteneur de cases vide
 * Allocation en m�moire dynamique du conteneur de cases de capacit� capa
 * @see detruire, pour sa d�sallocation en fin d'utilisation
 * @param[out] g : le conteneur de cases
 * @param[in] capa : la capacit� du conteneur
 * @param[in] e : pas d'extension du conteneur
 * @param[in] modulo : modulo du conteneur
 * @param[in] mines : nombre de mines dans le conteneur
 * @pre capa>0 et e > 0
 */
void initialize(Grid& g, unsigned int capa, unsigned int e, unsigned int modulo, unsigned int mines) {
	assert(capa > 0 && e > 0);
	g.capacity = capa;
	g.grid = new Case[capa];
	g.extension = e;
	g.modulo = modulo;
	g.nbMines = mines;
}

/**
 * @brief D�salloue un conteneur de cases en m�moire dynamique
 * @see initialiser, le conteneur de cases a d�j� �t� allou�
 * @param[out] g : le conteneur de cases
 */
void destroy(Grid& g) {
	delete g.grid;
	g.grid = NULL;
	g.capacity = 0;
	g.extension = 0;
	g.nbMines = 0;
}

/**
 * @brief Lecture d'une case d'un conteneur de cases
 * @param[in] g : le conteneur de cases
 * @param[in] i : la position de l'item dans le conteneur
 * @return la case � la position i
 * @pre i < c.capacite
 */
Case read(const Grid& g, unsigned int i) {
	assert(i < g.capacity);

	return g.grid[i];
}

/**
 * @brief Ecrire une case dans un conteneur de cases
 * @param[out] g : le conteneur de cases
 * @param[in] i : la position o� ajouter/modifier la case
 * @param[in] c : la case � �crire
 * @pre i < c.capacite
 */
void write(Grid& g, unsigned int i, const Case& c) {
	if (i >= g.capacity) {

		unsigned int newCapacity = (i + 1) * g.extension;
		Case* newGrid = new Case[newCapacity];

		for (int i = 0; i < g.capacity; i++) {
			newGrid[i] = g.grid[i];
		}

		unsigned int newModulo = g.modulo, newNbMines = g.nbMines;

		delete g.grid;
		g.grid = newGrid;
		g.capacity = newCapacity;
		g.modulo = newModulo;
		g.nbMines = newNbMines;
	}

	g.grid[i] = c;
}