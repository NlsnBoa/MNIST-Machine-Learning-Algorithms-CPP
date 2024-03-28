#include "knn.hpp"
#include "cmath"
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.hpp"

knn::knn(int val)
{
  k = val;
}
knn::knn()
{
  // NOTHING TO DO
}
knn::~knn() 
{
  // NOTHING TO DO
}

void knn::find_knearest_neighbors(data * query_point) 
{
  neighbors = new std::vector<data *>();
  double min = std::numeric_limits<double>::max();
  double previous_min = min;
  int index = 0;

  for (int i = 0; i < k; i++)
  {
    if (i == 0)
    {
      for (int j = 0; j < training_data->size(); j++)
      {
        double distance = calculate_distance(query_point, training_data->at(j));
        training_data->at(j)->set_distance(distance);
        if (distance < min)
        {
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    } else 
    {
      for (int j = 0; j < training_data->size(); j++)
      {
        double distance = calculate_distance(query_point, training_data->at(j));
        training_data->at(j)->set_distance(distance);
        if (distance < min && distance > previous_min)
        {
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    
    }
  }
  
}
void knn::set_training_data(std::vector<data *> * vect)
{
  training_data = vect;
}
void knn::set_test_data(std::vector<data *> * vect)
{
  test_data = vect;
}
void knn::set_validation_data(std::vector<data *> * vect)
{
  validation_data = vect;
}
void knn::set_k(int val) 
{
  k = val;
}

int knn::predict();
double knn::calculate_distance(data * query_point, data * input)
{
  double distance = 0.0;
  if (query_point->get_feature_vector_size() != input->get_feature_vector_size())
  {
    printf("Feature vector sizes do not match\n");
    exit(1);
  }

  #ifdef EUCLID
    // Euclidean distance implementation here
    for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++)
    {
      distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
    }
    distance = sqrt(distance);
  #elif defined MANHATTAN
    // Manhattan distance implementation here
  #endif

  return distance;
}
double knn::validate_performance();
double knn::test_performance();