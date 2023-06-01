#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#define STATUS_PATH "../../status.txt"
#define ROZKAZY_PATH "../../rozkazy.txt"
#define MAP_PATH "../../mapa.txt"
#define TEMP_STATUS_PATH "../../temp_status.txt"


//klasa gra (mapa,złoto i produkcja ktora runda)

enum class Jednostki { Knight, Swordsman, Archer, Pikeman, Ram, Catapult, Worker, Base, size };

class Jednostka
{
public:
	Jednostka(const std::string& typ, unsigned int id, unsigned int x, unsigned int y, int wytrzymalosc, const std::string& produkcja);
	~Jednostka();
	void setTypJednostki(const std::string& typ);

private:
	Jednostki m_typJednostki;
	unsigned int m_ID;
	unsigned int m_x;
	unsigned int m_y;
	int m_wytrzymalosc;
	std::string m_jednostkaProdukowana;

};

Jednostka::Jednostka(const std::string& typ, unsigned int id, unsigned int x, unsigned int y, int wytrzymalosc, const std::string& produkcja)
	:m_ID(id), m_x(x), m_y(y), m_wytrzymalosc(wytrzymalosc)
{
	setTypJednostki(typ);

}

Jednostka::~Jednostka()
{
}

void Jednostka::setTypJednostki(const std::string& typ)
{
	if (typ == "K") {
		m_typJednostki = Jednostki::Knight;
	}
	else if (typ == "S") {
		m_typJednostki = Jednostki::Swordsman;
	}
	else if (typ == "A") {
		m_typJednostki = Jednostki::Archer;
	}
	else if (typ == "P") {
		m_typJednostki = Jednostki::Pikeman;
	}
	else if (typ == "R") {
		m_typJednostki = Jednostki::Ram;
	}
	else if (typ == "C") {
		m_typJednostki = Jednostki::Catapult;
	}
	else if (typ == "W") {
		m_typJednostki = Jednostki::Worker;
	}
	else if (typ == "B") {
		m_typJednostki = Jednostki::Base;
	}
}


const size_t TablicaObrazen[(size_t)Jednostki::size][(size_t)Jednostki::size] =
{
	{35, 35, 35, 35, 35, 50, 35, 35},    // knight
	{30, 30, 30, 20, 20, 30, 30, 30},    // swordsman
	{15, 15, 15, 15, 10, 10, 15, 15},    // archer
	{35, 15, 15, 15, 15, 10, 15, 10},	 // pikeman
	{10, 10, 10, 10, 10, 10, 10, 50},	 // ram
	{40, 40, 40, 40, 40, 40, 40, 50},	 // catapult
	{5, 5, 5, 5, 5, 5, 5, 1},			 // worker
	{0, 0, 0, 0, 0, 0, 0, 0}			 // base

};
const size_t TabelaLiczbyRuchowNaKolejke[(size_t)Jednostki::size] =
{
	5, // knight
	2, // swordsman
	2, // archer
	2, // pikeman
	2, // ram
	2, // catapult
	2, // worker
	0  // base
};
const size_t TabelaZasieguAtaku[(size_t)Jednostki::size] =
{
	1, // knight
	1, // swordsman
	5, // archer
	2, // pikeman
	1, // ram
	7, // catapult
	1, // worker
	0  // base
};
const size_t TabelaWytrzymalosci[(size_t)Jednostki::size] =
{
	70, // knight
	60, // swordsman
	40, // archer
	50, // pikeman
	90, // ram
	50, // catapult
	20, // worker
	200 // base
};
const size_t TabelaKosztu[(size_t)Jednostki::size] =
{
	400, // knight
	250, // swordsman
	250, // archer
	200, // pikeman
	500, // ram
	800, // catapult
	100, // worker
	0   // base
};
const size_t TabelaCzasuBudowy[(size_t)Jednostki::size] =
{
	5, // knight
	3, // swordsman
	3, // archer
	3, // pikeman
	4, // ram
	6, // catapult
	2, // worker
	0  // base
};


//przekazywac pliki jako argc argv/w linii kodu

