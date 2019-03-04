#include <string>
#include <iostream>

#define TRIM_CHARS " "

class Solution {
public:
    std::string& ltrim(std::string& str, const std::string& chars = TRIM_CHARS){
        str.erase(0, str.find_first_not_of(chars));
        return str;
    }

    std::string& rtrim(std::string& str, const std::string& chars = TRIM_CHARS){
        str.erase(str.find_last_not_of(chars) + 1);
        return str;
    }

    std::string& trim(std::string& str, const std::string& chars = TRIM_CHARS){
        return ltrim(rtrim(str, chars), chars);
    }

    bool isNumber(std::string s) {
        s = trim(s);

        if(s.empty()) {
            return false;
        }

        bool hadN = false;
        bool hadE = false;
        bool hadDot = false;
        bool hadSign = false;

        char lastC = false;

        for (auto c : s) {
            if (c == ' ') {
                return false;
            } else if (c == '-' || c == '+') {
                if (hadSign || hadN || hadDot) {
                    return false;
                }

                hadSign = true;
            } else if (std::isdigit(c)) {
                hadN = true;
            } else if (c == '.') {
                if (hadDot || hadE) {
                    return false;
                }

                hadDot = true;
            } else if (c == 'e') {
                if (hadE || !hadN) {
                    return false;
                }

                hadN = false;
                hadSign = false;
                hadDot = false;
                hadE = true;
            } else {
                return false;
            }

            lastC = c;
        }

        if (lastC == 'e' || lastC == '-' || lastC == '+' || (!hadN && lastC == '.')) {
            return false;
        }

        return true;
    }
};

#define assert(s, e) if(solution.isNumber(s) != e) { std::cout << #s << " should return " << e << "\n"; } else { std::cout << "ok\n"; }

int main() {
    auto solution = Solution();

    assert("0", true);
    assert("", false);
    assert(" ", false);
    assert(".", false);
    assert(" 0.1 ", true);
    assert("abc", false);
    assert("1 a", false);
    assert("2e10", true);
    assert(" -90e3   ", true);
    assert(" 1e", false);
    assert("e3", false);
    assert(" 6e-1", true);
    assert(" 99e2.5 ", false);
    assert("53.5e93", true);
    assert(" --6 ", false);
    assert("-+3", false);
    assert("95a54e53", false);
    assert("3.", true);
    assert(".-4", false);
    assert("+.8", true);

    std::cout << "Done !";
}
