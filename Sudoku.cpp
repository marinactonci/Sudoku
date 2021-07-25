#include <iostream>
using namespace std;

class Solver {
public:
	Solver() {}

	// Vraca true ako je red zauzet (uneseni broj se nalazi u retku), inace false
	bool provjeraRed(int x[9][9], int red, int broj) {
		for (int i = 0; i < 9; i++) {
			if (broj != 0 && x[red][i] == broj)
				return true;
		}
		return false;
	}

	// Vraca true ako je stupac zauzet (uneseni broj se nalazi u stupcu), inace false
	bool provjeraStupac(int x[9][9], int stupac, int broj) {
		for (int i = 0; i < 9; i++) {
			if (broj != 0 && x[i][stupac] == broj)
				return true;
		}
		return false;
	}

	// Vraca true ako je 3x3 kvadrat zauzet (uneseni broj se nalazi u 3x3 kvadratu), inace false
	bool provjeraMalogKvadrata(int x[9][9], int mali_red, int mali_stupac, int b) {
		int red, stupac;
		for (red = 0; red < 3; red++) {
			for (stupac = 0; stupac < 3; stupac++) {
				if (b != 0 && x[red + mali_red][stupac + mali_stupac] == b)
					return true;
			}
		}
		return false;
	}

	// Vraca true ako je pozicija tocna, false ako je netocna
	bool provjeraSlobodno(int x[9][9], int red, int stupac, int broj) {
		if (!provjeraRed(x, red, broj)) {
			if (!provjeraStupac(x, stupac, broj)) {
				int mali_red = red - red % 3;
				int mali_stupac = stupac - stupac % 3;
				if (!provjeraMalogKvadrata(x, mali_red, mali_stupac, broj)) {
					return true;
				}
			}
		}
		return false;
	}

	// Vraca true ako je pozicija prazna (u ovom slucaju je prazna ako se na tom mjestu nalazi nula), inace false
	bool praznoMjesto(int x[9][9], int& red, int& stupac) {
		for (red = 0; red < 9; red++) {
			for (stupac = 0; stupac < 9; stupac++) {
				if (x[red][stupac] == 0)
					return true;
			}
		}
		return false;
	}

	// Vraca true ako je tablica rijesena, ako ne, vraca false
	bool sudokuSolver(int x[9][9]) {
		int red, stupac;
		if (praznoMjesto(x, red, stupac)) {
			for (int b = 1; b <= 9; b++) {
				if (provjeraSlobodno(x, red, stupac, b)) {
					x[red][stupac] = b;
					if (sudokuSolver(x) == true)
						return true;
					x[red][stupac] = 0;
				}
			}
			return false;
		}
		else
			return true;
	}

	~Solver() {}
};

class Sudoku : public Solver {
public:
	Sudoku() {}

	void run() {
		int odgovor;
		do {
			odgovor = izbornik(1);
			system("cls");
			odabirTezine(odgovor);
		} while (odgovor < 1 || odgovor > 5);
	}

	int izbornik(int p) {
		int answer;
		if (p == 1) {
			cout << "Odaberite tezinu:\n 1. Easy\n 2. Medium\n 3. Hard\n 4. Expert\n 5. Custom\n";
			cout << "Odgovor: ";
			cin >> answer;
			return answer;
		}
		else if (p == 2) {
			cout << endl << "Odaberite radnju:\n 1. Unos\n 2. Brisanje\n 3. Provjera rjesenja\n 4. Prikaz rjesenja\n";
			cout << "Odgovor: ";
			cin >> answer;
			return answer;
		}
		else if (p == 3) {
			cout << "\nZelite li nastaviti ili pocet ispocetka?\n 1. Nastavak\n 2. Restart\nOdgovor: ";
			cin >> answer;
			return answer;
		}
		else if (p == 4) {
			cout << "\nOdaberite radnju:\n 1. Igraj ispocetka\n 2. Izlaz iz programa\nOdgovor: ";
			cin >> answer;
			return answer;
		}
	}

