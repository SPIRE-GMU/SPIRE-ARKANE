#include <adf.h>
// #include "adf/new_frontend/adf.h"
#include "adf/new_frontend/adf.h"
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
//   kernel repeat_node;
  kernel k_in,k_out;     
  kernel phase0[7];
  kernel phase1[7];
  kernel phase2[7];
  kernel phase3[7];
  kernel phase4[7];
  kernel phase5[7];
  kernel phase6[7];
  kernel phase7[7];

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
    source(k_in) = "src/kernels/in.cc";
    source(k_out) = "src/kernels/out.cc";

    for(int i=0;i<6;i++){
        phase0[i] = kernel::create(Basis00);
        source(phase0[i]) = "src/kernels/order00.cc";
    }
    phase0[6] = kernel::create(Basis60);
    source(phase0[6]) = "src/kernels/order60.cc";

    for(int i=0;i<7;i++){
        phase1[i] = kernel::create(horizontal_1);
        source(phase1[i]) = "src/kernels/horizontal_1.cc";
    }
    for(int i=0;i<7;i++){
        phase2[i] = kernel::create(horizontal_2);
        source(phase2[i]) = "src/kernels/horizontal_2.cc";

    }
    for(int i=0;i<7;i++){
        phase3[i] = kernel::create(horizontal_3);
        source(phase3[i]) = "src/kernels/horizontal_3.cc";
        
    }
    for(int i=0;i<7;i++){
        phase4[i] = kernel::create(horizontal_4);
        source(phase4[i]) = "src/kernels/horizontal_4.cc";

    }
    for(int i=0;i<7;i++){
        phase5[i] = kernel::create(horizontal_5);
        source(phase5[i]) = "src/kernels/horizontal_5.cc";

    }
    for(int i=0;i<7;i++){
        phase6[i] = kernel::create(horizontal_6);
        source(phase6[i]) = "src/kernels/horizontal_6.cc";

    }



    phase7[0]= kernel::create(horizontal_07);
    phase7[1]= kernel::create(vertical_1);
    phase7[2]= kernel::create(vertical_2);
    phase7[3]= kernel::create(vertical_3);
    phase7[4]= kernel::create(vertical_4);
    phase7[5]= kernel::create(vertical_5);
    phase7[6]= kernel::create(vertical_6);

    source(phase7[0]) = "src/kernels/horizontal_07.cc";
    source(phase7[1]) = "src/kernels/vertical_1.cc";
    source(phase7[2]) = "src/kernels/vertical_2.cc";
    source(phase7[3]) = "src/kernels/vertical_3.cc";
    source(phase7[4]) = "src/kernels/vertical_4.cc";
    source(phase7[5]) = "src/kernels/vertical_5.cc";
    source(phase7[6]) = "src/kernels/vertical_6.cc";


    data_in = input_gmio::create("Data_in",128,256); //burst_length
    data_out = output_gmio::create("Data_out",128,256);

    pl_out = output_plio::create(plio_32_bits, "data/output_1.txt");
   

    connect<stream> net0 (data_in.out[0], k_in.in[0]);
    connect<stream> net1 (k_in.out[0], phase0[0].in[0]);

    connect<stream> net2 (phase0[0].out[1], phase0[1].in[0]);
    connect<stream> net3 (phase0[1].out[1], phase0[2].in[0]);
    connect<stream> net4 (phase0[2].out[1], phase0[3].in[0]);
    connect<stream> net5 (phase0[3].out[1], phase0[4].in[0]);
    connect<stream> net6 (phase0[4].out[1], phase0[5].in[0]);
    connect<stream> net7 (phase0[5].out[1], phase0[6].in[0]);


    connect<stream> net8  (phase0[0].out[0], phase1[0].in[0]);
    connect<stream> net9  (phase0[1].out[0], phase1[1].in[0]);
    connect<stream> net10 (phase0[2].out[0], phase1[2].in[0]);
    connect<stream> net11 (phase0[3].out[0], phase1[3].in[0]);
    connect<stream> net12 (phase0[4].out[0], phase1[4].in[0]);
    connect<stream> net13 (phase0[5].out[0], phase1[5].in[0]);
    connect<stream> net14 (phase0[6].out[0], phase1[6].in[0]);

    connect<stream> net15 (phase1[0].out[0], phase2[0].in[0]);
    connect<stream> net16 (phase1[1].out[0], phase2[1].in[0]);
    connect<stream> net17 (phase1[2].out[0], phase2[2].in[0]);
    connect<stream> net18 (phase1[3].out[0], phase2[3].in[0]);
    connect<stream> net19 (phase1[4].out[0], phase2[4].in[0]);
    connect<stream> net20 (phase1[5].out[0], phase2[5].in[0]);
    connect<stream> net21 (phase1[6].out[0], phase2[6].in[0]);

    connect<stream> net22 (phase2[0].out[0], phase3[0].in[0]);
    connect<stream> net23 (phase2[1].out[0], phase3[1].in[0]);
    connect<stream> net24 (phase2[2].out[0], phase3[2].in[0]);
    connect<stream> net25 (phase2[3].out[0], phase3[3].in[0]);
    connect<stream> net26 (phase2[4].out[0], phase3[4].in[0]);
    connect<stream> net27 (phase2[5].out[0], phase3[5].in[0]);
    connect<stream> net28 (phase2[6].out[0], phase3[6].in[0]);

    connect<stream> net29 (phase3[0].out[0], phase4[0].in[0]);
    connect<stream> net30 (phase3[1].out[0], phase4[1].in[0]);
    connect<stream> net31 (phase3[2].out[0], phase4[2].in[0]);
    connect<stream> net32 (phase3[3].out[0], phase4[3].in[0]);
    connect<stream> net33 (phase3[4].out[0], phase4[4].in[0]);
    connect<stream> net34 (phase3[5].out[0], phase4[5].in[0]);
    connect<stream> net35 (phase3[6].out[0], phase4[6].in[0]);

    connect<stream> net36 (phase4[0].out[0], phase5[0].in[0]);
    connect<stream> net37 (phase4[1].out[0], phase5[1].in[0]);
    connect<stream> net38 (phase4[2].out[0], phase5[2].in[0]);
    connect<stream> net39 (phase4[3].out[0], phase5[3].in[0]);
    connect<stream> net40 (phase4[4].out[0], phase5[4].in[0]);
    connect<stream> net41 (phase4[5].out[0], phase5[5].in[0]);
    connect<stream> net42 (phase4[6].out[0], phase5[6].in[0]);

    connect<stream> net43 (phase5[0].out[0], phase6[0].in[0]);
    connect<stream> net44 (phase5[1].out[0], phase6[1].in[0]);
    connect<stream> net45 (phase5[2].out[0], phase6[2].in[0]);
    connect<stream> net46 (phase5[3].out[0], phase6[3].in[0]);
    connect<stream> net47 (phase5[4].out[0], phase6[4].in[0]);
    connect<stream> net48 (phase5[5].out[0], phase6[5].in[0]);
    connect<stream> net49 (phase5[6].out[0], phase6[6].in[0]);

    connect<stream> net50 (phase6[0].out[0], phase7[0].in[0]);
    connect<stream> net51 (phase6[1].out[0], phase7[1].in[0]);
    connect<stream> net52 (phase6[2].out[0], phase7[2].in[0]);
    connect<stream> net53 (phase6[3].out[0], phase7[3].in[0]);
    connect<stream> net54 (phase6[4].out[0], phase7[4].in[0]);
    connect<stream> net55 (phase6[5].out[0], phase7[5].in[0]);
    connect<stream> net56 (phase6[6].out[0], phase7[6].in[0]);
    
    connect<stream> net57 (phase7[0].out[0], phase7[1].in[1]);
    connect<stream> net58 (phase7[1].out[0], phase7[2].in[1]);
    connect<stream> net59 (phase7[2].out[0], phase7[3].in[1]);
    connect<stream> net60 (phase7[3].out[0], phase7[4].in[1]);
    connect<stream> net61 (phase7[4].out[0], phase7[5].in[1]);
    connect<stream> net62 (phase7[5].out[0], phase7[6].in[1]);
    connect<stream> net63 (phase7[6].out[0], k_out.in[0]);


    connect<stream> net64 (k_out.out[0], pl_out.in[0]);
    connect<stream> net65 (k_out.out[0], data_out.in[0]);
    
   

    fifo_depth(net0) = 512;
    fifo_depth(net1) = 512;
    fifo_depth(net2) = 512;
    fifo_depth(net3) = 512;
    fifo_depth(net4) = 512;
    fifo_depth(net5) = 512;
    fifo_depth(net6) = 512;
    fifo_depth(net7) = 512;
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
    fifo_depth(net38) = 512;
    fifo_depth(net39) = 512;
    fifo_depth(net40) = 512;
    fifo_depth(net41) = 512;
    fifo_depth(net42) = 512;
    fifo_depth(net43) = 512;
    fifo_depth(net44) = 512;
    fifo_depth(net45) = 512;
    fifo_depth(net46) = 512;
    fifo_depth(net47) = 512;
    fifo_depth(net48) = 512;
    fifo_depth(net49) = 512;
    fifo_depth(net50) = 512;
    fifo_depth(net51) = 512;
    fifo_depth(net52) = 512;
    fifo_depth(net53) = 512;
    fifo_depth(net54) = 512;
    fifo_depth(net55) = 512;
    fifo_depth(net56) = 512;
    fifo_depth(net57) = 512;
    fifo_depth(net58) = 512;
    fifo_depth(net59) = 512;
    fifo_depth(net60) = 512;
    fifo_depth(net61) = 512;
    fifo_depth(net62) = 512;
    fifo_depth(net63) = 512;
    fifo_depth(net64) = 512;
    fifo_depth(net65) = 512;

    
    
    



    runtime<ratio>(k_in) = 0.1;
    runtime<ratio>(k_out) = 0.1;

    for(int i=0;i<7;i++){
        runtime<ratio>(phase0[i]) = 0.1;
        runtime<ratio>(phase1[i]) = 0.1;
        runtime<ratio>(phase2[i]) = 0.1;
        runtime<ratio>(phase3[i]) = 0.1;
        runtime<ratio>(phase4[i]) = 0.1;
        runtime<ratio>(phase5[i]) = 0.1;
        runtime<ratio>(phase6[i]) = 0.1;
        runtime<ratio>(phase7[i]) = 0.1;


    }    

    
    adf::location<kernel>(k_in)=adf::tile(0,0); 
    for(int i=0;i<7;i++){
        adf::location<kernel>(phase0[i])=adf::tile(1,i);
        adf::location<kernel>(phase1[i])=adf::tile(2,i);
        adf::location<kernel>(phase2[i])=adf::tile(3,i);
        adf::location<kernel>(phase3[i])=adf::tile(4,i);
        adf::location<kernel>(phase4[i])=adf::tile(5,i);
        adf::location<kernel>(phase5[i])=adf::tile(6,i);
        adf::location<kernel>(phase6[i])=adf::tile(7,i);
        adf::location<kernel>(phase7[i])=adf::tile(8,i);


    }
    adf::location<kernel>(k_out)=adf::tile(9,0); 
 
    }
};

