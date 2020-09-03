#include <stdlib.h>
#include <TFT.h>
#include <TouchScreen.h>
#include <Brain.h>
#include <BrainGraph.h>

#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3

#define PAD 4
#define TS_MINX 140
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940


Brain brain(Serial);  
BrainGraph bg;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t colors[8] = {RED, GREEN, WHITE, BLUE, YELLOW, CYAN, GRAY1, PINK};
uint8_t view_flag = 0;
bool chart_flag = 0;

void setup() {
  bg.init();
  Tft.init();  //init TFT library
  pinMode(0, OUTPUT);
  Tft.fillRectangle(0, 0, MAX_XRES, MAX_YRES, BLACK);
  Serial.begin(9600);
}

void loop() {
	
  if (brain.update()) {
    if (view_flag == 0) {
      drawLineGraph();
    }
    else if (view_flag == 1) {
      drawBarGraph();
    }
    else if (view_flag == 2) {
      drawChart();
    }
  }
  checkTouch();
}

void drawLineGraph() {
  for (int j = 0; j < CHANNEL_VALUES - 1; j++) {
    for (int i = 0; i < EEG_CHANNELS ; i++) {
      Tft.drawLine(j * PIXELS_PER_POINT_X,
                   bg.convertToLine(bg.getChannels()[i].getEEGPower()[j], bg.getChannels()[i].getEEGMax(), i),
                   (j + 1) * PIXELS_PER_POINT_X,
                   bg.convertToLine(bg.getChannels()[i].getEEGPower()[j + 1], bg.getChannels()[i].getEEGMax(), i),
                   BLACK);
    }
  }

  bg.update(brain.readPowerArray());

  for (int j = 0; j < CHANNEL_VALUES - 1; j++) {
    for (int i = 0; i < EEG_CHANNELS ; i++) {
      Tft.drawLine(j * PIXELS_PER_POINT_X,
                   bg.convertToLine(bg.getChannels()[i].getEEGPower()[j], bg.getChannels()[i].getEEGMax(), i),
                   (j + 1) * PIXELS_PER_POINT_X,
                   bg.convertToLine(bg.getChannels()[i].getEEGPower()[j + 1], bg.getChannels()[i].getEEGMax(), i),
                   colors[i]);
    }
  }
}

void drawBarGraph() {
  bg.update(brain.readPowerArray());
  for (int i = 0; i < EEG_CHANNELS; i++) {
    if (bg.getChannels()[i].getEEGPower()[0] > bg.getChannels()[i].getEEGPower()[1]) {
      Tft.fillRectangle(0, i * PIXELS_PER_GRAPH_Y,
                        bg.convertToBar(bg.getChannels()[i].getEEGPower()[0], i),
                        PIXELS_PER_GRAPH_Y - 1,
                        colors[i]);
    }

    else if (bg.getChannels()[i].getEEGPower()[0] < bg.getChannels()[i].getEEGPower()[1]) {
      Tft.fillRectangle(bg.convertToBar(bg.getChannels()[i].getEEGPower()[0], i) + 1,
                        i * PIXELS_PER_GRAPH_Y,
                        MAX_XRES - 1,
                        PIXELS_PER_GRAPH_Y - 1,
                        BLACK);
    }
  }
}

void setupChart() {
  Tft.drawLine(0, 0, 0, MAX_YRES - 1, WHITE);
  Tft.drawLine(0, 0, MAX_XRES - 1, 0, WHITE);
  Tft.drawLine(0, MAX_YRES - 1, MAX_XRES - 1, MAX_YRES - 1, WHITE);
  Tft.drawLine(MAX_XRES - 1, 0, MAX_XRES - 1, MAX_YRES - 1, WHITE);
  Tft.drawLine((MAX_XRES / 2) - 1, 0, (MAX_XRES / 2) - 1, MAX_YRES - 1, WHITE);
  
  for (int i = 1; i < EEG_CHANNELS; i++) {
    Tft.drawLine(0, i * PIXELS_PER_GRAPH_Y, MAX_XRES, i * PIXELS_PER_GRAPH_Y, WHITE);
  }

  Tft.drawString((char*)"DELTA", PAD, PAD + (PIXELS_PER_GRAPH_Y / 4), 2, RED);
  Tft.drawString((char*)"THETA", PAD, PAD + (PIXELS_PER_GRAPH_Y) + (PIXELS_PER_GRAPH_Y / 4), 2, GREEN);
  Tft.drawString((char*)"LOW", PAD, PAD + (PIXELS_PER_GRAPH_Y * 2), 2, WHITE);
  Tft.drawString((char*)"ALPHA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 2) + (PIXELS_PER_GRAPH_Y / 2), 2, WHITE);
  Tft.drawString((char*)"HIGH", PAD, PAD + (PIXELS_PER_GRAPH_Y * 3), 2, BLUE);
  Tft.drawString((char*)"ALPHA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 3) + (PIXELS_PER_GRAPH_Y / 2), 2, BLUE);
  Tft.drawString((char*)"LOW", PAD, PAD + (PIXELS_PER_GRAPH_Y * 4), 2, YELLOW);
  Tft.drawString((char*)"BETA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 4) + (PIXELS_PER_GRAPH_Y / 2), 2, YELLOW);
  Tft.drawString((char*)"HIGH", PAD, PAD + (PIXELS_PER_GRAPH_Y * 5), 2, CYAN);
  Tft.drawString((char*)"BETA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 5) + (PIXELS_PER_GRAPH_Y / 2), 2, CYAN);
  Tft.drawString((char*)"LOW", PAD, PAD + (PIXELS_PER_GRAPH_Y * 6), 2, GRAY1);
  Tft.drawString((char*)"GAMMA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 6) + (PIXELS_PER_GRAPH_Y / 2), 2, GRAY1);
  Tft.drawString((char*)"MID", PAD, PAD + (PIXELS_PER_GRAPH_Y * 7), 2, PINK);
  Tft.drawString((char*)"GAMMA", PAD, PAD + (PIXELS_PER_GRAPH_Y * 7) + (PIXELS_PER_GRAPH_Y / 2), 2, PINK);
  
  chart_flag = 1;
}
void drawChart() {
  bg.update(brain.readPowerArray());
  
  if (!chart_flag) {
    setupChart();
  }
  for (int i = 0; i < EEG_CHANNELS; i++) {
    char str[7];
    ltoa(bg.getChannels()[i].getEEGPower()[0], str, 10);
    Tft.fillRectangle(MAX_XRES / 2 + PAD, PAD + (PIXELS_PER_GRAPH_Y * i), (MAX_XRES / 2) - (PAD * 2), PIXELS_PER_GRAPH_Y - (PAD * 2), BLACK);
    Tft.drawString(str, PAD + (MAX_XRES / 2), PAD + (PIXELS_PER_GRAPH_Y / 4) + (PIXELS_PER_GRAPH_Y * i), 2, colors[i]);
  }
}

void checkTouch() {
  Point touch = ts.getPoint();
  if (touch.z > ts.pressureThreshhold) {
   view_flag = view_flag < 2 ? view_flag + 1 : 0;
    Tft.fillRectangle(0, 0, MAX_XRES, MAX_YRES, BLACK);
    chart_flag = 0;
  }
}
