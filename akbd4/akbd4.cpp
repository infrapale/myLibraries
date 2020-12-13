
#include "akbd4.h"


akbd4::akbd4(byte col1,byte col2,byte col3,byte col4)
{
  _pin_nbr[0] = col1;
  _pin_nbr[1] = col2;
  _pin_nbr[2] = col3;
  _pin_nbr[3] = col4;
 
  for (int i =0;i<4;i++) pinMode(_pin_nbr[i], INPUT);  
  
}

void akbd4::begin(void)
{
  kbdState=0;
}



// Row1-4: 179 - 409 - 605 - 847

unsigned int  key_val[NBR_ROW] = {
  179,  //1   
  409,  //2  
  605,  //3  
  846   //4  
};

char key_char[NBR_ROW][NBR_COL] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
void akbd4::set_aval(byte key_indx, unsigned int key_value){
    key_val[key_indx] = key_value;
}    

//int kbdPin = 15; 
int akbd4::rd_analog(byte col_indx){
  return( analogRead(_pin_nbr[col_indx]));
}
void akbd4::scan(void) {
  int kbdVal = 0; 
  int d;
  int row=0;
  char k=0;
  boolean done=false;
  byte col=0;
 
    while (! done){
        kbdVal = analogRead(_pin_nbr[col]);
        if (kbdVal < (1023- KEY_TOL) ) done = true;
        else col++;
        if (col>= NBR_COL) done = true;
    }
    if (kbdVal < (1023- KEY_TOL) ){
        done = false;
		k = 0x00;
        while (! done ){
            d = kbdVal-key_val[row];
            d = abs(d);
            if (d <= KEY_TOL) {
                k = key_char[row][col];
                done = true;
                //Serial.print("k="); Serial.println(k);
            }
            else row++;
            if (row>=NBR_ROW) done = true;
        }
	}
    //Serial.print("kbdState="); Serial.println(kbdState);       
    switch( kbdState ){
        case 0:  // no key pressed
        if (k) {
           lastKey = k;
           kbdDebCntr=KBD_DEB;
		   kbdPressedCntr = 0;
           kbdState= 1;
        }
        break;
        case 1:  // key pressed but debounce still active
         if (k == lastKey) {
			 kbdPressedCntr++;
             if (kbdDebCntr) kbdDebCntr--;
             else {
				 kbdState= 2;
				 rdKey = k;
			 }	 
         } else kbdState = 0;
         break;
        case 2:  // key pressed and accepted, not read
         if (k == rdKey) {
			 kbdPressedCntr++;
         } 
		 else {
			 kbdState = 3;
		 } 
         break;
        case 3:  // key read
           // wait to be read
           break;
        case 4:  // key read
           rdKey = 0x00;
		   kbdState = 0;
           break;
    }          
    if (kbdState == 0){
         lastKey = k;
         kbdDebCntr=KBD_DEB;      
    }
   
}




char akbd4::read(void){
  if (kbdState == 3){ 
     kbdState = 4;
     return(rdKey);
  } else return(0);
}

uint16_t akbd4::read_dur(void){
	uint16_t res = 0;
  if (kbdState == 3){ 
     kbdState = 4;
	 //Serial.print("Pressed="); Serial.println(kbdPressedCntr);
	 if (kbdPressedCntr > LONG_PRESS) res = 0x0100;
	 res = res | (uint16_t)rdKey;
     return(res);
  } else return(0);
}