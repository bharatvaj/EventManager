#include <iostream>
#include <em/EventManager.hpp>

enum class AEvent
{
    Start,
    Close
};

class A : public em::EventManager<AEvent, A>
{
  public:
    A()
    {
    }
    void start()
    {
        fireEvent(AEvent::Start, this);
    }
    void exit()
    {
        fireEvent(AEvent::Close, this);
    }
};

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

void onStart(A *a)
{
    std::cout << "::onStart" << std::endl;
}

int main(int argc, char *argv[])
{
    B b;
    A a;
    a.addEventHandler(AEvent::Start, onStart);
    a.start();
    return 0;
}