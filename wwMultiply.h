#ifndef WWMULTIPLY_H
#define WWMULTIPLY_H

class wwMultiply 
{
 public:
  void doIt(const wwMapGray &input1, const 
	    wwMapGray &input2, 
	    wwMapGray &output);

  void doIt(const wwMapColor &input1, const 
	    wwMapGray &input2, 
	    wwMapColor &output);

};


#endif
