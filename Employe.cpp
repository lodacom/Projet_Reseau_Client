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

//#include "Employe.h"
#include <iostream>
#include <stdio.h>
#include "sauvegarde.c"
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"
#include <string>
#include <vector>
using namespace std;
vector<string> liste_employe;
string pseudo;
string recuperation_rapport;
char recu[100];
char envoi[100];
int test=-1;
int destLocal=-1;
sockaddr_in* adresseExp;

/**
 * \brief Envoie la demande de liste des 
 * rapports qui ont été fait 
 */
void DemandeListeRapportFait()
{
    char tmp[100];
    strcpy(tmp,"demande_liste_rapport_fait>");
    send(destLocal,tmp,sizeof(tmp),0);
    // TO DO : envoi de la trame au serveur
}

/**
 * \brief Envoie la demande d'obtention d'un rapport
 * d'un employé
 */
void DemandeRapportParticulier()
{
    char* pseudo;
    printf("Saisissez l'employé dont vous voulez consultez le rapport\n");
    scanf("%s",pseudo);
    char tmp[100];
    strcpy(tmp,"demande_rapport>");
    strcat(tmp,pseudo);
    cout << "Concat ok" << endl;
    send(destLocal,tmp,sizeof(tmp),0);
    cout << "Envoie de la demande particulière effectuée" <<endl;
    // TO DO : envoi de de la trame au serveur
}

/**
 * \brief Permet au controleur d'effectuer un choix
 * -Soit obtenir la liste des employés qui ont fait
 * leur rapport
 * -Soit de consulter le rapport d'un employé
 * -Soit de se déconnecter
 */
void ChoixControleur()
{
    cout << "Plusieurs possibilités sont à votre dispositions (saisissez celui qui vous convient)" << endl;
    cout << "1. Consulter la liste des employés qui ont fait leur rapport" << endl;
    cout << "2. Consulter le rapport d'un employé" << endl;
    cout << "3. Vous déconnectez" << endl;
    int choix=0;
    scanf("%d",&choix);

    switch (choix)
    {
        case 1:
            DemandeListeRapportFait();
            break;

        case 2:
            DemandeRapportParticulier();
            break;
        case 3:
            char tmp[100];
            strcpy(tmp,"deconnexion>");
            strcat(tmp,pseudo.c_str());
            send(destLocal,tmp,sizeof(tmp),0);
            break;
        default: cout << "Désolé cette action est inconnue, veuillez recommencer" << endl;
            break;
    }
}

/**
 * \brief Permet au controleur de créer la liste
 * des employés qui vont écrire les rapports
 */
void CreationListe()
{
    string pseudo_liste;
    //string envoi_pseudo_liste;
    printf("Veuillez créer votre liste contenant les employés devant rédiger un rapport aujourd'hui\n");
    printf("Quand vous avez terminé, tapez fini\n");
    getline(cin,pseudo_liste);
    while(pseudo_liste.compare("fini")!=0)
    {
        char tmp[100];
        strcpy(tmp,"ajout_employe>");
        strcat(tmp,pseudo_liste.c_str());
        send(destLocal,tmp,sizeof(tmp),0);
        getline(cin,pseudo_liste);
    }
    printf("Liste terminée ! \n");
    ChoixControleur();
}

/**
 * \brief Permet d'envoyer le rapport en le découpant
 * en partie de 100 caractères
 */
void EnvoieRapport(string donnees)
{
    int cpt = 0;
    string mes = "";
    string envoi;
    for(int i = 0 ; i < donnees.length() ; i++)
    {
        mes += donnees.at(i);
        cpt++;
        if(cpt == 70)
        {
            //cout << mes << endl; //TODO a remplacer par un envois
            char tmp[100];
            strcpy(tmp,"partie_rapport>");
            strcat(tmp,pseudo.c_str());
            strcat(tmp,"@");
            strcat(tmp,mes.c_str());
            send(destLocal,tmp,sizeof(tmp),0);
            mes = "";
            cpt = 0;
        }
    }
    char tmp[100];
    strcpy(tmp,"fin_section>");
    strcat(tmp,pseudo.c_str());
    send(destLocal,tmp,sizeof(tmp),0);
   // cout << mes << endl;
}

/**
 * \brief Permet à un client de rédiger un rapport
 * et de l'envoyer puis le déconnecte automatiquement
 * dès qu'il a valider son rapport avec le mot clé:
 * "fin"
 */
