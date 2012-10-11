// Generates classes to read ROOT tree from existing ROOT file
//
// Usage:
// Way 1 (script mode):
// > root -l -q .x make_class.C
// Way 2 (precompiled mode):
// > root -l
// > .L make_class.C++
// > make_class()


#include "TFile.h"
#include "TTree.h"
#include <iostream>

void make_class(const char *file_name ="../../../../fitsuite.root"
               ,const char *tree_name = "FitSuiteTree"
               ,const char *class_name = "FitData")
{

    // open root file
    TFile *top = new TFile(file_name,"READ");

    // access to the tree stored in the file
    if( !top->IsOpen() ) {
        std::cout << "File is absent " << file_name << std::endl;
        return;
    }
    TTree *tree = (TTree *)top->Get(tree_name);
    if( !tree ) {
        std::cout << "Tree is absent " << tree_name << std::endl;
        return;
    }

    // generating class files (*.h, *.C)
    tree->MakeClass(class_name);
}
