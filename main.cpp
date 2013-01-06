#include <iostream>
#include <vector>
#include <map>
#include "Tuple.h"
#include "Candidate.h"
#include "LazyClassificator.h"
#include "ReducedTableCreator.h"
#include "HashTreeNode.h"
#include "HashTree.h"

vector<Tuple> table;

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
	
	vector<float> vec1;
	vec1.push_back(1.0);
	vec1.push_back(3.0);
	vec1.push_back(2.0);
	Tuple t1 = Tuple(vec1, 2);
	Tuple t3 = Tuple(vec1, 3);
	table.push_back(t1);
	table.push_back(t3);
	vector<float> vec2;
	vec2.push_back(1.0);
	vec2.push_back(2.0);
	vec2.push_back(2.0);
	Tuple t2 = Tuple(vec2, 4);

	LazyClassificator classificator;
	ReducedTableCreator reducedTableCreator = ReducedTableCreator(table, t2);
	vector<Tuple> table_red = reducedTableCreator.getReducedTable(table, t2);
	for (int i=0; i < table_red.size(); i++) {
		std::cout << table_red[i].getTupleClass();
		std::cout << table_red[i].getAttributes()[0];
		std::cout << table_red[i].getAttributes()[1];
		std::cout << table_red[i].getAttributes()[2] << std::endl;
	}

	int input;
	std::cin >> input;
	return 0;
}

