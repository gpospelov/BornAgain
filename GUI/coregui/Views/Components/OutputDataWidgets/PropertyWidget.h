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

    QSize minimumSizeHint() const { return QSize(230, 800); }

    void setupPropertyWidget(OutputDataItem *outputDataItem, QCPColorGradient gradient);

    int getWidth();
    void toggleProjections();

public slots:
    void onOutputDataItemModified();

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);

signals:
  void projectionsChanged(bool projection);
  void gradientChanged(QCPColorGradient gradient);


private:
    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyBrowser;
    OutputDataItem *m_outputDataItem;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    void addProperty(QtVariantProperty *property, const QString &id);
    int maxWidth;
    bool isProjection;
    QVector<QCPColorGradient> m_gradientVector;
    void initGradientVector();
    QtVariantProperty *m_projectionsProperty;
    QtVariantProperty *m_interpolationProperty;
    QtVariantProperty *m_logzProperty;
    QtVariantProperty *m_zminProperty;
    QtVariantProperty *m_zmaxProperty;
    QtVariantProperty *m_gradientProperty;
    QtVariantProperty *m_xtitleProperty;
    QtVariantProperty *m_ytitleProperty;


};

#endif // PROPERTYWIDGET_H
