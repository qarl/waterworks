#ifndef WWWATERRENDER_H
#define WWWATERRENDER_H

class wwWaterRender
{
 public:
  wwWaterRender();
  void doIt(const wwMapColor &image, const wwMapValue &water,
	    wwMapColor &output);


 private:

  void build_height_table();
  void build_thickness_table();
  void build_fresnel_table();
  void build_specular_table();
  void build_refract_table();
  void build_color_table();
  void make_height_blur(const wwMapValue &water);
  void draw(const wwMapColor &image, const wwMapValue &water,
			   wwMapColor &output);

};

#endif
