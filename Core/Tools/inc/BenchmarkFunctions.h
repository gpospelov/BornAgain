#ifndef BENCHMARKFUNCTIONS_H
#define BENCHMARKFUNCTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   BenchmarkFunctions.h
//! @brief  Collection of hard-to-minimize 2D functions testing minimizers
//! @author Scientific Computing Group at FRM II
//! @date   23.10.2012

#include <string>
#include <iostream>

namespace BenchmarkFunctions {


class IBenchmarkFunction
{
public:
    IBenchmarkFunction(std::string name, double xmin, double xmax, double ymin, double ymax, size_t npar) :
        m_name(name), m_ndim(2), m_xmin(xmin), m_xmax(xmax), m_ymin(ymin), m_ymax(ymax), m_npar(npar) {}
    virtual ~IBenchmarkFunction(){}
    std::string m_name;
    size_t m_ndim;
    double m_xmin;
    double m_xmax;
    double m_ymin;
    double m_ymax;
    size_t m_npar;
};


class DeJong : public IBenchmarkFunction
{
public:
    DeJong() : IBenchmarkFunction("DeJong",-5.12, 5.12, -5.12, 5.12, 2) { }
    double operator()(double *x, double *p ) {
        double sum(0);
        for(size_t i=0; i<m_ndim; ++i) {
            std::cout << "xxx " << i << " " << p[i] << " " << x[i] << std::endl;
            sum += p[i]*x[i]*x[i];
        }
        return sum;
    }
};



}

#endif // BENCHMARKFUNCTIONS_H
