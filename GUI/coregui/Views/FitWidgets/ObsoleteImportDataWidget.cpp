// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/ObsoleteImportDataWidget.cpp
//! @brief     Implements class ObsoleteImportDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteImportDataWidget.h"
#include "ColorMapPlot.h"
#include "IHistogram.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "FitParameterItems.h"
#include "ObsoleteFitModel.h"
#include <QLineEdit>
#include <QVBoxLayout>

ObsoleteImportDataWidget::ObsoleteImportDataWidget(ObsoleteFitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_line(new QLineEdit())
    , m_plot(new ColorMapPlot(this))
    , m_fitModel(fitModel)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_line);
    mainLayout->addWidget(m_plot);
    connect(m_line, SIGNAL(textChanged(QString)), this, SLOT(onTextUpdate()));
    setLayout(mainLayout);
}

void ObsoleteImportDataWidget::onTextUpdate() {
    QFileInfo chk(m_line->text());
    if (chk.exists() && chk.isFile()) {
        try {
            IHistogram *data = IntensityDataIOFactory::readIntensityData(m_line->text().toStdString());
            IntensityDataItem *item = new IntensityDataItem();
            item->setOutputData(data->createOutputData());
            m_plot->setItem(item);
            m_fitModel->setInputDataPath(m_line->text());
        } catch (...) { }
    }
}

void ObsoleteImportDataWidget::showEvent(QShowEvent *)
{
    onUpdateGUI();
}

void ObsoleteImportDataWidget::onUpdateGUI()
{

    m_line->setText(m_fitModel->getInputDataPath());
}