int main()
{
	std::vector <Jednostka> P_jednostki;
	std::vector <Jednostka> E_jednostki;
	//Otwieranie plików 
	std::ifstream status(STATUS_PATH, std::ios::in);//otwierany status w trybie do odczytu i zapisu
	std::ofstream rozkazy(ROZKAZY_PATH, std::ios::trunc);//otwierane rozkazy w trybie zapisu i czyścimy
	std::ifstream mapa(MAP_PATH); // otwierana mapa w trybie odczytu

	if (!status) {
		std::cerr << "Nie można otworzyć pliku status." << std::endl;
		return 1;
	}
	if (!rozkazy) {
		std::cerr << "Nie można otworzyć pliku rozkazy." << std::endl;
		return 1;
	}
	if (!mapa) {
		std::cerr << "Nie można otworzyć pliku mapa." << std::endl;
		return 1;
	}

	std::cout << "otwarto pliki" << std::endl;

	if (status.peek() == std::ifstream::traits_type::eof()) {
		// Sprawdzanie, czy plik jest pusty
		std::ofstream w_status(TEMP_STATUS_PATH); // Otwieranie pliku w trybie zapisu
		if (status.is_open()) {
			w_status << "2000" << std::endl;
			std::cout << "dopisanie zlota" << std::endl;
			int indexLini = 0; //tymczasowa wartośc dla koordynatu x
			if (mapa.is_open())
			{
				std::string linia;
				while (std::getline(mapa, linia)) //analizator mapy 
				{
					for (size_t index = 0; index < linia.length(); index++)
					{
						std::cout << linia[index];
						switch (linia[index])
						{
						case '1':
							w_status << "P B 1 " << indexLini << " " << index << " 200 0" << std::endl;
							std::cout << "dopisanie jednostki";
							break;
						case '2':
							w_status << "E B 2 " << indexLini << " " << index << " 200 0" << std::endl;
							std::cout << "dopisanie jednostki";
							break;
						}
					}
					indexLini++;
				}

			}
			w_status.close(); // Zamykanie pliku
			status.close();
			std::remove(STATUS_PATH); // Usuwanie oryginalnego pliku
			std::rename(TEMP_STATUS_PATH, STATUS_PATH); // Zmiana nazwy tymczasowego pliku na nazwę oryginalnego pliku

			std::cout << "Plik był pusty. Uzupelniono podstawowymi informacjami" << std::endl;
		}
		else {
			std::cout << "Nie można otworzyć pliku do zapisu." << std::endl;
		}
	}
	else
	{
		// Plik nie jest pusty, odczytywanie linia po linii 
		if (status.is_open()) {

			std::string linia;

			while (std::getline(status, linia)) {
				//zebrac w tym miejscu informacje o istniejących jednostkach
				std::stringstream ss(linia);

				std::string przynaleznosc, typ, produkcja;
				int id, x, y, wytrzymalosc;

				ss >> przynaleznosc >> typ >> id >> x >> y >> wytrzymalosc >> produkcja;
				if (przynaleznosc == "P")
				{
					Jednostka unit(typ, id, x, y, wytrzymalosc, produkcja);
					P_jednostki.push_back(unit);
				}
				if (przynaleznosc == "E")
				{
					Jednostka unit(typ, id, x, y, wytrzymalosc, produkcja);
					E_jednostki.push_back(unit);
				}
				if (std::isdigit(przynaleznosc[0]))
				{
					std::cout << "zloto" << std::endl;
				}
			}
			status.close();
		}

		if (mapa.is_open())
		{
			std::string linia;
			while (std::getline(status, linia)) {
				//zebrac w tym miejscu informacje o istniejących jednostkach

			}
			status.close();
		}

	}



	//std::cout << "status jest pusty";//
	//if (status.is_open()) {
	//	status << "2000" << std::endl; // dopisanie złota

		//std::cout << "dopisanie zlota";
		//int indexLini = 0; //tymczasowa wartoś dla koordynatu x
		//while (std::getline(mapa, linia)) //analizator mapy dobrze by było gdyby sie wykonał tylko przy pierwszym wykoaniu
		//{
		//	for (size_t index = 0; index < linia.length(); index++)
		//	{
		//		std::cout << linia[index];
		//		switch (linia[index])
		//		{
		//		case '1':
		//			status << "P B 1 " << indexLini << " " << index << " 100 0" << std::endl;
		//			std::cout << "dopisanie jednostki";
		//			break;
		//		case '2':
		//			status << "E B 2 " << indexLini << " " << index << " 100 0" << std::endl;
		//			std::cout << "dopisanie jednostki";
		//			break;
		//		}
		//	}
		//	std::cout << std::endl;
		//	indexLini++;
		//}


	//}
	//else {
	//	std::cout << "status nie jest pusty";//
	//	std::cout << "Plik nie jest pusty." << std::endl;//rozgrywka trwa 
	//	bool flagMoney = false;
	//	while (std::getline(status, linia)) //ANAL izator statusu 
	//	{
	//		if (!flagMoney)
	//		{
	//			for (char znak : linia) {
	//				if (std::isdigit(znak)) {
	//					flagMoney = true;
	//					//to pobrać stan pieniedzy do jakiejs zmiennej
	//					continue;
	//				}
	//			}

	//		}
	//		for (auto iter : linia) {
	//			//pobieranie z lini informacji o jednostkach 

	//		}
	//	}
	//}
	//std::cout << "koniec programu???";


	//if (rozkazy.peek() == std::ifstream::traits_type::eof()) {

	//	//Plik jest pusty

	//	int xValueR = 0;//tymczasowa wartoś dla koordynatu x
	//	int yValueR = 0;//tymczasowa wartoś dla koordynatu y
	//	while (std::getline(rozkazy, linia)) 
	//	{
	//		for (auto iter : linia)
	//		{
	//			switch (iter)
	//			{
	//			case 'M':
	//				rozkazy << " 12 M " << xValueR << " " << yValueR << " " << std::endl;
	//				break;
	//			case 'A':
	//				rozkazy << ID_Gracza << " A " << ID_Przeciwnika << std::endl;
	//				break;
	//			case 'B':
	//				rozkazy << ID_Bazy_G << " B " << " A " << std::endl;
	//				break;
	//			}
	//			yValueR++;
	//		}
	//		yValueR = 0;
	//		xValueR++;
	//	}

	//}
	//else {
	//	std::cout << "Plik nie jest pusty." << std::endl;

	//}


	//status.close();
	rozkazy.close();
	mapa.close();
	return 0;
}