
#define CLIP0(x) ((x)<0?0:(x))
#define CLIP255(x) ((x)>255?255:(x))

#define CLIPWIDTH(x) ((x)>(WW_WIDTH-1)?(WW_WIDTH-1):(x))
#define CLIPHEIGHT(x) ((x)>(WW_HEIGHT-1)?(WW_HEIGHT-1):(x))

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define WW_MAP_LOOP(VARIABLE1,VARIABLE2) for(int VARIABLE1 = 0; VARIABLE1 < WW_HEIGHT; VARIABLE1++) for(int VARIABLE2 = 0; VARIABLE2 < WW_WIDTH; VARIABLE2++)
