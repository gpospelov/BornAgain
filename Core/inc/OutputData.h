#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include "NamedVector.h"

class MultiIndex
{
    friend class OutputData;
public:
    std::vector<std::string> getLabels() { return m_labels; }
    MultiIndex& operator++();
private:
    MultiIndex();
    ~MultiIndex();
    // Disabling copy constructor and assignment
    MultiIndex(const MultiIndex& source);
    MultiIndex operator=(const MultiIndex& source);

    void init(const std::vector<NamedVector<double>*>& value_axes);
    void clear();
    std::vector<std::string> m_labels;
    size_t m_dimension;
    size_t m_total_size;
    size_t m_current_position;
    size_t* m_axis_sizes;
    size_t* m_current_coordinate;
};

class OutputData
{
public:
    typedef NamedVector<double> value_vector;
    OutputData();

    void addAxis(value_vector* p_new_axis);
    std::vector<value_vector*> getAxes() { return m_value_axes; }
    size_t getDimension() const { return m_dimension; }
    MultiIndex& getIndex() { return m_index; }
    double& currentValue();
private:
    void allocate();
    size_t m_dimension;
    size_t m_data_size;
    size_t m_allocated_size;
    std::vector<value_vector*> m_value_axes;
    double* m_data_table;
    MultiIndex m_index;
};

#endif // OUTPUTDATA_H
