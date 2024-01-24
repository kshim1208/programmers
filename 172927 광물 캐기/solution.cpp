#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    
    int     pick_num = picks[0] + picks[1] + picks[2];
    int     chunks = ceil(minerals.size() / 5.0);
    
    if (chunks > pick_num)
    {
        chunks = pick_num;
    }
    
    vector<int>     cost(chunks);
    vector<bool>    assigned(chunks);
    
    // mineral을 순회하는 알고리즘
    
    // mineral을 5개 단위로 검사한다.
    // 모든 조합을 구하고 싶지는 않다.
    // 피로도 단위도 5로 증가한다
        // 묶음 별로 피로도 소모 큰 광물 있으면 가능한 한 좋은 곡괭이 쓰는게 나음
    
    // mineral 길이 측정해서 vector들 생성
    
    // 곡괭이 수만큼만 chunk 저장
    for (int i = 0; i < chunks; i++)
    {
        for (int j = 0; j < 5 && i * 5 + j < minerals.size(); j++)
        {
            if (minerals[(i * 5) + j] == "diamond")
                cost[i] += 25;
            else if (minerals[(i * 5) + j] == "iron")
                cost[i] += 5;
            else
                cost[i] += 1;
        }
    }
    
    // cost 높을 수록 더 좋은 곡괭이 배정.
    // 배정된 곳에는 더 넣지 않음.
    // 다이아 배정
    for (int i = 0; i < picks[0]; i++)
    {
        int now_index = -1;
        for (int j = 0, now_cost = 0; j < chunks; j++)
        {
            if (now_cost < cost[j] && assigned[j] == false)
            {
                now_cost = cost[j];
                now_index = j;
            }
        }
        if (now_index != -1)
        {
            for (int k = 0; k < 5 && now_index * 5 + k < minerals.size(); k++)
            {
                answer += 1;
            }
            assigned[now_index] = true;
        }
    }
    
    // 철 배정
    for (int i = 0; i < picks[1]; i++)
    {
        int now_index = -1;
        for (int j = 0, now_cost = 0; j < chunks; j++)
        {
            if (now_cost < cost[j] && assigned[j] == false)
            {
                now_cost = cost[j];
                now_index = j;
            }
        }
        if (now_index != -1)
        {
            for (int k = 0; k < 5 && now_index * 5 + k < minerals.size(); k++)
            {
                if (minerals[now_index * 5 + k] == "diamond")
                    answer += 5;
                else if (minerals[now_index * 5 + k] == "iron")
                    answer++;
                else
                    answer++;
            }
            assigned[now_index] = true;
        }
    }
    // 돌 배정
    for (int i = 0; i < picks[2]; i++)
    {
        int now_index = -1;
        for (int j = 0, now_cost = 0; j < chunks; j++)
        {
            if (now_cost < cost[j] && assigned[j] == false)
            {
                now_cost = cost[j];
                now_index = j;
            }
        }
        if (now_index != -1)
        {
            for (int k = 0; k < 5 && now_index * 5 + k < minerals.size(); k++)
            {
                if (minerals[now_index * 5 + k] == "diamond")
                    answer += 25;
                else if (minerals[now_index * 5 + k] == "iron")
                    answer += 5;
                else
                    answer++; 
            }
            assigned[now_index] = true;
        }
    }
    
    return answer;
}
