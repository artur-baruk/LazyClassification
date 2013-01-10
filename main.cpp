#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
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
	std::cout << "JEPs classification";

	/*
	 * 1. Read file with data and load data into decision table.
	 * 2. Create reduced decision table.
	 * 3. Find contrast patterns and calculate support.
	 */

	/*<testy drzewa>*/

	vector<Candidate*> candidates;

	vector<int>* attr1 = new vector<int>();
	attr1->push_back(1);
	attr1->push_back(2);

	vector<int>* attr2 = new vector<int>();
	attr2->push_back(4);
	attr2->push_back(3);

	vector<int>* attr3 = new vector<int>();
	attr3->push_back(2);
	attr3->push_back(5);

	vector<int>* sup1 = new vector<int>();
	sup1->push_back(0);
	sup1->push_back(0);

	candidates.push_back(new Candidate(attr1, sup1 ));
	candidates.push_back(new Candidate(attr2, sup1 ));
	candidates.push_back(new Candidate(attr3, sup1 ));

	HashTree* ht = new HashTree(candidates,2);

	ht->printHashTree();

	/*</testy drzewa>*/

	getchar();

	vector<Tuple*> table;
	vector<int> objectsInClassesCount;

	vector<Type> types;
    types.push_back(AttrClass);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);

	readTuples("input2.txt", types, table, &objectsInClassesCount);

    cout << "Dataset read:" << endl;
	for(int i = 0; i < table.size(); ++i) {
	    Tuple* t = table[i];
        std::cout << "Tuple class: " << t->getTupleClass() << ", attributes: ";
	    for(int j = 0; j < (*t->getAttributes()).size(); ++j) {
            cout << t->getAttribute(j) << ", ";

        }
	    cout << endl;
	}

	Tuple* t2 = new Tuple(4, 1);
	vector<float>* attrs = t2->getAttributes();
	(*attrs)[0] = 1.0;
	(*attrs)[1] = 2.0;
	(*attrs)[2] = 2.0;
	(*attrs)[3] = 1.0;

	getReducedTable(&table, t2);


	cout << "Reduced table:" << endl;
	for(int i = 0; i < table.size(); ++i) {
	    Tuple* t = table[i];
        std::cout << "Tuple class: " << t->getTupleClass() << ", attributes: ";
	    for(int j = 0; j < (*t->getAttributes()).size(); ++j) {
            cout << t->getAttribute(j) << ", ";

        }
	    cout << endl;
	}

	candidateGeneratorTest(table);

	int input;
	std::cin >> input;
	return 0;
}

void candidateGeneratorTest(vector<Tuple*>& table_red) {
	CandidateGenerator candidateGenerator = CandidateGenerator(table_red, 3);
	candidateGenerator.execute();
	candidateGenerator.printSupportsOfCandiadtesLengthOne();
}

