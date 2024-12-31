// #include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <string.h>
#include <cstdio>
#include <stdio.h>
// #include "aie_api/aie_types.hpp"
// #include "aie_api/aie_adf.hpp"
// #include <aie_api/utils.hpp>
// #include <math.h>
// #include <time.h>
#include <adf.h>
#include <aie_api/aie.hpp>
// #include "adf/x86sim/streamApi.h"
// #include "adf/x86sim/streamStructs.h"
// #include "aie_api/aie_types.hpp"
#include "../kernels.h"
using namespace adf;

// float calculate_bspline(float *grid,  float x) {
//     float N0[4] = {0};  // Reduced to 4 for 0-degree
//     float N1[3] = {0};  // Reduced to 3 for 1st-degree
//     float N2[2] = {0};  // Reduced to 2 for 2nd-degree
//     float N3[1] = {0};  // Reduced to 1 for 3rd-degree
    
//     // Compute 0-degree B-spline coefficients
//     for (int i = 0; i < 4; i++) {  // Adjusted loop limit for 0-degree
//         N0[i] = (grid[i] <= x && x < grid[i + 1]) ? 1.0 : 0.0;
//     }

//     // Compute 1st-degree B-spline coefficients
//     for (int i = 0; i < 3; i++) {  // Adjusted loop limit for 1st-degree
//         float alpha_denominator = grid[i + 1] - grid[i];
//         float beta_denominator = grid[i + 2] - grid[i + 1];
//         float alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N0[i];
//         float beta = (beta_denominator == 0) ? 0 : (grid[i + 2] - x) / beta_denominator * N0[i + 1];
//         N1[i] = alpha + beta;
//     }

//     // Compute 2nd-degree B-spline coefficients
//     for (int i = 0; i < 2; i++) {  // Adjusted loop limit for 2nd-degree
//         float alpha_denominator = grid[i + 2] - grid[i];
//         float beta_denominator = grid[i + 3] - grid[i + 1];
//         float alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N1[i];
//         float beta = (beta_denominator == 0) ? 0 : (grid[i + 3] - x) / beta_denominator * N1[i + 1];
//         N2[i] = alpha + beta;
//     }

//     // Compute 3rd-degree B-spline coefficients
//     for (int i = 0; i < 1; i++) {  // Adjusted loop limit for 3rd-degree
//         float alpha_denominator = grid[i + 3] - grid[i];
//         float beta_denominator = grid[i + 4] - grid[i + 1];
//         float alpha = (alpha_denominator == 0) ? 0 : (x - grid[i]) / alpha_denominator * N2[i];
//         float beta = (beta_denominator == 0) ? 0 : (grid[i + 4] - x) / beta_denominator * N2[i + 1];
//         N3[i] = alpha + beta;
//     }

//     return N3[0];
// }

// float calculate_bspline(float *grid, int num_of_basis, float x) {
//     // Precompute zero-degree B-spline basis
//     float N0[4] = {0};
//     for (int i = 0; i < 4; i++) {
//         N0[i] = (grid[i] <= x && x < grid[i + 1]) ? 1.0 : 0.0;
//     }

//     // Compute coefficients for the 4 terms
//     float a0 = ((x - grid[0]) * (x - grid[0]) * (x - grid[0])) / 
//                ((grid[3] - grid[0]) * (grid[2] - grid[0]) * (grid[1] - grid[0]));

//     float a1 = ((x - grid[0]) * (x - grid[0]) * (grid[2] - x)) / 
//                ((grid[3] - grid[0]) * (grid[2] - grid[1]) * (grid[2] - grid[0])) + ((x-grid[0])*(grid[3]-x)*(x-grid[1]))/((grid[3]-grid[0])*(grid[3]-grid[1])*(grid[2]-grid[1])) + ((x-grid[1])*(grid[4]-x)*(x-grid[1]))/((grid[4]-grid[0])*(grid[3]-grid[1])*(grid[2]-grid[1]));

//     float a2 = ((x - grid[0]) * (grid[3] - x) * (grid[3] - x)) / 
//                ((grid[3] - grid[0]) * (grid[3] - grid[1]) * (grid[3] - grid[2]))+ 
//                ((x - grid[1]) * (grid[4] - x) * (grid[3] - x))/
//                ((grid[3] - grid[1]) * (grid[3] - grid[2]) * (grid[4] - grid[1])) + 
//                ((x - grid[2]) * (grid[4] - x) * (grid[4] - x))/
//                ((grid[4] - grid[1]) * (grid[4] - grid[2]) * (grid[3] - grid[2]));

//     float a3 = ((grid[4] - x) * (grid[4] - x) * (grid[4] - x)) / 
//                ((grid[4] - grid[1]) * (grid[4] - grid[2]) * (grid[4] - grid[3]));

//     // Combine the 4 terms
//     float N3 = a0 * N0[0] + a1 * N0[1] + a2 * N0[2] + a3 * N0[3];

//     return N3;
// }

/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void horizontal_5(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout)
{
    
    // char x_dim =20;
    char num =5;
    char k = 3;
    
    int num_interval = num+ 2*k;
    int num_basis = num + k -1; 
    float grid[2*num_interval] ; //very important

    float result_0; //3-dim, num_interval, order-0,x-dim    

    // read grid, transit to horizontal direction. it should predefined the interval
    for (int i = 0; i < num_interval; i++) {
        grid[i] =readincr(datain);
        writeincr(dataout,grid[i]);
    }
   

    //read data, transit in two direction
    float temp0;
    float temp1; //input vertical direction
    float temp2; //temp result
    float temp3; //
    float N0;    //
    for(int j=0;j<x_dim;j++)chess_prepare_for_pipelining{
        
        temp0=readincr(datain);
        writeincr(dataout,temp0);
        N0 =(grid[2] <= temp0 && temp0 < grid[2 + 1]) ? 1.0 : 0.0;
        temp1=readincr(datain);
        temp2 =((temp0 - grid[1]) * (grid[4] - temp0) * (grid[3] - temp0))/
               ((grid[3] - grid[1]) * (grid[3] - grid[2]) * (grid[4] - grid[1]));
        temp3 = temp1 + temp2*N0;
        writeincr(dataout,temp3);

    }
    
    // intrinsics (only v8 supported for float-point type)
    // float inv = 1/((grid[3] - grid[0]) * (grid[2] - grid[0]) * (grid[1] - grid[0]));
    // v8float temp1; //input vertical direction
    // v8float temp2; //temp result
    // v8float temp3;
    // for(int j=0;j<x_dim/8;j++)chess_prepare_for_pipelining{
        
    //     temp1=readincr_v<8>(datain);
    //     writeincr_v<8>(gridout,temp1);  

    //     temp2 = aie::sub(temp1,grid[0]); // v = x-grid 
    //     temp3 = fpmul(temp2,temp2); //v*v
    //     temp3 = fpmul(temp3,temp2);//v*v*v
    //     temp3 = lsrs(aie::mul(temp3,inv),0);//v*v*v / grid        

       
    //     writeincr_v<8>(dataout,temp3); 

    // }
    

    //output result result
    for(int j=0;j<4;j++){           
            writeincr(dataout, 0);//fill the buf in length of 128-bit
            // writeincr(gridout, 0);
        }


}

