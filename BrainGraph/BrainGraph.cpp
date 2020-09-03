#include "BrainGraph.h"


  void Channel::init(){
    for(int i=0; i<CHANNEL_VALUES; i++){
      eeg_power[i] = 0; 
    }
    eeg_max = 1;
  }
  void Channel::add(uint32_t x){    
    for(int i=CHANNEL_VALUES-1; i>0; i--){
      eeg_power[i] = eeg_power[i-1];  
    }
    eeg_power[0] = x;
    
	if(x > eeg_max){ 
		eeg_max = x;
	}

  }
  uint32_t* Channel::getEEGPower(){
    return eeg_power;
  }
  uint32_t Channel::getEEGMax(){
    return eeg_max;
  }


  void BrainGraph::init(){
    for(int i=0; i<EEG_CHANNELS; i++){
      channels[i].init();
    }
	channel_max = 0;
  }
  void BrainGraph::update(uint32_t eeg[EEG_CHANNELS]){
    for(int i=0; i<EEG_CHANNELS; i++){
		channels[i].add(eeg[i]);
		
		if(channels[i].getEEGMax() > channel_max){
			channel_max = channels[i].getEEGMax();
		}
    }    
  }
  Channel* BrainGraph::getChannels(){
	  return channels;
  }
  
  int BrainGraph::convertToLine(uint32_t eeg, uint32_t eeg_max, uint8_t offset){
	  return abs((PIXELS_PER_GRAPH_Y-1) - ((eeg * (PIXELS_PER_GRAPH_Y-1)) / eeg_max) + (PIXELS_PER_GRAPH_Y*offset));
  }
  
  int BrainGraph::convertToBar(uint32_t eeg, uint8_t offset){
		return (eeg*(MAX_XRES-1))/channel_max;
  }