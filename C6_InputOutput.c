#define GPIO_PORTF_DATA_R   (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R    (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R  (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R    (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R    (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R   (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R     (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R  (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R   (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R      (*((volatile unsigned long *)0x400FE108))

#define PA5 (*((volatile insigned long *) 0x40004080))

void PortF_Init(void){ 
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020; //F clock
    delay = SYSCTL_RCGC2_R; //DELAY
    GPIO_PORTF_LOCK_R = 0x4C4F434B; //Unlocks protF PF0
    GPIO_PORTF_CR_R = 0x1F; //Allow changes to PF4-0
    GPIO_PORTF_AMSEL_R = 0x00; //disabled analog funciton
    GPIO_PORTF_PCTL_R = 0x00000000; // GPIO clear bit PCTL
    GPIO_PORTF_DIR_R = 0x0E; //PF4, PF0 input, PF3, PF2, PF1 output
    GPIO_PORTF_AFSEL_R = 0x00; //No alternate function
    GPIO_PORTF_PUR_R = 0x11; //enable pull-up resistors on PF4,PF0
    GPIO_PORTF_DEN_R = 0x1F; //enable digital pins PF4-PF0
}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 100 ms
  }
}

unsigned long In; //input from PF4
unsigned long Out; //Output to PF2 (Blue LED)

//void PortF_Init(void);

int main(void){
    
	PortF_Init();    // make PF3-1 out (PF3-1 built-in LEDs)

  while(1){
    In = GPIO_PORTF_DATA_R&0x10;   // read PF4 into Sw1
    In = In>>2;                    // shift into position PF2
    Out = GPIO_PORTF_DATA_R;
    Out = Out&0xFB;
    Out = Out|In;                   // affect the bits in which we are interested and leave the remaining bits unchanged
    // GPIO_PORTF_DATA_R = In;
    GPIO_PORTF_DATA_R = Out;        // output
  }
}
