//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   G E N E T I C   A L G O R I T H M   T E S T   C L A S S   H E A D E R 
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "genetic_algorithm_test.h"


GeneticAlgorithmTest::GeneticAlgorithmTest() : UnitTesting()
{
}


GeneticAlgorithmTest::~GeneticAlgorithmTest()
{
}


void GeneticAlgorithmTest::test_constructor()
{
    cout << "test_constructor\n";

    NeuralNetwork nn;
    DataSet ds;

    TrainingStrategy training_strategy(&nn, &ds);

    GeneticAlgorithm ga1(&training_strategy);

    assert_true(ga1.has_training_strategy(), LOG);

    GeneticAlgorithm ga2;

    assert_true(!ga2.has_training_strategy(), LOG);
}


void GeneticAlgorithmTest::test_destructor()
{
    cout << "test_destructor\n";

    GeneticAlgorithm* ga = new GeneticAlgorithm;

    delete ga;
}


void GeneticAlgorithmTest::test_set_default()
{
    cout << "test_set_default\n";
}


void GeneticAlgorithmTest::test_initialize_population()
{
    cout << "test_initialize_population\n";

    DataSet data_set;

    Tensor<Index, 1> arquitecture(3);
    arquitecture.setValues({3,2,1});

    NeuralNetwork neural_network(NeuralNetwork::Approximation, arquitecture);

    SumSquaredError sum_squared_error(&neural_network, &data_set);

    TrainingStrategy ts(&neural_network, &data_set);

    GeneticAlgorithm ga(&ts);

    Tensor<bool, 2> population;

    ga.set_population_size(10);

    ga.set_inicialization_method(GeneticAlgorithm::Random);

    ga.initialize_population();

    population = ga.get_population();
    const Tensor<bool, 1> population_column = population.chip(0,1);

    assert_true(population.size() == 10, LOG);
    assert_true(population_column.size() == 3, LOG);

}


/// @todo

void GeneticAlgorithmTest::test_calculate_fitness() // @todo
{
    cout << "test_calculate_fitness\n";

//    DataSet data_set;

//    Tensor<Index, 1> arquitecture(3);
//    arquitecture.setValues({3,2,1});

//    NeuralNetwork neural_network(NeuralNetwork::Approximation, arquitecture);

//    SumSquaredError sum_squared_error(&neural_network, &data_set);

//    TrainingStrategy ts(&neural_network, &data_set);

//    GeneticAlgorithm ga(&ts);

//    Tensor<type, 2> loss(4,2);

//    Tensor<type, 1> fitness;

//    ga.set_population_size(4);

//    loss(0,1) = 1;
//    loss(1,1) = 2;
//    loss(2,1) = 3;
//    loss(3,1) = 4;

//    ga.set_loss(loss);

//    ga.set_fitness_assignment_method(GeneticAlgorithm::RankBased);

//    ga.calculate_fitness();

//    fitness = ga.get_fitness();

//    assert_true(maximal_index(fitness) == 0, LOG);
//    assert_true(minimal_index(fitness) == 3, LOG);

//    ga.set_fitness_assignment_method(GeneticAlgorithm::ObjectiveBased);

//    ga.calculate_fitness();

//    fitness = ga.get_fitness();

//    assert_true(maximal_index(fitness) == 0, LOG);
//    assert_true(minimal_index(fitness) == 3, LOG);
}


void GeneticAlgorithmTest::test_perform_selection() // @todo
{
    cout << "test_perform_selection\n";

//    DataSet data_set;

//    Tensor<Index, 1> arquitecture(3);
//    arquitecture.setValues({3,2,1});

//    NeuralNetwork neural_network(NeuralNetwork::Approximation, arquitecture);

//    SumSquaredError sum_squared_error(&neural_network, &data_set);

//    TrainingStrategy ts(&neural_network, &data_set);

//    GeneticAlgorithm ga(&ts);

//    Tensor<bool, 2> population;

//    Tensor< Tensor<bool, 1>, 1> selected_population;

//    Tensor<type, 1> fitness(4);

//    Tensor<type, 2> loss(4,2);

//    ga.set_population_size(4);

//    fitness[0] = 1;
//    fitness[1] = 2;
//    fitness[2] = 3;
//    fitness[3] = 4;

//    loss(0,0) = 0.0; loss(0,1) = static_cast<type>(0.4);
//    loss(1,0) = 0.0; loss(1,1) = static_cast<type>(0.3);
//    loss(2,0) = 0.0; loss(2,1) = static_cast<type>(0.2);
//    loss(3,0) = 0.0; loss(3,1) = static_cast<type>(0.1);

//    ga.set_inicialization_method(GeneticAlgorithm::Random);

//    ga.initialize_population();

//    ga.set_fitness(fitness);

//    ga.set_loss(loss);

//    ga.set_elitism_size(2);

//    population = ga.get_population();

//    ga.perform_selection();

////    selected_population = ga.get_population();

//    assert_true(selected_population[0] == population[3], LOG);
//    assert_true(selected_population[1] == population[2], LOG);
}


