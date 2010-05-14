#include <stdio.h>
#include <graphics.h>
//#include<conio.h>
//#include<stdlib.h>
#include<math.h>

void dec2bin(int decimal, char *binary, int noOfStages);
void shuffle(int inputs[], int n);
void dec2binint(int decimal, int *binaryint, int noOfStages);
 

int main()
{
  char binary[80];
  int gd=DETECT,gm, f, i, j, n, x1, x2, y, noOfSwitches, noOfStages, binaryint[80], inp, data, y1; 
  int* inputs;
  int valid_input;
  char output[256];
  //clrscr();

  //initializing graph
  initgraph(&gd,&gm,"..\bgi");
  //initgraph(&gd,&gm,"C:\\TC\\BGI");
  valid_input = 0;
  while( valid_input == 0 ) {
    printf("Enter the number of inputs (N): ");
    scanf("%d", &n);
    if(n % 2 == 0 )  valid_input = 1;
    else  printf("Invalid. N must be in denomination of 2\n");
  }

  valid_input = 0;
  while( valid_input == 0 ) {
    printf("Enter the input, where the data starts its transmission: ");  
    scanf("%d", &inp);
    if(inp < n )  valid_input = 1;
    else  printf("Invalid. Input can't exceed N.\n");
  }

  valid_input = 0;
  while( valid_input == 0 ) {
    printf("Enter the out put, where data ends its journey.: ");  
    scanf("%d", &data);
    if(data < n )  valid_input = 1;
    else  printf("Invalid. Input can't exceed N.\n");
  }
  system("clear"); 
  //clrscr();
  
  setbkcolor(6);
  setcolor(2);
   
 

// Put numbers into text
  sprintf(output, "Omega network for %d X %d. Input: %d Output: %d ", n, n, inp, data);
  outtextxy(15, 10,output);
   
  setcolor(15);
  
  
  //Calculate the no of switches and stages in omega network for given input
  noOfSwitches = n/2;
  noOfStages   = ceil(log(n)/log(2));

  //Initilizing inputs array
  inputs = (int*) malloc(n*sizeof(int));

  for(i=0;i<n;i++) {
   inputs[i] = i;
  } 

  //Suffle the input array
   shuffle(inputs, n);

  for( i=0; i< n; i++) { 
    //Convert input into binary
    dec2bin(i, binary, noOfStages);

    //Writting binary input value to the canvas
    outtextxy(15, 40 + (25 * i), binary);
  }

  for(j=0; j< noOfStages; j++){
   x1 = 45 + (130 * j);
   x2 = 65 + (130 * j);

  //Drwing network. http://en.wikipedia.org/wiki/File:Omega_Network.jpg
   for( i=0; i<n; i++) { 
     //------------------for reference of x and y-----------------------
     //line( int x1, int y1, int x2, int y2 );
     //rectangle( int left, int top, int right, int bottom );
     //---------------------------------------------------------

     //drawing a small line out from binary input. 
     line(x1, 45 + (25 * i), x2, 45 + (25 * i));

     //drawing the sec part of the line to join binary input to the next level's input. 
     //note this is not stright line. so y1 and y2 changes here
     line(x1 + 20, 45 + (25 * i), x2 + 40, 45 + (25 * inputs[i]));

     //drawing the sec part of the line.  note x2 of above line is x1 of this.
     line(x1 + 60, 45 + (25 * inputs[i]), x2 + 60, 45 + (25 * inputs[i]));

   } //for loop of i ends here


   for( i=0; i< noOfSwitches; i++) { 
    
    bar(x2 + 60, 38 + (50 * i), (x2 + 60 + 50), 78 + (50 * i));
   }
  
 } //for loop of noOfStages ends here

  

 //Drawing all stages and their inputs are over. Now draw the small output lines from final stage
 for( i=0; i<n; i++) { 
   //drawing the line which goes out from the final stage switches
   line(x2 + 110, 45 + (25 * i), x2 + 125, 45 + (25 * i));

   //Convert input into binary
    dec2bin(i, binary, noOfStages);

   //Writting binary input value to the canvas
   outtextxy(x2 + 130, 40 + (25 * i), binary);
 }
 
 //
 //Drawing of the network over. Now will draw the data path
 //
  setcolor(2);
    
  //First convert the data into binary
  dec2binint(data, binaryint, noOfStages);

  //Now drawing transimission
  //check Destination-tag routing in http://en.wikipedia.org/wiki/Omega_network
  //The msb of the destination address is used to select the output of the switch in the first stage; 
  //if the most significant bit is 0, the upper output is selected, and if it is 1, the lower output is selected. 
 

  y = 45;
  y1 = y;

  for(j=0; j < noOfStages; j++){
    x1 = 45 + (130 * j);
    x2 = 65 + (130 * j);
   
    //Input lines
    line(x1, y + (25 * inp), x2, y + (25 * inp) );
    line(x1 + 20, y + (25 * inp), x2 + 40, y + (25 * inputs[inp]));
    line(x1 + 60, y + (25 * inputs[inp]), x2 + 60, y + (25 * inputs[inp]));
  
    //input to the next stage
     inp = inputs[inp];

    //inside the switch
    //Decide: upward or downward transmission
    if (binaryint[j] == 1){ //downward
      //Only if input is in 1 of this switch, make it down/ else stragight
      if (inp % 2 == 0) (y1 = y + 25);
      else (y1 = y);
    }
    else{
      //Only if input is in 0 of this switch, make it up/ else stragight
      if (inp % 2 == 1) (y1 = y - 25);
      else (y1 = y);
    }
  
    //Line inside switch. Straight or down or up
    line(x2 + 60, y + (25 * inp), (x2 + 60 + 50), y1 + (25 * inp));
      
    //Switch. transmit upward or downward
    if (binaryint[j] == 1){ //downward
      //Only if input is in 1 of this switch, make it down/ else stragight
      if (inp % 2 == 0) 
        inp = inp + 1;
    }
    else{ //upward
      //Only if input is in 0 of this switch, make it up/ else stragight
       if (inp % 2 == 1) 
         inp =  inp - 1 ;
    }
 
  }

  //Final green line out 
  line(x2 + 110, 45 + (25 * inp), x2 + 125, 45 + (25 * inp));
  

  getch();
  return 0;
}

