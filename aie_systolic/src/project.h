#include <adf.h>
// #include "adf/new_frontend/adf.h"
#include "adf/new_frontend/adf.h"
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
//   kernel repeat_node;
  kernel k_in,k_out;     
  kernel basis0[7];
  kernel basis1[7];
  kernel basis2[7];
  kernel basis3[7];
   

//   kernel split1;
//   kernel split2;

//   kernel merge1;
//   kernel merge2; 
public:
  input_gmio data_in;

  output_plio pl_out;
  output_gmio data_out;
  simpleGraph()
  {
   
    k_in = kernel::create(in);
    k_out = kernel::create(out);
    
    for(int i=0;i<6;i++){
        basis0[i] = kernel::create(Basis0);
    }
    basis0[6] = kernel::create(Basis06);

    for(int i=0;i<7;i++){
        basis1[i] = kernel::create(Basis1);
    }

    for(int i=0;i<7;i++){
        basis2[i] = kernel::create(Basis2);
    }

    basis3[0]= kernel::create(Basis30);
    basis3[1]= kernel::create(Basis31);
    basis3[2]= kernel::create(Basis32);
    basis3[3]= kernel::create(Basis33);
    basis3[4]= kernel::create(Basis34);
    basis3[5]= kernel::create(Basis35);
    basis3[6]= kernel::create(Basis36);

    data_in = input_gmio::create("Data_in",128,256); //burst_length
    data_out = output_gmio::create("Data_out",128,256);

    pl_out = output_plio::create(plio_32_bits, "data/output_1.txt");
   

    connect<stream> net0 (data_in.out[0], k_in.in[0]);
    connect<stream> net1 (k_in.out[0], basis0[0].in[0]);

    connect<stream> net2 (basis0[0].out[1], basis0[1].in[0]);
    connect<stream> net3 (basis0[1].out[1], basis0[2].in[0]);
    connect<stream> net4 (basis0[2].out[1], basis0[3].in[0]);
    connect<stream> net5 (basis0[3].out[1], basis0[4].in[0]);
    connect<stream> net6 (basis0[4].out[1], basis0[5].in[0]);
    connect<stream> net7 (basis0[5].out[1], basis0[6].in[0]);

    connect<stream> net8 (basis0[0].out[0], basis1[0].in[0]);
    connect<stream> net9 (basis0[1].out[0], basis1[1].in[0]);
    connect<stream> net10 (basis0[2].out[0], basis1[2].in[0]);
    connect<stream> net11 (basis0[3].out[0], basis1[3].in[0]);
    connect<stream> net12 (basis0[4].out[0], basis1[4].in[0]);
    connect<stream> net13 (basis0[5].out[0], basis1[5].in[0]);
    connect<stream> net14 (basis0[6].out[0], basis1[6].in[0]);

    connect<stream> net15 (basis1[0].out[0], basis2[0].in[0]);
    connect<stream> net16 (basis1[1].out[0], basis2[1].in[0]);
    connect<stream> net17 (basis1[2].out[0], basis2[2].in[0]);
    connect<stream> net18 (basis1[3].out[0], basis2[3].in[0]);
    connect<stream> net19 (basis1[4].out[0], basis2[4].in[0]);
    connect<stream> net20 (basis1[5].out[0], basis2[5].in[0]);
    connect<stream> net21 (basis1[6].out[0], basis2[6].in[0]);

    connect<stream> net22 (basis2[0].out[0], basis3[0].in[0]);
    connect<stream> net23 (basis2[1].out[0], basis3[1].in[1]);
    connect<stream> net24 (basis2[2].out[0], basis3[2].in[1]);
    connect<stream> net25 (basis2[3].out[0], basis3[3].in[1]);
    connect<stream> net26 (basis2[4].out[0], basis3[4].in[1]);
    connect<stream> net27 (basis2[5].out[0], basis3[5].in[1]);
    connect<stream> net28 (basis2[6].out[0], basis3[6].in[1]);

    connect<stream> net29 (basis3[0].out[0], basis3[1].in[0]);
    connect<stream> net30 (basis3[1].out[0], basis3[2].in[0]);
    connect<stream> net31 (basis3[2].out[0], basis3[3].in[0]);
    connect<stream> net32 (basis3[3].out[0], basis3[4].in[0]);
    connect<stream> net33 (basis3[4].out[0], basis3[5].in[0]);
    connect<stream> net34 (basis3[5].out[0], basis3[6].in[0]);

    connect<stream> net35 (basis3[6].out[0], k_out.in[0]);
    
    connect<stream> net37 (k_out.out[0], pl_out.in[0]);
    connect<stream> net36 (k_out.out[0], data_out.in[0]);
    
   

    fifo_depth(net0) = 128;
    fifo_depth(net1) = 512;
    fifo_depth(net2) = 512;
    fifo_depth(net3) = 512;
    fifo_depth(net4) = 512;
    fifo_depth(net5) = 512;
    fifo_depth(net6) = 512;
    fifo_depth(net7) = 128;
    fifo_depth(net8) = 512;
    fifo_depth(net9) = 512;
    fifo_depth(net10) = 512;
    fifo_depth(net11) = 512;
    fifo_depth(net12) = 512;
    fifo_depth(net13) = 512;
    fifo_depth(net14) = 512;
    fifo_depth(net15) = 512;
    fifo_depth(net16) = 512;
    fifo_depth(net17) = 512;
    fifo_depth(net18) = 512;
    fifo_depth(net19) = 512;
    fifo_depth(net20) = 512;
    fifo_depth(net21) = 512;
    fifo_depth(net22) = 512;
    fifo_depth(net23) = 512;
    fifo_depth(net24) = 512;
    fifo_depth(net25) = 512;
    fifo_depth(net26) = 512;
    fifo_depth(net27) = 512;
    fifo_depth(net28) = 512;
    fifo_depth(net29) = 512;
    fifo_depth(net30) = 512;
    fifo_depth(net31) = 512;
    fifo_depth(net32) = 512;
    fifo_depth(net33) = 512;
    fifo_depth(net34) = 512;
    fifo_depth(net35) = 512;
    fifo_depth(net36) = 512;
    fifo_depth(net37) = 512;
    // fifo_depth(net38) = 512;
    // fifo_depth(net39) = 512;
    
    source(k_in) = "src/kernels/in.cc";
    source(k_out) = "src/kernels/out.cc";
    for(int i=0;i<6;i++){
        source(basis0[i]) = "src/kernels/order0.cc";
    }
    source(basis0[6]) = "src/kernels/order06.cc";
    
    for(int i=0;i<7;i++){
        source(basis1[i]) = "src/kernels/order1.cc";
    }
    for(int i=0;i<7;i++){
        source(basis2[i]) = "src/kernels/order2.cc";
    }
    
    source(basis3[0]) = "src/kernels/order30.cc";
    source(basis3[1]) = "src/kernels/order31.cc";
    source(basis3[2]) = "src/kernels/order32.cc";
    source(basis3[3]) = "src/kernels/order33.cc";
    source(basis3[4]) = "src/kernels/order34.cc";
    source(basis3[5]) = "src/kernels/order35.cc";
    source(basis3[6]) = "src/kernels/order36.cc";
    



    runtime<ratio>(k_in) = 0.1;
    runtime<ratio>(k_out) = 0.1;

    for(int i=0;i<7;i++){
        runtime<ratio>(basis0[i]) = 0.1;
        runtime<ratio>(basis1[i]) = 0.1;
        runtime<ratio>(basis2[i]) = 0.1;
        runtime<ratio>(basis3[i]) = 0.1;


    }    

    
    adf::location<kernel>(k_in)=adf::tile(0,0); 
    for(int i=0;i<7;i++){
        adf::location<kernel>(basis0[i])=adf::tile(i+1,0);
        adf::location<kernel>(basis1[i])=adf::tile(i+1,1);
        adf::location<kernel>(basis2[i])=adf::tile(i+1,2);
        adf::location<kernel>(basis3[i])=adf::tile(i+1,3);
    }
    adf::location<kernel>(k_out)=adf::tile(8,3); 
 
    }
};

