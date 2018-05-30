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
    void onStart(A *v)
    {
        std::cout << "B::onStart" << std::endl;
    }

    void onClose(A *v)
    {
        std::cout << "B::Exit" << std::endl;
    }

  public:
    B()
    {
        A *v = new A();
        v->addEventHandler(AEvent::Start, this, &B::onStart);
        v->addEventHandler(AEvent::Close, this, &B::onClose);
        v->start();
        v->exit();
    }
};

int main(int argc, char *argv[])
{
    B tn;
    return 0;
}