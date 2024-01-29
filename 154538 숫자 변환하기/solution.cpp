#include <string>
#include <vector>
#include <queue>
#include <set>
#include <deque>
#include <algorithm>
#include <utility>

#include <iostream>

using namespace std;

int solution(int x, int y, int n) {
    int answer = 0;
    
    // 최단거리에 가까우니 BFS, 추가로 특정 노드는 방문하지 않아도 되니 가지치기 가능할 것 같음 - 목표치보다 값이 커지는 경우는 안감
        // 더 줄일 방법이 있을까?
            // 계산 했던 값은 이미 큐에 올라있으니 제외한다 - 많이 줄여줄 것 같음
                // 정렬되게 넣고 이진 탐색이 더 빠른가?
                // set에 대한 binary_search보단 deque에 넣고 일반 탐색이 빠른 것 같다.
                // !!!!! set에서 제공되는 find 메소드가 algorith library의 binary search보다 빠르다!
                    // 적용하니까 바로 성공했음
        // 실패하는 케이스는 뭘까? 특수한 경우 같은데?
        
    queue<pair<int, int>>   calc_queue;
    set<int>                already_set;
    
    
    calc_queue.push(make_pair(x, 0));

    while(calc_queue.size() > 0)
    {   
        int     value = calc_queue.front().first;
        int     step = calc_queue.front().second;
        
        calc_queue.pop();
        
        if (value > y)
            continue ;
        
        if (value == y)
            return (step);
        
        if (value < y)
        {
            if (already_set.find(value) == already_set.end())
            {
                calc_queue.push(make_pair(value + n, step + 1));
                calc_queue.push(make_pair(value * 2, step + 1));
                calc_queue.push(make_pair(value * 3, step + 1));
                already_set.insert(value);
            }
            else
                continue ;
        }
        
    }
    
    return (-1);
}
