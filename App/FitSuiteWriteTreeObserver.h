// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FitSuiteWriteTreeObserver.h
//! @brief     Defines classes FitSuiteObserverFactory, FitSuiteObserverPrint, FitSuiteObserverDraw, FitSuiteObserverWriteTree
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEWRITETREEOBSERVER_H
#define FITSUITEWRITETREEOBSERVER_H

#include "IObserver.h"
#include "OutputData.h"

//! Save results of each fit iteration to the disk in the form of ROOT tree
class FitSuiteWriteTreeObserver : public IObserver
{
public:
    FitSuiteWriteTreeObserver(const std::string &file_name = std::string("fitsuite.root"));
    void update(IObservable *subject);
    virtual ~FitSuiteWriteTreeObserver(){ }

private:
    std::string m_file_name; //! canvas name were to draw
    OutputData<double> *m_prev_data;
};



#endif // FITSUITEWRITETREEOBSERVER_H


