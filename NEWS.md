### 2019-03-18 - DreamChess 0.3.0

DreamChess 0.3.0 is finally here. Eleven years have passed since the last
official release, with only a few release candidates happening in between.
Why has it taken so long? One reason is that the DreamChess team currently
consists of only two developers. Another reason is that we received very
little feedback for these release candidates, which made us reluctant to put
up a new official release. Especially considering the time and effort that
goes into building, testing and uploading official binaries.

Obviously this situation was far from ideal, and we wanted to lower the burden
for doing a release. We hope to have accomplished this now by integrating CI
systems. If things go according to plan, you can expect to see more frequent
releases from us going forward. These releases won't be getting the same
amount of testing that previous releases have had, but if problems pop up, we
should be able to get them sorted quickly, and push out a new version.

We hope you enjoy this long-awaited release.

Most important changes:
- Widescreen support
- Now uses SDL2 instead of SDL1
- Now uses Expat instead of mxml
- CMake build system
- Fixed issue with chess piece selection on some AMD GPUs
- Fixed issue with rotating chess board on some Linux machines
- Board is automatically flipped when playing with black
- Pondering support in Dreamer chess engine
- New icon
- Music pack support on macOS

### 2007-11-17 - DreamChess v0.2.0

Over a year has passed since the first release, and we are now happy to
present DreamChess v0.2.0. DreamChess is a 3D chess game for Windows, Mac OS X
and Linux. The new release can be downloaded from our website at
http://www.dreamchess.org.

The main new feature is sound support. Matthew P. Smith was kind of enough to
allow us to use some of his songs in the game. The music pack containing these
songs is available for download from our website.

Graphically the game has been improved significantly. This was made possible
by the decision to drop the Dreamcast port (see below). The old 3D models have
been replaced by new models with a lot more detail. Other improvements include
reflections, hardware lighting, new textures, and a new sketch theme by
Annie Kirkpatrick.

The GUI has seen many small improvements, such as additional options that
could previously only be set from the command line. A new feature is the
"easy mode" (for those who felt that our engine Dreamer put up too much of a
fight even on Level 1).

DreamChess is now also available for Mac OS X by courtesy of Lawrence Sebald.
Unfortunately, we were forced to drop support for Dreamcast and BeOS. If
you're interested in picking up these ports, please send an email to
feedback at dreamchess.org.

We hope you enjoy this new release!

About DreamChess:

DreamChess (http://www.dreamchess.org) is an open source chess game. Our
primary target platforms are Windows, Mac OS X and Linux. DreamChess features
3D OpenGL graphics and provides various chess board sets, ranging from classic
wooden to flat figurines.

A moderately strong chess engine is included: Dreamer. However, should this
engine be too weak for you, then you can use any other XBoard-compatible
chess engine, including the popular Crafty and GNU Chess.

Other features include music, sound effects, on-screen move lists using SAN
notation, undo functionality, and savegames in PGN format.

The DreamChess team currently consists of only a handful of people. We could
use help in many areas, such as programming, graphics, sound and testing. If
you're interested in helping out, please send an email to feedback at
dreamchess.org.

### 2006-09-24 - DreamChess v0.1.0

DreamChess (http://www.dreamchess.org) is an open source chess game. Our
primary target platforms are Linux, Windows, Dreamcast and BeOS. DreamChess
features 3D OpenGL graphics and provides various chess board sets, ranging
from classic wooden to flat figurines.

A moderately strong chess engine is included: Dreamer. However, should this
engine be too weak for you, then you can use any other XBoard-compatible
chess engine, including the popular Crafty and GNU Chess.

Other features include on-screen move lists using SAN notation, undo
functionality, and savegames in PGN format. In future releases we plan to add
support for time controls, audio, network play, more visual effects such as
reflections and shadows, and 3D animated pieces. If you're interested in
helping out, please head on over to http://www.dreamchess.org for more
information, and/or send an email to feedback at dreamchess.org.

We hope you enjoy the game!
