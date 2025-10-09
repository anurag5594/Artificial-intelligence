#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

/*
 Forward Chaining Algorithm
 --------------------------
 - Start with a set of known facts.
 - Repeatedly apply rules whose conditions are satisfied by the known facts.
 - Add the conclusions of those rules to the known facts.
 - Continue until no new facts can be added or the goal is achieved.
*/

// Structure for a rule: IF all conditions -> THEN conclusion
struct Rule {
    vector<string> conditions;
    string conclusion;
};

bool allConditionsMet(const vector<string> &conditions, const set<string> &facts) {
    for (const string &cond : conditions) {
        if (facts.find(cond) == facts.end())
            return false; // Condition not in known facts
    }
    return true;
}

void forwardChaining(vector<Rule> &rules, set<string> &facts, const string &goal) {
    bool newFactAdded = true;

    cout << "Initial Facts: ";
    for (const auto &f : facts) cout << f << " ";
    cout << "\n";

    while (newFactAdded) {
        newFactAdded = false;

        for (const auto &rule : rules) {
            // If all conditions of the rule are satisfied and conclusion is new
            if (allConditionsMet(rule.conditions, facts) &&
                facts.find(rule.conclusion) == facts.end()) {

                cout << "Applying Rule: IF ";
                for (size_t i = 0; i < rule.conditions.size(); ++i) {
                    cout << rule.conditions[i];
                    if (i < rule.conditions.size() - 1) cout << " AND ";
                }
                cout << " THEN " << rule.conclusion << "\n";

                facts.insert(rule.conclusion);
                newFactAdded = true;

                // If goal is achieved
                if (rule.conclusion == goal) {
                    cout << "Goal \"" << goal << "\" has been derived!\n";
                    return;
                }
            }
        }
    }

    cout << "No more rules can be applied.\n";
    if (facts.find(goal) != facts.end())
        cout << "Goal \"" << goal << "\" is in the knowledge base.\n";
    else
        cout << "Goal \"" << goal << "\" cannot be derived.\n";
}

int main() {
    // Knowledge base: Rules
    vector<Rule> rules = {
        { {"A", "B"}, "C" },       // Rule 1: IF A AND B -> THEN C
        { {"C"}, "D" },           // Rule 2: IF C -> THEN D
        { {"D", "E"}, "F" },      // Rule 3: IF D AND E -> THEN F
        { {"F"}, "G" }            // Rule 4: IF F -> THEN G
    };

    // Initial facts
    set<string> facts = {"A", "B", "E"};

    // Goal
    string goal = "G";

    cout << "=== Forward Chaining Inference ===\n";
    forwardChaining(rules, facts, goal);

    return 0;
}
