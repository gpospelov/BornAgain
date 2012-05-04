#ifndef DRAWHELPER_H
#define DRAWHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DrawHelper.h
//! @brief  Helper class definition for sophisticated data drawing
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "TObject.h"

class TCanvas;

class DrawHelper : public TObject
{
public:
  ~DrawHelper();
  static DrawHelper *instance();

  static void SetStyle();

  static void SaveReport();

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
