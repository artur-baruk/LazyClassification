#ifndef TUPLE_H
#define TUPLE_H

using namespace std;

/*
 * Wrapper normalizing string data into transactinal (numbers instead of words).
 * Value 0.0 in a vector with attributes means not specified (null).
 * Value 0 of class field means that class is not yet specified. 
 */
class Tuple {
	private:
		vector<float> attributes;		//nominal attributes like Temperature{Low=1.0, Mild=2.0, High=3.0} 
		int tupleClass;					//number of a class
 
	public:
		Tuple() {
		}

		Tuple(vector<float>& attributes, int tupleClass) {
			this->tupleClass = tupleClass;
			this->attributes = attributes;
		}

		int getTupleClass() { return tupleClass; }

		vector<float> getAttributes()  { return attributes; }

		void setAttribute(int index, float value) { attributes[index] = value; } 
		
		//TODO: generowanie podzbiorow k-elementowych z transakcji
		vector<vector<float>>* getSubSets(int k)
		{
			vector<vector<float>>* subsets = new vector<vector<float>>();
			vector<float>* attributes_dense;
			for(int i=0; i<attributes.size(); i++)
			{
				attributes_dense->push_back(attributes[i]); //zakladam ze w attributes moga byc luki wiec przepisuje. Zakladam tez ze attributes jest uporzadkowany rosnaco
			}
			
			return subsets;
							
		}
};
 
#endif
