#ifndef R3BFISIPMREADER_H
#define R3BFISIPMREADER_H

#include "R3BReader.h"


typedef struct EXT_STR_h101_FIBSIPM_t EXT_STR_h101_FIBSIPM;
class FairLogger;

class R3BFisipmReader : public R3BReader
{
	public:
		R3BFisipmReader(EXT_STR_h101_FIBSIPM *, UInt_t);
		~R3BFisipmReader();

		Bool_t Init(ext_data_struct_info *);
		Bool_t Read();
		void Reset();

	private:
		/* An event counter */
		//unsigned int fNEvent;
		/* Reader specific data structure from ucesb */
		EXT_STR_h101_FIBSIPM* fData;
		/* Data offset */
		UInt_t fOffset;
		/* FairLogger */
		FairLogger*	fLogger;
		/* the structs of type R3BFiberSIPMMappedItem */
		TClonesArray* fArray; /**< Output array. */


	public:
		ClassDef(R3BFisipmReader, 0);
};

#endif

