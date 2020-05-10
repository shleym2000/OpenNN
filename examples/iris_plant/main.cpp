//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   I R I S   P L A N T   A P P L I C A T I O N
//
//   Artificial Intelligence Techniques SL (Artelnics)
//   artelnics@artelnics.com

// This is a classical pattern recognition problem.

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

// OpenNN includes

#include "../../opennn/opennn.h"

using namespace OpenNN;

int main(void)
{
    try
    {
        cout << "OpenNN. Iris Plant Example." << endl;

        srand(static_cast<unsigned>(time(nullptr)));

        // Device

        

        // Data set

        DataSet data_set("../data/iris_plant_original.csv", ';', true);
        data_set.set_thread_pool_device(thread_pool_device);

        Tensor<string, 1> uses(5);
        uses.setValues({"Input","Input","Input","Input","Target"});
        data_set.set_columns_uses(uses);

        const Tensor<string, 1> inputs_names = data_set.get_input_variables_names();
        const Tensor<string, 1> targets_names = data_set.get_target_variables_names();

        const Tensor<string, 1> input_columns_names = data_set.get_input_columns_names();
        const Tensor<string, 1> target_columns_names = data_set.get_target_columns_names();

        data_set.split_instances_random();

        const Tensor<Descriptives, 1> inputs_descriptives = data_set.scale_inputs_minimum_maximum();

        // Neural network

        Tensor<Index, 1> architecture(3);
        architecture.setValues({4, 6, 3});

        NeuralNetwork neural_network(NeuralNetwork::Classification, architecture);
        neural_network.set_thread_pool_device(thread_pool_device);

        neural_network.set_inputs_names(inputs_names);

        neural_network.set_outputs_names(targets_names);

        ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

        scaling_layer_pointer->set_descriptives(inputs_descriptives);

        scaling_layer_pointer->set_scaling_methods(ScalingLayer::MinimumMaximum);

        // Training strategy

        TrainingStrategy training_strategy(&neural_network, &data_set);
        training_strategy.set_thread_pool_device(thread_pool_device);

        training_strategy.set_loss_method(TrainingStrategy::NORMALIZED_SQUARED_ERROR);
        training_strategy.set_optimization_method(TrainingStrategy::STOCHASTIC_GRADIENT_DESCENT);

//        QuasiNewtonMethod* quasi_Newton_method_pointer = training_strategy.get_quasi_Newton_method_pointer();

//        quasi_Newton_method_pointer->set_minimum_loss_decrease(1.0e-6);

//        quasi_Newton_method_pointer->set_loss_goal(1.0e-3);

//        quasi_Newton_method_pointer->set_minimum_parameters_increment_norm(0.0);

        training_strategy.perform_training();

        training_strategy.set_display(false);

        // Testing analysis

//        data_set.unscale_inputs_minimum_maximum(inputs_descriptives);

        TestingAnalysis testing_analysis(&neural_network, &data_set);

        const Tensor<Index, 2> confusion = testing_analysis.calculate_confusion();

        cout << "Confusion: " << endl;
        cout << confusion << endl;

        // Save results

        data_set.save("../data/data_set.xml");

        neural_network.save("../data/neural_network.xml");
        neural_network.save_expression("../data/expression.txt");

        training_strategy.save("../data/training_strategy.xml");

//        confusion.save_csv("../data/confusion.csv");

        cout << "Bye" << endl;

        return 0;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;

        return 1;
    }
}  


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2019 Artificial Intelligence Techniques SL
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
