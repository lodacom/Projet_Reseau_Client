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
    void CreationListe();
    void AuthentificationEmploye();
    void RedigeRapport();
    void envoieRapport(string);
    void RecuperationRapport();
    void Deconnexion();
    void RedigeRapport(string);
    void DemandeListeRapportFait();
    void DemandeRapportParticulier(string);
public:
    char recu[100];
    vector<string> liste_employe;
    string pseudo;
};

#endif /* EMPLOYE_H_ */
