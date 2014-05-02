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
    Q_ASSERT(model);
    Q_ASSERT(sample);
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


void GUIObjectBuilder::visit(const LayerInterface *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerInterface *)"  << getLevel();

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

    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    particleItem->setItemName(sample->getName().c_str());
    // TODO: set material
    m_levelToParent[getLevel()] = particleItem;

}


void GUIObjectBuilder::visit(const ParticleInfo *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleInfo *)" << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sessionModel->insertNewItem("Particle", m_sessionModel->indexOfItem(parent));
    Q_ASSERT(item);
    item->setProperty("Depth", sample->getDepth());
    item->setProperty("Abundance", sample->getAbundance());

    m_levelToParent[getLevel()] = item;

}


void GUIObjectBuilder::visit(const FormFactorCylinder *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const FormFactorCylinder *)" << getLevel();
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];

    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Cylinder");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());

    m_levelToParent[getLevel()] = particleItem;

}


void GUIObjectBuilder::visit(const FormFactorPrism3 *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const FormFactorPrism3 *)" << getLevel();
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];

    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Prism3");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Height", sample->getHeight());

    m_levelToParent[getLevel()] = particleItem;

}


void GUIObjectBuilder::visit(const InterferenceFunctionNone *)
{
    qDebug() << "GUIObjectBuilder::visit(const InterferenceFunctionNone *)" << getLevel();

}


void GUIObjectBuilder::visit(const LayerRoughness *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerRoughness *)" << getLevel();

}

