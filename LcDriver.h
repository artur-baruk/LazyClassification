#ifndef LC_DRIVER_H
#define LC_DRIVER_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include "Configuration.h"
#include "Timer.h"
#include "LazyClassificator.h"

class LcDriver {
	private:
		vector<Tuple*> table;

		vector<Tuple*> tuples_to_be_classified;

		vector<int> objectsInClassesCount;

		vector<Type> types;

		LazyClassificator* lazyClassificator;

	public:

		Configuration configuration;
		
		
		void run() 
		{
			Timer total;
			total.start("Total time");

			Timer t;
			t.start("Training data read time");

			readDataDescription(configuration.getDataDescriptionPath(),&types); //czytamy plik z formatem danych

			readTuples(configuration.getTrainingDataPath(), types, table, &objectsInClassesCount); // czytamy zbior danych

			t.stop();

			t.start("Objects to be classified read time");

			getTuplesToBeClsf(configuration.getObjectsToClsfPath(),&tuples_to_be_classified); //czytamy plik z obiektami ktore mamy klasyfikowac
			
			t.stop();

			for(int i = 0; i<tuples_to_be_classified.size();i++) 
			{
				t.start("Reduced table creation");
				getReducedTable(&table, tuples_to_be_classified[i]);
				t.stop();
				t.start("Classification of object no ");
				lazyClassificator = new LazyClassificator(table, Przemo, Generators, objectsInClassesCount);
				lazyClassificator->executeWithNCounters();
				t.stop();
			}

			total.stop();
			
		}
};

#endif