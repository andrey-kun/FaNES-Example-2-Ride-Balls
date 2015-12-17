#include <FaNES.h>

#define BALLS_MAX 64

const uchar paletteSprites[16] = {
	0x0f,0x17,0x27,0x37,
	0x0f,0x11,0x21,0x31,
	0x0f,0x15,0x25,0x35,
	0x0f,0x19,0x29,0x39
};

static uchar ballX[BALLS_MAX];
static uchar ballY[BALLS_MAX];
static uchar ballSpeedHorizontal[BALLS_MAX];
static uchar ballSpeedVertical[BALLS_MAX];

static uchar i = 0, x = 0, y = 0, h = 0, v = 0;

void main() {
    uchar randomDirectionSeed;
    //setPaletteColor(PALETTE_BACKGROUND_1 + 0, 0x0F);
    setPaletteSprites(paletteSprites);
    for (i = 0; i < BALLS_MAX; i++) {
        ballX[i] = getRandomUchar() % (256 - 8);
        ballY[i] = getRandomUchar() % (240 - 8);
        randomDirectionSeed = getRandomUchar();
        ballSpeedHorizontal[i] = 1 + getRandomUchar() % 3;
        ballSpeedVertical[i] = 1 + getRandomUchar() % 3;
        ballSpeedHorizontal[i] = (randomDirectionSeed & 1) ? ballSpeedHorizontal[i] : -ballSpeedHorizontal[i];
        ballSpeedVertical[i] = (randomDirectionSeed & 2) ? ballSpeedVertical[i] : -ballSpeedVertical[i];
        newSprite(ballX[i], ballY[i], 0x0F, i & 3, i << 2);
    }
    onGraphics();
    while(TRUE) {
        for (i = 0; i < BALLS_MAX; ++i) {
			x = ballX[i];
			y = ballY[i];
			h = ballSpeedHorizontal[i];
			v = ballSpeedVertical[i];
            setSpritePosition(x, y, i << 2);
            x += h;
            y += v;
            if (x >= (256 - 8)) h = -h;
			if (y >= (240 - 8)) v = -v;
			ballX[i] = x;
			ballY[i] = y;
			ballSpeedHorizontal[i] = h;
			ballSpeedVertical[i] = v;
        }
        waitFrame();
    }
}
