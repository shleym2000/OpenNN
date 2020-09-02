//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   S T A T I S T I C S   S O U R C E
//
//   Artificial Intelligence Techniques, SL
//   artelnics@artelnics.com

#include "statistics.h"

namespace OpenNN
{

/// Default constructor.

Descriptives::Descriptives()
{
    name = "Descriptives";
    minimum = -1.0;
    maximum = 1.0;
    mean = 0;
    standard_deviation = 1.0;
}


/// Values constructor.

Descriptives::Descriptives(const type &new_minimum, const type &new_maximum,
                           const type &new_mean, const type &new_standard_deviation)
{
    minimum = new_minimum;
    maximum = new_maximum;
    mean = new_mean;
    standard_deviation = new_standard_deviation;
}


/// Destructor.

Descriptives::~Descriptives()
{}


/// Sets a new minimum value in the descriptives structure.
/// @param new_minimum Minimum value.

void Descriptives::set_minimum(const type &new_minimum)
{
    minimum = new_minimum;
}


/// Sets a new maximum value in the descriptives structure.
/// @param new_maximum Maximum value.

void Descriptives::set_maximum(const type &new_maximum)
{
    maximum = new_maximum;
}


/// Sets a new mean value in the descriptives structure.
/// @param new_mean Mean value.

void Descriptives::set_mean(const type &new_mean)
{
    mean = new_mean;
}


/// Sets a new standard deviation value in the descriptives structure.
/// @param new_standard_deviation Standard deviation value.

void Descriptives::set_standard_deviation(const type &new_standard_deviation)
{
    standard_deviation = new_standard_deviation;
}


/// Returns all the statistical parameters contained in a single vector.
/// The size of that vector is four.
/// The elements correspond to the minimum, maximum, mean and standard deviation
/// values respectively.

Tensor<type, 1> Descriptives::to_vector() const
{
    Tensor<type, 1> statistics_vector(4);
    statistics_vector[0] = minimum;
    statistics_vector[1] = maximum;
    statistics_vector[2] = mean;
    statistics_vector[3] = standard_deviation;

    return statistics_vector;
}


/// Returns true if the minimum value is -1 and the maximum value is +1,
/// and false otherwise.

bool Descriptives::has_minimum_minus_one_maximum_one()
{
    if(abs(minimum + 1) < numeric_limits<type>::min() && abs(maximum - 1) < numeric_limits<type>::min())
    {
        return true;
    }

    return false;
}


/// Returns true if the mean value is 0 and the standard deviation value is 1,
/// and false otherwise.

bool Descriptives::has_mean_zero_standard_deviation_one()
{
    if(abs(mean) < numeric_limits<type>::min() && abs(standard_deviation - 1) < numeric_limits<type>::min())
    {
        return true;
    }
    else
    {
        return false;
    }

}


/// Print the tittle of descriptives structure

void Descriptives::print(const string& title) const
{
    cout << title << endl
         << "Minimum: " << minimum << endl
         << "Maximum: " << maximum << endl
         << "Mean: " << mean << endl
         << "Standard deviation: " << standard_deviation << endl;
}


BoxPlot::BoxPlot(const type& new_minimum, const type& new_first_cuartile, const type& new_median, const type& new_third_quartile, const type& new_maximum)
{
    minimum = new_minimum;
    first_quartile = new_first_cuartile;
    median = new_median;
    third_quartile = new_third_quartile;
    maximum = new_maximum;
}


/// Saves to a file the minimum, maximum, mean and standard deviation
/// of the descriptives structure.
/// @param file_name Name of descriptives data file.

void Descriptives::save(const string &file_name) const
{
    ofstream file(file_name.c_str());

    if(!file.is_open())
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "void save(const string&) const method.\n"
               << "Cannot open descriptives data file.\n";

        throw logic_error(buffer.str());
    }

    // Write file

    file << "Minimum: " << minimum << endl
         << "Maximum: " << maximum << endl
         << "Mean: " << mean << endl
         << "Standard deviation: " << standard_deviation << endl;

    // Close file

    file.close();
}


Histogram::Histogram() {}


/// Destructor.

Histogram::~Histogram() {}


/// Bins number constructor.
/// @param bins_number Number of bins in the histogram.

Histogram::Histogram(const Index &bins_number)
{
    centers.resize(bins_number);
    frequencies.resize(bins_number);
}


/// Values constructor.
/// @param new_centers Center values for the bins.
/// @param new_frequencies Number of variates in each bin.

Histogram::Histogram(const Tensor<type, 1>&new_centers,
                     const Tensor<Index, 1>&new_frequencies)
{
    centers = new_centers;
    frequencies = new_frequencies;
}


// Data constructor
/// @param data Numerical data.
/// @param number_of_bins Number of bins.

Histogram::Histogram(const Tensor<type, 1>& data,
                     const Index& number_of_bins)
{
    const type data_maximum = maximum(data);
    const type data_minimum = minimum(data);
    const type step = (data_maximum - data_minimum) / number_of_bins;


    Tensor<type, 1> new_centers(number_of_bins);
    for(Index i = 0; i < number_of_bins; i++)
    {
        new_centers(i) = data_minimum + (0.5 * step) + (step * i);
    }

    Tensor<Index, 1> new_frequencies(number_of_bins);
    new_frequencies.setZero();

    type value;
    Index corresponding_bin;

    for(Index i = 0; i < data.dimension(0); i++)
    {
        value = data(i);
        corresponding_bin = int((value - data_minimum) / step);

        new_frequencies(corresponding_bin)++;
    }

    centers = new_centers;
    frequencies = new_frequencies;
}


// Probabilities constructor
/// @param data Numerical probabilities data.

Histogram::Histogram(const Tensor<type, 1>& probability_data)
{
    const size_t number_of_bins = 10;
    type data_maximum = maximum(probability_data);
    const type data_minimum = 0.0;

    if(data_maximum > 1)
    {
        data_maximum = 100.0;
    }
    else
    {
        data_maximum = 1.0;
    }

    const type step = (data_maximum - data_minimum) / number_of_bins;


    Tensor<type, 1> new_centers(number_of_bins);
    for(Index i = 0; i < number_of_bins; i++)
    {
        new_centers(i) = data_minimum + (0.5 * step) + (step * i);
    }

    Tensor<Index, 1> new_frequencies(number_of_bins);
    new_frequencies.setZero();

    type value;
    Index corresponding_bin;

    for(Index i = 0; i < probability_data.dimension(0); i++)
    {
        value = probability_data(i);
        corresponding_bin = int((value - data_minimum) / step);

        new_frequencies(corresponding_bin)++;
    }

    centers = new_centers;
    frequencies = new_frequencies;
}

/// Returns the number of bins in the histogram.

Index Histogram::get_bins_number() const
{
    return centers.size();
}


/// Returns the number of bins with zero variates.

Index Histogram::count_empty_bins() const
{
    const auto size = frequencies.dimension(0);

    Index count = 0;

    for(Index i = 0; i < size; i++)
    {
        if(frequencies(i) == 0) count++;
    }

    return count;
}


/// Returns the number of variates in the less populated bin.

Index Histogram::calculate_minimum_frequency() const
{
    return minimum(frequencies);
}


/// Returns the number of variates in the most populated bin.

Index Histogram::calculate_maximum_frequency() const
{
    return maximum(frequencies);

}


/// Retuns the index of the most populated bin.

Index Histogram::calculate_most_populated_bin() const
{

    const Tensor<Index, 0> max_element = frequencies.maximum();

    for(Index i = 0; i < frequencies.size(); i++)
    {
        if(max_element(0) == frequencies(i)) return i;
    }

    return 0;
}


/// Returns a vector with the centers of the less populated bins.

Tensor<type, 1> Histogram::calculate_minimal_centers() const
{
    const Index minimum_frequency = calculate_minimum_frequency();

    Index minimal_indices_size = 0;

    for(Index i = 0; i < frequencies.size(); i++)
    {
        if(frequencies(i) == minimum_frequency)
        {
            minimal_indices_size++;
        }
    }

    Index index = 0;

    Tensor<type, 1> minimal_centers(minimal_indices_size);

    for(Index i = 0; i < frequencies.size(); i++)
    {
        if(frequencies(i) == minimum_frequency)
        {
            minimal_centers(index) = static_cast<type>(centers(i));

            index++;
        }
    }

    return minimal_centers;
}


/// Returns a vector with the centers of the most populated bins.

Tensor<type, 1> Histogram::calculate_maximal_centers() const
{
    const Index maximum_frequency = calculate_maximum_frequency();

    Index maximal_indices_size = 0;

    for(Index i = 0; i < frequencies.size(); i++)
    {
        if(frequencies(i) == maximum_frequency)
        {
            maximal_indices_size++;
        }
    }

    Index index = 0;

    Tensor<type, 1> maximal_centers(maximal_indices_size);

    for(Index i = 0; i < frequencies.size(); i++)
    {
        if(maximum_frequency == frequencies(i))
        {
            maximal_centers(index) = static_cast<type>(centers(i));

            index++;
        }
    }

    return maximal_centers;
}


/// Returns the number of the bin to which a given value belongs to.
/// @param value Value for which we want to get the bin.

Index Histogram::calculate_bin(const type&value) const
{
    const Index bins_number = get_bins_number();

    const type minimum_center = centers[0];
    const type maximum_center = centers[bins_number - 1];

    const type length = static_cast<type>(maximum_center - minimum_center)/static_cast<type>(bins_number - 1.0);

    type minimum_value = centers[0] - length / 2;
    type maximum_value = minimum_value + length;

    if(value < maximum_value)
    {
        return 0;
    }

    for(Index j = 1; j < bins_number - 1; j++)
    {
        minimum_value = minimum_value + length;
        maximum_value = maximum_value + length;

        if(value >= minimum_value && value < maximum_value)
        {
            return j;
        }
    }

    if(value >= maximum_value)
    {
        return bins_number - 1;
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "Index Histogram::calculate_bin(const type&) const.\n"
               << "Unknown return value.\n";

        throw logic_error(buffer.str());
    }
}


