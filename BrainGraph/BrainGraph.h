#ifndef BrainGraph_h
#define BrainGraph_h

#include <stdint.h>
#include <stdlib.h>

#define MAX_XRES				240
#define MAX_YRES 				320
#define EEG_CHANNELS 			8
#define CHANNEL_VALUES	 		20
#define PIXELS_PER_GRAPH_Y		MAX_YRES/EEG_CHANNELS
#define PIXELS_PER_POINT_X		MAX_XRES/CHANNEL_VALUES

class Channel {
	private:
		uint32_t eeg_power[CHANNEL_VALUES];
		uint32_t eeg_max;
		
	public:
		void init();
		void add(uint32_t x);
		uint32_t* getEEGPower();
		uint32_t getEEGMax();
};


class BrainGraph {
	private:
		Channel channels[EEG_CHANNELS];
		uint32_t channel_max;
				
	public:
		void init();
		void update(uint32_t eeg[EEG_CHANNELS]);
		Channel* getChannels();
		int convertToLine(uint32_t eeg, uint32_t eeg_max, uint8_t offset);
		int convertToBar(uint32_t eeg, uint8_t offset);
};

#endif