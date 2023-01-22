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
 * @brief Cr�e et renvoie une case selon les param�tres souhait�s
 * @param[out] c : la case
 * @param[in] discovered : case d�couverte
 * @param[in] merked : case marqu�e
 * @param[in] type : type de la case
 * @param[in] mineAround : mine autour de la case
 */
Case createCase(bool discovered, bool marked, TYPE type, int mineAround);

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
void initialize(Grid& g, unsigned int capa, unsigned int e, unsigned int modulo, unsigned int mines);

/**
 * @brief D�salloue un conteneur de cases en m�moire dynamique
 * @see initialiser, le conteneur de cases a d�j� �t� allou�
 * @param[out] g : le conteneur de cases
 */
void destroy(Grid& g);

/**
 * @brief Lecture d'une case d'un conteneur de cases
 * @param[in] g : le conteneur de cases
 * @param[in] i : la position de l'item dans le conteneur
 * @return la case � la position i
 * @pre i < c.capacite
 */
Case read(const Grid& g, unsigned int i);

/**
 * @brief Ecrire une case dans un conteneur de cases
 * @param[out] g : le conteneur de cases
 * @param[in] i : la position o� ajouter/modifier la case
 * @param[in] c : la case � �crire
 * @pre i < c.capacite
 */
void write(Grid& g, unsigned int i, const Case& c);



#endif