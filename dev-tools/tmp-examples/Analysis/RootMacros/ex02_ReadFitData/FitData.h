//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  7 10:30:49 2012 by ROOT version 5.34/02
// from TTree FitSuiteTree/Oh, my data
// found on file: /Users/pospelov/nest/analysis/batch/b03_11param_PreserveValues/fitsuite.root
//////////////////////////////////////////////////////////

#ifndef FitData_h
#define FitData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

#include <vector>
#include <string>
using namespace std;


class FitData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TreeEventFitData *Event;
   Int_t           niter;
   Int_t           nstrategy;
   vector<vector<double> > real_data;
   vector<vector<double> > fit_data;
   vector<vector<double> > axis0;
   vector<vector<double> > axis1;
   Double_t        chi2;
   vector<double>  parvalues;
   vector<string>  parnames;
   vector<bool>    parfixed;

   // List of branches
   TBranch        *b_Event_niter;   //!
   TBranch        *b_Event_nstrategy;   //!
   TBranch        *b_Event_real_data;   //!
   TBranch        *b_Event_fit_data;   //!
   TBranch        *b_Event_axis0;   //!
   TBranch        *b_Event_axis1;   //!
   TBranch        *b_Event_chi2;   //!
   TBranch        *b_Event_parvalues;   //!
   TBranch        *b_Event_parnames;   //!
   TBranch        *b_Event_parfixed;   //!

   FitData(TTree *tree=0);
   virtual ~FitData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FitData_cxx
FitData::FitData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Users/pospelov/nest/analysis/batch/b03_11param_PreserveValues/fitsuite.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Users/pospelov/nest/analysis/batch/b03_11param_PreserveValues/fitsuite.root");
      }
      f->GetObject("FitSuiteTree",tree);

   }
   Init(tree);
}

FitData::~FitData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FitData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FitData::LoadTree(Long64_t entry)
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

void FitData::Init(TTree *tree)
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

   fChain->SetBranchAddress("niter", &niter, &b_Event_niter);
   fChain->SetBranchAddress("nstrategy", &nstrategy, &b_Event_nstrategy);
   fChain->SetBranchAddress("real_data", &real_data, &b_Event_real_data);
   fChain->SetBranchAddress("fit_data", &fit_data, &b_Event_fit_data);
   fChain->SetBranchAddress("axis0", &axis0, &b_Event_axis0);
   fChain->SetBranchAddress("axis1", &axis1, &b_Event_axis1);
   fChain->SetBranchAddress("chi2", &chi2, &b_Event_chi2);
   fChain->SetBranchAddress("parvalues", &parvalues, &b_Event_parvalues);
   fChain->SetBranchAddress("parnames", &parnames, &b_Event_parnames);
   fChain->SetBranchAddress("parfixed", &parfixed, &b_Event_parfixed);
   Notify();
}

Bool_t FitData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FitData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FitData::Cut(Long64_t entry)
{
  (void)entry;
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FitData_cxx
