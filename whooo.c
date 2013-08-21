#include <gb/gb.h>
#include <gb/cgb.h>

#include "maps.c"

#define MARIO 0
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144


const UWORD spritepalette[] = {
	32301, 430, 27, 2783
};

unsigned char spritetiles[] = {
	173,173,173,173,203,203,171,171,169,169,0,0,0,0,0,0,
	72,72,168,168,170,170,170,170,69,69,0,0,0,0,0,0,
	148,148,149,149,137,137,137,137,8,8,0,0,0,0,0,0,
	152,152,84,84,88,88,84,84,148,148,0,0,0,0,0,0,
	196,196,170,170,202,202,170,170,164,164,0,0,0,0,0,0,
	152,152,144,144,152,152,144,144,216,216,0,0,0,0,0,0,
};

unsigned char mario[] = {
	0, 7, 0, 15, 15, 1, 31, 11, 31, 9, 31, 7, 7, 7, 13, 2, 0, 192, 0, 248, 224, 160, 248, 184, 252, 220, 248, 128, 240, 240, 192, 0, 29, 2, 60, 3, 58, 55, 56, 63, 48, 63, 0, 14, 28, 0, 60, 0, 184, 64, 60, 192, 92, 236, 28, 252, 12, 252, 0, 112, 56, 0, 60, 0
};


const UWORD backgroundpalette[] = {
	RGB_RED, RGB_YELLOW, RGB_BLUE, RGB_GREEN,
	RGB_BLACK, RGB_DARKGRAY, RGB_LIGHTGRAY, RGB_WHITE
};
unsigned char backgroundcharacters[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
	255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,
	0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};

	const unsigned char cgbmap[] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
char x, y, i = 0;

int input = 0; //the bitwise or of all the buttons pressed

//the location of the player on the map, pixelwise
UWORD spritex = 0;
UWORD spritey = 0;

//the location of the upper-left hand corner of the display on the map, pixelwise
UWORD camera_x = 0;
UWORD camera_y = 0;

UWORD world_width_px = 576;
char tile_width = 72;

char map_row = 0;

char scrolled = 1;

unsigned char* current_map = bgmap;
int main()
{
	//setup

	//sprite stuff
	set_sprite_palette(0,1,&spritepalette[0]);
	SPRITES_8x8;
	set_sprite_data(MARIO, 4, mario);
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
	set_sprite_tile(2,2);
	set_sprite_tile(3,3);

/*
	set_sprite_location(0, 0, 20, 0, MARIO, current_map);
	set_camera_location(0, 0, 2, 0);
*/



	//background stuff
	set_bkg_palette(0,1,&backgroundpalette[0]);
	set_bkg_palette(1,1,&backgroundpalette[4]);
	set_bkg_data(0,4,backgroundcharacters);
	VBK_REG=1;
	set_bkg_tiles(0,0,20,24,cgbmap);
	VBK_REG=0;
	set_bkg_tiles(0,0,20,24,bgmap);
	SHOW_BKG;
	enable_interrupts();
	DISPLAY_ON;
	scroll_bkg(0,1);
	
	while(1) {/*
		printf("camera_x: %i\n", camera_x);
		printf("camera_y: %i\n", camera_y);
		printf("spritex: %i\n", spritex);
		printf("spritey: %i\n", spritey);*/

		//read
		input = joypad();



		//eval
		if(input & J_UP) {
			spritey--;
		}
		if(input & J_DOWN) {
			spritey++;  
		}
		if(input & J_LEFT) {
			if(spritex != 0) {
				spritex--;
			}
			camera_x = spritex - 80;
			if(spritex <= 80) {
				camera_x = 0;
			}
			if(spritex >= world_width_px - 80) {
				camera_x = world_width_px - SCREEN_WIDTH;
			}
			scrolled = 0;
		}
		if(input & J_RIGHT) {
			if(spritex != world_width_px - 16) {
				spritex++;
			}
			camera_x = spritex - 80;
			if(spritex <= 80) {
				camera_x = 0;
			}
			if(spritex >= world_width_px - 80) {
				camera_x = world_width_px - SCREEN_WIDTH;
			}
			scrolled = 0;
		}

		//print
		for(y = 0; y <= 18; y++) {
		/*			VBK_REG=1;
		set_bkg_tiles(0,3,20,19,cgbmap);
		VBK_REG=0;
		set_bkg_tiles(0,0,20,19,bgmap);
		*/
			map_row = camera_y/8;
			map_row *= tile_width;
			map_row += (camera_x/8);

			VBK_REG=1;
			set_bkg_tiles(0,y,21,1,&cgbmap[map_row]);
			VBK_REG=0;
			set_bkg_tiles(0,y,21,1,&bgmap[map_row]);
		}

		move_sprite(0,spritex-camera_x+8,spritey-camera_y+16);
		move_sprite(1,spritex-camera_x+16,spritey-camera_y+16);
		move_sprite(2,spritex-camera_x+8,spritey-camera_y+24);
		move_sprite(3,spritex-camera_x+16,spritey-camera_y+24);

		//print
		for(i = 0; i < 4; i++) {
			//slow down animation
			wait_vbl_done();
		}
		SHOW_BKG;
		SHOW_SPRITES;
	}
	return 0;
}

void go_up() {

}

void go_down() {

}
/*
void go_left() {
	if(sprite_subx == 0) {
		sprite_subx = 7;
		spritex--;
	} else {
		sprite_subx--;
	}
	if(camera_x == 0) {
		if(camera_subx == 0) {

		}
	}
}
*/
void go_right() {

}