#ifndef WWBLOODWORKS_H
#define WWBLOODWORKS_H

class wwBloodWorks : public wwOperatorSimple
{
 public:
  void doIt(const wwMapColor &input, wwMapColor &output);


 private:
  wwLocator locator;
  wwWaterSpigotMultiRandom spigot;
  wwWaterSimulator simulator;
  wwBloodRender render;

  wwMapValue user;
  wwMapValue water;
};

#endif
