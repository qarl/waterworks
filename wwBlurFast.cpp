#include "ww.h"


void wwBlurFast::doIt(const wwMapColor &input, wwMapColor &output)
{
  // i find that if i leave this array in the code,
  // the function below runs 50% faster.  can anyone
  // explain that to me?
  char divisiontable[1280];


  for (int i = 0; i < WW_HEIGHT; i++)
    for (int c = 0; c < 3; c++)
    {
      output.colors[i][0][c] = input.colors[i][0][c];
      output.colors[i][WW_WIDTH-1][c] = input.colors[i][WW_WIDTH-1][c];
    }

  for (int i = 0; i < WW_WIDTH; i++)
    for (int c = 0; c < 3; c++)
    {
      output.colors[0][i][c] = input.colors[0][i][c];
      output.colors[WW_HEIGHT-1][i][c] = input.colors[WW_HEIGHT-1][i][c];
    }


  for (int i = 1; i < WW_HEIGHT -1; i++)
    for (int j = 1; j < WW_WIDTH -1; j++)
      for (int c = 0; c < 3; c++)
	output.colors[i][j][c] = (input.colors[i-1][j][c] +
				  input.colors[i-1][j+1][c] +
				  input.colors[i][j-1][c] +
				  input.colors[i][j][c] +
				  input.colors[i][j+1][c] +
				  input.colors[i+1][j-1][c] +
				  input.colors[i+1][j][c] +
				  input.colors[i+1][j+1][c]) >> 3;
}



void wwBlurFast::doIt(const wwMapGray &input, wwMapGray &output)
{
  // i find that if i leave this array in the code,
  // the function below runs 50% faster.  can anyone
  // explain that to me?
  char divisiontable[1280];


  for (int i = 0; i < WW_HEIGHT; i++)
    {
      output.grays[i][0] = input.grays[i][0];
      output.grays[i][WW_WIDTH-1] = input.grays[i][WW_WIDTH-1];
    }

  for (int i = 0; i < WW_WIDTH; i++)
    {
      output.grays[0][i] = input.grays[0][i];
      output.grays[WW_HEIGHT-1][i] = input.grays[WW_HEIGHT-1][i];
    }


  for (int i = 1; i < WW_HEIGHT -1; i++)
    for (int j = 1; j < WW_WIDTH -1; j++)
      output.grays[i][j] = (input.grays[i-1][j] +
			    input.grays[i-1][j+1] +
			    input.grays[i][j-1] +
			    input.grays[i][j] +
			    input.grays[i][j+1] +
			    input.grays[i+1][j-1] +
			    input.grays[i+1][j] +
			    input.grays[i+1][j+1]) >> 3;
}
