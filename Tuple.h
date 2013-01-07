#ifndef TUPLE_H
#define TUPLE_H

/**
 * Wrapper normalizing string data into transactinal (numbers instead of words).
 * Value 0.0 in a vector with attributes means not specified (null).
 * Value 0 of class field means that class is not yet specified.
 */
class Tuple {
	private:
		std::vector<float>* attributes;		//nominal attributes like Temperature{Low=1.0, Mild=2.0, High=3.0}
		int tupleClass;					//number of a class

	public:

        /**
         * Constructor initializing all attributes with -1
         */
		Tuple(int attrsCount, int tClass = -1) : tupleClass(tClass) {
		    attributes = new std::vector<float>(attrsCount);
		    for(int i = 0; i < attrsCount; ++i) {
		        (*attributes)[i] = -1;
		    }
		}

		~Tuple() {
		    if(attributes != NULL) {
                delete attributes;
		        attributes = NULL;
		    }
		}

		int getTupleClass() { return tupleClass; }

		void setTupleClass(int tClass) { tupleClass = tClass; }

		std::vector<float>* getAttributes() { return attributes; }

		void setAttribute(int index, float value) { (*attributes)[index] = value; }

		float getAttribute(int index) { return (*attributes)[index]; }

		//TODO: generowanie podzbiorow k-elementowych z transakcji
		std::vector<std::vector<float> >* getSubSets(int k)
		{
			std::vector<std::vector<float> >* subsets = new std::vector<std::vector<float> >();
			std::vector<float>* attributes_dense;
			for(int i=0; i<attributes->size(); i++)
			{
				attributes_dense->push_back((*attributes)[i]); //zakladam ze w attributes moga byc luki wiec przepisuje. Zakladam tez ze attributes jest uporzadkowany rosnaco
			}

			return subsets;

		}
};

#endif
