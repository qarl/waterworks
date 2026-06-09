#include "ww.h"
	#include<string.h>


wwBlurBox::wwBlurBox(int s, int b)
{
  size = s;
  bordertype = b;

  divisiontable = new short int[size * 65536];

  if (size)
    for (int i = 0; i < size * 65536; i++)
      divisiontable[i] = i/size;

}

wwBlurBox::~wwBlurBox()
{
  delete [] divisiontable;
}


void wwBlurBox::doIt(const wwMapColor &input, wwMapColor &output)
{

  if (!size)
    {
      output=input;
      return;
    }


  wwMapColor temp;

  // do horizontal;

  for (int i = 0; i < WW_HEIGHT; i++)
    {
      int a[3];
      int buffer[WW_WIDTH + size][3];

      for (int c = 0; c < 3; c++)
	a[c] = 0;

      int halfsize = size/2;

      for (int j = -halfsize; j < 0; j++)
	for (int c = 0; c < 3; c++)
	  buffer[j + halfsize][c] = 0;


      for(int j = 0; j < WW_WIDTH ; j++)
	for (int c = 0; c < 3; c++)
	  {
	    a[c] += input.colors[i][j][c];

	    buffer[j + halfsize][c] = a[c];
	  }

      for(int j = WW_WIDTH + (size+1)/2 -1; j >= WW_WIDTH; j--)
	for (int c = 0; c < 3; c++)
	  {
	    buffer[j + halfsize][c] = a[c];
	  }

      for(int j = 0; j < WW_WIDTH; j++)
	for (int c = 0; c < 3; c++)
	  temp.colors[i][j][c] = divisiontable[(buffer[j + size][c] - 
						buffer[j][c])];
      }


  //do vertical

  for (int i = 0; i < WW_WIDTH; i++)
    {
      int a[3];
      int buffer[WW_HEIGHT + size][3];

      int halfsize = size/2;

      for (int c = 0; c < 3; c++)
	a[c] = 0;

      for (int j = -halfsize; j < 0; j++)
	for (int c = 0; c < 3; c++)
	  buffer[j + halfsize][c] = 0;

      for(int j = 0; j < WW_HEIGHT ; j++)
	for (int c = 0; c < 3; c++)
	  {
	    a[c] += temp.colors[j][i][c];

	    buffer[j + halfsize][c] = a[c];
	  }


      for(int j = WW_HEIGHT + (size+1)/2 -1; j >= WW_HEIGHT; j--)
	for (int c = 0; c < 3; c++)
	  {
	    buffer[j + halfsize][c] = a[c];
	  }


      
      for(int j = 0; j < WW_HEIGHT; j++)
	for (int c = 0; c < 3; c++)
	  output.colors[j][i][c] = divisiontable[(buffer[j + size][c] - 
						  buffer[j][c])];

    }
}



void wwBlurBox::doIt(const wwMapGray &input, wwMapGray &output)
{


  if (!size)
    {
      output=input;
      return;
    }


  wwMapGray temp;

  // do horizontal;

  for (int i = 0; i < WW_HEIGHT; i++)
    {
      int a;
      int buffer[WW_WIDTH + size];

      a = 0;

      int halfsize = size/2;

      for (int j = -halfsize; j < 0; j++)
	  buffer[j + halfsize] = 0;


      for(int j = 0; j < WW_WIDTH ; j++)
	  {
	    a += input.grays[i][j];

	    buffer[j + halfsize] = a;
	  }

      for(int j = WW_WIDTH + (size+1)/2 -1; j >= WW_WIDTH; j--)
	  {
	    buffer[j + halfsize] = a;
	  }

      for(int j = 0; j < WW_WIDTH; j++)
	  temp.grays[i][j] = divisiontable[(buffer[j + size] - 
						buffer[j])];
      }


  //do vertical

  for (int i = 0; i < WW_WIDTH; i++)
    {
      int a;
      int buffer[WW_HEIGHT + size];

      int halfsize = size/2;

      a = 0;

      for (int j = -halfsize; j < 0; j++)
	  buffer[j + halfsize] = 0;

      for(int j = 0; j < WW_HEIGHT ; j++)
	  {
	    a += temp.grays[j][i];

	    buffer[j + halfsize] = a;
	  }


      for(int j = WW_HEIGHT + (size+1)/2 -1; j >= WW_HEIGHT; j--)
	  {
	    buffer[j + halfsize] = a;
	  }


      
      for(int j = 0; j < WW_HEIGHT; j++)
	output.grays[j][i] = divisiontable[(buffer[j + size] - 
						  buffer[j])];

    }
}




void wwBlurBox::doIt(const wwMapValue &input, wwMapValue &output)
{

  if (!size)
    {
      output=input;
      return;
    }



  wwMapValue temp;

  // do horizontal;
    for (int i = 0; i < WW_HEIGHT; i++)
      {
	int a = 0;
	long int buffer[WW_WIDTH + size];

	int halfsize = size/2;

	for (int j = -halfsize; j < 0; j++)
	  buffer[j + halfsize] = 0;


	for(int j = 0; j < WW_WIDTH ; j++)
	  {
	    a += input.values[i][j];

	    buffer[j + halfsize] = a;
	  }

	for(int j = WW_WIDTH + (size+1)/2 -1; j >= WW_WIDTH; j--)
	  {
	    buffer[j + halfsize] = a;
	  }

	for(int j = 0; j < WW_WIDTH; j++)
	  temp.values[i][j] = divisiontable[(buffer[j + size] - 
					       buffer[j])];
      }


  //do vertical
    for (int i = 0; i < WW_WIDTH; i++)
      {
	int a = 0;
	int buffer[WW_HEIGHT + size];

	int halfsize = size/2;

	for (int j = -halfsize; j < 0; j++)
	  buffer[j + halfsize] = 0;


	for(int j = 0; j < WW_HEIGHT ; j++)
	  {
	    a += temp.values[j][i];

	    buffer[j + halfsize] = a;
	  }


	for(int j = WW_HEIGHT + (size+1)/2 -1; j >= WW_HEIGHT; j--)
	  {
	    buffer[j + halfsize] = a;
	  }


	
	{// gross - our c-compiler has LOUSY optimization
	  short int *p = (short int *)&output.values[0][i];
	  short int *q = (short int *)&output.values[WW_HEIGHT-1][i];
	  int *b = &buffer[0];
	  for(short int *j = p; j <= q; j += WW_WIDTH)
	    {
	      *j = divisiontable[*(b+size)-*b];
	      b++;
	    }
	}
      }
}
