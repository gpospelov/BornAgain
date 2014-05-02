#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H

#include <QMap>
class DesignerScene;

class SampleViewAligner2
{
public:
    SampleViewAligner2();
    void align(DesignerScene *scene);

private:
    DesignerScene *m_scene;
};


#endif

