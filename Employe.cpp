/*
 * Employe.cpp
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#include "Employe.h"
#include <iostream>

Employe::Employe()
{
	// TODO Auto-generated constructor stub
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
        return "controleur";
    }
    if (action.compare("connexion_employe")==0)
    {
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
    return "impossible";
}

void Connexion()
{
    printf("Un employé se connecte...\n");
}

void Employe::AuthentificationEmploye()
{
    printf("Saisissez votre pseudo pour vous authentifiez\n");
    string message;
    cin >> message;
}

void envoieRapport(string donnees)
{
    int cpt = 0;
    string mes = "";
    
    for(int i = 0 ; i < donnees.length() ; i++)
    {
        mes += donnees.at(i);
        cpt++;
        if(cpt == 50)
        {
            cout << mes << endl; //TODO a remplacer par un envois
            mes = "";
            cpt = 0;
        }
    }
    cout << mes << endl;
}

Employe::~Employe()
{
	// TODO Auto-generated destructor stub
}

int main(int argc, char** argv)
{
	Employe* employ=new Employe();
    string donnees = "";
    getline(cin, donnees);
	employ->Connexion();
    
	return 0;
}
