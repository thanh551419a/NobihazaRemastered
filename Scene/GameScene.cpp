#include "GameScene.h"
#include "./System/SpriteLoader.h"
//#include "KeyboardInputState.h"
#include<math.h>
USING_NS_AX;
GameScene* GameScene::createScene()
{
    auto scene = GameScene::create();
    return scene;
}

bool GameScene::init()
{
    //npcList.resize(100);  // dự trữ chỗ cho 100 npc
    for (auto npc : npcList) {
        npc = Sprite::create("../assets/Sprite/Nobita/tile1.png");
        AXLOG("NPC Address: %p", npc);
    }
    winSize = Director::getInstance()->getWinSize();

    auto draw = DrawNode::create();
    draw->drawRect(Vec2(0, 0), Vec2(winSize.width, winSize.height), Color4F::RED);
    margin = Rect(9, 0, 9, 15);  // left , bottom , right , top
    this->addChild(draw, 1000);

    
    winSize     = Director::getInstance()->getWinSize();
    //auto origin      = Director::getInstance()->getVisibleOrigin();
    tileMap          = TMXTiledMap::create("../assets/Map/Map/mapTest1.tmx");
    this->addChild(tileMap);
    mapSize          = tileMap->getContentSize();
    PlayerPos        = Vec2(winSize.width * 0.5f, winSize.height * 0.5f);

    auto defaultAnim = Nobita.getPlayerAnim(0, 0);

    if (!defaultAnim.empty())
    {
        playerSprite = Sprite::createWithSpriteFrame(defaultAnim.at(0));
        playerSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
        PlayerSpritePos = Vec2(winSize.width * 0.5f, winSize.height * 0.5f);
        playerSprite->setPosition(PlayerSpritePos);  // Đặt vị trí ban đầu của nhân vật ở
        this->addChild(playerSprite);

        // 2. Chạy animation mặc định (idle)
        playAnimation(0, 0);
        
    }

    //KeyInputState.init(this);

    
    if (!Scene::init())
    {
        return false;
    }

    // Your initialization code here
    this->scheduleUpdate();
    return true;
}
Vec2 clampf2(Vec2 &v , Vec2 min , Vec2 max) {
    return Vec2(clampf(v.x, min.x, max.x), clampf(v.y, min.y, max.y));
}
Vec2 convertSizeToVec2(Size x) {
    Vec2 res;
    res.x = x.width;
    res.y = x.height;
    return res;
}
Vec2 Compare(const Vec2& v, const Vec2& min, const Vec2& max)
{
    Vec2 r;

    r.x = (v.x < min.x) ? 1 : (v.x > max.x) ? -1 : 0;

    r.y = (v.y < min.y) ? 1 : (v.y > max.y) ? -1 : 0;

    return r;
}

Vec2 GameScene::resolv(float signal , char coordidate, Vec2 maxLimit) {// hàm này sẽ xử lý và đưa ra xem cần di chuyển map , sprite như thế nào , signal là tín hiệu xem player đang ở đâu , coordidate là theo trục nào
    float PlayerPos1        = (coordidate == 'x') ? PlayerPos.x : PlayerPos.y; // Tọa độ convert theo coordidate
    float winSize1   = (coordidate == 'x') ? winSize.x : winSize.y;                  // winSize convert theo coordidate
    float maxOffset         = (coordidate == 'x') ? maxLimit.x : maxLimit.y;   // maxLimit convert theo coordidate

    Vec2 res; // res trả về là offset và tọa độ của PlayerSprite;
    if (signal == 1)
    {
        res.x = 0;
        res.y = PlayerPos1;
    }
    else if (signal == 0)
    {
        res.x = PlayerPos1 - winSize1/2;  // offset của tileMap
        res.y = winSize1 / 2;
    }
    else if (signal == -1)
    {
        res.x = maxOffset - winSize1/2;
        res.y = winSize1 / 2 + (PlayerPos1 - maxOffset); 
    }
    return res;

}
float clampWithBias(float value, float min, float max)
{
    if (value < min)
        return min;

    if (value > max)
        return max + 9.0f;

    return value;
}

