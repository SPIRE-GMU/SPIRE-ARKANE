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
// #include "adf/x86sim/streamStructs.h"
// #include "aie_api/aie_types.hpp"
#include "../kernels.h"



/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void Basis0(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout,output_stream<float>* __restrict gridout)
{
    
    // char x_dim =20;
    char num =5;
    char k = 3;
    
    int num_interval = num+ 2*k;
    int num_basis = num + k -1; 
    float grid[2*num_interval] ; //very important

    float result_0[(k+1)]; //3-dim, num_interval, order-0,x-dim    

    // read grid, transit to vertical direction. it should predefined the interval
    for (int i = 0; i < num_interval; i++) {
        grid[i] =readincr(datain);
        writeincr(dataout,grid[i]);
    }
    //transit to horizontal direction. // very important to shift the grid
    for (int i = 0; i < num_interval; i++) {
        writeincr(gridout,grid[i+1]);
    }

    //read data, transit in two direction
    // float buf[x_dim];
    float temp1;
    for(int j=0;j<x_dim;j++)chess_prepare_for_pipelining{
        // buf[i]=readincr(datain);
        // writeincr(dataout,buf[i]);  
        // writeincr(gridout,buf[i]);
        temp1=readincr(datain);
        writeincr(dataout,temp1); 
        writeincr(gridout,temp1);  
        //calculate order0

        for (int i = 0; i < k+1; i++) {
            result_0[i] = (grid[i] <= temp1 && temp1 < grid[i + 1]) ? 1.0 : 0.0;
            writeincr(dataout,result_0[i]);            
        }  
    }
    
    

    //output result result
    for(int j=0;j<4;j++){           
            writeincr(dataout, 0);//fill the buf in length of 128-bit
            writeincr(gridout, 0);
        }


}

