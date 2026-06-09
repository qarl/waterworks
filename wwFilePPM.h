/*


  USAGE DEPRICATED

  use wwFileInPPM or wwFileOutPPM

*/



#ifndef WWFILEPPM_H
#define WWFILEPPM_H

class wwFilePPM
{
 public:
  void load(const char *filename, wwMapColor &output);
  void save(const char *filename, const wwMapColor &input);

 private:

};


#endif
