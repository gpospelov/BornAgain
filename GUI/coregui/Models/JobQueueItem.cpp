#include "JobQueueItem.h"

JobQueueItem::JobQueueItem(const QString &model_type,
                                     JobQueueItem *parent)
    : m_model_type(model_type)
    , m_parent(parent)
{
    if (m_parent) {
        m_parent->addChildItem(this);
    }
    setItemName(m_model_type);
}

JobQueueItem::~JobQueueItem()
{
    qDeleteAll(m_children);
}

JobQueueItem *JobQueueItem::takeChildItem(int row)
{
    JobQueueItem *item = m_children.takeAt(row);
    item->m_parent = 0;
    return item;
}

//double JobQueueItem::parameterValue(const QString &name) const
//{
//    if (!m_parameters.contains(name)) {
//        throw Exceptions::RuntimeErrorException(
//                    "ParameterizedItem::getParameterValue: "
//                    "parameter does not exist");
//    }
//    return m_parameters[name];
//}

//void JobQueueItem::setParameter(const QString &name, double value)
//{
//    if (!m_parameters.contains(name)) {
//        throw Exceptions::RuntimeErrorException(
//                    "ParameterizedItem::getParameterValue: "
//                    "parameter does not exist");
//    }
//    m_parameters[name] = value;
//}

//bool JobQueueItem::acceptsAsChild(const QString &child_name) const
//{
//    return m_valid_children.contains(child_name);
//}

