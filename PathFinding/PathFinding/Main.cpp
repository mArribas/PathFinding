#include "DebugNew.h"
#include "Node.h"
#include "Graph.h"
#include "GraphSearchAlgorithms.h"
#include "Grid.h"
#include "GridSearchAlgorithms.h"

void DrawInputMap  (void);

int main (void)
{
    int screenWidth  = 800;
    int screenHeight = 400;

    // Graph
    SNode v1;
    SNode v2;
    SNode v3;
    SNode v4;
    SNode v5;
    SNode v6;

    v1.label = "V1";
    v1.position = CVector2D{ 100.f,300.f };
    v1.tint = PINK;
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
    v5.tint = DARKGREEN;
    v6.label = "V6";
    v6.position = CVector2D{ 400.f,200.f };
    v6.tint = MAGENTA;

    Nodes nodes;
    nodes.push_back (&v1);
    nodes.push_back (&v2);
    nodes.push_back (&v3);
    nodes.push_back (&v4);
    nodes.push_back (&v5);
    nodes.push_back (&v6);

    CGraph graph{ nodes };

    graph.CreateDirectionalEdge (&v1, &v2);
    graph.CreateNonDirectionalEdge (&v2, &v3);
    graph.CreateNonDirectionalEdge (&v4, &v3);
    graph.CreateNonDirectionalEdge (&v5, &v1);
    graph.CreateNonDirectionalEdge (&v5, &v2);
    graph.CreateNonDirectionalEdge (&v5, &v3);

    bool bfs       { false };
    bool dfs       { false };
    bool dijkstra  { false };
    bool aStar     { false };
    bool biDirAStar{ false };
    bool setStart  { false };
    bool setEnd    { false };

    SNode* start{ nullptr };
    SNode* end  { nullptr };

    // Grid.
    CGrid grid{ 8, 16, 50.f };

    InitWindow (screenWidth, screenHeight, "C++ PATH FINDING");

    SetTargetFPS (60);

    Nodes path;

    while (!WindowShouldClose ())
    {
        // Input.
        if (IsKeyDown (KEY_A))
        {
            bfs        = true;
            dfs        = false;
            dijkstra   = false;
            aStar      = false;
            biDirAStar = false;
        }

        if (IsKeyDown (KEY_B))
        {
            bfs        = false;
            dfs        = true;
            dijkstra   = false;
            aStar      = false;
            biDirAStar = false;
        }

        if (IsKeyDown (KEY_C))
        {
            bfs        = false;
            dfs        = false;
            dijkstra   = true;
            aStar      = false;
            biDirAStar = false;
        }

        if (IsKeyDown (KEY_D))
        {
            bfs        = false;
            dfs        = false;
            dijkstra   = false;
            aStar      = true;
            biDirAStar = false;
        }

        if (IsKeyDown (KEY_E))
        {
            bfs        = false;
            dfs        = false;
            dijkstra   = false;
            aStar      = false;
            biDirAStar = true;
        }

        /*if (IsKeyDown (KEY_S)) setStart = true;
        if (IsKeyDown (KEY_E)) setEnd   = true;
        if (IsKeyDown (KEY_R)) end      = nullptr;

        if (IsKeyDown (KEY_ONE) && setStart)
        {
            setStart = false;
            start    = &v1;
        }
        if (IsKeyDown (KEY_ONE) && setEnd)
        {
            setEnd = false;
            end    = &v1;
        }
        if (IsKeyDown (KEY_TWO) && setStart)
        {
            setStart = false;
            start    = &v2;
        }
        if (IsKeyDown (KEY_TWO) && setEnd)
        {
            setEnd = false;
            end    = &v2;
        }
        if (IsKeyDown (KEY_THREE) && setStart)
        {
            setStart = false;
            start    = &v3;
        }
        if (IsKeyDown (KEY_THREE) && setEnd)
        {
            setEnd = false;
            end    = &v3;
        }
        if (IsKeyDown (KEY_FOUR) && setStart)
        {
            setStart = false;
            start    = &v4;
        }
        if (IsKeyDown (KEY_FOUR) && setEnd)
        {
            setEnd = false;
            end    = &v4;
        }
        if (IsKeyDown (KEY_FIVE) && setStart)
        {
            setStart = false;
            start    = &v5;
        }
        if (IsKeyDown (KEY_FIVE) && setEnd)
        {
            setEnd = false;
            end    = &v5;
        }
        if (IsKeyDown (KEY_SIX) && setStart)
        {
            setStart = false;
            start    = &v6;
        }
        if (IsKeyDown (KEY_SIX) && setEnd)
        {
            setEnd = false;
            end    = &v6;
        }

        if (IsKeyDown (KEY_ENTER))
        {
            if (bfs)
            {
                if (!start) continue;

                if (!end)
                {
                    GraphSearchAlgorithms::BreadthFirstSearch (&graph, start);
                    path.clear ();
                }
                else
                {
                    path = GraphSearchAlgorithms::BreadthFirstSearch (
                        &graph
                        , start
                        , end);
                }
            }
            else if (dfs)
            {
                if (!start) continue;

                if (!end)
                {
                    GraphSearchAlgorithms::DepthFirstSearch (&graph, start);
                    path.clear ();
                }
                else
                {
                    path = GraphSearchAlgorithms::DepthFirstSearch (
                        &graph
                        , start
                        , end);
                }
            }
            if (dijkstra)
            {
                if (!start) continue;

                if (!end)
                {
                    GraphSearchAlgorithms::Dijkstra (&graph, start);
                    path.clear ();
                }
                else
                {
                    path = GraphSearchAlgorithms::Dijkstra (&graph, start, end);
                }
            }
        }*/

        start       = grid.GetNode (27);
        start->tint = DARKBLUE;
        end         = grid.GetNode (90);
        end->tint   = ORANGE;

        // Draw.
        BeginDrawing ();

        ClearBackground (RAYWHITE);

        /*graph.DrawPath (path);
        graph.Draw     ();
        DrawInputMap   ();

        if (start)
        {
            DrawText ("START: " , 450 , 300 , 20 , GREEN);
            DrawText (start->label.c_str (), 550, 300, 20, GREEN);
        }
        else
        {
            DrawText ("START: NONE", 450, 300, 20, GREEN);
        }

        if (end)
        {
            DrawText ("END: ", 450, 325, 20, GREEN);
            DrawText (end->label.c_str (), 550, 325, 20, GREEN);
        }
        else
        {
            DrawText ("END: NONE", 450, 325, 20, GREEN);
        }*/

        if (IsKeyDown (KEY_ENTER))
        {
            if (bfs)
            {
                path = GridSearchAlgorithms::BreadthFirstSearch (
                    &grid
                    , start->index
                    , end->index);
            }
            else if (dfs)
            {
                path = GridSearchAlgorithms::DepthFirstSearch (
                    &grid
                    , start->index
                    , end->index);
            }
            else if (dijkstra)
            {
                path = GridSearchAlgorithms::Dijkstra (
                    &grid
                    , start->index
                    , end->index);
            }
            else if (aStar)
            {
                path = GridSearchAlgorithms::AStar (
                    &grid
                    , start->index
                    , end->index
                    , GridSearchAlgorithms::eHeuristic_Euclidean);
            }
            else if (biDirAStar)
            {
                path = GridSearchAlgorithms::BiDirectionalAStar (
                    &grid
                    , start->index
                    , end->index
                    , GridSearchAlgorithms::eHeuristic_Manhattan);
            }
        }
        
        grid.Draw     ();
        grid.DrawPath (path);
        grid.DrawNode (start->index);
        grid.DrawNode (end->index);

        if (dijkstra)        DrawText ("SEARCH: DIJKSTRA", 600, 350, 20, LIME);
        else if (bfs)        DrawText ("SEARCH: BFS", 600, 350, 20, LIME);
        else if (dfs)        DrawText ("SEARCH: DFS", 600, 350, 20, LIME);
        else if (aStar)      DrawText ("SEARCH: A*", 600, 350, 20, LIME);
        else if (biDirAStar) DrawText ("SEARCH: BiDir A*", 600, 350, 20, LIME);
        else                 DrawText ("SEARCH: NONE", 600, 350, 20, LIME);

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}

void DrawInputMap (void)
{
    DrawText (
        "SET START: PRESS 'S' THEN '1', '2', '3', '4', '5' OR '6'."
        , 200
        , 5
        , 20
        , DARKGRAY);
    DrawText (
        "SET END: PRESS 'E' THEN '1', '2', '3', '4', '5' OR '6'."
        , 200
        , 30
        , 20
        , DARKGRAY);
    DrawText ("CLEAR END: PRESS 'R'.", 450, 55, 20, DARKGRAY);
    DrawText ("ENABLE BFS: PRESS 'A'.", 450, 80, 20, DARKGRAY);
    DrawText ("ENABLE DFS: PRESS 'B'.", 450, 105, 20, DARKGRAY);
    DrawText ("ENABLE DIJKSTRA: PRESS 'C'.", 450, 130, 20, DARKGRAY);
    DrawText ("SEARCH: PRESS 'ENTER'.", 450, 155, 20, DARKGRAY);
}