# game
- a class which does some job of initing glfw with some options
- intented to be used as a base class for some more complex games
- more functionality maybe added later
- it have 4 functions that can be overrided
  * `bool setup()`  called before main loop
  * `void update()` called in main loop before render()
  * `void render()` called in main loop after update()
  * `void shutdown()` called in ma
