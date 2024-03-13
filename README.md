folder includes a Visual Studio Solution with release and debug versions of the game project and instalation project, along with the Visual C++ redistributable package


This is a clone of a retro game Breakout where the goal is to clear a level using a bouncing ball. Player controls a paddle with A and D keys and needs to prevent the ball from touching the lower edge of the game screen. Once player destroys all of the brick on a level, a new random level is chosen among 9 possible. The game ends in a win once the player reaches a certain score or in a loss once the ball touches the lower egde 3 times (represented by 3 lives).
Player can press Q during a game to forfeit the score and return to title screen.

Game was made using Visual Studio 2022 in C++ using Allegro5 library for managing game objects and rendering, and pugiXML library to parse the XML files used to design levels. As mentioned, levels can be created using the XML by following the same pattern as for other, existing levels. Currently, levels are read by the game per-name, so one level would have to be replaced and named exactly the same as the one being replaced to be recognized by the game.
