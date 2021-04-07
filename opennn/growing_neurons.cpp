//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   G R O W I N G   N E U R O N S   C L A S S
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "growing_neurons.h"

namespace OpenNN
{

/// Default constructor.

GrowingNeurons::GrowingNeurons()
    : NeuronsSelection()
{
    set_default();
}


/// Training strategy constructor.
/// @param new_training_strategy_pointer Pointer to a gradient descent object.

GrowingNeurons::GrowingNeurons(TrainingStrategy* new_training_strategy_pointer)
    : NeuronsSelection(new_training_strategy_pointer)
{
    set_default();
}


/// Destructor.

GrowingNeurons::~GrowingNeurons()
{
}


/// Returns the number of the hidden perceptrons pointed in each iteration of the growing neurons algorithm.

const Index& GrowingNeurons::get_step() const
{
    return neurons_increment;
}


/// Returns the maximum number of selection failures in the model order selection algorithm.

const Index& GrowingNeurons::get_maximum_selection_failures() const
{
    return maximum_selection_failures;
}


/// Sets the members of the model selection object to their default values:

void GrowingNeurons::set_default()
{
    minimum_neurons = 1;

    maximum_neurons = 10;

    trials_number = 3;

    neurons_increment = 1;

    maximum_selection_failures = 100;

    maximum_time = 3600;
}


/// Sets the number of the hidden perceptrons pointed in each iteration of the growing algorithm
/// in the model order selection process.
/// @param new_step number of hidden perceptrons pointed.

void GrowingNeurons::set_step(const Index& new_step)
{
#ifdef OPENNN_DEBUG

    if(new_step <= 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: GrowingNeurons class.\n"
               << "void set_step(const Index&) method.\n"
               << "New_step(" << new_step << ") must be greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    neurons_increment = new_step;
}


/// Sets the maximum selection failures for the growing order selection algorithm.
/// @param new_maximum_selection_failures Maximum number of selection failures in the growing neurons selection algorithm.

void GrowingNeurons::set_maximum_selection_failures(const Index& new_maximum_selection_failures)
{
#ifdef OPENNN_DEBUG

    if(new_maximum_selection_failures <= 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: GrowingNeurons class.\n"
               << "void set_maximum_selection_failures(const Index&) method.\n"
               << "Maximum selection failures must be greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    maximum_selection_failures = new_maximum_selection_failures;
}


/// Perform neurons selection with the growing neurons method.

NeuronsSelectionResults GrowingNeurons::perform_neurons_selection()
{
    #ifdef OPENNN_DEBUG

    if(!training_strategy_pointer)
    {
         ostringstream buffer;

         buffer << "OpenNN Exception: growing_neurons class.\n"
                << "TrainingStrategy* training_strategy_pointer const method.\n"
                << "training_strategy_pointer is nullptr.\n";

         throw logic_error(buffer.str());
    }

    #endif

    NeuronsSelectionResults results(maximum_epochs_number);

    if(display)
    {
        cout << "Performing growing neurons selection..." << endl;
        cout.flush();
    }

    // Neural network    

    NeuralNetwork* neural_network = training_strategy_pointer->get_neural_network_pointer();

    const Index trainable_layers_number = neural_network->get_trainable_layers_number();

    const Tensor<Layer*, 1> trainable_layers_pointers = neural_network->get_trainable_layers_pointers();

    Index neurons_number;

    // Loss index

    type previous_selection_error = numeric_limits<type>::max();

    // Optimization algorithm

    Index selection_failures = 0;

    bool end = false;

    time_t beginning_time, current_time;

    type elapsed_time = 0;

    TrainingResults training_results;

    training_strategy_pointer->set_display(false);

    time(&beginning_time);

    // Main loop

    for(Index epoch = 0; epoch < maximum_epochs_number; epoch++)
    {               
        // Neural network

        neurons_number = minimum_neurons + epoch*neurons_increment;

        trainable_layers_pointers(trainable_layers_number-2)->set_neurons_number(neurons_number);

        trainable_layers_pointers(trainable_layers_number-1)->set_inputs_number(neurons_number);

        results.neurons_numbers(epoch) = neurons_number;

        // Loss index

        if(display)
        {
            cout << endl
                 << "Epoch: " << epoch+1 << endl;
            cout << "Neurons number: " << neurons_number << endl;
        }

        for(Index trial = 0; trial < trials_number; trial++)
        {
            neural_network->set_parameters_random();

            training_results = training_strategy_pointer->perform_training();

            if(display)
            {
                cout << "Trial: " << trial+1 << endl;
                cout << "Training error: " << training_results.training_error << endl;
                cout << "Selection error: " << training_results.selection_error << endl;
            }

            if(training_results.selection_error < results.optimum_selection_error)
            {
                results.optimal_neurons_number = neurons_number;
                results.optimal_parameters = training_results.parameters;

                results.optimum_training_error = training_results.training_error;
                results.optimum_selection_error = training_results.selection_error;
            }
        }

        if(results.optimum_selection_error > previous_selection_error)
        {
            selection_failures++;
        }

        previous_selection_error = results.optimum_selection_error;

        time(&current_time);

        elapsed_time = static_cast<type>(difftime(current_time, beginning_time));

        if(reserve_training_errors) results.training_errors(epoch) = training_results.training_error;

        if(reserve_selection_errors) results.selection_errors(epoch) = training_results.selection_error;

        // Stopping criteria

        if(elapsed_time >= maximum_time)
        {
            end = true;

            if(display) cout << "Maximum time reached." << endl;

            results.stopping_condition = GrowingNeurons::MaximumTime;
        }
        else if(training_results.selection_error <= selection_error_goal)
        {
            end = true;

            if(display) cout << "Selection error goal reached." << endl;

            results.stopping_condition = GrowingNeurons::SelectionErrorGoal;
        }
        else if(epoch >= maximum_epochs_number)
        {
            end = true;

            if(display) cout << "Maximum number of epochs reached." << endl;

            results.stopping_condition = GrowingNeurons::MaximumEpochs;
        }
        else if(selection_failures >= maximum_selection_failures)
        {
            end = true;

            if(display) cout << "Maximum selection failures (" << selection_failures << ") reached." << endl;

            results.stopping_condition = GrowingNeurons::MaximumSelectionFailures;
        }
        else if(neurons_number >= maximum_neurons)
        {
            end = true;

            if(display) cout << "Maximum number of neurons reached." << endl;

            results.stopping_condition = GrowingNeurons::MaximumNeurons;
        }

        if(display)
        {            
/*
            cout << "Epoch: " << epoch << endl
                 << "Neurons number: " << neurons_number << endl
                 << "Training error: " << training_results.selection_error << endl
                 << "Selection error: " << training_results.selection_error << endl;
*/
            cout << "Elapsed time: " << write_elapsed_time(elapsed_time) << endl;
        }

        if(end)
        {
            results.epochs_number = epoch;
            results.elapsed_time = write_elapsed_time(elapsed_time);

            break;
        }
    }

    if(display)
    {
        cout << endl;
        cout << "Optimal neurons number: " << results.optimal_neurons_number << endl;
        cout << "Optimum training error: " << results.optimum_training_error << endl;
        cout << "Optimum selection error: " << results.optimum_selection_error << endl;
    }

    // Save neural network

    trainable_layers_pointers[trainable_layers_number-1]->set_inputs_number(results.optimal_neurons_number);
    trainable_layers_pointers[trainable_layers_number-2]->set_neurons_number(results.optimal_neurons_number);

    neural_network->set_parameters(results.optimal_parameters);

    return results;
}


/// Writes as matrix of strings the most representative atributes.

Tensor<string, 2> GrowingNeurons::to_string_matrix() const
{
    ostringstream buffer;

    Tensor<string, 1> labels(10);
    Tensor<string, 1> values(10);

    // Minimum neurons number

    labels(0) = "Minimum neurons";

    buffer.str("");
    buffer << minimum_neurons;

    values(0) = buffer.str();

    // Maximum order

    labels(1) = "Maximum neurons";

    buffer.str("");
    buffer << maximum_neurons;

    values(1) = buffer.str();

    // Step

    labels(2) = "Step";

    buffer.str("");
    buffer << neurons_increment;

    values(2) = buffer.str();

    // Trials number

    labels(3) = "Trials number";

    buffer.str("");
    buffer << trials_number;

    values(3) = buffer.str();

    // Selection loss goal

    labels(4) = "Selection loss goal";

    buffer.str("");
    buffer << selection_error_goal;

    values(4) = buffer.str();

    // Maximum selection failures

    labels(5) = "Maximum selection failures";

    buffer.str("");
    buffer << maximum_selection_failures;

    values(5) = buffer.str();

    // Maximum iterations number

    labels(6) = "Maximum iterations number";

    buffer.str("");
    buffer << maximum_epochs_number;

    values(6) = buffer.str();

    // Maximum time

    labels(7) = "Maximum time";

    buffer.str("");
    buffer << maximum_time;

    values(7) = buffer.str();

    // Plot training error history

    labels(8) = "Plot training error history";

    buffer.str("");

    reserve_training_errors ? buffer << "true" : buffer << "false";

    values(8) = buffer.str();

    // Plot selection error history

    labels(9) = "Plot selection error history";

    buffer.str("");

    if(reserve_selection_errors)
    {
        buffer << "true";
    }
    else
    {
        buffer << "false";
    }

    values(9) = buffer.str();

    const Index rows_number = labels.size();
    const Index columns_number = 2;

    Tensor<string, 2> string_matrix(rows_number, columns_number);

    string_matrix.chip(0, 1) = labels;
    string_matrix.chip(1, 1) = values;

    return string_matrix;
}


/// Serializes the growing neurons object into a XML document of the TinyXML library without
/// keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document.

void GrowingNeurons::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    ostringstream buffer;

    file_stream.OpenElement("GrowingNeurons");

    // Minimum order

    file_stream.OpenElement("MinimumNeurons");

    buffer.str("");
    buffer << minimum_neurons;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum order

    file_stream.OpenElement("MaximumNeurons");

    buffer.str("");
    buffer << maximum_neurons;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Step

    file_stream.OpenElement("Step");

    buffer.str("");
    buffer << neurons_increment;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Trials number

    file_stream.OpenElement("TrialsNumber");

    buffer.str("");
    buffer << trials_number;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Selection error goal

    file_stream.OpenElement("SelectionErrorGoal");

    buffer.str("");
    buffer << selection_error_goal;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum selection failures

    file_stream.OpenElement("MaximumSelectionFailures");

    buffer.str("");
    buffer << maximum_selection_failures;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum time

    file_stream.OpenElement("MaximumTime");

    buffer.str("");
    buffer << maximum_time;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve training erro history

    file_stream.OpenElement("ReserveTrainingErrorHistory");

    buffer.str("");
    buffer << reserve_training_errors;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve selection error data

    file_stream.OpenElement("ReserveSelectionErrorHistory");

    buffer.str("");
    buffer << reserve_selection_errors;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    file_stream.CloseElement();
}


/// Deserializes a TinyXML document into this growing neurons object.
/// @param document TinyXML document containing the member data.

void GrowingNeurons::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("GrowingNeurons");

    if(!root_element)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: GrowingNeurons class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "GrowingNeurons element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Minimum neurons
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("MinimumNeurons");

        if(element)
        {
            const Index new_minimum_neurons = static_cast<Index>(atoi(element->GetText()));

            try
            {
                minimum_neurons = new_minimum_neurons;
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Maximum neurons
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumNeurons");

        if(element)
        {
            const Index new_maximum_neurons = static_cast<Index>(atoi(element->GetText()));

            try
            {
                maximum_neurons = new_maximum_neurons;
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Step
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("Step");

        if(element)
        {
            const Index new_step = static_cast<Index>(atoi(element->GetText()));

            try
            {
                set_step(new_step);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Trials number
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("TrialsNumber");

        if(element)
        {
            const Index new_trials_number = static_cast<Index>(atoi(element->GetText()));

            try
            {
                set_trials_number(new_trials_number);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Selection error goal
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("SelectionErrorGoal");

        if(element)
        {
            const type new_selection_error_goal = static_cast<type>(atof(element->GetText()));

            try
            {
                set_selection_error_goal(new_selection_error_goal);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Maximum selection failures
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumSelectionFailures");

        if(element)
        {
            const Index new_maximum_selection_failures = static_cast<Index>(atoi(element->GetText()));

            try
            {
                set_maximum_selection_failures(new_maximum_selection_failures);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Maximum time
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumTime");

        if(element)
        {
            const type new_maximum_time = atoi(element->GetText());

            try
            {
                set_maximum_time(new_maximum_time);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }


    // Reserve training error history
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("ReserveTrainingErrorHistory");

        if(element)
        {
            const string new_reserve_training_error_data = element->GetText();

            try
            {
                set_reserve_training_error_data(new_reserve_training_error_data != "0");
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Reserve selection error history
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("ReserveSelectionErrorHistory");

        if(element)
        {
            const string new_reserve_selection_error_data = element->GetText();

            try
            {
                set_reserve_selection_error_data(new_reserve_selection_error_data != "0");
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }
}


/// Saves to a XML-type file the members of the growing neurons object.
/// @param file_name Name of growing neurons XML-type file.

void GrowingNeurons::save(const string& file_name) const
{
    FILE * file = fopen(file_name.c_str(), "w");

    tinyxml2::XMLPrinter printer(file);

    write_XML(printer);

    fclose(file);
}


/// Loads a growing neurons object from a XML-type file.
/// @param file_name Name of growing neurons XML-type file.

void GrowingNeurons::load(const string& file_name)
{
    set_default();

    tinyxml2::XMLDocument document;

    if(document.LoadFile(file_name.c_str()))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: GrowingNeurons class.\n"
               << "void load(const string&) method.\n"
               << "Cannot load XML file " << file_name << ".\n";

        throw logic_error(buffer.str());
    }

    from_XML(document);
}

}

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2021 Artificial Intelligence Techniques, SL.
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
