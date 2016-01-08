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
                //WHAT if item does not have property named "Parameter"
                //TODO: write a guard to catch this error!

                try{
                    item->getRegisteredProperty(parameter);
                }
                catch(GUIHelpers::Error e){
                    //qDebug()<<"Cannot find 'parameter!!!!================='";
                    return QVariant();
                }
                return item->getRegisteredProperty(parameter);

            case ITEM_Ancestors:

                try{
                    item->getRegisteredProperty(ancestors);
                }
                catch(GUIHelpers::Error e){
                    //qDebug()<<"Cannot find 'predecessor!!!!================='";
                    return QVariant();
                }

                return item->getRegisteredProperty(ancestors);


            default:
                return QVariant();
            }
        }
        /*else if (role == Qt::DecorationRole && m_iconProvider) {
            return m_iconProvider->icon(item->modelType());
        }*/
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

            //qDebug()<<"HEADER DATA: Name=======================================";

            return tr("Parameter");
        case ITEM_Property_Value:

            //qDebug()<<"HEADER DATA: Property Value=============================";
            return tr("Value");
        case ITEM_Ancestors:
            //qDebug()<<"HEADER DATA: Ancestors==================================";
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

/*QStringList FitModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    //this type will only provide plain text
    return types;
}*/
QMimeData* FitModel::mimeData(const QModelIndexList &indices) const
{
    qDebug()<<"beginning of Function MimeData";

    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {

        ParameterizedItem *parentItem = item->parent();

//        QString previous_predecessor_value = parentItem->getRegisteredProperty(ParameterizedItem::P_ID).toString();

        //previous_predecessor_value.append(this->m_modelName);

        try{
            qDebug()<<"Item already had property 'Ancestors': "<<item->getRegisteredProperty(ancestors);

//            try{
//                item->registerProperty(immediate_predecessor, previous_predecessor_value);
//                qDebug()<<"Item now has property 'Previous Predecessor': "<<item->getRegisteredProperty(immediate_predecessor);
//            }
//            catch(GUIHelpers::Error e){
//                //If item is now moving the second time
//                item->setRegisteredProperty(immediate_predecessor, previous_predecessor_value);
//                qDebug()<<"Item has new value for property 'Previous Predecessor': "<<item->getRegisteredProperty(immediate_predecessor);
//            }
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
            ancestors_value.append(item->getRegisteredProperty(ParameterizedItem::P_ID).toString());

            item->registerProperty(ancestors, ancestors_value);
            qDebug()<<"\n";
            qDebug()<<"\n";
            qDebug()<<"\n";
            qDebug()<<"Item now has property 'Ancestors': "<<item->getRegisteredProperty(ancestors);
            qDebug()<<"\n";
            qDebug()<<"\n";
            qDebug()<<"\n";
        }

        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::MimeType, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;

    /*qDebug()<<"beginning of Function MimeData";

    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;

            qDebug()<<index;
            qDebug()<<text;
        }
    }

    //only need to getparent of the item's first column
    ParameterizedItem *itemToEncode = itemForIndex(indexes.at(0));
    ParameterizedItem *parentItem = itemToEncode->parent();

    //recursive function to travel all the way up to the root
    while(parentItem != getRoot()){
        QString text = parentItem->itemName();

        stream<<text;

        qDebug()<<text;

        parentItem = parentItem->parent();
        //to go one level up
    }

    stream<<m_modelName;
    qDebug()<<m_modelName;
    mimeData->setData("application/vnd.text.list", encodedData);

    //this->selectionMap.insert(indexes.at(0),QModelIndex());
    //insert a placeholder with invalid index for the value.
    //need to be updated later when the item is dropped.

    qDebug()<<"end of Function MimeData";

    qDebug()<<this;

    return mimeData;*/
}

//need to fix this!!!!
bool FitModel::canDropMimeData(const QMimeData *data,
                               Qt::DropAction action, int row, int column, const QModelIndex &parent) const{
    //TODO do it

    qDebug()<<"Beginning of canDropMimeData =====================================";
    Q_UNUSED(data);
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(column);
    //Q_UNUSED(parent);

    ParameterizedItem* parentItem = itemForIndex(parent);

    //check parent item has name that contains the word "Parameter" (or maybe should be FitParameter?)
    QString itemName = parentItem->itemName();
    if(!itemName.contains("Parameter")){
        qDebug("reason 1");
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
            //qDebug()<<"     Item has parameter: " <<reader.attributes().value(SessionXML::ParameterNameAttribute).toString();
            //qDebug()<<"     parameter has value: " <<reader.attributes().value(SessionXML::ParameterValueAttribute).toString();

            if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ancestors){
                ancestorString = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                qDebug()<<"\n";
                qDebug()<<"\n";
                qDebug()<<"\n";
                qDebug()<<"     Item has parameter: " <<reader.attributes().value(SessionXML::ParameterNameAttribute);
                qDebug()<<"     parameter has value: " <<reader.attributes().value(SessionXML::ParameterValueAttribute);
                qDebug()<<"\n";
                qDebug()<<"\n";
                qDebug()<<"\n";
            }

            if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == immediate_predecessor){
                predecessor_String = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
            }
        }
        //qDebug()<<reader.attributes().value(Parameter);
     }

     //if the Item has subItems then cannot be dropped
     if (numberOfItems > 2){
         qDebug("reason 2");
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
//                     qDebug()<<(parentItem->itemName());
//                     qDebug()<<(parentItem->getRegisteredProperty(parameter));

//                     qDebug()<<(childItem->itemName());
//                     qDebug()<<(childItem->getRegisteredProperty(parameter));
                     qDebug()<<("reason 3");
                     return false;
                 }

             }
         }
     }

     qDebug()<<"Leaving canDropMimeData";

     return true;

    /*
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;

    int columns = 0;

    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;

        //qDebug()<<columns;
        //qDebug()<<text;

        ++columns;
    }

    QString parameterName = newItems.at(0);
    QString ancestorString;

    //if the item doesn't have a parameter name attached to it
    if(parameterName != QString()){

        int ancestorCount = newItems.size();

        for (int ancestors = 2; ancestors < ancestorCount -1; ancestors++){
            ancestorString.append(newItems.at(ancestors));
            ancestorString.append(", ");
        }
        ancestorString.append(newItems.at(ancestorCount -1));
    }
    else{
        return false;
    }

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
            return false;
        }

    }

    qDebug()<<"End of canDropMimeData =====================================";

    return true;*/
}

