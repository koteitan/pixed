#include <Arduboy.h>
#define WX 128
#define WY 64
unsigned char *vram; // =arduboy.getBuffer()

#define KEY_L 0
#define KEY_R 1
#define KEY_U 2
#define KEY_D 3
#define KEY_B 4
#define KEY_A 5
#define KEYS  6
int button[KEYS]={ LEFT_BUTTON, RIGHT_BUTTON, UP_BUTTON, DOWN_BUTTON, A_BUTTON, B_BUTTON};
boolean keypressed[KEYS];
Arduboy arduboy;
AbPrinter text(arduboy);
int frame_rate = 60;  // frames/sec
int cx=WX/2;
int cy=WY/2;
int cc=0;
int cb=0;
int clkNow=0;
int clkMax=10;
int keyRepeatNow = 0;
int keyRepeatThr = 20;
void setup(){
  arduboy.begin();
  vram = arduboy.getBuffer();
  arduboy.setFrameRate(frame_rate);
}

void loop(){
  for(int k=0;k<KEYS;k++) keypressed[k] |= arduboy.pressed(button[k]); // latch key
  if (!(arduboy.nextFrame())) return;
  loopGame();
  for(int k=0;k<KEYS;k++) keypressed[k]=0; //clear key
}

void loopGame(){
  //key----------
  if(keypressed[KEY_A])cb=1;
  if(keypressed[KEY_B])cb=0;
  if(keypressed[KEY_L]||keypressed[KEY_R]||keypressed[KEY_U]||keypressed[KEY_D]){
    int isMove = 0;
    if(keyRepeatNow==0){
      keyRepeatNow++;
      isMove = 1;
    }else{
      if(keyRepeatNow==keyRepeatThr){
        isMove = 1;
      }else{
        keyRepeatNow++;
      }
    }
    if(isMove){
      arduboy.drawPixel(cx,cy,cb);
      if(keypressed[KEY_L])cx--;
      if(keypressed[KEY_R])cx++;
      if(keypressed[KEY_U])cy--;
      if(keypressed[KEY_D])cy++;
      if(cx<0) cx=WX-1;
      if(cy<0) cy=WY-1;
      if(cx>=WX) cx=0;
      if(cy>=WY) cy=0;
      cb=arduboy.getPixel(cx,cy);
    }
  }else{// L|R|U|D
    keyRepeatNow = 0;
  }
  //draw---------
  arduboy.drawPixel(cx,cy,cc);
  if(clkNow==clkMax){
    cc^=1;
    clkNow=0;
  }else{
    clkNow++;
  }
  arduboy.display();
}





