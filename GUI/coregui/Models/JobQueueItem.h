#ifndef JOBQUEUEITEM_H
#define JOBQUEUEITEM_H

#include <QList>
#include <QVariant>
#include <QString>

class QXmlStreamWriter;

class JobQueueItem
{
public:
    JobQueueItem(QString name) : m_name(name){}

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    void writeTo(QXmlStreamWriter *writer);

private:
    QString m_name;

};


//class JobQueueItem
//{
//public:
//    explicit JobQueueItem(const QString &model_type=QString(),
//                               JobQueueItem *parent=0);
//    ~JobQueueItem();

//    //! retrieves the model type
//    QString modelType() const { return m_model_type; }

//    //! retrieves the item's name
//    QString itemName() const { return m_item_name; }

//    //! sets the item's name
//    void setItemName(const QString &item_name) { m_item_name = item_name; }

//    //! retrieve parent item
//    JobQueueItem *parent() const { return m_parent; }

//    //! retrieve child item in given row
//    JobQueueItem *childAt(int row) const {
//        return m_children.value(row);
//    }

//    //! get row number of child
//    int rowOfChild(JobQueueItem *child) const {
//        return m_children.indexOf(child);
//    }

//    //! get number of child items
//    int childItemCount() const { return m_children.count(); }

//    //! indicates if item has child items
//    bool hasChildItems() const { return !m_children.isEmpty(); }

//    //! returns the a list of child items
//    QList<JobQueueItem *> childItems() const { return m_children; }

//    //! inserts a child item at specified row
//    void insertChildItem(int row, JobQueueItem *item)
//        { item->m_parent = this; m_children.insert(row, item); }

//    //! append child item
//    void addChildItem(JobQueueItem *item)
//        { item->m_parent = this; m_children << item; }

//    //! swap two child items
//    void swapChildItems(int row_1, int row_2)
//        { m_children.swap(row_1, row_2); }

//    //! take child item (this removes it from the current item)
//    JobQueueItem *takeChildItem(int row);

////    //! retrieves the parameter's value
////    double parameterValue(const QString &name) const;

////    //! sets the parameter's value, if it exists
////    void setParameter(const QString &name, double value);

////    //! retrieves the whole list of paramaters
////    QMap<QString, double> &parameters() { return m_parameters; }

////    //! indicates if the passed item can be set as
////    //! a child item
////    bool acceptsAsChild(const QString &child_name) const;

////    //! get list of acceptable child object names
////    QList<QString> acceptableChildItems() const { return m_valid_children; }

//protected:
////    QList<QString> m_valid_children;
////    QMap<QString, double> m_parameters;

//private:
//    QString m_model_type;
//    QString m_item_name;
//    JobQueueItem *m_parent;
//    QList<JobQueueItem *> m_children;
//};





#endif
