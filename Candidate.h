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
		vector<int>* attributes;			//nominal attributes like Temperature{Low=1, Mild=2, High=3}
		vector<int>* supports;			//vector of supports for particular classes (we usually have two classes)

	public:
		Candidate(vector<int>* attributes, vector<int>* supports) {
			this->attributes = attributes;
			this->supports = supports;
		}

		Candidate(vector<int>* attributes) { //in can be invoked in inte two-arguments constructor
			this->attributes = attributes;
		}

		vector<int>* getAttributes()  { return attributes; }

		vector<int>* getSupports() { return supports; }

		//porownanie atrybutow kandydata z podzbiorem atrybutow transakcji
		bool attributesEquals(vector<int>* p_attributes)
		{
			for(int i = 0; i<attributes->size();i++)
			{
				if (attributes->at(i) != p_attributes->at(i)) {
					return false;
				}
			}
			return true;

		}

		/*
		* A Candidate is a contrast pattern iff support of one class is not equal to zero and support of other classes is equal to zero.
		*/
		bool isContrastPattern() {
			int counterOfZeroSupports = 0;
			for(int i = 0; i < supports->size(); i++) {
				if(supports->at(i) == 0) {
					counterOfZeroSupports++;
				}
			}
			if(counterOfZeroSupports == supports->size() - 1) {
				return true;
			}
			return false;
		}

		bool isJoinable(Candidate* other) {
			if(attributes->size() != other->attributes->size()) {
				return false;
			}
			for(int i = 0; i < attributes->size() - 1; i++) {
				if(attributes->at(i) != other->attributes->at(i)) {
					return false;
				}
			}
			if(attributes->back() == other->attributes->back()) {
				return false;
			}
			return true;
		}

		void incrementSupport(int tClass) {
			++supports->at(tClass);
		}
};

#endif
