#include <iostream>
#include <string>                     
#include <fstream>                    

using namespace std;

class Etaj {

private:
	const int nrEtaj;
	int nrSali;
	int* sali;
	char* caleAcces;
	static string cinematograf;

public:
	Etaj() : nrEtaj(0) {
		nrSali = 0;
		sali = nullptr;
		caleAcces = nullptr;
	}

	Etaj(int nrEtaj, int nrSali, int* sali, const char* caleAcces) : nrEtaj(nrEtaj) {
		if (nrSali > 0) {
			this->nrSali = nrSali;
		}
		else {
			this->nrSali = 0;
		}
		if (sali != nullptr && nrSali > 0) {
			this->sali = new int[nrSali];
			for (int i=0; i < nrSali; i++) {
				this->sali[i] = sali[i];
			}
		}
		else {
			this->sali = nullptr;
		}
		if (caleAcces != nullptr) {
			this->caleAcces = new char[strlen(caleAcces) + 1];
			strcpy_s(this->caleAcces, strlen(caleAcces) + 1, caleAcces);
		}
		else {
			this->caleAcces = nullptr;
		}
		

	}

	Etaj(const Etaj& e) : nrEtaj(e.nrEtaj) {
		
		if (e.nrSali > 0 && e.sali != nullptr) {
			nrSali = e.nrSali;
			sali = new int[e.nrSali];
			for (int i = 0; i < e.nrSali; i++) {
				sali[i] = e.sali[i];
			}
		}
		else {
			nrSali = 0;
			sali = nullptr;
		}
		if (e.caleAcces != nullptr) {
			caleAcces = new char[strlen(e.caleAcces) + 1];
			strcpy_s(caleAcces, strlen(e.caleAcces) + 1, e.caleAcces);
		}
		else {
			caleAcces = nullptr;
		}
	}


	~Etaj() {
		if (sali != nullptr) {
			delete[] sali;
		}
		if (caleAcces != nullptr) {
			delete[] caleAcces;
		}
	}

	Etaj& operator=(const Etaj& e) {
		if (sali != nullptr) {
			delete[] sali;
		}
		if (caleAcces != nullptr) {
			delete[] caleAcces;
		}

		if (e.nrSali > 0 && e.sali != nullptr) {
			nrSali = e.nrSali;
			sali = new int[e.nrSali];
			for (int i = 0; i < e.nrSali; i++) {
				sali[i] = e.sali[i];
			}
		}
		else {
			nrSali = 0;
			sali = nullptr;
		}
		if (e.caleAcces != nullptr) {
			caleAcces = new char[strlen(e.caleAcces) + 1];
			strcpy_s(caleAcces, strlen(e.caleAcces) + 1, e.caleAcces);
		}
		else {
			caleAcces = nullptr;
		}
		return *this;
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrSali && sali != nullptr) {
			return sali[index];
		}
		else {
			throw exception("Index invalid!");
		}
	}

	Etaj operator+(int saliNoi) {
		Etaj copie = *this;
		copie.nrSali += saliNoi;
		return copie;
	}

	Etaj operator++() {
		this->nrSali++;
		return *this;
	}

	Etaj operator++(int i) {
		Etaj copie = *this;
		this->nrSali++;
		return copie;
	}

	explicit operator int() {
		return nrSali;
	}

	bool operator!() {
		return nrSali > 0;
	}

	bool operator<(Etaj e) {
		return this->nrSali < e.nrSali;
	}

	bool operator==(Etaj e) {
		if (this->nrSali != e.nrSali) {
			return false;
		}
		for (int i = 0; i < this->nrSali; i++) {
			if (this->sali[i] != e.sali[i]) {
				return false;
			}
		}
		if (strcmp(this->caleAcces, e.caleAcces) != 0 ) {
			return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream&, Etaj);
    friend istream& operator>>(istream&, Etaj&);

};

