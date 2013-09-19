A Qt-Browser for the Raspberry Pi, created by Björn Ejvald as part of a Master's Thesis in embedded systems, originally intended to be used as a Set-Top-Box for Hibox Systems Oy.


For the browser to work correctly, i.e. display hardware-accelerated video, Qt-Libraries have to be built together with Luca Carlons PiOMXTextures-plugin for QtMultimedia


The browser auto-launches to a website that is hardcoded, as this is the original purpose, but a parameter can be used to launch some other URL.


For example:

./rpi-qt-browser http://www.google.com


The javascript object "rpi" can be used to access media player controls. Details can be found in bridgeobject.cpp
