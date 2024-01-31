#include <string>
#include <vector>

#include <iostream>

using namespace std;


vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer(2);
    
    int length = sequence.size();
    int now_sum = 0;
    int iter_front = length - 1;
    
    for (int iter_back = length - 1; iter_back >= 0; )
    {
        while (iter_front >= 0)
        {
            now_sum += sequence[iter_front];
            if (now_sum == k)
            {
                // 제일 앞 찾아서 반환
                while (now_sum == k && iter_front >= 0)
                {
                    answer[0] = iter_front;
                    answer[1] = iter_back;
                    
                    iter_front--;
                    now_sum += sequence[iter_front];    

                    now_sum -= sequence[iter_back];
                    iter_back--;

                }
                return (answer);
            }
            else if (now_sum > k)
            {
                // 현재 iter_back 빼고 앞 가리키게
                now_sum -= sequence[iter_back];
                iter_back--;
                now_sum -= sequence[iter_front];
            }
            else if (now_sum < k)
            {
                // iter_front 한 칸 앞으로
                iter_front--;
            }
        }
    }
    
    
    
    return answer;
}
