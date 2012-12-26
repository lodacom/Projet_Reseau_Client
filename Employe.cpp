/*!
 * \file Employe.cpp
 * \brief Programme permettant de lancer le client
 * \authors Duplouy Olivier, Burc Pierre
 * \version 1.0
 * \date 24 décembre 2012
 *
 * Enregistrement de rapports d'activité dans une entreprise
 *
 */

#include "Employe.h"
#include <iostream>
#include <stdio.h>
#include "sauvegarde.c"
#include <errno.h>

/**
* \brief Fonction permettant d'initialisé le client 
*/
Employe::Employe()
{
    // TODO Auto-generated constructor stub
    this->descripteur_client=-1;
    SockDist Expd("127.0.0.1",31467);//changer par adresse
    Sock BRlocal(SOCK_STREAM, 31466, 0);//pour autotest 31466/31467

    this->destLocal = BRlocal.getsDesc();

    this->adresseExp = Expd.getAdrDist();
}

/**
 * \fn string Analyse(string p_message)
 * \brief Permet d'analyser ce qui arrive dans la trame que l'on a reçu 
 * \param string p_message
 * \return une string correspondant à ce qu'on veut renvoyer
 */
string Employe::Analyse()
{
    recv(this->destLocal,recu,sizeof recu, 0);
    char* message=recu;
    string p_message=message;
    
    cout << "Analyse de la trame..." << endl;
    int i=0;
    while(i<p_message.length() and p_message.at(i)!='>')
    {
        i++;
    }
    string action=p_message.substr(0,i);
    string transmission=p_message.substr(i+1,p_message.length());
    cout << "La trame a été analysée avec action: "<< action << " et message: " << transmission << endl;

    printf("On décide de ce qu'on va faire\n");
    if (action.compare("reponse")==0)
    {
        cout << transmission << endl;
        return "reponse";
    }
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
        cout << "Désolé vous avez été refusé par le serveur" << endl;
        return "refuse";
    }
    if(action.compare("liste_rapport_fait")==0)
    {
        cout << transmission << endl;
        return "liste";
    }
    if(action.compare("transfert_rapport")==0)
    {
        this->recuperation_rapport+=transmission;
        return "rapport";
    }
    if (action.compare("fin_transfert")==0)
    {
        Ecrit(this->recuperation_rapport.c_str(),transmission.c_str());
        this->recuperation_rapport="";
    }
    if(action.compare("deconnexion")==0)
    {
        if (transmission.compare("controleur")!=0)
        {
            OuvreRapport(transmission.c_str());
        }
        this->Deconnexion();
        return "deconnexion";
    }
    if(action.compare("reponse")==0)
    {
        cout << transmission << endl;
        return "reponse";
    }
    return "impossible";
}

/**
 * \fn bool Connexion()
 * \brief On essaie de connecter le client au serveur
 * s'il on n'y arrive pas on essaie en boucle
 * \return vrai quand on est connecté
 */
bool Employe::Connexion()
{
    printf("Je me connecte au serveur ...\n");
    this->descripteur_client = connect(this->destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
    if (this->descripteur_client!=0)
    {
        this->descripteur_client = connect(this->destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
        perror("On a pas pu se connecter");
        return false;
    }
    else
    {
        this->AuthentificationEmploye();
        return true;  
    }
}

/**
 * \brief Permet au client de s'authentifier avec un 
 * pseudo
 */
void Employe::AuthentificationEmploye()
{
    string message;
    printf("Saisissez votre pseudo pour vous authentifiez (pas plus de 20 caractères et pas d'espace)\n");
    getline(cin,message);
    while (message.length()>20 and strtok((char*)message.c_str()," ")!=NULL)
    {
       printf("Saisissez votre pseudo pour vous authentifiez (pas plus de 20 caractères et pas d'espace)\n");
        getline(cin,message);
    }
    this->pseudo = message;
    string connexion = "connexion_employe>"+message;
    int test=send(this->destLocal,(const void *)connexion.c_str(),sizeof(connexion),0);
    if (test>=0)
    {
        cout<< "Le message a été envoyé" << endl;
    }
    else
    {
         perror("Erreur d'envoi"); 
    }
}
/**
 * \brief Permet au controleur de créer la liste
 * des employés qui vont écrire les rapports
 */
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
        send(this->destLocal,(const void *)envoi_pseudo_liste.c_str(),sizeof(envoi_pseudo_liste),0);
        getline(cin,pseudo_liste);
    }
    printf("Liste terminée ! \n");
}

