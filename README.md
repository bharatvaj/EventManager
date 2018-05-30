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

### Callbacks within classes
```cpp
class B
{
    void onStart(A *a)
    {
        std::cout << "B::onStart" << std::endl;
    }

    void onClose(A *a)
    {
        std::cout << "B::Exit" << std::endl;
    }

  public:
    B()
    {
        A *a = new A();
        a->addEventHandler(AEvent::Start, this, &B::onStart);
        a->addEventHandler(AEvent::Close, this, &B::onClose);
        a->start();
        a->exit();
    }
};
```
Since the member-to-pointer needs object, the addEventHandler method is changed on class callbacks as,
```cpp
v->addEventHandler(AEvent::Close, this, &B::onClose);
```