void GeneticAlgorithmTest::test_perform_crossover() // @todo
{
    cout << "test_perform_crossover\n";

    DataSet data_set;

    Tensor<Index, 1> arquitecture(3);
    arquitecture.setValues({2,2,1});

    NeuralNetwork neural_network(NeuralNetwork::Approximation, arquitecture);

    SumSquaredError sum_squared_error(&neural_network, &data_set);

    TrainingStrategy ts(&neural_network, &data_set);

    GeneticAlgorithm ga(&ts);

    Tensor<bool, 2> population(4,4);
    Tensor<bool, 1> individual(2);

    Tensor<bool, 2> crossover_population;

    Tensor<type, 1> fitness(4);

    Tensor<type, 2> loss(4,2);

    individual[0] = true;
    individual[1] = true;
//    population[0] = individual[0];
//    population[1] = individual[1];

    individual[0] = false;
    individual[1] = true;
//    population[2] = individual[0];
//    population[3] = individual[1];

    fitness[0] = 1;
    fitness[1] = 2;
    fitness[2] = 3;
    fitness[3] = 4;

    loss(0,0) = 0.0; loss(0,1) = static_cast<type>(0.4);
    loss(1,0) = 0.0; loss(1,1) = static_cast<type>(0.3);
    loss(2,0) = 0.0; loss(2,1) = static_cast<type>(0.2);
    loss(3,0) = 0.0; loss(3,1) = static_cast<type>(0.1);

//    ga.set_population_size(4);

////    ga.set_population(population);

//    ga.set_fitness(fitness);

//    ga.set_loss(loss);

//    ga.set_elitism_size(2);

//    ga.perform_selection();

//    ga.set_crossover_method(GeneticAlgorithm::Uniform);

//    ga.perform_crossover();

////    crossover_population = ga.get_population();

//    assert_true(crossover_population(2,1) == true, LOG);

////    ga.set_population(population);

//    ga.set_fitness(fitness);

//    ga.set_loss(loss);

//    ga.set_elitism_size(2);

//    ga.perform_selection();

//    ga.set_crossover_method(GeneticAlgorithm::OnePoint);

//    ga.set_crossover_first_point(1);

//    ga.perform_crossover();

//    crossover_population = ga.get_population();

//    assert_true(crossover_population(2,1) == true, LOG);
}


void GeneticAlgorithmTest::test_perform_mutation()
{
    cout << "test_perform_mutation\n";

    DataSet data_set;

    Tensor<Index, 1> arquitecture(3);
    arquitecture.setValues({1,2,1});

    NeuralNetwork neural_network(NeuralNetwork::Approximation, arquitecture);

    SumSquaredError sum_squared_error(&neural_network, &data_set);

    TrainingStrategy ts(&neural_network, &data_set);

    GeneticAlgorithm ga(&ts);

    Tensor<bool, 2> population(4,1);
    Tensor<bool, 1> individual(1);

    Tensor<bool, 2> mutated_population;

//    individual[0] = 1;
//    population[0] = individual;
//    population[1] = individual;

//    individual[0] = 0;
//    population[2] = individual;
//    population[3] = individual;

    ga.set_population_size(4);

    ga.set_population(population);

    ga.set_mutation_rate(1);

    ga.perform_mutation();

    mutated_population = ga.get_population();

//    assert_true(mutated_population[0][0] == 1, LOG);
//    assert_true(mutated_population[1][0] == 1, LOG);
//    assert_true(mutated_population[2][0] == 1, LOG);
//    assert_true(mutated_population[3][0] == 1, LOG);

    ga.set_population(population);

    ga.set_mutation_rate(0);

    ga.perform_mutation();

    mutated_population = ga.get_population();

//    assert_true(mutated_population[0][0] == 1, LOG);
//    assert_true(mutated_population[1][0] == 1, LOG);
//    assert_true(mutated_population[2][0] == 0, LOG);
//    assert_true(mutated_population[3][0] == 0, LOG);

}


