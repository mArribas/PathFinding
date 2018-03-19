#pragma once

#include "Vector2D.h"

#include <string>
#include <raylib.h>

#define DARKGOLD CLITERAL{ 163, 141, 28, 255 }
#define BURGUNDY CLITERAL{ 166, 6, 76, 255 }

struct SVertex
{
    SVertex  (void) = default;
    ~SVertex (void) = default;

    void Draw (void) const
    {
#pragma warning(push)
#pragma warning(disable: 4244)

        DrawCircle (
            position.mX
            , position.mY
            , radius
            , tint);
        DrawText (
            label.c_str ()
            , position.mX + radius
            , position.mY + radius
            , 20
            , tint);
        DrawText (
            std::to_string (weight).c_str ()
            , position.mX - radius * 2
            , position.mY - radius * 3
            , 10
            , tint);

#pragma warning(pop)
    }

    unsigned int index     { 0 };
    SVertex*     parent    { nullptr };
    std::string  label     {"VERTEX"};
    // Accumulated weight to reach the vertex.
    float        weight    { 0.f };
    bool         visited   { false };
    // Current position in the screen.
    CVector2D    position  { 0.f,0.f };
    float        radius    { 7.f };
    // The tint with which the vertex will be drawn.
    Color        tint      { 255,255,255,255 };
};
