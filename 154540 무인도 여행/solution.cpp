#include <string>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool    visited[100][100];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int maps_width;
int maps_height;

int recursive(int iter_x, int iter_y, vector<string> &maps, int &value)
{
    // recursion 종료
    if (visited[iter_x][iter_y] == true)
        return (1);
    visited[iter_x][iter_y] = true;
    
    value += maps[iter_y][iter_x] -'0';
    
    for (int iter = 0; iter < 4; iter++)
    {
        int move_x = iter_x + dx[iter];
        int move_y = iter_y + dy[iter];
        
        if (visited[move_x][move_y] == true || move_x < 0 || move_x == maps_width || move_y < 0 || move_y == maps_height
            || maps[move_y][move_x] == 'X')
            continue ;
        
        recursive(move_x, move_y, maps, value);
    }
    
    return (0);
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
        
    maps_width = maps[0].length();
    maps_height = maps.size();
    
    // visited한 적 없는 땅에 올 때마다 함수 수행하여 총합 저장
    for (int iter_x = 0; iter_x < maps_width; iter_x++)
    {
        for (int iter_y = 0; iter_y < maps_height; iter_y++)
        {
            if (visited[iter_x][iter_y] == false)
            {
                if (maps[iter_y][iter_x] == 'X')
                {
                    visited[iter_x][iter_y] = true;
                }
                else
                {
                    // '함수'
                    int     value = 0;
                    recursive(iter_x, iter_y, maps, value);
                    
                    answer.push_back(value);
                }
                
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    
    // '함수'
        // 한 지점에서 시작하여 주변에 있는 모든 곳을 탐색해야하고, 중복되면 안됨.
        // 백트래킹?
    
    if (answer.size() == 0)
        answer.push_back(-1);
    
    return answer;
}