void GeneticAlgorithmTest::test_perform_inputs_selection() // @todo
{
    cout << "test_perform_inputs_selection\n";

//    DataSet data_set;

//    Tensor<type, 2> data(20,3);

//    NeuralNetwork neural_network;

//    SumSquaredError sum_squared_error(&neural_network,& data_set);

//    GeneticAlgorithm::GeneticAlgorithmResults* ga_results;
//    GeneticAlgorithm::GeneticAlgorithmResults* ga1_results;

//    // Test

//    for(Index i = 0; i < 20; i++)
//    {
//        data(i,0) = static_cast<type>(i);
//        data(i,1) = 10.0;
//        data(i,2) = static_cast<type>(i);
//    }

//    data_set.set(data);

//    Tensor<Index, 1> arquitecture(3);
//    arquitecture.setValues({2,6,1});

//    neural_network.set(NeuralNetwork::Approximation, arquitecture);

//    TrainingStrategy ts(&neural_network, &data_set);

//    GeneticAlgorithm ga(&ts);

//    ts.set_display(false);

//    ga.set_display(false);

//    ga.set_approximation(true);

//    ga.set_population_size(10);

//    ga.set_selection_error_goal(1);

//    ga_results = ga.perform_inputs_selection();

//    assert_true(ga_results->final_selection_error < 1, LOG);
//    assert_true(ga_results->stopping_condition == InputsSelection::SelectionErrorGoal, LOG);

//    ga.delete_selection_history();
//    ga.delete_parameters_history();
//    ga.delete_loss_history();

//    // Test

////    Index j = -10;

////    for(Index i = 0; i < 10; i++)
////    {
////        data(i,0) = (type)j;
////        data(i,1) = rand();
////        data(i,2) = 1.0;
////        j+=1;
////    }
////    for(Index i = 10; i < 20; i++)
////    {
////        data(i,0) = (type)i;
////        data(i,1) = rand();
////        data(i,2) = 0.0;
////    }

////    data_set.set(data);

//    data_set.generate_inputs_selection_data(20,3);

//    data_set.set_default_columns_uses();

//    neural_network.set(NeuralNetwork::Approximation, arquitecture);

//    TrainingStrategy ts1(&neural_network, &data_set);

//    GeneticAlgorithm ga1(&ts);

//    ts1.set_display(false);

//    ga1.set_display(false);

//    ga1.set_approximation(false);

//    ga1.set_population_size(10);

//    ga1.set_selection_error_goal(0.0);
//    ga1.set_maximum_iterations_number(1);

//    ga1_results = ga1.perform_inputs_selection();

////    assert_true(ga1_results->iterations_number == 1, LOG);
//    assert_true(ga1_results->final_selection_error < 1, LOG);
//    assert_true(ga_results->stopping_condition == InputsSelection::SelectionErrorGoal, LOG);

//    ga1.delete_selection_history();
//    ga1.delete_parameters_history();
//    ga1.delete_loss_history();
}


void GeneticAlgorithmTest::test_to_XML()
{
    cout << "test_to_XML\n";

    GeneticAlgorithm ga;

    tinyxml2::XMLDocument* document = ga.to_XML();
    assert_true(document != nullptr, LOG);

    delete document;
}


void GeneticAlgorithmTest::test_from_XML()
{
    cout << "test_from_XML\n";

    GeneticAlgorithm ga;

    tinyxml2::XMLDocument* document = ga.to_XML();
    ga.from_XML(*document);

    delete document;
}


void GeneticAlgorithmTest::run_test_case()
{
    cout << "Running genetic algorithm test case...\n";

    // Constructor and destructor methods

    test_constructor();
    test_destructor();

    // Set methods

    test_set_default();

    // Population methods

    test_initialize_population();

    test_calculate_fitness();

    // Selection methods

    test_perform_selection();

    // Crossover methods

    test_perform_crossover();

    // Mutation methods

    test_perform_mutation();

    // Order selection methods

    test_perform_inputs_selection();

    // Serialization methods

    test_to_XML();

    test_from_XML();

    cout << "End of genetic algorithm test case.\n";
}
