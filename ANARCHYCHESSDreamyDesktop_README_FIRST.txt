
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

