//
// Created by raphael on 26/02/19.
//

#include <string>
#include <vector>
#include <iostream>

class Solution {
public:
    bool isMatchP(char s, char p) {
        return s && p && (p == '.' || s == p);
    }

    bool isMatch(std::string s, std::string p) {
        unsigned long sc = 0;
        unsigned long pc = 0;
        char starChar = false;
        char lastStarChar = false;

        if (p.empty()) {
            return s.empty();
        }

        while (true) {
            auto mpc = p.size() - 1;
            auto msc = s.empty() ? 0 : s.size() - 1;

            char schar = (sc > msc || s.empty()) ? false : s[sc];
            char cpchar = pc > mpc ? false : p[pc];
            char pchar = starChar ? starChar : cpchar;

            if (!schar && !pchar) {
                return true;
            }

            if (!starChar && pc < mpc && p[pc + 1] == '*') {
                starChar = p[pc];
                pc += 2;

                continue;
            }

            if (starChar && schar && pchar && isMatch(s.substr(sc), p.substr(pc))) {
                return true;
            } else if (isMatchP(schar, pchar)) {
                sc++;

                if (!starChar) {
                    pc++;
                    lastStarChar = false;
                } else {
                    lastStarChar = pchar;
                }
            } else if (starChar) {
                starChar = false;
            } else if (isMatchP(schar, lastStarChar)) {
                starChar = false;
            } else {
                return false;
            }
        }
    }
};

#define assert(s, p, e) if(solution.isMatch(s, p) != e) { std::cout << #s << " match " #p << " should return " << e << "\n"; } else { std::cout << "ok\n"; }

int main() {
    auto solution = Solution();

    assert("aa", "a", false);
    assert("aaa", "aaaa", false);
    assert("aa", "a*", true);
    assert("aaa", "a*a", true);
    assert("a", "a*a", true);
    assert("ab", ".*", true);
    assert("aab", "c*a*b", true);
    assert("mississippi", "mis*is*ip*.", true);
    assert("ab", ".*c", false);
    assert("cccaaacaccabaab", "a*c*c*b*b*b*b*a*c", false);
    assert("aaa", "ab*a*c*a", true);
    assert("bbbba", ".*a*a", true);
    assert("ab", ".*..", true);
    assert("a", ".*..a", false);
    assert("a", ".*..a*", false);
    assert("", ".*", true);
    assert("bbba", ".*b", false);
    assert("abcdede", "ab.*de", true);
    assert("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s", true);
    assert("bccbbabcaccacbcacaa", ".*b.*c*.*.*.c*a*.c", false);
    assert("abbaaaabaabbcba", "a*.*ba.*c*..a*.a*.", true);

    std::cout << "Done !";
}
