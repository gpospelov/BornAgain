// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitProgressInfo.h
//! @brief     Declares class FitProgressInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPROGRESSINFO_H
#define FITPROGRESSINFO_H

#include "WinDllMacros.h"
#include <QVector>

//! The FitProgressInfo class contains all essential information about fit progress.
//! It is send from GUIFitObserver to FitSuiteWidget on every nth iteration.

class BA_CORE_API_ FitProgressInfo {
public:
    FitProgressInfo();

    double chi2() const { return m_chi2; }
    int iterationCount() const { return m_iteration_count; }
    QVector<double> parValues() const { return m_values; }

    friend class GUIFitObserver;
private:
    double m_chi2;
    int m_iteration_count;
    QVector<double> m_values;
};

#endif
