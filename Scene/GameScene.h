#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "axmol.h"
//#include "KeyboardInputState.h"
#include "./System/SpriteLoader.h"
#include<vector>
USING_NS_AX;

class GameScene : public ax::Scene
{
private:
    void playAnimation(int row, int col);
    //KeyboardInputState& KeyInputState;  // tham chiếu đến singleton KeyboardInputState
    float animDuration = 1.0f;  // tổng thời gian mỗi anim
    SpriteLoader Nobita;
    Sprite* playerSprite= nullptr; 
    int currentAnimRow = 0;
    int currentAnimCol = 0;
    TMXTiledMap* tileMap = nullptr;
    float cameraSpeed    = 30.0f;
    float playerSpeed    = 10.0f;
    Vec2 mapOffset       = Vec2::ZERO;
    Vec2 PlayerSpritePos = Vec2::ZERO;
    Vec2 PlayerPos       = Vec2::ZERO;
    Vec2 tileSize        = Size::ZERO;
    Size mapSize         = Size::ZERO;
    Size winSize         = Size::ZERO;
    Rect margin          = Rect(0, 0, 0, 0);  // margin for camera
    Vector<Sprite*> npcList;

public:
    static GameScene* createScene();
   
    virtual bool init() override;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    GameScene();  // contructor
    virtual ~GameScene();
    void movePlayer(Vec2 dir);
    void CheckAnimation(int up, int down, int left, int right);  // kiểm tra animation có cần thay đổi hay không
    void updateCameraAndPlayer(const Vec2& dir , float delta);
    virtual void update(float delta) override;
    Vec2 CanMoveMapAxis(const Vec2 dir);
    Vec2 resolv(float signal , char coordidate , Vec2 maxLimit);
};
#endif  // __GAME_SCENE_H__
