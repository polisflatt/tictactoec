# tictactoec
The traditional tic-tac-toe written in C -- and with multiplayer support!

## What is tictactoec?
To put it very simply, tictactoec is yet another tic-tac-toe game written in C, with the addition of some P2P multiplayer support (due to boredom). It operates very much like any other version of the game would--perhaps a bit less efficiently. Tictactoec has a CLI-interface, without ncurses or anything, pure text. 

To play, just do `tictactoec` after installing, and you can play two-player, with no bot yet, sorry.

## Mechanics
In order to play, you are required to know how to operate a coordinate system, where the y-coordinates are in reverse order. This is because of how arrays work in most programming languages, including C.

When you play, you must place the coordinates down, first selecting the y-coordinate, and then the x-coordinate, like so: 

![enter image description here](https://i.ibb.co/9vCZj3w/2019-11-18-091406-688x250-scrot.png)


## Multiplayer
As aforementioned, tictactoec offers P2P multiplayer, through a host and a peer. Essentially, peer connects to a host, who is listening for connections. If you want to play through the internet-and not locally-you must, obviously, port forward.

To host, you need to `tictactoec --host [port] [username]`, where [port] is the port you wish to bind to, and [username] is the username you want to show up as (which is pointless, but I added it anyway).

To join a host, you must `tictactoec --join [address] [port] [username]`, where [address] is the IP address of the person you are joining, [port] is the port which is being binded to, and [username] which is what you want to show up as, as aforementioned. 

If you wish to send messages to one another (again, another pointless feature, which was added in anyway), you may, when prompted for your coordinate, type '-1' to be introduced to a command prompt. In this command prompt, you must type '@', followed by the message, with no spaces in between. Note, one person can only send a message at a time, when it is their turn, for simplicity purposes. Note, this feature is buggy right now and will most certainly segmentation fault.

It should also be noted that in order for two players to play with each other, they need the same number of rows and columns in their board array (i.e., the dimensions as said many times, they can be modified in the misc.c file). If one attempts to do so, the host will reject their connection, as the host sets the dimensions.

The host also decides if one can cheat or not. For instance, if I netcat the host, and type something impossible (like going onto a letter that already exists), the host will catch that and promptly kill the socket connection. However, this can be disabled by modifying the settings. 

Eventually, in the future, a matchmaking server can be made to connect P2P players. However, for now, I do not see that as necessary, considering how simple and primitive this game is. Though it should be mentioned that multiple players may be a thing in the future, with, let's say, 100x100 boards, with a move every day. That would make it more enjoyable. A web interface would also exist, interfacing with the protocol (porting this would be astronomically easy, considering how C is like other languages).

## Installation
In order to install tictactoe, you need make. Once you have make (or if you already do, which I would assume yes) you must run `sudo make install` to install it onto your system. Additionally, if you are paranoid, go check through the code or put it through a sandbox--whichever works best for you.

Additionally, you can compile the program itself, without installing it, and without root privileges by doing `make`, though I would assume you probably knew that.

## Configuration
If you wish to configure the game, you may seek the *misc.c* file, where you can configure the dimensions of the board, whether you want to protect against cheating or not, the error messages, or the protocol itself which multiplayer play abides by (which I highly recommend not to change, because it creates compatibility errors).
