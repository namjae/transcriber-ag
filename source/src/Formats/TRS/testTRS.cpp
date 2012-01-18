/********************************************************************************/
/*************** Copyright (C) 2006-2011 Bertin Technologies, SAS  **************/
/*			  				      	TranscriberAG	 							*/
/* 	         																	*/
/* See COPYING for license information										  	*/
/* 	         																	*/
/********************************************************************************/

#include <ag/agfio_plugin.h>
#include <xercesc/parsers/SAXParser.hpp>
#include <fstream>
#include <ag/AGException.h>
#include <ag/RE.h>
#include <ag/AGAPI.h>
#include "SAX_TRSHandlers.h"
#include "agfXercesUtils.h"


int main(int argc, const char* argv[])
{
  try {
    xercesc_open();
  }
  catch (const agfioError& e) {
    throw agfio::LoadError(string("TRS:") + e.what());
  }

  SAX_TRSHandlers handler("UTF-8");

  bool val_opt = true;
  string encoding = "";
      val_opt = false;

  try {
	  TRSagfSAXParse(&handler, argv[1], val_opt, encoding);
   }
  catch (const XMLException& e) {
    Log::err() << "TRS:loading failed due to the following error\n" << trans(e.getMessage()) << endl;
  }
  catch (AGException& e) {
    Log::err() << "TRS:loading failed due to the following error\n" <<
			   e.error() << endl;
  }
  catch (const char* msg) {
	Log::err() << "Caught error = " << msg << endl;
	}

  list<AGId> result = handler.get_agids();
  xercesc_close();

cout << "AGID = " << *(result.begin()) << endl;
cout << "AGSETID = " << GetAGSetId(*(result.begin())) << endl;

	toXML(GetAGSetId(*(result.begin())));

  return 0;

}
