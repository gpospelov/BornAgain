#include "GUIObjectBuilder.h"
#include "SessionModel.h"
#include <QDebug>


GUIObjectBuilder::GUIObjectBuilder()
    : m_sessionModel(0)
//    , m_parentItem(0)
{

}


void GUIObjectBuilder::populateModel(SessionModel *model, ISample *sample)
{
    qDebug() << "GUIObjectBuilder::populateModel()";
    m_sessionModel = model;

    //sample->accept(this);
    VisitSampleTree(*sample, *this);

}


void GUIObjectBuilder::visit(const ParticleLayout *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleLayout *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sessionModel->insertNewItem("ParticleLayout", m_sessionModel->indexOfItem(parent));
    item->setItemName(sample->getName().c_str());

    m_levelToParent[getLevel()] = item;

}


void GUIObjectBuilder::visit(const Layer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Layer *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sessionModel->insertNewItem("Layer", m_sessionModel->indexOfItem(parent));
    item->setItemName(sample->getName().c_str());
    // TODO: set material
    // TODO: set thickness

    m_levelToParent[getLevel()] = item;

}


void GUIObjectBuilder::visit(const MultiLayer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const MultiLayer *)" << getLevel();

    ParameterizedItem *item = m_sessionModel->insertNewItem("MultiLayer");
    item->setItemName(sample->getName().c_str());
    item->setProperty("Cross Correlation Length", sample->getCrossCorrLength());

    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const Particle *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Particle *)" << getLevel();

//    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
//    // TODO: set material
//    m_levelToParent[getLevel()] = particleItem;

}


void GUIObjectBuilder::visit(const ParticleInfo *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleInfo *)" << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    qDebug() << "1.1" << parent->itemName() << m_sessionModel->indexOfItem(parent);
    ParameterizedItem *item = m_sessionModel->insertNewItem("Particle", m_sessionModel->indexOfItem(parent));
    qDebug() << "1.2";
    Q_ASSERT(item);
    item->setItemName(sample->getName().c_str());
    item->setProperty("Depth", sample->getDepth());
    item->setProperty("Abundance", sample->getAbundance());
    qDebug() << "1.3";

    m_levelToParent[getLevel()] = item;
    qDebug() << "1.4";

}



