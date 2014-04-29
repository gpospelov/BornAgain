#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include "OutputDataItem.h"
#include "centralplot.h"

class QtProperty;
class QtVariantProperty;


class PropertyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyWidget(QWidget *parent);
    virtual ~PropertyWidget(){}

    QSize minimumSizeHint() const { return QSize(150, 600); }

    void setupPropertyWidget(CentralPlot *centralPlot, OutputDataItem *outputDataItem);


private:
    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyBrowser;
    OutputDataItem *m_outputDataItem;
    CentralPlot *m_centralPlot;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    void addProperty(QtVariantProperty *property, const QString &id);



private slots:
    void valueChanged(QtProperty *property, const QVariant &value);
};

#endif // PROPERTYWIDGET_H
