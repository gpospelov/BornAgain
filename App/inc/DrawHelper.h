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
//! @brief  Helper class for graphics in ROOT
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "TObject.h"


class TCanvas;
class MultiLayer;
class TPad;

//- -------------------------------------------------------------------
//! @class DrawHelper
//! @brief Several usefull utilities for graphics in ROOT
//!
//! Provides magnification of pads in canvas, common style for drawing,
//! saving of all opened canvases from memory to pdf file
//- -------------------------------------------------------------------
class DrawHelper : public TObject
{
public:
  ~DrawHelper();
  static DrawHelper &instance();

  //! set own drawing style
  static void SetStyle();

  //! saving canvases from memory into multipage pdf file
  static void SaveReport();

  //! connect user canvas with magnifier function
  void SetMagnifier(TCanvas *c);

  //! process double click in canvas to magnify given pad
  void ExecuteMagnifier(Int_t event, Int_t px, Int_t py, TObject *sel);

  //! draw multilayer structure in TPad
  void DrawMultilayer(const MultiLayer *sample);

private:
  /// prevents client from creating a copy of the singleton
  DrawHelper();
  DrawHelper(const DrawHelper &);
  DrawHelper &operator=(const DrawHelper &);

  /// reaction on too early destroyed object
  static void onDeadReference();

  /// create single copy of manager
  static void create();

  static DrawHelper *m_instance;
  static bool m_destroyed;

  ClassDef(DrawHelper,1)
};

#endif // DRAWHELPER_H
