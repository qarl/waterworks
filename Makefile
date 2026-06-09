
PROGS  = WaterWorks BloodWorks SlimeWorks GhostWorks TimeWorks FireWorks \
	Skinny Fatty ToonWorks proto timer c
OBJS   = wwDisplaySDL.o wwCameraV4L.o wwLocator.o wwGamma.o wwMapColor.o \
	wwMapValue.o wwFireRender.o wwWaterSimulator.o wwWaterSpigot.o \
	wwMapVector.o wwWaterRender.o wwBloodRender.o wwWaterSpigotRandom.o \
	wwWaterSpigotMultiRandom.o wwBloodWorks.o wwMain.o \
	wwSlimeWorks.o wwSlimeRender.o wwTimeBlur.o wwBlurBox.o \
	wwGhostWorks.o wwMapGray.o wwWaterWorks.o wwTimer.o \
	wwBlurFast.o wwFireWorks.o wwFilePPM.o wwNoisePerlin.o \
	wwMapPointer.o wwSlope.o wwWarp.o wwStretch.o wwSkinny.o \
	wwFatty.o wwSplit.o wwMerge.o wwRemapGray.o wwRemapGrayColor.o \
	wwColorize.o wwRub.o wwProto.o wwMultiply.o wwGradientFilePPM.o \
	wwToonWorks.o wwFileInPPM.o wwBurn.o wwConvert.o \
	wwAdd.o wwAddClipped.o wwScale.o wwInvert.o \
	wwOverlay.o wwFireSimulator.o \
	perlin.o

CPPFLAGS = -g -O3 -I/usr/include/SDL -march=i686

WWLIB  = libww.a
WWLINK = $(WWLIB)

SDLLINK = -lSDL -lpthread

PPMLINK = -lpbm -lppm

LINK = $(WWLINK) $(SDLLINK) $(PPMLINK)

all : $(PROGS)
	chmod a+rX *

$(WWLIB) : $(OBJS) ww.h Makefile
	ar cr $(WWLIB) $(OBJS)

WaterWorks: WaterWorks.o $(WWLIB)
	g++ -o WaterWorks WaterWorks.o $(LINK)

BloodWorks: BloodWorks.o $(WWLIB)
	g++ -o BloodWorks BloodWorks.o $(LINK)

SlimeWorks: SlimeWorks.o $(WWLIB)
	g++ -o SlimeWorks SlimeWorks.o $(LINK)

GhostWorks: GhostWorks.o $(WWLIB)
	g++ -o GhostWorks GhostWorks.o $(LINK)

TimeWorks: TimeWorks.o $(WWLIB)
	g++ -o TimeWorks TimeWorks.o $(LINK)

FireWorks: FireWorks.o $(WWLIB)
	g++ -o FireWorks FireWorks.o $(LINK)

Skinny: Skinny.o $(WWLIB)
	g++ -o Skinny Skinny.o $(LINK)

Fatty: Fatty.o $(WWLIB)
	g++ -o Fatty Fatty.o $(LINK)

ToonWorks: ToonWorks.o $(WWLIB)
	g++ -o ToonWorks ToonWorks.o $(LINK)

c: c.o $(WWLIB)
	g++ -o c c.o $(LINK)



proto: proto.o $(WWLIB)
	g++ -o proto proto.o $(LINK)

timer: timer.o $(WWLIB)
	g++ -o timer timer.o $(LINK)

clean:
	rm -f \#*\# *.o *~ core* $(PROGS) $(WWLIB)
