#include "FairLogger.h"

#include "TClonesArray.h"
#include "FairRootManager.h"
#include "R3BFisipmReader.h"
#include "R3BFisipmMappedData.h"

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_fibsipm.h"
        
}

R3BFisipmReader::R3BFisipmReader(EXT_STR_h101_FIBSIPM* data, UInt_t offset)
  : R3BReader("R3BFisipmReader")
  , fData(data)
  , fOffset(offset)
  , fLogger(FairLogger::GetLogger())
  , fArray(new TClonesArray("R3BFisipmMappedData"))
{
}

R3BFisipmReader::~R3BFisipmReader()
{}

Bool_t R3BFisipmReader::Init(ext_data_struct_info *a_struct_info)
{
	int ok;

	EXT_STR_h101_FIBSIPM_ITEMS_INFO(ok, *a_struct_info, fOffset,
	    EXT_STR_h101_FIBSIPM, 0);

	if (!ok) {
		perror("ext_data_struct_info_item");
		fLogger->Error(MESSAGE_ORIGIN,
		    "Failed to setup structure information.");
		return kFALSE;
	}

    // Register output array in tree
    FairRootManager::Instance()->Register("FibSIPMMapped", "Land", fArray, kTRUE);

	return kTRUE;
}

Bool_t R3BFisipmReader::Read()
{
	// Convert plain raw data to multi-dimensional array
    EXT_STR_h101_FIBSIPM_onion* data = (EXT_STR_h101_FIBSIPM_onion*)fData;

	// Display data
	// fLogger->Info(MESSAGE_ORIGIN, "  Event data:");


      uint32_t numChannels_l = data->FIBSIPM_TLCM; //number of leading channels
      uint32_t numChannels_t = data->FIBSIPM_TTCM; //number of trailing channels
      uint32_t curChannelStart=0;
      //      uint32_t curChannelStart_t=0;
      // loop over channels
      for (int i=0;i<numChannels_l;i++){
	  uint32_t channel=data->FIBSIPM_TLCMI[i]; // or 1..65
	  uint32_t nextChannelStart=data->FIBSIPM_TLCME[i]; 
	  if(data->FIBSIPM_TLCME[i]!=data->FIBSIPM_TLFME[i] ||
	     data->FIBSIPM_TLCMI[i]!=data->FIBSIPM_TLFMI[i]){
	    fLogger->Info(MESSAGE_ORIGIN, "  Coarse and Fine channel do not match:");
	    continue;
	  }
	  // if we had multi hit data, we would need to read
	  for(int j=curChannelStart; j < nextChannelStart; j++){
	    uint32_t coarse = data->FIBSIPM_TLCv[j];
	    uint32_t fine   = data->FIBSIPM_TLFv[j];
	    
	    new ((*fArray)[fArray->GetEntriesFast()])
	      R3BFisipmMappedData(0,channel,
				  coarse, fine, 1);
	  }
	  
	  curChannelStart=nextChannelStart;
      }
      curChannelStart=0;//reset
      for (int i=0;i<numChannels_t;i++){
	  uint32_t channel=data->FIBSIPM_TTCMI[i]; // or 1..65
	  uint32_t nextChannelStart=data->FIBSIPM_TTCME[i]; 
	  if(data->FIBSIPM_TTCME[i]!=data->FIBSIPM_TTFME[i] ||
	     data->FIBSIPM_TTCMI[i]!=data->FIBSIPM_TTFMI[i]){
	    fLogger->Info(MESSAGE_ORIGIN, "  Coarse and Fine channel do not match:");
	    continue;
	  }
	  // if we had multi hit data, we would need to read
	  for(int j=curChannelStart; j < nextChannelStart; j++){
	    uint32_t coarse = data->FIBSIPM_TTCv[j];
	    uint32_t fine   = data->FIBSIPM_TTFv[j];
	    
	    new ((*fArray)[fArray->GetEntriesFast()])
	      R3BFisipmMappedData(0,channel,
				  coarse, fine, 0);
	  }
	  curChannelStart=nextChannelStart;
      }
      
}

void R3BFisipmReader::Reset()
{
  // Reset the output array
  fArray->Clear();
}

ClassImp(R3BFisipmReader)

