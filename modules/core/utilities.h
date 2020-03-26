#pragma once
#include "ppm.h"
#include <fstream>
namespace rt{
    struct Hitpoint;

void savePCL(std::vector<Hitpoint> &data,char* fn){
    std::ofstream pcl(fn,std::ofstream::out);
    pcl<<std::setprecision(8);
    for (auto it : data ){
        pcl << it.hit[0]<<" "<<it.hit[1]<<" "<<it.hit[2]<<" "<<it.color[0]<<" "<<it.color[0]<<" "<<it.color[0]<<std::endl;
    }
    pcl.close();
}

}