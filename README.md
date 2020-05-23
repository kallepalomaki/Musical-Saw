Copyright Kalle Palomäki 21-May-2020

This project includes source codes and image assets of the Musical Saw app
for iOS. The code is shared under GNU Public Licence (GPLv2). See license
terms:
https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html

You can get the Musical Saw app from Apple AppStore for free.

The project uses cocos2dx and Juce libraries. That you need to obtain
them separately.

Steps to get going.

1) Get cocos2d-x
The current version of Musical Saw app is based on cocos2dx that is
newer than current release obtained through github. This is because of
UIWeb view fix.

You can get it as follows:
git clone https://github.com/cocos2d/cocos2d-x cocos2d-x
cd cocos2d-x
git checkout f07cf50a3edd4074447135448ce981823b341927 

2) Get Juce. I have used Version 3.2.0. You can get it from github
as follows.
git clone https://github.com/juce-framework/JUCE juce
cd juce
git checkout f07cf50a3edd4074447135448ce981823b341927

Newer versions may also work, but I haven't tested.

3) Compose project. Start with cocos2d-x. Follow instructions in cocos2d-x
to install cocos2d-x and make a simple HelloWorld project. You may choose a
name you want for the project.

Open and compile the project in xcode. You can get more information from:
www.cocos.com

4) Add source files distributed here to "Classes" - directory with the copy
flag on. Make sure all *.cpp files are compiled.

5) Add Juce. In xcode go to build phases and add the following juce files
to Compile Sources. Add juce "modules" directory under JuceLibraryCode/

juce_audio_formats.mm
juce_graphics.mm
jucd_data_structures.mm
juce_events.mm
juce_audio_devices.mm
juce_core.mm
juce_gui_basics.mm
juce_audio_utils.mm
juce_audio_basics.mm

6) In build phases headers add AppConfig.h

7) Add all the png images into Resources directory.

6) Under proj.ios_mac/ios drag icon*.png files to right places in
Images.xcassets