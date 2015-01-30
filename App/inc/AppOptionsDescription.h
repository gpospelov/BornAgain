// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/AppOptionsDescription.h
//! @brief     Defines global function AppOptionsDescription.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef APPOPTIONSDESCRIPTION_H
#define APPOPTIONSDESCRIPTION_H

class ProgramOptions;
class ApplicationTestFactory;

//! Adds command line and config file options
void AddApplicationOptions(ProgramOptions *p_options, ApplicationTestFactory *p_test_factory);

#endif // APPPROGRAMOPTIONS_H


