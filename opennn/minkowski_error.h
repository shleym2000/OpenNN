//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   M I N K O W S K I   E R R O R   C L A S S   H E A D E R               
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef MINKOWSKIERROR_H
#define MINKOWSKIERROR_H

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

// OpenNN includes

#include "loss_index.h"
#include "data_set.h"
#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the Minkowski error term. 

///
/// The Minkowski error measures the difference between the outputs of a neural network and the targets in a data set. 
/// This error term is used in data modeling problems.
/// It can be more useful when the data set presents outliers. 

class MinkowskiError : public LossIndex
{

public:

   // Constructors

   explicit MinkowskiError();

   explicit MinkowskiError(NeuralNetwork*);

   explicit MinkowskiError(DataSet*);

   explicit MinkowskiError(NeuralNetwork*, DataSet*);

   explicit MinkowskiError(const tinyxml2::XMLDocument&);

   // Destructor

   virtual ~MinkowskiError();

   // Get methods

   double get_Minkowski_parameter() const;

   // Set methods

   void set_default();

   void set_Minkowski_parameter(const double&);

   // loss methods

   double calculate_training_error() const;
   double calculate_training_error(const Vector<double>&) const;

   double calculate_selection_error() const;

   double calculate_batch_error(const Vector<size_t>&) const;
   double calculate_batch_error(const Vector<size_t>&, const Vector<double>&) const;

   /// @todo Virtual method not implemented.

   FirstOrderLoss calculate_first_order_loss(const DataSet::Batch&) const {return FirstOrderLoss();}

   void calculate_first_order_loss(const DataSet::Batch&, const NeuralNetwork::ForwardPropagation&, FirstOrderLoss&) const
   {

   }

   Tensor<double> calculate_output_gradient(const Tensor<double>&, const Tensor<double>&) const;

   void calculate_output_gradient(const DataSet::Batch& batch,
                                  const NeuralNetwork::ForwardPropagation& forward_propagation,
                                  FirstOrderLoss& first_order_loss) const
   {
        #ifdef __OPENNN_DEBUG__

        check();

        #endif

        const size_t training_instances_number = data_set_pointer->get_training_instances_number();

        const size_t trainable_layers_number = neural_network_pointer->get_trainable_layers_number();

        first_order_loss.output_gradient = lp_norm_gradient(forward_propagation.layers[trainable_layers_number].activations - batch.targets, minkowski_parameter)/static_cast<double>(training_instances_number);
   }


   string get_error_type() const;
   string get_error_type_text() const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML() const;   
   void from_XML(const tinyxml2::XMLDocument&);   

   void write_XML(tinyxml2::XMLPrinter&) const;

private:

   /// Minkowski exponent value.

   double minkowski_parameter;

};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
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
