#include <cs50.h>
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
// Program based on Luhn's Algorithm

int main()

{  long num;
   int count = 0;
   do
   {
       //asking user to input credit card number but without any - or any other char
       num = get_long("Number: "); 
   } // while number is less than or equal to 0 do the above statement
   while (num <= 0);
   {
       long n = num;
       // counting the total digits in the credit card number
       while (n!=0)    
       {
           n=n/10;
           ++count;
       }
        // condition for checking american express card
       if (count == 15)  
       {
           // power function in math lib
           double a = pow(10,13); 
           int b = num / a;
           n = num;
           // if num starts with 34 or 37 and follows checksum
           if ((b==34) || (b==37) ) 
           {
               int sum=0,no[count];
               //storing the card number in the form of array
               for (int i = (count-1); i >= 0; i--) 
               {
                   no[i] = n % 10;
                   n = n / 10;
                   
               }
               //finding the sum of alternate no starting from last second to verify the check sum
               for (int i = (count-2); i >= 0; i--)             
               {
                   int m = no[i] * 2;
                   int counter = 0;
                   //counting the no. which is multiplied by 2 if this no is a two digit no. then both the digits will be added seperately
                   while (m != 0)                   
                   {
                       m = m / 10;
                       ++counter;
                       
                   }
                   m = no[i] * 2;
                   if (counter == 2)
                   {
                       sum = sum + m % 10;
                       m = m / 10;
                       sum = sum + m % 10;
                       
                   }
                   else
                   {
                       sum = sum + m;
                       
                   }
                   i = i - 1;
                   
               }
               for (int i = count - 1;i >= 0; i--)
               {
                  sum = sum + no[i];
                  i = i - 1;
                   
               }
               if (sum % 10 == 0)
               {
                   printf("AMEX\n");
                   
               }
               else
               {
                   printf("INVALID\n");
                   
               }
               
           }
           else
           {
               printf("INVALID\n");
           }
           
       }
       else if (count == 16) // condition to check master card and visa card
       {
           double a = pow(10, 14);
           int b = num / a;
           n = num;
           if ((b == 51) || (b == 52) || (b == 53) || (b == 54) || (b == 55))
           {
               int sum = 0, no[count];
               for (int i = (count-1); i >= 0; i--)
               {
                   no[i] = n % 10;
                   n = n / 10;
                   
               }
               for (int i = (count-2); i >= 0; i--)
               {
                   int m = no[i] * 2;
                   int counter = 0;
                   while (m != 0)
                   {
                       m = m / 10;
                       ++counter;
                       
                   }
                   m = no[i] * 2;
                   if (counter == 2)
                   {
                       sum = sum + m % 10;
                       m = m / 10;
                       sum = sum + m % 10;
                       
                   }
                   else
                   {
                      sum = sum + m;
                       
                   }
                   i = i - 1;
                   
               }
               for (int i = count-1; i >= 0; i--)
               {
                   sum = sum + no[i];
                   i = i - 1;
                   
               }
               if (sum % 10 == 0)
               {
                   printf("MASTERCARD\n");
                   //using exit so that it directly goes out of the program and without checking other conditions

                   exit(0);                                    
                }
                else
                {
                    printf("INVALID\n");
                    exit(0);
                    
                }
               
           }
              a = pow(10,15);
              b = num / a;
              n = num;
              if (b == 4)
              {
                  int sum = 0, no[count];
                  for (int i = (count-1); i >= 0; i--)
                  {
                      no[i] = n % 10;
                      n = n / 10;
                      
                  }
                  for (int i = (count-2); i >= 0; i--)
                  {
                      int m = no[i] * 2;
                      int counter = 0;
                      while (m != 0)
                      {
                          m = m / 10;
                          ++counter;
                          
                      }
                      m = no[i] * 2;
                      if (counter == 2)
                      {
                          sum = sum + m % 10;
                          m = m / 10;
                          sum = sum + m % 10;
                          
                      }
                      else
                      {
                          sum = sum + m;
                          
                      }
                      i = i - 1;
                      
                  }
                  for (int i = count-1; i >= 0; i--)
                  {
                      sum = sum + no[i];
                      i = i - 1;
                      
                  }
                  if (sum % 10 == 0)
                  {
                      printf("VISA\n");
                      
                  }
                  else
                  {
                      printf("INVALID\n");
                      
                  }
                  
              }
              else
              {
                  printf("INVALID\n");

              }
           
       }
       else if (count == 13) // condition for checking visa card
       {
           double a = pow(10,12);
           int b = num / a;
           n = num;
           if (b == 4)
           {
               int sum = 0, no[count];
               for(int i = (count-1); i >= 0; i--)
               {
                   no[i] = n % 10;
                   n = n / 10;
                   
               }
               for (int i = (count-2); i >= 0; i--)
               {
                   int m = no[i] * 2;
                   int counter = 0;
                   while(m != 0)
                   {
                       m = m / 10;
                       ++counter;
                       
                   }
                   m = no[i] * 2;
                   if (counter == 2)
                   {
                       sum = sum + m % 10;
                       m = m / 10;
                       sum = sum + m % 10;
                       
                   }
                   else
                   {
                       sum = sum + m;
                       
                   }
                   i = i - 1;
                   
               }
               for (int i = count-1; i >= 0; i--)
               {
                   sum = sum + no[i];
                   i = i - 1;
                   
               }
               if (sum % 10 == 0)
               {
                   printf("VISA\n");
                   
               }
               else
               {
                   printf("INVALID\n");
                   
               }
               
           }
           else
           {
               printf("INVALID\n");
               
           }
           
       }
       else   // or else if wrong number is inserted then print invalid
       {
           printf("INVALID\n");
       }
       
   }

}
