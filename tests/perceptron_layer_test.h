//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   P E R C E P T R O N   L A Y E R   T E S T   C L A S S   H E A D E R   
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef PERCEPTRONLAYERTEST_H
#define PERCEPTRONLAYERTEST_H

// Unit testing includes

#include "unit_testing.h"

using namespace OpenNN;


class PerceptronLayerTest : public UnitTesting
{

#define STRING(x) #x
#define TOSTRING(x) STRING(x)
#define LOG __FILE__ ":" TOSTRING(__LINE__)"\n"

public:

   explicit PerceptronLayerTest();

   virtual ~PerceptronLayerTest();

   // Constructor and destructor methods

   void test_constructor();
   void test_destructor();

   // Assignment operators methods

   void test_assignment_operator();

   // Get methods

   // Inputs and perceptrons

   void test_is_empty();
   void test_get_inputs_number();
   void test_get_neurons_number();
   void test_get_perceptrons();

   // Parameters

   void test_get_biases();
   void test_get_synaptic_weights();
   void test_get_parameters_number();
   void test_get_parameters();

   // Activation functions

   void test_get_activation_function();
   void test_write_activation_function();
   
   // Display messages

   void test_get_display();

   // Set methods

   void test_set();
   void test_set_default();

   // Parameters

   void test_set_biases();
   void test_set_synaptic_weights();
   void test_set_parameters();

   // Inputs

   void test_set_inputs_number();

   //Perceptrons

   void test_set_perceptrons_number();

   // Activation functions

   void test_set_activation_function();

   // Display messages

   void test_set_display();

   // Parameters initialization methods

   void test_set_parameters_constant();
   void test_set_synaptic_weights_constant();
   void test_set_parameters_random();

   // Combination

   void test_calculate_combinations();

   // Activation

   void test_calculate_activations();
   void test_calculate_activations_derivatives();

   // Outputs

   void test_calculate_outputs();

   // Forward propagate

   void test_forward_propagate();

   // Hidden delta

   void test_calculate_hidden_delta();
   void test_calculate_output_delta();

   // Gradient

   void test_calculate_error_gradient();

   // Expression methods

   void test_write_expression();

   // Unit testing methods

   void run_test_case();
};


#endif


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2020 Artificial Intelligence Techniques, SL.
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
