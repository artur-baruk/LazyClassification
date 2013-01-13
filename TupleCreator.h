#ifndef TUPLECREATOR_H_INCLUDED
#define TUPLECREATOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "stringtools.h"
#include "Tuple.h"

const float null_value = -1.0f;

/**
 * Tuple attribute types
 */
enum Type
{
    AttrCategorical,
    AttrInteger,
    AttrReal,
    AttrClass
};

int getKeyIndex(vector<std::string>* vector, std::string key)
{
    for(int i = 0; i < vector->size(); ++i) {
        if(vector->at(i) == key)
            return i;
    }
    return -1;
}

/**
 * Reads dataset from csv file
 * Returns class count
 */
int readTuples(const std::string& fileName, const std::vector<Type>& types, std::vector<Tuple*>& tuples, std::vector<int>* objectsInClassesCount) {

    std::string temp;
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());

    std::vector<std::string> keys;
    std::vector<std::vector<std::string> > attrsKeys(types.size());

    while(!inputFile.eof())
    {
        getline(inputFile, temp);
        std::vector<std::string> strs;
        split(temp, ',', strs);
        Tuple* t = new Tuple(strs.size() - 1);
        int attrCount = 0;
        int keyIndex;
        for (int i = 0; i < strs.size(); ++i) {
            switch(types[i])
            {
                case AttrClass:
                    keyIndex = getKeyIndex(&keys, strs[i]);
                    if(keyIndex == -1) {
                        keys.push_back(strs[i]);
                        t->setTupleClass(keys.size() - 1);
                        objectsInClassesCount->push_back(1);
                    } else {
                        t->setTupleClass(keyIndex);
                        objectsInClassesCount->at(keyIndex)++;
                    }
                    break;
                case AttrInteger:
                    t->setAttribute(attrCount++, strToFloat(strs[i]));
                    break;
                case AttrReal:
                    t->setAttribute(attrCount++, strToFloat(strs[i]));
                    break;
                case AttrCategorical:
                    keyIndex = getKeyIndex(&attrsKeys[i], strs[i]);
                    if(keyIndex == -1) {
                        attrsKeys[i].push_back(strs[i]);
                        t->setAttribute(attrCount++, attrsKeys[i].size() - 1);
                    } else {
                        t->setAttribute(attrCount++, keyIndex);
                    }
                    break;
            }
        }
        tuples.push_back(t);
    }
    //TODO po wszystkim trzeba znormalizowaa atrybuty typu real

	inputFile.close();

    return keys.size();
}

void getReducedTable(std::vector<Tuple*>* table, Tuple* tuple) {
	int tupleAttributesSize = tuple->getAttributes()->size();
	for (int i = 0; i < table->size(); i++) {
		for (int j = 0; j < tupleAttributesSize; j++) {
			if((*tuple->getAttributes())[j] != (*(*table)[i]->getAttributes())[j]) {
				(*table)[i]->setAttribute(j, null_value);
			}
		}
	}
}

#endif // TUPLECREATOR_H_INCLUDED
