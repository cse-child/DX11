#pragma once


struct Vertex // ����: 3���� ���������� �� ��
{
    Float3 pos;
    Float2 uv; // u:����, v:���� ,0~1���� ���� ����

    Vertex() : pos(0, 0, 0), uv(0, 0)
    {
    }

    Vertex(float x, float y, float u, float v)
        :pos(x, y, 0), uv(u, v)
    {
        
    }
};

struct VertexColor // ����: 3���� ���������� �� ��
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