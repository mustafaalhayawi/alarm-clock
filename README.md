# alarm-clock
A small, custom alarm clock. The small design was inspired by a keychain I have which has 4 keyboard switches on it. The width of the clock is the same as the keychain but it is taller. The alarm clock made up of two parts, the front and the back which can snap-fit for easy opening and closing. I also implemented a port for the USB-C connector and hooks for the display and the devboard. This project was a good opportunity to learn CAD for the first time. Learning CAD was tricky at first but I got used to the controls and the shortcuts and eventually got comfortable.

<img width="1257" height="963" alt="Screenshot 2026-07-09 213157" src="https://github.com/user-attachments/assets/69c6a160-47cd-4087-9ed6-1f8b41490200" />

## Hardware and wiring

### Bill of materials

* Lolin C3 Mini ESP 32 Devboard
* ST7789 SPI TFT Display (284x76)
* 4x Keyboard Switches
* 1x 3.3V Piezzo Buzzer
* Jumper cables for wiring

### Wiring diagram

<img width="1296" height="992" alt="Screenshot 2026-07-09 130150" src="https://github.com/user-attachments/assets/971729b1-c2a5-4e3b-8a05-b656d9e5606b" />

## Progress
I began by creating a hollow box split into two parts, rounded the corners, and made cut-outs for where the keyboard switches, the USB-C connector and the buzzer would go.

<img width="575" height="915" alt="image" src="https://github.com/user-attachments/assets/44ca6cda-523d-44e5-a7c2-d08cd74af26c" />

Making the cut-out for the screen was a challenge as the case was too small which meant that the screen was not aligned. Additionally I had to leave space for the header pins in the screen so the screen is not flat with the cover, instead is indented slightly to allow for space inside the case for the header pins. 

<img width="985" height="527" alt="image" src="https://github.com/user-attachments/assets/e5ac208f-4822-401e-bc04-2d4a51ac20b1" />

To connect the two parts of the case securely I decided to use a snap-fitting mechanism. Ideally the mechanism of the snap-fitting should've been larger however the case was too small to allow for that.

<img width="1487" height="898" alt="image" src="https://github.com/user-attachments/assets/5daa81f5-8dd4-4144-92f6-f840452299fb" />

## Firmware

At the moment the clock has very simple firmware. The network ssid and password are entered into the .ino file as well as the alarm settings. The clock then fetches the current time using WiFi as it doesn't have a clock-module. Then when the current time is equal to the alarm time defined by the user, the buzzer is turned on and when any key is pressed the buzzer is turned off. Once I build the clock and am able to debug it I will implement some games to make turning the alarm off harder.

### Requirements
* `Adafruit_GFX`
* `Adafruit_ST7789`

## Attributions

<a href="https://www.printables.com/model/395060-cherry-mx-blank-keycap-for-customising/files">Keycap 3d model</a>

<a href="https://github.com/ConstantinoSchillebeeckx/cherry-mx-switch/blob/master/switch.step">Switch 3d model</a>

Made for <a href="https://blare.hackclub.com/">Hackclub Blare</a>
