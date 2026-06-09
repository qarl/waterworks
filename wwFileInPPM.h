#ifndef WWFILEINPPM_H
#define WWFILEINPPM_H

class wwFileInPPM 
{
 public:
  wwFileInPPM(const char *filename);
  void doIt(wwMapColor &output);

 private:
  wwMapColor cache;

};


#endif
