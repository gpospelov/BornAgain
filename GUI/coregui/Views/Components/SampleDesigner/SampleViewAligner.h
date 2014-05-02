#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H


#include <QMap>
#include "IView.h"


//! aligns IView's on graphics scene
class SampleViewAligner
{
public:

    static void align(QList<IView *> views);

private:
    //! returns number of areas on graphics scene
    static int getMaximumAreaNumber() { return 2;}

    //! place given items using given reference point
    static QPointF placeItems(const QList<IView *> &items, QPointF reference);

    //! returns total vertical space occupied by items
    static qreal getTotalVerticalSpace(const QList<IView *> &items);

    //! returns maximum horizontal space needed for items
    static qreal getMaximumHorizontalSpace(const QList<IView *> &items);

    static QMap<QString, int> m_typeToArea; //!< correspondance of ParameterizedItem's type and area on the screen,
};


#endif
