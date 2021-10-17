#include <em/EventManager.hpp>

enum class AState {
    READ,
    COMPLETE
};

struct Data {
    int i;
};

class A : public em::EventManager<AState> {
    public:
    void read(){
        fireEvent<std::string>(AState::READ, std::string("Read"));
    }
    void complete(){
        fireEvent(AState::COMPLETE, std::string("Complete"));
        fireEvent<Data>(AState::COMPLETE, {10});
    }
};

void fn(std::string status){
    std::cout << status << std::endl;
}

void fnd(Data d){
    std::cout << d.i << std::endl;    
}

int main(int argc, char* argv[]){
    A a;
    a.on<std::string>(AState::READ, fn);
    a.on<Data>(AState::COMPLETE, +[](Data d){
        std::cout << d.i << std::endl;
    });
    a.read();
    a.complete();
    return 0;
}