Qt::ItemFlags FitModel::flags(const QModelIndex &index) const
{
//    if (!index.isValid())
//        return 0;

    qDebug()<<"Inside flags!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
    //if item doesn't have 'parameter' property, then it should NOT be draggable
    ParameterizedItem* item = this->itemForIndex(index);
    try{
        item->getRegisteredProperty(parameter);
        qDebug()<<"    has property: "<<item->getRegisteredProperty(parameter)<<"\n";

        if(item->getRegisteredProperty(parameter) == QVariant())
            return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);

    }
    catch(GUIHelpers::Error){
        qDebug()<<"    has not parameter property!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);
    }

    if (index.isValid()){
        //qDebug()<<"Inside flags: draggable, droppable, editable, and etc";
//
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    else{
        //qDebug()<<"Inside flags: droppable, and etc";

        return Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);
    }
}

bool FitModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                            int row, int column, const QModelIndex &parent){

    qDebug()<<"Entering dropMimeData";


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

            qDebug()<<reader.name();

            if(reader.name() == SessionXML::ItemTag){
                qDebug()<<"WHERE IS MY NAME!!!!!";
                qDebug()<<reader.attributes().value(SessionXML::ItemNameAttribute).toString();

                if(firstItemFound == false){
                    parameterName = reader.attributes().value(SessionXML::ItemNameAttribute).toString();
                    firstItemFound = true;
                }

            }
            if(reader.name() == SessionXML::ParameterTag){
                qDebug()<<reader.attributes().value(SessionXML::ParameterNameAttribute).toString();
                qDebug()<<reader.attributes().value(SessionXML::ParameterValueAttribute).toString();

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ancestors){
                    ancestorString = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == parameter){
                    parameterValue = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }

                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == immediate_predecessor){
                    prev_predecessor = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }
                if(reader.attributes().value(SessionXML::ParameterNameAttribute).toString() == ParameterizedItem::P_ID){
                    ID = reader.attributes().value(SessionXML::ParameterValueAttribute).toString();
                }
            }


            //qDebug()<<reader.attributes().value(Parameter);
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

    qDebug()<<"Leaving dropMimeData";

    /*
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;

    int columns = 0;

    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;

        qDebug()<<columns;
        qDebug()<<text;

        ++columns;
    }
    newItems.size();

    QString parameterValue = newItems.at(1);
    //this should be where the parameter attached to the item is stored
    //should be not-QString() if the item indeed has a double for its parameter -> which is what we can drag

    if(parameterValue != QString()){

        qDebug()<<"inside of dropMimeData";
        qDebug()<<this;

        ParameterizedItem* parentItem = itemForIndex(parent);
        qDebug()<<parentItem->itemName()<<": CAN BE dragged!";

        ParameterizedItem* childItem = new ParameterizedItem(Constants::FitParameterType);
        childItem->setItemName(newItems.at(0));
        childItem->registerProperty(parameter, parameterValue);


        QString ancestorString;
        int ancestorCount = newItems.size();

        //ancestorCount -1 because the last item contains the m_modelName of the item being dragged
        //newItems.at(0) contains the name of the property
        //newItems.at(0) contains the value of the property

        for (int ancestors = 2; ancestors < ancestorCount - 1; ancestors++){
            ancestorString.append(newItems.at(ancestors));
            ancestorString.append(", ");
        }
        ancestorString.append(newItems.at(ancestorCount -1));

        qDebug()<<ancestorString;
        childItem->registerProperty(ancestors,ancestorString);

        int childrenCount = parentItem->childItemCount();

        beginInsertRows(parent, childrenCount, childrenCount);

        parentItem->insertChildItem(childrenCount,childItem);
        endInsertRows();

        if(newItems.at(ancestorCount -1) == FitParameterModel_Name){
            //delete the duplicate item from the model
            //how?
        }

    }
    else{

        qDebug()<<"Cannot be dragged!";
    }

    return true;*/
}

