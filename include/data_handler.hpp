#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <fstream> // read for file i/o
#include "stdint.h" // uint8_t
#include "data.hpp" 
#include <vector> // dynamic array
#include <string> 
#include <map> // to map a class label to its enumerated value
#include <unordered_set> // to keep track of indexes as we split the data into training data test data and validation data 

// This class is responsible for reading in the data from the binary files
// It reads in the data and stores it in a vector of data objects
// It also splits the data into training data, test data, and validation data
// The data is stored in a vector of data objects
// The training data is stored in a vector of data objects
// The test data is stored in a vector of data objects
// The validation data is stored in a vector of data objects
// The class also keeps track of the number of classes and the size of the feature vector
// The class also keeps track of the mapping of class labels to enumerated values

// an explanation of how MNIST is stored: https://medium.com/theconsole/do-you-really-know-how-mnist-is-stored-600d69455937
class data_handler
{
  std::vector<data *> *data_array; // all of the data (pre-split)
  std::vector<data *> *training_data;
  std:: vector<data*> *test_data;
  std::vector<data *> *validation_data;

  int num_classes;
  int feature_vector_size;
  std::map<uint8_t, int> class_map;
  
  const double TRAIN_SET_PERCENT = 0.75;
  const double TEST_SET_PERCENT = 0.30;
  const double VALIDATION_PERCENT = 0.05;

  public :
  // Constructor
  data_handler();

  // Destructor
  ~data_handler();

  // Read in the data from the binary files
  void read_feature_vector(std::string path);
  void read_feature_labels(std::string path);

  // Split the data into training data, test data, and validation data  
  void split_data();
  // Count the number of classes in the data
  void count_classes();

  uint32_t convert_to_little_endian(const unsigned char* bytes);

  // Getters
  std::vector<data *> * get_training_data();
  std::vector<data *> * get_test_data();
  std::vector<data *> * get_validation_data();
};

#endif
