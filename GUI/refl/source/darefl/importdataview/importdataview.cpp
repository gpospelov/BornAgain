// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/importdataview/importdataeditor.h>
#include <darefl/importdataview/importdataview.h>
#include <darefl/model/applicationmodels.h>

namespace DaRefl {

ImportDataView::ImportDataView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor(models->experimentalDataModel()));
    layout->setContentsMargins(0, 0, 0, 0);
}

} // namespace DaRefl
