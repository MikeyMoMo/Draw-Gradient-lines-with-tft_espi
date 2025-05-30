# Draw-Gradient-lines-with-tft_espi
The great library tft_espi does not offer gradient line capability.  This is an entire app with a gradient line drawing routine in it.  With this code, you can make your projects just a little bit prettier.  I will use it in an area graph program that is already uploaded here in my repositories named "Triple-Time-Zones-on-TTGO-T4-v1.3", soon.

All of the heavy lifting is done in the drawGradientLine routine.  In this demo, I call it several times and it ends up looking like a gradient rectangle but that is just for showing it off better.  You need only call it once for each line you want to show.  Input RGB565 starting and ending colors and let 'er rip.  Of course, you could call the gradient rectangle with a 1 pixel width but that's a lot of extra overhead just for 1 line.

Here's the RGB565 macro:  #define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

The TFT_RED and TFT_BLUE are in the RGB565 format already.  You can use your own by coding "uint16_t color = RGB565(red_value, green_value, blue_value)";

Enjoy,
Mikey the Midnight Coder
