#ifndef SAMPLEVIEWALIGNER2_H
#define SAMPLEVIEWALIGNER2_H

#include <QMap>
#include <QModelIndex>
class DesignerScene;

class SampleViewAligner2
{
public:
    SampleViewAligner2();
    void align(DesignerScene *scene);

    void updateViews(const QModelIndex & parentIndex = QModelIndex());

private:
    DesignerScene *m_scene;
};


#endif

