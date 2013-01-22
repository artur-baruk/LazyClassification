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

int main() {


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
    types.push_back(AttrInteger);/*
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
    types.push_back(AttrInteger);*/

	readTuples("LECTURE.txt", types, table, &objectsInClassesCount);

	t.stop();

	t.start("Reduced table creation");

	Tuple* t2 = new Tuple(4, -1);
	vector<float>* attrs = t2->getAttributes();

	//wiekszosc atrybutow z LITERY T, index klasy T = 19
	//I,5,12,3,7,2,10,5,5,4,13,3,9,2,8,4,10
	//N,4,6,6,6,6,6,9,5,3,6,4,8,7,8,4,9
	//O,4,5,5,4,3,7,7,8,5,7,6,8,2,8,3,8
	(*attrs)[0] = 3.0;
	(*attrs)[1] = 3.0;
	(*attrs)[2] = 1.0;
	(*attrs)[3] = 2.0;
	/*(*attrs)[4] = 3.0;
	(*attrs)[5] = 6.0;
	(*attrs)[6] = 6.0;
	(*attrs)[7] = 8.0;
	(*attrs)[8] = 5.0;
	(*attrs)[9] = 6.0;
	(*attrs)[10] = 6.0;
	(*attrs)[11] = 8.0;
	(*attrs)[12] = 2.0;
	(*attrs)[13] = 8.0;
	(*attrs)[14] = 2.0;
	(*attrs)[15] = 8.0;*/

	getReducedTable(&table, t2);

	cout << "Reduced table size:" <<  table.size() << endl;

	t.stop();

	LazyClassificator lazyClassificator = LazyClassificator(table, Przemo, Generators, objectsInClassesCount);
	lazyClassificator.executeWithNCounters();
	//lazyClassificator.executeParallelWithTwoLengthCounter();

	total.stop();

	int input;
	std::cin >> input;
	return 0;
}


