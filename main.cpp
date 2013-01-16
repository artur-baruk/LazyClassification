#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include "Timer.h"
#include "Combination.h"
#include "Candidate.h"
#include "Tuple.h"
#include "LazyClassificator.h"
#include "TupleCreator.h"
#include "CandidateGenerator.h"
#include "ContrastPatternScorer.h"

void candidateGeneratorTest(vector<Tuple*>& table_red, vector<int>& objectsInClassesCount);

int main() {
	std::cout << "JEPs classification" << endl;

	/*
	 * 1. Read file with data and load data into decision table.
	 * 2. Create reduced decision table.
	 * 3. Find contrast patterns and calculate support.
	 */

	Timer total;
	total.start("Total time");

	Timer t;
	t.start("File read time");

	vector<Tuple*> table;

	vector<int> objectsInClassesCount;

	vector<Type> types;
    types.push_back(AttrClass);
    types.push_back(AttrInteger);
    types.push_back(AttrCategorical);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);

	readTuples("input2.txt", types, table, &objectsInClassesCount);

	for(int i = 0; i < table.size(); ++i) {
        cout<< "obj: " << i << " attr: " << table[i]->getAttributes()->at(1) << endl;
	}

    return 0;
	t.stop();

	t.start("Reduced table creation");

	Tuple* t2 = new Tuple(16, -1);
	vector<float>* attrs = t2->getAttributes();

	//wiekszosc atrybutow z LITERY T, index klasy T = 19
	//I,5,12,3,7,2,10,5,5,4,13,3,9,2,8,4,10
	(*attrs)[0] = 5.0;
	(*attrs)[1] = 12.0;
	(*attrs)[2] = 3.0;
	(*attrs)[3] = 7.0;
	(*attrs)[4] = 2.0;
	(*attrs)[5] = 10.0;
	(*attrs)[6] = 5.0;
	(*attrs)[7] = 5.0;
	(*attrs)[8] = 4.0;
	(*attrs)[9] = 11.0;
	(*attrs)[10] = 3.0;
	(*attrs)[11] = 9.0;
	(*attrs)[12] = 2.0;
	(*attrs)[13] = 8.0;
	(*attrs)[14] = 3.0;
	(*attrs)[15] = 10.0;

	getReducedTable(&table, t2);

	cout << "Reduced table size:" <<  table.size() << endl;

	t.stop();

	candidateGeneratorTest(table, objectsInClassesCount);

	total.stop();

	int input;
	std::cin >> input;
	return 0;
}

void candidateGeneratorTest(vector<Tuple*>& table_red, vector<int>& objectsInClassesCount) {
	CandidateGenerator candidateGenerator = CandidateGenerator(table_red, 26);
	candidateGenerator.execute(Michal1);

	ContrastPatternScorer scorer(candidateGenerator.getContrastPatterns(), objectsInClassesCount);
	cout << "Wybrana klasa to : " << scorer.chooseDecisionClass();

	//for (int i = 0; i < objectsInClassesCount.size(); i++) {
	//	cout << "klasa : " << i << " licznosc: " << objectsInClassesCount[i] << endl;
	//}
}

