//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   Q U A S I - N E W T O N   M E T H O D    C L A S S   H E A D E R      
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef QUASINEWTONMETHOD_H
#define QUASINEWTONMETHOD_H

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "config.h"
#include "device.h"

#include "loss_index.h"

#include "optimization_algorithm.h"
#include "learning_rate_algorithm.h"

#include "tinyxml2.h"

// Eigen Includes

#include "../eigen/unsupported/Eigen/KroneckerProduct"

using Eigen::MatrixXd;

namespace OpenNN
{

/// Class of optimization algorithm based on Newton's method.
/// An approximate Hessian matrix is computed at each iteration of the algorithm based on the gradients.

/// This concrete class represents a quasi-Newton training algorithm[1], used to minimize loss function.
///
/// \cite 1  Neural Designer "5 Algorithms to Train a Neural Network."
/// \ref https://www.neuraldesigner.com/blog/5_algorithms_to_train_a_neural_network

class QuasiNewtonMethod : public OptimizationAlgorithm
{

public:

    struct OptimizationData
    {
        /// Default constructor.

        explicit OptimizationData()
        {
        }

        explicit OptimizationData(QuasiNewtonMethod* new_quasi_newton_method_pointer)
        {
            set(new_quasi_newton_method_pointer);
        }

        virtual ~OptimizationData() {}

        void set(QuasiNewtonMethod* new_quasi_newton_method_pointer)
        {
            quasi_newton_method_pointer = new_quasi_newton_method_pointer;

            LossIndex* loss_index_pointer = quasi_newton_method_pointer->get_loss_index_pointer();

            NeuralNetwork* neural_network_pointer = loss_index_pointer->get_neural_network_pointer();

            const Index parameters_number = neural_network_pointer->get_parameters_number();

            // Neural network data

            parameters.resize(parameters_number);
            parameters = neural_network_pointer->get_parameters();

            old_parameters.resize(parameters_number);

            parameters_increment.resize(parameters_number);

            // Loss index data

            old_gradient.resize(parameters_number);

            inverse_hessian.resize(parameters_number, parameters_number);
            inverse_hessian.setZero();

            old_inverse_hessian.resize(parameters_number, parameters_number);
            old_inverse_hessian.setZero();

            // Optimization algorithm data

            training_direction.resize(parameters_number);

        }

        void print() const
        {
        }

        QuasiNewtonMethod* quasi_newton_method_pointer = nullptr;

        // Neural network data

        Tensor<type, 1> parameters;
        Tensor<type, 1> old_parameters;

        Tensor<type, 1> parameters_increment;

        // Loss index data

        type old_training_loss = 0;

        Tensor<type, 1> old_gradient;

        Tensor<type, 2> inverse_hessian;
        Tensor<type, 2> old_inverse_hessian;

        // Optimization algorithm data

        Index epoch = 0;

        Tensor<type, 1> training_direction;

        Tensor<type, 0> training_slope;

        type learning_rate = 0;
        type old_learning_rate = 0;
    };


   // Enumerations

   /// Enumeration of the available training operators for obtaining the approximation to the inverse hessian.

   enum InverseHessianApproximationMethod{DFP, BFGS};

   // Constructors

   explicit QuasiNewtonMethod();

   explicit QuasiNewtonMethod(LossIndex*);

   explicit QuasiNewtonMethod(const tinyxml2::XMLDocument&);

   virtual ~QuasiNewtonMethod();

   // Get methods

   const LearningRateAlgorithm& get_learning_rate_algorithm() const;
   LearningRateAlgorithm* get_learning_rate_algorithm_pointer();

   const InverseHessianApproximationMethod& get_inverse_hessian_approximation_method() const;
   string write_inverse_hessian_approximation_method() const;

   // Training parameters

   const type& get_warning_parameters_norm() const;
   const type& get_warning_gradient_norm() const;
   const type& get_warning_learning_rate() const;

   const type& get_error_parameters_norm() const;
   const type& get_error_gradient_norm() const;
   const type& get_error_learning_rate() const;

   const Index& get_epochs_number() const;

   // Stopping criteria

   const type& get_minimum_parameters_increment_norm() const;

