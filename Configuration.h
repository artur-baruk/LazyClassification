#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

using namespace std;

class Configuration {
  
	private:
		
		string training_data_path;
		string data_description_path;
		string objects_to_clsf_path;

	public:

		Configuration() {}

		string getTrainingDataPath() {return training_data_path;}

		string getDataDescriptionPath() {return data_description_path;}

		string getObjectsToClsfPath() {return objects_to_clsf_path;}

		void setTrainingDataPath(string p_str) {training_data_path = p_str;}

		void setDataDescriptionPath(string p_str) {data_description_path = p_str;}

		void setObjectsToClsfPath(string p_str) {objects_to_clsf_path = p_str;}
		

};

#endif
