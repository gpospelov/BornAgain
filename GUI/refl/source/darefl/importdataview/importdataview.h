// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H

#include <QWidget>
#include <darefl/darefl_export.h>

namespace DaRefl {

class ApplicationModels;

//! Main window to import user data.

class DAREFLCORE_EXPORT ImportDataView : public QWidget {
    Q_OBJECT

public:
    ImportDataView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    ApplicationModels* m_models{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H
