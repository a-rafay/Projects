#include <iostream>
#include <stdio.h>

#include "sBox.h"
#define Uint unsigned int

using namespace std;

// ======================================================
// A function which returns a substituted value according
// to the box mentioned by the user.
// If box = 1, sBox is used for substitution.
// If box = 2, E_Table is used for substitution.
// If box = 3, L_Table is used for substitution.
// ======================================================

Uint substitute(Uint a, int box)
{
   Uint row, col;
   col = 0x0f;
   row = 0xf0;
   
   row = row & a;
   col = col & a;
   
   row = row>>4 ;
   if (box == 1)
   return(sBox[row][col]);
   
   if (box == 2)
   return (E_Table[row][col]);
   
   if (box == 3)
   return (L_Table[row][col]);
}


int main()
{
   int i,j,k;
   Uint message[4][4];
   
   // ======================================================
   // Initial text message is stored column wise.
   // Row wise was stored initially in "text" array just 
   // for the ease of user to change the value easily
   // in order to check the functionality of program
   // using different inputs, otherwise the whole operation
   // is done column wise in this program.
   // ======================================================
   
   cout<<"\nInitial Data: ";
   for (i = 0; i < 4; i++)
   {
      for(j = 0 ; j < 4; j++)
      {
         message[j][i] = text[i][j];
         printf("%x ",message[j][i]);
      }
   }
   
   // ======================================================
   // ============== Initial Sample key ====================
   // ======================================================
   
   cout<<"\n\nInitial Key:  ";
   for(i = 0; i < 16; i++)
   {
      printf("%x ",Key[i]);
   }
   

   // ======================================================
   // ==Before the rounds are started, round key is added===
   // ======================================================
   
   k=0;
   for(i=0;i<4;i++)
   {
      for (j=0;j<4;j++)
      {
         message[j][i] = message[j][i] ^ Key[k];
         k++;
      }
   
   }   

   // ======================================================
   // =============== 10 rounds of AES =====================
   // ======================================================
   
   for (int round = 0 ; round <10; round++)
   {
   
   // ======================================================
   // ========== Stage 1 : Byte Substitution ===============
   // ======================================================
   
      for (i=0;i<4;i++)
      {
         for(j=0;j<4;j++)
         {
            message[i][j] = substitute(message[i][j],1);
         }
      }

      int temp_val,indx;     
 
   // ======================================================
   // ============ Stage 2 : Row Shifting ==================
   // ======================================================
 
      for (i=1;i<4;i++)
      { 
         for(j=1;j<=i;j++)
         {
            temp_val = message[i][0];
            message[i][0]=message[i][1];
            message[i][1]=message[i][2];
            message[i][2]=message[i][3];
            message[i][3]=temp_val;
         }
      }
      
   // ======================================================
   // ============ Stage 3 : Column Mixing =================
   // ======================================================
      
      Uint message_new[4][4];
   
   // ===IF ITS THE LAST ROUND, SKIP COLUMN MIXING STAGE===
 
      if (round != 9)
      {
         for(k=0;k<4;k++)
         {
            for (i=0;i<4;i++)
            {
               temp_val = 0;
               for(j=0;j<4;j++)
               {
                  Uint L1,L2,L,E;
                  L1 = substitute(mul[k][j],3);
                  L2 = substitute(message[j][i],3);
                  L = L1+L2;
               
                  if (L > 0xff) L = L - 0xff;
                  
                  E  = substitute(L,2);
                  
                  temp_val = temp_val ^ E;
               }
                  message_new[k][i] = temp_val;  
            }
         }
      }
      
      if (round == 9)
      {
         for (i=0;i<4;i++){for(j=0;j<4;j++){message_new[i][j]=message[i][j];}}
      }

      
   // ======================================================
   // ======== Stage 4 : Generating Round Keys =============
   // ======================================================

      Uint gKey [4] = {Key[13],Key[14],Key[15],Key[12]};
      for(i=0;i<4;i++) gKey[i] = substitute(gKey[i],1);
          
      gKey[0] = gKey[0] ^ RC[round];

         
      for (i=0;i<16;i++)
      {
         if(i<4)
         {
            Key[i] = Key[i] ^ gKey[i];
         }
         else
         {
            Key[i] = Key[i] ^ Key[i-4];
         }
      }

      k=0;
      for(i=0;i<4;i++)
      {
         for (j=0;j<4;j++)
         {
            message_new[j][i] = message_new[j][i] ^ Key[k];
            k++;
         }
      
      }
      
      for (i = 0; i < 4; i++)
      {
         for(j = 0 ; j < 4; j++)
         {
            message[i][j] = message_new[i][j];
         }
      }
   }
   
   // ======================================================
   // ================ Encrypted Data ======================
   // ======================================================
   
   cout<<"\n\nEncrypted Data: ";
   for(i=0;i<4;i++)
   {
      for(j=0;j<4;j++)
      {
         printf("%x ",message[j][i]);
      }
   }
   cout<<endl;
   return 0;
}
