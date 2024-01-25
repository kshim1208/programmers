#include <string>
#include <vector>

#include <queue>
#include <utility>

#include <iostream>

using namespace std;

// number, index
priority_queue<pair<int, int>>  soldier_queue;
priority_queue<pair<int, int>>  invincible_queue;


int solution(int n, int k, vector<int> enemy) {
    int answer = 0;
    
    // 광물 캐기와 비슷하지만, 그리디하게 풀기엔 조건이 복잡한 것 같음.
    // 무적권의 갯수 때문에 예측에 드는 비용이 너무 높음. 그냥 재귀적으로 처리하는게 나을 것 같음.
    // 이전 결과가 이후 결과의 일부인가? 그런 것 같기도 함. 근데 메모이제이션 하긴 힘들지 않나?
    
    // 무적권의 배치 방법이 핵심임.
        // 어떻게 계산을 줄일 수 있을까?
        // 최악을 가정

    // 기본은 DFS 같음
        // 최적화 방안
            // 인원 적은 조합 (인원-인덱스)을 계속 우선순위 큐에 역순으로 추가하면?
        // dfs 안하기로 했음
            // 다 보는게 오히려 비효율적인
    
    // 아이디어 1
        // 1. 두 개의 구조를 만든다. 하나는 병사 사용 큐, 하나는 무적권 사용 큐
        // 2. 병사로 죽일 수 있는 동안에는 우선순위 큐에 추가한다.
        // 3. 병사로 죽일 수 없을 때, 무적권이 남아있다면, 무적권을 현재 적 혹은 병사가 지금까지 죽였던 적의 수가 가장 많은 병사큐의 top 중 더 큰 쪽(top) 에 사용한다. (병사 큐에서 무적권 큐로 옮김)
        // 3-1. 만약 병사 큐의 최대 값보다 현재 적이 더 크다면, 무적권을 그냥 쓴다.
        // 3-2. 만약 병사 큐의 최대 값보다 현재 적이 더 작다면, 병사 큐의 최대 값에 무적권을 쓰고 현재 적을 병사 큐에 넣은 뒤, 병사 잔량을 조절한다.
        // 4. 병사로 죽일 수 없을 때, 무적권이 없다면, 게임이 종료된다.
        // 5. 현재 라운드를 반환한다.
    
    int soldier = n;
    int invincible = k;
    
    for (int iter = 0; iter < enemy.size(); iter++)
    {
        // 현재 병사 수에 대해 적의 수가 같거나 작음
        if (enemy[iter] <= soldier)
        {
            // 병사가 죽였음을 저장함
            soldier_queue.push(make_pair(enemy[iter], iter));
            soldier -= enemy[iter];
        }
        else
        {
            // 현재 병사 수보다 적의 수가 많음
            if (invincible != 0)
            {
                // 무적권이 남아있음
                if (soldier_queue.size() == 0 || soldier_queue.top().first <= enemy[iter])
                {
                    // 병사 큐 중 가장 값 높은 값보다 크거나 같음 - 무적권 쓰기
                    invincible_queue.push(make_pair(enemy[iter], iter));
                    
                    

                }
                else
                {
                    // 병사 큐에서 가장 큰 값이 현재 적보다 큼 -> 무적권을 예전에 쓴 것으로 처리하기
                    int top_soldier = soldier_queue.top().first;
                    int top_index = soldier_queue.top().second;
                    
                    soldier_queue.pop();
                    invincible_queue.push(make_pair(top_soldier, top_index));
                    soldier_queue.push(make_pair(enemy[iter], iter));
                    
                    // 병사 잔량 조정
                    soldier += top_soldier - enemy[iter];
                    
                }
                // 어쨌든 무적권은 씀
                invincible--;
            }
            else
            {
                return (answer);
            }
        }
        
        answer++;
        
    }
    
    return (enemy.size());
}



