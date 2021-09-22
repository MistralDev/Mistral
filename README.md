# Mistral 
[![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=flat-square)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![TF2](https://img.shields.io/badge/game-TF2-orange.svg?style=flat-square)](https://store.steampowered.com/app/440/Team_Fortress_2/) 
[![GNU/Linux](https://img.shields.io/badge/platform-GNU%2FLinux-ff69b4?style=flat-square)](https://www.gnu.org/gnu/linux-and-gnu.en.html) 
[![x86](https://img.shields.io/badge/arch-x86-red.svg?style=flat-square)](https://en.wikipedia.org/wiki/X86) 
[![License](https://img.shields.io/github/license/MistralDev/Mistral.svg?style=flat-square)](LICENSE)
[![Issues](https://img.shields.io/github/issues/MistralDev/Mistral.svg?style=flat-square)](https://github.com/MistralDev/Mistral/issues)

Free open-source GNU/Linux training software for **Team Fortress 2** game. Designed as an internal cheat - [Shared Library](https://en.wikipedia.org/wiki/Library_(computing)#Shared_libraries) (SO) loadable into game process. Compatible with the Steam version of the game.

## Getting started

### Prerequisites

Prerequisites are handled automatically by the [dependencycheck](https://github.com/MistralDev/Mistral/blob/master/scripts/dependencycheck) script.

### Downloading

Open a terminal window and enter following command:

    bash <(wget -qO- https://raw.githubusercontent.com/MistralDev/Mistral/master/install-all)

`Mistral` folder should have been successfully created, containing all the source files.

### Compiling from source

When you have equipped a copy of the source code, next step is opening it with your IDE of choice.

Then check if your particular CPU supports the `AVX2` instruction set, if not change all `-mavx2` arguements inside [CMakeLists.txt](https://github.com/MistralDev/Mistral/blob/master/CMakeLists.txt) to `-march=native -mtune=native`. This should result in more performant code, optimized for your CPU.

And simply run the following command while inside the source folder:

    ./toolbox.sh -b

If everything went right you should receive `libMistral.so`  binary file.

### Loading / Injecting into game process

The loading script will try to disguise Mistral as the [gamemode](https://github.com/FeralInteractive/gamemode) library. If you happen to be using it, change `libgamemodeauto.so.0` inside [toolbox.sh](https://github.com/MistralDev/Mistral/blob/master/toolbox.sh) to other library names.

Run the following command while inside the source folder:

    ./toolbox.sh -l

This will inject `libMistral.so` into `hl2_linux` process.

When injected, menu is openable under `INSERT` key.

## FAQ

### How do I open menu?
Press <kbd>INSERT</kbd> while focused on TF2 window.

### Where is my config file saved?
Configuration files are saved inside `Mistral` folder in your `opt` folder (`/opt/Mistral/data`). The config is in human readable format and can be edited via your text editor of choice.

## Acknowledgments

*   [nullworks](https://github.com/nullworks) and [contributors](https://github.com/nullworks/cathook/graphs/contributors) for creating and maintaining a GNU/Linux TF2 training software - [cathook](https://github.com/nullworks/cathook).
*   [ocornut](https://github.com/ocornut) and [contributors](https://github.com/ocornut/imgui/graphs/contributors) for creating and maintaining an amazing GUI library - [Dear imgui](https://github.com/ocornut/imgui).
*   [nlohmann](https://github.com/nlohmann) and [contributors](https://github.com/nlohmann/json/graphs/contributors) for creating and maintaining JSON for modern C++ - [json](https://github.com/nlohmann/json).
*   [seksea](https://github.com/seksea) for creating a convenient toolbox.sh utility.
*   [danielkrupinski](https://github.com/danielkrupinski/Osiris) - for creating his README file that I used as a template.

## See also
*   [cathook](https://github.com/nullworks/cathook) - Training software that I started on.