#ifndef WWWATERSPIGOT_H
#define WWWATERSPIGOT_H

class wwWaterSpigot
{
 public:
  wwWaterSpigot(float position=0.5, float size=0.05, float flow=0.2,
		float amp=0.1, float freq=0.02);
  void doIt(wwMapValue &water);

 private:
  int p;
  int s;
  float f;
  float a;
  float fr;
  int t;
};


#endif
