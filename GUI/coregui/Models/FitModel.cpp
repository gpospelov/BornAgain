// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModel.cpp
//! @brief     Implements class FitModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitModel.h"
#include "ItemIDFactory.h"

namespace
{
enum EColumn { ITEM_Name, ITEM_Property_Value, ITEM_Ancestors, MAX_COLUMNS };
    QString FitParameterModel_Name = "FitParameterModel";
}

FitModel::FitModel(int columns, AcceptableFitModelNames modelName, QObject *parent)
    : SessionModel(SessionXML::FitModelTag, parent)
{
    parameter = "Parameter";
    ancestors = "Ancestors";
    immediate_predecessor = "Previous Predecessor";
    m_columns = columns;
    m_modelName = modelName;
}

QVariant FitModel::data(const QModelIndex &index, int role) const{

    ParameterizedItem* root = this->rootItem();

    if (!root || !index.isValid() || index.column() < 0 || index.column() >= m_columns) {
        return QVariant();
    }

    if (ParameterizedItem *item = itemForIndex(index)) {

        if (role == Qt::DisplayRole || role == Qt::EditRole) {

            switch (index.column()) {

            case ITEM_Name:
                return item->itemName();

            case ITEM_Property_Value:

                try{
                    item->getRegisteredProperty(parameter);
                }
                catch(GUIHelpers::Error e){

                    return QVariant();
                }
                return item->getRegisteredProperty(parameter);

            case ITEM_Ancestors:

                try{
                    item->getRegisteredProperty(ancestors);
                }
                catch(GUIHelpers::Error e){

                    return QVariant();
                }

                return item->getRegisteredProperty(ancestors);


            default:
                return QVariant();
            }
        }

    }
    return QVariant();

}


QModelIndex FitModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!rootItem() || row < 0 || column < 0 || column >= m_columns
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();

    ParameterizedItem *parent_item = itemForIndex(parent);

    if (ParameterizedItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }

    return QModelIndex();
}


QVariant FitModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {

        switch (section) {

        case ITEM_Name:
            return tr("Parameter");

        case ITEM_Property_Value:
            return tr("Value");

        case ITEM_Ancestors:          
            return tr("Predecessor");
        }
    }
    return QVariant();
}

