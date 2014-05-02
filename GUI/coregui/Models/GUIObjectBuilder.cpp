#include "GUIObjectBuilder.h"
#include "SessionModel.h"
#include "Units.h"
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


void GUIObjectBuilder::visit(const FormFactorAnisoPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "AnisoPyramid");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Width", sample->getWidth());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorBox *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Box");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Width", sample->getWidth());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCone *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Cone");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCone6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Cone6");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCuboctahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Cuboctahedron");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("HeightRatio", sample->getHeightRatio());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Cylinder");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorEllipsoidalCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "EllipsoidalCylinder");
    ffItem->setProperty("Radius_a", sample->getRadiusA());
    ffItem->setProperty("Radius_b", sample->getRadiusB());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorFullSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "FullSphere");
    ffItem->setProperty("Radius", sample->getRadius());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorFullSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "FullSpheroid");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorHemiEllipsoid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "HemiEllipsoid");
    ffItem->setProperty("Radius_a", sample->getRadiusA());
    ffItem->setProperty("Radius_b", sample->getRadiusB());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPrism3 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Prism3");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPrism6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Prism6");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Pyramid");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorRipple1 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Ripple1");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Width", sample->getWidth());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorRipple2 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Ripple2");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Width", sample->getWidth());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Asymmetry", sample->getAsymmetry());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTetrahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "Tetrahedron");
    ffItem->setProperty("Length", sample->getLength());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Alpha", Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTruncatedSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "TruncatedSphere");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTruncatedSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->addFormFactorProperty("Form Factor", "TruncatedSpheroid");
    ffItem->setProperty("Radius", sample->getRadius());
    ffItem->setProperty("Height", sample->getHeight());
    ffItem->setProperty("Hfc", sample->getHeightFlattening());
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