//special function used by ProxySampleModel to search for corresponding item in fitParameterModel
//and vice versa
ParameterizedItem* FitModel::searchByNameGUID(QString name, QString GUID, QModelIndex parentIndex, bool found){

    ParameterizedItem* returnItem = NULL;

    if(!found){

        QString itemName;
        QString itemAncestor;
        QString itemGUID;

        ParameterizedItem* parentItem = itemForIndex(parentIndex);

        std::cout<<"parentItem has name: "<<parentItem->itemName().toStdString()<<" and GUID "<<parentItem->getRegisteredProperty("GUID").toString().toStdString()<<"\n";

        if(m_modelName == FitParameterModel){

            std::cout<<"    Number of children is: "<<rowCount(parentIndex)<<"\n";

            for(int i_row = 0; i_row <rowCount(parentIndex); i_row++){

                std::cout<<"        I am child num: "<<i_row<<"\n";

                itemName = parentItem->childAt(i_row)->itemName();

                try{

                    itemAncestor = parentItem->childAt(i_row)->getRegisteredProperty(ancestors).toString();

                }
                catch(GUIHelpers::Error){

                    //                std::cout<<"            Before: "<<i_row<<"\n";
                    //                searchByNameGUID(name, GUID, indexOfItem(parentItem->childAt(i_row)));
                    //                std::cout<<"            after: "<<i_row<<"\n";
                }
                if(itemName == name && itemAncestor.contains(GUID)){

                    std::cout<<"        FOUND "<<parentItem->childAt(i_row)<<"! \n";
                    return parentItem->childAt(i_row);
                }

                std::cout<<"        and I have: "<<itemName.toStdString()<< " and "<<itemAncestor.toStdString()<<"\n";

                std::cout<<"        +I am child num: "<<i_row<<"\n";

                returnItem = searchByNameGUID(name, GUID, indexOfItem(parentItem->childAt(i_row)), found);

                if(returnItem != NULL){
                    return returnItem;
                }
                std::cout<<"        "<<returnItem<<" and "<<found<<"\n";

                std::cout<<"        ++I am child num: "<<i_row<<"\n \n";
            }

        }
        else if(m_modelName == ProxySampleModel){

            std::cout<<"    Number of children is: "<<rowCount(parentIndex)<<"\n";

            for(int i_row = 0; i_row <rowCount(parentIndex); i_row++){

                std::cout<<"        I am child num: "<<i_row<<"\n";

                itemName = parentItem->childAt(i_row)->itemName();

                itemGUID = parentItem->childAt(i_row)->getRegisteredProperty(ParameterizedItem::P_ID).toString();


                if(itemName == name && itemGUID == (GUID)){

                    std::cout<<"        FOUND "<<parentItem->childAt(i_row)<<"! \n";
                    return parentItem->childAt(i_row);
                }

                std::cout<<"        and I have: "<<itemName.toStdString()<< " and "<<itemGUID.toStdString()<<"\n";

                std::cout<<"        +I am child num: "<<i_row<<"\n";

                returnItem = searchByNameGUID(name, GUID, indexOfItem(parentItem->childAt(i_row)), found);

                if(returnItem != NULL){
                    return returnItem;
                }
                std::cout<<"        "<<returnItem<<" and "<<found<<"\n";

                std::cout<<"        ++I am child num: "<<i_row<<"\n \n";
            }

        }
        else{

            return returnItem;
        }
    }

    return returnItem;

}
