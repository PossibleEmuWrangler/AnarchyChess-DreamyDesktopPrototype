10th August 2023 Updated for release v0.8.6


AnarchyChess - Dreamy Desktop PROTOTYPE Readme First.
NOTE: the Prototype Github respository will soon become deprecated. Please file any issues in main repository


Contents:
  Intro
  Building Introduction
  Getting Started
  Limitations
  Known Bugs
  Appendix A: Raspberry Pi configuration steps
  Appendix B: Updated Raspberry Pi installation instructions
  Appendix C: Old Raspberry Pi installation instructions
  Appendix D: Ubuntu Build Notes

Intro.
This is a fork of Dreamchess added to allow promotion to Knook (Horsey and Rook)

Formally,in algebraic notation, the Knook is being treated as the letter "O"




Building Introduction
AnarchyChess Dreamy Desktop is more a code patch to dreamchess-0.3.0 than a fully supported standalone application. 
To build the program, the process involves using the Operating system to download the source for dreamchess 
and make use of Operating system specific changes (e.g. Patches by debian to get it to work with their OS).
This was done so as not to introduce another level of changes.

It was tested to be downloaded and installed on a Raspberry Pi 400 and step by step details are later in this document.


Getting Started


Once the program has started, go into the configuration.

The theme should be set to "Figurine" (preferred but 2d theme) or "Classic Wooden" (3d theme but knook "piece" is currently a partial rook).
Engine has to be set to "" (default should be "dreamer") The inbuilt engine dreamer hasn't been coded for the new piece yet and the game "undoes" moves its engine doesnt recognise.
The game does support xboard engines and im trying not to break that if i can help it.

Go back to main menu and select a new game
Games need to be set as Human vs human. Set difficulty Easy and Level 1 

Start Game

The promotion dialog doesnt have correct image for Knook yet, see dialog text as it says how to promote to knook.
On the 2d board themes, the Knook should have a K in the middle of the rook piece.





Limitations
 Dreamchess was built to be compatible with engines. AnarchyChess-DreamyDesktop initial release is only for Human vs Human games, AI is not supported at the moment as it will likely mess up their internal board represenations and cause issues.

Current testing has Engine text of "" instead of "dreamer" and this gives an error message
which was hardcoded out for this build. Need to add error message again for proper engine support

The graphics need some work and are planned to be changed in versions closer to 1.0 


Known Bugs

Some Algebraic notation for the Knook isnt showing correctly - not a showstopper


Promotion dialog does not have a image for the Knook (but there is text there to tell person to click rightmost horsey). 
 Fixing this means updating pieces.png in the styles/ directory as well as changes already made to pieces.
 I tried and couldnt get it working easily, so its staying open for now.
 pieces.png also contains an avatar image when i tried to add a Knook to rightmost, it didnt still read avatar correctly
 as if two distinct pieces of code and adding the extra column caused an inconsistency.

 I should be able to get to it later, but its not a showstopper.




A Knook capturing a Knook which had an enemy King in check caused a Crash/ Seg Fault.
 Need to look at this a bit. It should be fixed as i think the code tried to update a counter for captured pieces which didnt have a spot for Knooks. - Should be fixed






==========
Appendix A: Raspberry Pi configuration steps (first boot of system) - This appendix is for Chess players who might be overwhelmed setting up a new system

Boot Raspberry Pi with memory card in. 
Configure Country
Create User - For this guide we'll use the example of eg: garychess - Password EnPassant    Google how to generate a good password though.
Set Up Screen
Select WiFi Network - You'll need the SSID and password
Update Software - May take a while
Setup Complete - Restart the Computer , Login will be done automatically, proceed to Appendix B



==========
Appendix B: Updated Raspberry Pi installation instructions

Overview
  Download the dreamchess source
  Download the dreamydesktop source
  Unzip dreamydesktop source
  Compile code as dreamchess packages
  Install dreamchess packages
  Play

Its assumed the installer has a Raspberry Pi Debian Bullseye 2023-05-03 release running. These steps were tested with a clean installation of a image installed as per Appendix A. 

1. Open a command prompt window (click on icon with black background and >_ in toolbar) and type in the commands

2. Edit the sources file list so OS can download programs sources.
sudo nano /etc/apt/sources.list

When the editor opens, remove the "#" from the third line so it just starts with "deb-src"

Press Control + X to exit the program, saving the file updates.

3. run apt program so it knows about source URIs
sudo apt update

4. make a directory to build in and change directory to work in it
mkdir DreamChessBuild
cd  DreamChessBuild 
(Note: you can press Tab to complete long filenames)


5. Download the dreamchess source 
apt source dreamchess

6. Get code from AnarchyChess-DreamyDesktopPrototype repository
NOTE: This will eventually be changed to deal with packages and zips,

Open up chromium web browser (Blue circle icon with white lines through it) and go to https://github.com/PossibleEmuWrangler/AnarchyChess-DreamyDesktopPrototype

The page should have a Green icon with "Code" and a down arrow.

Click on the down arrow and click on "Download ZIP"

AnarchyChess-DreamyDesktopPrototype-main.zip should now be in your Downloads file


7. Unzip the AnarchyChess-DreamyDesktopPrototype-main.zip into the current directory
unzip ~/Downloads/AnarchyChess-DreamyDesktopPrototype-main.zip -d .

