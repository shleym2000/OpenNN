//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   L O G I C A L   O P E R A T O R S   A P P L I C A T I O N
//
//   Artificial Intelligence Techniques SL (Artelnics)
//   artelnics@artelnics.com

// This is a classical learning problem.

// System includes

#include <iostream>
#include <math.h>
#include <time.h>

// OpenNN includes

#include "../../opennn/opennn.h"

#include <../eigen/unsupported/Eigen/CXX11/Tensor>

#include <../../eigen/unsupported/Eigen/CXX11/ThreadPool>


using namespace OpenNN;

int main(void)
{
    try
    {
        cout << "OpenNN. Logical Operations Example." << endl;

        srand(static_cast<unsigned>(time(nullptr)));

        // Device

        const int n = omp_get_max_threads();
        NonBlockingThreadPool* non_blocking_thread_pool = new NonBlockingThreadPool(n);
        ThreadPoolDevice* thread_pool_device = new ThreadPoolDevice(non_blocking_thread_pool, n);

        // Data set

        DataSet data_set("../data/logical_operations.csv", ';', true);
        data_set.set_thread_pool_device(thread_pool_device);

        Tensor<string, 1> uses(8);
        uses.setValues({"Input","Input","Target","Target","Target","Target","Target","Target"});

        data_set.set_columns_uses(uses);

        const Tensor<string, 1> inputs_names = data_set.get_input_variables_names();
        const Tensor<string, 1> targets_names = data_set.get_target_variables_names();

        // Neural network

        Tensor<Index, 1> architecture(3);
        architecture.setValues({2, 6, 6});

        NeuralNetwork neural_network(NeuralNetwork::Classification, architecture);
        neural_network.set_thread_pool_device(thread_pool_device);

        neural_network.set_inputs_names(inputs_names);

        neural_network.set_outputs_names(targets_names);

        // Training strategy

        TrainingStrategy training_strategy(&neural_network, &data_set);
        training_strategy.set_thread_pool_device(thread_pool_device);

        training_strategy.perform_training();

        // Save results

        data_set.save("../data/data_set.xml");

        neural_network.save("../data/neural_network.xml");

        training_strategy.save("../data/training_strategy.xml");

        // Print results to screen

        Tensor<type, 2> inputs(1,2);
        Tensor<type, 2> outputs(1,6);

        cout << "X Y AND OR NAND NOR XOR XNOR" << endl;

        inputs(0,0) = 1.0;
        inputs(0,1) = 1.0;

        outputs = neural_network.calculate_outputs(inputs);

        cout <<"X = 1 Y = 1" << endl << inputs << " " << outputs << endl;

        inputs(0,0) = 1.0;
        inputs(0,1) = 0.0;

        outputs = neural_network.calculate_outputs(inputs);

        cout << "X = 1 Y = 0" << endl << inputs << " " << outputs << endl;

        inputs(0,0) = 0.0;
        inputs(0,1) = 1.0;

        outputs = neural_network.calculate_outputs(inputs);

        cout << "X = 0 Y = 1" << endl << inputs << " " << outputs << endl;

        inputs(0,0) = 0.0;
        inputs(0,1) = 0.0;

        outputs = neural_network.calculate_outputs(inputs);

        cout << "X = 0 Y = 0" << endl << inputs << " " << outputs << endl;

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
