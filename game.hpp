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
    
    virtual bool setup() {return true;}
    virtual void update(float dt){};
    virtual void render(){};
    virtual void shutdown(){};

  private:
    bool onSetup();
    void onUpdate(float dt);
    void onRender();
    void onShutDown();

  protected:
    GLFWwindow* window  = nullptr;
    int width, height;

    bool vsync;
};

#endif /* !GAME_HPP */