/// Returns the frequency of the bin to which a given value belongs to.
/// @param value Value for which we want to get the frequency.

Index Histogram::calculate_frequency(const type&value) const
{
    const Index bin_number = calculate_bin(value);

    const Index frequency = frequencies[bin_number];

    return frequency;
}


void Histogram::save(const string& histogram_file_name) const
{
    const Index number_of_bins = centers.dimension(0);
    ofstream histogram_file(histogram_file_name);


    histogram_file << "centers,frequencies" << endl;
    for(Index i = 0; i < number_of_bins; i++)
    {
        histogram_file << centers(i) << ",";
        histogram_file << frequencies(i) << endl;
    }

    histogram_file.close();

}


/// Returns the smallest element of a type vector.
/// @param vector Vector to obtain the minimum value.

type minimum(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    if(size == 0) return NAN;

    type minimum = numeric_limits<type>::max();

    for(Index i = 0; i < size; i++)
    {
        if(vector(i) < minimum && !::isnan(vector(i)))
        {
            minimum = vector(i);
        }
    }

    return minimum;
}


/// Returns the smallest element of a index vector.
/// @param vector Vector to obtain the minimum value.

Index minimum(const Tensor<Index, 1>& vector)
{
    const Index size = vector.size();

    if(size == 0) return 0;

    Index minimum = numeric_limits<Index>::max();

    for(Index i = 0; i < size; i++)
    {
        if(vector(i) < minimum)
        {
            minimum = vector(i);
        }
    }

    return minimum;
}


/// Returns the smallest element of a type vector.
/// @param vector Vector to obtain the minimum value.
/// @param indices Vector of used indices.

type minimum(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
    const Index size = indices.dimension(0);

    type minimum = numeric_limits<type>::max();

    Index index;

    for(Index i = 0; i < size; i++)
    {
        index = indices(i);

        if(vector(index) < minimum && !::isnan(vector(index)))
        {
            minimum = vector(index);
        }
    }

    return minimum;
}



/// Returns the smallest element of a Index vector.

//time_t minimum(const Tensor<time_t, 1>& vector)
//{

//    const Tensor<time_t, 0> min_element = vector.minimum();

//    return min_element(0);
//}


/// Returns the largest element in the vector.
/// @param vector Vector to obtain the maximum value.

type maximum(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    type maximum = -numeric_limits<type>::max();

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)) && vector(i) > maximum)
        {
            maximum = vector(i);
        }
    }

    return maximum;
}


/// Returns the largest element in the vector.
/// @param vector Vector to obtain the maximum value.
/// @param indices Vector of used indices.

type maximum(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
    const Index size = indices.dimension(0);

    type maximum = -numeric_limits<type>::max();

    Index index;

    for(Index i = 0; i < size; i++)
    {
        index = indices(i);

        if(!::isnan(vector(index)) && vector(index) > maximum)
        {
            maximum = vector(index);
        }
    }

    return maximum;
}



time_t maximum(const Tensor<time_t, 1>& vector)
{
    const Tensor<time_t,0> max_element = vector.maximum();

    return max_element(0);
}


/// Returns the maximums values of given columns.
/// The format is a vector of type values.
/// The size of that vector is equal to the number of given columns.
/// @param matrix Used matrix.
/// @param rows_indices Indices of the rows for which the maximums are to be computed.
/// @param columns_indices Indices of the columns for which the maximums are to be computed.

Tensor<type, 1> columns_maximums(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& rows_indices, const Tensor<Index, 1>& columns_indices)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    Tensor<Index, 1> used_columns_indices;

    if(columns_indices.dimension(0) == 0)
    {
        used_columns_indices.resize(columns_number);

        for (Index i = 0; i < columns_number; i++)
        {
            used_columns_indices(i) = i;
        }
    }
    else
    {
        used_columns_indices = columns_indices;
    }

    Tensor<Index, 1> used_rows_indices;

    if(rows_indices.dimension(0) == 0)
    {
        used_rows_indices.resize(rows_number);

        for (Index i = 0; i < rows_number; i++)
        {
            used_rows_indices(i) = i;
        }
    }
    else
    {
        used_rows_indices = rows_indices;
    }

    const Index rows_indices_size = used_rows_indices.size();
    const Index columns_indices_size = used_columns_indices.size();

    Tensor<type, 1> maximums(columns_indices_size);

    Index row_index;
    Index column_index;

    Tensor<type, 1> column(rows_indices_size);

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = used_columns_indices(j);

        for(Index i = 0; i < rows_indices_size; i++)
        {
            row_index = used_rows_indices(i);

            column(i) = matrix(row_index,column_index);
        }

        maximums(j) = maximum(column);
    }

    return maximums;
}


/// Returns the mean of the subvector defined by a start and end elements.
/// @param vector Vector to be evaluated.
/// @param begin Start element.
/// @param end End element.

type mean(const Tensor<type, 1>& vector, const Index& begin, const Index& end)
{
#ifdef __OPENNN_DEBUG__

    if(begin > end)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "type mean(const Tensor<type, 1>& vector, const Index& begin, const Index& end) \n"
               << "Begin must be less or equal than end.\n";

        throw logic_error(buffer.str());
    }

#endif

    if(end == begin) return vector[begin];

    type sum = 0;

    for(Index i = begin; i <= end; i++)
    {
        sum += vector(i);
    }

    return sum /static_cast<type>(end-begin+1);
}


/// Returns the mean of the elements in the vector.
/// @param vector Vector to be evaluated.

type mean(const Tensor<type, 1>& vector)
{

    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type mean(const Tensor<type, 1>& vector, const Index& begin, const Index& end) "
               "const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    type sum = 0;

    Index count = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)))
        {
            sum += vector(i);
            count++;
        }
    }

    cout << "sum: " << sum << endl;
    cout << "count: " << count << endl;

    const type mean = sum /static_cast<type>(count);

    return mean;
}


/// Returns the variance of the elements in the vector.
/// @param vector Vector to be evaluated.

type variance(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type variance(const Tensor<type, 1>& vector) "
               "const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    type sum = 0;
    type squared_sum = 0;

    Index count = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)))
        {
            sum += vector(i);
            squared_sum += vector(i) * vector(i);

            count++;
        }
    }

    if(count <= 1)
    {
        return 0.0;
    }

    const type numerator = squared_sum -(sum * sum) /static_cast<type>(count);
    const type denominator = static_cast<type>(count - 1);

    return numerator/denominator;
}


/// Returns the variance of the elements in the vector.
/// @param vector Vector to be evaluated.

type variance(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
    const Index size = indices.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type variance(const Tensor<type, 1>&, const Tensor<Index, 1>&) "
               "const method.\n"
               << "Indeces size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    type sum = 0;
    type squared_sum = 0;

    Index count = 0;

    Index index = 0;

    for(Index i = 0; i < size; i++)
    {
        index = indices(i);

        if(!::isnan(vector(index)))
        {
            sum += vector(index);
            squared_sum += vector(index) * vector(index);

            count++;
        }
    }

    if(count <= 1)
    {
        return 0.0;
    }

    const type numerator = squared_sum -(sum * sum) /static_cast<type>(count);
    const type denominator = static_cast<type>(count - 1);

    return numerator/denominator;
}


/// Returns the standard deviation of the elements in the vector.
/// @param vector Vector to be evaluated.

type standard_deviation(const Tensor<type, 1>& vector)
{
#ifdef __OPENNN_DEBUG__

    const Index size = vector.dimension(0);

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type standard_deviation(const Tensor<type, 1>&) const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    return sqrt(variance(vector));
}


/// Returns the standard deviation of the elements in the vector.
/// @param vector Vector to be evaluated.

type standard_deviation(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
#ifdef __OPENNN_DEBUG__

    const Index size = vector.dimension(0);

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type standard_deviation(const Tensor<type, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    return sqrt(variance(vector, indices));
}



/// @todo check

Tensor<type, 1> standard_deviation(const Tensor<type, 1>& vector, const Index& period)
{
    const Index size = vector.dimension(0);

    Tensor<type, 1> std(size);

    type mean_value = 0;
    type sum = 0;

    for(Index i = 0; i < size; i++)
    {
        const Index begin = i < period ? 0 : i - period + 1;
        const Index end = i;

        mean_value = mean(vector, begin,end);

        for(Index j = begin; j < end+1; j++)
        {
            sum += (vector(j) - mean_value) *(vector(j) - mean_value);
        }

        std(i) = sqrt(sum / type(period));

        mean_value = 0;
        sum = 0;
    }


    return std;
}


/// Returns the asymmetry of the elements in the vector.
/// @param vector Vector to be evaluated.

type asymmetry(const Tensor<type, 1>& vector)
{

    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type asymmetry(const Tensor<type, 1>& vector) const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    if(size == 1)
    {
        return 0.0;
    }

    const type standard_deviation_value = standard_deviation(vector);

    const type mean_value = mean(vector);

    type sum = 0;

    Index count = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)))
        {
            sum += (vector(i) - mean_value) *(vector(i) - mean_value) *(vector(i) - mean_value);

            count++;
        }
    }

    const type numerator = sum /count;
    const type denominator = standard_deviation_value * standard_deviation_value * standard_deviation_value;

    return numerator/denominator;

}

/// Returns the kurtosis of the elements in the vector.
/// @param vector Vector to be evaluated.

type kurtosis(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);
#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type kurtosis(const Tensor<type, 1>& vector) const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    if(size == 1)
    {
        return 0.0;
    }

    const type standard_deviation_value = standard_deviation(vector);

    const type mean_value = mean(vector);

    type sum = 0;

    Index count = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)))
        {
            sum += (vector(i) - mean_value)*(vector(i) - mean_value)*(vector(i) - mean_value)*(vector(i) - mean_value);

            count++;
        }
    }

    const type numerator = sum /count;
    const type denominator = standard_deviation_value*standard_deviation_value*standard_deviation_value*standard_deviation_value;

    return numerator/denominator - 3;

}


