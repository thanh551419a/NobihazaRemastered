

#include "axmol.h"
#include <string>
#ifndef __SPRITELOADER_H__
#    define __SPRITELOADER_H__
using namespace std;
USING_NS_AX;

class SpriteLoader 
{
    

private:
    Vector<SpriteFrame*> playerAnim[4][4];  // 4 directions, 4 type animate , 3 frames each


public:
    //static SpriteLoader* getInstance(); // Lấy Instance
    SpriteLoader(string path); // Constructor
    ~SpriteLoader(); // Destructor
    void addPlayerAnim(SpriteFrame* Sprite, int direction, int typeAnimate);// setter()
    void clearPlayerAnim();                                                   // clear all loaded animation
    Vector<SpriteFrame*> getPlayerAnim(int direction, int typeAnimate);     // getter()
};
#endif  //
