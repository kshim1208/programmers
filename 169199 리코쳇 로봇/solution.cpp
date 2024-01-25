#include <string>
#include <vector>

#include <utility>
#include <queue>

#include <iostream>

using namespace std;
    
int board_width;
int board_height;

pair<int, int>  start;
pair<int, int>  goal;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool visited[100][100];

int solution(vector<string> board) {
    int answer = 0;
    
    // 최단 거리 찾기
    // 4방향 중 갈 수 있는 방향으로 접근하는 BFS 쓰면 될 것 같음.
    // BFS는 넓이 우선 탐색이니 가장 가까운 거리 찾기에 좋을 것 같음
    
    // 보드 관리 방식
        // 실질적으로 접근하지 않는 좌표도 있음 - 장애물이 있는 좌표처럼
        // 동적으로 보드에 이력을 늘려나가는게 좋을 것 같음
        // 근데 동적으로 늘리면 '탐색'에 시간이 걸림
        // 그렇다면 차라리 전체 보드를 vector화해서 메모리를 소모하고 접근 속도를 높이는게 낫지 않을까? - 공간 복잡도와 시간 복잡도의 타협
    
    // 전체 보드를 저장해보기로 했음. 각 보드의 메모리 크기가 그렇게 크지 않을 것으로 판단됨.
    
//     vector<vector<pair<string, vector<int>>>>     step_board;
    
//     for (int board_iter = 0; board_iter < board.size(); board_iter++)
//     {
//         int board_elements = board[board_iter].length;
//         vector<pair<string, vector<int>>>     plate;
        
//         for (int string_iter = 0; string_iter < board_elements; string_iter++)
//         {
//             plate.push_back(make_pair(board[board_iter][string_iter], ));
            
//         }
        
//     }
    
    // !!!!! 다시 고민해본 결과, 전체 보드를 저장하지 않고 '도달할 수 없음'을 판단할 방법이 있나 확인해보는게 나을 것 같았음
        // 저장은 필요한데, 왔던 곳 또 오지 않는게 나으니 방문 여부만 저장하는게 맞는 것 같음
    
    board_width = board[0].length();
    board_height = board.size();
    
    for (int board_iter = 0; board_iter < board_height; board_iter++)
    {
        for (int string_iter = 0; string_iter < board_width; string_iter++)
        {
            if (board[board_iter][string_iter] == 'R')
            {
                start = make_pair(string_iter, board_iter);
            }
            else if (board[board_iter][string_iter] == 'G')
            {
                goal = make_pair(string_iter, board_iter);
            }
        }
    }
    
    // BFS 작동 원리
        // 각 하위 노드에 답안이 있는지 확인한 후에, 다시 각 하위 노드의 하위 노드를 탐색함.
        // 이 문제는 4방향을 탐색하므로 처음에는 경우가 4개, 그 다음에는 16개, 그 다음에는 64개로 늘어날 것 같음 - 실제로는 가지 못하는 방향도 있어서 더 적어짐
        // 고정 배열보단 변동 가능한 queue나 list가 나을 것 같음
    
        // 또한 재귀 대신 queue를 쓸 것으로 생각됨. 계속 파고 들어가는게 아니라, 경우를 늘려나갈 듯?
    
        // 1. 현재 위치가 답안인지 확인함.
        // 2. 4방향으로 이동하는 경우를 queue에 추가함 (1-2를 확인-추가 함수라 명명)
        // 3. queue를 검사하여 각 경우에 대해 확인-추가 함수를 다시 수행함
        // 4. 반복할 때마다 현재 깊이를 높여나감.
        // 5. 답안이 처음으로 나오면, 현재 깊이를 반환하여 함수 종료
    
        // ????? 이 문제의 경우 특정 지점에 방문한 이력을 저장하지 않고 있다.
            // 그러면 -1을 어떻게 알 수 있을까? 저장하는게 맞지 않나?
            // 이력 저장하는게 맞다. 나중에 다시 같은 곳에 온다는 건, 이미 BFS한 곳에 다시 온다는 것이니 불가능해야한다.
    

    queue<pair<pair<int, int>, int>>    queue;
    
    queue.push(make_pair(start, 0));
    visited[start.first][start.second] = true;
    
    while (queue.size() != 0)
    {
        // 현재 좌표와 깊이 추출
        int now_x = queue.front().first.first;
        int now_y = queue.front().first.second;
        int now_len = queue.front().second;
        
        queue.pop();
        
        // 현재 위치가 G인지 확인
        if (goal.first == now_x && goal.second == now_y)
        {
            return (now_len);
        }
        
        // 현재 위치에서 나아갈 수 있는 방향 탐색
            // 각 방향으로 1씩 증가하며 멈추는 조건 탐색
            // 멈출 경우, visited하지 않은 곳이라면 queue에 추가
        
        for (int iter = 0; iter < 4; iter++)
        {
            
            int move_x = now_x + dx[iter];
            int move_y = now_y + dy[iter];
            
            // 현재 위치에서 이동 가능한지
            if (move_x < 0 || move_x == board_width || move_y < 0 || move_y == board_height
                || board[move_y][move_x] == 'D')
            {
                // 각 이동 방향에서 막힌 경우 - 각 방향 당 한 조건임
                    // 한 방향에서 이동을 못하니 다음 iter로 넘어감 - 다른 방향 시도
                continue ;
            }
        
            // 이 방향으로 이동이 가능한 경우
            
            // 반복해서 움직이면서 '닿는지' 확인
            
            while (1)
            {
                move_x += dx[iter];
                move_y += dy[iter];
                
                if (move_x < 0 || move_x == board_width || move_y < 0 || move_y == board_height
                    || board[move_y][move_x] == 'D')
                {
                    // 이동 도중에 막힌 경우 - 이동은 했음
                    // 방문한 적 없으면 추가
                    move_x -= dx[iter];
                    move_y -= dy[iter];
                    
                    if (visited[move_x][move_y] == false)
                    {
                        queue.push(make_pair(make_pair(move_x, move_y), now_len + 1));
                        visited[move_x][move_y] = true;
                    }   
                    break ;
                }
            }
            
        }
        
    }
    
    if (answer == 0)
        return (-1);
    return answer;
}
