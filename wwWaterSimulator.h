#ifndef WWWATERSIMULATOR_H
#define WWWATERSIMULATOR_H

class wwWaterSimulator
{
 public:
  wwWaterSimulator();
  void doIt(const wwMapValue &user, wwMapValue &water);

 private:
  wwMapVector pixeltable;
};

#endif
