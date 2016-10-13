// @(#)root/tmva $Id$    
// Author: Peter Speckmayer

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : TMVA::GeneticGenes                                                    *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Implementation (see header for description)                               *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Peter Speckmayer <speckmay@mail.cern.ch>  - CERN, Switzerland             *
 *                                                                                *
 * Copyright (c) 2005:                                                            *
 *      CERN, Switzerland                                                         *
 *      MPI-K Heidelberg, Germany                                                 *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/

#include "TMVA/GeneticGenes.h"
#include "TMVA/GeneticPopulation.h"

//_______________________________________________________________________
//                                                                      
// Cut optimisation interface class for genetic algorithm               //
//_______________________________________________________________________

//ClassImp(TMVA::GeneticGenes)
   
//_______________________________________________________________________
BA_TMVA::GeneticGenes::GeneticGenes( std::vector<Double_t> & f  ) 
{
   // Constructor:
   // set the factors of this individual
   fFactors = f;
   fFitness = 0;
}

Bool_t BA_TMVA::operator <(const BA_TMVA::GeneticGenes& first, const BA_TMVA::GeneticGenes& second)
{
   return first.fFitness < second.fFitness;
}
