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
			Candidate* maxScoreCandidate;
			double maxScore = 0;

			for(int i = 0; i < contrastPatterns.size(); i++) {
				int currentCompactScore;
				if((currentCompactScore = calculateCompactScore(contrastPatterns[i])) > maxScore) {
					maxScore = currentCompactScore;
					maxScoreCandidate = contrastPatterns[i];
				}
			}

			if(maxScoreCandidate != NULL) {
				return getContrastPatternDecisonClass(maxScoreCandidate);
			} else {
				return -1;	//ERROR, there are no contrast patterns
			}
		}
		
};
 
#endif
