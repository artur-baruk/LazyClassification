#ifndef CANDIDATE_GENERATOR_H
#define CANDIDATE_GENERATOR_H

#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <math.h>


using namespace std;

enum Method
{
	Przemo,
	Michal1,
	Michal2
};

enum OptimizationType {
	No,
	Generators,
	Closures
};

/*
* Executes the porcess of candidates generation and collects contrast patterns;
*/
class CandidateGenerator {
private:
	vector<Tuple*>& reducedTable;
	vector<vector<Candidate*>*> candidates;
	vector<Candidate*> contrastPatterns;			//exists only in one class and not outside that class
	vector<vector<int> > supportsOfCandidates;		//vector to store supports of candidates of length 1
	const int numberOfClasses;
	HashTree* hashTree;
	FixedHashTree::HashTree* fixedHashTree;
	map<unsigned long, vector<Candidate*>*> mapOfCandidatesForGenerators;
	OptimizationType generatorOptimization;

	void findOneLengthCandidates() {
		if(reducedTable.size() == 0) {
			cout << "Empty reduced table";
			return;
		}

		const int numberOfCandidates = reducedTable[0]->getAttributes()->size();

		//initializes support matrix (candidate x class)
		for(int i = 0; i < numberOfCandidates; i++) {
			vector<int> internalSupports;
			for(int i = 0; i < numberOfClasses; i++) {
				internalSupports.push_back(0);
			}
			supportsOfCandidates.push_back(internalSupports);
		}

		//full scan of reduced table
		for(unsigned long i = 0; i < reducedTable.size(); i++) {
			for(int j = 0; j < numberOfCandidates; j++) {
				if((*reducedTable[i]->getAttributes())[j] > 0.0f) {
					int tClass = reducedTable[i]->getTupleClass();
					supportsOfCandidates[j][tClass]++;	//increment support of atribute in appropriate class
				}
			}
		}

		//create and insert candidate
		vector<Candidate*>* candidatesOfLengthOne = new vector<Candidate*>();
		for(int i = 0; i < numberOfCandidates; i++) {
			int candidateId = i + 1;
			vector<int>* attributes = new vector<int>();
			attributes->push_back(candidateId);
			Candidate* candidate =  new Candidate(attributes, &supportsOfCandidates[i]);
			cout << "Candidate " << candidateId << " is contast pattern: " << candidate->isContrastPattern() << endl;
			if(candidate->isContrastPattern()) {
				contrastPatterns.push_back(candidate);
			} else {
				candidatesOfLengthOne->push_back(candidate);
			}
		}
		candidates.push_back(candidatesOfLengthOne);

		//with generator optimisation
		if(generatorOptimization == Generators) {
			insertCandidatesToHashMapForGenerators(candidatesOfLengthOne);
		}
	}

