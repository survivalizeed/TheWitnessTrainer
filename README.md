# TheWitnessTrainer
#### This repository makes use of the LWM-Trainer (https://github.com/survivalizeed/LWM-Trainer)
Please don't use this program to fake speedruns or such things.  
I originally created this trainer to be able to unlock everything until I reach my lost savegame but it  
turned out to be a nice side project to refresh my reversing, hacking and C++ skills :)
##### Tools used: Cheat Engine, x64dbg, IDApro, Visual Studio 2022 C++ and Defuse.ca x86 disassembler 
##### If you have any questions contact me on Discord: survivalizeed#7659
#### Please remember: This Trainer is still in a very early state and Reverse Engineering is often a stony path. So please expect some bugs!
  
  
### Features:    (There are now a lot more features available. I just haven't had the time to update this list!)

- GameChanger
  - Fly (speed customizable) | You can fly through walls but it is still not a no clip hack, which means that you will probably glitch through the world 
  - FasterSprint (speed customizable) | Lets you customize your sprint speed
  - AllSolutionsWork | No matter how you draw the laser through the puzzle it will always be correct 
  - LeaveSolve | Pretty much the same as AllSolutionsWork but you don't have to drag it to the end. It will solve the puzzle as soon as you leave the puzzle. This is useful for partially locked puzzles
  - LeaveSolveEnviroment | Same as LeaveSolve but this one is for the enviromental puzzles.
  - SavePosition | Saves your current position
  - MoveToPosition | Move yourself to the previously stored position
- Fun
  - NoNodLimit | Disables the pitch axis lock
- Misc
  - DisableSave | Disable the possibility to save the game. This will show the warning that the game is unable to save
  - DisableNoSaveMessage | Disable the possibility to save the game. This won't show the warning that the game is unable to save
  - OpenGameDirectory | This will open the executables directory
  - OpenSettings | This will open a config file in which you can customize the FlySpeed, SprintSpeed, AutoTunePlay (0 or 1) and AlphaStickToProcess (0 - 255)
  - ReloadSettings | Apply the changes you made in the config file to the Trainer
  - MuteGame | Mute the game. I patched out the games audio manager. I did not experience any bugs but it is still poorly explored
  - StickToProcess | Stick the window to the upper-left corner to imitate the feeling of an internal hack.
- Navigation
  - Numpad * | Hide and disable input for the Trainer
  - Backspace | Navigate back to the menu
More features will be added soon. To your own benefit use the Quit option in the Trainer itself to automatically revert all changes to the process.  
Also make sure only one of the SolutionSolver options is enabled at a time. Same applys to the DisableSave!
