#include "Tuple.h"

#ifndef REDUCED_TAB_CREATOR_H
#define REDUCED_TAB_CREATOR_H

using namespace std;

const float null_value = 0.0f;

/*
 * Enables to create reduced table based on an original table and a pattern to be classified.
 * 
 * 
 */
class ReducedTableCreator {
	private:
		vector<Tuple> table;
		Tuple tuple;
		
	public:
		/*
		* Gets an original table and a pattern (Tuple). Returns a reference to a reduced table.
		*/
		ReducedTableCreator(vector<Tuple> table, Tuple& tuple) {
			this->table = table;
			this->tuple = tuple;
		}

		vector<Tuple> getReducedTable(vector<Tuple> table, Tuple tuple) {
			int tupleAttributesSize = tuple.getAttributes().size();
			for (int i = 0; i < table.size(); i++) {
				for (int j = 0; j < tupleAttributesSize; j++) {
					if(tuple.getAttributes()[j] != table[i].getAttributes()[j]) {
						table[i].setAttribute(j, null_value);
					}
				}
			}
			return table;
		}
		
};
 
#endif