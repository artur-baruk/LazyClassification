#include <iostream>
#include <vector>
#include "Tuple.h"
#include "Candidate.h"
#include "LazyClassificator.h"
#include "ReducedTableCreator.h"


vector<Tuple> table;

int main() {
	std::cout << "JEPs classification";

	/*
	 * 1. Read file with data and load data into decision table. 
	 * 2. Create reduced decision table.
	 * 3. Find contrast patterns and calculate support.
	 */
	
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

