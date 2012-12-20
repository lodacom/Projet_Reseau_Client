/*
 * Employe.h
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#ifndef EMPLOYE_H_
#define EMPLOYE_H_
#include "sock.h"
#include "sockdist.h"
#include <string>
#include <vector>
using namespace std;

class Employe
{
public:
	Employe();
	~Employe();
    string Analyse(string);
    bool Connexion();
    void CreationListe();
    void AuthentificationEmploye();
    void ChoixControleur();
    void RedigeRapport();
    void EnvoieRapport(string);
    void RecuperationRapport();
    void Deconnexion();
    void RedigeRapport(string);
    void DemandeListeRapportFait();
    void DemandeRapportParticulier(string);
public:
    char recu[100];
    char envoi[100];
    vector<string> liste_employe;
    string pseudo;
    int descripteur_client;
    int destLocal;
    sockaddr_in* adresseExp;
};

#endif /* EMPLOYE_H_ */
