#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include "TObject.h"

class TCanvas;

class DrawHelper : public TObject
{
public:
  ~DrawHelper();
  static DrawHelper *instance();

  static void SetStyle();

  /// connect user canvas with magnifier function
  void SetMagnifier(TCanvas *c);

  /// process double click in canvas to magnify given pad
  void ExecuteMagnifier(Int_t event, Int_t px, Int_t py, TObject *sel);
private:
  DrawHelper();

  static DrawHelper *m_instance;
  ClassDef(DrawHelper,1)
};

#endif // DRAWHELPER_H
