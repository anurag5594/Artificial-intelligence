#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

/*
 Backward Chaining Algorithm
 ---------------------------
 - Start with the GOAL we want to prove.
 - See if the goal is already in the known facts.
 - Otherwise, look for rules whose conclusion matches the goal.
 - For each such rule, recursively try to prove all of its conditions.
 - If all conditions of some rule are proved, we can conclude the goal.
*/

// Rule structure: IF conditions THEN conclusion
struct Rule {
    vector<string> conditions;
    string conclusion;
};

// Recursive function to prove a goal
bool backwardChaining(const string &goal,
                      const vector<Rule> &rules,
                      const set<string> &facts,
                      set<string> &visited)
{
    // If goal is already known
    if (facts.find(goal) != facts.end()) {
        cout << "Goal \"" << goal << "\" is already a known fact.\n";
        return true;
    }

    // To prevent infinite loops in case of cycles
    if (visited.find(goal) != visited.end()) {
        return false;
    }
    visited.insert(goal);

    // Try to find a rule that concludes the goal
    for (const auto &rule : rules) {
        if (rule.conclusion == goal) {
            cout << "To prove \"" << goal << "\", need to prove: ";
            for (size_t i = 0; i < rule.conditions.size(); ++i) {
                cout << rule.conditions[i];
                if (i < rule.conditions.size() - 1) cout << ", ";
            }
            cout << "\n";

            bool allProved = true;
            for (const auto &cond : rule.conditions) {
                if (!backwardChaining(cond, rules, facts, visited)) {
                    allProved = false;
                    break;
                }
            }

            if (allProved) {
                cout << "Hence, \"" << goal << "\" is proved by rule.\n";
                return true;
            }
        }
    }

    // No rule can prove the goal
    cout << "Cannot prove \"" << goal << "\".\n";
    return false;
}

int main() {
    // Knowledge base: rules
    vector<Rule> rules = {
        { {"A", "B"}, "C" },      // IF A AND B THEN C
        { {"C"}, "D" },          // IF C THEN D
        { {"D", "E"}, "F" },     // IF D AND E THEN F
        { {"F"}, "G" }           // IF F THEN G
    };

    // Known facts
    set<string> facts = {"A", "B", "E"};

    // Goal to prove
    string goal = "G";

    cout << "=== Backward Chaining Inference ===\n";
    set<string> visited;

    if (backwardChaining(goal, rules, facts, visited))
        cout << "\nConclusion: Goal \"" << goal << "\" can be derived.\n";
    else
        cout << "\nConclusion: Goal \"" << goal << "\" cannot be derived.\n";

    return 0;
}