bool FitModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (ParameterizedItem *item = itemForIndex(index)) {

        if (role == Qt::EditRole) {

            switch (index.column()){

            case ITEM_Name:
                item->setItemName(value.toString());
                break;

            case ITEM_Property_Value:
                item->setRegisteredProperty(parameter, value);
                break;

            case ITEM_Ancestors:
                item->setRegisteredProperty(ancestors, value);
                break;
            }

        }
        else{
            return false;
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int FitModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return m_columns;
}

bool FitModel::insertRows(int position, int rows, const QModelIndex &parent){
    ParameterizedItem *parentItem = itemForIndex(parent);

    beginInsertRows(parent, position, position + rows - 1);
    for(int i = position; i < position + rows; i++){
        ParameterizedItem *newItem = new ParameterizedItem(Constants::FitParameterType);
        parentItem->insertChildItem(position,newItem);
    }
    endInsertRows();

    return true;

}


bool FitModel::insertColumns(int column, int count, const QModelIndex & parent){

    Q_UNUSED(column);
    Q_UNUSED(count);
    Q_UNUSED(parent);
    return true;

}

bool FitModel::removeRows(int row, int count, const QModelIndex & parent){

    ParameterizedItem *parentItem = itemForIndex(parent);

    int childrenCount = parentItem->childItemCount();


    if(row + count < childrenCount){
        beginRemoveRows(parent, row, row + count - 1);

        for (int i = 0; i < count; ++i) {
            delete parentItem->takeChildItem(row);
            //taken directly from session model.
            //assumes that as soon as a child is deleted, the following children are shifted "up" to fill the space
        }
        endRemoveRows();
        return true;
    }

    //trying to delete more children than what is the parent item has
    return false;
}
bool FitModel::removeColumns(int column, int count, const QModelIndex & parent){

    Q_UNUSED(column);
    Q_UNUSED(count);
    Q_UNUSED(parent);
    return true;
}

Qt::DropActions FitModel::supportedDropActions() const{
    return Qt::CopyAction | Qt::MoveAction;
}

QMimeData* FitModel::mimeData(const QModelIndexList &indices) const
{
    qDebug()<<"beginning of Function MimeData";

    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {

        ParameterizedItem *parentItem = item->parent();

        try{
            qDebug()<<"Item already had property 'Ancestors': "<<item->getRegisteredProperty(ancestors);

        }
        catch(GUIHelpers::Error e){
            //if item does not already have ancestor property, then register it.

            QString ancestors_value;

            while(parentItem != rootItem()){
                QString text = parentItem->itemName();

                ancestors_value.append(text);
                ancestors_value.append(", ");

                qDebug()<<text;

                parentItem = parentItem->parent();
                //to go one level up
            }

            //attach id of immediate predecessor unto the end
            //parentItem = item->parent();
            //ancestors_value.append(item->getRegisteredProperty(ParameterizedItem::P_ID).toString());

            item->registerProperty(ancestors, ancestors_value);

            qDebug()<<"Item now has property 'Ancestors': "<<item->getRegisteredProperty(ancestors);

        }

        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::MimeType, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool FitModel::canDropMimeData(const QMimeData *data,
                               Qt::DropAction action, int row, int column, const QModelIndex &parent) const{

    qDebug()<<"Beginning of canDropMimeData =====================================";
    Q_UNUSED(data);
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(column);

    ParameterizedItem* parentItem = itemForIndex(parent);

    //check parent item has name that contains the word "Parameter"
    QString itemName = parentItem->itemName();
    if(!itemName.contains("Parameter")){
        qDebug("    cannot Drop Mime Data: reason 1");
        return false;
    }

    QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
    QXmlStreamReader reader(xml_data);

    int numberOfItems = 0;
    QString parameterName,ancestorString;
    QString predecessor_String = NULL;

     while (!reader.atEnd()) {
        reader.readNext();

        if(numberOfItems == 0 && reader.name() == SessionXML::ItemTag){
            qDebug()<<"Item has name: "<<reader.attributes().value(SessionXML::ItemNameAttribute).toString();
            parameterName = reader.attributes().value(SessionXML::ItemNameAttribute).toString();

            numberOfItems++;
        }
        if(reader.name() == SessionXML::ParameterTag){

            if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ancestors){
                ancestorString = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();

                qDebug()<<"     Item has parameter: " <<reader.attributes().value(SessionXML::ParameterNameAttribute);
                qDebug()<<"     parameter has value: " <<reader.attributes().value(SessionXML::ParameterValueAttribute);

            }

            if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == immediate_predecessor){
                predecessor_String = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
            }
        }
     }

     //if the Item has subItems then cannot be dropped
     if (numberOfItems > 2){
         qDebug("   cannot Drop Mime Data: reason 2");
         return false;
     }

     if(predecessor_String == NULL){

         int numberOfFitParameters = parentItem->parent()->childItemCount();

         for(int j = 0; j< numberOfFitParameters; j++){

             parentItem = parentItem->parent()->childAt(j);

             QList<ParameterizedItem*> childrenItem = parentItem->childItems();

             for(int i = 0; i< parentItem->childItemCount(); i++){

                 ParameterizedItem* childItem = childrenItem.at(i);
                 QVariant childParameter;

                 childParameter = childItem->itemName();

                 QVariant childAncestorString;

                 try{
                     childAncestorString = childrenItem.at(i)->getRegisteredProperty(ancestors);
                 }
                 catch(GUIHelpers::Error e){
                     childAncestorString = QVariant();
                 }

                 qDebug()<<"Can drop data: "<<childParameter <<" & "<<childAncestorString;
                 qDebug()<<"Can drop data: "<<parameterName <<" & "<<ancestorString;

                 if(childParameter.toString() == parameterName && childAncestorString.toString() == ancestorString){

                     qDebug()<<("   cannot Drop Mime Data: reason 3");
                     return false;
                 }

             }
         }
     }

     qDebug()<<"Leaving canDropMimeData";

     return true;
}

Qt::ItemFlags FitModel::flags(const QModelIndex &index) const
{

    ParameterizedItem* item = this->itemForIndex(index);
    try{
        item->getRegisteredProperty(parameter);

        if(item->getRegisteredProperty(parameter) == QVariant())
            return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);

    }
    catch(GUIHelpers::Error){
        return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);
    }

    if (index.isValid()){
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    else{
        return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);
    }
}

