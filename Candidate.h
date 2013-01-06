#ifndef CANDIDATE_H
#define CANDIDATE_H

using namespace std;

/*
 * Wrapper normalizing string data into transactinal (numbers instead of words).
 * Value 0.0 in a vector with attributes means not specified (null).
 * Value 0 of class field means that class is not yet specified. 
 */
class Candidate {
	private:
		vector<float> attributes;		//nominal attributes like Temperature{Low=1.0, Mild=2.0, High=3.0} 
		int length;						//number of attributes in the candidate (that are not equal to 0.0)
		vector<int> supports;			//vector of supports for particular classes (we usually have two classes)
 
	public:
		Candidate(vector<float>* attributes, int length, vector<int>* supports) {
			this->attributes = *attributes;
			this->length = length;
			this->supports = *supports;
		}

		vector<float> getAttributes()  { return attributes; }

		int getLength() { return length; }

		vector<int> getSupports() { return supports; }
		
		//porownanie atrybutow kandydata z podzbiorem atrybutow transakcji
		bool attributesEquals(vector<float>* p_attributes) 
		{
			bool result = true;
			for(int i = 0; i<attributes.size();i++)
			{
				if (attributes[i] != p_attributes->at(i)) {
					result = false;
				}
			}
			return result;

		}
};
 
#endif
