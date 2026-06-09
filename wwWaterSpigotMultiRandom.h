#ifndef WWWATERSPIGOTMULTIRANDOM_H
#define WWWATERSPIGOTMULTIRANDOM_H

class wwWaterSpigotMultiRandom
{
 public:
  wwWaterSpigotMultiRandom(int number=10, 
		      float startchance=0.0004, float stopchance=0.0002);
  ~wwWaterSpigotMultiRandom();
  void doIt(wwMapValue &water);


 private:
  int n;
  float start;
  float stop;
  wwWaterSpigotRandom *spigots[100];
};

#endif
