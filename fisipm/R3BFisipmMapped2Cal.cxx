// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           R3BFi4Mapped2Cal                        -----
// -----                    Created  21-01-2016 by R. Plag                 -----
// -----		   adapted to new test-det by J. Tscheuschner	   -----
// -----                                                                   -----
// -----------------------------------------------------------------------------
/* Convert Mapped data to Cal data, meaning: apply gain 
 * to the energy values. & get the fibernumber (position)
 */

#include <iostream>
using namespace std;

#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairLogger.h"
#include "R3BTCalEngine.h"

#include <sstream>

#include "R3BEventHeader.h"
#include "R3BFibersipmMappedData.h"
#include "R3BFibersipmCalData.h"
#include "R3BFibersipmMapped2Cal.h"
		
// R3BFibersipmMapped2Cal::R3BFibersipmMapped2Cal()
//   : fMappedItems(NULL)
//   , fClockFreq(1000. / CLOCK_TDC_MHZ)
//   , fCalItems(new TClonesArray("R3BFibersipmCalItem")){//change item to data

// }

R3BFibersipmMapped2Cal::R3BFibersipmMapped2Cal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fMappedItems(NULL)
    , fClockFreq(1000. / CLOCK_TDC_MHZ)
    , fCalItems(new TClonesArray("R3BFibersipmCalItem")){

}

R3BFibersipmMapped2Cal::~R3BFibersipmMapped2Cal(){
}

InitStatus R3BFibersipmMapped2Cal::Init(){
    FairRootManager* fMan = FairRootManager::Instance();
    fHeader = (R3BEventHeader*)fMan->GetObject("R3BEventHeader");
    fMappedItems = (TClonesArray*)fMan->GetObject("FibersipmMapped"); // = branch name in TTree
    if (!fMappedItems)
    {
		printf("Could not get handle on Fibersipm mapped items\n");
		return kFATAL;
	}
    //fCalItems = (TClonesArray*)fMan->GetObject("R3BFibersipmCalItem");
    fCalibration = NULL; // care about that later
    FairRootManager::Instance()->Register("FibersipmCal", "Land", fCalItems, kTRUE);
    ReadMapping(fMappingfile);
    //    ReadGainMatching(fMatchingfile);
    return kSUCCESS;
}

void R3BFibersipmMapped2Cal::Exec(Option_t* option){
  if (!fMappedItems){//check that the data exist
    printf("Cannot access FI_sipm mapped items\n");
    return;
  }
  ReadCalib(fCalibfile)
  UInt_t fiberdetpos;//as option for later which fiber-det position (z-axis) the detector has
  UInt_t detector_offset = 5;//not sure which detectornumber they will get
  //need two loops for bottom and top MPPC
  Int_t nMapped = fMappedItems->GetEntries();

  for (Int_t i = 0; i < nMapped; i++){

    R3BFibersipmMappedData* mItem = (R3BFibersipmMappedData*)fMappedItems->At(i);
    // calibrate and add to fCalItems
    //First some cuts
    
    if( !mItem->IsLeading() )continue;
    UInt_t detector_1 = mItem->GetDetector();
    UInt_t channel_1  = mItem->GetChannel();
    UInt_t time_c1   = mItem->GetCoarse();
    UInt_t time_f1   = mItem->GetFine();
    Float_t time_1 = Time(time_c1, time_f1);
    for (Int_t j = i; j < nMapped; j++){
      R3BFibersipmMappedData* mItem2 = (R3BFibersipmMappedData*)fMappedItems->At(j);
      if( mItem2->IsLeading() )continue;
      UInt_t detector_2 = mItem2->GetDetector();
      UInt_t channel_2  = mItem2->GetChannel();
      if(channel_2!=channel_1)continue;
      UInt_t time_c2   = mItem2->GetCoarse();
      UInt_t time_f2   = mItem2->GetFine();
      Float_t time_2 = Time(time_c2, time_f2);
      if(time_2<time_1)continue;
      
      new ((*fCalItems)[fCalItems->GetEntriesFast()])
	R3BFibersipmCalItem(detector_1,       //for later distinguish between double single layer and single readout
			    channel_1,        //position related
			    time_2-time_1,    //TOT
			    time_1, time_2);  //start and stop
      break;//first time greater than leading time is the correct time, except for scattered signal, hopefully not happening will result in two signals with small time diff
    }
  }
}


void R3BFibersipmMapped2Cal::FinishEvent(){
  fCalItems->Clear();
}

void R3BFibersipmMapped2Cal::FinishTask(){
}


void R3BFibersipmMapped2Cal::ReadCalib(TString calib){
  //TODO
  for(Int_t i=0;i<2;i++)
    for(Int_t j=0;j<128;j++)
      fCalib[i][j]=1;
}

Float_t R3BFibersipmMapped2Cal::Fine(UInt_t fine, UInt_t channel, Bool_t isleading){
  return fine*fCalib[isleading][channel];
}

Float_t R3BFibersipmMapped2Cal::Time(UInt_t coarse, UInt_t fine, UInt_t channel, Bool_t isleading){
  Float_t fine_ns = fine(fine, channel, isleading);
  return coarse * fClockFreq -fine_ns ;
}


//void R3BFibersipmMapped2Cal::WriteHistos() {}

ClassImp(R3BFibersipmMapped2Cal)
