# Dross

A simple bullet-hell inspired shooter game originally made for a Programming class at college.

## Controls
- move left: A or left arrow
- move right: D or right arrow
- fire: Space or left mouse click
- Pause: ESC

## Display

Your character's hit box is represented as a white box overlaid on the sprite, this is so you can easily keep track of it to dodge bullets, you can turn it off by setting the global bool HIT_BOX to false, this will use your sprites bounding box as the hit box.

Your kill count for the current level is displayed in the upper left, the current level number is displayed in the upper middle, and your current lives are displayed in the upper right

## Other Notes

By default there are 6 levels. Since this was originally a class project I included a global bool in main.c called ALL_LEVELS which if set to false will make the program not add the last 4 levels to the game for easier testing by the professor.

## Building

Dross uses the Meson build system, so you will need Meson installed. You will also need the SFML library installed. To build simply:
- From a terminal navigate to the root folder
- Do "meson setup build"
- Do "cd build"
- Do "meson compile"
- Move the executable ("dross") out to the root folder

## TODO

- Make installer
- Add sound
- Add animations