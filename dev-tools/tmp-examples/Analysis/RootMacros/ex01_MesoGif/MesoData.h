//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 10 12:09:54 2012 by ROOT version 5.34/00
// from TTree testmeso/Oh, my data
// found on file: testmeso.root
//////////////////////////////////////////////////////////

#ifndef MesoData_h
#define MesoData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <vector>
using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MesoData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //EventFrame      *Event;
   Int_t           nframe;
   Double_t        alpha_i;
   Double_t        phi_i;
   Int_t           nphi_f;
   Double_t        phi_f_min;
   Double_t        phi_f_max;
   Int_t           nalpha_f;
   Double_t        alpha_f_min;
   Double_t        alpha_f_max;
   Double_t        malpha;
   Double_t        mphi;
   Double_t        npR;
   vector<vector<double> > vi;
   vector<vector<double> > valpha_f;
   vector<vector<double> > vphi_f;

   // List of branches
   TBranch        *b_Event_nframe;   //!
   TBranch        *b_Event_alpha_i;   //!
   TBranch        *b_Event_phi_i;   //!
   TBranch        *b_Event_nphi_f;   //!
   TBranch        *b_Event_phi_f_min;   //!
   TBranch        *b_Event_phi_f_max;   //!
   TBranch        *b_Event_nalpha_f;   //!
   TBranch        *b_Event_alpha_f_min;   //!
   TBranch        *b_Event_alpha_f_max;   //!
   TBranch        *b_Event_malpha;   //!
   TBranch        *b_Event_mphi;   //!
   TBranch        *b_Event_npR;   //!
   TBranch        *b_Event_vi;   //!
   TBranch        *b_Event_valpha_f;   //!
   TBranch        *b_Event_vphi_f;   //!

   MesoData(TTree *tree=0);
   virtual ~MesoData();
//    virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MesoData_cxx
MesoData::MesoData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("testmeso.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("testmeso.root");
      }
      f->GetObject("testmeso",tree);

   }
   Init(tree);
}

MesoData::~MesoData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MesoData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MesoData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MesoData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nframe", &nframe, &b_Event_nframe);
   fChain->SetBranchAddress("alpha_i", &alpha_i, &b_Event_alpha_i);
   fChain->SetBranchAddress("phi_i", &phi_i, &b_Event_phi_i);
   fChain->SetBranchAddress("nphi_f", &nphi_f, &b_Event_nphi_f);
   fChain->SetBranchAddress("phi_f_min", &phi_f_min, &b_Event_phi_f_min);
   fChain->SetBranchAddress("phi_f_max", &phi_f_max, &b_Event_phi_f_max);
   fChain->SetBranchAddress("nalpha_f", &nalpha_f, &b_Event_nalpha_f);
   fChain->SetBranchAddress("alpha_f_min", &alpha_f_min, &b_Event_alpha_f_min);
   fChain->SetBranchAddress("alpha_f_max", &alpha_f_max, &b_Event_alpha_f_max);
   fChain->SetBranchAddress("malpha", &malpha, &b_Event_malpha);
   fChain->SetBranchAddress("mphi", &mphi, &b_Event_mphi);
   fChain->SetBranchAddress("npR", &npR, &b_Event_npR);
   fChain->SetBranchAddress("vi", &vi, &b_Event_vi);
   fChain->SetBranchAddress("valpha_f", &valpha_f, &b_Event_valpha_f);
   fChain->SetBranchAddress("vphi_f", &vphi_f, &b_Event_vphi_f);
   Notify();
}

Bool_t MesoData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MesoData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
// Int_t MesoData::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
#endif // #ifdef MesoData_cxx
