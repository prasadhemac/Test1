#include <vector>

using namespace std;

int countNonEmptyElements(const vector<string>& elems){
    int count = 0;
    for(const string& e : elems){
        if(e != "")
            count++;
    }
    return count;
}

class Rule{
public:
    Rule(string id, vector<string> elems)
        : id_(id)
        , elements_{elems}
    {
        count_ = countNonEmptyElements(this->elements_);
    }
    string id_{};
    vector<string> elements_;
    bool valid_{true};
    int count_{0};
};

bool isGeneric(const Rule& source_rule, const Rule& destRule){
    int N = source_rule.elements_.size();
    for(int i = 0; i < N; i++){
        auto e1 = source_rule.elements_[i];
        auto e2 = destRule.elements_[i];

        if(e1 != e2 && e1 != "")
            return false;
    }
    return true;
}

int main(int argc, char** argv){

    vector<Rule> rules;
    rules.push_back({"4", {"", "P", "Z"}});
    rules.push_back({"6", {"", "P", "Z"}});
    rules.push_back({"1", {"X", "Y", "Z"}});
    rules.push_back({"2", {"X", "Y", ""}});
    rules.push_back({"3", {"", "Y", "Z"}});
    rules.push_back({"5", {"", "Y", ""}});
    
    sort(rules.begin(), rules.end(), [](const Rule& a, const Rule& b){
        return a.count_ < b.count_;
    });
    for(auto rule : rules){
        cout << rule.id_ << " " << rule.valid_ << endl;
    }
    for(int i = 0; i < rules.size(); i++){
        auto& rule1 = rules[i];
        if(!rule1.valid_)
            continue;
        for(int j = i+1; j < rules.size(); j++){
            auto& rule2 = rules[j];
            if(!rule2.valid_)
                continue;
            if(isGeneric(rule1, rule2))
                rule2.valid_ = false;
        }
    }
    for(auto rule : rules){
        cout << rule.id_ << " " << rule.valid_ << endl;
    }

    return 0;
}