#include <string>
#include <vector>

#include <algorithm>

using namespace std;

bool cmp(vector<int> &a, vector<int> &b)
{
    return (a[0] < b[0]);
}

int solution(vector<vector<int>> targets) {
    int answer = 0;
    
    // 정렬 - s가 낮은 순
    sort(targets.begin(), targets.end(), cmp);
    
    // 반복 - 미사일 산출 
    int target_num = targets.size();
    int iter = 0;
    
    int now_end = 100000001;

    while (iter < target_num)
    {
        // 이전 미사일의 e와 현재 미사일의 시작점을 비교
        if (now_end <= targets[iter][0])
        {
            // 현재 미사일보다 이전 미사일의 시작점이 앞이면, 요격 한 발 날려야함
            answer++;
            
            // 새로운 미사일의 now_end 저장됨
            now_end = targets[iter][1];
            
        }
        else
        {
            // 현재 미사일의 종료점보다 이전 미사일의 시작점이 더 늦으면, 같이 부술 수 있는 미사일임
            
            // 만약 현재 종료점이 같이 부술 수 있는 미사일의 종료점보다 크다면, 종료점을 갱신함
            if (now_end > targets[iter][1])
                now_end = targets[iter][1];
        }
        
        iter++;
    }

    // 마지막 처리용 한 발 날림
    answer++;
    
    return answer;
}
