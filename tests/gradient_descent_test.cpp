//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   G R A D I E N T   D E S C E N T   T E S T   C L A S S                 
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "gradient_descent_test.h"


GradientDescentTest::GradientDescentTest() : UnitTesting()
{
}


GradientDescentTest::~GradientDescentTest()
{
}


void GradientDescentTest::test_constructor() // @todo
{
   cout << "test_constructor\n"; 

//   SumSquaredError sum_squared_error;

//   // Default constructor

//   GradientDescent gd1;
//   assert_true(gd1.has_loss_index() == false, LOG);

//   // Loss index constructor

//   GradientDescent gd2(&sum_squared_error);
//   assert_true(gd2.has_loss_index() == true, LOG);
}


void GradientDescentTest::test_destructor() // @todo
{
   cout << "test_destructor\n"; 
}


void GradientDescentTest::test_set_reserve_all_training_history() // @todo
{
   cout << "test_set_reserve_all_training_history\n";

//   GradientDescent gd;

//   gd.set_reserve_all_training_history(true);

//   assert_true(gd.get_reserve_training_error_history() == true, LOG);
//   assert_true(gd.get_reserve_selection_error_history() == true, LOG);
}


void GradientDescentTest::test_perform_training() // @todo
{
   cout << "test_perform_training\n";

//   DataSet data_set(1, 1, 2);
//   data_set.set_data_random();

//   NeuralNetwork neural_network(NeuralNetwork::Approximation, {1, 2});
//   neural_network.set_parameters_random();

//   SumSquaredError sum_squared_error(&neural_network, &data_set);

//   GradientDescent gd(&sum_squared_error);

//   // Test

//   //type old_loss = sum_squared_error.calculate_error({0});

//   gd.set_display(false);
//   gd.set_maximum_epochs_number(1);

//   gd.perform_training();

//   //type loss = sum_squared_error.calculate_error({0});

//   //assert_true(loss < old_loss, LOG);

//   // Minimum parameters increment norm

//   neural_network.set_parameters_constant(-1.0);

//   type minimum_parameters_increment_norm = 0.1;

//   gd.set_minimum_parameters_increment_norm(minimum_parameters_increment_norm);
//   gd.set_loss_goal(0.0);
//   gd.set_minimum_loss_decrease(0.0);
//   gd.set_gradient_norm_goal(0.0);
//   gd.set_maximum_epochs_number(1000);
//   gd.set_maximum_time(1000.0);

//   gd.perform_training();

//   // Performance goal

//   neural_network.set_parameters_constant(-1.0);

//   type training_loss_goal = 0.1;

//   gd.set_minimum_parameters_increment_norm(0.0);
//   gd.set_loss_goal(training_loss_goal);
//   gd.set_minimum_loss_decrease(0.0);
//   gd.set_gradient_norm_goal(0.0);
//   gd.set_maximum_epochs_number(1000);
//   gd.set_maximum_time(1000.0);

//   gd.perform_training();

//   //loss = sum_squared_error.calculate_error({0});

//   // Minimum loss increase

//   neural_network.set_parameters_constant(-1.0);

//   type minimum_loss_decrease = 0.1;

//   gd.set_minimum_parameters_increment_norm(0.0);
//   gd.set_loss_goal(0.0);
//   gd.set_minimum_loss_decrease(minimum_loss_decrease);
//   gd.set_gradient_norm_goal(0.0);
//   gd.set_maximum_epochs_number(1000);
//   gd.set_maximum_time(1000.0);

//   gd.perform_training();

//   // Gradient norm goal

//   neural_network.set_parameters_constant(-1.0);

//   type gradient_norm_goal = 0.1;

//   gd.set_minimum_parameters_increment_norm(0.0);
//   gd.set_loss_goal(0.0);
//   gd.set_minimum_loss_decrease(0.0);
//   gd.set_gradient_norm_goal(gradient_norm_goal);
//   gd.set_maximum_epochs_number(1000);
//   gd.set_maximum_time(1000.0);

//   gd.perform_training();

//   type gradient_norm = sum_squared_error.calculate_error_gradient({0}).l2_norm();
//   assert_true(gradient_norm < gradient_norm_goal, LOG);

}


void GradientDescentTest::test_resize_training_history() // @todo
{
   cout << "test_resize_training_history\n";

//   GradientDescent gd;

//   gd.set_reserve_all_training_history(true);

//   OptimizationAlgorithm::Results gdtr;//(&gd);

//   gdtr.resize_training_history(1);

//   assert_true(gdtr.training_error_history.size() == 1, LOG);
//   assert_true(gdtr.selection_error_history.size() == 1, LOG);
}


/// @todo

void GradientDescentTest::test_to_XML() // @todo
{
   cout << "test_to_XML\n";

//   GradientDescent gd;

//   tinyxml2::XMLDocument* document;

//   // Test

//   document = gd.to_XML();
//   assert_true(document != nullptr, LOG);

//   delete document;

}


void GradientDescentTest::test_from_XML() // @todo
{
   cout << "test_from_XML\n";
}


void GradientDescentTest::run_test_case() // @todo
{
   cout << "Running gradient descent test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

//   // Set methods

   test_set_reserve_all_training_history();

   // Training methods

   test_perform_training();

   // Training history methods

   test_resize_training_history();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   cout << "End of gradient descent test case.\n\n";
}


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

