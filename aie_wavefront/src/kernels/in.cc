// #include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <string.h>
#include <cstdio>
#include <stdio.h>
// #include <math.h>
// #include <time.h>
#include <adf.h>
#include <aie_api/aie.hpp>
// #include "adf/x86sim/streamApi.h"
// #include "aie_api/aie_types.hpp"
#include "../kernels.h"
// #include "adf/x86sim/streamApi.h"
// #include "adf/x86sim/streamApi.h"

// #define ctl_num  5
// #define order 3





/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void in(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout)
{
    
    // char x_dim =20;
    char num =5;
    char k = 3;
    
    int num_interval = num+ 2*k;
    int num_basis = num + k -1; 
    float grid[num_interval];


    //float temp; //can use temp tp save the storage if necessary
    // read grid. it should predefined the interval
    for (int i = 0; i < num_interval; i++)chess_prepare_for_pipelining {
        grid[i] =readincr(datain);
        writeincr(dataout,grid[i]);
    }

    float temp1; //can use temp tp save the storage if necessary
    //read data
    // float buf[x_dim];
    for(int i=0;i<x_dim;i++)chess_prepare_for_pipelining{
        temp1=readincr(datain);
        writeincr(dataout,temp1);        
    }
    

    
    //output push the rest data
    for(int j=0;j<4;j++){           
            writeincr(dataout, 0);//fill the buf in length of 128-bit
        }


}

