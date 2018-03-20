#pragma once

#include "Vector2D.h"

#include <string>
#include <raylib.h>

#define DARKGOLD CLITERAL{ 163, 141, 28, 255 }
#define BURGUNDY CLITERAL{ 166, 6, 76, 255 }

struct SNode
{
    SNode  (void) = default;
    ~SNode (void) = default;

    void Draw (void) const
    {
#pragma warning(push)
#pragma warning(disable: 4244)

        Vector2 size{ radius, radius };
        Vector2 pos { position.mX - radius/2, position.mY - radius/2 };


        DrawRectangleV (pos , size , tint);
        /*DrawCircle (
            position.mX
            , position.mY
            , radius/5
            , BLACK);*/
        DrawText   (
            label.c_str ()
            , position.mX - radius/2.5f
            , position.mY - radius/2.5f
            , 20
            , BLACK);
        DrawText   (
            std::to_string (static_cast<int>(weight)).c_str ()
            , position.mX - radius
            , position.mY - radius
            , 15
            , tint);

#pragma warning(pop)
    }

    unsigned int index   { 0 };
    SNode*       parent  { nullptr };
    std::string  label   {"node"};
    // Accumulated weight to reach the node.
    float        weight  { 0.f };
    bool         visited { false };
    // Current position in the screen.
    CVector2D    position{ 0.f,0.f };
    float        radius  { 30.f };
    // The tint with which the node will be drawn.
    Color        tint    { 255,255,255,255 };
};
