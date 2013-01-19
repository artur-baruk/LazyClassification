#ifndef CONTRAST_PATTERN_SCORER_H
#define CONTRAST_PATTERN_SCORER_H

#include <vector>
#include <iostream>
#include "Candidate.h"
#include "Tuple.h"
#include "FixedHashTree.h"


#define HASH_DISTRIBUTE 371-1

using namespace std;

class ContrastPatternScorer {
	private:
		vector<Candidate*>* contrastPatterns;
		vector<int>& classCardinalityTable;
		vector<Tuple*>& reducedTable;
		vector<int> compactSupportOfClassesCounter;

		void assignCompactSupportsToCandidatesFromAttrDense(FixedHashTree::HashTree* hashTree, vector<int>* compactSupportOfClassesCounter) {
			for(unsigned long i = 0; i < reducedTable.size(); i++) {
				reducedTable[i]->countCompactSupportFromAttrDense(compactSupportOfClassesCounter, hashTree);
			}
		}

	public:
		ContrastPatternScorer(vector<Tuple*>& tReducedTable, vector<Candidate*>* tContrastPatterns, vector<int>& tClassCardinalityTable): contrastPatterns(tContrastPatterns),  
						classCardinalityTable(tClassCardinalityTable), reducedTable(tReducedTable){ 
			for(int i = 0; i < classCardinalityTable.size(); i++) {
				compactSupportOfClassesCounter.push_back(0);
			}
		}

		int chooseDecisionClass() {
			Timer t;
			t.start("hash tree build");
			FixedHashTree::HashTree* hashTree = new FixedHashTree::HashTree(contrastPatterns, HASH_DISTRIBUTE);
			t.stop();
			t.start("assign compact supports");
			assignCompactSupportsToCandidatesFromAttrDense(hashTree, &compactSupportOfClassesCounter);
			t.stop();

			int indexOfClass = 0;
			double maxCompactScore = 0.0;
			double currentComapctScore = 0.0;
			for(int i = 0; i < classCardinalityTable.size(); i++) {
				currentComapctScore = ((double)compactSupportOfClassesCounter[i]) / ((double)classCardinalityTable[i]);
				cout << "score dla klasy " << i << ": " << currentComapctScore << endl;
				if(currentComapctScore > maxCompactScore) {
					maxCompactScore = currentComapctScore;
					indexOfClass = i;
				}
			}
			return indexOfClass;
		}

};

#endif
