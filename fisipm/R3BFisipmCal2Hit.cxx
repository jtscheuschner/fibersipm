// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BFisipmCal2Hit                           -----
// -----		   created 09-03-2016 by J. Tscheuschner	   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------
/* Convert Cal data to Hit data, meaning: calculating position, 
 * meaning given a reference-point one can give each det-type to this point a z-shift
 * and angle to the x-axis(if zero no shift in z-direction per fiber) also the thickness
 * of the fiber can be given. If nothing is given reference-point will be (0,0,0), the 
 * z-shift, and angle will be set to zero, too. The thickness of the single fiber is then 
 * set to 200um.
 */

#include <iostream>
using namespace std;
#include <sstream>

#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairLogger.h"

#include "R3BEventHeader.h"
#include "R3BFisipmCalData.h"
#include "R3BFisipmHitData.h"
#include "R3BFisipmCal2Hit.h"

#include <TMath.h>

// R3BFisipmCal2Hit::R3BFisipmCal2Hit()
//     : fCalDatas(NULL)
//     , fHitDatas(new TClonesArray("R3BFisipmHitData"))
//     , fNDet(1)
//     , fGeofile(0)
//     , fFiberWidthfile(0)
//     , fFiber_width(0)
//     , fAngle(0)
//     , fRevPoint(0)
// {
// }

R3BFisipmCal2Hit::R3BFisipmCal2Hit(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose)
  , fCalData(NULL)
  , fHitData(new TClonesArray("R3BFisipmHitData"))
    //    , fNDet(1)
    //    , fGeofile(0)
    //    , fFiberWidthfile(0)
  , fFiber_width(0)
  , fAngle(0)
  , fRevPoint(0)
  , fMaxT(100)
{
}

R3BFisipmCal2Hit::~R3BFisipmCal2Hit()
{
}

InitStatus R3BFisipmCal2Hit::Init()
{
  FairRootManager* fMan = FairRootManager::Instance();
  fHeader = (R3BEventHeader*)fMan->GetObject("R3BEventHeader");
  fCalData = (TClonesArray*)fMan->GetObject("FisipmCal"); // = branch name in TTree

  if (!fCalData)
    {
      printf("Couldnt get handle on FI4 cal items\n");
      return kFATAL;
    }
  //fHitData = (TClonesArray*)fMan->GetObject("R3BFisipmHitData");
  //fCalibration = NULL; // care about that later
  FairRootManager::Instance()->Register("FisipmHit", "Land", fHitData, kTRUE);
  //fAngle      =vector<Float_t>(fNDet);
  // fRevPoint   =vector<vector<Float_t>>(fNDet);
    
  //    ReadGeometry();
  fFiber_width=0.20;//Fiber width in mm
  return kSUCCESS;

}

void R3BFisipmCal2Hit::Exec(Option_t* option)
{
  if (!fCalData) 
    {
      printf("Cannot access FiberSIPM cal items\n");
      return;
    }

  Int_t nMapped = fCalData->GetEntries();
  for (Int_t i = 0; i < nMapped; i++){
    R3BFisipmCalData* mCalData = (R3BFisipmCalData*)fCalData->At(i);
    //get the stuff
    UInt_t det_type = mCalData->GetDetector();
    UInt_t SiPM_1   = mCalData->GetSiPM();
    Float_t ToT_1   = mCalData->GetTOT();
    Float_t Time_1  = mCalData->GetTime_l();

    for (Int_t j = 0; j < nMapped; j++){
      R3BFisipmCalData* mCalData2 = (R3BFisipmCalData*)fCalData->At(j);
      //get the stuff
      UInt_t det_type = mCalData->GetDetector();
      UInt_t SiPM_2   = mCalData->GetSiPM();
      Float_t ToT_2   = mCalData->GetTOT();
      Float_t Time_2  = mCalData->GetTime_l();
      if( !BasicCut(Time_2, Time_1, SiPM_1, SiPM_2)) continue;
	
      //calc the position
      UInt_t fiber = fMapping[SiPM_1][SiPM_2];
      Float_t x_pos=XPos(fiber);
      //      Float_t z_pos=ZPos(fiber,det_type);
      new ((*fHitData)[fHitData->GetEntriesFast()])
	R3BFisipmHitData(det_type, fiber, x_pos,
			 ToT_1, ToT_2,
			 Time_1, Time_2);
	
    }
  }
}

void R3BFisipmCal2Hit::FinishEvent()
{
  fHitData->Clear();
}

void R3BFisipmCal2Hit::FinishTask()
{
}

Bool_t R3BFisipmCal2Hit::BasicCut(Float_t t1, Float_t t2, UInt_t sipm1, UInt_t sipm2){
  if(TMath::Abs(t1-t2)>fMaxT) return kFALSE;
  else return kTRUE;
}

//read-functions for mapping
void R3BFisipmCal2Hit::ReadMapping(){//TODO
  //read the mapping to get for the combinations of mppc's the fiber-number
  //different kind of mapping possible, may depend on the detector-number or experiment

  // Loading Fiber mappings

  ifstream mapping;//TODO
  mapping.open(fMappingfile);
  if(mapping.good()){
    LOG(INFO) << "R3BFiSiPMMapped2Cal opening Mapping file : " << fMappingfile << FairLogger::endl;
    std::string line, factor;
    int detector=0, channel=0;
    while(mapping.good()){

      getline(mapping,line);
      std::istringstream iss(line);
      iss>>factor;
      detector++;
      
    }
    mapping.close();
  }else{ 
    LOG(INFO)  << "R3BFibersipmCal2Hit NO Mapping file :  -> Setting to 16*c1+c2 as mapping " << FairLogger::endl;
    for(Int_t i=0;i<NCHANNEL;i++)
       for(Int_t j=0;j<NCHANNEL;j++)
	 fMapping[i][j]=i*NCHANNEL+j;
   }
   
}

Float_t R3BFisipmCal2Hit::XPos(UInt_t fiber){//, UInt_t det_type){
  return fiber*fFiber_width *TMath::Cos(fAngle)+ fOffset;//*TMath::Cos(fAngle[det_type])+fRevPoint[0];
  
}
//void R3BFisipmCal2Hit::WriteHistos() {}

ClassImp(R3BFisipmCal2Hit)
