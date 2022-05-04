
//  Created by Mahmoud El Bergui on 26.04.22.
//

#ifndef PerlinNoise_h
#define PerlinNoise_h

#include <stdio.h>
#include<vector>

#endif /* PerlinNoise_hpp */

namespace rt{

     class CPerlinNoise{
          std::vector<int>p;
     public:
     /**  @Brief Construct Perlin Noise using values of the permutation vector
     */
          DllExport CPerlinNoise();

     /**  @Brief Generate 3D noise
          @param x x-coordinate value
          @param y y-coordinate value
          @param z z-coordinate value     */
          DllExport  double noise(double x, double y, double z);
          
     /**  @Brief Generate 3D turbulence
          @param x x-coordinate value
          @param y y-coordinate value
          @param z z-coordinate value
          @param octaves of noise octaves(layers)
          @param f frequency of the noise
          @param amplitude amplitude of the noise
          @param lacunarity lacunarity value(Determines how finer the next octaves should be) Lacunarity>1
          @param persistence persistence value(Controls how fast the next octave will die out) 0<Persistence<1
          @return turbulence value
          */
          DllExport double turbulence(double x, double y, double z, int octaves ,float f, float amplitude, float lacunarity,float persistence);

     private:
     /**  @Brief Smoothstep function
          @param val value that we want to use the smoothstep on
          @return smoothstep value
     */
          DllExport double fade(double val);
          
     /**  @Brief Interpolation function
          @param val value that we want to interpolated
          @param a first border of the interpolation
          @param b second border of the interpolation
          @return interpolated value
     */
          DllExport  double lerp(double val, double a, double b);
          
     //Calculate the gradiant
     /**@Brief Gradient function
          @param hash hashing value
          @param x x-coordinate value
          @param y y-coordinate value
          @param z z-coordinate value
     */
          DllExport double grad(int hash, double x, double y, double z);
     };
}
