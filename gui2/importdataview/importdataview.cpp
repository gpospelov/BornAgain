// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/importdataview/importdataview.h"
#include "gui2/importdataview/importdataeditor.h"
#include "gui2/model/applicationmodels.h"
#include <QVBoxLayout>

namespace DaRefl {

ImportDataView::ImportDataView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor(models->experimentalDataModel()));
    layout->setContentsMargins(0, 0, 0, 0);
}

} // namespace DaRefl