	/*
	* Generates candidates of length k+1 based on candidates of length k.
	* Return true if there are at least two candidates generated (but not contrast patterns).
	*/
	vector<Candidate*>* generateCandidatesLengthKPlusOne(Method method, vector<Candidate*>* candidatesLenkthK) {
		vector<Candidate*>* candidatesLengthKPlusOne =  new vector<Candidate*>();			//it can contain contrast patterns as well
		vector<Candidate*>* candidatesLengthKPlusOneWithoutContrastPatterns =  new vector<Candidate*>();
						Timer t;
		t.start("Generate candidates");
		for(int i = 0; i < candidatesLenkthK->size(); i++) {
			for(int j = i + 1; j < candidatesLenkthK->size(); j++) {
				if((*candidatesLenkthK)[i]->isJoinable((*candidatesLenkthK)[j])) {
					vector<int>* attributes =  new vector<int>();
					joinCandidates(attributes, (*candidatesLenkthK)[i], (*candidatesLenkthK)[j]);
					vector<int>* supports = new vector<int>(numberOfClasses);
					Candidate* candidate = new Candidate(attributes,supports);
					candidatesLengthKPlusOne->push_back(candidate);
					cout << "pushing candidate" << endl;
				}
			}
		}
						t.stop();
						t.start("Build hash tree");
		switch(method) {
		case Przemo:
			hashTree = new HashTree(candidatesLengthKPlusOne, candidates.size() + 1);
			break;
		case Michal1: case Michal2:
			fixedHashTree = new FixedHashTree::HashTree(candidatesLengthKPlusOne, candidates.size() + 1);
			cout << endl << endl;
			break;
		}
						t.stop();
						t.start("Subset and count support");
		switch(method) {
		case Przemo:
			assignSupportsToCandidates(hashTree);
			break;
		case Michal1:
			assignSupportsToCandidatesFromAttrDense(fixedHashTree);
			break;
		}
						t.stop();
						t.start("Collect Contrast Pattern");
		collectContrastPattern(candidatesLengthKPlusOne, candidatesLengthKPlusOneWithoutContrastPatterns);	//and put into candidatesLengthKPlusOneWithoutContrastPatterns
						t.stop();
						t.start("Delete tree");
		if(fixedHashTree != NULL) {
			delete fixedHashTree;
			fixedHashTree = NULL;
		}
		if(hashTree != NULL) {
			delete hashTree;
			hashTree = NULL;
		}
						t.stop();
						cout << "Number of candidates = " << candidatesLengthKPlusOne->size() << endl;
						cout << "Number of candidates without contrast patterns = " << candidatesLengthKPlusOneWithoutContrastPatterns->size() << endl;
		
		//for generators
		if(generatorOptimization == Generators) {
			vector<Candidate*>* candidatesLengthPlusOneMinusGeneratorSupersets;
			candidatesLengthPlusOneMinusGeneratorSupersets = performGeneratorOptimisation(candidatesLengthKPlusOneWithoutContrastPatterns);
			insertCandidatesToHashMapForGenerators(candidatesLengthPlusOneMinusGeneratorSupersets);	
			candidates.push_back(candidatesLengthPlusOneMinusGeneratorSupersets);
			cout << "GEN candidates length of set: " << candidatesLengthPlusOneMinusGeneratorSupersets->size();
			delete candidatesLengthKPlusOne;
			return candidatesLengthPlusOneMinusGeneratorSupersets;
		}

		candidates.push_back(candidatesLengthKPlusOneWithoutContrastPatterns);
		delete candidatesLengthKPlusOne;
		return candidatesLengthKPlusOneWithoutContrastPatterns;
	}

	void collectContrastPattern(vector<Candidate*>* candidatesLenkthKPlusOne, vector<Candidate*>* candidatesLenkthKPlusOneWithoutContrastPatterns) {
		for(int i = 0; i < candidatesLenkthKPlusOne->size(); i++) {
			if((*candidatesLenkthKPlusOne)[i]->isContrastPattern()) {
				contrastPatterns.push_back((*candidatesLenkthKPlusOne)[i]);
			} else {
				candidatesLenkthKPlusOneWithoutContrastPatterns->push_back((*candidatesLenkthKPlusOne)[i]);
			}
		}
	}


	//does one scan of database and determine supports
	void assignSupportsToCandidates(HashTree* hashTree) {
		for(unsigned long i = 0; i < reducedTable.size(); i++) {
			reducedTable[i]->subset_and_count(hashTree);
		}
	}

	void assignSupportsToCandidatesFromAttrDense(FixedHashTree::HashTree* hashTree) {
		for(unsigned long i = 0; i < reducedTable.size(); i++) {
			reducedTable[i]->countSupportFromAttrDense(hashTree);
		}
	}

	void joinCandidates(vector<int>* attributes, Candidate* first, Candidate* second) {
		for(int i = 0; i < first->getAttributes()->size(); i++) {
			attributes->push_back(first->getAttributes()->at(i));
		}
		attributes->push_back(second->getAttributes()->back());
	}

