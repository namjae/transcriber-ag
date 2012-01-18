/********************************************************************************/
/*************** Copyright (C) 2006-2011 Bertin Technologies, SAS  **************/
/*			  				      	TranscriberAG	 							*/
/* 	         																	*/
/* See COPYING for license information										  	*/
/* 	         																	*/
/********************************************************************************/
// agdemo.cc: A demo of using AG API
// Steven Bird & Xiaoyi Ma
// Copyright (C) 2001-2003 Linguistic Data Consortium
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <list>
#include <ag/AGAPI.h>
#include <gtkmm.h>

#include "DataModel/DataModel.h"
#include "Common/util/StringOps.h"
using namespace tag;

void toto();

int main(int argc, const char* argv[])
{
	if ( argc < 2 ) {
	cout << "Usage : " << argv[0] << " <filename>" << endl;
	return 1;
	}

	/*
	list<AGId> ids = Load("TransAG", argv[1], "");
list<AGId>::iterator it; 
cout << "Loaded " << argv[1] << endl;
  AGSetId loadId = "";
	AGId id = *(ids.begin());

	for ( it=ids.begin(); it!= ids.end(); ++it) {
	cout << " \t ID=" << *it << endl;	
	
loadId = GetAGSetId(*it);	
}
	loadId = GetAGSetId(id);
cout << " Corpus = " << loadId << endl;
	*/
	
	DataModel data("TransAG");
	data.loadFromFile(argv[1]);

	cout << " corpus = " << data.getCorpusName() << endl;
	
	cout << " offset = " << GetAnchorOffset("TransAG:1:6") << endl;
	cout << " offset = " << GetStartOffset("TransAG:1:E6") << endl;
	float f;
	f=GetAnchorOffset("TransAG:1:6");
	cout << " offset = " << f << endl;
	f = GetStartOffset("TransAG:1:E6") ;
	cout << " offset = " << f << endl;
	cout << "AnnotInfo = " << GetAnnotationInfo("TransAG:1:E6") << endl;

	SignalSegment s("TransAG:1:E6");
	data.getSegment("TransAG:1:E6", s);

	cout << "segment start = " << s.getStartOffset() << endl;
	const list<AnnotationId>& an = GetAnnotationSetByOffset(data.getAGTrans(), 15.3, "turn");
	cout << "IDS = " <<endl;
	copy(an.begin(), an.end(), ostream_iterator<AnnotationId>(cout, " "));
	cout << endl;
	
	vector<SignalSegment> v;
	data.getSegments("turn", v);

	cout << "-------" << endl;
	cout << " seg3 = " << v[3].getStartOffset() << endl;
//toto();
return 0;
}

void toto()
{

  AGSetId agsetId = CreateAGSet("TIMIT");
  TimelineId timelineId = CreateTimeline(agsetId);
  SetFeature(timelineId,"length","30 min");
  SignalId signalId2 = CreateSignal(timelineId,"test_uri","test_mimeclass","test_mimetype","test_encoding","test_unit","test_track");
  set<SignalId> signalIds = GetSignals(timelineId);
  AGId agId = CreateAG(agsetId,timelineId);
  SetFeature(agId,"Purpose","\n<Subset id=\"toto\">value</Subset>\n");

  SetFeature(signalId2,"Source","CNNI");

  TimelineId timelineId2 = CreateTimeline(agsetId);
  SetFeature(timelineId2,"length","30 min");

  AnchorId anchor1 = CreateAnchor(agId,10,"sec",signalIds);
  AnchorId anchor2 = CreateAnchor(agId,20,"sec",signalIds);
  AnchorId anchor3 = CreateAnchor(agId,30,"sec",signalIds);
  AnnotationId annotation1 = CreateAnnotation(agId,anchor1,anchor2,"timit");
  AnnotationId annotation2 = CreateAnnotation(agId,anchor2,anchor3,"timit");
  AnnotationId annotation3 = CreateAnnotation(agId,anchor1,anchor3,"timit");
  SetFeature(annotation1,"sentence","He will walk to the store.");
  SetFeature(annotation2,"sentence","He will be walking.");

  cout << "A simple AG with three nodes and three arcs:" << endl;  
  cout << toXML(agsetId);
  //Store("AG", "toto", agsetId);
  cout << "-------------------------" << endl;

  SetAnchorOffset(anchor3,40);
  cout << "change the offset of anchor3 to 40:" << endl;
  cout << toXML(agsetId) << endl;
  cout << "-------------------------" << endl;

  SetStartAnchor(annotation2,anchor1);
  cout << "change start of annotation2 to anchor1" << endl;
  cout << toXML(agsetId)  << endl;
  cout << "-------------------------" << endl;

  SetFeature(annotation1, "tense", "simple future");
  cout << "Set feature \"tense\" of annotation1 to \"simple future\"" << endl;
  cout << toXML(agsetId) << endl;
  cout << "-------------------------" << endl;

  map<string,string> features;
  features["sentence"] = "Peace is coming.";
  features["tense"] = "present progressive";
  features["#tokens"] = "3";
  SetFeatures(annotation3, features);
  cout << "Set features of annotation3 to sentence=Peace is coming.;tense=present progressive;#tokens=3" << endl;
  cout << toXML(agsetId) << endl;
  cout << "-------------------------" << endl;

  cout << "Get all information of annotation2:" <<endl;
  cout << GetAnnotationInfo(annotation2) << endl;
  cout << "-------------------------" << endl;

  CopyAnnotation(annotation2);
  cout << "copy annotation2" << endl;
  cout << toXML(agsetId) << endl;
  cout << "-------------------------" << endl;


  SplitAnnotation(annotation3);
  cout << "split annotation3" << endl;
  cout << toXML(agsetId) << endl;
  cout << "-------------------------" << endl;

  SetStartAnchor(annotation2,anchor2);
  cout << "change start of annotation2 to anchor2" << endl;
  cout << toXML(agsetId)  << endl;
  cout << "-------------------------" << endl;

  cout << "Get annotation set by feature with \"tense\" = \"simple future\"" << endl;
  //cout <<  GetAnnotationSetByFeature(agId,"tense", "simple future") << endl;
  set<AnnotationId> annSet = GetAnnotationSetByFeature(agId,"tense", "simple future");
  set<AnnotationId>::iterator pos = annSet.begin();
  for (; pos != annSet.end(); ++pos)
    cout << *pos << " ";
  cout << endl;
  cout << "-------------------------" << endl;

  cout << "Get annotation seq by offset = 10" << endl;
  //cout <<  GetAnnotationSetByOffset(agId,10) << endl;
  list<AnnotationId> annList = GetAnnotationSetByOffset(agId,10);
  list<AnnotationId>::iterator pos2;
  for (pos2=annList.begin(); pos2 != annList.end(); ++pos2)
    cout << *pos2 << " ";
  cout << endl;
  cout << "-------------------------" << endl;


  cout << "Get outgoing annotation of anchor " << anchor1 << endl;
  //cout <<  GetOutgoingAnnotationSet(anchor1) << endl;
  annSet = GetOutgoingAnnotationSet(anchor1);
  for (pos=annSet.begin(); pos != annSet.end(); ++pos)
    cout << *pos << " ";
  cout << endl;
  cout << "-------------------------" << endl;

}
