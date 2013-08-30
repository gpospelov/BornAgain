#ifndef ISGISAXS06BUILDER_H
#define ISGISAXS06BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS06Lattice1Builder class to build sample: 2D lattice with different
//! disorder (IsGISAXS example #6)
class BA_CORE_API_ IsGISAXS06Lattice1Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice1Builder(){}
    ISample *buildSample() const;
};


//! The IsGISAXS06Lattice2Builder class to build sample: 2D lattice with different
//! disorder (IsGISAXS example #6)
class BA_CORE_API_ IsGISAXS06Lattice2Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice2Builder(){}
    ISample *buildSample() const;
};


//! The IsGISAXS06Lattice3Builder class to build sample: 2D lattice with different
//! disorder (IsGISAXS example #6)
class BA_CORE_API_ IsGISAXS06Lattice3Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice3Builder(){}
    ISample *buildSample() const;
};


//! The IsGISAXS06Lattice4Builder class to build sample: 2D lattice with different
//! disorder (IsGISAXS example #6)
class BA_CORE_API_ IsGISAXS06Lattice4Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice4Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_xi;

};



#endif // ISGISAXS06BUILDER_H
