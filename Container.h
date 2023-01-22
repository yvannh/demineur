#ifndef _CONTAINER_
#define _CONTAINER_

typedef enum { VOID, MINE } TYPE;

struct Case {
	bool discovered = false;
	bool marked = false;
	TYPE type;
	int mineAround = -1;
};

struct Grid {
	unsigned int capacity;
	unsigned int extension;
	Case* grid;
	unsigned int modulo;
	unsigned int nbMines;
};

/**
 * @brief Crée et renvoie une case selon les paramètres souhaités
 * @param[out] c : la case
 * @param[in] discovered : case découverte
 * @param[in] merked : case marquée
 * @param[in] type : type de la case
 * @param[in] mineAround : mine autour de la case
 */
Case createCase(bool discovered, bool marked, TYPE type, int mineAround);

/**
 * @brief Initialise un conteneur de cases vide
 * Allocation en mémoire dynamique du conteneur de cases de capacité capa
 * @see detruire, pour sa désallocation en fin d'utilisation
 * @param[out] g : le conteneur de cases
 * @param[in] capa : la capacité du conteneur
 * @param[in] e : pas d'extension du conteneur
 * @param[in] modulo : modulo du conteneur
 * @param[in] mines : nombre de mines dans le conteneur
 * @pre capa>0 et e > 0
 */
void initialize(Grid& g, unsigned int capa, unsigned int e, unsigned int modulo, unsigned int mines);

/**
 * @brief Désalloue un conteneur de cases en mémoire dynamique
 * @see initialiser, le conteneur de cases a déjà été alloué
 * @param[out] g : le conteneur de cases
 */
void destroy(Grid& g);

/**
 * @brief Lecture d'une case d'un conteneur de cases
 * @param[in] g : le conteneur de cases
 * @param[in] i : la position de l'item dans le conteneur
 * @return la case à la position i
 * @pre i < c.capacite
 */
Case read(const Grid& g, unsigned int i);

/**
 * @brief Ecrire une case dans un conteneur de cases
 * @param[out] g : le conteneur de cases
 * @param[in] i : la position où ajouter/modifier la case
 * @param[in] c : la case à écrire
 * @pre i < c.capacite
 */
void write(Grid& g, unsigned int i, const Case& c);



#endif