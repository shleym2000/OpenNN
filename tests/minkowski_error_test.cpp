//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   M I N K O W S K I   E R R O R   T E S T   C L A S S                   
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "minkowski_error_test.h"


MinkowskiErrorTest::MinkowskiErrorTest() : UnitTesting() 
{
}


MinkowskiErrorTest::~MinkowskiErrorTest() 
{
}


void MinkowskiErrorTest::test_constructor()
{
   cout << "test_constructor\n";

   // Default

   MinkowskiError minkowski_error1;

   assert_true(!minkowski_error1.has_neural_network(), LOG);
   assert_true(!minkowski_error1.has_data_set(), LOG);

   // Neural network and data set

   NeuralNetwork nn3;
   DataSet ds3;
   MinkowskiError minkowski_error3(&nn3, &ds3);

   assert_true(minkowski_error3.has_neural_network(), LOG);
   assert_true(minkowski_error3.has_data_set(), LOG);
}


void MinkowskiErrorTest::test_destructor()
{
   cout << "test_destructor\n";
}


void MinkowskiErrorTest::test_get_Minkowski_parameter()
{
   cout << "test_get_Minkowski_parameter\n";

   MinkowskiError minkowski_error;

   minkowski_error.set_Minkowski_parameter(1.0);
   
   assert_true(minkowski_error.get_Minkowski_parameter() == 1.0, LOG);
}


void MinkowskiErrorTest::test_set_Minkowski_parameter()
{
   cout << "test_set_Minkowski_parameter\n";
}


void MinkowskiErrorTest::test_calculate_error()
{
   cout << "test_calculate_error\n";

   NeuralNetwork neural_network;

   Tensor<type, 1> parameters;

   Tensor<type, 2> data;

   DataSet data_set(1, 1, 1);
   data_set.initialize_data(0.0);

   Index samples_number;
   Index inputs_number;
   Index target_number;

   MinkowskiError minkowski_error(&neural_network, &data_set);
   minkowski_error.set_Minkowski_parameter(1.5);
   minkowski_error.set_regularization_method(LossIndex::RegularizationMethod::NoRegularization);

   // Test trivial

   samples_number = 1;
   inputs_number = 1;
   target_number = 1;

   DataSetBatch batch(1, &data_set);

   Tensor<Index,1> training_samples_indices = data_set.get_training_samples_indices();
   Tensor<Index,1> inputs_indices = data_set.get_input_variables_indices();
   Tensor<Index,1> targets_indices = data_set.get_target_variables_indices();

   batch.fill(training_samples_indices, inputs_indices, targets_indices);

   Tensor<Index, 1> architecture(2);
   architecture.setValues({inputs_number,target_number});

   neural_network.set(NeuralNetwork::Approximation, architecture);
   neural_network.set_parameters_constant(0);

   NeuralNetworkForwardPropagation forward_propagation(data_set.get_training_samples_number(), &neural_network);
   LossIndexBackPropagation training_back_propagation(data_set.get_training_samples_number(), &minkowski_error);

   neural_network.forward_propagate(batch, forward_propagation);
   minkowski_error.back_propagate(batch, forward_propagation, training_back_propagation);

   minkowski_error.calculate_error(batch, forward_propagation, training_back_propagation);

   assert_true(training_back_propagation.error == 0.0, LOG);

   // Test

   neural_network.set_parameters_constant(1);

   NeuralNetworkForwardPropagation forward_propagation_2(data_set.get_training_samples_number(), &neural_network);
   LossIndexBackPropagation training_back_propagation_2(data_set.get_training_samples_number(), &minkowski_error);

   neural_network.forward_propagate(batch, forward_propagation_2);
   minkowski_error.back_propagate(batch, forward_propagation_2, training_back_propagation_2);

   minkowski_error.calculate_error(batch, forward_propagation_2, training_back_propagation_2);

   assert_true(training_back_propagation_2.error - 0.761 < 1.0e-3, LOG);
}


void MinkowskiErrorTest::test_calculate_selection_error()
{
   cout << "test_calculate_selection_error\n";
}


