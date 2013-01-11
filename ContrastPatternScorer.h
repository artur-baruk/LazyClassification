#ifndef CONTRAST_PATTERN_SCORER_H
#define CONTRAST_PATTERN_SCORER_H

#include <vector>
#include <iostream>
#include "Candidate.h"

using namespace std;

class ContrastPatternScorer {
	private:
		vector<Candidate*>& contrastPatterns;
		vector<int>& classCardinalityTable;

		double calculateCompactScore(Candidate* candidate) {
			int numberOfTuplesInClass = classCardinalityTable[getContrastPatternDecisonClass(candidate)];
			double x = (double) getContrastPatternSupport(candidate);
			double y = ((double) getContrastPatternSupport(candidate)) / ((double) numberOfTuplesInClass);
			return ((double) getContrastPatternSupport(candidate)) / ((double) numberOfTuplesInClass);
		}

		int getContrastPatternSupport(Candidate* candidate) {
			for(int i = 0; i < candidate->getSupports().size(); i++) {
				if(candidate->getSupports()[i] != 0) {
					return candidate->getSupports()[i];
				}
			}
			return -1;		//candidate is not a contrast pattern
		}

		int getContrastPatternDecisonClass(Candidate* candidate) {
			for(int i = 0; i < candidate->getSupports().size(); i++) {
				if(candidate->getSupports()[i] != 0) {
					return i;
				}
			}
			return -1;		//candidate is not a contrast pattern
		}

	public:
		ContrastPatternScorer(vector<Candidate*>& tContrastPatterns, vector<int>& tClassCardinalityTable): contrastPatterns(tContrastPatterns),  classCardinalityTable(tClassCardinalityTable){ }

		int chooseDecisionClass() {
			Candidate* maxScoreCandidate = NULL;
			double maxScore = 0.0;
			int maxScoreIndex = 0;

			for(int i = 0; i < contrastPatterns.size(); i++) {
				double currentCompactScore = calculateCompactScore(contrastPatterns[i]);
				if(currentCompactScore > maxScore) {
					maxScore = currentCompactScore;
					maxScoreCandidate = contrastPatterns[i];
					maxScoreIndex = i;
				}
			}

			if(maxScoreCandidate != NULL) {
				cout << "Max score con pattern index: " << maxScoreIndex << endl;
				return getContrastPatternDecisonClass(maxScoreCandidate);
			} else {
				return -1;	//ERROR, there are no contrast patterns
			}
		}
		
};
 
#endif
