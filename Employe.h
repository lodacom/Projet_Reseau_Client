/*!
 * \file Employe.h
 * \brief Fichier header pour l'employé 
 * \authors Duplouy Olivier, Burc Pierre
 * \version 1.0
 * \date 24 décembre 2012
 *
 * Enregistrement de rapports d'activité dans une entreprise
 *
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
    string Analyse();
    bool Connexion();
    void CreationListe();
    void AuthentificationEmploye();
    void ChoixControleur();
    void RedigeRapport();
    void EnvoieRapport(string);
    void Deconnexion();
    void DemandeListeRapportFait();
    void DemandeRapportParticulier(string);
public:
    char recu[100];
    char envoi[100];
    vector<string> liste_employe;
    string pseudo;
    string recuperation_rapport;
    int descripteur_client;
    int destLocal;
    sockaddr_in* adresseExp;
};

#endif /* EMPLOYE_H_ */