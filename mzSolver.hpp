#ifndef MZ_SOLVER
#define MZ_SOLVER
#include "MazeSolver.hpp"
#include <vector>
#include "MazeSolution.hpp"
#include "Maze.hpp"

class mzSolver: public MazeSolver
{
    private:
        int height;
        int width;
        std::vector<std::vector<int>> mzCpy;
        bool inBounds(int x, int y)
        {
            if(x >= 0 && x < width && y >= 0 && y < height)
            {
                return true;
            }
            return false;
        }
        std::vector<Direction> findPath(const Maze & maze, int x, int y)
        {
            std::vector<Direction> paths;
            if(inBounds(x + 1, y) && mzCpy[y][x + 1] == 1 && !maze.wallExists(x, y, Direction::right))
            {
                paths.push_back(Direction::right);
            }
            if(inBounds(x - 1, y) && mzCpy[y][x-1] == 1 && !maze.wallExists(x, y, Direction::left))
            {
                paths.push_back(Direction::left);
            }
            if(inBounds(x , y + 1) && mzCpy[y + 1][x] && !maze.wallExists(x, y, Direction::down))
            {
                paths.push_back(Direction::down);
            }
            if(inBounds(x, y - 1) && mzCpy[y - 1][x] && !maze.wallExists(x, y, Direction::up))
            {
                paths.push_back(Direction::up);
            }
            return paths;
           
            

        }
        void solve(const Maze & maze, MazeSolution & mzSol)
        {
            std::pair<int, int> cell  = mzSol.getCurrentCell();
            int x = cell.first;
            int y = cell.second;
            std::vector<Direction> paths;
            mzCpy[y][x] = 0;
            do
            {
                paths = findPath(maze, x, y);
                if(mzSol.isComplete())  {break;}
                if(paths.empty())   {mzSol.backUp(); break;}
                mzSol.extend(paths[0]);
                solve(maze, mzSol);
            }while(true);
        }
    public:
        mzSolver(){}
        void solveMaze(const Maze & maze, MazeSolution & mazeSolution) override
        {
            height = maze.getHeight();
            width = maze.getWidth();
            mzCpy = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
            solve(maze, mazeSolution);
        }



};
#endif
