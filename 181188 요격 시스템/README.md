요격 시스템
=========

### 사용 접근방식
매 미사일마다 가장 효율적인 요격체 (요격 미사일) 발사 여부를 그때그때 판단한다.  
따라서 매 수행마다 그 순간에 가장 최적인 방법을 찾는 그리디 알고리즘이라 볼 수 있을 것이다.  


### 문제 겪은 부분
접근 방식은 문제가 없는 것 같은데 문제가 통과되지 않았다.  

동작을 재검토한 결과, 초반에 sort 하는 부분에서 comparator를 직접 만들어 사용할 때, vector의 원소가 아닌 begin iterator를 비교하고 있었다.  
그 결과 정렬이 이루어지지 않아 동작이 비정상적이었던 것이다.  

