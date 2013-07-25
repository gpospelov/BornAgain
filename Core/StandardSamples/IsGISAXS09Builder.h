#ifndef ISGISAXS09BUILDER_H
#define ISGISAXS09BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS09Builder class to build sample: Pyramids, rotated pyramids on
//! top of substrate (IsGISAXS example #9)
class IsGISAXS09Builder : public ISampleBuilder
{
public:
    IsGISAXS09Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_half_side;
    double m_alpha;
};


class IsGISAXS09RotatedBuilder : public ISampleBuilder
{
public:
    IsGISAXS09RotatedBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_half_side;
    double m_alpha;
    double m_zangle;
};


#endif // ISGISAXS09BUILDER_H