	void odabirTezine(int odgovor) {
		int odabir, red, stupac, broj;
		if (odgovor == 1) {
			int easy[9][9] = {
				{ 0,0,0,  2,7,0,  0,9,0 },
				{ 0,9,0,  4,0,5,  8,1,7 },
				{ 0,0,3,  0,0,0,  0,0,5 },

				{ 0,0,0,  7,0,9,  1,2,3 },
				{ 0,0,4,  0,1,2,  0,8,0 },
				{ 1,0,0,  3,5,0,  0,4,0 },

				{ 6,5,0,  1,0,0,  4,0,0 },
				{ 0,3,2,  0,6,7,  9,0,1 },
				{ 9,1,0,  0,0,0,  0,3,8 }
			};
			cout << "Tezina: Easy\n";
			ispisTablice(easy);
			do {
				radnja(easy, easy_solved);
			} while (provjera == false);
		}
		if (odgovor == 2) {
			int medium[9][9] = {
				{ 0,0,0,  8,2,0,  0,0,0 },
				{ 0,0,0,  6,0,9,  0,0,1 },
				{ 9,0,4,  0,0,1,  0,0,0 },

				{ 0,9,0,  7,0,0,  2,8,0 },
				{ 0,0,0,  0,0,0,  0,5,7 },
				{ 7,0,5,  0,0,0,  0,0,0 },

				{ 0,7,8,  9,6,2,  0,0,5 },
				{ 0,2,0,  0,8,0,  7,0,3 },
				{ 0,6,0,  0,7,4,  0,2,0 }
			};
			cout << "Tezina: Medium\n";
			ispisTablice(medium);
			do {
				radnja(medium, medium_solved);
			} while (provjera == false);
		}
		if (odgovor == 3) {
			int hard[9][9] = {
				{ 6,0,0,  0,5,7,  1,0,0 },
				{ 0,0,0,  0,0,3,  0,0,5 },
				{ 0,1,0,  9,0,0,  2,0,0 },

				{ 0,0,0,  0,0,0,  7,0,0 },
				{ 2,8,1,  0,4,0,  6,0,0 },
				{ 0,3,0,  0,0,0,  0,0,2 },

				{ 0,0,0,  0,0,0,  0,1,4 },
				{ 0,5,8,  0,0,0,  0,0,7 },
				{ 0,0,7,  0,6,0,  8,0,0 }
			};
			cout << "Tezina: Hard\n";
			ispisTablice(hard);
			do {
				radnja(hard, hard_solved);
			} while (provjera == false);
		}
		if (odgovor == 4) {
			int expert[9][9] = {
				{ 9,8,0,  6,0,0,  0,3,1 },
				{ 0,0,7,  0,0,0,  0,0,0 },
				{ 6,0,0,  5,4,0,  0,0,0 },

				{ 0,0,0,  0,0,8,  3,7,4 },
				{ 0,0,0,  0,6,0,  0,0,0 },
				{ 0,0,0,  0,0,0,  9,0,2 },

				{ 0,3,2,  0,0,7,  4,0,0 },
				{ 0,4,0,  3,0,0,  0,1,0 },
				{ 0,0,0,  0,0,0,  0,0,0 }
			};
			cout << "Tezina: Expert\n";
			ispisTablice(expert);
			do {
				radnja(expert, expert_solved);
			} while (provjera == false);
		}
		if (odgovor == 5) {
			int custom[9][9], temp;
			int provjera_nova;
			int petlja_nova = 0;
			cout << "Tezina: Custom";
			cout << "\nUnesite zadanu sudoku tablicu za prikaz njenog rjesenja.\nNula oznacava prazno mjesto.\n";
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					do {
						cout << "Unesite " << j + 1 << ". element " << i + 1 << ". retka: ";
						cin >> temp;
						if (temp < 0 || temp>9) {
							cout << "Krivo unesen broj (interval od 1 do 9)!\n";
							petlja_nova = 1;
						}
						else if (provjeraRed(custom, i, temp) == true) {
							cout << "U redu se vec nalazi ovaj broj.\n";
							petlja_nova = 1;
						}
						else if (provjeraStupac(custom, j, temp) == true) {
							cout << "U stupcu se vec nalazi ovaj broj.\n";
							petlja_nova = 1;
						}
						else if (provjeraMalogKvadrata(custom, i - i % 3, j - j % 3, temp) == true) {
							cout << "U trenutnom 3x3 kvadratu se vec nalazi ovaj broj.\n";
							petlja_nova = 1;
						}
						else
							petlja_nova = 0;
						custom[i][j] = temp;
					} while (petlja_nova == 1);
				}
			}
			system("cls");
			cout << "Tezina: Custom\nPocetna tablica:\n";
			ispisTablice(custom);
			cout << endl;
			if (sudokuSolver(custom)) {
				cout << "Rijesena tablica:\n";
				ispisTablice(custom);
				provjera_nova = izbornik(4);
				do {
					if (provjera_nova == 1) {
						system("cls");
						run();
					}
					else if (provjera_nova == 2) {
						cout << "Izlaz...";
						exit(0);
					}
				} while (provjera_nova < 1 || provjera_nova > 2);
			}
			else
				cout << "\nZadatak nije moguce rijesit.";
		}
	}

	void radnja(int z[9][9], int z_solved[9][9]) {
		int odabir, red, stupac, broj, zavrsetak, petlja;
		odabir = izbornik(2);
		if (odabir == 1) {
			do {
				petlja = 0;
				cout << "\nUnesite red i stupac pozicije unosa te broj koji zelite unijet:\n";
				cout << "Red: ";
				cin >> red;
				cout << "Stupac: ";
				cin >> stupac;
				cout << "Broj: ";
				cin >> broj;
				if (red < 1 || red > 9) {
					cout << "Krivo unesen red (interval od 1 do 9)!\n";
					petlja = 1;
				}
				if (stupac < 1 || stupac > 9) {
					cout << "Krivo unesen stupac (interval od 1 do 9)!\n";
					petlja = 1;
				}
				if (broj < 1 || broj > 9) {
					cout << "Krivo unesen broj (interval od 1 do 9)!\n";
					petlja = 1;
				}
				if (z[red - 1][stupac - 1] != 0 && red >= 1 && red <= 9 && stupac >= 1 && stupac <= 9) {
					cout << "Pozicija je vec popunjena!\n";
					petlja = 1;
				}
			} while (petlja == 1);
			unos(z, red, stupac, broj);
			ispisTablice(z);
		}
		else if (odabir == 2) {
			do {
				petlja = 0;
				cout << "Unesite red i stupac pozicije brisanja:\n";
				cout << "Red: ";
				cin >> red;
				cout << "Stupac: ";
				cin >> stupac;
				if (red < 1 || red > 9) {
					cout << "Krivo unesen red (interval od 1 do 9)!";
					petlja = 1;
				}
				if (stupac < 1 || stupac > 9) {
					cout << "Krivo unesen stupac (interval od 1 do 9)!";
					petlja = 1;
				}
				if (z[red - 1][stupac - 1] == 0) {
					cout << "Ovo je vec prazno mjesto!\n";
					petlja = 1;
				}
			} while (petlja == 1);
			brisanje(z, red, stupac);
			ispisTablice(z);
		}
		else if (odabir == 3) {
			if (provjeraRjesenja(z, z_solved) == true) {
				cout << "Uspjesno rijesen zadatak!";
				provjera = true;
				do {
					cout << "\nZelite li ponovo igrati?\n1. Da\n2. Ne\nOdgovor: ";
					cin >> zavrsetak;
					if (zavrsetak == 1) {
						system("cls");
						run();
					}
					else if (zavrsetak == 2) {
						cout << "\nIzlaz...";
						exit(0);
					}
				} while (zavrsetak < 1 || zavrsetak > 2);
			}
			else if (provjeraRjesenja(z, z_solved) == false) {
				cout << "Zadatak je krivo rijesen!";
				do {
					odabir = izbornik(3);
					if (odabir == 1) {
						petlja = false;
					}
					else if (odabir == 2) {
						system("cls");
						run();
					}
				} while (odabir < 1 || odabir > 2);
				petlja = false;
			}
		}
		else if (odabir == 4) {
			if (sudokuSolver(z_solved)) {
				cout << endl << "Rijesena tablica: \n";
				ispisTablice(z_solved);
				do {
					cout << "\nZelite li ponovo igrat?\n1. Da\n2. Ne\nOdgovor: ";
					cin >> zavrsetak;
					if (zavrsetak == 1) {
						system("cls");
						run();
					}
					else if (zavrsetak == 2) {
						cout << "\nIzlazak iz igre...";
						exit(0);
					}
				} while (zavrsetak < 1 || zavrsetak > 2);
			}
			else
				cout << "Zadatak nije moguce rijesit.";
		}
	}

	void unos(int x[9][9], int red, int stupac, int broj) {
		x[red - 1][stupac - 1] = broj;
	}

	void brisanje(int x[9][9], int red, int stupac) {
		x[red - 1][stupac - 1] = 0;
	}

	bool provjeraRjesenja(int x[9][9], int y[9][9]) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (x[i][j] != y[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	void ispisTablice(int x[9][9]) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << x[i][j] << "  ";
				if (j == 2 || j == 5) {
					cout << "|  ";
				}
			}
			cout << endl;
			if (i == 2 || i == 5) {
				cout << "---------+-----------+----------";
				cout << endl;
			}
		}
	}

	~Sudoku() {}
