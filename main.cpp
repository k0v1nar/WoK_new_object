#include <gamebase/Gamebase.h>

using namespace gamebase;
using namespace std;

class MyApp : public App
{
    void load()
    {

    }

    void process(Input input)
    {
        using namespace gamebase::InputKey;

    }

    void move()
    {
        
    }
};

int main(int argc, char** argv)
{
    MyApp app;
    app.setConfig("WoK_new_objectConfig.json");
    app.setDesign("Design.json");
    if (!app.init(&argc, argv))
        return 1;
    app.run();
    return 0;
}
