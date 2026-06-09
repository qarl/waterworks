#ifndef WWADDCLIPPED_H
#define WWADDCLIPPED_H

class wwAddClipped 
{
 public:
  void doIt(const wwMapGray &input1, const 
	    wwMapGray &input2, 
	    wwMapGray &output);

  void doIt(const wwMapColor &input1, const 
	    wwMapColor &input2, 
	    wwMapColor &output);

};


#endif
