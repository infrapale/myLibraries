#ifndef akbd4_h
#define akbd4_h
#include <Arduino.h>


#define NBR_ROW 4
#define NBR_COL 4
#define KBD_PIN 15
#define KEY_TOL 16
#define KBD_DEB 4
#define LONG_PRESS 60

class akbd4
{
  public:
    akbd4(byte col1,byte col2,byte col3,byte col4);
    void begin(void);
    void set_aval(byte key_indx, unsigned int key_value);
    void scan(void);
    char read(void);
	uint16_t read_dur(void);
    int rd_analog(byte col_indx);
  private:
    byte _pin_nbr[NBR_COL];
    volatile char lastKey;
	volatile char rdKey;
    volatile int  kbdDebCntr;
	volatile int  kbdPressedCntr;
    volatile int  kbdState;


};

#endif
