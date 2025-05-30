#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
bool doShow = false;
float pctBlend;
uint16_t blendedColor;

uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc) {
  uint32_t rxb = bgc & 0xF81F;
  rxb += ((fgc & 0xF81F) - rxb) * (alpha >> 2) >> 6;
  uint32_t xgx = bgc & 0x07E0;
  xgx += ((fgc & 0x07E0) - xgx) * alpha >> 8;
  return (rxb & 0xF81F) | (xgx & 0x07E0);
}

void setup() {
  Serial.begin(115200); delay(2000);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);

  ledcAttach(TFT_BL, 5000, 8);  // PWM timer automatically assigned.
  ledcWrite(TFT_BL, 200);       // Turn the display on bigly for init messages.
}

// This ONLY draws orthogonal lines, NO diagonals!
void drawGradientLine(int x0, int y0, int x1, int y1, uint16_t colorStart, uint16_t colorEnd) {
  int steps = abs(x1 - x0) > abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0);
  if (doShow) Serial.printf("Steps: %i\r\n", steps);
  int x = x0, y = y0;
  for (int i = 0; i <= steps; i++) {
    pctBlend = (float)i / steps;
    blendedColor = alphaBlend((uint8_t)(pctBlend * 255), colorEnd, colorStart);
    if (doShow) Serial.printf("x %i, y %i, pctBlend %f\r\n", x, y, pctBlend);
    tft.drawPixel(x, y, blendedColor);
    if ((x0 - x1) == 0) y1 > y0 ? y++ : y--;
    if ((y0 - y1) == 0) x1 > x0 ? x++ : x--;
  }
}

void loop() {
  //Vertical lines
  Serial.println("Vertical part 1");
  for (int x = 0; x < tft.width() / 2; x++) {
    //    if (x == 0)
    //      doShow = true;
    //    else
    //      doShow = false;
    //                                          Bottom,   Top
    drawGradientLine(x, tft.height() - 1, x, 0, TFT_BLUE, TFT_RED);
  }

  delay(2000);

  Serial.println("Vertical part 2");
  for (int x = tft.width() / 2; x < tft.width(); x++) {
    //    if (x == tft.width() / 2)
    //      doShow = true;
    //    else
    //      doShow = false;
    //                                          Bottom,    Top
    drawGradientLine(x, tft.height() - 1, x, 0, TFT_WHITE, TFT_GREEN);
  }
  delay(5000);
  tft.fillScreen(TFT_WHITE);

  // Horizontal lines
  for (int y = 0; y < tft.height() / 2 - 1 ; y++)
    //                                     Left,    Right
    drawGradientLine(0, y, tft.width(), y, TFT_RED, TFT_BLUE);

  delay(2000);

  for (int y = tft.height() / 2; y < tft.height() - 1; y++)
    //                                     Left,      Right
    drawGradientLine(0, y, tft.width(), y, TFT_GREEN, TFT_WHITE);

  delay(5000);
  tft.fillScreen(TFT_WHITE);
}
