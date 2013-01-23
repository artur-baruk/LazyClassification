#include <iostream>
#include <stdio.h>

#include "LcDriver.h"

int main() {

	LcDriver lcDriver;

	lcDriver.configuration.setDataDescriptionPath("plik z opisem danych.txt");
	
	lcDriver.configuration.setTrainingDataPath("LECTURE.txt");
	
	lcDriver.configuration.setObjectsToClsfPath("plik z tuplami do klasyfikowania");


	lcDriver.run();

	getchar();

	return 0;
}


