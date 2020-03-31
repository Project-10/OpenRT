#pragma once
#include "ppm.h"
#include <fstream>
namespace rt{
    struct Hitpoint;

void savePCL(std::vector<Hitpoint> &data,char* fn,double mn = 0,double mx = 1){
    std::ofstream pcl(fn,std::ofstream::out);
    pcl<<std::setprecision(8);
    auto scale = [mn,mx](float c){return (c - mn)*255/(mx - mn);};
    for (auto it : data ){
        pcl << it.hit[0]<<" "<<it.hit[1]<<" "<<it.hit[2]<<" "<<scale(it.color[0])<<" "<<scale(it.color[1])<<" "<<scale(it.color[2])<<std::endl;
    }
    pcl.close();
}

}