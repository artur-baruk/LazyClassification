#ifndef LAZY_CLASSIFICATOR_H
#define LAZY_CLASSIFICATOR_H

#include <iostream>

/*
 * The class that execute the process of classification.
 */
class LazyClassificator {
	private:
		std::vector<Tuple*> reducedTable;			//table with reduced classified records


	public:
		LazyClassificator() {
			cout << "Creating Lazy Clasificator";
		}


};

#endif
