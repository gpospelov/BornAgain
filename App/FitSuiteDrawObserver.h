// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FitSuiteDrawObserver.h
//! @brief     Defines class FitSuiteDrawObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEDRAWOBSERVER_H
#define FITSUITEDRAWOBSERVER_H


#include "IObserver.h"
#include "OutputData.h"

//class TPaveText;
class TCanvas;


//! Draw fit progress at the end of each FitSuite's iteration
class FitSuiteDrawObserver : public IObserver
{
public:
    FitSuiteDrawObserver( int draw_every_nth = 20, const std::string &canvas_base_name = std::string("FitSuiteDrawObserver") );
    virtual ~FitSuiteDrawObserver(){}

    void update(IObservable *subject);

    //! return output data which contains relative difference between simulation and real data
    OutputData<double > *getRelativeDifferenceMap(const OutputData<double> *p_simu_data, const OutputData<double> *p_real_data);

private:
    int m_draw_every_nth; //! update canvas every nth iteration
    std::string m_canvas_base_name; //! canvas name were to draw
//    TPaveText *m_ptext;
    std::vector<TCanvas *> m_data_canvas;
};



#endif // FITSUITEDRAWOBSERVER_H