/// Returns the median of the elements in the vector
/// @param vector Vector to be evaluated.

type median(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    // Fix missing values

    Index new_size = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!isnan(vector(i)))
        {
            new_size++;
        }
    }

    Tensor<type, 1> sorted_vector;
    sorted_vector.resize(new_size);

    Index sorted_index = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!isnan(vector(i)))
        {
            sorted_vector(sorted_index) = vector(i);

            sorted_index++;
        }
    }

    // Calculate median

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    Index median_index;

    if(new_size % 2 == 0)
    {
        median_index = static_cast<Index>(new_size / 2);

        return (sorted_vector(median_index-1) + sorted_vector(median_index)) / static_cast<type>(2.0);
    }
    else
    {
        median_index = static_cast<Index>(new_size / 2);

        return sorted_vector(median_index);
    }
}


/// Returns the quartiles of the elements in the vector.
/// @param vector Vector to be evaluated.

Tensor<type, 1> quartiles(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    // Fix missing values

    Index new_size = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!isnan(vector(i)))
        {
            new_size++;
        }
    }

    Tensor<type, 1> sorted_vector;
    sorted_vector.resize(new_size);

    Index sorted_index = 0;

    for(Index i = 0; i < size; i++)
    {
        if(!isnan(vector(i)))
        {
            sorted_vector(sorted_index) = vector(i);

            sorted_index++;
        }
    }

    // Calculate quartiles

    Tensor<type, 1> first_sorted_vector(new_size/2);
    Tensor<type, 1> last_sorted_vector(new_size/2);

    for(Index i = 0; i < new_size/2 ; i++)
    {
        first_sorted_vector(i) = sorted_vector(i);
    }

    for(Index i = 0; i < new_size/2; i++)
    {
        last_sorted_vector(i) = sorted_vector[i + new_size - new_size/2];
    }

    Tensor<type, 1> quartiles(3);

    if(new_size == 1)
    {
        quartiles(0) = sorted_vector(0);
        quartiles(1) = sorted_vector(0);
        quartiles(2) = sorted_vector(0);
    }
    else if(new_size == 2)
    {
        quartiles(0) = (sorted_vector(0)+sorted_vector(1))/4;
        quartiles(1) = (sorted_vector(0)+sorted_vector(1))/2;
        quartiles(2) = (sorted_vector(0)+sorted_vector(1))*3/4;
    }
    else if(new_size == 3)
    {
        quartiles(0) = (sorted_vector(0)+sorted_vector(1))/2;
        quartiles(1) = sorted_vector(1);
        quartiles(2) = (sorted_vector(2)+sorted_vector(1))/2;
    }
    else if(new_size % 2 == 0)
    {
        Index median_index = static_cast<Index>(first_sorted_vector.size() / 2);
        quartiles(0) = (first_sorted_vector(median_index-1) + first_sorted_vector(median_index)) / static_cast<type>(2.0);

        median_index = static_cast<Index>(new_size / 2);
        quartiles(1) = (sorted_vector(median_index-1) + sorted_vector(median_index)) / static_cast<type>(2.0);

        median_index = static_cast<Index>(last_sorted_vector.size() / 2);
        quartiles(2) = (last_sorted_vector(median_index-1) + last_sorted_vector(median_index)) / static_cast<type>(2.0);
    }
    else
    {
        quartiles(0) = sorted_vector(new_size/4);
        quartiles(1) = sorted_vector(new_size/2);
        quartiles(2) = sorted_vector(new_size*3/4);
    }

    return quartiles;
}


/// Returns the quartiles of the elements of the vector that correspond to the given indices.
/// @param vector Vector to be evaluated.
/// @param indices Indices of the elements of the vector to be evaluated.

Tensor<type, 1> quartiles(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
    const Index indices_size = indices.dimension(0);

    // Fix missing values

    Index index;
    Index new_size = 0;

    for(Index i = 0; i < indices_size; i++)
    {
        index = indices(i);

        if(!isnan(vector(index)))
        {
            new_size++;
        }
    }

    Tensor<type, 1> sorted_vector;
    sorted_vector.resize(new_size);

    Index sorted_index = 0;

    for(Index i = 0; i < indices_size; i++)
    {
        index = indices(i);

        if(!isnan(vector(index)))
        {
            sorted_vector(sorted_index) = vector(index);

            sorted_index++;
        }
    }

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    // Calculate quartiles

    Tensor<type, 1> first_sorted_vector(new_size/2);
    Tensor<type, 1> last_sorted_vector(new_size/2);

    for(Index i = 0; i < new_size/2 ; i++)
    {
        first_sorted_vector(i) = sorted_vector(i);
    }

    for(Index i = 0; i < new_size/2; i++)
    {
        last_sorted_vector(i) = sorted_vector(i + new_size - new_size/2);
    }

    Tensor<type, 1> quartiles(3);

    if(new_size == 1)
    {
        quartiles(0) = sorted_vector(0);
        quartiles(1) = sorted_vector(0);
        quartiles(2) = sorted_vector(0);
    }
    else if(new_size == 2)
    {
        quartiles(0) = (sorted_vector(0)+sorted_vector(1))/4;
        quartiles(1) = (sorted_vector(0)+sorted_vector(1))/2;
        quartiles(2) = (sorted_vector(0)+sorted_vector(1))*3/4;
    }
    else if(new_size == 3)
    {
        quartiles(0) = (sorted_vector(0)+sorted_vector(1))/2;
        quartiles(1) = sorted_vector(1);
        quartiles(2) = (sorted_vector(2)+sorted_vector(1))/2;
    }
    else if(new_size % 2 == 0)
    {
        Index median_index = static_cast<Index>(first_sorted_vector.size() / 2);
        quartiles(0) = (first_sorted_vector(median_index-1) + first_sorted_vector(median_index)) / static_cast<type>(2.0);

        median_index = static_cast<Index>(new_size / 2);
        quartiles(1) = (sorted_vector(median_index-1) + sorted_vector(median_index)) / static_cast<type>(2.0);

        median_index = static_cast<Index>(last_sorted_vector.size() / 2);
        quartiles(2) = (last_sorted_vector(median_index-1) + last_sorted_vector(median_index)) / static_cast<type>(2.0);
    }
    else
    {
        quartiles(0) = sorted_vector(new_size/4);
        quartiles(1) = sorted_vector(new_size/2);
        quartiles(2) = sorted_vector(new_size*3/4);
    }

    return quartiles;
}



/// Returns the box and whispers for a vector.
/// @param vector Vector to be evaluated.

BoxPlot box_plot(const Tensor<type, 1>& vector)
{
    BoxPlot boxplot;

    if(vector.dimension(0) == 0) return boxplot;

    const Tensor<type, 1> quartiles = OpenNN::quartiles(vector);

    boxplot.minimum = minimum(vector);
    boxplot.first_quartile = quartiles(0);
    boxplot.median = quartiles(1);
    boxplot.third_quartile = quartiles(2);
    boxplot.maximum = maximum(vector);

    return boxplot;
}


/// Returns the box and whispers for the elements of the vector that correspond to the given indices.
/// @param vector Vector to be evaluated.
/// @param indices Indices of the elements of the vector to be evaluated.

BoxPlot box_plot(const Tensor<type, 1>& vector, const Tensor<Index, 1>& indices)
{
    BoxPlot boxplot;

    if(vector.dimension(0) == 0 || indices.dimension(0) == 0) return boxplot;

    const Tensor<type, 1> quartiles = OpenNN::quartiles(vector, indices);

    boxplot.minimum = minimum(vector, indices);
    boxplot.first_quartile = quartiles(0);
    boxplot.median = quartiles(1);
    boxplot.third_quartile = quartiles(2);
    boxplot.maximum = maximum(vector, indices);

    return boxplot;
}


/// This method bins the elements of the vector into a given number of equally
/// spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins.
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
/// @param vector Vector to obtain the histogram.
/// @param bins_number Number of bins to split the histogram.

Histogram histogram(const Tensor<type, 1>& vector, const Index &bins_number)
{
#ifdef __OPENNN_DEBUG__

    if(bins_number < 1)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "Histogram histogram(const Tensor<type, 1>&, "
               "const Index&) const method.\n"
               << "Number of bins is less than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    const Index size = vector.dimension(0);

    Tensor<type, 1> minimums(bins_number);
    Tensor<type, 1> maximums(bins_number);

    Tensor<type, 1> centers(bins_number);
    Tensor<Index, 1> frequencies(bins_number);
    frequencies.setZero();

    Index unique_values_number = 1;
    Tensor<type, 1> old_unique_values(1);
    Tensor<type, 1> unique_values(1);
    unique_values(0) = vector(0);
    old_unique_values = unique_values;

    for(Index i = 1; i < size; i++)
    {
        if(std::find(unique_values.data(), unique_values.data()+unique_values.size(), vector(i)) == unique_values.data()+unique_values.size())
        {
            unique_values_number++;

            unique_values.resize(unique_values_number);

            for(Index j = 0; j < unique_values_number-1; j++) unique_values(j) = old_unique_values(j);

            unique_values(unique_values_number-1) = vector(i);

            old_unique_values = unique_values;
        }

        if(unique_values_number > bins_number) break;
    }

    if(unique_values_number <= bins_number)
    {
        sort(unique_values.data(), unique_values.data() + unique_values.size(), less<type>());

        centers = unique_values;
        minimums = unique_values;
        maximums = unique_values;

        frequencies.resize(unique_values_number);
        frequencies.setZero();

        for(Index i = 0; i < size; i++)
        {
            if(isnan(vector(i))) continue;

            for(Index j = 0; j < unique_values_number; j++)
            {
                if(static_cast<Index>(vector(i)) == static_cast<Index>(centers(j)))
                {
                    frequencies(j)++;
                    break;
                }
            }
        }
    }
    else
    {
        const type min = minimum(vector);
        const type max = maximum(vector);

        const type length = (max - min) /static_cast<type>(bins_number);

        minimums(0) = min;
        maximums(0) = min + length;
        centers(0) = (maximums(0) + minimums(0)) /static_cast<type>(2.0);

        // Calculate bins center

        for(Index i = 1; i < bins_number; i++)
        {
            minimums(i) = minimums(i - 1) + length;
            maximums(i) = maximums(i - 1) + length;

            centers(i) = (maximums(i) + minimums(i)) /static_cast<type>(2.0);
        }

        // Calculate bins frequency

        const Index size = vector.dimension(0);

        for(Index i = 0; i < size; i++)
        {
            if(isnan(vector(i)))
            {
                continue;
            }

            for(Index j = 0; j < bins_number - 1; j++)
            {
                if(vector(i) >= minimums(j) && vector(i) < maximums(j))
                {
                    frequencies(j)++;
                    break;
                }
            }

            if(vector(i) >= minimums(bins_number - 1))
            {
                frequencies(bins_number - 1)++;
            }
        }
    }

    Histogram histogram;
    histogram.centers = centers;
    histogram.minimums = minimums;
    histogram.maximums = maximums;
    histogram.frequencies = frequencies;

    return histogram;
}


