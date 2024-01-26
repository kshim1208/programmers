#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>

using namespace std;

int     hhmmToInt(const std::string& hhmm)
{
    std::string tmp;
    int         time;
    
    tmp[0] = hhmm[0];
    tmp[1] = hhmm[1];
    time = stoi(tmp) * 60;
    tmp[0] = hhmm[3];
    tmp[1] = hhmm[4];
    time += stoi(tmp);
    return (time);
}

bool    hhmmCompare(const vector<string>&  v1, const vector<string>& v2)
{
    return (hhmmToInt(v1[1]) > hhmmToInt(v2[1]));
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    deque<vector<string>>   stopstack;
    deque<int>      lefttime;
    deque<vector<string>>   working;
    
    int     working_end;
    int     working_time;
    int     next_start;
    int     now_time;
    
    // 내림차순 - vector push_back
    sort(plans.begin(), plans.end(), hhmmCompare);
    working.push_back(plans[plans.size() - 1]);
    plans.pop_back();
    now_time = hhmmToInt(working[0][1]);
    working_time = stoi(working[0][2]);
    while (working.size() != 0)
    {
        // 현재 작업의 종료 시간과 다음 새 과제 시작 시간 비교
        working_end = now_time + working_time;
        if (plans.size() == 0)
            next_start = -1;
        else
            next_start = hhmmToInt(plans[plans.size() - 1][1]);
        if (next_start != -1 && working_end >= next_start)
        {
            // 1. 새 과제 시작할 시간이 된 경우
            if (working_end == next_start)
            {
                answer.push_back(working[0][0]);
                working.pop_back();
            }
            else
            {
                stopstack.push_back(working[0]);
                lefttime.push_back(working_end - next_start);
                working.pop_back();
            }
            working.push_back(plans[plans.size() - 1]);
            plans.pop_back();
            now_time = hhmmToInt(working[0][1]);
            working_time = stoi(working[0][2]);
        }
        else
        {
            // 2. 새 과제 시작할 시간이 안된 경우, 또는 새 과제가 없는 경우
            answer.push_back(working[0][0]);
            working.pop_back();
            if (stopstack.size() != 0)
            {
                working.push_back(stopstack[stopstack.size() - 1]);
                stopstack.pop_back();
                now_time = working_end;
                working_time = lefttime[lefttime.size() - 1];
                lefttime.pop_back();
            }
            else if (plans.size() != 0)
            {
                working.push_back(plans[plans.size() - 1]);
                plans.pop_back();
                now_time = hhmmToInt(working[0][1]);
                working_time = stoi(working[0][2]);
            }
        }

    }
    return answer;
}
