# COM3505 The Internet of Things

## Lab1 Introduction

The assessment is to build and document a device that gives a visual indication of the activation strength of a touch sensor. We use the ESP32's built-in touch sensing capability. In our touchy thing, there is a simple wire connected to GPIO pin 32, and we use 3 LEDs (red light, yellow light, and green light) which are connected to GPIO pins 17, 21, 16 respectively to show how strong the sensor activation. In addition, the touchy thing can illuminate LEDs to indicate different levels seen by the touch sensor.

## Lab2 Introduction

Lab assessment2 is to build an ESP32-based voice-controlled automation system called Marvin, which uses a custom microphone board and a low-noise MEMS mic. In this system, we use a pre-trained model to detect the words. The Wit.ai server will work out the user's intention, and then the ESP32 will execute the command [1]. In our project, we aim to implement greeting, LED music player, a "pain-sensitive" robot, and sentiment recognition, more details will be explained in the following sections.
