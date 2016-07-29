//
//  elementOscilator.h
//  DGTL_Generator
//
//  Created by Eduard Frigola on 29/07/16.
//
//

#ifndef elementOscilator_h
#define elementOscilator_h

#include "ofMain.h"

class elementOscilator{
public:
    elementOscilator();
    ~elementOscilator(){};
    
    float computeFunc(float phasor, int index);
    
private:
    //Parameters
    float freq_Param; //Desphase Quantity
    int pow_Param; //Pow of the funcion, working on sin, cos....
    int indexCount_Param; //The max number you will get from index
    

    
};

#endif /* elementOscilator_h */
