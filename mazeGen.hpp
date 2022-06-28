#ifndef MAZE_GEN
#define MAZE_GEN
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>

class MazeGen: public MazeGenerator
{

    private:
        std::random_device device;
        std::default_random_engine engine{device()};
        std::vector<std::vector<int>> mzCpy;
        int height; 
        int width;

        std::vector<Direction> findAdj(int x, int y)
        {
            std::vector<Direction> adj;
            for(int dx = (x > 0 ? -1 : 0); dx <= ( x < (height- 1) ? 1 : 0); ++dx)
            {
                for (int dy = (y > 0 ? -1 : 0); dy <= (y < (width- 1) ? 1: 0); ++dy)
                {
                    if(dx != 0 || dy != 0)
                    {
                        if(dx == -1 && dy == 0 && mzCpy[x + dx][y + dy] == 1)
                        {
                            adj.push_back(Direction::up);
                        } 
                        if(dx == 1 && dy == 0 && mzCpy[x + dx][y + dy] == 1)
                        {
                            adj.push_back(Direction::down);
                        }
                        if(dx == 0  && dy == -1  && mzCpy[x + dx][y + dy] == 1)
                        {
                            adj.push_back(Direction::left);
                        }
                        if(dx == 0  && dy == 1 && mzCpy[x + dx][y + dy] == 1)
                        {
                            adj.push_back(Direction::right);
                        }
                    }
                }
            }
            return adj;
        }
        void  mazeAlgo(int x, int y, Maze & mz)
        {
            mzCpy[x][y] = 0;
            std::vector<Direction> adj;
            do
            {
                adj = findAdj(x, y);
                if(adj.empty()) {break;}
                std::uniform_int_distribution<int> dist(0, adj.size() - 1);
                int randAdj = dist(engine);
                mz.removeWall(y, x, adj[randAdj]);
                switch (adj[randAdj])
                {
                    case Direction::up:
                        mazeAlgo(x - 1, y, mz);
                        break;
                    case Direction::right:
                        mazeAlgo(x, y + 1, mz);
                        break;
                    case Direction::down:
                        mazeAlgo(x + 1, y, mz);
                        break;
                    case Direction::left:
                        mazeAlgo(x, y - 1, mz);
                        break;
                    default:
                        break;                 
               }
            }while(true); 
        }

    public:
        MazeGen(){}
        void generateMaze(Maze & maze) override
        {
            height = maze.getHeight();
            width = maze.getWidth();
            maze.addAllWalls();
            mzCpy = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
            mazeAlgo(0, 0, maze);

        }



};
#endif
