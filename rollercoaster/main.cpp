/*************************************************************
* Created by J. Weij
*************************************************************/
#include <NodeLib/NodeMaster.h>

#include "Rollercoaster.h"


int main(void)
{
    NodeLib::NodeMaster node(2);
    Rollercoaster rollercoaster(node);
    //init();

    //USBDevice.attach();


    node.Init();
    rollercoaster.Stop();

    for (;;)
    {

        node.Loop();
        //delay(2000);
        //if (serialEventRun){serialEventRun();}
    }

    rollercoaster.Stop();
}
