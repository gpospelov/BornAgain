//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/importdataview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAVIEW_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAVIEW_H

#include "darefl_export.h"
#include <QWidget>

namespace gui2 {

class ApplicationModels;

//! Main window to import user data.

class DAREFLCORE_EXPORT ImportDataView : public QWidget {
    Q_OBJECT

public:
    ImportDataView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    ApplicationModels* m_models{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAVIEW_H
