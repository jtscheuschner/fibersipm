
#include "R3BFiSipmMappedData.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016
// adapted by Joachim March 2016

R3BFisipmMappedData::R3BFisipmMappedData()
    : fDetector(0)
    , fSiPM(0)
    ,  flctime(0)
    ,  flftime(0)
{
}

R3BFisipmMappedData::R3BFisipmMappedData(	UChar_t detector, 
						UInt_t sipm,
						UInt_t ctime,
						UInt_t ftime,
						Bool_t leading
						)
  : fDetector(detector)
  , fSiPM(sipm)
  ,  flctime(ctime)
  ,  flftime(ftime)
  ,  fleading(leading)

{
}

ClassImp(R3BFisipmMappedData)
