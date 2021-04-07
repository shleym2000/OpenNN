//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   S I M P L E   F U N C T I O N   R E G R E S S I O N   A P P L I C A T I O N
//
//   Artificial Intelligence Techniques SL (Artelnics)
//   artelnics@artelnics.com

// System includes

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

// OpenNN includes

#include "../../opennn/opennn.h"

using namespace OpenNN;
using namespace std;
using namespace Eigen;

int main()
{
    try
    {
        cout << "OpenNN. Simple Function Regression Example." << endl;

        srand(static_cast<unsigned>(time(nullptr)));

        // Data set

        DataSet data_set("../data/simple_function_regression.csv", ';', true);

        const Tensor<Descriptives, 1> input_variables_descriptives = data_set.scale_input_variables(DataSet::MinimumMaximum);

        const Tensor<Descriptives, 1> targets_descriptives = data_set.scale_target_variables(DataSet::MinimumMaximum);

        // Neural network

        NeuralNetwork neural_network(NeuralNetwork::Approximation, {1, 3, 1});

        // Training strategy

        TrainingStrategy training_strategy(&neural_network, &data_set);

        training_strategy.set_loss_method(TrainingStrategy::MEAN_SQUARED_ERROR);

        training_strategy.set_optimization_method(TrainingStrategy::ADAPTIVE_MOMENT_ESTIMATION);

        training_strategy.get_loss_index_pointer()->set_regularization_method("NO_REGULARIZATION");

        training_strategy.get_adaptive_moment_estimation_pointer()->set_display_period(100);

        training_strategy.perform_training();

        data_set.unscale_input_variables_minimum_maximum(input_variables_descriptives);

        data_set.unscale_target_variables(DataSet::MinimumMaximum, targets_descriptives);

        neural_network.save_expression_python("simple_function_regresion.py");

        cout << "Bye Simple Function Regression" << endl;

        return 0;
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;

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
