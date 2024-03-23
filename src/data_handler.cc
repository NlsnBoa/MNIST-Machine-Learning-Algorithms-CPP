#include "data_handler.hpp"

data_handler::data_handler()
{
  data_array = new std::vector<data *>;
  test_data = new std::vector<data *>;
  training_data = new std::vector<data *>;
  validation_data = new std::vector<data *>;
}
data_handler::~data_handler()
{
  // FREE Dynamically Allocated things
}

void data_handler::read_feature_vector(std::string path)
{
  uint32_t header[4]; // Magic Number, Number of Images, Number of Rows, Number of Columns
  unsigned char bytes[4];
  FILE *file = fopen(path.c_str(), "r");
  if(file)
  {
    for(int i = 0; i < 4; i++)
    {
      if(fread(bytes, sizeof(bytes), 1, file))
      {
        header[i] = convert_to_little_endian(bytes);
      }
    }

    printf("Done getting input file header.\n");
    int image_size = header[2] * header[3];
    for(int i = 0; i < header[1]; i++)
    {
      data *d = new data();
      uint8_t element[1];
      for(int j = 0; j < image_size; j++)
      {
        if(fread(element, sizeof(element), 1, file))
        {
          d->append_to_feature_vector(element[0]);
        } else 
        {
          printf("Error reading image data.\n");
          exit(1);
        }
      }
      data_array->push_back(d);
    }
    printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
    
  } else 
  {
    printf("Error opening file.\n");
    exit(1);
  }
}


void data_handler::read_feature_vector(std::string path)
{
  uint32_t header[2]; // Magic Number, Number of Images
  unsigned char bytes[4];
  FILE *file = fopen(path.c_str(), "r");
  if(file)
  {
    for(int i = 0; i < 2; i++)
    {
      if(fread(bytes, sizeof(bytes), 1, file))
      {
        header[i] = convert_to_little_endian(bytes);
      }
    }

    printf("Done getting label file header.\n");
    for(int i = 0; i < header[1]; i++)
    {
      uint8_t element[1];
      if(fread(element, sizeof(element), 1, file))
      {
        data_array->at(i)->set_label(element[0]);
      } else 
      {
        printf("Error reading label data.\n");
        exit(1);
      }
    }
    printf("Successfully read and stored %lu labels.\n", data_array->size());
    
  } else 
  {
    printf("Error opening file.\n");
    exit(1);
  }
}
void data_handler::split_data()
{
  std::unordered_set<int> indexes;
  int num_training = TRAIN_SET_PERCENT * data_array->size();
  int num_test = TEST_SET_PERCENT * data_array->size();
  int num_validation = VALIDATION_PERCENT * data_array->size();
  while(indexes.size() < num_training)
  {
    indexes.insert(rand() % data_array->size());
  }
  for(int i = 0; i < data_array->size(); i++)
  {
    if(indexes.find(i) != indexes.end())
    {
      training_data->push_back(data_array->at(i));
    } else 
    {
      test_data->push_back(data_array->at(i));
    }
  }
  indexes.clear();
  while(indexes.size() < num_test)
  {
    indexes.insert(rand() % test_data->size());
  }
  for(int i = 0; i < test_data->size(); i++)
  {
    if(indexes.find(i) != indexes.end())
    {
      validation_data->push_back(test_data->at(i));
    } else 
    {
      test_data->push_back(test_data->at(i));
    }
  }
  printf("Training data size: %lu\n", training_data->size());
  printf("Test data size: %lu\n", test_data->size());
  printf("Validation data size: %lu\n", validation_data->size());

}
void count_classes();

uint32_t convert_to_little_endian(const unsigned char* bytes);
std::vector<data *> * get_training_data();
std::vector<data *> * get_test_data();
std::vector<data *> * get_validation_data();