//
// accepts a decimal integer and returns a binary coded string array
//
void dec2bin(int decimal, char *binary, int noOfStages)
{
  int  k = 0, n = 0;
  int  remain;
  char temp[80];
  
  do 
  {
    remain    = decimal % 2;
    decimal   = decimal / 2;
    // converts digit 0 or 1 to character '0' or '1'
    temp[k++] = remain + '0';
  } while (decimal > 0);

   //Little hack required to add trailing 0's in cases like 0, 1, 2
  if (k < noOfStages ){
    while (k < noOfStages)
     {
      temp[k++] = '0';
     }
  }

  // reverse the spelling
  while (k >= 0)
    binary[n++] = temp[--k];
    binary[n-1] = 0; 
}

//
// accepts a decimal integer and returns a binary coded integer array
//

void dec2binint(int decimal, int *binaryint, int noOfStages)
{
  int  i = 0, n = 0;
  int  remain;
  int temp[80];
  
  while (decimal >0) 
  { 
   temp[i] = decimal%2; 
   decimal = decimal/2; 
   i++; 
  } 

  //Little hack required to add trailing 0's in cases like 0, 1, 2
  if (i < noOfStages ){
    while (i < noOfStages)
     {
      temp[i++] = 0;
     }
  }

  // reverse the spelling
  while (i >= 0)
   binaryint[n++] = temp[--i];
   binaryint[n-1] = 0; 
  }
   
//
//This method suffles the input as required by omega network
//
void  shuffle(int inputs[], int n)
{
  int i, mid, j;
  int* temp;

  
  mid = n/2;
  temp = (int*) malloc(n*sizeof(int));

  //First part of the suffled array
  for( i=0; i<=mid; i++) { 
   temp[i] =  inputs[i] + i;
  }
   

  //Second part of the suffled array
  for( j=0; j<mid; j++) { 
   temp[mid + j] = inputs[mid + j] - (mid - j - 1);
  }

    
  for (i=0; i<n; i++) {
    inputs[i] = temp[i];
  } 

  free(temp);
}
