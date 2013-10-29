#pragma once

#include "global.h"

extern "C"
void initSegmentArray(uint *segments, uint  *seg_length, uint *seg_index, uint *seg_offset, int size, const cudaDeviceProp *devProp);
