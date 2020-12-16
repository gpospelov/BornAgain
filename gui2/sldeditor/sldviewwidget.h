// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDVIEWWIDGET_H
#define DAREFL_SLDEDITOR_SLDVIEWWIDGET_H

#include "darefl_export.h"
#include <QGraphicsView>
#include <memory>

namespace DaRefl {

class ApplicationModels;
class SLDElementController;

//! The segment QGraphicsViewItem on the Graphicsscene
class DAREFLCORE_EXPORT SLDViewWidget : public QGraphicsView {
    Q_OBJECT

public:
    SLDViewWidget(QWidget* parent = nullptr);
    ~SLDViewWidget();

    void setModels(ApplicationModels* models);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    std::unique_ptr<SLDElementController> m_sld_controller;
};

} // namespace DaRefl

#endif