/// This method bins the elements of the vector into a given number of equally
/// spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins.
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
/// @param vector
/// @param center
/// @param bins_number


Histogram histogram_centered(const Tensor<type, 1>& vector, const type& center, const Index & bins_number)
{
#ifdef __OPENNN_DEBUG__

    if(bins_number < 1)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "Histogram histogram_centered(const Tensor<type, 1>&, "
               "const type&, const Index&) const method.\n"
               << "Number of bins is less than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    Index bin_center;

    if(bins_number%2 == 0)
    {
        bin_center = static_cast<Index>(static_cast<type>(bins_number)/static_cast<type>(2.0));
    }
    else
    {
        bin_center = static_cast<Index>(static_cast<type>(bins_number)/static_cast<type>(2.0) + static_cast<type>(0.5));
    }

    Tensor<type, 1> minimums(bins_number);
    Tensor<type, 1> maximums(bins_number);

    Tensor<type, 1> centers(bins_number);
    Tensor<Index, 1> frequencies(bins_number);
    frequencies.setZero();

    const type min = minimum(vector);
    const type max = maximum(vector);

    const type length = (max - min)/static_cast<type>(bins_number);

    minimums(bin_center-1) = center - length;
    maximums(bin_center-1) = center + length;
    centers(bin_center-1) = center;

    // Calculate bins center

    for(Index i = bin_center; i < bins_number; i++) // Upper centers
    {
        minimums(i) = minimums(i - 1) + length;
        maximums(i) = maximums(i - 1) + length;

        centers(i) = (maximums(i) + minimums(i)) /static_cast<type>(2.0);
    }

    for(Index i = static_cast<Index>(bin_center)-2; i >= 0; i--) // Lower centers
    {
        minimums(i) = minimums(i + 1) - length;
        maximums(i) = maximums(i + 1) - length;

        centers(i) = (maximums(i) + minimums(i)) /static_cast<type>(2.0);
    }

    // Calculate bins frequency

    const Index size = vector.dimension(0);

    for(Index i = 0; i < size; i++)
    {
        for(Index j = 0; j < bins_number - 1; j++)
        {
            if(vector(i) >= minimums(j) && vector(i) < maximums(j))
            {
                frequencies(j)++;
            }
        }

        if(vector(i) >= minimums(bins_number - 1))
        {
            frequencies(bins_number - 1)++;
        }
    }

    Histogram histogram(bins_number);
    histogram.centers = centers;
    histogram.minimums = minimums;
    histogram.maximums = maximums;
    histogram.frequencies = frequencies;

    return histogram;
}


/// This method bins the elements of the vector into a given number of equally
/// spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins.
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
/// @todo isnan is not defined for bool.

Histogram histogram(const Tensor<bool, 1>& v)
{
    Tensor<type, 1> minimums(2);
    minimums.setZero();
    Tensor<type, 1> maximums(2);
    maximums.setConstant(1);

    Tensor<type, 1> centers(2);
    centers.setValues({0,1});
    Tensor<Index, 1> frequencies(2);
    frequencies.setZero();

    // Calculate bins frequency

    const Index size = v.dimension(0);

    for(Index i = 0; i < size; i++)
    {        
//        if(isnan(v(i))) continue;

        for(Index j = 0; j < 2; j++)
        {
            if(static_cast<Index>(v(i)) == static_cast<Index>(minimums(j)))
            {
                frequencies(j)++;
            }
        }
    }

    Histogram histogram(2);
    histogram.centers = centers;
    histogram.minimums = minimums;
    histogram.maximums = maximums;
    histogram.frequencies = frequencies;

//    Histogram histogram;
    return histogram;
}


/// This method bins the elements of the vector into a given number of equally
/// spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins.
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
/// @param vector
/// @param bins_number

Histogram histogram(const Tensor<Index, 1>& vector, const Index& bins_number)
{
#ifdef __OPENNN_DEBUG__

    if(bins_number < 1)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "Histogram calculate_histogram_integers(const Tensor<Index, 1>&, "
               "const Index&) const method.\n"
               << "Number of bins is less than one.\n";

        throw logic_error(buffer.str());
    }

#endif
/*
    Tensor<Index, 1> centers = vector.get_integer_elements(bins_number);
    const Index centers_number = centers.size();

    sort(centers.data(), centers.data() + centers.size(), less<Index>());

    Tensor<type, 1> minimums(centers_number);
    Tensor<type, 1> maximums(centers_number);
    Tensor<Index, 1> frequencies(centers_number);

    for(Index i = 0; i < centers_number; i++)
    {
      minimums(i) = centers(i);
      maximums(i) = centers(i);
      frequencies(i) = vector.count_equal_to(centers(i));
    }

    Histogram histogram(centers_number);
    histogram.centers = centers.cast<type>();
    histogram.minimums = minimums;
    histogram.maximums = maximums;
    histogram.frequencies = frequencies;

    return histogram;
    */

    return Histogram();
}


/// Returns a vector containing the sum of the frequencies of the bins to which
/// this vector belongs.
/// @param histograms Used histograms.

Tensor<Index, 1> total_frequencies(const Tensor<Histogram, 1>&histograms)
{
    const Index histograms_number = histograms.size();

    Tensor<Index, 1> total_frequencies(histograms_number);

    for(Index i = 0; i < histograms_number; i++)
    {
        total_frequencies(i) = histograms(i).frequencies(i);
    }

    return total_frequencies;
}


/// Calculates a histogram for each column, each having a given number of bins.
/// It returns a vector of vectors.
/// The size of the main vector is the number of columns.
/// Each subvector contains the frequencies and centers of that colums.
/// @param matrix Data to calculate histograms
/// @param bins_number Number of bins for each histogram.

Tensor<Histogram, 1> histograms(const Tensor<type, 2>& matrix, const Index& bins_number)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    Tensor<Histogram, 1> histograms(columns_number);

    Tensor<type, 1> column(rows_number);

    for(Index i = 0; i < columns_number; i++)
    {
        column = matrix.chip(i,1);

        histograms(i) = histogram(column, bins_number);

        /*
              if(column.is_binary())
              {
                  histograms(i) = histogram(column.to_bool_vector());
              }
              else
              {
                  histograms(i) = histogram(column, bins_number);
              }
        */
    }

    return histograms;
}


/// Returns the basic descriptives of the columns.
/// The format is a vector of descriptives structures.
/// The size of that vector is equal to the number of columns in this matrix.
/// @param matrix Used matrix.

Tensor<Descriptives, 1> descriptives(const Tensor<type, 2>& matrix)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

#ifdef __OPENNN_DEBUG__

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "Tensor<Descriptives, 1> descriptives(const Tensor<type, 2>&) "
               "const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    Tensor<Descriptives, 1> descriptives(columns_number);

    Tensor<type, 1> column(rows_number);

    #pragma omp parallel for private(column)

    for(Index i = 0; i < columns_number; i++)
    {
        column = matrix.chip(i,1);

        descriptives(i) = OpenNN::descriptives(column);
    }

    return descriptives;
}


/// Returns the basic descriptives of given columns for given rows.
/// The format is a vector of descriptives structures.
/// The size of that vector is equal to the number of given columns.
/// @param row_indices Indices of the rows for which the descriptives are to be computed.
/// @param columns_indices Indices of the columns for which the descriptives are to be computed.

Tensor<Descriptives, 1> descriptives(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& row_indices, const Tensor<Index, 1>& columns_indices)
{
    const Index row_indices_size = row_indices.size();
    const Index columns_indices_size = columns_indices.size();

    Tensor<Descriptives, 1> descriptives(columns_indices_size);

    Index row_index, column_index;

    Tensor<type, 1> minimums(columns_indices_size);
    minimums.setConstant(numeric_limits<type>::max());

    Tensor<type, 1> maximums(columns_indices_size);
    maximums.setConstant(numeric_limits<type>::min());

    Tensor<type, 1> sums(columns_indices_size);
    Tensor<type, 1> squared_sums(columns_indices_size);
    Tensor<Index, 1> count(columns_indices_size);

    sums.setZero();
    squared_sums.setZero();
    count.setZero();

    for(Index i = 0; i < row_indices_size; i++)
    {
        row_index = row_indices(i);

        #pragma omp parallel for private(column_index)

        for(Index j = 0; j < columns_indices_size; j++)
        {
            column_index = columns_indices(j);

            if(isnan((matrix(row_index,column_index)))) continue;

            if(matrix(row_index,column_index) < minimums(j))
            {
                minimums(j) = matrix(row_index,column_index);
            }

            if(matrix(row_index,column_index) > maximums(j))
            {
                maximums(j) = matrix(row_index,column_index);
            }

            sums(j) += matrix(row_index,column_index);
            squared_sums(j) += matrix(row_index,column_index)*matrix(row_index,column_index);
            count(j)++;
        }
    }

    const Tensor<type, 1> mean = sums/count;

    Tensor<type, 1> standard_deviation(columns_indices_size);

    if(row_indices_size > 1)
    {
        for(Index i = 0; i < columns_indices_size; i++)
        {
            const type numerator = squared_sums(i) -(sums(i) * sums(i)) / count(i);
            const type denominator = static_cast<type>(count(i) - 1);

            standard_deviation(i) = numerator / denominator;

            standard_deviation(i) = sqrt(standard_deviation(i));
        }
    }

    for(Index i = 0; i < columns_indices_size; i++)
    {
        descriptives(i).minimum = minimums(i);
        descriptives(i).maximum = maximums(i);
        descriptives(i).mean = mean(i);
        descriptives(i).standard_deviation = standard_deviation(i);
    }

    return descriptives;
}


