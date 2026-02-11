# Kane & Lynch 2: Dog Days Fix

This is a small project aimed at fixing some of the issues with Kane & Lynch 2 on PC. It is meant to be used on version 1.2, and it works for both Steam and GOG.

### Fixes:
- **Fixed noise effect:** Contrary to what you might have thought, the noise effect wasn't gone from the PC version. Both the exposure shader and the noise shader had to be corrected based on math from the Xbox 360 version of the game that was done on the CPU. Additionally, the 2 values used to sample from the noise UV weren't accounting for the framerate which made the noise not look as strong at a higher framerate which has been fixed.
- **Removed second window:** The game explicitly checks if you have a second monitor and creates a window on it which is what caused users' second monitors to go black. This has been removed and put behind a config toggle.
- **Corrected death screen:** The PC port has a small oversight causing the death screen to not have a black background in singleplayer of if you are the co-op host. This has been corrected to match console.
- **Corrected aim assist:** In the vanilla game, on both console and PC, the aim assist setting seemingly does nothing. It has been corrected to disable snapping the crosshair to the closest enemy when you start aiming.
- **Corrected co-op bleed/tap QTE**: At a higher (or lower) framerate than 60, both the depletion of the bar and the tapping would become incorrect. The tapping itself is originally scaled with the frametime, and the higher your framerate, the lower it is, meaning that when you tap and it tries to re-fill the bar, a smaller percantage will get filled (or vice-versa). The depletion itself does also use the frametime (and it should) but it still was incorrect.
- **Built-in LAA/4 GB patcher**: This prevents the game from dying at exactly 42% when loading, which is the result of failed heap allocation. When you launch the game, if it has not been patched, you will get prompted to patch it. Note that if it still fails you can find standalone LAA patchers and use them instead, the result will be the same. If you are having issues with the LAA patcher, you can turn it off in the config by setting DisableLAAPatcher to 1.

### Miscellaneous:
- **Skip intros**: Forces the splash sequence to reach its end immediately which is the safest way to skip the intros without breaking UI and it is optional and off by default.
- **Debug/Cheat menu**: Replaces the main menu with the debug menu, has features such as level loading. Do not hit the back button in the debug menu as that will cause the game to get stuck and you'll have to force quit it. The setting takes priority over the option to skip intros.
- **Multi-instance:** By default, you can only run one instance of the game. With MultiInstance being enabled you can run as many as you'd like. This is really only useful for testing but I figured I would include it anyway.

### QoL:
- **Borderless windowed:** Self-explanatory feature, makes it so that you won't need third-party software to do this. This is also off by default.
- **True Alt + F4:** You normally get a message asking you if you want to quit when you try force closing it. A setting to let you force close it properly has been added and is off by default.

### Installation:
 - Download the latest release and extract the contents of the archive to your game folder, and optionally configure the .ini to your liking.

### Credits

- Shader Help: [miru97](https://github.com/mlleemiles)
- Silent: [ModUtils](https://github.com/CookiePLMonster/ModUtils)
- ThirteenAG: [Ultimate-ASI-Loader (bundled with releases)](https://github.com/ThirteenAG/Ultimate-ASI-Loader) 