	vector<Candidate*>* performGeneratorOptimisation(vector<Candidate*>* candidatesWithoutContrastPatterns) {
		//we create a list from a vector to increase the speed of candidates removal
		vector<Candidate*>* newSetOfCandidatesWithoutCP = new vector<Candidate*>();
		std::vector<Candidate*>::iterator it;
		for(it = candidatesWithoutContrastPatterns->begin(); it != candidatesWithoutContrastPatterns->end(); ++it) {
			if(!isForDeletionByGeneratorsOptimization(*it)) {
				newSetOfCandidatesWithoutCP->push_back(*it);
			}
		}
		return newSetOfCandidatesWithoutCP;
	}

	bool isForDeletionByGeneratorsOptimization(Candidate* candidate) {
		//generate subsets k-1 length
		for(int i = 0; i < candidate->getAttributes()->size(); i++) {
			vector<int> subset;
			subset.reserve(candidate->getAttributes()->size()-1);
			for(int k = 0; k < candidate->getAttributes()->size(); k++) {
				if(k != i) {
					subset.push_back((*candidate->getAttributes())[k]);
				}
			}
			unsigned long hashCode = calculateHashCode(&subset);
			if(mapOfCandidatesForGenerators.find(hashCode) != mapOfCandidatesForGenerators.end()) {
				vector<Candidate*>* candidatesOfHashCode = mapOfCandidatesForGenerators[hashCode];
				for(int k = 0; k < candidatesOfHashCode->size(); k++) {
					if((*candidatesOfHashCode)[k]->attributesEquals(&subset) && (*candidatesOfHashCode)[k]->equalsToSupports(candidate->getSupports())) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void insertCandidatesToHashMapForGenerators(vector<Candidate*>* candidates) {
		unsigned long curentIndexInHashMap = 0;
		for(int i = 0; i < candidates->size(); i++) {
			Candidate* candidate = (*candidates)[i];
			curentIndexInHashMap = calculateHashCode(candidate);

			if(mapOfCandidatesForGenerators.find(curentIndexInHashMap) == mapOfCandidatesForGenerators.end()) {
				vector<Candidate*>* candidatesOfHashCode = new vector<Candidate*>();
				candidatesOfHashCode->push_back(candidate);
				mapOfCandidatesForGenerators.insert(pair<unsigned long,vector<Candidate*>*>(curentIndexInHashMap,candidatesOfHashCode));
			} else {
				mapOfCandidatesForGenerators[curentIndexInHashMap]->push_back(candidate);
			}
		}
	}

	unsigned long calculateHashCode(Candidate* candidate) {
		vector<int>* attributes = candidate->getAttributes();
		return calculateHashCode(attributes);
	}

	unsigned long calculateHashCode(vector<int>* attributes) {
		unsigned long sumOfHashCodesOfAttributes = 0;
		const unsigned long one = 1;
		for(int i = 0; i < attributes->size(); i++) {
			sumOfHashCodesOfAttributes += one << ( i % 32) + i + one << ((*attributes)[i] % 32) + (*attributes)[i] + 1; 
		}
		return sumOfHashCodesOfAttributes;
	}

public:
	CandidateGenerator(vector<Tuple*>& tReducedTable, const int tNumberOfClasses, OptimizationType tGeneratorOptimisation): reducedTable(tReducedTable), numberOfClasses(tNumberOfClasses) {
		generatorOptimization = tGeneratorOptimisation;
		hashTree = NULL;
		fixedHashTree = NULL;
	}

	void execute(Method method) {
		Timer t;
		t.start("Candidates of length 1 generation & support count");
		findOneLengthCandidates();
		t.stop();
		if(candidates[0]->size() >= 2) {
			int k = 1;		//initial length of candidates that will be incremented
			while(1) {
				cout << "########################" << endl;
				cout << "Candidates of length [" << k +1  << "]" << endl;
				if(generateCandidatesLengthKPlusOne(method, candidates[k-1])->size() <= 1) {
					break;	//the process of generating patterns has finished
				}
				k++;
			}
		}
	}

	vector<vector<Candidate*>*>& getCandidates() { return candidates; }

	vector<Candidate*>* getContrastPatterns() { return &contrastPatterns; }

};

#endif
