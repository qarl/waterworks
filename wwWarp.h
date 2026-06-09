#ifndef WWWARP_H
#define WWWARP_H

class wwWarp
{
 public:
  void doIt(const wwMapGray &input, const wwMapVector &warp, 
	    wwMapGray &output);
  void doIt(const wwMapColor &input, const wwMapVector &warp, 
	    wwMapColor &output);

 private:

};


#endif
