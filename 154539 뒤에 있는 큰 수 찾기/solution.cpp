#include <string>
#include <vector>
#include <stack>

using namespace std;

//  단순한 그리디로 하면 메커니즘 상 문제는 적다.
    // 하지만 시간 초과 발생 -> 시간 복잡도 문제임

    // 제한 사항에서 입력 데이터가 클 경우. 시간 복잡도 낮출 방법을 공부해야 함
        // n*n을 logn*n으로 만드는 대표적인 방식 - heap 자료구조 (heap, 우선순위 큐 등 - 둘 다 트리 구조를 가진다고 함)
        // heap의 구조상 특징 공부하기

        // stack을 쓰면 어떤지?

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    
    // 단순 이중 반복문 - 시간 복잡도가 크다
//     for (int iter = 0; iter < numbers.size() - 1; iter++)
//     {
//         int target = numbers[iter];
//         bool success   = false;    
    
//         for (int search = iter + 1; search < numbers.size(); search++)
//         {
//             if (numbers[search] > target)
//             {
//                 answer.push_back(numbers[search]);
//                 success = true; 
//                 break ;
//             }
//         }
//         if (success == false)
//             answer.push_back(-1);
//     }
    
//     answer.push_back(-1);
    
    // 후방부터 전방을 향해 값 넣기 위해 미리 vector 크기를 설정한다
        // vector의 생성자에 크기 지정하는 것도 문제 없을 것 같음
    answer.resize(numbers.size());
    stack<int> big_numbers;
    
    for(int iter = numbers.size() - 1; iter >= 0; iter--)
    {
        while(1)
        {
            // 더 큰 수가 없음
            if (big_numbers.empty() == true)
            {
                answer[iter] = -1;
                break;
            }
            // 더 큰 수가 스택의 탑에 존재함 - 최근에 들어온 수 - 점점 뒤에 있는 수를 보게 된다.
            if (big_numbers.top() > numbers[iter])
            {
                answer[iter] = big_numbers.top();
                break;
            }
        
            // 그보다 뒤에 있는 수를 본다.
            big_numbers.pop();
        }
        // 다음 반복에서 현재 숫자를 판단하기 위해 스택에 추가한다.
        big_numbers.push(numbers[iter]);
    }

    return answer;
}