/// Returns the means of given rows.
/// The format is a vector of type values.
/// The size of that vector is equal to the number of given rows.
/// @param matrix Used matrix.
/// @param columns_indices Indices of the columns for which the descriptives are to be computed.

Tensor<type, 1> rows_means(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& row_indices)
{
    const Index columns_number = matrix.dimension(1);

    Tensor<Index, 1> used_row_indices;

    if(matrix.dimension(0) == 0 && matrix.dimension(1) == 0)
    {
        used_row_indices.resize(matrix.dimension(0));
    }
    else
    {
        used_row_indices = row_indices;
    }

    const Index row_indices_size = used_row_indices.size();

    Tensor<type, 1> means(columns_number);

    Tensor<type, 1> column(row_indices_size);

    for(Index i = 0; i < columns_number; i++)
    {
        for(Index j = 0; j < row_indices_size; j++)
        {
            Index row_index = row_indices(j);

            column(j) = matrix(row_index,i);
        }

        means(i) = mean(column);
    }

    return means;
}


/// Returns the minimums values of given columns.
/// The format is a vector of type values.
/// The size of that vector is equal to the number of given columns.
/// @param matrix Used matrix.
/// @param rows_indices Indices of the rows for which the minimums are to be computed.
/// @param columns_indices Indices of the columns for which the minimums are to be computed.

Tensor<type, 1> columns_minimums(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& rows_indices, const Tensor<Index, 1>& columns_indices)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    Tensor<Index, 1> used_columns_indices;

    if(columns_indices.dimension(0) == 0)
    {
        used_columns_indices.resize(columns_number);

        for (Index i = 0; i < columns_number; i++)
        {
            used_columns_indices(i) = i;
        }
    }
    else
    {
        used_columns_indices = columns_indices;
    }

    Tensor<Index, 1> used_rows_indices;

    if(rows_indices.dimension(0) == 0)
    {
        used_rows_indices.resize(rows_number);

        for (Index i = 0; i < rows_number; i++)
        {
            used_rows_indices(i) = i;
        }
    }
    else
    {
        used_rows_indices = rows_indices;
    }

    const Index rows_indices_size = used_rows_indices.size();
    const Index columns_indices_size = used_columns_indices.size();

    Tensor<type, 1> minimums(columns_indices_size);

    Index row_index;
    Index column_index;

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = used_columns_indices(j);

        Tensor<type, 1> column(rows_indices_size);

        for(Index i = 0; i < rows_indices_size; i++)
        {
            row_index = used_rows_indices(i);

            column(i) = matrix(row_index,column_index);
        }

        minimums(j) = minimum(column);
    }

    return minimums;
}


/// Returns the maximums values of given columns.
/// The format is a vector of type values.
/// The size of that vector is equal to the number of given columns.
/// @param matrix Used matrix.
/// @param columns_indices Indices of the columns for which the descriptives are to be computed.

Tensor<type, 1> columns_maximums(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& columns_indices)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    Tensor<Index, 1> used_columns_indices;

    if(columns_indices.dimension(0) == 0 && columns_indices.dimension(1) == 0)
    {
        used_columns_indices.resize(columns_number);
    }
    else
    {
        used_columns_indices = columns_indices;
    }

    const Index columns_indices_size = used_columns_indices.size();

    Tensor<type, 1> maximums(columns_indices_size);

    Index column_index;
    Tensor<type, 1> column(rows_number);

    for(Index i = 0; i < columns_indices_size; i++)
    {
        column_index = used_columns_indices(i);

        column = matrix.chip(column_index,1);

        maximums(i) = maximum(column);
    }

    return maximums;
}


type range(const Tensor<type, 1>& vector)
{
    const type min = minimum(vector);
    const type max = maximum(vector);

    return abs(max - min);
}

/*
/// Calculates the box plots for a set of rows of each of the given columns of this matrix.
/// @param matrix Used matrix.
/// @param rows_indices Rows to be used for the box plot.
/// @param columns_indices Indices of the columns for which box plots are going to be calculated.
/// @todo remove?

Tensor<BoxPlot, 1> box_plots(const Tensor<type, 2>& matrix, const Tensor<Tensor<Index, 1>, 1>& rows_indices, const Tensor<Index, 1>& columns_indices)
{
    const Index columns_number = columns_indices.size();

#ifdef __OPENNN_DEBUG__

    if(columns_number == rows_indices.size())
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class."
               << "void box_plots(const Tensor<type, 2>&, "
               "const Tensor<Tensor<Index, 1>, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size of row indices must be equal to the number of columns.\n";

        throw logic_error(buffer.str());
    }

#endif

    Tensor<BoxPlot, 1> box_plots(columns_number);

    for(Index i = 0; i < matrix.dimension(1); i++)
    {


    }

        Tensor<type, 1> column;

         #pragma omp parallel for private(column)

        for(Index i = 0; i < columns_number; i++)
        {
            box_plots(i).resize(5);

            const Index rows_number = rows_indices(i).size();

            column = matrix.get_column(columns_indices(i)).get_subvector(rows_indices(i));

            sort(column.begin(), column.end(), less<type>());

            // Minimum

            box_plots(i)[0] = column[0];

            if(rows_number % 2 == 0)
            {
                // First quartile

                box_plots(i)[1] = (column[rows_number / 4] + column[rows_number / 4 + 1]) /static_cast<type>(2.0);

                // Second quartile

                box_plots(i)[2] = (column[rows_number * 2 / 4] +
                               column[rows_number * 2 / 4 + 1]) /
                              2.0;

                // Third quartile

                box_plots(i)[3] = (column[rows_number * 3 / 4] +
                               column[rows_number * 3 / 4 + 1]) /
                              2.0;
            }
            else
            {
                // First quartile

                box_plots(i)[1] = column[rows_number / 4];

                // Second quartile

                box_plots(i)[2] = column[rows_number * 2 / 4];

                //Third quartile

                box_plots(i)[3] = column[rows_number * 3 / 4];
            }

            // Maximum

            box_plots(i)[4] = column[rows_number-1];
        }

    return box_plots;
}
*/

/// Returns the minimum, maximum, mean and standard deviation of the elements in the vector.
/// @param vector Vector to be evaluated.

Descriptives descriptives(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics Class.\n"
               << "type descriptives(const Tensor<type, 1>&, "
               "const Tensor<Index, 1>&).\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

#endif

    Descriptives descriptives;

    type minimum = numeric_limits<type>::max();
    type maximum;

    type sum = 0;
    type squared_sum = 0;
    Index count = 0;

    maximum = -numeric_limits<type>::max();

    for(Index i = 0; i < size; i++)
    {
        if(!::isnan(vector(i)))
        {
            if(vector(i) < minimum)
            {
                minimum = vector(i);
            }

            if(vector(i) > maximum)
            {
                maximum = vector(i);
            }

            sum += vector(i);
            squared_sum += vector(i) *vector(i);

            count++;
        }
    }

    const type mean = sum/static_cast<type>(count);

    type standard_deviation;

    if(count <= 1)
    {
        standard_deviation = 0;
    }
    else
    {
        const type numerator = squared_sum -(sum * sum) / count;
        const type denominator = size - static_cast<type>(1.0);

        standard_deviation = numerator / denominator;
    }

    standard_deviation = sqrt(standard_deviation);

    descriptives.minimum = minimum;
    descriptives.maximum = maximum;
    descriptives.mean = mean;
    descriptives.standard_deviation = standard_deviation;

    return descriptives;
}


/// Calculates the distance between the empirical distribution of the vector and
/// the normal, half-normal and uniform cumulative distribution. It returns 0, 1
/// or 2 if the closest distribution is the normal, half-normal or the uniform,
/// respectively.
/// @todo review.

Index perform_distribution_distance_analysis(const Tensor<type, 1>& vector)
{
    Tensor<type, 1> distances(2);
    distances.setZero();

    const Index nans = count_nan(vector);

    const Index new_size = vector.size() - nans;

    Tensor<type, 1> new_vector(new_size);

    Index index = 0;

    for(Index i = 0; i < vector.size(); i++)
    {
        if(!::isnan(vector(i)))
        {
            new_vector(index) = vector(i);
            index++;
        }
    }

    const Index n = vector.dimension(0);

    Tensor<type, 1> sorted_vector(new_vector);

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    const Descriptives descriptives = OpenNN::descriptives(vector);

    const type mean = descriptives.mean;
    const type standard_deviation = descriptives.standard_deviation;
    const type minimum = sorted_vector(0);
    const type maximum = sorted_vector(n-1);

    #pragma omp parallel for schedule(dynamic)

    for(Index i = 0; i < n; i++)
    {
        const type normal_distribution = static_cast<type>(0.5)
                * static_cast<type>(erfc((mean - sorted_vector(i)))/static_cast<type>((standard_deviation*static_cast<type>(sqrt(2)))));

        const type uniform_distribution = (sorted_vector(i)-minimum)/(maximum-minimum);

        type empirical_distribution;

        Index counter = 0;

        if(vector(i) < sorted_vector(0))
        {
            empirical_distribution = 0;
        }
        else if(vector(i) >= sorted_vector(n-1))
        {
            empirical_distribution = 1.0;
        }
        else
        {
            counter = static_cast<Index>(i + 1);

            for(Index j = i+1; j < n; j++)
            {
                if(sorted_vector(j) <= sorted_vector(i))
                {
                    counter++;
                }
                else
                {
                    break;
                }
            }

            empirical_distribution = static_cast<type>(counter)/static_cast<type>(n);
        }

        #pragma omp critical
        {
            distances(0) += abs(normal_distribution - empirical_distribution);
            distances(1) += abs(uniform_distribution - empirical_distribution);
        }
    }

    return minimal_index(distances);
}


