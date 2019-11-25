Link: https://leetcode.com/problems/word-ladder/

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

Note:

- Return 0 if there is no such transformation sequence.
- All words have the same length.
- All words contain only lowercase alphabetic characters.
- You may assume no duplicates in the word list.
- You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:\
beginWord = "hit",\
endWord = "cog",\
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog", return its length 5.

Example 2:

Input:\
beginWord = "hit"\
endWord = "cog"\
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

---
I could not figure out how to solve this problem. Took idea from the web. BFS since we want the shortest path. I am not completely following what is going on, especially why we need to `erase()` the word once we find it in `wordList`. I will come back.

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;
        queue<string> q;
        q.push(beginWord);
        int step = 1;
        while (q.size()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                string word = q.front();
                q.pop();
                if (word == endWord) return step;
                for (int k = 0; k < word.size(); k++) {
                    char c = word[k];
                    for (char x = 'a'; x <= 'z'; x++) {
                        word[k] = x;
                        if (x != c && wordSet.count(word)) {
                            q.push(word);
                            wordSet.erase(word);
                        }
                    }
                    word[k] = c; // restore the original character
                }
            }
            step++;
        }
        return 0;
    }
};
``` 