void RedigeRapport()
{
    printf("Saisissez votre rapport sections par sections\n");
    printf("Une fois votre rapport terminé, tapez fin\n");
    string rapport;
    getline(cin,rapport);
    while(rapport.compare("fin")!=0)
    {
        EnvoieRapport(rapport);
        printf("Saisissez votre rapport sections par sections\n");
        getline(cin,rapport);
    }
    printf("Votre rapport est terminé ! Vous allez être déconnecté \n");
    char tmp[100];
    strcpy(tmp,"deconnexion>");
    strcat(tmp,pseudo.c_str());
    send(destLocal,tmp,sizeof(tmp),0);
}

/**
 * \brief On déconnecte le client
 */
void Deconnexion()
{
    close(test);
    close(destLocal);
    cout << "l'employé se déconnecte" << endl;
}

/**
 * \brief Permet au client de s'authentifier avec un 
 * pseudo
 */
void AuthentificationEmploye()
{
    char* p_message;
    printf("Saisissez votre pseudo pour vous authentifiez (pas plus de 20 caractères et pas d'espace)\n");
    scanf("%s",p_message);
    string message=p_message;
    while (message.length()>20 and strtok((char*)message.c_str()," ")!=NULL)
    {
       printf("Saisissez votre pseudo pour vous authentifiez (pas plus de 20 caractères et pas d'espace)\n");
        scanf("%s",p_message);
        message=p_message;
    }
    pseudo = message;
    //string connexion = "connexion_employe>"+message;
    char tmp[50];
    strcpy(tmp,"connexion_employe>");
    strcat(tmp,p_message);
    int test=send(destLocal,tmp,sizeof(tmp),0);
    //int test=send(destLocal,connexion.c_str(),strlen(connexion.c_str()),0);
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
 * \fn string Analyse(string p_message)
 * \brief Permet d'analyser ce qui arrive dans la trame que l'on a reçu 
 * \param string p_message
 * \return une string correspondant à ce qu'on veut renvoyer
 */
string Analyse()
{
    recv(destLocal,recu,100*sizeof(&recu), 0);
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
        CreationListe();
        return "controleur";
    }
    if (action.compare("connexion_employe")==0)
    {
        RedigeRapport();
        return "employe";
    }
    if (action.compare("connexion_refuse")==0)
    {
        cout << "Désolé vous avez été refusé par le serveur" << endl;
        return "refuse";
    }
    if (action.compare("action_suivante_controleur")==0)
    {
        cout << transmission << endl;
        ChoixControleur();
        return "action suivante";
    }
    if(action.compare("liste_rapport_fait")==0)
    {
        cout << transmission << endl;
        return "liste";
    }
    if(action.compare("transfert_rapport")==0)
    {
        recuperation_rapport+=transmission;
        return "rapport";
    }
    if (action.compare("fin_transfert")==0)
    {
        Ecrit(recuperation_rapport.c_str(),transmission.c_str());
        recuperation_rapport="";
    }
    if(action.compare("deconnexion")==0)
    {
        if (transmission.compare("controleur")!=0)
        {
            OuvreRapport(transmission.c_str());
        }
        Deconnexion();
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
bool Connexion()
{
    printf("Je me connecte au serveur ...\n");
    test = connect(destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
    if (test!=0)
    {
        test = connect(destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
        perror("On a pas pu se connecter");
        return false;
    }
    else
    {
        perror("Connection...");
        AuthentificationEmploye();
        return true;  
    }
}


//~Employe()
//{
//	// TODO Auto-generated destructor stub
//}

/**
 * \brief Point d'entrer principal du programme
 */
int main(int argc, char** argv)
{
   // Employe();
    
    cout << "On initialise le client" << endl;
    SockDist Expd("127.0.0.1",31467);//changer par adresse
    Sock BRlocal(SOCK_STREAM, 31466, 0);//pour autotest 31466/31467

    destLocal = BRlocal.getsDesc();

    adresseExp = Expd.getAdrDist();
    printf("Je me connecte au serveur ...\n");
    test = connect(destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
    if (test!=0)
    {
        test = connect(destLocal,(struct sockaddr *) adresseExp,sizeof(*adresseExp));
        perror("On a pas pu se connecter");
    }
    else
    {
        perror("Connection...");
        AuthentificationEmploye(); 
        cout << "On attend la réponse avec l'analyse" << endl;
        while (Analyse().compare("deconnexion")!=0)
        {
        /*cout << "Saisissez une trame à tester" << endl;
        getline(cin,message);*/
        }
        cout << "On se déconnecte..." << endl;
    }
    return 0;
}