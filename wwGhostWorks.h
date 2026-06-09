#ifndef WWGHOSTWORKS_H
#define WWGHOSTWORKS_H

#define WW_ERR_GHOST_ALLOC WW_ERR_GHOST_GENERAL + 1


class wwGhostWorks: public wwOperatorSimple
{
 public:
  wwGhostWorks(int frames=1024);
  ~wwGhostWorks();
  void doIt(const wwMapColor &input, wwMapColor &output);

 private:
  wwLocator  locator;
  wwBlurBox  blur;
  wwTimeBlur timeblur;

  wwMapValue user;
  wwMapValue gray;
  wwMapValue grayblurred;
  wwMapGray ghost;
  wwMapGray *oldghost;
  int frames;
  int ghostnum;
};


#endif
