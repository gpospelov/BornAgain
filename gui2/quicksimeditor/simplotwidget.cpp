// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/quicksimeditor/simplotwidget.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/jobmodel.h"
#include "mvvm/plotting/graphcanvas.h"
#include "mvvm/standarditems/graphviewportitem.h"
#include <QList>
#include <QSplitter>
#include <QVBoxLayout>

namespace DaRefl {

SimPlotWidget::SimPlotWidget(QWidget* parent)
    : QWidget(parent)
    , m_specularCanvas(new ModelView::GraphCanvas)
    , m_diffCanvas(new ModelView::GraphCanvas) {
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 5, 5, 5);

    auto splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(m_specularCanvas);
    splitter->addWidget(m_diffCanvas);

    //    splitter->setStyleSheet("background-color:white;");
    splitter->setSizes(QList<int>() << 300 << 100);

    layout->addWidget(splitter);

    auto on_axis_margins = [this](int left, int, int right, int) {
        // syncronizes left and right margins, leave top and bottom automatic
        m_diffCanvas->setAxisMargins(left, -1, right, -1);
    };
    connect(m_specularCanvas, &ModelView::GraphCanvas::axisMarginsChanged, on_axis_margins);
}

SimPlotWidget::~SimPlotWidget() = default;

void SimPlotWidget::setModels(ApplicationModels* models) {
    m_models = models;
    m_specularCanvas->setItem(m_models->jobModel()->specularViewport());
    m_diffCanvas->setItem(m_models->jobModel()->diffViewport());
}

void SimPlotWidget::updateViewport() {
    m_specularCanvas->setViewportToContent();
    m_diffCanvas->setViewportToContent();
}

} // namespace DaRefl
