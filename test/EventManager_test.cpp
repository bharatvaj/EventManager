#include <iostream>
#include <em/EventManager.hpp>

enum class AEvent
{
    Start,
    Exit
};

class A : public em::EventManager<AEvent>
{
  public:
    A()
    {
    }
    void start()
    {
        fireEvent<A*>(AEvent::Start, this);
    }

    void exit()
    {
        fireEvent<A*>(AEvent::Exit, this);
    }
};

class B
{
    void onStart(A *a)
    {
        std::cout << "B::onStart" << std::endl;
    }

    void onExit(A *a)
    {
        std::cout << "B::onExit" << std::endl;
    }

  public:
    B()
    {
        A *a = new A();
        a->on(AEvent::Start, this, &B::onStart);
        // a->on<A*>(AEvent::Exit, this, &B::onExit);
        a->start();
        a->exit();
    }
};

void onStart(A *a)
{
    std::cout << "::onStart" << std::endl;
}

void onExit(A *a){
  std::cout << "::onExit" << std::endl;
}

int main(int argc, char *argv[])
{
    B b;
    A a;
    // a.on(em::event::EVERY, onStart);
    a.on<A*>(AEvent::Exit, onExit);
    a.start();
    a.exit();
    return 0;
}
