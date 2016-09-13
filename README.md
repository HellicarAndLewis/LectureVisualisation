# LectureVisualisation
A series of audio visualisations of recorded lectures.

# Controls

g to hide and show gui

m to show mouse

press play to start playing and hide the gui and mouse

gui for the rest!

#Required Addons

ofxNestedFileLoader: https://github.com/Bentleyj/ofxNestedFileLoader

ofxFft: https://github.com/kylemcdonald/ofxFft

ofxAudioVisualApp: (move the addon from the repo into the addons folder)

ofxGui: (included with openFrameworks)

# User Guide From Package
This is the general guide for the Lecture Visualization App created by Hellicar & Lewis. Please note that this application is in an early alpha stage.

The best way to learn the application is to play with it to experiment but some things are worth going over before-hand to clarify. This application will only run on a macintosh computer. To run the application simply right click on the icon file labelled test_allDebug. and select "open". A warning may appear telling you this application is from an unknown developer. Simply select "open anyway" to proceed.

There are two windows: a full-screen application that displays the visualization and a window that displays the controls for the visualization called the GUI. The full-screen window may oclude the GUI controls when you first launch the application, if this is the case simply expose your windows by pressing the F3 key to find the gui window. You can drag this window onto a second screen if you have one available so you can observe the full output of the visualization screen without seeing the gui.

The application is designed to take an audio file and use the FFT to create a beautiful color design based on the noise generate3d by the sound file. At the top left of your gui window you will see several buttons and sliders. Here is a quick reference about what each one does, starting with the first column and working down.

Sample Height: This does nothing and is obsolete.

Output On: This toggles the sound output on and off, you'll need to toggle this on to see the visualization.

Play: This toggles the sound pllaying on and off, you'll need to toggle this on to see the visualization.

Background auto: This toggles whether or not the background is refreshed each frame. You should toggle this on if you want to do a long exposure camera shot.

Speed: This scales the speed at which the audio is played from 1x speed to 10x speed. You can calculate the duration of the audio file using this number.

Scrub: This allows you to scrub through the audio by manually changing the play-head to a different part of the audio.
Draw Speed: This determines the rate at which your effects are drawn.

High: This is the color that corresponds to well represented frequency spectra.

Low: This is the color that corresponds to poorly represented frequency spectra.

Use FFT: This is make the FFT control the high and low colors.

Use Palette: This will toggle the use of a pre-loaded color palette selected below instead of the high and low colors. Colors will be sampled from left to right along the FFT from the pallete and if "Use FFT" is also enabled then the strip from which those colors are sampled will react to the volume of the sound being played. This is represented in the platte image near the bottom of the GUI.

Lectures: This is where you select which audio file you want to play. So-far only one audio file has been loaded so there is no need to use this section.

Palettes: This is where the palette you sample from while "Use Palette" is active is selected.

Threshold: This determined the threshold below which sound is not registered and therefor the overall brightness of the effects.

Symmetrical: This toggles between the symmetrical or top-down FFT option affecting the look of the visuals.

Start Bin: This determines which bin the FFT begins sampling from.

End Bin: This determines which bin the FFT ends sampling at.

Cut Up: This determines the high cut-off for frequencies.

Cut Down: This determines the low cut-off for frequencies.

Visualization options: These determine the overall visualization sceme. Select whichever you like!

Stream: Enable Tearing: This toggles whether or not tearing is enabled for the audio stream.

The best way to get comfortable with the app is to open it, select Output On and Play and then play with all of the parameters. You'll quickly learn what they all do!

