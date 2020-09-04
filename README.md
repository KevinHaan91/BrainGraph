# BrainGraph

#### Overview

<img width="500" src="screenshot.jpg" />

This is an Arduino library used to read and visualize EEG brainwave data. It is designed to manipulate the data from a modified MindFlex EEG headset using an Arduino, and display it visually on a TFT LCD shield.

This project was created using an Arduino UNO, a modified MindFlex EEG Headset, and a Seeed 2.8" TFT Touch Shield v1.0. The BrainGraph library was specifically designed to run on an Arduino UNO, so it is optimized to use the least amount of memory possible. It should work with any Arduino however, with minimal changes, if any. It also was written specifically for use with a modified MindFlex EEG Headset, and may or may not work with other EEG headsets.

The BrainGraph library itself does not rely on any additional libraries, however, the example Arduino file has a couple different library dependencies in order to function.

### Dependencies:

 - https://github.com/kitschpatrol/Brain This library is used to parse the data from the MindFlex, which then gets manipulated using the BrainGraph library.
 
 - https://files.seeedstudio.com/wiki/TFT_Touch_Shield_V1.0/res/TFT_TouchScreen_for_Arduino_1.0.zip  This library is used for the particular TFT Touch LCD shield that I used. Each TFT shield will use a specific library, but for the most part everything should translate without problems.  
