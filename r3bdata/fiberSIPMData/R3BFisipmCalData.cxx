
#include "R3BFisipmCalData.h"

// for the data analysis of the s438b Fisipm detectors. 
// Introduced by Ralf, Jan 2016
// adapted by Joachim March 2016


R3BFisipmCalData::R3BFisipmCalData()
    : fDetector(0)
      //    , fFiber_n(0)
    , fTOT_1(0)
      //    , fTOT_2(0)
    , fTime_l1(0)
      //    , fTime_l2(0)
    , fTime_t1(0)
      //    , fTime_t2(0)
{
}

R3BFisipmCalData::R3BFisipmCalData(	UChar_t detector, //UInt_t fiber_n,
					UInt_t channel,
					Float_t TOT_1  ,  //Float_t TOT_2,
					Float_t time_l1,  //Float_t time_l2,
					Float_t time_t1)  //Float_t time_t2)
  : fDetector(detector)
  , fSiPM(channel)
    //  , fFiber_n(fiber_n)
  , fTOT_1(TOT_1)
    // , fTOT_2(TOT_2)
  , fTime_l1(time_l1)
    //  , fTime_l2(time_l2)
  , fTime_t1(time_t1)
    //  , fTime_t2(time_t2)
  
{
}

ClassImp(R3BFisipmCalData)