   const type& get_minimum_loss_decrease() const;
   const type& get_loss_goal() const;
   const type& get_gradient_norm_goal() const;
   const Index& get_maximum_selection_error_increases() const;

   const Index& get_maximum_epochs_number() const;
   const type& get_maximum_time() const;

   const bool& get_choose_best_selection() const;
   const bool& get_apply_early_stopping() const;

   // Reserve training history

   const bool& get_reserve_training_error_history() const;
   const bool& get_reserve_selection_error_history() const;

   // Set methods

   void set_loss_index_pointer(LossIndex*);

   void set_inverse_hessian_approximation_method(const InverseHessianApproximationMethod&);
   void set_inverse_hessian_approximation_method(const string&);

   void set_display(const bool&);

   void set_default();

   // Training parameters

   void set_warning_parameters_norm(const type&);
   void set_warning_gradient_norm(const type&);
   void set_warning_learning_rate(const type&);

   void set_error_parameters_norm(const type&);
   void set_error_gradient_norm(const type&);
   void set_error_learning_rate(const type&);

   // Stopping criteria

   void set_minimum_parameters_increment_norm(const type&);

   void set_minimum_loss_decrease(const type&);
   void set_loss_goal(const type&);
   void set_gradient_norm_goal(const type&);
   void set_maximum_selection_error_increases(const Index&);

   void set_maximum_epochs_number(const Index&);
   void set_maximum_time(const type&);

   void set_choose_best_selection(const bool&);
   void set_apply_early_stopping(const bool&);

   // Reserve training history

   void set_reserve_training_error_history(const bool&);
   void set_reserve_selection_error_history(const bool&);

   // Utilities

   void set_display_period(const Index&);

   // Training methods

   Tensor<type, 2> calculate_DFP_inverse_hessian(const Tensor<type, 1>&,
                                                 const Tensor<type, 1>&,
                                                 const Tensor<type, 1>&,
                                                 const Tensor<type, 1>&,
                                                 const Tensor<type, 2>&) const;

   Tensor<type, 2> calculate_BFGS_inverse_hessian(const Tensor<type, 1>&,
                                                  const Tensor<type, 1>&,
                                                  const Tensor<type, 1>&,
                                                  const Tensor<type, 1>&,
                                                  const Tensor<type, 2>&) const;

   Tensor<type, 2> calculate_inverse_hessian_approximation(const Tensor<type, 1>&,
                                                           const Tensor<type, 1>&,
                                                           const Tensor<type, 1>&,
                                                           const Tensor<type, 1>&,
                                                           const Tensor<type, 2>&) const;

   const Tensor<type, 2> kronecker_product(Tensor<type, 2>&, Tensor<type, 2>&) const;
   const Tensor<type, 2> kronecker_product(Tensor<type, 1>&, Tensor<type, 1>&) const;

   Results perform_training();

   void perform_training_void();

   // Training history methods

   void set_reserve_all_training_history(const bool&);

   string write_optimization_algorithm_type() const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML() const;
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;

   string object_to_string() const;
   Tensor<string, 2> to_string_matrix() const;

