
/*
A simple "hello world" example.
Set the screen background color and palette colors.
Then write a message to the nametable.
Finally, turn on the PPU to display video.
*/

#include "neslib.h"
#include "vrambuf.h"


// link the pattern table into CHR ROM
//#link "chr_generic.s"
//#link "vrambuf.c"

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] =
{
0x21, // screen color
0x27, 0x12, 0x16, 0x00, // background palette 0
0x1C, 0x20, 0x2C, 0x00, // background palette 1
0x00, 0x1A, 0x20, 0x00, // background palette 2
0x23, 0x31, 0x41, 0x00, // sprite palette 0
0x16, 0x12, 0x28, 0x00, // sprite palette 1
0x36, 0x21, 0x19, 0x00, // sprite palette 2
0x1D, 0x37, 0x2B, // sprite palette 3
};

// main function, run after console reset
void main(void) {
  int i;
  char state = 0;
  pal_all(PALETTE);
  // write text to name table
  vram_adr(NTADR_A(2,2));		
  vram_write("This is", 7);
  vram_adr(NTADR_A(2,3));		
  vram_write("Eric McCaw's", 12);
  vram_adr(NTADR_A(2,4));		
  vram_write("first NES 'Game'!!", 18);	
  for(i = 1; i < 32; ++i){
  vram_adr(NTADR_A(i,15));		
  vram_put(0xc1);
  }
  vrambuf_clear();
  set_vram_update(updbuf); // updbuf = 0x100 -- start of stack RAM
  // enable PPU rendering (turn on screen)
  ppu_on_all();
  i = 8;
  // infinite loop
  while (1){
    // do this at the start of each frame
  char oam_id = 0;
  // Do this when "drawing" each sprite
  oam_id = oam_spr(i, 110, '?', 0,oam_id);
  // Do this to "hide" any remaining sprites
  oam_hide_rest(oam_id);
    state?--i:++i;
  
    if( i > 240  || i < 8){
      state = !state;
    }
    
    if(i >230)
    	vrambuf_put(NTADR_A(2, 5), "On the door", 11);
    else
    	vrambuf_put(NTADR_A(2, 5), "           ", 11);
    vrambuf_flush();
  }
}
