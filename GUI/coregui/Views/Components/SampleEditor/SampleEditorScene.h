#ifndef SAMPLEEDITORSCENE_H
#define SAMPLEEDITORSCENE_H

#include <QGraphicsScene>

//- -------------------------------------------------------------------
//! @class ISampleEditorScene
//! @brief Interface for SampleEditorScene
//- -------------------------------------------------------------------
class ISampleEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ISampleEditorScene(QObject *parent = 0) : QGraphicsScene(parent){}
    virtual ~ISampleEditorScene(){}

};


class SampleEditorScene : public ISampleEditorScene
{
    Q_OBJECT

public:
    explicit SampleEditorScene(QObject *parent = 0);
    virtual ~SampleEditorScene() {}


private:
    int m_xmax;
};

#endif // SAMPLEEDITORSCENE_H
