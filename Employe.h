/*
 * Employe.h
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#ifndef EMPLOYE_H_
#define EMPLOYE_H_
#include <string>
#include <vector>
using namespace std;

class Employe
{
public:
	Employe();
	~Employe();
    string Analyse(string);
    void Connexion();
	void AuthentificationEmploye();
    void VerificationEstDansListe();
    void RedigeRapport();
    void RecuperationRapport();
    void Deconnexion();
    void RedigeRapport(string);
    void PassageMessage(string);
public:
    char recu[100];
    vector<string> liste_employe;
};

#endif /* EMPLOYE_H_ */
