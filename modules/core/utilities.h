#pragma once
#include "ppm.h"
#include <fstream>
namespace rt{
void saveRT(std::vector<Hitpoint> &data,char* fn,double mn = 0,double mx = 1){
    std::ofstream pcl(fn,std::ofstream::out);
    pcl<<std::setprecision(8);
    auto scale = [mn,mx](float c){return (c - mn)*255/(mx - mn);};
    for (auto it : data ){
        pcl << it.hit[0]<<" "<<it.hit[1]<<" "<<it.hit[2]<<" "<<scale(it.color[0])<<" "<<scale(it.color[1])<<" "<<scale(it.color[2])<<std::endl;
    }
    pcl.close();
}

void savePM(std::unordered_set<Photon,TkeyHash> &data,char* fn,double mn = 0,double mx = 1){
    std::ofstream pcl(fn,std::ofstream::out);
    pcl<<std::setprecision(8);
    auto scale = [mn,mx](float c){return static_cast<double>(1000*(c - mn)*255/(mx - mn)) ;};
    for (auto it : data ){
        pcl << it.hit[0]<<" "<<it.hit[1]<<" "<<it.hit[2]<<" "<<scale(it.radiance[0])<<" "<<scale(it.radiance[1])<<" "<<scale(it.radiance[2])<<std::endl;
    }
    pcl.close();
}

double comp(double mn, Vec3f val, int op = 0){
    Vec3d a(val);
    double lst[4] = {mn,a[0],a[1],a[2]};
    if(op == 0){
        //min
        return *std::min_element(lst,lst+4);

    }
    else{
        return *std::max_element(lst,lst+4);

    }
}

}