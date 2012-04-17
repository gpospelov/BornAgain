#include "DrawHelper.h"
#include <iostream>
#include "TCanvas.h"
#include "TObject.h"


DrawHelper *DrawHelper::m_instance = 0;


DrawHelper::DrawHelper()
{

}


DrawHelper::~DrawHelper()
{

}


DrawHelper *DrawHelper::instance()
{
  if( m_instance == 0) {
    m_instance = new DrawHelper();
  }
  return m_instance;
}


void DrawHelper::SetMagnifier(TCanvas *canvas)
{
  canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "DrawHelper", this, "ExecuteMagnifier(int,int,int,TObject*)");
}


void DrawHelper::ExecuteMagnifier(int event, int px, int py, TObject *sel)
{
  TCanvas *c = (TCanvas *) gTQSender;
  if(sel) {
    // we do not need it for the moment
  }
  if ( (event == kButton1Double) ) {
    char cname[256];
    sprintf(cname,"%s_%d",c->GetTitle(),(int)time(0));
    TPad *pad = c->Pick(px, py, 0);
    TPad *pad_new = (TPad *) pad->Clone();
    pad_new->SetPad(0.0, 0.0, 1.0, 1.0);
    TCanvas *c1 = new TCanvas(cname, cname, 800, 600);
    c1->cd();
    pad_new->SetEditable(kTRUE);
    pad_new->Draw();
    pad_new->Modified();
     //gVirtualX->SetCursor(gPad->GetId()     , gVirtualX->CreateCursor(kWatch));
    pad_new->Update();
    c1->RaiseWindow();
  }
}
