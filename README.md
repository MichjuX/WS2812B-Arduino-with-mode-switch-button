# LED Strip Animation Project

This Arduino project utilizes the FastLED library to create various animated effects on a NeoPixel LED strip. The project includes functions for generating wave patterns, a rainbow wave, a Cylon animation, and a fire effect.

## Table of Contents
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Customization](#customization)
- [Contributing](#contributing)

## Requirements
- Arduino board (e.g., Arduino Uno, Arduino Nano)
- Power Supply suitable for the selected LED strip and its length
- Push Button
- NeoPixel LED strip (WS2812B tested)
- FastLED library

## Installation
1. Connect the NeoPixel LED strip to the specified pin on your Arduino board.
2. Install the FastLED library in your Arduino IDE.
3. Upload the provided sketch (`led_strip_animation.ino`) to your Arduino board.

## Usage
1. [Connect a push button](https://docs.arduino.cc/built-in-examples/digital/Button) to the specified pin on your Arduino board (default pin 2). 
2. Power on the Arduino board.
3. Press the button to cycle through different animation modes.

## Customization
- Adjust the `NUM_LEDS` constant in the sketch to match the number of LEDs in your strip.
- Modify the `buttonPin` constant to match the pin where you connect the push button.
- Experiment with different animation functions by changing the `mode` variable in the `loop` function.
- Customize wave parameters in the `waves` function (e.g., color, amount, etc.).
- Explore other FastLED functions to create your own animations.

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests to enhance the project.
