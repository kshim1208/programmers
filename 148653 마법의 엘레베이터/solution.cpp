#include <string>
#include <vector>

using namespace std;


int solution(int storey) {
    int answer = 0;

    while (storey != 0)
    {
        // 뒷자리부터 잘라내기
        int target = storey % 10;
        
        if (6 <= target && target <= 9)
        {
            answer += 10 - target;
            storey = storey / 10;
            storey++;
        }
        else if (0 <= target && target <= 4)
        {
            answer += target;
            storey = storey / 10;
        }
        else
        {
            // 다음 숫자를 보고 판단하기
            int tmp = storey / 10;
            tmp = tmp % 10;
            
            if (5 <= tmp && tmp <= 9)
            {
                answer += 10 - target;
                storey = storey / 10;
                storey++;
            }
            else
            {
                answer += target;
                storey = storey / 10;
            }
            
        }

    }
    
    return answer;
}