/*
/// Returns a vector with the mean values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.
/// @param matrix Matrix used.
/// @todo to delete.

Tensor<type, 1> columns_mean(const Tensor<type, 2>& matrix)
{

    const Index rows_number = matrix.dimension(0);

    const Index columns_number = matrix.dimension(1);

#ifdef __OPENNN_DEBUG__

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "Tensor<type, 1> mean(const Tensor<type, 2>&) const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    Tensor<type, 1> columns_mean(columns_number);

    for(Index i = 0; i < columns_number; i++)
    {
        Tensor<type, 0> mean = matrix.chip(i,1).mean();

        columns_mean(i) = mean(0);
    }

    return columns_mean;
}

*/
/// Returns a vector with the mean values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.
/// @param matrix Matrix used.

Tensor<type, 1> mean(const Tensor<type, 2>& matrix)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

#ifdef __OPENNN_DEBUG__

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "Tensor<type, 1> mean(const Tensor<type, 2>&) const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Mean

    Tensor<type, 1> mean(columns_number);
    mean.setZero();

    for(Index j = 0; j < columns_number; j++)
    {
        for(Index i = 0; i < rows_number; i++)
        {
            if(!::isnan(matrix(i,j)))
            {
                mean(j) += matrix(i,j);
            }
        }

        mean(j) /= static_cast<type>(rows_number);
    }

    return mean;
}


/// Returns a vector with the mean values of given columns.
/// The size of the vector is equal to the size of the column indices vector.
/// @param columns_indices Indices of columns.

Tensor<type, 1> mean(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& columns_indices)
{
    const Index rows_number = matrix.dimension(0);

    const Index columns_indices_size = columns_indices.size();

    Index column_index;

    // Mean

    Tensor<type, 1> mean(columns_indices_size);
    mean.setZero();

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = columns_indices(j);

        for(Index i = 0; i < rows_number; i++)
        {
            mean(j) += matrix(i, column_index);
        }

        mean(j) /= static_cast<type>(rows_number);
    }

    return mean;
}


/// Returns a vector with the mean values of given columns for given rows.
/// The size of the vector is equal to the size of the column indices vector.
/// @param matrix Matrix used.
/// @param row_indices Indices of rows.
/// @param columns_indices Indices of columns.

Tensor<type, 1> mean(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& row_indices, const Tensor<Index, 1>& columns_indices)
{
    const Index row_indices_size = row_indices.size();
    const Index columns_indices_size = columns_indices.size();

#ifdef __OPENNN_DEBUG__

    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    // Rows check

    if(row_indices_size > rows_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "Tensor<type, 1> mean(const Tensor<type, 2>& matrix, "
               "const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size of row indices(" << row_indices_size << ") is greater than number of rows(" << rows_number << ").\n";

        throw logic_error(buffer.str());
    }

    for(Index i = 0; i < row_indices_size; i++)
    {
        if(row_indices(i) >= rows_number)
        {
            ostringstream buffer;

            buffer << "OpenNN Exception: Statistics class.\n"
                   << "Tensor<type, 1> mean(const Tensor<type, 2>& matrix, "
                   "const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
                   << "Row index " << i << " must be less than rows number.\n";

            throw logic_error(buffer.str());
        }
    }

    if(row_indices_size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "Tensor<type, 1> mean(const Tensor<type, 2>& matrix, "
               "const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size of row indices must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

    // Columns check

    if(columns_indices_size > columns_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "Tensor<type, 1> mean(const Tensor<type, 2>& matrix, "
               "const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Column indices size must be equal or less than columns number.\n";

        throw logic_error(buffer.str());
    }

    for(Index i = 0; i < columns_indices_size; i++)
    {
        if(columns_indices(i) >= columns_number)
        {
            ostringstream buffer;

            buffer << "OpenNN Exception: Statistics class.\n"
                   << "Tensor<type, 1> mean(const Tensor<type, 2>& matrix, "
                   "const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
                   << "Column index " << i << " must be less than columns number.\n";

            throw logic_error(buffer.str());
        }
    }

#endif

    Index row_index;
    Index column_index;

    Index count = 0;

    // Mean

    Tensor<type, 1> mean(columns_indices_size);
    mean.setZero();

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = columns_indices(j);

        for(Index i = 0; i < row_indices_size; i++)
        {
            row_index = row_indices(i);

            if(!::isnan(matrix(row_index,column_index)))
            {
                mean(j) += matrix(row_index,column_index);
                count++;
            }
        }

        mean(j) /= static_cast<type>(count);
    }

    return mean;
}


/// Returns a vector with the mean values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.

type mean(const Tensor<type, 2>& matrix, const Index& column_index)
{
    const Index rows_number = matrix.dimension(0);

#ifdef __OPENNN_DEBUG__

    const Index columns_number = matrix.dimension(1);

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "type mean(const Tensor<type, 2>&, const Index&) const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

    if(column_index >= columns_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Statistics class.\n"
               << "type mean(const Tensor<type, 2>&, const Index&) const method.\n"
               << "Index of column must be less than number of columns.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Mean

    type mean = 0;

    Index count = 0;

    for(Index i = 0; i < rows_number; i++)
    {
        if(!::isnan(matrix(i,column_index)))
        {
            mean += matrix(i,column_index);
            count++;
        }
    }

    mean /= static_cast<type>(count);

    return mean;
}


/// Returns a vector with the median values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.

Tensor<type, 1> median(const Tensor<type, 2>& matrix)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

#ifdef __OPENNN_DEBUG__

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "Tensor<type, 1> median() const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

#endif

    // median

    Tensor<type, 1> median(columns_number);

    for(Index j = 0; j < columns_number; j++)
    {
        Tensor<type, 1> sorted_column(matrix.chip(j,1));

        sort(sorted_column.data(), sorted_column.data() + sorted_column.size(), less<type>());

        if(rows_number % 2 == 0)
        {
            median(j) = (sorted_column[rows_number*2/4] + sorted_column[rows_number*2/4+1])/2;
        }
        else
        {
            median(j) = sorted_column[rows_number*2/4];
        }
    }

    return median;
}


/// Returns a vector with the median values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.

type median(const Tensor<type, 2>& matrix, const Index& column_index)
{
    const Index rows_number = matrix.dimension(0);    

#ifdef __OPENNN_DEBUG__

    const Index columns_number = matrix.dimension(1);

    if(rows_number == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "type median(const Index&) const method.\n"
               << "Number of rows must be greater than one.\n";

        throw logic_error(buffer.str());
    }

    if(column_index >= columns_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "type median(const Index&) const method.\n"
               << "Index of column must be less than number of columns.\n";

        throw logic_error(buffer.str());
    }

#endif

    // median

    type median = 0;

    Tensor<type, 1> sorted_column(matrix.chip(column_index,1));

    sort(sorted_column.data(), sorted_column.data() + sorted_column.size(), less<type>());

    if(rows_number % 2 == 0)
    {
        median = (sorted_column[rows_number*2/4] + sorted_column[rows_number*2/4+1])/2;
    }
    else
    {
        median = sorted_column[rows_number*2/4];
    }

    return median;
}


/// Returns a vector with the median values of given columns.
/// The size of the vector is equal to the size of the column indices vector.
/// @param columns_indices Indices of columns.


Tensor<type, 1> median(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& columns_indices)
{
    const Index rows_number = matrix.dimension(0);

    const Index columns_indices_size = columns_indices.size();

    Index column_index;

    // median

    Tensor<type, 1> median(columns_indices_size);

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = columns_indices(j);

        Tensor<type, 1> sorted_column(matrix.chip(column_index, 1));

        sort(sorted_column.data(), sorted_column.data() + sorted_column.size(), less<type>());

        if(rows_number % 2 == 0)
        {
            median(j) = (sorted_column[rows_number*2/4] + sorted_column[rows_number*2/4+1])/2;
        }
        else
        {
            median(j) = sorted_column[rows_number*2/4];
        }
    }

    return median;
}


/// Returns a vector with the median values of given columns for given rows.
/// The size of the vector is equal to the size of the column indices vector.
/// @param row_indices Indices of rows.
/// @param columns_indices Indices of columns.

