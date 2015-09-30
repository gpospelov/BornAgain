// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/FitSuiteDrawObserver.cpp
//! @brief     Implements class FitSuiteDrawObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteDrawObserver.h"
#include "FitSuite.h"
#include "BornAgainNamespace.h"
//#include "ExperimentConstants.h"
#include "IsGISAXSTools.h"

#include "TCanvas.h"
#include "TH2D.h"

#include <iomanip>
#include <sstream>


// FitSuiteObserverDraw c-tor
FitSuiteDrawObserver::FitSuiteDrawObserver(int draw_every_nth, const std::string &canvas_base_name )
    : m_draw_every_nth(draw_every_nth)
    , m_canvas_base_name(canvas_base_name)
//    , m_ptext(0)
//    , m_stat_canvas(0)
{ }




// draw results of fit iteration in ROOT's canvas
void FitSuiteDrawObserver::update(IObservable */*subject*/)
{
    throw NotImplementedException("Obsolete code");
//    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
//    if( !fitSuite ) throw NullPointerException("FitSuiteObserverDraw::update() -> Error! Can't cast FitSuite");

//    if( fitSuite->isLastIteration()) return;
//    if( (fitSuite->getNCalls() % m_draw_every_nth != 0) && fitSuite->getNCalls()!=0) return; // draw first iteration and then every n'th

//    if(fitSuite->getNCalls() == 0) {
//        for(size_t i_fit_object=0; i_fit_object<fitSuite->getFitObjects()->size(); ++i_fit_object) {
//            std::ostringstream ostr;
//            ostr << m_canvas_base_name << std::string("_data_") << i_fit_object << std::endl;
//            TCanvas *c1 = new TCanvas(ostr.str().c_str(), ostr.str().c_str(), 800, 600);
//            c1->Divide(2,2);
//            m_data_canvas.push_back(c1);
//        }
//    }

//    // plotting data
//    for(size_t i_fit_object=0; i_fit_object<fitSuite->getFitObjects()->size(); ++i_fit_object) {
//        TCanvas *c1 = m_data_canvas[i_fit_object];
//        const FitObject *fitObject = fitSuite->getFitObjects()->getObject(i_fit_object);
//        assert(fitObject);
//        assert(fitObject->getChiSquaredModule());
//        assert(fitObject->getChiSquaredModule()->getRealData());
//        assert(fitObject->getChiSquaredModule()->getSimulationData());

//        // preparing data to draw
//        const char *hname[]={ "RealData", "SimulatedData", "RelativeDifference","Chi2Map"};
//        std::vector<OutputData<double > *> data2draw;
//        data2draw.push_back( fitObject->getChiSquaredModule()->getRealData()->clone() );
//        data2draw.push_back( fitObject->getChiSquaredModule()->getSimulationData()->clone() ); //chi module have normalized simulation
//        data2draw.push_back( getRelativeDifferenceMap(fitObject->getChiSquaredModule()->getSimulationData(), fitObject->getRealData() ) );
//        data2draw.push_back( fitObject->getChiSquaredModule()->createChi2DifferenceMap() );

//        // drawing
//        for(size_t i_hist=0; i_hist<data2draw.size(); ++i_hist)  {
//            const OutputData<double > *data = data2draw[i_hist];
//            if( !data->getAxis(BornAgain::ALPHA_AXIS_NAME) || !data->getAxis(BornAgain::PHI_AXIS_NAME) ) throw LogicErrorException("FitSuiteObserverDraw::update() -> Error! Can't handle axis");

//            c1->cd((int)i_hist+1);
//            gPad->SetLogz();
//            gPad->SetLeftMargin(0.12);
//            gPad->SetRightMargin(0.12);

//            if( data->getAxis(BornAgain::ALPHA_AXIS_NAME)->getSize() != 1 && data->getAxis(BornAgain::PHI_AXIS_NAME)->getSize() != 1)
//            {
//                TH2D *hist2 = IsGISAXSTools::getOutputDataTH2D( *data, hname[i_hist]);
//                hist2->DrawCopy("COLZ");
//                delete hist2;
//            } else if(data->getAxis(BornAgain::ALPHA_AXIS_NAME)->getSize() == 1 || data->getAxis(BornAgain::PHI_AXIS_NAME)->getSize() == 1){
//                TH1D *hist1 =  IsGISAXSTools::getOutputDataScanHist(*data, hname[i_hist]);
//                hist1->DrawCopy();
//                delete hist1;
//            }

//        }
//        for(size_t i_hist=0; i_hist<data2draw.size(); ++i_hist) delete data2draw[i_hist];
//        data2draw.clear();
//        c1->Update();
//    }

//    // updating canvas
//    for(size_t i_fit_object=0; i_fit_object<fitSuite->getFitObjects()->size(); ++i_fit_object) {
//        m_data_canvas[i_fit_object]->Update();
//    }

}


// return output data which contains relative difference between simulation and real data
OutputData<double > *FitSuiteDrawObserver::getRelativeDifferenceMap(const OutputData<double> *p_simu_data, const OutputData<double> *p_real_data)
{
    OutputData<double > *p_difference_map = p_simu_data->clone();
    p_difference_map->setAllTo(0.0);

    OutputData<double>::const_iterator it_sim = p_simu_data->begin();
    OutputData<double>::const_iterator it_real = p_real_data->begin();
    OutputData<double>::iterator it_diff = p_difference_map->begin();

    while (it_sim != p_simu_data->end()) {
        double value_simu = *it_sim++;
        double value_real = *it_real++;
        double value_diff(0);
        if( value_real > 0) value_diff = std::abs(value_real - value_simu)/value_real;
        *it_diff = value_diff;
        ++it_diff;
    }
    return p_difference_map;
}




