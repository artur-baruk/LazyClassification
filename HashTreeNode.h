#ifndef HASH_TREE_NODE_H
#define HASH_TREE_NODE_H

using namespace std;

/*
 *
 */

class HashTreeNode {
  private:
		int level; //roots level = 0
		map<int,HashTreeNode*> children;
		vector<Candidate*> candidates;
		
 
	public:

		HashTreeNode(int p_level) {
			level = p_level;
		}

		~HashTreeNode() //jakos tak bym rozjebal potomkow, dla candidates tylko czyscimy wektor
		{
			for ( int i = 0; i < children.size(); i++ ) {
				delete children[i];
			}
			children.clear();
			candidates.clear();
		};

		//zwraca wskaznik na potomka o odpowiednim haszu. W przypadku kiedy taki potomek nie istnieje to go tworzy.
		HashTreeNode* getChild(int hash) 
		{
			map<int,HashTreeNode*>::iterator it;
			pair<map<int,HashTreeNode*>::iterator,bool> ret;
			it = children.find(hash);
			if (it == children.end()) {
			  ret =	children.insert(pair<int,HashTreeNode*>(hash,new HashTreeNode(level+1)));
			  it = ret.first;
			}
			return it->second;
		}

		//wrzuca wsk na kandydata do wektora
		void insertCandidate(Candidate* p_candidate)
		{
			candidates.push_back(p_candidate);
		}


		//do testow rekurencyjne drukowanie wezlow
		void print()
		{
			vector<float> attributes;
			cout << endl << "level: " << level << endl;
			cout << "num of children: " << children.size() << " " << endl;
			cout << "candidates:" << endl;
			for (int i=0; i<candidates.size(); i++)
			{
				cout << "candidate " << i << ": [";
				attributes = candidates[i]->getAttributes();
				for(int j=0; j<attributes.size();j++)
				{
					cout << attributes[j];
				}
				cout << "]";
			}
			map<int,HashTreeNode*>::iterator it;
			for ( it = children.begin(); it!=children.end();it++)
			{
				it->second->print();
			}
			
		}

};
 
#endif