void GameScene::updateCameraAndPlayer(const Vec2& dir, float delta)
{

    Vec2 minLimit = winSize / 2;
    Vec2 maxLimit = mapSize - winSize/2;

    AXLOG("PlayerPos before: x:%f y%f",PlayerPos.x, PlayerPos.y);
    PlayerPos += dir* cameraSpeed;
    //Tính offset
    
    PlayerPos = clampf2(PlayerPos, Size(0, 0), Size(mapSize.width, mapSize.height));// giới hạn lại tọa độ player trong map
    
    Vec2 cmp = Compare(PlayerPos, minLimit, maxLimit);
    // offset khong duoc vuot qua maxLimit
    Vec2 MoveX = resolv(cmp.x, 'x', maxLimit);
    Vec2 MoveY = resolv(cmp.y, 'y', maxLimit);

    /*AXLOG("Cmp Valuer: x:%f y:%f", cmp.x, cmp.y);
    AXLOG("maxLimit : x:%f y:%f", maxLimit.x, maxLimit.y);
    AXLOG("minLimit : x:%f y:%f", minLimit.x, minLimit.y);
    AXLOG("PlayerPos after : x:%f y:%f", PlayerPos.x, PlayerPos.y);
    AXLOG("Offset tileMap : x:%f y:%f", -MoveX.x, -MoveY.x);
    AXLOG("PlayerSpritePos : x:%f y:%f", MoveX.y, MoveY.y);*/

    tileMap->setPosition(Size(-MoveX.x , -MoveY.x));
    //AXLOG("Margin : x:%f y:%f w:%f h:%f", margin.origin.x, margin.origin.y, margin.size.width, margin.size.height);
    MoveX.y = clampWithBias(margin.origin.x, MoveX.y, 1272.0f);
    MoveY.y = clampf(margin.origin.y, MoveY.y, MoveY.y + margin.size.height);
    playerSprite->setPosition(Vec2(MoveX.y, MoveY.y));
}



//GameScene::GameScene() : KeyInputState(KeyboardInputState::getInstance()), Nobita("../assets/Sprite/Nobita")
//{
//    playerSprite = nullptr;
//    AXLOG("GameScene Constructor");
//}
GameScene::GameScene() : Nobita("../assets/Sprite/Nobita")
{
	playerSprite = nullptr;
	AXLOG("GameScene Constructor");
}
GameScene::~GameScene()
{
    // Destructor code here
    AXLOG("GameScene Destructor");
}
void GameScene::playAnimation(int row, int col)
{
    // Tránh chạy lại animation đang chạy
    if (currentAnimRow == row && currentAnimCol == col)
        return;

    // Dừng animation cũ
    playerSprite->stopAllActions();

    // Lấy animation mới
    auto playerAnim = Nobita.getPlayerAnim(row, col);
    if (playerAnim.empty())
    {
        AXLOG("Animation [%d][%d] không tồn tại!", row, col);
        return;
    }

    // Tạo và chạy animation
    float animDuration = 0.5f;
    float frameTime    = animDuration / playerAnim.size();
    auto animation     = Animation::createWithSpriteFrames(playerAnim, frameTime);
    animation->setLoops(-1);  // Loop vô hạn
    animation->setRestoreOriginalFrame(false);
    auto animate = Animate::create(animation);

    playerSprite->runAction(animate);

    // Cập nhật trạng thái
    currentAnimRow = row;
    currentAnimCol = col;

    //AXLOG("Đổi sang animation [%d][%d]", row, col);
}
void GameScene::CheckAnimation(int up , int down , int left , int right) {
    
    //if (up != 0 || down != 0 || left != 0 || right != 0)
      //  AXLOG("W:%d S:%d A:%d D:%d", up, down, left, right);
    int rows = 0;
    int cols = 0;
    if (down)
        rows = 0;
    if (left)
        rows = 1;
    if (right)
        rows = 2;
    if (up)
        rows = 3;
    if (up != 0 || down != 0 || left != 0 || right != 0)
        playAnimation(rows, cols);
}
void GameScene::update(float delta)
{
    int up, down, left, right;
    
    //up    = KeyInputState.takeKey(EventKeyboard::KeyCode::KEY_W) ? 1 : 0;
    //down  = KeyInputState.takeKey(EventKeyboard::KeyCode::KEY_S) ? 1 : 0;
    //left  = KeyInputState.takeKey(EventKeyboard::KeyCode::KEY_A) ? 1 : 0;
    //right = KeyInputState.takeKey(EventKeyboard::KeyCode::KEY_D) ? 1 : 0;
    //CheckAnimation(up , down , left , right);
    //Vec2 dir(right - left, up - down);
    ///*movePlayer(dir);*/
    //if(dir != Vec2::ZERO) updateCameraAndPlayer(dir, delta);

    //temp->removeFromParent();
}
