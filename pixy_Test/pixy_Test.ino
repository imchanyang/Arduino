
#include <Pixy2.h>
#include <Pixy2UART.h>
#include <Pixy2CCC.h>
#include <TPixy2.h>


Pixy2 pixy;

 

void setup() {

  Serial1.begin(115200);
  Serial1.print("start\n");

  pixy.init();
}

void loop() {
  int i;
  
  pixy.ccc.getBlocks();

  if(pixy.ccc.numBlocks) {
    Serial1.print("Detect");
    Serial1.println(pixy.ccc.numBlocks);
    for (i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial1.print(" block ");
      Serial1.print(i);
      Serial1.print(": ");
      pixy.ccc.blocks[i].print();
      
    }
  }
  
}