private:
	int easy_solved[9][9] = {
		{ 5,8,1,  2,7,6,  3,9,4 },
		{ 2,9,6,  4,3,5,  8,1,7 },
		{ 7,4,3,  9,8,1,  2,6,5 },

		{ 8,6,5,  7,4,9,  1,2,3 },
		{ 3,7,4,  6,1,2,  5,8,9 },
		{ 1,2,9,  3,5,8,  7,4,6 },

		{ 6,5,8,  1,9,3,  4,7,2 },
		{ 4,3,2,  8,6,7,  9,5,1 },
		{ 9,1,7,  5,2,4,  6,3,8 }
	};
	int medium_solved[9][9] = {
		{ 6,1,3,  8,2,7,  5,4,9 },
		{ 2,5,7,  6,4,9,  8,3,1 },
		{ 9,8,4,  5,3,1,  6,7,2 },

		{ 1,9,6,  7,5,3,  2,8,4 },
		{ 8,3,2,  4,9,6,  1,5,7 },
		{ 7,4,5,  2,1,8,  3,9,6 },

		{ 3,7,8,  9,6,2,  4,1,5 },
		{ 4,2,9,  1,8,5,  7,6,3 },
		{ 5,6,1,  3,7,4,  9,2,8 }
	};
	int hard_solved[9][9] = {
		{ 6,9,4,  2,5,7,  1,3,8 },
		{ 8,7,2,  6,1,3,  9,4,5 },
		{ 5,1,3,  9,8,4,  2,7,6 },

		{ 4,6,9,  8,3,2,  7,5,1 },
		{ 2,8,1,  7,4,5,  6,9,3 },
		{ 7,3,5,  1,9,6,  4,8,2 },

		{ 9,2,6,  3,7,8,  5,1,4 },
		{ 1,5,8,  4,2,9,  3,6,7 },
		{ 3,4,7,  5,6,1,  8,2,9 }
	};
	int expert_solved[9][9] = {
		{ 9,8,4,  6,7,2,  5,3,1 },
		{ 2,5,7,  8,3,1,  6,4,9 },
		{ 6,1,3,  5,4,9,  8,2,7 },

		{ 5,6,1,  9,2,8,  3,7,4 },
		{ 4,2,9,  7,6,3,  1,8,5 },
		{ 3,7,8,  4,1,5,  9,6,2 },

		{ 8,3,2,  1,5,7,  4,9,6 },
		{ 7,4,5,  3,9,6,  2,1,8 },
		{ 1,9,6,  2,8,4,  7,5,3 }
	};
	bool provjera = false;
};

int main() {
	Sudoku game;
	game.run();

	return 0;
}