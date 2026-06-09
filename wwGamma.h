#ifndef WWGAMMA_H
#define WWGAMMA_H

class wwGamma
{
 public:
  wwGamma();

  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  char gammatable[256];

};


#endif
