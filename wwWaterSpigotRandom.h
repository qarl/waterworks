#ifndef WWWATERSPIGOTRANDOM_H
#define WWWATERSPIGOTRANDOM_H

class wwWaterSpigotRandom
{
 public:
  wwWaterSpigotRandom();
  ~wwWaterSpigotRandom();
  void doIt(wwMapValue &water);


 private:
  wwWaterSpigot *spigot;
};

#endif