bool FitModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                            int row, int column, const QModelIndex &parent){

    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    if (ParameterizedItem *parentItem = itemForIndex(parent)) {

        QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
        QXmlStreamReader reader(xml_data);

        ParameterizedItem* newItem = new ParameterizedItem(Constants::FitParameterType);

        QString parameterName,ancestorString;
        QString parameterValue;
        QString prev_predecessor = NULL;
        QString ID;

        bool firstItemFound = false;

        while (!reader.atEnd()) {

            reader.readNext();

            if(reader.name() == SessionXML::ItemTag){

                if(firstItemFound == false){
                    parameterName = reader.attributes().value(SessionXML::ItemNameAttribute).toString();
                    firstItemFound = true;
                }

            }
            if(reader.name() == SessionXML::ParameterTag){

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ancestors){
                    ancestorString = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == parameter){
                    parameterValue = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == immediate_predecessor){
                    prev_predecessor = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }
                /*if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ParameterizedItem::P_ID){
                    ID = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }*/
            }

        }

        newItem->setItemName(parameterName);
        newItem->registerProperty(parameter, parameterValue);
        newItem->registerProperty(ancestors, ancestorString);

        int siblings = parentItem->childItemCount();

        beginInsertRows(parent, row, row);

        parentItem->insertChildItem(siblings,newItem);

        endInsertRows();

        if(prev_predecessor == NULL){
            QString currentParentID = ItemIDFactory::getID(parentItem);
            newItem->registerProperty(immediate_predecessor, currentParentID);

        }
        else{

            ParameterizedItem* previous_item = ItemIDFactory::getItem(ID);
            ParameterizedItem* previous_parent = previous_item->parent();
            ParameterizedItem* previous_predecessor = ItemIDFactory::getItem(prev_predecessor);

            //extra redundant check. Provided canDropMime and mimeData is implemented correctly
            //the if statement should ALWAYS be true!!!
            if(previous_parent == previous_predecessor){

                int row = previous_parent->rowOfChild(previous_item);
                QModelIndex parent_index= this->indexOfItem(previous_parent);

                beginRemoveRows(parent_index, row, row);
                    previous_parent->takeChildItem(row);
                endRemoveRows();

                QString currentParentID = ItemIDFactory::getID(parentItem);
                newItem->registerProperty(immediate_predecessor, currentParentID);
            }

        }

        return true;
    }
    return false;

}

//special function used by ProxySampleModel to search for corresponding item in fitParameterModel
//and vice versa
ParameterizedItem* FitModel::searchByNameGUID(QString name, QString GUID, QModelIndex parentIndex, bool found){

    ParameterizedItem* returnItem = NULL;

    if(!found){

        QString itemName = "";
        QString itemAncestor = "";
        QString itemGUID = "";

        ParameterizedItem* parentItem = itemForIndex(parentIndex);

        if(m_modelName == FitParameterModel){

            for(int i_row = 0; i_row <rowCount(parentIndex); i_row++){

                itemName = parentItem->childAt(i_row)->itemName();

                try{
                    itemAncestor = parentItem->childAt(i_row)->getRegisteredProperty(ancestors).toString();
                }
                catch(GUIHelpers::Error){
                }

                if(itemName == name && itemAncestor.contains(GUID)){

                    return parentItem->childAt(i_row);
                }

                returnItem = searchByNameGUID(name, GUID, indexOfItem(parentItem->childAt(i_row)), found);

                if(returnItem != NULL){
                    return returnItem;
                }

            }

        }
        else if(m_modelName == ProxySampleModel){

            for(int i_row = 0; i_row <rowCount(parentIndex); i_row++){

                itemName = parentItem->childAt(i_row)->itemName();

                itemGUID = parentItem->childAt(i_row)->getRegisteredProperty(ParameterizedItem::P_PORT).toString();


                if(itemName == name && itemGUID == (GUID)){
                    return parentItem->childAt(i_row);
                }

                returnItem = searchByNameGUID(name, GUID, indexOfItem(parentItem->childAt(i_row)), found);

                if(returnItem != NULL){
                    return returnItem;
                }

            }

        }
        else{

            return returnItem;
        }
    }

    return returnItem;

}
