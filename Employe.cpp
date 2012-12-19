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
