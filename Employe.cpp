/*
 * Employe.cpp
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#include "Employe.h"
#include <iostream>
#include <stdio.h>


Employe::Employe()
{
	// TODO Auto-generated constructor stub
    /*SockDist Expd("127.0.0.1",31467);//changer par adresse
	Sock BRlocal(SOCK_STREAM, 31466, 0);//pour autotest 31466/31467
	
	this->destLocal = BRlocal.getsDesc();
    
    this->adresseExp = Expd.getAdrDist();*/
}

string Employe::Analyse(string p_message)
{
	//read(tp,recu, 0);
    //char* message=recu;
    //string inter=this->message;
    printf("Analyse de la trame...\n");
    int i=0;
    while(i<p_message.length() and p_message.at(i)!='>')
    {
        i++;
    }
    string action=p_message.substr(0,i);
    string transmission=p_message.substr(i+1,p_message.length());
    cout << "La trame a été analysée avec action: "<< action << " et message: " << transmission << endl;

    printf("On décide de ce qu'on va faire\n");
    if (action.compare("connexion_controleur")==0)
    {
        this->CreationListe();
        return "controleur";
    }
    if (action.compare("connexion_employe")==0)
    {
        this->RedigeRapport();
        return "employe";
    }
    if (action.compare("connexion_refuse")==0)
    {
        return "refuse";
    }
    if(action.compare("liste_rapport_fait")==0)
    {
        return "liste";
    }
    if(action.compare("transfert_rapport")==0)
    {
        return "rapport";
    }
    if(action.compare("deconnexion")==0)
    {
        this->Deconnexion();
        return "deconnexion";
    }
    return "impossible";
}

bool Employe::Connexion()
{
    printf("Je me connecte au serveur ...\n");
    /*this->descripteur_client = connect(this->destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));*/
    return true;
}

void Employe::AuthentificationEmploye()
{
    printf("Saisissez votre pseudo pour vous authentifiez\n");
    string message;
    getline(cin,message);
    this->pseudo = message;
    string connexion = "connexion_employe>"+message;
}

void Employe::CreationListe()
{
    string pseudo_liste;
    string envoi_pseudo_liste;
    printf("Veuillez créer votre liste contenant les employés devant rédiger un rapport aujourd'hui\n");
    printf("Quand vous avez terminé, tapez fini\n");
    getline(cin,pseudo_liste);
    while(pseudo_liste.compare("fini")!=0)
    {
        envoi_pseudo_liste = "ajout_employe>"+pseudo_liste; //TO DO envoi du pseudo 
        getline(cin,pseudo_liste);
    }
    printf("Liste terminée ! \n");
}

void Employe::ChoixControleur()
{
    cout << "Plusieurs possibilités sont à votre dispositions (saisissez celui qui vous convient)" << endl;
    cout << "1. Consulter la liste des employés qui ont fait leur rapport" << endl;
    cout << "2. Consulter le rapport d'un employé" << endl;
    cout << "3. Vous déconnectez" << endl;
    int choix=0;
    cin >> choix;
    while (choix!=3)
    {
        switch (choix)
        {
            case 1:
                this->DemandeListeRapportFait();
                break;
                
            case 2:
                cout << "Saisissez l'employé dont vous voulez consultez le rapport" << endl;
                string p_pseudo;
                getline(cin,p_pseudo);
                this->DemandeRapportParticulier(p_pseudo);
        }
    }
    string deconnexion="deconnexion>";
}

void Employe::DemandeListeRapportFait()
{
    string demande_liste="demande_liste_rapport_fait>";
    
    // TO DO : envoi de la trame au serveur
}

void Employe::DemandeRapportParticulier(string pseudo)
{
    string demande_rapport="demande_rapport>"+pseudo;
    
    // TO DO : envoi de de la trame au serveur
}

void Employe::RedigeRapport()
{
    printf("Saisissez votre rapport sections par sections\n");
    printf("Une fois votre rapport terminé, tapez fin\n");
    string rapport;
    getline(cin,rapport);
    while(rapport.compare("fin")!=0)
    {
        printf("Saisissez votre rapport sections par sections\n");
        this->EnvoieRapport(rapport);
        getline(cin,rapport);
    }
    printf("Votre rapport est terminé ! Vous allez être déconnecté \n");
}

void Employe::EnvoieRapport(string donnees)
{
    int cpt = 0;
    string mes = "";
    string envoi;
    for(int i = 0 ; i < donnees.length() ; i++)
    {
        mes += donnees.at(i);
        cpt++;
        if(cpt == 50)
        {
            //cout << mes << endl; //TODO a remplacer par un envois
            envoi ="partie_rapport>"+this->pseudo+"@"+mes;
            mes = "";
            cpt = 0;
        }
    }
   // cout << mes << endl;
}

void Employe::Deconnexion()
{
    /*
     close(this->descripteur_client);
     close(this->destLocal);
     */
    cout << "l'employé se déconnecte" << endl;
}

Employe::~Employe()
{
	// TODO Auto-generated destructor stub
}

int main(int argc, char** argv)
{
    Employe* employ=new Employe();
    if (employ->Connexion())
    {
        employ->AuthentificationEmploye();
        string message;
        cout << "Saisissez une trame à tester" << endl;
        getline(cin,message);
        while (employ->Analyse(message).compare("deconnexion")!=0)
        {
            cout << "Saisissez une trame à tester" << endl;
            getline(cin,message);
        }
    }
    else
    {
        cout << "Problème de connexion au serveur" << endl;
    }
    return 0;
}
