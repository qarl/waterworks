#ifndef WWTIMEBLUR_H
#define WWTIMEBLUR_H

class wwTimeBlur: public wwOperatorSimple
{
 public:
  wwTimeBlur(int factor=5);
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  int shift;
  int multiplier;
  wwMapColor previous;

};

#endif

