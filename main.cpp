#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include "Tuple.h"
#include "Candidate.h"
#include "LazyClassificator.h"
#include "HashTreeNode.h"
#include "HashTree.h"
#include "TupleCreator.h"

int main() {
	std::cout << "JEPs classification";

	/*
	 * 1. Read file with data and load data into decision table.
	 * 2. Create reduced decision table.
	 * 3. Find contrast patterns and calculate support.
	 */

	/*<testy drzewa>*/

	vector<Candidate*> candidates;

	vector<float>* attr1 = new vector<float>();
	attr1->push_back(1.0);
	attr1->push_back(2.0);

	vector<float>* attr2 = new vector<float>();
	attr2->push_back(4.0);
	attr2->push_back(3.0);

	vector<float>* attr3 = new vector<float>();
	attr3->push_back(2.0);
	attr3->push_back(5.0);

	vector<int>* sup1 = new vector<int>();
	sup1->push_back(0);
	sup1->push_back(0);

	candidates.push_back(new Candidate(attr1, 2, sup1 ));
	candidates.push_back(new Candidate(attr2, 2, sup1 ));
	candidates.push_back(new Candidate(attr3, 2, sup1 ));

	HashTree* ht = new HashTree(candidates,2);

	ht->printHashTree();

	/*</testy drzewa>*/

	getchar();

	vector<Tuple*> table;

	vector<Type> types;
    types.push_back(AttrClass);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);
    types.push_back(AttrInteger);

	readTuples("input.txt", types, table);

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

	int input;
	std::cin >> input;
	return 0;
}

