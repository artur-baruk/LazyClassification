#ifndef TUPLECREATOR_H_INCLUDED
#define TUPLECREATOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "stringtools.h"
#include "Tuple.h"

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

/**
 * Reads dataset from csv file
 */
void readTuples(const std::string& fileName, const std::vector<Type>& types, std::vector<Tuple*>& tuples) {

    std::string temp;
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());

    while(!inputFile.eof())
    {
        getline(inputFile, temp);
        std::vector<std::string> strs;
        split(temp, ',', strs);
        Tuple* t = new Tuple(strs.size() - 1);
        int attrCount = 0;
        for (int i = 0; i < strs.size(); ++i) {
            switch(types[i])
            {
                case AttrClass:
                    t->setTupleClass(strToInt(strs[i]));
                    break;
                case AttrInteger:
                    t->setAttribute(attrCount++, strToFloat(strs[i]));
                    break;
                case AttrReal:
                    t->setAttribute(attrCount++, strToFloat(strs[i]));
                    break;
                case AttrCategorical:
                    //TODO hashmapa itp
                    break;
            }
        }
        tuples.push_back(t);
    }
    //TODO po wszystkim trzeba znormalizowaæ atrybuty typu real

	inputFile.close();

    return;
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
