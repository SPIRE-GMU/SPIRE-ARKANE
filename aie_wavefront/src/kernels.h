#ifndef spline_h
#define spline_h

// #include "adf/x86sim/streamStructs.h"
#include <adf.h>

#define x_dim 20

void in(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis00(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout,output_stream<float>* __restrict gridout);
void horizontal_1(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_2(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_3(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_4(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_5(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_6(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void horizontal_07(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis60(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void vertical_1(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);
void vertical_2(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);
void vertical_3(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);
void vertical_4(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);
void vertical_5(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);
void vertical_6(input_stream<float> *  __restrict datain, input_stream<float> *  __restrict result_in,output_stream<float>*  __restrict dataout);

void out(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);




#endif
