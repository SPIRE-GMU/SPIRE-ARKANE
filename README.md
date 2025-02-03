This repository contains code and data for the ARKANE paper.

1. Folder pykan-2-c includes C-based implementation of KAN. It doesn't rely on APIs or other libraries except basic math lib so it can be easy to migrate. More work is worth to research on the optimization of the parameter or a better gradient decent optimization. Simple compilation command as:

        gcc -o spline_test spline_test.c ../spline2fun_adam.c ../utils.c -lm 

    To monitor the power consumption, you can use the latest power tool powertop or powerstat.

2. Folder aie-xxx are source codes running on AI engines. The software is Vitis 2023.2 (also PDM 2023.2) but other versions are fine.

3. Folder Bspline-cuda is a simple GPU version of Bspline developed from spline_test.c with the same parameter. It distributes the spline functions into threads but has the potential to achieve a better speedup in other ways. Simple run it with:

        nvcc -o test calculate_test.cu -run

    Power consumption of GPU can be observed on nvidia-smi:

        watch -n 1 nvidia-smi
