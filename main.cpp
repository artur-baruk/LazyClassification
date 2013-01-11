#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include "Timer.h"
#include "Combination.h"
#include "Candidate.h"
#include "HashTreeNode.h"
#include "HashTree.h"
#include "Tuple.h"
#include "LazyClassificator.h"
#include "TupleCreator.h"
#include "CandidateGenerator.h"

void candidateGeneratorTest(vector<Tuple*>& table_red);

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
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
	types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
	types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
	types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);

	readTuples("letter.txt", types, table, &objectsInClassesCount);

	t.stop();

	t.start("Reduced table creation");
	
	Tuple* t2 = new Tuple(16, -1);
	vector<float>* attrs = t2->getAttributes();

	//wiekszosc atrybutow z LITERY T, index klasy T = 19

	(*attrs)[0] = 2.0;
	(*attrs)[1] = 8.0;
	(*attrs)[2] = 3.0;
	(*attrs)[3] = 5.0;
	(*attrs)[4] = 1.0;
	(*attrs)[5] = 8.0;
	(*attrs)[6] = 13.0;
	(*attrs)[7] = 1.0;
	(*attrs)[8] = 2.0;
	(*attrs)[9] = 2.0;
	(*attrs)[10] = 1.0;
	(*attrs)[11] = 8.0;
	(*attrs)[12] = 0.0;
	(*attrs)[13] = 8.0;
	(*attrs)[14] = 1.0;
	(*attrs)[15] = 8.0;

	getReducedTable(&table, t2);

	cout << "Reduced table size:" <<  table.size() << endl;

	t.stop();

	candidateGeneratorTest(table);

	total.stop();

	int input;
	std::cin >> input;
	return 0;
}

void candidateGeneratorTest(vector<Tuple*>& table_red) {
	CandidateGenerator candidateGenerator = CandidateGenerator(table_red, 26);
	candidateGenerator.execute();
	//candidateGenerator.printSupportsOfCandiadtesLengthOne();
}

