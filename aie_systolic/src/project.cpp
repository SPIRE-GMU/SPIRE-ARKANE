#include "project.h"
// #include <cmath>
#include <fstream>
#include <cstdlib>
#include <string.h>
// #include <inttypes.h>
// #include <sys/time.h>
#include "math.h"
simpleGraph mygraph;


#if defined(__AIESIM__) || defined(__X86SIM__)
// static unsigned long long cpucycles(void)
// {
//     unsigned long long result;
//       __asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
//               : "=a" (result) ::  "%rdx");
//         return result;
// }

// 数据生成
void generate_data(float *inputs, float *outputs, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        inputs[i] = ((float)rand() / RAND_MAX) * 6 - 3; // -3到3之间的随机数
        outputs[i] = 1.5 *exp(0.5 *inputs[i] + 1)+1; // 
    }
}

int main(int argc, char **argv) 
{
    // uint64_t cyc0; 
    // uint64_t cyc1;
    // int num_samples=1000;
    // float inputs[num_samples];
    // float outputs[num_samples];
    // generate_data(inputs, outputs, num_samples);

    int num_interval=11;
    float grid[num_interval];
    for (int i = 0; i < num_interval; i++) {
        grid[i] = -1.0 + i * (2.0 / (num_interval - 1));
    }


    float inputs[2000]={-0.5,0,0.5};
    
    float  *inputbuf  = (float*) GMIO::malloc((num_interval+2000+20)*sizeof(float)); //GMIO input in this way
    float *outputbuf = (float*) GMIO::malloc(2000*7*sizeof(float));

    

    printf("\nThe input grid to bspline graph is :\n");
    for(int i=0;i<num_interval;i++){
        inputbuf[i]=grid[i];
    }

    for(int i=0;i<2000;i++)
	{
        inputbuf[i+num_interval]=inputs[i];
		// printf("%f",inputbuf[i]);	
	}

    // cyc0 = cpucycles();
    mygraph.init();
    
    
    mygraph.run(1);
    

    for(int i=0;i<1;i++){
        mygraph.data_in.gm2aie_nb(&inputbuf[0],2020*sizeof(float));
        //mygraph.update(mygraph.mlen, mlen);
  	    //mygraph.wait(); 
        mygraph.data_out.aie2gm_nb(&outputbuf[0],14000*sizeof(float));
        mygraph.data_out.wait(); //important !! wait for data move to DDR
    }
    mygraph.end();

    // cyc1 =  cpucycles();
    // printf("\ncycles of sha256 : %" PRIu64 "\n\n", cyc1-cyc0);
    
    printf("\nThe output is :\n");  //  
    // for(int i=0;i<1400;i++){	
        
    //     if(i%7==0){
    //         printf("\n");
    //     }
    //     printf("%f",outputbuf[i]);       	
	// }
    printf("\n");

    GMIO::free(inputbuf);
    GMIO::free(outputbuf);
  return 0;
} 
#endif