
#include "R3BFisipmHitData.h"

// for the data analysis of the s438b PSPX detectors. 
// Introduced by Ralf, Jan 2016
// adapted by Joachim March 2016

R3BFisipmHitData::R3BFisipmHitData()
    : fDetector(0)
    , fFiber_n(0)
    , fFiber_Xpos(0)
    , fTOT_1(0)
    , fTOT_2(0)
    , fTime_1(0)
    , fTime_2(0)
{
}

R3BFisipmHitData::R3BFisipmHitData(	UInt_t detector, 
				UInt_t fiber,
				Float_t xpos,
				Float_t tot_1,
				Float_t tot_2,
				Float_t time_1,
				Float_t time_2)
: fDetector(detector)
  , fFiber_n(fiber)
  , fFiber_Xpos(xpos)
  , fTOT_1(tot_1)
  , fTOT_2(tot_2)
  , fTime_1(time_1)
  , fTime_2(time_2)
  
{
}

ClassImp(R3BFisipmHitData)
