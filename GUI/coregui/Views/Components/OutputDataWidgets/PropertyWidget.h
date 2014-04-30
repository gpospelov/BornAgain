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

    int getWidth();


public slots:
    void onOutputDataItemModified();

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);


private:
    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyBrowser;
    CentralPlot *m_centralPlot;
    OutputDataItem *m_outputDataItem;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    void addProperty(QtVariantProperty *property, const QString &id);
    int maxWidth;


};

#endif // PROPERTYWIDGET_H
