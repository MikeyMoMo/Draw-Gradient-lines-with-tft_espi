#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

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
  tft.fillScreen(TFT_BLACK);

  ledcAttach(TFT_BL, 5000, 8);  // PWM timer automatically assigned.
  ledcWrite(TFT_BL, 200);       // Turn the display on bigly for init messages.

  for (int i = 0; i < 100; i++)
    drawGradientLine(0, i, tft.width(), i, TFT_RED, TFT_BLUE);
  for (int i = 101; i < 200; i++)
    drawGradientLine(0, i, tft.width(), i, TFT_GREEN, TFT_WHITE);
}

void drawGradientLine(int x0, int y0, int x1, int y1, uint16_t colorStart, uint16_t colorEnd) {
  int steps = abs(x1 - x0) > abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0);

  for (int i = 0; i <= steps; i++) {
    float ratio = (float)i / steps;
    uint16_t blendedColor = alphaBlend((uint8_t)(ratio * 255), colorEnd, colorStart);
    int x = x0 + (x1 - x0) * ratio;
    int y = y0 + (y1 - y0) * ratio;
    tft.drawPixel(x, y, blendedColor);
  }
}

void loop() {
}
