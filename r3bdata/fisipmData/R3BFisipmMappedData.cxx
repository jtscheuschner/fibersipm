
#include "R3BFisipmMappedData.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016
// adapted by Joachim March 2016

R3BFisipmMappedData::R3BFisipmMappedData()
    : fDetector(0)
    , fSiPM(0)
    , fcoarse(0)
    , ffine(0)
{
}

R3BFisipmMappedData::R3BFisipmMappedData(	UChar_t detector, 
						UInt_t sipm,
						UInt_t coarse,
						UInt_t fine,
						Bool_t leading
						)
  : fDetector(detector)
  , fSiPM(sipm)
  , fcoarse(coarse)
  , ffine(fine)
  , fleading(leading)

{
}

ClassImp(R3BFisipmMappedData)
