#ifndef WWWATERWORKS_H
#define WWWATERWORKS_H

class wwWaterWorks : public wwOperatorSimple
{
 public:
  void doIt(const wwMapColor &input, wwMapColor &output);


 private:
  wwLocator locator;
  wwWaterSpigotMultiRandom spigot;
  wwWaterSimulator simulator;
  wwWaterRender render;

  wwMapValue user;
  wwMapValue water;
};

#endif
