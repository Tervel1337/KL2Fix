# Kane & Lynch 2: Dog Days Fix

This is a small project aimed at fixing some of the issues with Kane & Lynch 2 on PC. It is meant to be used on version 1.2, and it works for both Steam and GOG.

### Fixes:
- **Fixed noise effect:** Contrary to what you might have thought, the noise effect wasn't gone from the PC version. Both the exposure shader and the noise shader had to be corrected based on math from the Xbox 360 version of the game that was done on the CPU. Additionally, the 2 values used to sample from the noise UV weren't accounting for the framerate which made the noise not look as strong at a higher framerate which has been fixed.
- **Removed second window:** The game explicitly checks if you have a second monitor and creates a window on it which is what caused users' second monitors to go black. This has been removed and put behind a config toggle. 

### Miscellaneous:
- **Skip intros**: Forces the splash sequence to reach its end immediately which is the safest way to skip the intros without breaking UI and it is optional and off by default.
- **Debug/Cheat menu**: Replaces the main menu with the debug menu, has features such as level loading. Do not hit the back button in the debug menu as that will cause the game to get stuck and you'll have to force quit it. The setting takes priority over the option to skip intros.

### QoL:
- **Borderless windowed:** Self-explanatory feature, makes it so that you won't need third-party software to do this. This is also off by default.

### Installation:
 - Download the latest release and extract the contents of the archive to your game folder, and optionally configure the .ini to your liking.

### Credits

- Shader Help: [miru97](https://github.com/mlleemiles)
- Silent: [ModUtils](https://github.com/CookiePLMonster/ModUtils)
- ThirteenAG: [Ultimate-ASI-Loader (bundled with releases)](https://github.com/ThirteenAG/Ultimate-ASI-Loader)
