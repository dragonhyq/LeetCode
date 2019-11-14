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
找到。总之是一个有向图里找环的经典题目。Lyft phone screen问了这个题。有用indegree和DFS两种解法。

解法一：indegree

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

解法二：DFS

DFS是每条道都是一条道走到黑。对于每个点建立一个`visited`的值，分三种: `visitied = 0`: 没有访问过，`visited = 1`，正在访问（正在走到黑，还没走完），`visited = 2`，访问完了，所有的道都走到黑了。如果在用DFS在图里面转悠的时候遇到一个`visited == 0`的点，就可以从那个点为岔路的起点往下走，如果遇到一个`visited == 2`的点，就说明那个岔路已经走完了，不用再走了。如果遇到`visited == 1`的点，就说明这是我以前来过的点，就说明图中有环，这样的话DFS就停不下来了，所以检测到环就要主动退出。

如果一个点，它的所有的孩子节点都已经走完了，然后也没有遇到环，那么它自己就走完了，就把`visited`设为2。既然走完了，就可以把它放在一个vector里。就这样，一个一个点都被放进去了。但是放进去的顺序与执行的顺序是反的。你想，如果一个点是终点，没有children，那它立刻就完成了，就进到vector里面去了。但是这些点是通过它的dependency才达到的，它`visited==2`了才能轮着它的dependency。所以那些dependency都要晚完成。所以，那个vector记录的，是反的执行顺序。把vector反过来就是正确的执行顺序了。

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> graph(n, vector<int>());
        vector<int> visited(n, 0);
        vector<int> out;
        for (auto x: prerequisites) {
            graph[x[1]].push_back(x[0]);
        }    
        for (int i = 0; i < n; i++) {
            if (go(i, graph, visited) == false) {
                out.clear();
                break;
            }
        }
        reverse(out.begin(), out.end());
        return out;
    }

    bool go(int i, vector<vector<int>>& graph, vector<int>& visited, vector<int>& out) {
        // returns true if no loop is found
        if (visited[i] == 2) return true;
        if (visited[i] == 1) return false; // loop found
        visited[i] = 1;
        for (int j: graph[i]) {
            if (go(j, graph, visited) == false) return false;
        }
        visited[i] = 2;
        out.push_back(i);
        return true;
    }
};
```
