void MinkowskiErrorTest::test_calculate_error_gradient()
{
   cout << "test_calculate_error_gradient\n";

   DataSet data_set;

   Tensor<Index, 1> samples_indices;
   Tensor<Index, 1> input_indices;
   Tensor<Index, 1> target_indices;

   DataSetBatch batch;

   NeuralNetwork neural_network;
   NeuralNetworkForwardPropagation forward_propagation;

   MinkowskiError minkowski_error(&neural_network, &data_set);

   Tensor<type, 1> error_gradient;
   Tensor<type, 1> numerical_error_gradient;

   Index samples_number;
   Index inputs_number;
   Index outputs_number;
   Index hidden_neurons;

   LossIndexBackPropagation training_back_propagation(samples_number, &minkowski_error);

   ScalingLayer* scaling_layer;

   RecurrentLayer* recurrent_layer;

   LongShortTermMemoryLayer* long_short_term_memory_layer;

   PerceptronLayer* perceptron_layer_1;
   PerceptronLayer* perceptron_layer_2;

   ProbabilisticLayer* probabilistic_layer;

//    Test perceptron and probabilistic
{

   samples_number = 2;
   inputs_number = 4;
   hidden_neurons = 3;
   outputs_number = 10;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.set_data_binary_random();

   data_set.set_training();

   batch.set(samples_number, &data_set);

   samples_indices = data_set.get_training_samples_indices();
   input_indices = data_set.get_input_variables_indices();
   target_indices = data_set.get_target_variables_indices();

   batch.set(samples_number, &data_set);

   batch.fill(samples_indices, input_indices, target_indices);

   perceptron_layer_1->set(inputs_number, hidden_neurons);
   probabilistic_layer->set(hidden_neurons, outputs_number);

   neural_network.add_layer(perceptron_layer_1);
   neural_network.add_layer(probabilistic_layer);

   neural_network.set_parameters_random();

   minkowski_error.set_Minkowski_parameter(1.5);

   forward_propagation.set(samples_number, &neural_network);
   training_back_propagation.set(samples_number, &minkowski_error);

   minkowski_error.set_regularization_method(LossIndex::RegularizationMethod::NoRegularization);

   neural_network.forward_propagate(batch, forward_propagation);

   minkowski_error.back_propagate(batch, forward_propagation, training_back_propagation);

   error_gradient = training_back_propagation.gradient;

   numerical_error_gradient = minkowski_error.calculate_gradient_numerical_differentiation();

   assert_true(are_equal(error_gradient, numerical_error_gradient, 1.0e-3), LOG);
}


   // Test trivial
{

   samples_number = 10;
   inputs_number = 1;
   outputs_number = 1;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.initialize_data(0.0);

   batch.set(samples_number, &data_set);

   samples_indices = data_set.get_training_samples_indices();
   input_indices = data_set.get_input_variables_indices();
   target_indices = data_set.get_target_variables_indices();

   batch.fill(samples_indices, input_indices, target_indices);

   perceptron_layer_1->set(inputs_number, outputs_number);
   neural_network.add_layer(perceptron_layer_1);

   neural_network.set_parameters_constant(0.0);

   forward_propagation.set(samples_number, &neural_network);
   training_back_propagation.set(samples_number, &minkowski_error);
   minkowski_error.back_propagate(batch, forward_propagation, training_back_propagation);

   neural_network.forward_propagate(batch, forward_propagation);
   numerical_error_gradient = minkowski_error.calculate_gradient_numerical_differentiation();

   minkowski_error.calculate_error_gradient(batch, forward_propagation, training_back_propagation);

   assert_true(are_equal(training_back_propagation.gradient, numerical_error_gradient), LOG);

}

   // Test perceptron and probabilistic
{

   neural_network.set();

   samples_number = 10;
   inputs_number = 3;
   outputs_number = 2;
   hidden_neurons = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.set_data_random();

   data_set.set_training();

   perceptron_layer_1->set(inputs_number, hidden_neurons);
   perceptron_layer_2->set(hidden_neurons, outputs_number);
   probabilistic_layer->set(outputs_number, outputs_number);

   neural_network.add_layer(perceptron_layer_1);
   neural_network.add_layer(perceptron_layer_2);
   neural_network.add_layer(probabilistic_layer);

   neural_network.set_parameters_random();

//   minkowski_error.calculate_error_gradient();

   numerical_error_gradient = minkowski_error.calculate_gradient_numerical_differentiation();

   assert_true(are_equal(error_gradient, numerical_error_gradient ,1.0e-3), LOG);

}

   // Test lstm
{

   neural_network.set();
   samples_number = 10;
   inputs_number = 3;
   outputs_number = 2;
   hidden_neurons = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.set_data_random();

   data_set.set_training();

   long_short_term_memory_layer->set(inputs_number, hidden_neurons);
   perceptron_layer_2->set(hidden_neurons, outputs_number);

   neural_network.add_layer(long_short_term_memory_layer);
   neural_network.add_layer(perceptron_layer_2);

   neural_network.set_parameters_random();
//   error_gradient = me.calculate_error_gradient();

//   numerical_error_gradient = me.calculate_gradient_numerical_differentiation();

//   assert_true(absolute_value(error_gradient - numerical_error_gradient) < 1.0e-3, LOG);

}

   // Test recurrent
{

   neural_network.set();

   samples_number = 10;
   inputs_number = 3;
   outputs_number = 2;
   hidden_neurons = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.set_data_random();

   data_set.set_training();

   recurrent_layer->set(inputs_number, hidden_neurons);
   perceptron_layer_2->set(hidden_neurons, outputs_number);

   neural_network.add_layer(recurrent_layer);
   neural_network.add_layer(perceptron_layer_2);

   neural_network.set_parameters_random();

//   error_gradient = me.calculate_error_gradient();

   numerical_error_gradient = minkowski_error.calculate_gradient_numerical_differentiation();

   assert_true(are_equal(error_gradient, numerical_error_gradient, 1.0e-3), LOG);

}

   // Test convolutional
{

   samples_number = 5;
   inputs_number = 147;
   outputs_number = 1;

   data_set.set(samples_number, inputs_number, outputs_number);
//   data_set.set_input_variables_dimensions(Tensor<Index, 1>({3,7,7}));
   data_set.set_data_random();
   data_set.set_training();

//   const type parameters_minimum = -100.0;
//   const type parameters_maximum = 100.0;

//   ConvolutionalLayer* convolutional_layer_1 = new ConvolutionalLayer({3,7,7}, {2,2,2});
//   Tensor<type, 2> filters_1({2,3,2,2}, 0);
//   filters_1.setRandom(parameters_minimum,parameters_maximum);
//   convolutional_layer_1->set_synaptic_weights(filters_1);
//   Tensor<type, 1> biases_1(2, 0);
//   biases_1.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_1->set_biases(biases_1);

//   ConvolutionalLayer* convolutional_layer_2 = new ConvolutionalLayer(convolutional_layer_1->get_outputs_dimensions(), {2,2,2});
//   convolutional_layer_2->set_padding_option(OpenNN::ConvolutionalLayer::Same);
//   Tensor<type, 2> filters_2({2,2,2,2}, 0);
//   filters_2.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_2->set_synaptic_weights(filters_2);
//   Tensor<type, 1> biases_2(2, 0);
//   biases_2.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_2->set_biases(biases_2);

//   PoolingLayer* pooling_layer_1 = new PoolingLayer(convolutional_layer_2->get_outputs_dimensions(), {2,2});

//   ConvolutionalLayer* convolutional_layer_3 = new ConvolutionalLayer(pooling_layer_1->get_outputs_dimensions(), {1,2,2});
//   convolutional_layer_3->set_padding_option(OpenNN::ConvolutionalLayer::Same);
//   Tensor<type, 2> filters_3({1,2,2,2}, 0);
//   filters_3.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_3->set_synaptic_weights(filters_3);
//   Tensor<type, 1> biases_3(1, 0);
//   biases_3.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_3->set_biases(biases_3);

//   PoolingLayer* pooling_layer_2 = new PoolingLayer(convolutional_layer_3->get_outputs_dimensions(), {2,2});
//   pooling_layer_2->set_pooling_method(PoolingLayer::MaxPooling);

//   PoolingLayer* pooling_layer_3 = new PoolingLayer(pooling_layer_2->get_outputs_dimensions(), {2,2});
//   pooling_layer_3->set_pooling_method(PoolingLayer::MaxPooling);

//   PerceptronLayer* perceptron_layer = new PerceptronLayer(pooling_layer_3->get_outputs_dimensions().calculate_product(), 3, OpenNN::PerceptronLayer::ActivationFunction::Linear);
//   perceptron_layer->set_parameters_random(parameters_minimum, parameters_maximum);

//   ProbabilisticLayer* probabilistic_layer = new ProbabilisticLayer(perceptron_layer->get_neurons_number(), outputs_number);
//   probabilistic_layer->set_parameters_random(parameters_minimum, parameters_maximum);

//   neural_network.set();
//   neural_network.add_layer(convolutional_layer_1);
//   neural_network.add_layer(convolutional_layer_2);
//   neural_network.add_layer(pooling_layer_1);
//   neural_network.add_layer(convolutional_layer_3);
//   neural_network.add_layer(pooling_layer_2);
//   neural_network.add_layer(pooling_layer_3);
//   neural_network.add_layer(perceptron_layer);
//   neural_network.add_layer(probabilistic_layer);

//   numerical_error_gradient = me.calculate_gradient_numerical_differentiation();

//   error_gradient = me.calculate_error_gradient();

//   assert_true(absolute_value(numerical_error_gradient - error_gradient) < 1e-3, LOG);

}

}


void MinkowskiErrorTest::test_to_XML()
{
   cout << "test_to_XML\n";  

//   MinkowskiError minkowski_error;

//   tinyxml2::XMLDocument* document;

   // Test

//   document = me.to_XML();

//   assert_true(document != nullptr, LOG);

//   delete document;

}


void MinkowskiErrorTest::test_from_XML()    // @todo
{
   cout << "test_from_XML\n";

//   MinkowskiError minkowski_error1;
//   MinkowskiError minkowski_error2;

//  tinyxml2::XMLDocument* document;

//  // Test

//  me1.set_Minkowski_parameter(1.33);
//  me1.set_display(false);

//  document = me1.to_XML();

//  me2.from_XML(*document);

//  delete document;

//  assert_true(me2.get_Minkowski_parameter() == 1.33, LOG);

}


void MinkowskiErrorTest::run_test_case()
{
   cout << "Running Minkowski error test case...\n";  

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Get methods

   test_get_Minkowski_parameter();

   // Set methods

   test_set_Minkowski_parameter();

   // Error methods

   test_calculate_error();
   test_calculate_selection_error();
   test_calculate_error_gradient();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   cout << "End of Minkowski error test case.\n\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2021 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
