题目链接：https://leetcode.com/problems/course-schedule-ii/

题目内容：

There are a total of n courses you have to take, labeled from 0 to n-1. Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Note:

- The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
- Read more about how a graph is represented.
- You may assume that there are no duplicate edges in the input prerequisites.

---

这是一道很经典的题：拓扑排序。就是安装一个程序需要dependency的感觉：先要安装dependency，才能安装程序。
拓扑排序就是给你一堆点，每一个点有一些其他的点作为dependency，让你给出一个执行点的顺序，使得所有的点都可以完成。基本一样，但要求不同的话，是问你这样一个顺序能不能
找到。总之是一个有向图里找环的经典题目。有用indegree和DFS两种解法。

indegree解法：

对于图里的每一个点，如果它有dependency的话，就是说有别的点指向它，它的入度（indegree）就加1。有一些没有dependency的点，indegree就是0。那么一个任务就可以从这些indegree为0的点开始运行，具体先运行哪个无所谓，因为大家都没有dependency。把这些indegree的点放在一个queue里，叫做`starters`吧。对于每一个没有dependency的点`x`，如果`x`运行完了，那么那些以`x`为dependency的点就不再需要x了，因为dependency实现了。那么对于indegree，就相当于那些点每一个都少了一个从`x`指向它的edge，那么它的indegree就减1。减的操作做完就有可能indegree就为0了，就可以执行这个点了。所以每做一次减操作，我们都检查一下indegree是不是0，如果是0，就认为它变成了没有dependency的点，就把它放在`starters`里，按照顺序轮到它的话就可以直接执行了。

如果图里面有环的话，那么环里面的点就永远不可能有indegree==0的时候。你就可以看看是不是有些点indegree不是0。如果是，那么有环，想所有点都运行完，这样的顺序是找不到的。如果所有的点都是indegree为0，那么图里没有环，肯定可以按某个顺序完成所有点。

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> graph(n, vector<int>());
        vector<int> indegree(n);
        vector<int> out;
        for (auto x: prerequisites) {
            graph[x[1]].push_back(x[0]);
            indegree[x[0]]++;
        }    
        queue<int> starters;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) starters.push(i);
        }
        while (!starters.empty()) {
            int i = starters.front(); 
            starters.pop();
            out.push_back(i);
            for (int j = 0; j < graph[i].size(); j++) {
                indegree[graph[i][j]]--;
                if (indegree[graph[i][j]] == 0) starters.push(graph[i][j]);
            }
        }
        if (out.size() < n) out.clear();
        return out;
    }
};
```














