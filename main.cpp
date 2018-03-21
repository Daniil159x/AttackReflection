// UTF-8 BOM

#include "allinclusions.hpp"


int main()
{
    Button::GlobalFontInit();

    Game gm;
    gm.Init();
    gm.ShowMenu();
    gm.Display();

    return 0;
}
