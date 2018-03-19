#include "DebugNew.h"
#include "Vertex.h"
#include "Graph.h"
#include "SearchAlgorithms.h"

int main (void)
{
    int screenWidth = 800;
    int screenHeight = 450;

    SVertex v1;
    SVertex v2;
    SVertex v3;
    SVertex v4;
    SVertex v5;
    SVertex v6;

    v1.label = "V1";
    v1.position = CVector2D{ 100.f,300.f };
    v1.tint = BURGUNDY;
    v2.label = "V2";
    v2.position = CVector2D{ 100.f,100.f };
    v2.tint = SKYBLUE;
    v3.label = "V3";
    v3.position = CVector2D{ 300.f,100.f };
    v3.tint = VIOLET;
    v4.label = "V4";
    v4.position = CVector2D{ 300.f,300.f };
    v4.tint = GRAY;
    v5.label = "V5";
    v5.position = CVector2D{ 200.f,200.f };
    v5.tint = GREEN;
    v6.label = "V6";
    v6.position = CVector2D{ 400.f,200.f };
    v6.tint = MAGENTA;

    Vertices vertices;
    vertices.push_back (&v1);
    vertices.push_back (&v2);
    vertices.push_back (&v3);
    vertices.push_back (&v4);
    vertices.push_back (&v5);
    vertices.push_back (&v6);

    CGraph graph{ vertices };

    graph.CreateNonDirectionalEdge (&v2, &v1);
    graph.CreateNonDirectionalEdge (&v2, &v3);
    graph.CreateNonDirectionalEdge (&v3, &v6);
    graph.CreateNonDirectionalEdge (&v4, &v3);
    graph.CreateNonDirectionalEdge (&v5, &v1);
    graph.CreateNonDirectionalEdge (&v5, &v2);
    graph.CreateNonDirectionalEdge (&v5, &v3);

    // Depth First Search.
    //SearchAlgorithms::DFS (&graph, &v4, true);
    // Breadth First Search.
    SearchAlgorithms::BFS (&graph, &v4);
    // Dijkstra.
    //SearchAlgorithms::Dijkstra (&graph, &v4);

    InitWindow (screenWidth, screenHeight, "C++ PATH FINDING");

    SetTargetFPS (60);

    while (!WindowShouldClose ())
    {

        BeginDrawing ();

        ClearBackground (RAYWHITE);

        graph.Draw ();

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}