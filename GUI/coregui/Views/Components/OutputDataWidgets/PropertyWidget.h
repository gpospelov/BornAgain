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
    void connectSignals();
    void disconnectSignals();

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
