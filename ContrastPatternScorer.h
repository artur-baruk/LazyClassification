#ifndef CONTRAST_PATTERN_SCORER_H
#define CONTRAST_PATTERN_SCORER_H

#include <vector>
#include <iostream>
#include "Candidate.h"
#include "Tuple.h"
#include "FixedHashTree.h"

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
			classCardinalityTable(tClassCardinalityTable), reducedTable(tReducedTable){ }

		int chooseDecisionClass() {
			FixedHashTree::HashTree* hashTree = new FixedHashTree::HashTree(contrastPatterns, 0);
			assignCompactSupportsToCandidatesFromAttrDense(hashTree, &compactSupportOfClassesCounter);

			int indexOfClass = 0;
			double maxCompactScore = 0.0;
			double currentComapctScore = 0.0;
			for(int i = 0; i < classCardinalityTable.size(); i++) {
				currentComapctScore = compactSupportOfClassesCounter[i] / classCardinalityTable[i];
				if(currentComapctScore > maxCompactScore) {
					maxCompactScore = currentComapctScore;
					indexOfClass = i;
				}
			}
			return indexOfClass;
		}


};

#endif
