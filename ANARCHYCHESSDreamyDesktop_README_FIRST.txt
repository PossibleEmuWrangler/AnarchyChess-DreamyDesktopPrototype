
AnarchyChess - Dreamy Desktop PROTOTYPE Readme First.

Intro.
This is a fork of Dreamchess added to allow promotion to Knook (Horsey and Rook)

Formally,in algebraic notation, the Knook is being treated as the letter "O"



Build Plan

 I'm looking to complete a prototype solo with butchered graphics and then create a project open for others to contribute

 I dont want to ask anyone to spend hours making graphics without being able to deliver, plus Ive got some personal reasons
 to get it done solo aside from some techincal reasons. It should be done within a week and prototype gets removed. 
 the Prototype project will remain distinct but become dormant. 


 After that, it'll migrate to AnarchyChess-DreamyDesktopV0.8 and be made publicly available to developers as alpha testers

 After theres a consensus its good, AnarchyChess-DreamyDesktopV0.9 goes to wider playtest as beta

 And AnarchyChess-DreamyDesktopV1.0 should be publicly released as a fully working project. 



Getting Started

Once the program has started, go into the configuration.

Theme should be set to "Figurine" (preferred but 2d) or "Classic Wooden" (3d but knook "piece" is currently a partial rook).
Engine has to be set to "" (default should be "dreamer") The engine(s) havent been coded for the new piece yet and the engine can "undo" moves it doesnt recognise.

Go back to main menu and select a new game
Games need to be set as Human vs human. Set difficulty Easy and Level 1 

Start Game

For the first run do the moves:

  e4 d5
  exd5 c5
  dxc6 f6
  cxb7 f5 (alternately kf7)
  bxa8=O.

Promotion dialog doesnt have correct image for Knook yet, see dialog text as it says how to promote to knook.
On the board the Knook should have a K in the middle of the rook piece.

Quit game, and then start a new game. 




Limitations
 Dreamchess was built to be compatible with engines. AnarchyChess-DreamyDesktop
 initial release is only for Human vs Human games, AI is not supported at the moment as it will likely mess up their internal board represenations and cause issues.

Current testing has Engine text of "" instead of "dreamer" and this gives an error message
which was hardcoded out for this build. Need to add error message again for proper engine support

The graphcis need some work and are planned to be changed. 


Known Bugs

Some Algebraic notation for the Knook isnt showing correctly
 not a showstopper


Promotion dialog does not have a image for the Knook (but there is text there to tell person to click rightmost horsey). 
 Fixing this means updating pieces.png in the styles/ directory as well as changes already made to pieces.
 I tried and couldnt get it working easily, so its staying open for now.
 pieces.png also contains an avatar image when i tried to add a Knook to rightmost, it didnt still read avatar correctly
 as if two distinct pieces of code and adding the extra column caused an inconsistency.

 I should be able to get to it later, but its not a showstopper.


A Knook capturing a Knook which had an enemy King in check caused a Crash/ Seg Fault.
 Need to look at this a bit. It should be fixed as i think the code tried to update a counter for captured pieces which didnt have a spot for Knooks.



Notes:



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

==========
Appendix A:
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


