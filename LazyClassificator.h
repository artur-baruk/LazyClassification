#ifndef LAZY_CLASSIFICATOR_H
#define LAZY_CLASSIFICATOR_H

#include <iostream>
#include "Timer.h"
#include "Combination.h"
#include "Candidate.h"
#include "Tuple.h"
#include "TupleCreator.h"
#include "CandidateGenerator.h"
#include "ContrastPatternScorer.h"

using namespace std;

/*
 * The class that execute the process of classification.
 */
class LazyClassificator {
	private:
		std::vector<Tuple*>& reducedTable;			//table with reduced classified records
		Method method;
		OptimizationType optimizationType;
		std::vector<int>& objectsInClassesCount;

	public:
		LazyClassificator(vector<Tuple*>& tReducedTable, Method tMethod, OptimizationType tOptimizationType, vector<int>& tObjectsInClassesCount) : reducedTable(tReducedTable), objectsInClassesCount(tObjectsInClassesCount) {
			optimizationType = tOptimizationType;
			method = tMethod;
		}

		void executeParallelWithTwoLengthCounter() {
			//trzeba skopiowac n tablic zredukowanych
			// w petli odpalic n razy to samo co w executeWithNCounters, tylko wczesniej odpowiednio zmienić w reducedtable klasy na 0 i 1
			//zebrać wzorce kontarstujące i odpalic scorera
		}

		void executeWithNCounters() {
			CandidateGenerator candidateGenerator = CandidateGenerator(reducedTable, objectsInClassesCount.size(), optimizationType);
			candidateGenerator.execute(method);

			Timer t;
			t.start("SCORER execution time");
			ContrastPatternScorer scorer = ContrastPatternScorer(reducedTable, candidateGenerator.getContrastPatterns(), objectsInClassesCount);
			cout << "Wybrana klasa to : " << scorer.chooseDecisionClass();
			t.stop();
		}


};

#endif
