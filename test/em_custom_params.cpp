#include <em/EventManager.hpp>

enum class AState {
    READ,
    COMPLETE
};

struct Data {
    int i;
};

class A : public em::EventManager<AState, Data> {
    public:
    void read(){
        fireEvent(AState::READ, {5});
    }
    void complete(){
        fireEvent(AState::COMPLETE, 0, 0);        
    }
};

int main(int argc, char* argv[]){
    A a;
    // a.on(AState::COMPLETE, [](int status){
    //     std::cout << status << std::endl;
    // });
    a.complete();
    return 0;
}