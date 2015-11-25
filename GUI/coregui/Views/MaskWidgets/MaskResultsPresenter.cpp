// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskResultsPresenter.cpp
//! @brief     Implements class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskResultsPresenter.h"
#include "ColorMapPlot.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "OutputData.h"
#include "MaskItems.h"
#include "IShape2D.h"
#include <boost/scoped_ptr.hpp>
#include <QVBoxLayout>
#include <QDebug>

MaskResultsPresenter::MaskResultsPresenter(QWidget *parent)
    : QWidget(parent)
    , m_colorMapPlot(new ColorMapPlot(this))
    , m_resultModel(0)
{
    setObjectName(QStringLiteral("MaskResultsPresenter"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_colorMapPlot);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void MaskResultsPresenter::setModel(SessionModel *maskModel, const QModelIndex &rootIndex)
{
    m_maskModel = maskModel;
    m_rootIndex = rootIndex;
}

void MaskResultsPresenter::updatePresenter()
{
    m_colorMapPlot->setItem(0);

    IntensityDataItem *origItem = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
    Q_ASSERT(origItem);

    delete m_resultModel;
    m_resultModel = new SessionModel(SessionXML::MaskModelTag);
    m_resultModel->initFrom(m_maskModel, origItem);

    IntensityDataItem *item = dynamic_cast<IntensityDataItem *>(m_resultModel->getTopItem());
    item->setOutputData(createMaskPresentation());
    Q_ASSERT(item);


    m_colorMapPlot->setItem(item);
}

OutputData<double> *MaskResultsPresenter::createMaskPresentation()
{
    qDebug() << "MaskResultsPresenter::createMaskPresentation()";

    IntensityDataItem *origItem = dynamic_cast<IntensityDataItem *>(m_maskModel->itemForIndex(m_rootIndex));
    Q_ASSERT(origItem);

    OutputData<double> *result = origItem->getOutputData()->clone();
    result->setAllTo(0.0);


    qDebug() << "BBB 1.1";
    for (int i_row = 0; i_row < m_maskModel->rowCount(m_rootIndex); ++i_row) {
        qDebug() << "BBB 1.2";
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, m_rootIndex);
        if (MaskItem *item = dynamic_cast<MaskItem *>(m_maskModel->itemForIndex(itemIndex))) {
            qDebug() << "BBB 1.3";
            Geometry::IShape2D *shape = item->createShape();
            if(shape) {
                qDebug() << "BBB 1.3.1" <<item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
                m_detectorMask.addMask(*shape, item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool());
            }
            delete shape;
        }
    }

    m_detectorMask.initMaskData(*result);

    qDebug() << "BBB 1.4" << m_detectorMask.getNumberOfMaskedChannels();
    for(size_t i=0; i<m_detectorMask.getMaskData()->getAllocatedSize(); ++i) {
        (*result)[i] = (*m_detectorMask.getMaskData())[i];
    }


    return result;

}

