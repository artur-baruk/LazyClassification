#ifndef CONTRAST_PATTERN_SCORER_H
#define CONTRAST_PATTERN_SCORER_H

#include <vector>
#include <iostream>
#include "Tuple.h"
#include "Candidate.h"
#include "HashTree.h"

using namespace std;


class ContrastPatternScorer {
	private:
		vector<Candidate*>& contrastPatterns;

	public:
		ContrastPatternScorer(vector<Candidate*>& tContrastPatterns): contrastPatterns(tContrastPatterns) { }
		
};
 
#endif
