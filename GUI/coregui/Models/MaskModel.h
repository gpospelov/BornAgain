#ifndef MASKMODEL_H
#define MASKMODEL_H

#include "SessionModel.h"

class BA_CORE_API_ MaskModel : public SessionModel
{
    Q_OBJECT

public:
    explicit MaskModel(QObject *parent = 0);
    virtual ~MaskModel() {}
};

#endif
