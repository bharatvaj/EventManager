#include <iostream>
#include <em/EventManager.hpp>

using namespace em;

enum class AEvent
{
    Start,
    Close
};
class ProcessA : public EventManager<AEvent, int>
{
  public:
    ProcessA()
    {
        fireEvent(AEvent::Start, new int(0));
    }
    ~ProcessA()
    {
        fireEvent(AEvent::Close, new int(100));
    }
};

class ProcessB
{
    void onStart(int val)
    {
        std::cout << "A started with val: " << val << std::endl;
    }

    void onClose(int val)
    {
        std::cout << "A closed with val: " << val << std::endl;
    }

  public:
    ProcessB()
    {
        ProcessA a;
        //using namespace std::placeholders;
        //auto fun = std::bind(&ProcessB::onStart, this, _1);
        //a.addEventHandler(AEvent::Start, fun);
    }
};

int main(int argc, char *argv[])
{
    ProcessB b;
    return 0;
}