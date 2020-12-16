// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_INSTRUMENTPROPERTYEDITOR_H
#define DAREFL_QUICKSIMEDITOR_INSTRUMENTPROPERTYEDITOR_H

#include "darefl_export.h"
#include <QWidget>

namespace ModelView {
class PropertyTreeView;
}

namespace gui2 {

class ApplicationModels;

//! Widget with InstrumentItem properties.
//! Used to modify q-scan parameters, located under QuickSimEditor.

class DAREFLCORE_EXPORT InstrumentPropertyEditor : public QWidget {
    Q_OBJECT

public:
    InstrumentPropertyEditor(QWidget* parent = nullptr);
    ~InstrumentPropertyEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    ModelView::PropertyTreeView* m_beamPropertyEditor{nullptr};
};

} // namespace gui2

#endif // DAREFL_QUICKSIMEDITOR_INSTRUMENTPROPERTYEDITOR_H
