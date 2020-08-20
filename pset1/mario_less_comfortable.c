#include <cs50.h>
#include <stdio.h>

int main(void)
{ int i,j,height;
   do {
       height=get_int("Height: ");
       }
  while(height<1 || height>8 );
  { 

   for(i=0;i<height;i++)
   {
      for(j=0;j<height;j++)
      {
          if (j>=(height-(i+1)) && j<height)
          {
              printf("#");

          }
          else {printf(" ");}
          

      } printf("\n");
  }

  }
}
