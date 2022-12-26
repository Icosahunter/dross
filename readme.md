# Dross

A simple bullet-hell inspired shooter game originally made for a Programming class at college.

## Controls
- move left: A or left arrow
- move right: D or right arrow
- fire: Space or left mouse click
- Pause: ESC

## Notes

Your character's hit box is represented as a white box overlaid on the sprite, this is so you can easily keep track of it to dodge bullets, you can change this with build options.

Your kill count for the current level is displayed in the upper left, the current level number is displayed in the upper middle, and your current lives are displayed in the upper right.

By default there are 12 levels. Since this was originally a class project I included an option to disable all but the first two levels to the game for easier testing by the professor. You can now change this with build options.

## Building

Dross uses the Meson build system, so you will need Meson installed. You will also need the SFML library installed. To build simply:
- From a terminal navigate to the root folder
- Do "meson setup build"
- Do "cd build"
- Do "meson compile"

## Build Options

-Dtest={true|false}
    Set this to true if you are doing a non-install build (that is, testing the program). Currently all it does is set the data directory as the repository root directory.

-Ddata_dir=path
    Tells the program where to look for assets (images and fonts). Default data directory is "./", this will change when I add install capabilities.

-Dhit_box={true|false}
    If false use the sprite bounding box as the hit box.

-Dall_levels={true|false}
    If false only play the first two levels.

## TODO

- Make installer
- Add shooting & enemy destroyed sound effects
- Add Music
- Add enemy destroyed animation
- Refactor enemy shooting (it's weird due to sticking to the original assignments wording)
- Revamp player shooting (make it more interesting)