Tensor<type, 1> median(const Tensor<type, 2>& matrix, const Tensor<Index, 1>& row_indices, const Tensor<Index, 1>& columns_indices)
{

    const Index row_indices_size = row_indices.size();
    const Index columns_indices_size = columns_indices.size();

#ifdef __OPENNN_DEBUG__

    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    // Rows check

    if(row_indices_size > rows_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "Tensor<type, 1> median(const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size of row indices(" << row_indices_size << ") is greater than number of rows(" << rows_number << ").\n";

        throw logic_error(buffer.str());
    }

    for(Index i = 0; i < row_indices_size; i++)
    {
        if(row_indices(i) >= rows_number)
        {
            ostringstream buffer;

            buffer << "OpenNN Exception: Matrix template.\n"
                   << "Tensor<type, 1> median(const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
                   << "Row index " << i << " must be less than rows number.\n";

            throw logic_error(buffer.str());
        }
    }

    if(row_indices_size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "Tensor<type, 1> median(const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Size of row indices must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

    // Columns check

    if(columns_indices_size > columns_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: Matrix template.\n"
               << "Tensor<type, 1> median(const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
               << "Column indices size must be equal or less than columns number.\n";

        throw logic_error(buffer.str());
    }

    for(Index i = 0; i < columns_indices_size; i++)
    {
        if(columns_indices(i) >= columns_number)
        {
            ostringstream buffer;

            buffer << "OpenNN Exception: Matrix template.\n"
                   << "Tensor<type, 1> median(const Tensor<Index, 1>&, const Tensor<Index, 1>&) const method.\n"
                   << "Column index " << i << " must be less than columns number.\n";

            throw logic_error(buffer.str());
        }
    }

#endif

    Index column_index;

    // median

    Tensor<type, 1> median(columns_indices_size);

    for(Index j = 0; j < columns_indices_size; j++)
    {
        column_index = columns_indices(j);

        Tensor<type, 1> sorted_column(row_indices_size);

        for(Index k = 0; k < row_indices_size; k++)
        {
            const Index row_index = row_indices(k);

            sorted_column(k) = matrix(row_index, column_index);
        }

        sort(sorted_column.data(), sorted_column.data() + sorted_column.size(), less<type>());

        if(row_indices_size % 2 == 0)
        {
            median(j) = (sorted_column[row_indices_size*2/4] + sorted_column[row_indices_size*2/4 + 1])/2;
        }
        else
        {
            median(j) = sorted_column[row_indices_size * 2 / 4];
        }
    }

    return median;
}


/// Calculates the distance between the empirical distribution of the vector and the
/// normal distribution.
/// @param vector Vector to be evaluated.

type normal_distribution_distance(const Tensor<type, 1>& vector)
{
    type normal_distribution_distance = 0;

    const Index n = vector.dimension(0);

    const type mean_value = mean(vector);
    const type standard_deviation = OpenNN::standard_deviation(vector);

    type normal_distribution; // Normal distribution
    type empirical_distribution; // Empirical distribution

    Tensor<type, 1> sorted_vector(vector);

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    Index counter = 0;

    for(Index i = 0; i < n; i++)
    {
        normal_distribution = static_cast<type>(0.5) * static_cast<type>(erfc((mean_value - sorted_vector(i)))/(standard_deviation*static_cast<type>(sqrt(2.0))));
        counter = 0;

        for(Index j = 0; j < n; j++)
        {
            if(sorted_vector(j) <= sorted_vector(i))
            {
                counter++;
            }
            else
            {
                break;
            }
        }

        empirical_distribution = static_cast<type>(counter)/static_cast<type>(n);

        normal_distribution_distance += abs(normal_distribution - empirical_distribution);
    }

    return normal_distribution_distance;
}


/// Calculates the distance between the empirical distribution of the vector and the
/// half normal distribution.
/// @param vector Vector to be evaluated.

type half_normal_distribution_distance(const Tensor<type, 1>& vector)
{
    type half_normal_distribution_distance = 0;

    const Index n = vector.dimension(0);

    const type standard_deviation = OpenNN::standard_deviation(vector);

    type half_normal_distribution; // Half normal distribution
    type empirical_distribution; // Empirical distribution

    Tensor<type, 1> sorted_vector(vector);

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    Index counter = 0;

    for(Index i = 0; i < n; i++)
    {
        half_normal_distribution = static_cast<type>(erf((sorted_vector(i)))/(standard_deviation * static_cast<type>(sqrt(2))));
        counter = 0;

        for(Index j = 0; j < n; j++)
        {
            if(sorted_vector(j) <= sorted_vector(i))
            {
                counter++;
            }
            else
            {
                break;
            }
        }

        empirical_distribution = static_cast<type>(counter)/static_cast<type>(n);

        half_normal_distribution_distance += abs(half_normal_distribution - empirical_distribution);
    }

    return half_normal_distribution_distance;
}


/// Calculates the distance between the empirical distribution of the vector and the
/// uniform distribution.
/// @param vector Vector to be evaluated.

type uniform_distribution_distance(const Tensor<type, 1>& vector)
{
    type uniform_distribution_distance = 0;

    const Index n = vector.dimension(0);

    type uniform_distribution; // Uniform distribution
    type empirical_distribution; // Empirical distribution

    Tensor<type, 1> sorted_vector(vector);

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    const type minimum = sorted_vector[0];
    const type maximum = sorted_vector[n-1];

    Index counter = 0;

    for(Index i = 0; i < n; i++)
    {
        uniform_distribution = (sorted_vector(i)-minimum)/(maximum-minimum);
        counter = 0;

        for(Index j = 0; j < n; j++)
        {
            if(sorted_vector(j) <= sorted_vector(i))
            {
                counter++;
            }
            else
            {
                break;
            }
        }

        empirical_distribution = static_cast<type>(counter)/static_cast<type>(n);

        uniform_distribution_distance += abs(uniform_distribution - empirical_distribution);
    }

    return uniform_distribution_distance;
}


///@todo

type normality_parameter(const Tensor<type, 1>& vector)
{
    const type max = maximum(vector);
    const type min = minimum(vector);

    const Index n = vector.dimension(0);

    const type mean_value = mean(vector);
    const type standard_deviation = OpenNN::standard_deviation(vector);

    type normal_distribution;
    type empirical_distribution;
    type previous_normal_distribution = 0;
    type previous_empirical_distribution = 0;

    Tensor<type, 1> sorted_vector(vector);

    sort(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), less<type>());

    type empirical_area = 0;
    type normal_area = 0;

    Index counter = 0;

    for(Index i = 0; i < n; i++)
    {
        normal_distribution = static_cast<type>(0.5) * static_cast<type>(erfc((mean_value - sorted_vector(i)))/(standard_deviation*static_cast<type>(sqrt(2.0))));
        counter = 0;

        for(Index j = 0; j < n; j++)
        {
            if(sorted_vector(j) <= sorted_vector(i))
            {
                counter++;
            }
            else
            {
                break;
            }
        }

        empirical_distribution = static_cast<type>(counter)/static_cast<type>(n);

        if(i == 0)
        {
            previous_normal_distribution = normal_distribution;
            previous_empirical_distribution = empirical_distribution;
        }
        else
        {
            normal_area += static_cast<type>(0.5)*(sorted_vector(i)-sorted_vector[i-1])*(normal_distribution+previous_normal_distribution);
            empirical_area += static_cast<type>(0.5)*(sorted_vector(i)-sorted_vector[i-1])*(empirical_distribution+previous_empirical_distribution);

            previous_normal_distribution = normal_distribution;
            previous_empirical_distribution = empirical_distribution;
        }
    }

    const type uniform_area = (max - min)/static_cast<type>(2.0);

    return uniform_area;
}


Tensor<type, 1> variation_percentage(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    Tensor<type, 1> new_vector(size);

    for(Index i = 1; i < size; i++)
    {
        if(abs(vector[i-1]) < numeric_limits<type>::min())
        {
            new_vector(i) = (vector(i) - vector[i-1])*static_cast<type>(100.0)/vector[i-1];
        }
    }

    return new_vector;
}


/// Returns the index of the smallest element in the vector.

Index minimal_index(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    if(size == 0) return Index();

    Index minimal_index = 0;
    type minimum = vector[0];

    for(Index i = 1; i < size; i++)
    {
        if(vector(i) < minimum)
        {
            minimal_index = i;
            minimum = vector(i);
        }
    }

    return minimal_index;
}


/// Returns the index of the largest element in the vector.

Index maximal_index(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    if(size == 0) return Index();

    Index maximal_index = 0;
    type maximum = vector[0];

    for(Index i = 1; i < size; i++)
    {
        if(vector(i) > maximum)
        {
            maximal_index = i;
            maximum = vector(i);
        }
    }

    return maximal_index;
}

/// Returns the indices of the smallest elements in the vector.
/// @param number Number of minimal indices to be computed.

Tensor<Index, 1> minimal_indices(const Tensor<type, 1>& vector, const Index &number)
{
    Eigen::Tensor<type, 1> vector_ = vector;

    const Index size = vector.dimension(0);
    Tensor<Index, 1> minimal_indices(number);
    Eigen::Tensor<type, 0> maxim = vector.maximum();

#ifdef __OPENNN_DEBUG__

if(number > size)
{
   ostringstream buffer;

   buffer << "OpenNN Exception: Statistics class.\n"
          << "Tensor<Index, 1> minimal_indices(Tensor<type, 1>& , const Index &) \n"
          << "Number of minimal indices to be computed must be lower (or equal) than the size of the imput vector.\n";

   throw logic_error(buffer.str());
}
#endif

    for(Index j = 0; j < number; j++)
    {
        Index minimal_index = 0;
        type minimum = vector_(0);

        for(Index i = 0; i < size; i++)
        {
            if(vector_(i) < minimum)
            {
                minimal_index = i;
                minimum = vector_(i);
            }
        }
        vector_(minimal_index) = maxim(0)+1;
        minimal_indices(j) = minimal_index;
    }
      return minimal_indices;
}


/// Returns the indices of the largest elements in the vector.
/// @param number Number of maximal indices to be computed.

Tensor<Index, 1> maximal_indices(const Tensor<type, 1>& vector, const Index &number)
{
    Eigen::Tensor<type, 1> vector_ = vector;

    const Index size = vector.dimension(0);
    Tensor<Index, 1> maximal_indices(number);
    Eigen::Tensor<type, 0> minim = vector.minimum();

#ifdef __OPENNN_DEBUG__

if(number > size)
{
   ostringstream buffer;

   buffer << "OpenNN Exception: Statistics class.\n"
          << "Tensor<Index, 1> maximal_indices(Tensor<type, 1>& , const Index &) \n"
          << "Number of maximal indices to be computed must be lower (or equal) than the size of the imput vector.\n";

   throw logic_error(buffer.str());
}
#endif

    for(Index j = 0; j < number; j++)
    {
        Index maximal_index = 0;
        type maximal = vector_(0);

        for(Index i = 0; i < size; i++)
        {
            if(vector_(i) > maximal)
            {
                maximal_index = i;
                maximal = vector_(i);
            }
        }
        vector_(maximal_index) = minim(0)-1;
        maximal_indices(j) = maximal_index;
    }
      return maximal_indices;
}

/// Returns the row and column indices corresponding to the entry with minimum value.

