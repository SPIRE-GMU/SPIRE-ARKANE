#ifndef spline_h
#define spline_h

// #include "adf/x86sim/streamStructs.h"
#include <adf.h>

#define x_dim 2000

void in(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis0(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout,output_stream<float>* __restrict gridout);
void Basis06(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis1(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis2(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis30(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis31(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis32(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis33(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis34(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis35(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void Basis36(input_stream<float>* __restrict left_in,  input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);
void out(input_stream<float> *  __restrict datain, output_stream<float>*  __restrict dataout);




#endif
