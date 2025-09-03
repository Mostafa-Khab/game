/*********************************
 * author     : mostafa khaled
 * date       : 
 * desc       : 
 ********************************/
#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>

class game 
{
  public:
    bool init(int w, int h, bool fullscreen, bool debug, bool vsync = true);
    void run();
    
    bool onSetup();
    void onUpdate();
    void onRender();
    void onShutDown();

    virtual bool setup() {return true;}
    virtual void update(){};
    virtual void render(){};
    virtual void shutdown(){};

  protected:
    GLFWwindow* window  = nullptr;
    int width, height;

    bool vsync;
};

#endif /* !GAME_HPP */
