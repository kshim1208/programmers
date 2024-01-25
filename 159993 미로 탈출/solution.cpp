#include <string>
#include <vector>

#include <queue>
#include <utility>

#include <iostream>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool visited[100][100];

pair<int, int>  start;
pair<int, int>  goal;
pair<int, int>  lever;


int solution(vector<string> maps) {
    int answer_lever = 0;
    int answer_end = 0;
    
    // 중복 이동 가능 - 하지만 실질적으로는 레버를 당기기 위해 이동하는 것
    // 과제를 2개로 쪼갠다.
        // 레버 당기기 최소 거리 - 출구를 통로 취급
        // 레버에서 출구까지 최소 거리 - 시작점을 통로 취급
    
    // 시작점, 출구, 레버
    int maps_height = maps.size();
    int maps_width = maps[0].length();
    
    for (int iter_y = 0; iter_y < maps_height; iter_y++)
    {
        for (int iter_x = 0; iter_x < maps_width; iter_x++)
        {
            if (maps[iter_y][iter_x] == 'S')
            {
                start = make_pair(iter_x, iter_y);
            }
            else if (maps[iter_y][iter_x] == 'E')
            {
                goal = make_pair(iter_x, iter_y);
            }
            else if (maps[iter_y][iter_x] == 'L')
            {
                lever = make_pair(iter_x, iter_y);
            }
        }
    }
    
    // 2번의 BFS
    
    queue<pair<pair<int, int>, int>>    lever_queue;
    lever_queue.push(make_pair(start, 0));
    
    visited[start.first][start.second] = true;
    
    while (lever_queue.size() > 0)
    {
        int now_x = lever_queue.front().first.first;
        int now_y = lever_queue.front().first.second;
        int now_len = lever_queue.front().second;
        
        lever_queue.pop();
        
        if (lever.first == now_x && lever.second == now_y)
        {
            answer_lever += now_len;
            break ;
        }
        
        for (int iter = 0; iter < 4; iter++)
        {
            int move_x = now_x + dx[iter];
            int move_y = now_y + dy[iter];
            
            // 이동 불가능한 경우
            if (move_x < 0 || move_x == maps_width || move_y < 0 || move_y == maps_height
                || maps[move_y][move_x] == 'X')
            {
                continue;
            }
            
            // 이동 가능한 경우
    
            if (visited[move_x][move_y] == false)
            {
                lever_queue.push(make_pair(make_pair(move_x, move_y), now_len + 1));
                visited[move_x][move_y] = true;
            }
            
        }
    }
    
    if (answer_lever == 0)
        return (-1);
    
    queue<pair<pair<int, int>, int>>    end_queue;
    end_queue.push(make_pair(lever, 0));
    
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            visited[x][y] = false; 
        }
    }
    
    visited[lever.first][lever.second] = true;
    

    while (end_queue.size() > 0)
    {
        int now_x = end_queue.front().first.first;
        int now_y = end_queue.front().first.second;
        int now_len = end_queue.front().second;
        
        end_queue.pop();
        
        if (goal.first == now_x && goal.second == now_y)
        {
            answer_end += now_len;
            break ;
        }
        
        for (int iter = 0; iter < 4; iter++)
        {
            int move_x = now_x + dx[iter];
            int move_y = now_y + dy[iter];
            
            // 이동 불가능한 경우
            if (move_x < 0 || move_x == maps_width || move_y < 0 || move_y == maps_height
                || maps[move_y][move_x] == 'X')
            {
                continue;
            }
            
            // 이동 가능한 경우
            if (visited[move_x][move_y] == false)
            {
                end_queue.push(make_pair(make_pair(move_x, move_y), now_len + 1));
                visited[move_x][move_y] = true;
            }
        }
    }
    
    if (answer_end == 0)
        return (-1);
    
    return (answer_lever + answer_end);
}
