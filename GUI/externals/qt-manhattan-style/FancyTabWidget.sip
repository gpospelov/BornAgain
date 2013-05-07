


%Import QtGui/QtGuimod.sip

namespace Manhattan {

class FancyTabWidget : public QWidget{

%TypeHeaderCode
#include "fancytabwidget.h"
%End

public:

    FancyTabWidget(QWidget *parent = 0);

    void insertTab(int index, QWidget *tab /TransferThis/, const QIcon &icon, const QString &label);

};

};