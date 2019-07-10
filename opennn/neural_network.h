/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   N E U R A L   N E T W O R K   C L A S S   H E A D E R                                                      */
/*                                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   artelnics@artelnics.com                                                                                    */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __NEURALNETWORK_H__
#define __NEURALNETWORK_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <errno.h>

#ifdef __OPENNN_MPI__
#include <mpi.h>
#endif

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "data_set.h"

#include "perceptron_layer.h"
#include "multilayer_perceptron.h"
#include "inputs_trending_layer.h"
#include "scaling_layer.h"
#include "principal_components_layer.h"
#include "unscaling_layer.h"
#include "outputs_trending_layer.h"
#include "bounding_layer.h"
#include "probabilistic_layer.h"
#include "inputs.h"
#include "outputs.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the concept of neural network in the OpenNN library.
/// A neural network here is defined as a multilayer perceptron extended with a scaling layer, an unscaling layer, 
/// a bounding layer and a probabilistic layer.
/// This neural network is used to span a function space for the variational problem at hand. 

class NeuralNetwork
{

public:

   // DEFAULT CONSTRUCTOR

   explicit NeuralNetwork();

   // MULTILAYER PERCEPTRON CONSTRUCTOR

   explicit NeuralNetwork(const MultilayerPerceptron& new_multilayer_perceptron);

   // MULTILAYER PERCEPTRON ARCHITECTURE CONSTRUCTOR

   explicit NeuralNetwork(const Vector<size_t>& new_multilayer_perceptron_architecture);

   explicit NeuralNetwork(const vector<size_t>& new_multilayer_perceptron_architecture);


    // ONE PERCEPTRON LAYER CONSTRUCTOR

   explicit NeuralNetwork(const size_t& new_inputs_number, const size_t& new_outputs_number);

   // TWO PERCEPTRON LAYERS CONSTRUCTOR

   explicit NeuralNetwork(const size_t& new_inputs_number, const size_t& new_hidden_perceptrons_number, const size_t& new_outputs_number);

   // FILE CONSTRUCTOR

   explicit NeuralNetwork(const string& file_name);

   // XML CONSTRUCTOR

   explicit NeuralNetwork(const tinyxml2::XMLDocument& document);

   // COPY CONSTRUCTOR

   NeuralNetwork(const NeuralNetwork& other_neural_network);

   // DESTRUCTOR

   virtual ~NeuralNetwork();

   // ASSIGNMENT OPERATOR

   NeuralNetwork& operator = (const NeuralNetwork& other_neural_network);

   // EQUAL TO OPERATOR

   bool operator == (const NeuralNetwork& other_neural_network) const;


   // GET METHODS

   bool has_multilayer_perceptron() const;
   bool has_inputs() const;
   bool has_outputs() const;
   bool has_inputs_trending_layer() const;
   bool has_scaling_layer() const;
   bool has_principal_components_layer() const;
   bool has_unscaling_layer() const;
   bool has_outputs_trending_layer() const;
   bool has_bounding_layer() const;
   bool has_probabilistic_layer() const;

   MultilayerPerceptron* get_multilayer_perceptron_pointer() const;
   Inputs* get_inputs_pointer() const;
   Outputs* get_outputs_pointer() const;
   InputsTrendingLayer* get_inputs_trending_layer_pointer() const;
   ScalingLayer* get_scaling_layer_pointer() const;
   PrincipalComponentsLayer* get_principal_components_layer_pointer() const;
   UnscalingLayer* get_unscaling_layer_pointer() const;   
   OutputsTrendingLayer* get_outputs_trending_layer_pointer() const;
   BoundingLayer* get_bounding_layer_pointer() const;
   ProbabilisticLayer* get_probabilistic_layer_pointer() const;

   const bool& get_display() const;

   // SET METHODS

   void set();

   void set(const MultilayerPerceptron& new_multilayer_perceptron);
   void set(const Vector<size_t>& new_multilayer_perceptron_architecture);
   void set(const size_t& new_inputs_number, const size_t& new_outputs_number);
   void set(const size_t& new_inputs_number, const size_t& new_hidden_neurons_number, const size_t& new_outputs_number);

   void set(const size_t&);

   void set(const string& file_name);
   void set(const NeuralNetwork& other_neural_network);

   void set_inputs(const Vector<bool>& new_uses);

   virtual void set_default();

#ifdef __OPENNN_MPI__
   void set_MPI(const NeuralNetwork* neural_network);
#endif

   void set_multilayer_perceptron_pointer(MultilayerPerceptron*);
   void set_inputs_trending_layer_pointer(InputsTrendingLayer*);
   void set_scaling_layer_pointer(ScalingLayer*);
   void set_principal_components_layer_pointer(PrincipalComponentsLayer*);
   void set_unscaling_layer_pointer(UnscalingLayer*);
   void set_outputs_trending_layer_pointer(OutputsTrendingLayer*);
   void set_bounding_layer_pointer(BoundingLayer*);
   void set_probabilistic_layer_pointer(ProbabilisticLayer*);
   void set_inputs_pointer(Inputs*);
   void set_outputs_pointer(Outputs*);

   void set_scaling_layer(ScalingLayer&);

   void set_display(const bool&);

   // Growing and pruning

   void grow_input(const Statistics<double>& new_statistics = Statistics<double>());

   void prune_input(const size_t& index);
   void prune_output(const size_t& index);

   void resize_inputs_number(const size_t&);
   void resize_outputs_number(const size_t&);

   // Pointer methods

