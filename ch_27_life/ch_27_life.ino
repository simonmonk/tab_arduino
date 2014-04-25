

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(10, 8, -1);
//                                    TFT_CS, TFT_DC, TFT_RST

const int w = 20;
const int h = 16;

const int initialPopulation = 70;

byte board[2][w][h];
byte g = 0;


void setup(void) 
{
  // Our supplier changed the 1.8" display slightly after Jan 10, 2012
  // so that the alignment of the TFT had to be shifted by a few pixels
  // this just means the init code is slightly different. Check the
  // color of the tab to see which init code to try. If the display is
  // cut off or has extra 'random' pixels on the top & left, try the
  // other option!
  // If you are seeing red and green color inversion, use Black Tab

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  // If your TFT's plastic wrap has a Red Tab, use the following:
  //tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
  // If your TFT's plastic wrap has a Green Tab, use the following:
  //tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab

  tft.fillScreen(0x0000);
  tft.setRotation(3);
  seedRandomGeneration();
  Serial.begin(9600);
}

void seedRandomGeneration()
{
  randomSeed(analogRead(A1));
  for (byte i=0; i < initialPopulation; i++)
  {
    int x = random(w);
    int y = random(h);
    board[g][x][y] = 1;
  }
}

void displayBoard()
{
  tft.fillScreen(0x0000);
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (board[g][x][y])
      {
       tft.fillRect(x * 8, y * 8, 8, 8, ST7735_YELLOW);
      }
    }
  }
}

void loop() 
{
  if (analogRead(A3) > 512)
  {
    displayBoard();
    updateGeneration();
    g = !g;
  }
}

void updateGeneration()
{
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      board[!g][x][y] = updateCell(x, y);
    }
  }
}

byte updateCell(int x, int y)
{
  int n = numNeighbors(x, y);
  if (board[g][x][y] == 1)
  {
    if (n < 2) return 0;
    else if (n == 2 || n == 3) return 1;
    else if (n > 3) return 0;
  }
  else
  {
    return (n == 3);
  }
}

int numNeighbors(int x, int y)
{
  int n = 0;
  for (int dx = -1; dx <= 1; dx++)
  {
    for (int dy = -1; dy <= 1; dy++)
    {
      int x1 = x + dx;
      int y1 = y + dy;
      boolean middle = (dx == 0 && dy == 0);
      if (!middle && x1 > 0 && x1 < w && y1 > 0 && y1 < h)
      {
        n += board[g][x1][y1];
      }
    }
  }
  Serial.print(n);
  return n;
}



