
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
const char PALETTE[32] =
{
0x03, // screen color
0x24, 0x16, 0x20, 0x0, // background palette 0
0x1c, 0x20, 0x2c, 0x0, // background palette 1
0x00, 0x1a, 0x20, 0x0, // background palette 2
0x23, 0x31, 0x41, 0x0, // sprite palette 0
0x00, 0x37, 0x25, 0x0, // sprite palette 1
0x36, 0x21, 0x19, 0x0, // sprite palette 2
0x1d, 0x37, 0x2b, // sprite palette 3
};

// main function, run after console reset
void main(void) {
  int i;
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
  
  // infinite loop
  while (1){
    // do this at the start of each frame
  char oam_id = 0;
  // Do this when "drawing" each sprite
  oam_id = oam_spr(100, 100, 0x09, 0,oam_id);
  // Do this to "hide" any remaining sprites
  oam_hide_rest(oam_id);
    
    vrambuf_put(NTADR_A(2, 5), "HELLO, WORLD!", 13);
    vrambuf_flush();
  }
}