   void construct_multilayer_perceptron();
   void construct_inputs_trending_layer();
   void construct_scaling_layer();
   void construct_scaling_layer(const Vector< Statistics<double> >& input_statistics);
   void construct_scaling_layer(const Eigen::MatrixXd& input_statistics);
   void construct_principal_components_layer();
   void construct_unscaling_layer();
   void construct_unscaling_layer(const Vector< Statistics<double> >& target_statistics);
   void construct_unscaling_layer(const Eigen::MatrixXd& target_statistics);
   void construct_outputs_trending_layer();
   void construct_bounding_layer();
   void construct_probabilistic_layer();
   void construct_inputs();
   void construct_outputs();

   void destruct_multilayer_perceptron();
   void destruct_inputs_trending_layer();
   void destruct_scaling_layer();
   void destruct_unscaling_layer();
   void destruct_outputs_trending_layer();
   void destruct_bounding_layer();
   void destruct_probabilistic_layer();
   void destruct_inputs();
   void destruct_outputs();

   void delete_pointers();

   // Initialization methods

   void initialize_random();

   // Layers 

   size_t get_layers_number() const;

   // Architecture

   size_t get_inputs_number() const;
   size_t get_outputs_number() const;

   Vector<size_t> get_architecture() const;

   // Parameters

   size_t get_parameters_number() const;
   Vector<double> get_parameters() const;

   void set_parameters(const Vector<double>& new_parameters);

   // Parameters initialization methods

   void initialize_parameters(const double& value);

   void randomize_parameters_uniform();
   void randomize_parameters_uniform(const double& minimum, const double& maximum);
   void randomize_parameters_uniform(const Vector<double>& minimum, const Vector<double>& maximum);
   void randomize_parameters_uniform(const Vector< Vector<double> >& minimum_maximum);

   void randomize_parameters_normal();
   void randomize_parameters_normal(const double& mean, const double& standard_deviation);
   void randomize_parameters_normal(const Vector<double>& mean, const Vector<double>& standard_deviation);
   void randomize_parameters_normal(const Vector< Vector<double> >& mean_standard_deviation);

   // Parameters

   double calculate_parameters_norm() const;
   Statistics<double> calculate_parameters_statistics() const;
   Histogram<double> calculate_parameters_histogram(const size_t& bins_number = 10) const;

   void perturbate_parameters(const double&);

   // Feature importance

   Vector<double> calculate_inputs_importance_parameters(const size_t& output_index) const;

   // Output 

   Matrix<double> calculate_outputs(const Matrix<double>& inputs) const;
   Matrix<double> calculate_outputs(const Matrix<double>& inputs, const double& time) const;
   Eigen::MatrixXd calculate_outputs_eigen(const Eigen::MatrixXd& inputs) const;
   Vector< Matrix<double> > calculate_Jacobian(const Matrix<double>& inputs) const;
   Matrix<double> calculate_Jacobian(const Vector<double>& inputs, const double& time) const;
   Vector< Matrix<double> > calculate_Hessian(const Vector<double>& inputs) const;

   Matrix<double> calculate_directional_inputs(const size_t& direction, const Vector<double>& point, const double& minimum, const double& maximum, const size_t& points_number = 101) const;

   Vector< Matrix<double> > calculate_Jacobian_data(const Matrix<double>& inputs) const;

   Vector< Histogram<double> > calculate_outputs_histograms(const size_t& points_number = 1000, const size_t& bins_number = 10) const;
   Vector< Histogram<double> > calculate_outputs_histograms(const Matrix<double>& inputs, const size_t& bins_number = 10) const;


   vector<double> calculate_outputs_std(const vector<double>& inputs) const;

   // Serialization methods

   string object_to_string() const;
 
   virtual tinyxml2::XMLDocument* to_XML() const;
   virtual void from_XML(const tinyxml2::XMLDocument& document);

   virtual void write_XML(tinyxml2::XMLPrinter&) const;
   // virtual void read_XML(   );

   void print() const;
   void save(const string& file_name) const;
   void save_parameters(const string& file_name) const;

   virtual void load(const string& file_name);
   void load_parameters(const string& file_name);

   void save_data(const string& file_name) const;

   // Expression methods

   string write_expression() const;
   string write_mathematical_expression_php() const;
   string write_expression_python() const;
   string write_expression_php() const;
   string write_expression_R() const;

   void save_expression(const string& file_name);
   void save_expression_python(const string& file_name);
   void save_expression_R(const string& file_name);

   // PMML methods

   tinyxml2::XMLDocument* to_PMML() const;
   void write_PMML(const string& file_name) const;

   void from_PMML(const tinyxml2::XMLDocument& document);

protected:

   // MEMBERS

   /// Pointer to a multilayer perceptron object.

   MultilayerPerceptron* multilayer_perceptron_pointer = nullptr;

   /// Pointer to an inputs trending layer object.

   InputsTrendingLayer* inputs_trending_layer_pointer = nullptr;

   /// Pointer to a scaling layer object.

   ScalingLayer* scaling_layer_pointer = nullptr;

   /// Pointer to a principal components layer object.

   PrincipalComponentsLayer* principal_components_layer_pointer = nullptr;

   /// Pointer to an unscaling layer object.

   UnscalingLayer* unscaling_layer_pointer = nullptr;

   /// Pointer to an outputs trending layer object.

   OutputsTrendingLayer* outputs_trending_layer_pointer = nullptr;

   /// Pointer to a bounding layer object.

   BoundingLayer* bounding_layer_pointer = nullptr;

   /// Pointer to a probabilistic layer.

   ProbabilisticLayer* probabilistic_layer_pointer = nullptr;

   /// Pointer to an inputs object.

   Inputs* inputs_pointer = nullptr;

   /// Pointer to an outputs object.

   Outputs* outputs_pointer = nullptr;

   /// Display messages to screen. 

   bool display;
};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2019 Artificial Intelligence Techniques, SL.
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

