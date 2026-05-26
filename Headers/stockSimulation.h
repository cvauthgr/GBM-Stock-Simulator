#pragma once

#include "RandomGeneration.h"
#include <iostream>
#include <vector>
#include <fstream>

using stockPrice = double ;
using timeIndex = int ;
using stockPriceAndTimeIndex = std::pair< stockPrice , timeIndex > ;

class stockPriceSimulator
{
private :

    double m_currentStockPrice { } ;
    double m_previousStockPrice { } ;
    double m_driftRate { } ;
    double m_volatility { } ;
    double m_shock { } ;
    const int m_numberOfValues { } ;
    int m_index { 0 } ;
    std::vector< stockPriceAndTimeIndex > m_simulationOutput { } ;
    const double m_dt = 1.0/252.0 ;

public :

    explicit stockPriceSimulator( int numberOfValues , double startingPrice ,double volatility )
             : m_numberOfValues { numberOfValues } ,
               m_previousStockPrice { startingPrice } ,
               m_volatility { volatility }
    {}

    std::vector< stockPriceAndTimeIndex > getStockValues(){ return m_simulationOutput ; }

    double getPreviousStockPrice(){ return m_previousStockPrice ; } const
    double getDriftRate(){ return m_driftRate ; } const
    double getVolatility(){ return m_volatility ; } const
    double getShock(){ return m_shock ; } const
    double getNumberOfValues(){ return m_numberOfValues ; } const

    void mutatePreviousStockPrice( double newPreviousPrice ){ m_previousStockPrice = newPreviousPrice  ; }
    void mutateVolatility( double newVolatility ){ m_volatility = newVolatility ; }
    void mutateShock ( double newShock ){ m_shock = newShock ; }

    void incrementIndex(){ m_index += 1 ;}

    void volatilityMovement()
    {
        double randomChance { random::getReal( 0.0 , 1.0 ) } ;
        double suddenVolatilityMovement = m_volatility * std::sqrt( m_dt ) ;

        if( m_volatility < 1 && m_volatility > 0 )
        {
            if( randomChance <= 0.68 )
                m_volatility += random::fairChance(suddenVolatilityMovement) ;
            else if( randomChance <= 0.95 )
                m_volatility += 2*random::fairChance(suddenVolatilityMovement) ;
            else if( randomChance <= 0.99 )
                m_volatility += 3*random::fairChance(suddenVolatilityMovement) ;
            else
                m_volatility += 4*random::fairChance(suddenVolatilityMovement) ;
        }

    }

    stockPriceAndTimeIndex calculateNextPrice()
    {
        volatilityMovement() ;

        std::normal_distribution<double> shockDist( 0.0, 1.0 );

        m_shock = shockDist( random::mt ) * std::sqrt( m_dt ) ;

        m_currentStockPrice = m_previousStockPrice * std::pow( std::numbers::e , ( m_driftRate * m_dt ) + ( m_volatility * m_shock ) ) ;
        m_previousStockPrice = m_currentStockPrice  ;
        incrementIndex() ;

        return std::make_pair( m_currentStockPrice , m_index ) ;
    }

    void collectAllPrices(){ m_simulationOutput.push_back( calculateNextPrice() ) ; }

    void executeSimulation()
    {
        std::normal_distribution<double> driftRateDist( 0.1 , 0.05 );
        m_driftRate = driftRateDist( random::mt ) ;

        for( int index = 0 ; index < m_numberOfValues ; ++ index )
            collectAllPrices() ;
    }

    void printStockPriceAndTimeIndex()
    {
        for( stockPriceAndTimeIndex data : m_simulationOutput )
        {
            std::cout << "Price : " << data.first << " , index : " << data.second << '\n' ;
        }
    }

    void writeStockDataToFile()
    {
        std::string fileName { "SimulatedStockSnapshot.txt" } ;

            std::ofstream objectFileName;

            objectFileName.open(fileName) ; //Open the provided object file with the choosen name

            if( objectFileName.is_open() )
            {
                for( int index = 0 ; index < std::ssize( m_simulationOutput ) ; ++ index )
                {
                    objectFileName << m_simulationOutput[index].first << '\n' ;
                }

                objectFileName.close() ;
            }
    }

};
stockPriceSimulator createSimulationObject( int numberOfValues , double startingPrice , double volatility )
{
    stockPriceSimulator object { numberOfValues , startingPrice , volatility } ;

    return object ;
}