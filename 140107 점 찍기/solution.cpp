#include <string>
#include <vector>

#include <cmath>

#include <iostream>

using namespace std;

long long solution(int k, int d) {
    long long answer = 0;
    
    // 최악의 경우에 pow-sqrt 연산 수가 늘어남 - pow-sqrt로 연산하지 말고, 가능한 범위를 지정한 후 그 안에 있는 점의 수를 카운팅?
    // 함수 유도 가능. 그 함수의 x 값에 대해 y 값 숫자를 세는게 빠를지도?
    
    
    // 처음에 float으로 하고 있었는데, d가 100만일 경우 100만의 2승이 float을 넘어가고 있었다.
    double   height_pow = pow(d, 2);
    
    for (int iter = 0; iter * k <= d; iter++)
    {
        // 1. 부채꼴
            // 부채꼴의 높이를 구하면 시간 초과 발생한다.
            // 다른 방법이 있을까?
//         float max = height_pow - pow(iter * k, 2);
        
//         int cnt = 0;
        
//         while(pow(cnt * k, 2) <= max)
//         {
//             answer++;
//             cnt++;
//         }
        
        // 2. 점을 더하는 방식을 변경해봄
//         float max = sqrt(height_pow - pow(iter * k, 2));
        
//         answer += (max / k) + 1;
        
        
        
        // 3. 시간 초과는 안 발생함. 접근 방식의 문제? 아니면 answer가 long long이던데 일부 값에 문제가 있나?
        int max = static_cast<int>(sqrt(height_pow - pow(iter * k, 2)));
        
        answer += (max / k) + 1;
        
        
    }
    return answer;
}
