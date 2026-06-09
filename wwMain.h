#ifndef WWMAIN_H
#define WWMAIN_H

class wwMain
{
 public:
  wwMain(wwOperatorSimple *oper);
  int main();

 private:
  wwOperatorSimple *oper;
  wwTimer timer;
};

#endif
