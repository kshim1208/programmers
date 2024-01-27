#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>

#include <iostream>

using namespace std;

int solution(vector<vector<string>> book_time) {
    int answer = 0;
    
    deque<vector<int>> book_time_list;
    
    // 방을 만들 때마다 빠른 시간 순으로 넣을 수 있는 방을 계속해서 찾는다?
    
    for (int iter = 0; iter < book_time.size(); iter++ )
    {
        stringstream    ss;
        int             hour1, hour2, minute1, minute2;
        char            colon1, colon2;
        vector<int>     book_time_node;
        
        ss << book_time[iter][0];
        ss >> hour1 >> colon1 >> minute1;
        book_time_node.push_back(hour1 * 60 + minute1);
        
        ss.str("");
        ss.clear();
        
        ss << book_time[iter][1];
        ss >> hour2 >> colon2 >> minute2;
        book_time_node.push_back(hour2 * 60 + minute2);
        
        cout << book_time_node[0] << ", " << book_time_node[1] << endl;
        
        book_time_list.push_back(book_time_node);
        

    }
    
    sort(book_time_list.begin(), book_time_list.end());
    
    // 정렬 후 넣는 알고리즘 - 그리디하게?
    
    while (book_time_list.size() > 0)
    {
        int     end_time;
        // int     begin_time;
        
        // begin_time = list.front().first;
        end_time = (book_time_list.front())[1];
        
        book_time_list.pop_front();
        
        answer++;
        
        deque<vector<int>>::iterator list_iter = book_time_list.begin();
        
        while (list_iter != book_time_list.end())
        {
            // 조건문으로 노드 삭제하는 경우 (erase하는 경우) 에는 iter를 옮기지 않음
            if ((*list_iter)[0] >= end_time + 10)
            {
                // 추가 입실 가능
                end_time = (*list_iter)[1];
                
                // erase - erase의 사용법 제대로 기억하기 -> erase의 결과가 iterator로 나오니 받아서 사용한다.
                // 그냥 자동으로 iterator가 정상 설정되는게 아니다.
                list_iter = book_time_list.erase(list_iter);
            }
            else
            {
                list_iter++;
            }
        }
        
    }
    
    return answer;
}
