#ifndef IALGORITHM_H
#define IALGORITHM_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IAlgorithm.h
//! @brief  Definition of IAlgorithm
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012


class IAlgorithm
{
public:
  virtual ~IAlgorithm() {}

  virtual void execute();
};

#endif // IALGORITHM_H

