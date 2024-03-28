#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

// This class represents a single data point
// It has a feature vector and a label
// The feature vector is a vector of uint8_t
// The label is a uint8_t
// The enumerated label is an int
// The enumerated label is used to represent the label as an integer
// A -> 1, B -> 2 ...
class data 
{
  std::vector<uint8_t> * feature_vector; // no class at end.
  uint8_t label;
  int enum_label; // A -> 1, B -> 2 ...
  double distance;

  public:
  data();
  ~data();
  void set_feature_vector(std:: vector<uint8_t> *);
  void append_to_feature_vector(uint8_t);
  void set_label(uint8_t);
  void set_enumerated_label(int);
  void set_distance(double val);
  
  int get_feature_vector_size();
  uint8_t get_label();
  uint8_t get_enumerated_label();
  
  std::vector<uint8_t> * get_feature_vector();
};

#endif
