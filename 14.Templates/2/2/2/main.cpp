#include <iostream>
#include <string>
#include <memory>

class VeryHeavyDatabase {
public:
    virtual std::string GetData(const std::string& key) const {
        return "value"; 
    }

    virtual ~VeryHeavyDatabase() = default;
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object;
    size_t max_shots;
    mutable size_t shots_used;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object(real_object), max_shots(shots), shots_used(0) {}

    std::string GetData(const std::string& key) const override {
        if (shots_used < max_shots) {
            shots_used++;
            return real_object->GetData(key);
        }
        else {
            return "error";
        }
    }
};

int main() {
    VeryHeavyDatabase real_db;
    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << std::endl; 
    std::cout << limit_db.GetData("key") << std::endl; 
    std::cout << limit_db.GetData("key") << std::endl; 
    std::cout << limit_db.GetData("key") << std::endl; 

    return 0;
}