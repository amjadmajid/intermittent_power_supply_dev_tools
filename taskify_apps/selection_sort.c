#include <msp430.h> 
#include <ipos.h>

/*
 
 The Original program 

void sortAlgo(int arr[], int arrLen){
    for (int i=0; i< arrLen-1;i++){
        for(int j=i+1; j < arrLen; j++){
            if(arr[i] >  arr[j]) { //ascending order
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

*/


// Tasks Prototypes
void task_finish();
void task_outer_loop();
void task_inner_loop();

unsigned int arr[] =  {3,1,4,6,9,5,10,8,16,20};
unsigned int arr2[] = {3,1,4,6,9,5,10,8,16,20};

unsigned int arr_len = 10;
unsigned int i =  0;
unsigned int j = 1;


void task_inner_loop()
{

    if( arr[i]  > arr[j] )
    {
        unsigned int temp = arr[ j];
        arr[j] =  arr[i];
        arr[i] =  temp;
    }

    if( j < (arr_len-1) )
    {
        // execute the same task
    }else{
      // go to task_outer_loop
    }
    
    j++;
}


void task_outer_loop()
{
    i++;
    if(i < arr_len)
    {
      // go to task_inner_loop
    }else{
      // go to task_finish
    }

    j= i+1;
}



void task_finish()
{

  // reset everything
  unsigned cct;
  for(cct=0; cct< arr_len; cct++)
  {
      arr[cct] =  arr2[cct];
  }

  i = 0;
  j = 1;
}

void init()
{
  WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
  // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings.
  PM5CTL0 &= ~LOCKLPM5;       // Lock LPM5.
}

int main(void) {
    init();

    while(1){
      task_inner_loop();
      task_outer_loop();
      task_finish();
    }
  
       return 0;
}
