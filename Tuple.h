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

		// generowanie podzbiorow k-elementowych z transakcji
		std::vector<std::vector<int>*>* getSubSets(int k)
		{
			std::vector<std::vector<int>*>* subsets = new std::vector<std::vector<int>*>();
			std::vector<int>* attributes_dense;
			std::vector<int>* subset;

			for(int i=0; i<attributes->size(); i++)
			{
				if(attributes->at(i) !=  -1) 
				{
					attributes_dense->push_back(i);
				}
			}
			
			int num_of_attributes = attributes_dense->size(); //ile elementow ma transakcja
			int subset_size = k;
			int last_start = num_of_attributes - subset_size +1; //attributes are ordered, the starting items can only by from 1 to last_start
			
			if (num_of_attributes < subset_size)
				return subsets;

			for(int i=0; i<last_start; i++) 
			{
				for(int j=i+1; j<num_of_attributes; j++)
				{
					subset = new std::vector<int>();
					subset->push_back(attributes_dense->at(i));
					subset->push_back(attributes_dense->at(j));
					subsets->push_back(subset);
				}
			}
			return subsets;
		}

		//bierze jedna transakcje, rozbija na podzbiory i jedzie każdym podzbiorem po drzewie az do liscia.
		//w lisciu sprawdza czy jest kandydat rowny temu podzbiorowi. Jezeli jest to podbija wsparcie kandydata o 1
		//przed uzyciem tej funkcji trzeba zbudowac drzewo k-elementowych kandydatow. HashTree* ht = new HashTree(candidates,k);
		void subset_and_count(HashTree* tree) 
		{
			int k = tree->getMaxLevel();
			std::vector<std::vector<int>*>* subsets = getSubSets(k);
			for(int i=0; i<subsets->size();i++) 
			{
				tree->countSupport(subsets->at(i),tupleClass);
			}
		}

};

#endif