Tensor<Index, 1> minimal_indices(const Tensor<type, 2>& matrix)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    type minimum = matrix(0,0);
    Tensor<Index, 1> minimal_indices(2);

    for(Index i = 0; i < rows_number; i++)
    {
        for(Index j = 0; j < columns_number; j++)
        {
            if(!::isnan(matrix(i,j))  && matrix(i,j) < minimum)
            {
                minimum = matrix(i,j);
                minimal_indices(0) = i;
                minimal_indices(1) = j;
            }
        }
    }

    return minimal_indices;
}


/// Returns the row and column indices corresponding to the entry with maximum value.

Tensor<Index, 1> maximal_indices(const Tensor<type, 2>& matrix)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    type maximum = matrix(0,0);

    Tensor<Index, 1> maximal_indices(2);

    for(Index i = 0; i < rows_number; i++)
    {
        for(Index j = 0; j < columns_number; j++)
        {
            if(!::isnan(matrix(i,j)) && matrix(i,j) > maximum)
            {
                maximum = matrix(i,j);
                maximal_indices(0) = i;
                maximal_indices(1) = j;
            }
        }
    }

    return maximal_indices;
}


/// Returns a matrix in which each of the columns contain the maximal indices of each of the columns of the
/// original matrix.

Tensor<Index, 2> maximal_columns_indices(const Tensor<type,2>& matrix, const Index& maximum_number)
{
    const Index rows_number = matrix.dimension(0);
    const Index columns_number = matrix.dimension(1);

    Tensor<Index, 2> maximal_columns_indices(maximum_number, columns_number);

    Tensor<type, 1> columns_minimums = OpenNN::columns_minimums(matrix);

    for(Index j = 0; j < columns_number; j++)
    {
        Tensor<type, 1> column = matrix.chip(j,1);

        for(Index i = 0; i < maximum_number; i++)
        {
            Index maximal_index = 0;
            type maximal = column(0);

            for(Index k = 0; k < rows_number; k++)
            {
                if(column(k) > maximal && !::isnan(column(k)))
                {
                    maximal_index = k;
                    maximal = column(k);
                }
            }

            column(maximal_index) = columns_minimums(j)-static_cast<type>(1);
            maximal_columns_indices(i,j) = maximal_index;
        }
    }

    return maximal_columns_indices;
}


type strongest(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

    if(size == 0) return 0.0;

    type strongest = vector[0];

    for(Index i = 0; i < size; i++)
    {
        if(fabs(vector(i)) > fabs(strongest))
        {
            strongest = vector(i);
        }
    }

    return strongest;
}


/// Returns a vector containing the means of the subsets which correspond
/// to each of the given integers. The matrix must have 2 columns, the first
/// one containing the integers and the second one the corresponding values.

Tensor<type, 1> means_by_categories(const Tensor<type, 2>& matrix)
{
/*
    const Index integers_number = matrix.size();
    Tensor<type, 1> elements_uniques = matrix.get_column(0).get_unique_elements();
    Tensor<type, 1> values = matrix.chip(1,1);

    #ifdef __OPENNN_DEBUG__

    if(integers_number == 0)
    {
       ostringstream buffer;

       buffer << "OpenNN Exception: Matrix template.\n"
              << "Tensor<type, 1> calculate_means_integers(const Tensor<type, 2>& \n"
              << "Number of integers must be greater than 0.\n";

       throw logic_error(buffer.str());
    }

    #endif

    const Index rows_number = matrix.dimension(0);

    Tensor<type, 1> means(elements_uniques);

    type sum = 0;
    Index count = 0;

    for(Index i = 0; i < integers_number; i++)
    {
        sum = 0;
        count = 0;

        for(unsigned j = 0; j < rows_number; j++)
        {
            if(matrix(j,0) == elements_uniques(i) && !::isnan(values(j)))
            {
                sum += matrix(j,1);
                count++;
            }
        }

        if(count != 0)
        {
            means(i) = static_cast<type>(sum)/static_cast<type>(count);

        }
        else
        {
            means(i) = 0;
        }
    }

    return means;
*/
    return Tensor<type, 1>();
}



/// Returns a vector containing the values of the means for the 0s and 1s of a
/// binary column.
/// The matrix must have 2 columns, the first one has to be binary.

Tensor<type, 1> means_binary_column(const Tensor<type, 2>& matrix)
{
    Tensor<type, 1> means(2);
    means.setZero();

    Index count = 0;

    for(Index i = 0; i < matrix.dimension(0); i++)
    {
        if(abs(matrix(i,0)) < numeric_limits<type>::min())
        {
            means[0] += matrix(i,1);
            count++;
        }
        else if(static_cast<Index>(matrix(i,0)) == 1)
        {
            means[1] += matrix(i,1);
            count++;
        }
    }

    if(count != 0)
    {
        means[0] = static_cast<type>(means[0])/static_cast<type>(count);
        means[1] = static_cast<type>(means[1])/static_cast<type>(count);
    }
    else
    {
        means[0] = 0;
        means[1] = 0;
    }

    return means;
}


/// Returns a vector containing the values of the means for the 1s of each
/// of all binary columns.
/// All the columns except the last one must be binary.

Tensor<type, 1> means_binary_columns(const Tensor<type, 2>& matrix)
{
    Tensor<type, 1> means(matrix.dimension(1)-1);

    type sum = 0;
    Index count = 0;

    for(Index i = 0; i < matrix.dimension(1)-1; i++)
    {
        sum = 0;
        count = 0;

        for(Index j = 0; j < matrix.dimension(0); j++)
        {
            if(static_cast<Index>(matrix(j,i)) == 1)
            {
                sum += matrix(j,matrix.dimension(1)-1);

                count++;
            }
        }

        if(count != 0)
        {
            means(i) = static_cast<type>(sum)/static_cast<type>(count);

        }
        else
        {
            means(i) = 0;
        }
    }
    return means;
}


///Returns a vector with the percentiles of a vector given.

Tensor<type, 1> percentiles(const Tensor<type, 1>& vector)
{
    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size < 10)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: vector Template.\n"
               << "Tensor<type, 1> percentiles(const Tensor<type, 1>& vector) method.\n"
               << "Size must be greater than 10.\n";

        throw logic_error(buffer.str());
    }

#endif

      Index new_size = 0;

      for(Index i = 0; i < size; i++)
      {
          if(!::isnan(vector(i)))
          {
              new_size++;
          }
      }

      Index index = 0;
      Tensor<type, 1> new_vector(new_size);

      for(Index i = 0; i < size; i++)
      {
          if(!::isnan(vector(i)))
          {
              new_vector(index) = vector(i);
              index++;
          }
      }

      Tensor<type, 1> sorted_vector(new_vector);

      sort(sorted_vector.data(), sorted_vector.data() + new_size, less<type>());

      Tensor<type, 1> percentiles(10);

      if(new_size % 2 == 0)
      {
        percentiles[0] = (sorted_vector[new_size * 1 / 10] + sorted_vector[new_size * 1 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[1] = (sorted_vector[new_size * 2 / 10] + sorted_vector[new_size * 2 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[2] = (sorted_vector[new_size * 3 / 10] + sorted_vector[new_size * 3 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[3] = (sorted_vector[new_size * 4 / 10] + sorted_vector[new_size * 4 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[4] = (sorted_vector[new_size * 5 / 10] + sorted_vector[new_size * 5 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[5] = (sorted_vector[new_size * 6 / 10] + sorted_vector[new_size * 6 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[6] = (sorted_vector[new_size * 7 / 10] + sorted_vector[new_size * 7 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[7] = (sorted_vector[new_size * 8 / 10] + sorted_vector[new_size * 8 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[8] = (sorted_vector[new_size * 9 / 10] + sorted_vector[new_size * 9 / 10 + 1]) /static_cast<type>(2.0);
        percentiles[9] = maximum(new_vector);
      }
      else
      {
        percentiles[0] = static_cast<type>(sorted_vector[new_size * 1 / 10]);
        percentiles[1] = static_cast<type>(sorted_vector[new_size * 2 / 10]);
        percentiles[2] = static_cast<type>(sorted_vector[new_size * 3 / 10]);
        percentiles[3] = static_cast<type>(sorted_vector[new_size * 4 / 10]);
        percentiles[4] = static_cast<type>(sorted_vector[new_size * 5 / 10]);
        percentiles[5] = static_cast<type>(sorted_vector[new_size * 6 / 10]);
        percentiles[6] = static_cast<type>(sorted_vector[new_size * 7 / 10]);
        percentiles[7] = static_cast<type>(sorted_vector[new_size * 8 / 10]);
        percentiles[8] = static_cast<type>(sorted_vector[new_size * 9 / 10]);
        percentiles[9] = maximum(new_vector);
      }

      return percentiles;
}


/// Returns the weighted mean of the vector.
/// @param weights Weights of the elements of the vector in the mean.

type weighted_mean(const Tensor<type, 1>& vector, const Tensor<type, 1>& weights)
{
    const Index size = vector.dimension(0);

#ifdef __OPENNN_DEBUG__

    if(size == 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: vector Template.\n"
               << "type calculate_weighted_mean(const Tensor<type, 1>&) const method.\n"
               << "Size must be greater than zero.\n";

        throw logic_error(buffer.str());
    }

    const Index weights_size = weights.size();

    if(size != weights_size)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: vector Template.\n"
               << "type calculate_weighted_mean(const Tensor<type, 1>&) "
               "const method.\n"
               << "Size of weights must be equal to vector size.\n";

        throw logic_error(buffer.str());
    }
#endif

    type weights_sum = 0;

    type sum = 0;

    for(Index i = 0; i < size; i++)
    {
        sum += weights(i)*vector(i);
        weights_sum += weights(i);
    }

    const type mean = sum / weights_sum;

    return mean;
}

/// Returns the number of nans in the vector.
/// @param vector Vector to count the NANs

Index count_nan(const Tensor<type, 1>& vector)
{
    Index nan_number = 0;

    for(Index i = 0; i < vector.dimension(0); i++)
    {
        if(isnan(vector(i))) nan_number++;
    }

    return nan_number;
}

}


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
