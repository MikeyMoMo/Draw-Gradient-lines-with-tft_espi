# Draw-Gradient-lines-with-tft_espi
The great library tft_espi does not offer gradient line capability.  This is an entire app with a gradient line drawing routine in it.  With this code, you can make your projects just a little bit prettier.  I use it in an area graph program that is already uploaded here in my repositories named "Triple-Time-Zones-on-TTGO-T4-v1.3".

All of the heavy lifting is done in the drawGradientLine routine.  In this demo, I call it several times and it ends up looking like a gradient rectangle but that is just for showing it off better.  Later calls show a sloping area, too.  These are also show variations of shading areas.  You need only call it once for each line you want to show.  Input RGB565 starting and ending colors and let 'er rip.  Of course, you could call the tft_espi gradient rectangle with a 1 pixel width but that's a lot of extra overhead just for 1 line.

Here's the RGB565 macro:  #define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3))) // Used to prepare 16 bit color used by the library and many displays

The colors used in this demo are in the RGB565 format already.  You can use your own by coding "uint16_t color = RGB565(red_value, green_value, blue_value)";

I have 3 variations of the gradient line you can use:

1. Normal gradient with fully proportional blending of the two colors evenly throughout the length of the line. See this in the first triangular demo "Variable Gradient";

2. Force the gradient to change with a fixed number independent of the length of the line.  This could be useful where you have a graph that, when it dips low, dips into a red area but, when higher, turns green.  This could work for a money value graph.  I use this feature for an exchange rate graph in another of my repositories.  See this in the second triangular demo "Fixed Gradient";

3. Force the gradient to change prematurely.  This function compresses the gradient change into an area less than the length of the line.  This can highlight the ending color that I have found, sometimes, seemes too compressed to really show up well.  See this in the third triangular demo "Short Gradient".

4. You can also force the change the other way, i.e., late.  Just make the steps larger than the line length.  See it in the example program.

The gradient routine determines whether you are trying to draw vertically or horizontally.  There is no need for indication of this in the routine call.

Enjoy,
Mikey the Midnight Coder
