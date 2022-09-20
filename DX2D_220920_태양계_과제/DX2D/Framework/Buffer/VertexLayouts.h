#pragma once


struct Vertex // 정점: 3차원 공간에서의 한 점
{
    Float3 pos;

    Vertex() : pos(0, 0, 0)
    {
    }

    Vertex(float x, float y)
    {
        pos = { x, y, 0.0f };
    }
};

struct VertexColor // 정점: 3차원 공간에서의 한 점
{
    Float3 pos;
    Float4 color;

    VertexColor() : pos(0, 0, 0), color(1, 1, 1, 1)
    {
    }

    VertexColor(float x, float y, float r, float g, float b)
    {
        pos = { x, y, 0.0f };
        color = { r, g, b, 1.0f };
    }
};