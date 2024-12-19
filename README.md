**************************************
          Analógicos:
**************************************
Joy L = CH1 Y CH2 ;

CH1= min 512, reposo 8, max -508;

CH2= min -508, reposo 8, max 512;

Joy R= CH4 Y CH5

CH4= min 512,  reposo 4, max -508

CH5= min -508, reposo 4, max 512

L2 brake =   CH3  0-1020

R2 throttle= CH6  0-1020

**************************************
          BOTONES:
**************************************
Dpad UP =    dpad: 0x01

Dpad DOWN =  dpad: 0x02

Dpad LEFT =  dpad: 0x08

Dpad RIGHT = dpad: 0x04

X  = buttons: 0x0001

0  = buttons: 0x0002

^  = buttons: 0x0008

[] = buttons: 0x0004

L1 =    buttons: 0x0010 

R1 =    buttons: 0x0020

JOY L = buttons: 0x0100 

JOY R = buttons: 0x0200

**************************************
          ESPECIALES:
**************************************
PS =     misc: 0x01

CREATE = misc: 0x02

OPT =    misc: 0x04

MIC =    misc: 0x08



Led colors = ctl->setColorLED(255, 0, 0);

Led user = ctl->setPlayerLEDs(led & 0x0f); // Turn on the 4 LED. Each bit represents one LED.
