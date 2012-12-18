/*
 * Employe.cpp
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#include "Employe.h"
#include "Authentification.h"
#include "AnalyseurTrame.h"
#include "RedactionRapport.h"
#include "Serveur.h"

Employe::Employe()
{
	// TODO Auto-generated constructor stub
}

void Employe::AuthentificationEmploye()
{
    
	//if (Se_Connecter())
	//{
		printf("Saisissez votre pseudo pour vous authentifiez\n");
		string pseudo="";
		cin >> pseudo;
		Authentification* auth=new Authentification(pseudo);
		if (auth->Envoi_Authentification())
		{
            
		}
	/*}
	else
	{
		printf("Le serveur n'est pas lancé ou erreur\n");
	}
	Se_Deconnecter();*/
}

void Employe::RedigeRapport(string p_partie)
{
    Redaction_Rapport* redac=new Redaction_Rapport();
    string message=redac->PartieRapport(p_partie);
    Serveur* serv=new Serveur();
    serv->LancementServeur(message);
}

void Employe::PassageMessage(string p_message)
{
    AnalyseurTrame* anal=new AnalyseurTrame(p_message);
    anal->Analyse();
    string action=anal->DecisionAction();
    if (action=="controleur")
    {
        /*On doit lui faire remplir une liste sur le choix
         *(je sais pas l'énoncé est trop ambigüe)
         */
    }
    if (action=="employe")
    {
        /*Pour l'instant on considère que le controleur a fait
         *la liste des employes et qu'on doit faire le
         *rapport....
         */
        printf("Ecrivez votre rapport et finissez votre rapport par: fin rapport\n");
        string partie="";
		cin >> partie;
        this->RedigeRapport(partie);
    }
    if (action=="refuse")
    {
        this->AuthentificationEmploye();
    }
    if (action=="partie_recue")
    {
        printf("Continuez à écrire votre rapport et finissez votre rapport par: fin rapport\n");
        string partie="";
		cin >> partie;
        this->RedigeRapport(partie);
    }
    if (action=="fin_partie_recue")
    {
        printf("Merci pour votre contribution...\n");
    }
}

Employe::~Employe()
{
	// TODO Auto-generated destructor stub
}

int main(int argc, char** argv)
{
	Employe* employ=new Employe();
	employ->AuthentificationEmploye();
	return 0;
}
