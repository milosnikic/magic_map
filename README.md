# Magic map
## Description
This project is designed for escape room, which subject is Harry Potter. Idea is to have place bottle on the right spot, and then hidden way starts to appear.

What you need for this project?
- Arduino (Nano, Uno, etc.) [logo]: https://www.elektor.com/media/catalog/product/cache/23126780d17198beb71f0dbe2a3ae59a/a/r/arduinonanofront_3_sm_1.jpg "Arduino"
- 2m WS2812B LED tape [logo]: https://cdn.shopify.com/s/files/1/0023/2960/8292/products/Artboard_2_700x700.jpg?v=1553053307 "WS2812B"
- Soldering equipment
- MFRC522 module [logo]: https://www.espruino.com/refimages/MFRC522.jpg "MFRC522" [logo]: https://i1.wp.com/randomnerdtutorials.com/wp-content/uploads/2015/11/tags.png?resize=387%2C126&ssl=1 "tags"
- Wires 
- External Power Supply (5v for LEDs)

## Specification
- Arduino Input Voltage 7-12V
- WS2812B Input Voltage 5v
- Approximate price: 20 e

## Libraries
1. Download the RFID library (MFRC522) and FastLED
2. Unzip the RFID library and FastLED
3. Install the RFID library and FastLED in your Arduino IDE
4. Restart your Arduino IDE

## Pin wiring
Pin	Wiring Arduino Uno and MFRC522
- SDA ->	Digital 10
- SCK ->	Digital 13
- MOSI ->	Digital 11
- MISO ->	Digital 12
- IRQ ->	unconnected
- GND ->	GND
- RST ->	Digital 9
- 3.3V ->	3.3V

Pin Wiring Arduino Uno and WS2812B
- 5v -> External Power Supply 5V
- GND -> External Power Supply GND and Arduino GND
- Data Input -> Digital 7

## Demonstration

![](magic_map.gif)

[logo]: (magic_map1.png) "Magic map1"
[logo]: (magic_map2.png) "Magic map2"
