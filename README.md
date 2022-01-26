# dwm6-3
Yet another DWM repo. This repo is just another fork of dwm with some patches.

This repo though does not have the patches already applied, but has the vanilla code and you apply the patches. This allows to include further patches by adding them to the patch folder. 

## What patches are included?
* [cfact-vanitygaps combo](https://dwm.suckless.org/patches/vanitygaps/)
* [attach bottom](https://dwm.suckless.org/patches/attachbottom/)
* [autostart](https://dwm.suckless.org/patches/autostart/)
* [swallow](https://dwm.suckless.org/patches/swallow/)
* [status2d](https://dwm.suckless.org/patches/status2d/)
* [statusallmons](https://dwm.suckless.org/patches/statusallmons/)
* [statuscmd-status2d](https://dwm.suckless.org/patches/statuscmd/)

Needles to say, my job has been fixing the patch conflicts and determining the right order to apply them. I have not developed any of those patches, kudos goes to their creators.

## How do I apply the patches?
Instructions for dummies:
```
git clone https://github.com/DasHammett/dwm.git
cd dwm
for i in patches/*.diff; do patch --ignore-whitespace < $i; done
make
sudo make install
```
Please note the `--ignore-whitespace` from the patch command. Without it, several patches will fail to apply. I am too lazy to correct tabs for spaces and such, sorry :)

Also please have a look at `patches/8-config.def.h.diff` and make the necessary adjustments there. This is my personal preference and there are some custom scripts you problably will not have.
Should you forget to make the changes before applying the patches and compiling dwm, then remove `config.h`, edit `config.def.h` to your liking and compile again with `make` and `sudo make install`

## What bar do you use?
The bar is [dwmblocks-async](https://github.com/UtkarshVerma/dwmblocks-async) from the awesome UtkarshVerma. Please make sure you follow the instructions to the letter if you want to have the clickable blocks. I have included a patch for `dwm.c`, so should be enough to configure the bar and compile it.

## Wait, no screenshot?
Nope, not really... This is not a ricing dwm. Although you will find here the scripts I use for `dwmblocks-async`, the intention is to have a backup in case I screw-up somewhere down the line and I need a clean slate :)

## I am trying your dwmblocks scripts but some are not working
Some of the scripts point to other scripts I have in my system, mainly the `yad` windows for the weather and date scripts. The weather scripts themselves are in turn python scripts I wrote time ago. I will not post those. Should you really want them, let me know and I will see how I can share them with you.
