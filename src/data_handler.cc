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
  // header[0] = magic number 
  // header[1] = number of images
  // header[2] = number of rows
  // header[3] = number of columns
  uint32_t header[4]; // Magic Number, Number of Images, Number of Rows, Number of Columns
  unsigned char bytes[4];
  FILE *file = fopen(path.c_str(), "r");

  if(file)
  {
    // Read the header
    // The header is 4 bytes long
    // The first 4 bytes are the magic number
    // The next 4 bytes are the number of images
    // The next 4 bytes are the number of rows
    // The next 4 bytes are the number of columns
    for(int i = 0; i < 4; i++)
    {
      if(fread(bytes, sizeof(bytes), 1, file))
      {
        header[i] = convert_to_little_endian(bytes);
        printf("Header[%d]: %d\n", i, header[i]);
      }
    }

    printf("Done getting input file header.\n");
    int image_size = header[2] * header[3];
    int num_images = header[1];

    // Read the image data
    // Each image is 28x28 pixels
    // Each pixel is a byte
    // Each image is 28 * 28 = 784 bytes
    for(int i = 0; i < num_images; i++)
    {
      // Create a new data object
      data *d = new data();
      uint8_t element[1];
      // Read the image data
      for(int j = 0; j < image_size; j++)
      {
        // Read the pixel value
        if(fread(element, sizeof(element), 1, file))
        {
          d->append_to_feature_vector(element[0]);
        } else 
        {
          printf("Error reading image data.\n");
          exit(1);
        }
      }
      // Add the data object to the data array
      data_array->push_back(d);
    }
    printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
    
  } else 
  {
    printf("Error opening file.\n");
    exit(1);
  }
}


void data_handler::read_feature_labels(std::string path)
{
  // header[0] = magic number
  // header[1] = number of labels
  uint32_t header[2]; // Magic Number, Number of Images
  unsigned char bytes[4];
  FILE *file = fopen(path.c_str(), "r");

  if(file)
  {
    // Read the header
    for(int i = 0; i < 2; i++)
    {
      if(fread(bytes, sizeof(bytes), 1, file))
      {
        header[i] = convert_to_little_endian(bytes);
      }
    }

    printf("Done getting label file header.\n");
    int num_labels = header[1];

    // Read the label data
    for(int i = 0; i < num_labels; i++)
    {
      uint8_t element[1];

      // We must store the label in a data object it corresponds to
      if(fread(element, sizeof(element), 1, file))
      {
        data_array->at(i)->set_label(element[0]);
      } else 
      {
        printf("Error reading label data.\n");
        exit(1);
      }
    }
    printf("Successfully read and stored labels.\n");
    
  } else 
  {
    printf("Error opening file.\n");
    exit(1);
  }
}

void data_handler::split_data()
{
  printf("Splitting data into training data, test data, and validation data.\n");
  std::unordered_set<int> used_indexes;
  int training_size = TRAIN_SET_PERCENT * data_array->size();
  int testing_size = TEST_SET_PERCENT * data_array->size();
  int validation_size = VALIDATION_PERCENT * data_array->size();

  // Training data
  int count = 0;
  while(count < training_size)
  {
    int rand_index = rand() % data_array->size(); // Random number between 0 and the size of the data array
    if (used_indexes.find(rand_index) == used_indexes.end())
    {
      // Notice how we are storing pointers to data objects not the data objects themselves
      training_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }

  // Test data
  count = 0;
  while(count < testing_size)
  {
    int rand_index = rand() % data_array->size(); // Random number between 0 and the size of the data array
    if (used_indexes.find(rand_index) == used_indexes.end())
    {
      // Notice how we are storing pointers to data objects not the data objects themselves
      test_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }


  // Validation data
  count = 0;
  while(count < validation_size)
  {
    int rand_index = rand() % data_array->size(); // Random number between 0 and the size of the data array
    if (used_indexes.find(rand_index) == used_indexes.end())
    {
      // Notice how we are storing pointers to data objects not the data objects themselves
      validation_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }

  // Sanity check
  printf("Training data size: %lu\n", training_data->size());
  printf("Test data size: %lu\n", test_data->size());
  printf("Validation data size: %lu\n", validation_data->size());
}

void data_handler::count_classes()
{
  int count = 0;
  // Iterate through the data array and count the number of classes
  for (unsigned int i = 0; i < data_array->size(); i++)
  {
    // If the class label is not in the map, add it
    if(class_map.find(data_array->at(i)->get_label()) == class_map.end())
    {
      // Add the class label to the map
      class_map[data_array->at(i)->get_label()] = count;
      // Set the enumerated label
      data_array->at(i)->set_enumerated_label(count);
      count++;
    }
  }

  num_classes = count;
  printf("Successfuly Extracted %d Unique Classes.\n", num_classes);
}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes)
{
  return (uint32_t) ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

std::vector<data *> * data_handler::get_training_data() 
{
  return training_data;
}

std::vector<data *> * data_handler::get_test_data()
{
  return test_data;
}

std::vector<data *> * data_handler::get_validation_data()
{
  return validation_data;
}

// int main() 
// {
//   data_handler *dh = new data_handler();
//   dh->read_feature_vector("data/train-images.idx3-ubyte");
//   dh->read_feature_labels("data/train-labels.idx1-ubyte");
//   dh->split_data();
//   dh->count_classes();

//   return 0;
// }