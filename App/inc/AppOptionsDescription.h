#ifndef APPOPTIONSDESCRIPTION_H
#define APPOPTIONSDESCRIPTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   AppOptionsDescription.h
//! @brief  Definition of Application options
//! @author Scientific Computing Group at FRM II
//! @date   21.09.2012

class ProgramOptions;

//! add command line and config file options
void AddApplicationOptions(ProgramOptions *p_options);

#endif // APPPROGRAMOPTIONS_H
