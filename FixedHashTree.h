#ifndef FIXEDHASHTREE_H_INCLUDED
#define FIXEDHASHTREE_H_INCLUDED

#include "Candidate.h"

namespace FixedHashTree {


class HashTreeNode {
    private:
        int level; //roots level = 0
        int hash_arg;

        map<int,HashTreeNode*> children;
        vector<Candidate*> candidates;

	public:
        HashTreeNode(int hash_arg, int level) : hash_arg(hash_arg), level(level) {
            candidates.reserve(2);

        }

        ~HashTreeNode() //jakos tak bym rozjebal potomkow, dla candidates tylko czyscimy wektor
		{
			for ( int i = 0; i < children.size(); i++ ) {
				delete children[i];
			}
			children.clear();
			candidates.clear();
		};

		//wrzuca wsk na kandydata do wektora
		void insertCandidate(Candidate* p_candidate)
		{
		    if(children.empty() && candidates.size() < 2) {
                candidates.push_back(p_candidate);
		    }
            else {
                map<int,HashTreeNode*>::iterator it;
                for(int i = 0; i < candidates.size(); ++i) {
                    int hash = candidates[i]->getAttributes()->at(level) % hash_arg;
                    it = children.find(hash);
                    if(it == children.end()) {
                        children.insert(pair<int,HashTreeNode*>(hash, new HashTreeNode(hash_arg, level+1)));
                    }
                    children[hash]->insertCandidate(candidates[i]);

                }
                int hash = p_candidate->getAttributes()->at(level) % hash_arg;
                it = children.find(hash);
                if(it == children.end()) {
                    children.insert(pair<int,HashTreeNode*>(hash, new HashTreeNode(hash_arg, level+1)));
                }
                children[hash]->insertCandidate(p_candidate);
                candidates.clear();
            }
		}

		void print() {
		    for(map<int,HashTreeNode*>::iterator it = children.begin(); it != children.end(); ++it) {
                it->second->print();
		    }
		    std::cout << "Node level: " << level << std::endl;
		    std::cout << "Candidates count: " << candidates.size() << std::endl;
		    for(int i = 0; i < candidates.size(); ++i) {
                std::cout << "Candidate " << i << " attributes: ";
                std::vector<int>* attr = candidates[i]->getAttributes();
                for(int j = 0; j < attr->size(); ++j) {
                    std::cout << attr->at(j) << ", ";
                }
		    std::cout << std::endl;
		    }
		}

};

class HashTree {
  private:
		HashTreeNode* root;
		int hash_arg;
		int maxLevel;

	public:
		HashTree(std::vector<Candidate*>* p_candidates, int k) //k to dlugosc wstawianych kandydatow
		{
			maxLevel = k; // wysokosc drzewa
			hash_arg = k+1; // bedziemy haszowac hash = argument MOD hash_arg

			root = new HashTreeNode(hash_arg, 0);

			for ( int i = 0; i < p_candidates->size(); i++ ) {
				root->insertCandidate(p_candidates->at(i));
			}
		}

		~HashTree()
		{
			delete root;
			int i = 1;
		};

		int getMaxLevel() {
			return maxLevel;
		}

};


}

#endif // FIXEDHASHTREE_H_INCLUDED
