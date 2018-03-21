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
        Vector2 nodeSize{ size, size };
        Vector2 pos { position.mX - size/2, position.mY - size/2 };


        DrawRectangleV (pos , nodeSize , tint);
        /*DrawCircle (
            position.mX
            , position.mY
            , radius/5
            , BLACK);*/
        DrawText   (
            label.c_str ()
            , position.mX - size / 2.5f
            , position.mY - size / 2.5f
            , 20
            , BLACK);
        if (!visited)
        {
            DrawText (
                "-"
                , position.mX - size
                , position.mY - size
                , 15
                , tint);
        }
        else
        {
            DrawText (
                std::to_string (static_cast<int>(weight)).c_str ()
                , position.mX - size
                , position.mY - size
                , 15
                , tint);
        }

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
    float        size    { 30.f };
    // The tint with which the node will be drawn.
    Color        tint    { 255,255,255,255 };
};
