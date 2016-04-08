// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SimulationOptionsItem.h
//! @brief     Defines class SimulationOptionsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationOptionsItem.h"
#include "ComboProperty.h"
#include "Utils.h"

const QString SimulationOptionsItem::P_RUN_POLICY = "Run Policy";
const QString SimulationOptionsItem::P_NTHREADS = "Number of Threads";
const QString SimulationOptionsItem::P_COMPUTATION_METHOD = "Computation method";
const QString SimulationOptionsItem::P_MC_POINTS = "Number of points";


SimulationOptionsItem::SimulationOptionsItem()
    : SessionItem(Constants::SimulationOptionsType)
{

    ComboProperty policy;
    policy << Constants::JOB_RUN_IMMEDIATELY
           << Constants::JOB_RUN_IN_BACKGROUND
           << Constants::JOB_RUN_SUBMIT_ONLY;
    addProperty(P_RUN_POLICY, policy.getVariant());

    ComboProperty nthreads;
    nthreads << getCPUUsageOptions();
    addProperty(P_NTHREADS, nthreads.getVariant());

    ComboProperty computationMethod;
    computationMethod << Constants::SIMULATION_ANALYTICAL << Constants::SIMULATION_MONTECARLO;
    addProperty(P_COMPUTATION_METHOD, computationMethod.getVariant());

    addProperty(P_MC_POINTS, 100);
}



//! returns list with number of threads to select
QStringList SimulationOptionsItem::getCPUUsageOptions()
{
    QStringList result;
    int nthreads = Utils::System::getThreadHardwareConcurrency();
    for(int i = nthreads; i>0; i--){
        if(i == nthreads) {
            result.append(QString("Max (%1 threads)").arg(QString::number(i)));
        } else if(i == 1) {
            result.append(QString("%1 thread").arg(QString::number(i)));
        } else {
            result.append(QString("%1 threads").arg(QString::number(i)));
        }
    }
    return result;
}
