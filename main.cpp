#include "stockSimulation.h"

int main()
{
    auto simulationObject = createSimulationObject( 252 , 100 , 0.35 ) ;

    simulationObject.executeSimulation() ;
    simulationObject.printStockPriceAndTimeIndex() ;
    simulationObject.writeStockDataToFile() ;
    
    return 0;
}
