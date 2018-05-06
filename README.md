# ThingProviderNodes
The Arduino Nodes to ThingProvider 

## Build Status [![Build Status](https://travis-ci.org/kevinmmartins/ThingProviderNodes.svg?branch=master)](https://travis-ci.org/kevinmmartins/ThingProviderNodes)

![alt text](https://user-images.githubusercontent.com/20428703/38177975-3c21b5d4-35df-11e8-8193-aff06af8f356.png)

## Setup
* Arduino;
* Arduino Ethernet shield;
* Arduino IDE;
* SPI.h,Ethernet.h,aREST.h and avr/wdt.h libraries;

## Rain Node

  Get information about rain sensor

 ![alt text](https://user-images.githubusercontent.com/20428703/39284286-e34afcc8-48e8-11e8-9743-cfb94a5d2a45.JPG)
 ![alt text](https://user-images.githubusercontent.com/20428703/39284287-e3878b7a-48e8-11e8-987f-88dd75ce16ca.JPG)
 
Resources:
 ### GET
 http://192.168.0.10:98/rainDigitalValue
 ![alt text](https://user-images.githubusercontent.com/20428703/39284285-e30d17dc-48e8-11e8-8707-59f249e5c0c7.PNG)
 
 Json example:
 ```json
{
    "rainDigitalValue": 0,
    "id": "1",
    "name": "rainAPI",
    "hardware": "arduino",
    "connected": true
}
```
 ### GET
 http://192.168.0.10:98/rainAnalogicValue
 ![alt text](https://user-images.githubusercontent.com/20428703/39284284-e2ceb4f6-48e8-11e8-997c-3d55163f525c.PNG)

  Json example:
  ```json
 {
    "rainAnalogicValue": 131,
    "id": "1",
    "name": "rainAPI",
    "hardware": "arduino",
    "connected": true
}
```
## Led Node

  Change the LED state

 ![alt text](https://user-images.githubusercontent.com/20428703/39284288-e3ca00cc-48e8-11e8-80f8-f71e747d1fc2.JPG)
 ![alt text](https://user-images.githubusercontent.com/20428703/39284289-e409234c-48e8-11e8-86ac-394cb4f7e28f.JPG)
 
 Resource:
 ### POST 
 192.168.0.10:98/led
 
 ### On
 ![alt text](https://user-images.githubusercontent.com/20428703/39284291-e48e76be-48e8-11e8-9e73-a64c45152e38.PNG)
 
 ### Off
 ![alt text](https://user-images.githubusercontent.com/20428703/39284290-e44b6946-48e8-11e8-807c-d08ac41019f2.PNG)
 
