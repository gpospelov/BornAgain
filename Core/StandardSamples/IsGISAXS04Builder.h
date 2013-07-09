#ifndef ISGISAXS04BUILDER_H
#define ISGISAXS04BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS04Builder class to build sample: cylinders with 1DDL structure
//! factor (IsGISAXS example #4)
class IsGISAXS04Para1DBuilder : public ISampleBuilder
{
public:
    IsGISAXS04Para1DBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_corr_peak_distance;
    double m_corr_width;
    double m_corr_length;
    double m_cylinder_height;
    double m_cylinder_radius;
};


//! The IsGISAXS04Builder class to build sample: cylinders with 2DDL structure
//! factor (IsGISAXS example #4)
class IsGISAXS04Para2DBuilder : public ISampleBuilder
{
public:
    IsGISAXS04Para2DBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_peak_distance;
    double m_corr_length;
    double m_domain_size_1;
    double m_domain_size_2;
    double m_cylinder_height;
    double m_cylinder_radius;
};


#endif // ISGISAXS04BUILDER_H
