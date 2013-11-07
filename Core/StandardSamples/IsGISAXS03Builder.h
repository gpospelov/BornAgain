#ifndef ISGISAXS03BUILDER_H
#define ISGISAXS03BUILDER_H


#include "ISampleBuilder.h"

//! The IsGISAXS03DWBABuilder class to build sample: cylinder formfactor in DWBA
//! (IsGISAXS example #3, part I)
class IsGISAXS03DWBABuilder : public ISampleBuilder
{
public:
    IsGISAXS03DWBABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! The IsGISAXS03BABuilder class to build sample: cylinder formfactor in BA
//! (IsGISAXS example #3, part II)
class IsGISAXS03BABuilder : public ISampleBuilder
{
public:
    IsGISAXS03BABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! The IsGISAXS03BASizeBuilder class to build sample: cylinder formfactor in BA
//! with size distribution (IsGISAXS example #3, part II)
class IsGISAXS03BASizeBuilder : public ISampleBuilder
{
public:
    IsGISAXS03BASizeBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};



#endif // ISGISAXS03BUILDER_H
