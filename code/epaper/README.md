# Files relating to e-paper development 

### Links

[Third party board manager URLs, I need the ESP8266](https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls)

[E-Paper ESP8266 Driver Board Documentation](https://www.waveshare.com/wiki/E-Paper_ESP8266_Driver_Board)

[Locating arduino boards in the Arduino 2 IDE](https://support.arduino.cc/hc/en-us/articles/4415103213714-Find-sketches-libraries-board-cores-and-other-files-on-your-computer#boards)

### Notes
`Loader.ino` demo IP connection is not reliable, it needs to have an correct ip assigned to it without conflicts. It doesn't seem to use DHCP.

``` c
  IP4_ADDR(&info.ip, 192, 168, 1, 189);
  IP4_ADDR(&info.gw, 192, 168, 1, 1);
```

![Problem](https://www.waveshare.com/w/upload/e/e4/Epd2in13_esp_chose3.png)

