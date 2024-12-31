#include <stdio.h>
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



/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void Basis1(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout)
{
    

    // char x_dim =20;
    char num =5;
    char k = 3;
    
    int num_interval = num+ 2*k;
    int num_basis = num + k -1; 
    float grid[num_interval];

    float N0[k+1];  
    float N1[k];  

    // read grid. it should predefined the interval
    for (int i = 0; i < num_interval; i++) {
        // grid[i] = -1.0 + i * (2.0 / (num_interval - 1));
        grid[i] =readincr(datain);
        writeincr(dataout,grid[i]);
    }

    float alpha_denominator = grid[1] - grid[0];
    float beta_denominator = grid[2] - grid[1];       

    float x;
    //calculate order0
    for(int j=0;j<x_dim;j++)chess_prepare_for_pipelining{
        //read x
        x = readincr(datain);
        //read result
        for(int i=0;i<k+1;i++){
            N0[i] = readincr(datain);         
        }

        //transit x
        writeincr(dataout,x);
        //process and transit result
        for (int i = 0; i < k; i++) {
            float alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N0[i];
            float beta = (beta_denominator == 0) ? 0 : (grid[i + 2] - x) / beta_denominator * N0[i + 1];
            N1[i] = alpha + beta;
            writeincr(dataout,N1[i]);
        }
    }



    //output result result
    for(int j=0;j<4;j++){           
            writeincr(dataout, 0);//fill the buf in length of 128-bit
        }


}

