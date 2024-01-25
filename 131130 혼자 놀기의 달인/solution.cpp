#include <string>
#include <vector>

#include <algorithm>

#include <iostream>

using namespace std;

int solution(vector<int> cards) {
    int answer = 0;
    
    // index + 1 = 상자 번호, cards[index] - index + 1번 상자의 카드 번호
    // 꼬리 물면 종료된다. 그룹이 존재한다.
    
    // 모든 그룹을 찾고, 각 그룹 중 가장 큰 값 2개를 곱한다.
    // 한 그룹을 찾을 때마다 기존 상자에서 해당 그룹 제거함.
    
    vector<int> groups;
    int box_index = 0;
    
    while (box_index < cards.size())
    {
        // 상자 열기   
        if (cards[box_index] != 0)
        {
            // 상자 안에 다른 상자 열 수 있는 카드 있을 경우
            int box_num = 1;
            int chain_index = cards[box_index] - 1;
            
            // 열린 상자 처분
            cards[box_index] = 0;
            
            while (cards[chain_index] != 0)
            {
                box_num++;
                // 상자 연쇄 시작
                int tmp_index = chain_index;
                chain_index = cards[chain_index] - 1;
                cards[tmp_index] = 0;
            }
            
            groups.push_back(box_num);
            
        }
        box_index++;
    }
    if (groups.size() == 1)
        return (0);
    
    sort(groups.begin(), groups.end());
    
    return (*(groups.end() - 1) * *(groups.end() - 2)) ;
}
