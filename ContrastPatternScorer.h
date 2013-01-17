#ifndef CONTRAST_PATTERN_SCORER_H
#define CONTRAST_PATTERN_SCORER_H

#include <vector>
#include <iostream>
#include "Candidate.h"
#include "Tuple.h"

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
			//FixedHashTree::HashTree* hashTree = new FixedHashTree::HashTree(contrastPatterns);

			//for(unsigned long i = 0; i < reducedTable.size(); i++) {
			//	reducedTable[i]->subset_and_count(hashTree);
			//}
			return -1;
		}

};

#endif
