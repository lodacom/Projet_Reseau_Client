/*
 * AnalyseurTrame.h
 *
 *  Created on: 13 déc. 2012
 *      Author: Lolo
 */

#ifndef ANALYSEURTRAME_H_
#define ANALYSEURTRAME_H_
#include <string>
using namespace std;

class AnalyseurTrame {
public:
	AnalyseurTrame();
	~AnalyseurTrame();
	void Analyse();
    string DecisionAction();
public:
	int tp;
    string message;
    string action;
    string transmission;
};

#endif /* ANALYSEURTRAME_H_ */