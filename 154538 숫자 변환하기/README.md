## 숫자 변환하기  

### 사용한 접근 방식  
최소 수행 수를 찾아야하니 BFS를 사용하고, 유망하지 않은 노드 탐색 금지 위해 가지치기를 했다.  

### 겪은 문제와 해결 방안  
시간 초과가 발생하여 memoization을 사용하기로 했다. 2와 3의 곱 과정에서 발생하는 중복 노드에 대한 접근을 막기 위해 저장을 수행헀다.  
필요한 만큼의 효율을 보이는 함수를 늦게 찾아서 시행착오를 좀 겪었다.  

1. deque에 순차 저장 후 cpp algorithm의 find 사용하기 - 시간초과
2. set에 저장 후 동일 라이브러리의 binary search 사용하기 - deque보다도 효율이 좋지 않았음. 굉장히 의아함.
3. set에서 제공되는 find 메소드를 사용하기 - 통과.

이유를 찾아본 결과, set의 find 메소드는 컴파일러의 구현에 의존하지만 일반적인 경우 내부적 tree 구조를 활용하는 방식을 사용한다고 한다.  
반면 algorithm library의 binary_search는 iteraotr를 통한 접근으로 탐색을 수행하는데, iterator에 대한 탐색은 결국 iterator의 종류에 그 효율이 의존하게 된다.  
iterator에는 forward access, bidirectional access, random access가 존재하는데, set은 tree 구조이기에 bidirectional access이다.  
그리고 bidirectional access이기에 iterator를 찾아가는 비용이 f(n)만큼 들게 된다.  
set의 find 메소드는 tree 구조의 특성을 이용하는 경우가 많고, set은 많은 경우 red-black tree로 구성되기에 탐색 과정의 효율을 log시간으로 줄일 수 있다고 한다.  
그래서 set의 find 메소드가 alogrithm library를 쓰는 것보다 효율이 좋았던 것이다.  
  
정렬하여 보관하고 이를 사용하는 과제의 경우 set을 잘 쓰면 좋을 것 같았다.  
또한 alogrithm library를 사용하기 전에 우선 container의 method를 사용해보는게 좋을 것 같았다.  