/**
 * \brief Permet au controleur d'effectuer un choix
 * -Soit obtenir la liste des employés qui ont fait
 * leur rapport
 * -Soit de consulter le rapport d'un employé
 * -Soit de se déconnecter
 */
void Employe::ChoixControleur()
{
    string p_pseudo;
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
                continue;
                
            case 2:
                cout << "Saisissez l'employé dont vous voulez consultez le rapport" << endl;
                getline(cin,p_pseudo);
                this->DemandeRapportParticulier(p_pseudo);
                continue;
            default: cout << "Désolé cette action est inconnue, veuillez recommencer" << endl;
                continue;
        }
    }
    string deconnexion="deconnexion>"+this->pseudo;
    send(this->destLocal,(const void *)deconnexion.c_str(),sizeof(deconnexion),0);
}

/**
 * \brief Envoie la demande de liste des 
 * rapports qui ont été fait 
 */
void Employe::DemandeListeRapportFait()
{
    string demande_liste="demande_liste_rapport_fait>";
    send(this->destLocal,(const void *)demande_liste.c_str(),sizeof(demande_liste),0);
    // TO DO : envoi de la trame au serveur
}

/**
 * \brief Envoie la demande d'obtention d'un rapport
 * d'un employé
 */
void Employe::DemandeRapportParticulier(string pseudo)
{
    string demande_rapport="demande_rapport>"+pseudo;
    send(this->destLocal,(const void *)demande_rapport.c_str(),sizeof(demande_rapport),0);
    // TO DO : envoi de de la trame au serveur
}

/**
 * \brief Permet à un client de rédiger un rapport
 * et de l'envoyer puis le déconnecte automatiquement
 * dès qu'il a valider son rapport avec le mot clé:
 * "fin"
 */
void Employe::RedigeRapport()
{
    printf("Saisissez votre rapport sections par sections\n");
    printf("Une fois votre rapport terminé, tapez fin\n");
    string rapport;
    getline(cin,rapport);
    while(rapport.compare("fin")!=0)
    {
        this->EnvoieRapport(rapport);
        printf("Saisissez votre rapport sections par sections\n");
        getline(cin,rapport);
    }
    printf("Votre rapport est terminé ! Vous allez être déconnecté \n");
    string deconnexion="deconnexion>"+this->pseudo;
    send(this->destLocal,(const void *)deconnexion.c_str(),sizeof(deconnexion),0);
}

/**
 * \brief Permet d'envoyer le rapport en le découpant
 * en partie de 100 caractères
 */
void Employe::EnvoieRapport(string donnees)
{
    int cpt = 0;
    string mes = "";
    string envoi;
    for(int i = 0 ; i < donnees.length() ; i++)
    {
        mes += donnees.at(i);
        cpt++;
        if(cpt == 100)
        {
            //cout << mes << endl; //TODO a remplacer par un envois
            envoi ="partie_rapport>"+this->pseudo+"@"+mes;
            send(this->destLocal,(const void *)envoi.c_str(),sizeof(envoi),0);
            mes = "";
            cpt = 0;
        }
    }
    envoi="fin_section>"+this->pseudo;
    send(this->destLocal,(const void *)envoi.c_str(),sizeof(envoi),0);
   // cout << mes << endl;
}

/**
 * \brief On déconnecte le client
 */
void Employe::Deconnexion()
{
    close(this->descripteur_client);
    close(this->destLocal);
    cout << "l'employé se déconnecte" << endl;
}

Employe::~Employe()
{
	// TODO Auto-generated destructor stub
}

/**
 * \brief Point d'entrer principal du programme
 */
int main(int argc, char** argv)
{
    Employe* employ=new Employe();
    if (employ->Connexion())
    {
        employ->AuthentificationEmploye();
        cout << "On attend la réponse avec l'analyse" << endl;
        while (employ->Analyse().compare("deconnexion")!=0)
        {
            /*cout << "Saisissez une trame à tester" << endl;
            getline(cin,message);*/
        }
        cout << "On se déconnecte..." << endl;
    }
    else
    {
        cout << "Problème de connexion au serveur" << endl;
    }
    return 0;
}