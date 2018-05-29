# EventManager
EventManager can be used for any event driven programming in CPP

### Usage Example
```cpp
enum class AEvent {
    Start,
    Close
};
class A : public EventManager<AEvent, int>{
    public:
    A(){
    }
    void run(){
        fireEvent(AEvent::Start, 0);
        fireEvent(AEvent::Close, 100);
    }
};

void onStart(int val){
    //do something on start of A
}

void onClose(int val){
    //do something on close of A
}

int main(int argc, char *argvp[]){
    A a;
    a.addEventHandler(AEvent::Start, onStart);
    a.addEventHandler(AEvent::Close, onClose);
    a.start();
    return 0;
}
```