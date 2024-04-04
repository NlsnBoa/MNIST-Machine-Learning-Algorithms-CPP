# MNIST Dataset Machine Learning Project

## Project Overview

This project is dedicated to exploring and benchmarking various popular Machine Learning (ML) algorithms on the MNIST dataset. The MNIST dataset, which stands for Modified National Institute of Standards and Technology, is a large database of hand-drawn digits (0 through 9) that is widely used for training and testing in the field of machine learning. Our goal is to train different ML models to accurately classify these hand-drawn numbers and evaluate their efficiency and performance.

## Objectives

- **Training ML Models**: Utilize several well-known machine learning algorithms to train models on the MNIST dataset.
- **Performance Evaluation**: Assess and compare the performance of each algorithm in terms of accuracy, speed, and resource consumption.
- **Efficiency Measurement**: Investigate the efficiency of each model, considering aspects such as training time and model complexity.
- **Benchmarking**: Create a comprehensive benchmark that includes the results and findings from our experiments, providing insights into the suitability of each algorithm for digit classification tasks.

## Machine Learning Algorithms

I plan to experiment with a variety of machine learning algorithms, including but not limited to:

- Support Vector Machines (SVM)
- Convolutional Neural Networks (CNN)
- Random Forests
- K-Nearest Neighbors (KNN)
- Decision Trees
- Gradient Boosting Machines (GBM)

## Dataset

The MNIST dataset comprises 60,000 training images and 10,000 testing images of hand-drawn digits, each of which is a 28x28 pixel grayscale image. This dataset provides a standard for evaluating the performance of image classification algorithms.

## Setup and Installation

Detailed instructions on how to set up the environment, install dependencies, and run the experiments will be provided. This will include steps for cloning the repository, installing required Python packages, and executing scripts to train models and evaluate their performance.

## Performance Metrics

I will evaluate the models based on several key performance metrics:

- **Accuracy**: The percentage of correctly classified images.
- **Precision and Recall**: Measures of the quality of the classification.
- **F1 Score**: The harmonic mean of precision and recall.
- **Execution Time**: The time taken to train the model and make predictions.

## Results and Discussion

The results of our experiments, including accuracy scores, performance metrics, and efficiency analysis, will be documented here. This section will provide insights into the strengths and weaknesses of each algorithm when applied to the MNIST dataset.

## Contributing

I welcome contributions from the community, including suggestions for additional algorithms to test, improvements to the codebase, and enhancements to the performance analysis. Please refer to the `CONTRIBUTING.md` file for more details on how to contribute to this project.

## Usage Notes

The essence of this project is to create libraries to be further implemented elsewhere. To make libraries we will be using a Makefile and running the scripts we need a library.

To use the "make" and "make clean" scripts you must run the following code in your terminal where the Makefile exists:

```
export MNIST_ML_ROOT=$PWD  
```

And in order to make a library is in your file path run the follwing code in your terminal while inside the "/lib" folder:

```
export LD_LIBRARY_PATH=$PWD
```

## License

Specify the license under which your project is released, ensuring that users and contributors are aware of their rights and obligations when using or contributing to your project.

---

This project aims to contribute to the machine learning community by providing detailed benchmarks and insights into the performance of various algorithms on the MNIST dataset. I hope that our findings will aid researchers and practitioners in selecting the most appropriate algorithms for their specific needs in digit classification tasks.
