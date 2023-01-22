#include <iostream>
#include "Commands.h"
using namespace std;

/**
 * @brief Crée un problème
 * @param[in] grid : conteneur de cases
 */
void createProblem(Grid& grid) {
	unsigned int x, y, m, capa;
	do {
		cin >> x >> y >> m;
	} while (x < 3 || y < 3 || m < 1 || m > x*y);

	capa = x * y;

	initialize(grid, capa, x*y+1, y, m);
	setAllCases(grid, capa);
	
	cout << x << " " << y << " " << m << " ";
	setMines(grid, m, capa, -1);
	cout << endl;
}

/**
 * @brief Choisit des index aléatoires pour les mines
 * @param[in] grid : conteneur de cases
 * @param[in] capa : index à ne pas dépasser
 * @return l'index choisi
 */
int randomMines(Grid& grid, unsigned int capa) {
	int index;
	do {
		index = rand() % (capa);
	} while (!read(grid, index).type != MINE);

	cout << index << " ";
	
	return index;
}

/**
 * @brief Place les mines aux index choisis
 * @param[in] grid : le conteneur de cases
 * @param[in] m : nombre de mines à générer
 * @param[in] capa : index maximal
 * @param[in] index : index voulu
 */
void setMines(Grid& grid, unsigned int m, unsigned int capa, int index) {
	Case mine = createCase(false, false, MINE, -1);
	bool hasToRandom = false;

	if (index < 0) hasToRandom = true;

	for (unsigned int i = 0; i < m; i++) {
		if (hasToRandom == true) index = randomMines(grid, capa);

		write(grid, index, mine);
		updateCases(grid, index);
	}
}

/**
 * @brief Met à jour les cases autour d'une mine
 * @param[in] grid : le conteneur de cases
 * @param[in] index : l'index de la mine
 */
void updateCases(Grid& grid, unsigned int index) {
	Case updatedCase = createCase(false, false, VOID, 0);

	unsigned int mod = grid.modulo;
	int square = index - mod - 1;

	int t = 0;

	for (unsigned int i = 1; i < 10; i++) {

		if (isOutOfBorder(square, mod, grid.capacity, index) == false && read(grid, square).type != MINE) {
			updatedCase.mineAround = read(grid, square).mineAround + 1;
			if (!(square == 0 && index == mod - 1)) write(grid, square, updatedCase);
		}

		if (i % 3 == 0) {
			square += (mod - 3);
		}
		
		square++;
	}
}

/**
 * @brief Vérifie qu'un index ne soit pas hors de la grille
 * @param[in] index : index à vérifier
 * @param[in] mod : modulo de la grille
 * @param[in] capa : index maximal
 * @param[in] idxMine : index de la mine
 * @return index n'est pas hors de bordure
 */
bool isOutOfBorder(int index, int mod, int capa, int idxMine) {
	if (index < 0 || index >= capa) return true;
	if (idxMine % mod < mod - 2 && index % mod == mod - 1 && (index + 1) % mod == 0) return true;
	if (idxMine % mod > 1 && index % mod == 0 && (index - 1) % mod == mod - 1) return true;
	else return false;
}

/**
 * @brief Initialise toutes les cases de la grille
 * @param[in] grid : le conteneur de cases
 * @param[in] loop : nombre de cases de la grille
 */
void setAllCases(Grid& grid, int loop) {
	Case c = createCase(false, false, VOID, 0);

	for (int i = 0; i < loop; i++) {
		write(grid, i, c);
	}
}

/**
 * @brief Crée une grille
 * @param[in] grid : le conteneur de cases
 */
void createGrid(Grid& grid) {
	unsigned int x, y, m, c, capa, tempM;
	char s[10];

	do {
		cin >> x >> y >> m;
	} while (x < 3 || y < 3 || m < 1 || m > x*y);

	capa = y * x;
	initialize(grid, capa, x * y + 1, y, m);
	setAllCases(grid, capa);

	for (int i = 0; i < m; i++) {
		cin >> tempM;

		setMines(grid, m, capa, tempM);
	}

	do {
		cin >> c;
	} while (c < 0);


	for (int i = 0; i < c; i++) {
		cin >> s;
		
		//strokeHistory(grid, *s);
	}

	display(grid, x, y);
}

/**
 * @brief Met à jour les cases selon le coup joué
 * @param[in] grid : le conteneur de cases
 * @param[in] stroke : l'entrée console
 */
void strokeHistory(Grid& grid, char& stroke) {
	Case updateCase = createCase(false, false, VOID, -1);
	char action;
	unsigned int caseAction;

	sscanf(&stroke, "%s%u", &action, &caseAction);

	updateCase.discovered = read(grid, caseAction).discovered;
	updateCase.marked = read(grid, caseAction).marked;
	updateCase.type = read(grid, caseAction).type;
	updateCase.mineAround = read(grid, caseAction).mineAround;

	if (action == 'D') {
		updateCase.discovered = true;

		write(grid, caseAction, updateCase);
	}

	if (action == 'M') {
		updateCase.marked = true;

		write(grid, caseAction, updateCase);
	}
}

/**
 * @brief Affiche la grille
 * @param[in] grid : le conteneur de cases
 * @param[in] x : nombre de colonnes
 * @param[in] y : nombre de lignes
 */
void display(Grid& grid, unsigned int x, unsigned int y) {

	int modulo = grid.modulo, index = 0;

	cout << x << " " << y << endl;
	for (int iGrid = 0; iGrid < grid.modulo; iGrid++) {
		for (int i = 0; i < modulo; i++) {
			cout << " ___";
		}
		cout << endl;

		for (int line = 0; line < modulo; line++) {
			cout << "| ";
			if (grid.grid[iGrid].discovered == false && grid.grid[iGrid].marked == false) cout << ". ";
			else if (grid.grid[iGrid].marked == true) cout << "x ";
			else if (grid.grid[iGrid].type == MINE && grid.grid[iGrid].discovered == false && grid.grid[iGrid].marked == false) cout << "m ";
			else cout << grid.grid[iGrid].mineAround << " ";
			index++;
		}
		cout << "|" << endl;
	}

	for (int i = 0; i < modulo; i++) {
		cout << " ___";
	}

	cout << endl;
}

/**
 * @brief Vérifie quelle commande exécuter
 * @param[in] grid : le conteneur de cases
 * @param[in] command : numéro d'entrée de la commande
 */
void commandCheck(Grid& grid, int command) {
	switch (command)
	{
	case 1:
		createProblem(grid);
		break;
	case 2:
		createGrid(grid);
		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	default:
		cout << "Commande inconnue\n";
		break;
	}
}