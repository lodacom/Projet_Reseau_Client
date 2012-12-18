/*
 * Employe.h
 *
 *  Created on: 7 déc. 2012
 *      Author: Lolo
 */

#ifndef EMPLOYE_H_
#define EMPLOYE_H_
#include <string>
using namespace std;
#include "Personnel.h"

class Employe: Personnel
{
public:
	Employe();
	~Employe();
	void AuthentificationEmploye();
    void RedigeRapport(string);
    void PassageMessage(string);
};

#endif /* EMPLOYE_H_ */