8. Copy DreamyDesktop source to overwrite dreamchess
cp -r AnarchyChess-DreamyDesktopPrototype-main/* dreamchess-0.3.0/

9. Change working directory into dreamchess-0.3.0
cd dreamchess-0.3.0

10. Download dependencies required to build
sudo apt install bison cmake debhelper-compat flex libglew-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev

11. Build package
dpkg-buildpackage -b -uc -us


12. Install app, data and dbgsym via package manager
sudo dpkg -i ../*.deb

13. Run Dreamchess
dreamchess


14. Continue from the "Getting Started" Section of this document. 



==========
Appendix C: Old Raspberry Pi installation instructions 

Installation for Raspberry Pi 400 (Package install dreamchess, localbuild anarchychess exe from anarchychess-dreamydesktopprototype repository	)- Last updated 31Jul2023

The aim of these steps is to get a repeatable steps for users to download the build and get it
running on their computer. 



RaspberryPi Imager v1.7.5 used, Raspberry Pi OS 32-bit Debian Bullseye Released 2023-05-03 used. 

Assumed User has full access to system and created initial account which is used to do install.
System updated to latest as part of initial install
 

1. Open a command prompt up, create a directory to build in and cd into it
mkdir DreamChessBuild
cd DreamchessBuild

2. Edit file to allow downloading of package sources
sudo nano /etc/apt/sources.list

3. remove "#" from first column on third line and save with CTRL-O
Note: line to read "deb-src"... instead of "#deb-src"...

4. exit nano with CTRL-X

5. run apt program so it knows about source URIs
sudo apt update

5. download source using apt command (as regular user, not root so we dont need sudo) 
apt source dreamchess

6. install dreamchess onto system using OS package manager.
sudo apt install dreamchess

7. test run dreamchess to confirm it runs on system natively
dreamchess

8. Start a new Human vs human game on original install
New Game
Players -> Human vs Human
Start Game

9. e4 e5 Ke2 Ke7 and Quit game
Right click -> Quit Game. 
Quit to Title -> Ok


10. Change configuration for Theme and remove engine
Click Configuration.
Change theme to "Figureine"
Delete all text in Engine textbox
Click Ok

11.Start a new game with figureine piece set
Board loads using 2D pieces.

12. e4 e5 Ke2 Ke7 and Quit game
Right click -> Quit Game. 
Quit to Title -> Ok

13. Quit Dreamchess
Window closes and back to command prompt


14. Get code from AnarchyChess-DreamyDesktopPrototype repository
NOTE: This will eventually be changed to deal with packages and zips,

Open up chromium web browser and go to https://github.com/PossibleEmuWrangler/AnarchyChess-DreamyDesktopPrototype

The page should have a Green icon with "Code" and a down arrow.

Click on the down arrow and click on "Download ZIP"

AnarchyChess-DreamyDesktopPrototype-main.zip should now be in your Downloads file

15. Move code to folder to build from
Move ZIP file to DreamChessBuild directory created earlier (either by command line or file explorer)


16. Unzip ZIP file
from the command line, "unzip AnarchyChess-DreamyDesktopPrototype-main.zip" or "unzip An<TAB>" for command line to complete the filename via TAB shortcut



17 Using the file explorer copy all files and subdirectories in AnarchyChess folder into dreamchess-0.3.0 folder, overwriting any existing files.


18 Change command prompt to dreamchess-0.3.0 subdirectory.
cd dreamchess-0.3.0


19. Build (without required dependencies installed)
dpkg-buildpackage -b -uc -us

A print out of unmet dependencies is shown


19 Download dependencies required to build
sudo apt install bison cmake debhelper-compat flex libglew-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev


20. Build (without required dependencies installed)
dpkg-buildpackage -b -uc -us


21 Install app, data and dbgsym via package manager
sudo dpkg -i ../dreamchess_0.3.0-1_armhf.deb
sudo dpkg -i ../dreamchess-data_0.3.0-1_all.deb
sudo dpkg -i ../dreamchess-dbgsym_0.3.0-1_armhf.deb

22 Run Dreamchess
dreamchess

(AnarchChess 0.3.0 Development) is printed on command line and GUI shows red spraypaint.

23 Update configuration
Configuration -> Engine = ""

24. Start New game of Human vs Human
Board is shown with 2d characters 

25. Begin playtest game

 O is Knooks character in Algebraic notation
1. e4 d5
2. exd5 c5
3. dxc6 f6
4. cxb7 f5
5. bxa8=O f4
6. Ob6   (Note: O is shown as boxy square, known bug)


Appendix D: Ubuntu Build Notes
    To get dreamchess working on Ubuntu 20.04 i created a sub directory in my home directory called DreamChessBuild

    I then changed directory to that directory

    I used apt to get the source (don’t do as root)

    change directory into dreamchess-0.3.0 5?? i might have run configure, unsure, but noting for future reference

    build with dpkg-buildpackage -b -uc -us

    Hit error messages about uninstalled packages needed to build, had to install several as root.

    build again

    run the new package (note although exe is in subdirectiory, the program uses global files like /usr/share/games/dreamchess/pieces)

Commands
    mkdir DreamChessBuild

    cd DreamChessBuild

    apt source dreamchess

    cd dreamchess-0.3.0

    dpkg-buildpackage -b -uc -us

    sudo apt install bison flex libglew-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev

    dpkg-buildpackage -b -uc -us

    ./debian/dreamchess/usr/games/dreamchess



Files on installed system.
Image files and stuff the program uses are in /usr/share/games/dreamchess/



