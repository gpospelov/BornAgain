#ifndef THREADINFO_H_
#define THREADINFO_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ThreadInfo.h
//! @brief  Definition of ThreadInfo class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 14, 2012

//- -------------------------------------------------------------------
//! @class ThreadInfo
//! @brief Structure holding information for threads
//- -------------------------------------------------------------------
struct ThreadInfo
{
    ThreadInfo();
    size_t n_threads;
    size_t i_thread;
};

inline ThreadInfo::ThreadInfo()
: n_threads(1)
, i_thread(0)
{
}

#endif /* THREADINFO_H_ */
