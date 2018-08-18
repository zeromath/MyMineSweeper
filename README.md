# MyMineSweeper

There are three game modes: LOW MID HIGH

- Double click "欢迎你" => Change User Name
- Double click sandglass icon => Restart the game
- Double click nuclear icon => Change game mode
- Double click score board => Ranking borad of top 5 gamers

Classes in the program:

- CMine: The main window and the main class
- CRecord: The record of top 5 users
- CMap: The map of the game
- DHero: The Dialog of ranking board
- DLevel: The Dialog to change game mode
- DUser: The Dialog to change user name
- LHero: The Label showing time
- LInfo: The Label showing mines
- LMine: The block in the main gaming area
- LUser: Welcome window

Process:
After CMine received mouseClick() event, it calls LMine to deal with it, which calls search function to do the rest

Assignments:

- Chen: CMap.init() and all icons
- Zhang: CMine.search() and CRecord class
- Me: The rest