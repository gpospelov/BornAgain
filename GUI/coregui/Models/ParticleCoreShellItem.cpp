#include "ParticleCoreShellItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString ParticleCoreShellItem::P_TYPE_NAME = "ParticleCoreShell";
const QString ParticleCoreShellItem::P_CORE_X = "Core_X";
const QString ParticleCoreShellItem::P_CORE_Y = "Core_Y";
const QString ParticleCoreShellItem::P_CORE_Z = "Core_Z";


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
    registerProperty(P_CORE_X, 0.0);
    registerProperty(P_CORE_Y, 0.0);
    registerProperty(P_CORE_Z, 0.0);

    addToValidChildren(QString("Particle"));
    addToValidChildren(QString("Core Particle"));
    addToValidChildren(QString("Shell Particle"));

    m_coreshell.resize(2);
    m_coreshell[0] = 0;
    m_coreshell[1] = 0;
}

//void ParticleCoreShellItem::addChildItem(ParameterizedItem *item)
//{

//    int index = item->getRegisteredProperty(ParameterizedItem::P_SLOT).toInt();
//    qDebug() << "ParticleCoreShellItem::addChildItem()" << index;
//    Q_ASSERT(0);
//    if(index >= m_coreshell.size())
//        throw GUIHelpers::Error("ParticleCoreShellItem::addChildItem() -> Error! Unknown index");

//    if(index == -1) {
//        if(!m_coreshell[Core]) {
//            index = Core;
//        } else {
//            index = Shell;
//        }
//        item->setRegisteredProperty(ParameterizedItem::P_SLOT, index);
//    }

//    m_coreshell[index] = item;
//    ParameterizedGraphicsItem::addChildItem(item);

//}


//ParameterizedItem *ParticleCoreShellItem::getCandidateForRemoval(ParameterizedItem *new_comer)
//{
//    if(!new_comer) return 0;
//    int nmax_allowed_number = m_nmax_children[new_comer->modelType()];
//    if(nmax_allowed_number == 0) return 0;
//    QList<ParameterizedItem *> candidates;
//    foreach(ParameterizedItem *child, m_children) {
//        if(child->modelType() == new_comer->modelType() && child != new_comer) {
//            candidates.append(child);
//        }
//    }
//    //qDebug() << " ParameterizedItem::getCandidateForRemoval() " << nmax_allowed_number << candidates.size();
//    if(candidates.size() == nmax_allowed_number)
//        return candidates.back();
//    return 0;
//}