ostream& operator<<(ostream& out, Etaj e)
{
	out << "Numarul etajului: " << e.nrEtaj << endl;
	out << "Numarul de sali: " << e.nrSali << endl;
	if (e.sali != nullptr && e.nrSali > 0) {
		for (int i = 0; i < e.nrSali; i++) {
			out << "Sala " << i+1 << " : " << e.sali[i] << endl;
		}
	}
	else {
		out << "Nu exista nicio sala!" << endl;
	}
	if (e.caleAcces != nullptr) {
		out << "Calea de acces: " << e.caleAcces << endl;
	}
	else {
		out << "Nu exista nicio cale de acces!" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Etaj& e)
{
	cout << "Cate sali se gasesc la acest etaj? ";
	in >> e.nrSali;
	if (e.sali != nullptr) {
		delete[] e.sali;
	}
	if (e.nrSali > 0) {
		e.sali = new int[e.nrSali];
		for (int i = 0; i < e.nrSali; i++)
		{
			cout << "Sala " << i << " : ";
			in >> e.sali[i];
		}
	}
	else {
		e.sali = nullptr;
		e.nrSali = 0;
	}
	cout << "Calea de acces: ";
	if (e.caleAcces != nullptr) {
		delete[] e.caleAcces;
	}
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	e.caleAcces = new char[strlen(buffer) + 1];
	strcpy_s(e.caleAcces, strlen(buffer) + 1, buffer);
	return in;
}

class Film {
	
private:
	const int id_Film;
	char* numeFilm;       
	int durataMinute;                   
	int nrRecenzii;
	double* recenzii;
	static string accesoriu;

public:
	Film() : id_Film(0) {
		durataMinute = 0;
		numeFilm = nullptr;
		nrRecenzii = 0;
		recenzii = nullptr;
	}

	Film(int id_Film, int durataMinute, const char* numeFilm, int nrRecenzii, double* recenzii) : id_Film(id_Film) {
		this->durataMinute = durataMinute;
		if (numeFilm != nullptr) {
			this->numeFilm = new char[strlen(numeFilm) + 1];
			strcpy_s(this->numeFilm, strlen(numeFilm) + 1, numeFilm);
		}
		else {
			this->numeFilm = nullptr;
		}
		if (nrRecenzii > 0) {
			this->nrRecenzii = nrRecenzii;
		}
		else {
			this->nrRecenzii = 0;
		}
		if (recenzii != nullptr && nrRecenzii > 0) {
			this->recenzii = new double[nrRecenzii];
			for (int i = 0; i < nrRecenzii; i++) {
				this->recenzii[i] = recenzii[i];
			}
		}
		else {
			this->recenzii = nullptr;
		}

	}

	Film(const Film& e) : id_Film(e.id_Film) {
		if (e.durataMinute > 0) {
			durataMinute = e.durataMinute;
		}
		else {
			durataMinute = 0;
		}
		if (e.numeFilm != nullptr) {
			numeFilm = new char[strlen(e.numeFilm) + 1];
			strcpy_s(numeFilm, strlen(e.numeFilm) + 1, e.numeFilm);
		}
		else {
			numeFilm = nullptr;
		}
		if (e.nrRecenzii > 0 && e.recenzii != nullptr) {
			nrRecenzii = e.nrRecenzii;
			recenzii = new double[e.nrRecenzii];
			for (int i = 0; i < e.nrRecenzii; i++) {
				recenzii[i] = e.recenzii[i];
			}
		}
		else {
			nrRecenzii = 0;
			recenzii = nullptr;
		}
	}

	~Film() {
		if (numeFilm != nullptr) {
			delete[] numeFilm;
		}
		if (recenzii != nullptr) {
			delete[] recenzii;
		}
	}

	Film& operator=(const Film& e) {
		if (numeFilm != nullptr) {
			delete[] numeFilm;
		}
		if (recenzii != nullptr) {
			delete[] recenzii;
		}

		if (e.durataMinute > 0) {
			durataMinute = e.durataMinute;
		}
		else {
			durataMinute = 0;
		}
		if (e.numeFilm != nullptr) {
			numeFilm = new char[strlen(e.numeFilm) + 1];
			strcpy_s(numeFilm, strlen(e.numeFilm) + 1, e.numeFilm);
		}
		else {
			numeFilm = nullptr;
		}
		if (e.nrRecenzii > 0 && e.recenzii != nullptr) {
			nrRecenzii = e.nrRecenzii;
			recenzii = new double[e.nrRecenzii];
			for (int i = 0; i < e.nrRecenzii; i++) {
				recenzii[i] = e.recenzii[i];
			}
		}
		else {
			nrRecenzii = 0;
			recenzii = nullptr;
		}
	}

	double& operator[](int index) {
		if (index >= 0 && index < nrRecenzii && recenzii != nullptr) {
			return recenzii[index];
		}
		else {
			throw exception("Index recenzie invalid!");
		}
	}

	Film operator+(int recenziiNoi) {
		Film copie = *this;
		copie.nrRecenzii += recenziiNoi;
		return copie;
	}

	Film operator++() {
		this->nrRecenzii++;
		return *this;
	}

	Film operator++(int i) {
		Film copie = *this;
		this->nrRecenzii++;
		return copie;
	}

	explicit operator int() {
		return nrRecenzii;
	}

	bool operator!() {
		return nrRecenzii > 0;
	}

	bool operator<(Film e) {
		return this->nrRecenzii < e.nrRecenzii;
	}

	bool operator==(Film e) {
		if (this->nrRecenzii != e.nrRecenzii) {
			return false;
		}
		if(this->durataMinute != e.durataMinute)
		for (int i = 0; i < this->nrRecenzii; i++) {
			if (this->recenzii[i] != e.recenzii[i]) {
				return false;
			}
		}
		if (strcmp(this->numeFilm, e.numeFilm) != 0) {
			return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream&, Film);
	friend istream& operator>>(istream&, Film&);
};

ostream& operator<<(ostream& out, Film e)
{
	out << "Id-ul filmului:  " << e.id_Film << endl;
	if (e.numeFilm != nullptr) {
		out << "Numele filmului: " << e.numeFilm << endl;
	}
	else {
		out << "Eroare: acest film nu are nume!" << endl;
	}
	out << "Durata filmului: " << e.durataMinute << " minute. " << endl;
	out << "Numarul recenziilor: " << e.nrRecenzii << endl;
	if (e.recenzii != nullptr && e.nrRecenzii > 0) {
		for (int i = 0; i < e.nrRecenzii; i++) {
			out << "Recenzia " << i+1 << " : " << e.recenzii[i] << endl;
		}
	}
	else {
		out << "Nu exista nicio recenzie pentru acest film!" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Film& e)
{
	cout << "Introduceti numele filmului: ";
	if (e.numeFilm != nullptr) {
		delete[] e.numeFilm;
	}
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99); 
	e.numeFilm = new char[strlen(buffer) + 1];
	strcpy_s(e.numeFilm, strlen(buffer) + 1, buffer);
	cout << "Cate minute are acest film? ";
	in >> e.durataMinute;
	cout << "Cate recenzii vor fi introduse? ";
	in >> e.nrRecenzii;
	if (e.recenzii != nullptr) {
		delete[] e.recenzii;
	}
	if (e.nrRecenzii > 0) {
		e.recenzii = new double[e.nrRecenzii];
		for (int i = 0; i < e.nrRecenzii; i++)
		{
			cout << "Veti introduce recenzia cu numarul  " << i+1 << " : ";
			in >> e.recenzii[i];
		}
	}
	else {
		e.recenzii = nullptr;
		e.nrRecenzii = 0;
	}
	return in;
}

class Bilet {

private:
	const int id_Bilet;
	int nrBilet;
	int sala;
	int loc;
	int pretBilet;
	char* tipBilet;                
	string data;
	string ora;
	int nrLocuriVecine;
	int* locuriVecine;
	static string material;

public:
	Bilet() : id_Bilet(0) {
		nrBilet = 0;
		sala = 0;
		loc = 0;
		pretBilet = 0;
		tipBilet = nullptr;
		data = "01-01-1999";
		ora = "00:00";
		locuriVecine = nullptr;
	}

	Bilet(int id_Bilet, int nrBilet, int sala, int loc, int pretBilet, const char* tipBilet, string data, string ora, int nrLocuriVecine, int* locuriVecine) : id_Bilet(id_Bilet) {
		this->nrBilet = nrBilet;
		this->sala = sala;
		this->loc = loc;
		this->pretBilet = pretBilet;
		this->data = data;
		this->ora = ora;
		if (tipBilet!= nullptr) {
			this->tipBilet = new char[strlen(tipBilet) + 1];
			strcpy_s(this->tipBilet, strlen(tipBilet) + 1, tipBilet);
		}
		else {
			this->tipBilet = nullptr;
		}
		if (nrLocuriVecine > 0) {
			this->nrLocuriVecine = nrLocuriVecine;
		}
		else {
			this->nrLocuriVecine = 0;
		}
		if (locuriVecine != nullptr && nrLocuriVecine > 0) {
			this->locuriVecine = new int[nrLocuriVecine];
			for (int i = 0; i < nrLocuriVecine; i++) {
				this->locuriVecine[i] = locuriVecine[i];
			}
		}
		else {
			this->locuriVecine = nullptr;
		}

	}

	Bilet(const Bilet& e) : id_Bilet(e.id_Bilet) {
		if (e.nrBilet > 0) {
			nrBilet = e.nrBilet;
		}
		else {
			nrBilet = 0;
		}
		if (e.sala > 0) {
			sala = e.sala;
		}
		else {
			sala = 0;
		}
		if (e.loc > 0) {
			loc = e.loc;
		}
		else {
			loc = 0;
		}
		if (e.pretBilet > 0) {
			pretBilet = e.pretBilet;
		}
		else {
			pretBilet = 0;
		}
		if (e.tipBilet != nullptr) {
			tipBilet = new char[strlen(e.tipBilet) + 1];
			strcpy_s(tipBilet, strlen(e.tipBilet) + 1, e.tipBilet);
		}
		else {
			tipBilet = nullptr;
		}
		data = e.data;
		ora = e.ora;
		if (e.nrLocuriVecine > 0 && e.locuriVecine != nullptr) {
			nrLocuriVecine = e.nrLocuriVecine;
			locuriVecine = new int[e.nrLocuriVecine];
			for (int i = 0; i < e.nrLocuriVecine; i++) {
				locuriVecine[i] = e.locuriVecine[i];
			}
		}
		else {
			nrLocuriVecine = 0;
			locuriVecine = nullptr;
		}
	}

	~Bilet() {
		if (tipBilet != nullptr) {
			delete[] tipBilet;
		}
		if (locuriVecine != nullptr) {
			delete[] locuriVecine;
		}
	}

	Bilet& operator=(const Bilet& e) {
		if (tipBilet != nullptr) {
			delete[] tipBilet;
		}
		if (locuriVecine != nullptr) {
			delete[] locuriVecine;
		}

		if (e.nrBilet > 0) {
			nrBilet = e.nrBilet;
		}
		else {
			nrBilet = 0;
		}
		if (e.sala > 0) {
			sala = e.sala;
		}
		else {
			sala = 0;
		}
		if (e.loc > 0) {
			loc = e.loc;
		}
		else {
			loc = 0;
		}
		if (e.pretBilet > 0) {
			pretBilet = e.pretBilet;
		}
		else {
			pretBilet = 0;
		}
		if (e.tipBilet != nullptr) {
			tipBilet = new char[strlen(e.tipBilet) + 1];
			strcpy_s(tipBilet, strlen(e.tipBilet) + 1, e.tipBilet);
		}
		else {
			tipBilet = nullptr;
		}
		data = e.data;
		ora = e.ora;
		if (e.nrLocuriVecine > 0 && e.locuriVecine != nullptr) {
			nrLocuriVecine = e.nrLocuriVecine;
			locuriVecine = new int[e.nrLocuriVecine];
			for (int i = 0; i < e.nrLocuriVecine; i++) {
				locuriVecine[i] = e.locuriVecine[i];
			}
		}
		else {
			nrLocuriVecine = 0;
			locuriVecine = nullptr;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrLocuriVecine && locuriVecine != nullptr) {
			return locuriVecine[index];
		}
		else {
			throw exception("Index loc vecin invalid!");
		}
	}

	Bilet operator+(int locuriVecineNoi) {
		Bilet copie = *this;
		copie.nrLocuriVecine += locuriVecineNoi;
		return copie;
	}

	Bilet operator++() {
		this->nrLocuriVecine++;
		return *this;
	}

	Bilet operator++(int i) {
		Bilet copie = *this;
		this->nrLocuriVecine++;
		return copie;
	}

	explicit operator int() {
		return nrLocuriVecine;
	}

	bool operator!() {
		return nrLocuriVecine > 0;
	}

	bool operator<(Bilet e) {
		return this->nrLocuriVecine < e.nrLocuriVecine;
	}

	bool operator==(Bilet e) {
		if (this->nrBilet != e.nrBilet) {
			return false;
		}
		if (this->sala != e.sala) {
			return false;
		}
		if (this->loc != e.loc) {
			return false;
		}
		if (this->pretBilet != e.pretBilet) {
			return false;
		}
		if (strcmp(this->tipBilet, e.tipBilet) != 0) {
			return false;
		}
		if (this->data != e.data) {
			return false;
		}
		if (this->ora != e.ora) {
			return false;
		}
		if (this->nrLocuriVecine != e.nrLocuriVecine) {
			return false;
		}
		for (int i = 0; i < this->nrLocuriVecine; i++) {
			if (this->locuriVecine[i] != e.locuriVecine[i]) {
				return false;
			}
		}
		return true;
	}

	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet&);
};

ostream& operator<<(ostream& out, Bilet e)
{
	out << "Id-ul biletului:  " << e.id_Bilet << endl;
	if (e.tipBilet != nullptr) {
		out << "Tipul de bilet: " << e.tipBilet << endl;
	}
	else {
		out << "Eroare: acest tip de bilet nu exista!" << endl;
	}
	out << "Numarul biletului: " << e.nrBilet << endl;
	out << "Numarul salii: " << e.sala << endl;
	out << "Locul in sala: " << e.loc << endl;
	out << "Data: " << e.data << endl;
	out << "Ora: " << e.ora << endl;
	out << "Pretul biletului in lei: " << e.pretBilet << endl;
	out << "Numarul de locuri vecine: " << e.nrLocuriVecine << endl;
	if (e.locuriVecine != nullptr && e.nrLocuriVecine > 0) {
		for (int i = 0; i < e.nrLocuriVecine; i++) {
			out << "Locul vecin " << i+1 << " : " << e.locuriVecine[i] << endl;
		}
	}
	else {
		out << "Nu exista locuri vecine!" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Bilet& e)
{
	cout << "Introduceti numarul biletului: ";
	in >> e.nrBilet;
	cout << "Introduceti sala: ";
	in >> e.sala;
	cout << "Introduceti locul in sala: ";
	in >> e.loc;
	cout << "Introduceti pretul biletului: ";
	in >> e.pretBilet;
	cout << "Introduceti tipul de bilet: ";
	if (e.tipBilet != nullptr) {
		delete[] e.tipBilet;
	}
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	e.tipBilet = new char[strlen(buffer) + 1];
	strcpy_s(e.tipBilet, strlen(buffer) + 1, buffer);
	cout << "Introduceti data: ";
	in >> e.data;
	cout << "Introduceti ora: ";
	in >> e.ora;
	if (e.locuriVecine != nullptr) {
		delete[] e.locuriVecine;
	}
	cout << "Introduceti numarul de locuri vecine: ";
	in >> e.nrLocuriVecine;
	if (e.nrLocuriVecine > 0) {
		e.locuriVecine = new int[e.nrLocuriVecine];
		for (int i = 0; i < e.nrLocuriVecine; i++)
		{
			cout << "Veti introduce locul alaturat " << i + 1 << " : ";
			in >> e.locuriVecine[i];
		}
	}
	else {
		e.locuriVecine = nullptr;
		e.nrLocuriVecine = 0;
	}
	return in;
}

class Abonament {

private:
	const string tipAbonament;
	string dInceput;
	string dSfarsit;
	int pretAbonament;         
	char* numeClient;
	int nrLuni;
	int* nrUtilizari;
	static string formaFizica;

public:
	Abonament() : tipAbonament("") {
		dInceput = "01-01-1999";
		dSfarsit = "02-01-1999";
		pretAbonament = 0;
		numeClient = nullptr;
		nrLuni = 0;
		nrUtilizari = nullptr;
	}

	Abonament(string tipAbonament, string dInceput, string dSfarsit, int pretAbonament, const char* numeClient, int nrLuni, int* nrUtilizari) : tipAbonament(tipAbonament) {
		this->dInceput = dInceput;
		this->dSfarsit = dSfarsit;
		this->pretAbonament = pretAbonament;
		
		if (numeClient != nullptr) {
			this->numeClient = new char[strlen(numeClient) + 1];
			strcpy_s(this->numeClient, strlen(numeClient) + 1, numeClient);
		}
		else {
			this->numeClient = nullptr;
		}
		if (nrLuni > 0) {
			this->nrLuni = nrLuni;
		}
		else {
			this->nrLuni = 0;
		}
		if (nrUtilizari != nullptr && nrLuni > 0) {
			this->nrUtilizari = new int[nrLuni];
			for (int i = 0; i < nrLuni; i++) {
				this->nrUtilizari[i] = nrUtilizari[i];
			}
		}
		else {
			this->nrUtilizari = nullptr;
		}

	}

	Abonament(const Abonament& e) : tipAbonament(e.tipAbonament) {
		dInceput = e.dInceput;
		dSfarsit = e.dSfarsit;
		if (e.pretAbonament > 0) {
			pretAbonament = e.pretAbonament;
		}
		else {
			pretAbonament = 0;
		}
		if (e.nrLuni > 0 && e.nrUtilizari != nullptr) {
			nrLuni = e.nrLuni;
			nrUtilizari = new int[e.nrLuni];
			for (int i = 0; i < e.nrLuni; i++) {
				nrUtilizari[i] = e.nrUtilizari[i];
			}
		}
		else {
			nrLuni = 0;
			nrUtilizari = nullptr;
		}
		if (e.numeClient != nullptr) {
			numeClient = new char[strlen(e.numeClient) + 1];
			strcpy_s(numeClient, strlen(e.numeClient) + 1, e.numeClient);
		}
		else {
			numeClient = nullptr;
		}
	}

	~Abonament() {
		if (numeClient != nullptr) {
			delete[] numeClient;
		}
		if (nrUtilizari != nullptr) {
			delete[] nrUtilizari;
		}
	}

	Abonament& operator=(const Abonament& e) {
		if (numeClient != nullptr) {
			delete[] numeClient;
		}
		if (nrUtilizari != nullptr) {
			delete[] nrUtilizari;
		}

		dInceput = e.dInceput;
		dSfarsit = e.dSfarsit;
		if (e.pretAbonament > 0) {
			pretAbonament = e.pretAbonament;
		}
		else {
			pretAbonament = 0;
		}
		if (e.nrLuni > 0 && e.nrUtilizari != nullptr) {
			nrLuni = e.nrLuni;
			nrUtilizari = new int[e.nrLuni];
			for (int i = 0; i < e.nrLuni; i++) {
				nrUtilizari[i] = e.nrUtilizari[i];
			}
		}
		else {
			nrLuni = 0;
			nrUtilizari = nullptr;
		}
		if (e.numeClient != nullptr) {
			numeClient = new char[strlen(e.numeClient) + 1];
			strcpy_s(numeClient, strlen(e.numeClient) + 1, e.numeClient);
		}
		else {
			numeClient = nullptr;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrLuni && nrUtilizari != nullptr) {
			return nrUtilizari[index];
		}
		else {
			throw exception("Index invalid!");
		}
	}

	Abonament operator+(int luniNoi) {
		Abonament copie = *this;
		copie.nrLuni += luniNoi;
		return copie;
	}

	Abonament operator++() {
		this->nrLuni++;
		return *this;
	}

	Abonament operator++(int i) {
		Abonament copie = *this;
		this->nrLuni++;
		return copie;
	}

	explicit operator int() {
		return nrLuni;
	}

	bool operator!() {
		return nrLuni > 0;
	}

	bool operator<(Abonament e) {
		return this->nrLuni < e.nrLuni;
	}

	bool operator==(Abonament e) {
		if (this->dInceput != e.dInceput) {
			return false;
		}
		if (this->dSfarsit != e.dSfarsit) {
			return false;
		}
		if (this->pretAbonament != e.pretAbonament) {
			return false;
		}
		if (this->nrLuni != e.nrLuni) {
			return false;
		}
		for (int i = 0; i < this->nrLuni; i++) {
			if (this->nrUtilizari[i] != e.nrUtilizari[i]) {
				return false;
			}
		}
		if (strcmp(this->numeClient, e.numeClient) != 0) {
			return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream&, Abonament);
	friend istream& operator>>(istream&, Abonament&);

};

ostream& operator<<(ostream& out, Abonament e)
{
	out << "Tipul abonamentului:  " << e.tipAbonament << endl;
	out << "Data inceput abonament: " << e.dInceput << endl;
	out << "Data sfarsit abonament: " << e.dSfarsit << endl;
	out << "Pretul abonamentului: " << e.pretAbonament << endl;
	if (e.numeClient != nullptr) {
		out << "Numele complet al clientului: " << e.numeClient << endl;
	}
	else {
		out << "Eroare: acest client nu este inregistrat!" << endl;
	}
	out << "Numarul de luni aferente abonamentului: " << e.nrLuni << endl;
	if (e.nrUtilizari != nullptr && e.nrLuni > 0) {
		for (int i = 0; i < e.nrLuni; i++) {
			out << "Utilizari ale abonamentului in luna " << i + 1 << " : " << e.nrUtilizari[i] << endl;
		}
	}
	else {
		out << "Nu exista utilizari ale abonamentului!" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Abonament& e)
{
	cout << "Introduceti data de inceput a abonamentului: ";
	in >> e.dInceput;
	cout << "Introduceti data de sfarsit a abonamentului: ";
	in >> e.dSfarsit;
	cout << "Introduceti pretul abonamentului: ";
	in >> e.pretAbonament;
	cout << "Introduceti numele complet al clientului: ";
	if (e.numeClient != nullptr) {
		delete[] e.numeClient;
	}
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	e.numeClient = new char[strlen(buffer) + 1];
	strcpy_s(e.numeClient, strlen(buffer) + 1, buffer);
	if (e.nrUtilizari != nullptr) {
		delete[] e.nrUtilizari;
	}
	cout << "Introduceti numarul de luni aferente abonamentului: ";
	in >> e.nrLuni;
	if (e.nrLuni > 0) {
		e.nrUtilizari = new int[e.nrLuni];
		for (int i = 0; i < e.nrLuni; i++)
		{
			cout << "Numarul de utilizari ale abonamentului in luna  " << i + 1 << " : ";
			in >> e.nrUtilizari[i];
		}
	}
	else {
		e.nrUtilizari = nullptr;
		e.nrLuni = 0;
	}
	return in;
}


class Eveniment {

private:
	const int id_Eveniment;
	string eInceput;                                  
	string eSfarsit;                     
	char* numeEveniment;                             
	int nrZile;
	int* nrFilme;
	static string siteEveniment;

public:
	Eveniment() : id_Eveniment(0) {
		eInceput = "01-01-1999";
		eSfarsit = "02-01-1999";
		numeEveniment = nullptr;
		nrZile = 0;
		nrFilme = nullptr;
	}

	Eveniment(int id_Eveniment, string eInceput, string eSfarsit, const char* numeEveniment, int nrZile, int* nrFilme) : id_Eveniment(id_Eveniment) {
		this->eInceput = eInceput;
		this->eSfarsit = eSfarsit;
		if (numeEveniment != nullptr) {
			this->numeEveniment = new char[strlen(numeEveniment) + 1];
			strcpy_s(this->numeEveniment, strlen(numeEveniment) + 1, numeEveniment);
		}
		else {
			this->numeEveniment = nullptr;
		}
		if (nrZile > 0) {
			this->nrZile = nrZile;
		}
		else {
			this->nrZile = 0;
		}
		if (nrFilme != nullptr && nrZile > 0) {
			this->nrFilme = new int[nrZile];
			for (int i = 0; i < nrZile; i++) {
				this->nrFilme[i] = nrFilme[i];
			}
		}
		else {
			this->nrFilme = nullptr;
		}

	}

	Eveniment(const Eveniment& e) : id_Eveniment(e.id_Eveniment) {
		eInceput = e.eInceput;
		eSfarsit = e.eSfarsit;
		if (e.nrZile > 0 && e.nrFilme != nullptr) {
			nrZile = e.nrZile;
			nrFilme = new int[e.nrZile];
			for (int i = 0; i < e.nrZile; i++) {
				nrFilme[i] = e.nrFilme[i];
			}
		}
		else {
			nrZile = 0;
			nrFilme = nullptr;
		}
		if (e.numeEveniment != nullptr) {
			numeEveniment = new char[strlen(e.numeEveniment) + 1];
			strcpy_s(numeEveniment, strlen(e.numeEveniment) + 1, e.numeEveniment);
		}
		else {
			numeEveniment = nullptr;
		}
	}

	~Eveniment() {
		if (numeEveniment != nullptr) {
			delete[] numeEveniment;
		}
		if (nrFilme != nullptr) {
			delete[] nrFilme;
		}
	}

	Eveniment& operator=(const Eveniment& e) {
		if (numeEveniment != nullptr) {
			delete[] numeEveniment;
		}
		if (nrFilme != nullptr) {
			delete[] nrFilme;
		}

		eInceput = e.eInceput;
		eSfarsit = e.eSfarsit;
		if (e.nrZile > 0 && e.nrFilme != nullptr) {
			nrZile = e.nrZile;
			nrFilme = new int[e.nrZile];
			for (int i = 0; i < e.nrZile; i++) {
				nrFilme[i] = e.nrFilme[i];
			}
		}
		else {
			nrZile = 0;
			nrFilme = nullptr;
		}
		if (e.numeEveniment != nullptr) {
			numeEveniment = new char[strlen(e.numeEveniment) + 1];
			strcpy_s(numeEveniment, strlen(e.numeEveniment) + 1, e.numeEveniment);
		}
		else {
			numeEveniment = nullptr;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrZile && nrFilme != nullptr) {
			return nrFilme[index];
		}
		else {
			throw exception("Index loc vecin invalid!");
		}
	}

	Eveniment operator+(int zileNoi) {
		Eveniment copie = *this;
		copie.nrZile += zileNoi;
		return copie;
	}

	Eveniment operator++() {
		this->nrZile++;
		return *this;
	}

	Eveniment operator++(int i) {
		Eveniment copie = *this;
		this->nrZile++;
		return copie;
	}

	explicit operator int() {
		return nrZile;
	}

	bool operator!() {
		return nrZile > 0;
	}

	bool operator<(Eveniment e) {
		return this->nrZile < e.nrZile;
	}

	bool operator==(Eveniment e) {
		if (this->eInceput != e.eInceput) {
			return false;
		}
		if (this->eSfarsit != e.eSfarsit) {
			return false;
		}
		
		if (strcmp(this->numeEveniment, e.numeEveniment) != 0) {
			return false;
		}
		if (this->nrZile != e.nrZile) {
			return false;
		}
		for (int i = 0; i < this->nrZile; i++) {
			if (this->nrFilme[i] != e.nrFilme[i]) {
				return false;
			}
		}
		return true;
	}
	friend ostream& operator<<(ostream&, Eveniment);
	friend istream& operator>>(istream&, Eveniment&);
};

ostream& operator<<(ostream& out, Eveniment e)
{
	out << "Id-ul evenimentului: " << e.id_Eveniment << endl;
	out << "Inceputul evenimentului: " << e.eInceput << endl;
	out << "Sfarsitul evenimentului: " << e.eSfarsit << endl;
	if (e.numeEveniment != nullptr) {
		out << "Numele complet al evenimentului: " << e.numeEveniment << endl;
	}
	else {
		out << "Eroare: acest eveniment nu este exista!" << endl;
	}
	out << "Numar de zile (durata) eveniment: " << e.nrZile << endl;
	if (e.nrFilme!= nullptr && e.nrZile > 0) {
		for (int i = 0; i < e.nrZile; i++) {
			out << "Numar de filme in ziua " << i + 1 << " a evenimentului : " << e.nrFilme[i] << endl;
		}
	}
	else {
		out << "Nu exista filme pentru acest eveniment!" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Eveniment& e)
{
	cout << "Introduceti data de inceput a evenimentului: ";
	in >> e.eInceput;
	cout << "Introduceti data de sfarsit a evenimentului: ";
	in >> e.eSfarsit;
	cout << "Introduceti numele complet al evenimentului: ";
	if (e.numeEveniment != nullptr) {
		delete[] e.numeEveniment;
	}
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	e.numeEveniment = new char[strlen(buffer) + 1];
	strcpy_s(e.numeEveniment, strlen(buffer) + 1, buffer);
	if (e.nrFilme != nullptr) {
		delete[] e.nrFilme;
	}
	cout << "Introduceti numarul de zile aferente evenimentului: ";
	in >> e.nrZile;
	if (e.nrZile > 0) {
		e.nrFilme = new int[e.nrZile];
		for (int i = 0; i < e.nrZile; i++)
		{
			cout << "Numarul de filme in ziua " << i + 1 << " a evenimentului : ";
			in >> e.nrFilme[i];
		}
	}
	else {
		e.nrFilme = nullptr;
		e.nrZile = 0;
	}
	return in;
}

string Etaj::cinematograf = "CinemaCity";
string Film::accesoriu = "Ochelari 3D";
string Bilet::material = "hartie";
string Abonament::formaFizica = "card";
string Eveniment::siteEveniment = "https://www.cinemacity.ro/evenimente";

int main() {

	Etaj e1;
	int salile[] = { 2020, 2021 };
	Etaj e2(1, 2, salile, "lift");
	Etaj e3;

	try {
		cout << e2[0] << endl;
	}
	catch(exception& x){
		cout << x.what() << endl;
	}

	if (!e2) {
		cout << "Sunt destule sali" << endl;
	}
	else {
		cout << "Sunt prea putine sali" << endl;
	}

	int a = (int)e2;
	cout << a << endl;

	if (e1<e3==true) {
		cout << "e2 are mai multe sali" << endl;
	}
	else if (e3<e1==true){
		cout << "Sunt prea putine sali" << endl;
	}
	else {
		cout << "Cele 2 etaje au acelasi numar de sali." << endl;
	}

	e1 = e2;

	if (e1 == e2) {
		cout << "Obiectele e1 si e2 sunt egale." << endl;
	}
	else {
		cout << "Obiectele e1 si e2 nu sunt egale." << endl;
	}
	Eveniment s1;
	cin >> s1;
	cout << s1;
}