#ifndef WWSLIMEWORKS_H
#define WWSLIMEWORKS_H

class wwSlimeWorks : public wwOperatorSimple
{
 public:
  void doIt(const wwMapColor &input, wwMapColor &output);


 private:
  wwLocator locator;
  wwWaterSpigotMultiRandom spigot;
  wwWaterSimulator simulator;
  wwSlimeRender render;

  wwMapValue user;
  wwMapValue water;
};

#endif