   void update_optimization_data(
           const DataSet::Batch& batch,
           NeuralNetwork::ForwardPropagation& forward_propagation,
           const LossIndex::BackPropagation& back_propagation,
           OptimizationData& optimization_data)
   {
       const Index parameters_number = optimization_data.parameters.dimension(0);

       if(optimization_data.epoch == 0
       || l2_norm(optimization_data.old_parameters - optimization_data.parameters) < numeric_limits<type>::min()
       || l2_norm(optimization_data.old_gradient - back_propagation.gradient) < numeric_limits<type>::min())
       {
           optimization_data.inverse_hessian.setZero();

           for(Index i = 0; i < parameters_number; i++) optimization_data.inverse_hessian(i,i) = 1.0;
       }
       else
       {
           optimization_data.inverse_hessian = calculate_inverse_hessian_approximation(
                                 optimization_data.old_parameters,
                                 optimization_data.parameters,
                                 optimization_data.old_gradient,
                                 back_propagation.gradient,
                                 optimization_data.old_inverse_hessian);
       }

       // Optimization algorithm

       optimization_data.training_direction = optimization_data.inverse_hessian.contract(-back_propagation.gradient, AT_B);

       optimization_data.training_direction = normalized(optimization_data.training_direction);

       // Calculate training slope

       optimization_data.training_slope = back_propagation.gradient.contract(optimization_data.training_direction, AT_B);

       // Check for a descent direction

       if(optimization_data.training_slope(0) >= 0)
       {
           //cout << "Training slope is greater than zero." << endl;

           optimization_data.training_direction = -back_propagation.gradient;

           optimization_data.training_direction = normalized(optimization_data.training_direction);
       }

       // Get initial training rate

       type initial_learning_rate = 0;

       optimization_data.epoch == 0
               ? initial_learning_rate = first_learning_rate
               : initial_learning_rate = optimization_data.old_learning_rate;

       pair<type,type> directional_point = learning_rate_algorithm.calculate_directional_point(
                batch,
                optimization_data.parameters, forward_propagation,
                back_propagation.loss,
                optimization_data.training_direction,
                initial_learning_rate);

       type learning_rate = directional_point.first; // training rate is always zero

       // Reset training direction when training rate is 0

       if(abs(learning_rate) < numeric_limits<type>::min())
       {
           optimization_data.training_direction = -back_propagation.gradient;

           optimization_data.training_direction = normalized(optimization_data.training_direction);

           directional_point = learning_rate_algorithm.calculate_directional_point(batch,
                               optimization_data.parameters, forward_propagation,
                               back_propagation.loss,
                               optimization_data.training_direction,
                               first_learning_rate);

           learning_rate = directional_point.first;
       }

       // training rate is always zero
       optimization_data.parameters += optimization_data.training_direction*learning_rate;

//       parameters_increment_norm = l2_norm(optimization_data.parameters_increment);

       optimization_data.old_parameters = optimization_data.parameters;

       optimization_data.old_training_loss = back_propagation.loss;

//       old_selection_error = selection_error;

       optimization_data.old_gradient = back_propagation.gradient;

       optimization_data.old_inverse_hessian = optimization_data.inverse_hessian;

//       optimization_data.old_learning_rate = learning_rate;


   }


private: 

   /// Training rate algorithm object. 
   /// It is used to calculate the step for the quasi-Newton training direction.

   LearningRateAlgorithm learning_rate_algorithm;

   /// Variable containing the actual method used to obtain a suitable training rate. 

   InverseHessianApproximationMethod inverse_hessian_approximation_method;

   type first_learning_rate = static_cast<type>(0.01);

   /// Value for the parameters norm at which a warning message is written to the screen. 

   type warning_parameters_norm;

   /// Value for the gradient norm at which a warning message is written to the screen. 

   type warning_gradient_norm;

   /// Training rate value at wich a warning message is written to the screen.

   type warning_learning_rate;

   /// Value for the parameters norm at which the training process is assumed to fail. 
   
   type error_parameters_norm;

   /// Value for the gradient norm at which the training process is assumed to fail. 

   type error_gradient_norm;

   /// Training rate at wich the line minimization algorithm is assumed to be unable to bracket a minimum.

   type error_learning_rate;

   // Stopping criteria

   /// Norm of the parameters increment vector at which training stops.

   type minimum_parameters_increment_norm;

   /// Minimum loss improvement between two successive epochs. It is used as a stopping criterion.

   type minimum_loss_decrease;

   /// Goal value for the loss. It is used as a stopping criterion.

   type loss_goal;

   /// Goal value for the norm of the error function gradient. It is used as a stopping criterion.

   type gradient_norm_goal;

   /// Maximum number of epochs at which the selection error increases.
   /// This is an early stopping method for improving selection.

   Index maximum_selection_error_increases;

   /// Maximum number of epochs to perform_training. It is used as a stopping criterion.

   Index maximum_epochs_number;

   /// Maximum training time. It is used as a stopping criterion.

   type maximum_time;

   /// True if the final model will be the neural network with the minimum selection error, false otherwise.

   bool choose_best_selection;

   /// True if the selection error decrease stopping criteria has to be taken in account, false otherwise.

   bool apply_early_stopping;

   // TRAINING HISTORY

   /// True if the training error history vector is to be reserved, false otherwise.

   bool reserve_training_error_history;

   /// True if the selection error history vector is to be reserved, false otherwise.

   bool reserve_selection_error_history;

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
