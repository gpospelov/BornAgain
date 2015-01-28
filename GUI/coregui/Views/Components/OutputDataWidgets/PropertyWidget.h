// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/PropertyWidget.h
//! @brief     Defines class PropertyWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include "OutputDataItem.h"
#include "centralplot.h"

class QtProperty;
class QtVariantProperty;


class BA_CORE_API_ PropertyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyWidget(QWidget *parent, bool isProjection);
    virtual ~PropertyWidget(){}

    QSize minimumSizeHint() const { return QSize(230, 800); }

    void setupPropertyWidget(OutputDataItem *outputDataItem, QCPColorGradient gradient);

    int getWidth();
    void toggleProjections();
    void updateData(OutputDataItem *outputDataItem, QCPColorGradient gradient = QCPColorGradient::gpPolar);
    void setProjections(bool visible);

public slots:
    void onOutputDataItemModified();

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);

signals:
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);


private:
    void addProperty(QtVariantProperty *property, const QString &id);
    void initGradientVector();

    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyBrowser;
    OutputDataItem *m_outputDataItem;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QVector<QCPColorGradient> m_gradientVector;
    QtVariantProperty *m_projectionsProperty;
    QtVariantProperty *m_interpolationProperty;
    QtVariantProperty *m_logzProperty;
    QtVariantProperty *m_zminProperty;
    QtVariantProperty *m_zmaxProperty;
    QtVariantProperty *m_gradientProperty;
    QtVariantProperty *m_xtitleProperty;
    QtVariantProperty *m_ytitleProperty;
    int m_maxWidth;
    bool m_isProjection;
};

#endif // PROPERTYWIDGET_H
