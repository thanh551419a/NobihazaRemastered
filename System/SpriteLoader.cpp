#include "SpriteLoader.h"
#include "axmol.h"
#include <iostream>
#include <fstream>
using namespace ax;

//SpriteLoader* SpriteLoader::getInstance()
//{
//    static SpriteLoader instance;
//    return &instance;
//}

void SpriteLoader::addPlayerAnim(SpriteFrame* frame, int direction, int typeAnimate)
{
    if (direction < 0 || direction >= 4)
        return;
    if (typeAnimate < 0 || typeAnimate >= 4)
        return;

    playerAnim[direction][typeAnimate].pushBack(frame);
}

void SpriteLoader::clearPlayerAnim()
{
    for (int d = 0; d < 4; d++)
        {
        for (int t = 0; t < 4; t++)
            {
                playerAnim[d][t].clear();  // tự release SpriteFrame*
            }
        }
}
Point ConvertNumberToPostion(int n)
{
    if (n < 1 || n > 48)
        return Point::ZERO;

    int index = (n - 1) / 3;

    int direction = index / 4;
    int typeAnim  = index % 4;

    //AXLOG("ConvertNumberToPostion: %d -> (%d, %d)", n, direction, typeAnim);
    return Point(direction, typeAnim);
}

int ConvertPathToNumber(string s) {
    int res = 0;
    bool check = false;
    for (char c : s)
    {
        if (c >= '0' && c <= '9')
        {
            res = res * 10 + (c - '0');
        }
    }
    //AXLOG("%s %d", s.c_str(), res);
    return res;
}

SpriteLoader::SpriteLoader(string path)
{
    // Constructor code here
    AXLOG("SpriteLoader Constructor");
    auto files = FileUtils::getInstance()->listFiles(path);
    for (const auto& file : files)
    {   
        //AXLOG("Found file: %s", file.c_str());
        int num = ConvertPathToNumber(file);
        if (num > 48)
            continue;
        Point temp = ConvertNumberToPostion(num);
        //AXLOG("File: %s -> (%f, %f)", file.c_str(), temp.x, temp.y);
        SpriteFrame* SpriteFrame1 = SpriteFrame::create(file, Rect(0 , 0 , 64 , 64));
        addPlayerAnim(SpriteFrame1, temp.x, temp.y);
        //AXLOG("Them SpriteFrame vao anim %d %d", temp.x, temp.y);
    }
    //AXLOG("kich thuoc cua vector tai 0 0 la %d %d", playerAnim[0][0].size());
}

SpriteLoader::~SpriteLoader()
{
    // Destructor code here
    clearPlayerAnim();
    AXLOG("SpriteLoader Destructor");
}

Vector<SpriteFrame*> SpriteLoader::getPlayerAnim(int direction, int typeAnimate)
{
    return playerAnim[direction][typeAnimate];
}
