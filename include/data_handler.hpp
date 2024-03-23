#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <fstream> // read for file i/o
#include "stdint.h" // uint8_t
#include "data.hpp" 
#include <vector> // dynamic array
#include <string> 
#include <map> // to map a class label to its enumerated value
#include <unordered_set> // to keep track of indexes as we split the data into training data test data and validation data 

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
  data_handler();
  ~data_handler();

  void read_feature_vector(std::string path);
  void read_feature_vector(std::string path);
  void split_data();
  void count_classes();

  uint32_t convert_to_little_endian(const unsigned char* bytes);

  std::vector<data *> * get_training_data();
  std::vector<data *> * get_test_data();
  std::vector<data *> * get_validation_data();
};
#endif
