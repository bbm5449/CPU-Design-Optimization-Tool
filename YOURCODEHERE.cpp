#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <math.h>
#include <fcntl.h>

#include "431project.h"
#include "431projectUtils.h"


/*
 * Returns 1 if valid, else 0
 */
int validateConfiguration(std::string configuration){
  int configurationDimsAsInts[18];
  int returnValue=1; // assume true, set to zero otherwise
  if(isan18dimconfiguration(configuration)){ // necessary, but insufficient
    extractConfiguration(configuration, configurationDimsAsInts); // Configuration parameters now available in array
    // FIXME - YOUR CODE HERE 
    // The ul2 block size must be at least twice your il1 (dl1) block size with a maximum block size of 128B
    unsigned int il1blocksize = 8 * (1 << configurationDimsAsInts[0]);
    unsigned int l2blocksize =  16 << configurationDimsAsInts[11];
    if (l2blocksize < 2*il1blocksize) {
      returnValue = 0;
    }
    // ul2 must be at least as large as il1 + dl1
    if (getl2size(configuration) < getil1size(configuration) + getdl1size(configuration)) {
        returnValue = 0;
    }
    // The il1 sizes and il1 latencies are linked as follows (the same linkages hold for the dl1 size and dl1 latency)
    int offset = 0;
    unsigned int dl1size = getdl1size(configuration);
    switch(1 << configurationDimsAsInts[7]){
      case 1: offset = 0;
        break;
      case 2: offset = 1;
        break;
      case 4: offset = 2;
        break;
    }
    if (dl1size < 8*1024 || dl1size > 64*1024){
      returnValue = 0;
    }
    else if (dl1size == 8*1024 && (configurationDimsAsInts[14] + 1) != (1 + offset)){
      returnValue = 0;
    } else if (dl1size == 16*1024 && (configurationDimsAsInts[14] + 1) != (2 + offset)){
      returnValue = 0;
    }
    else if (dl1size == 32*1024 && (configurationDimsAsInts[14] + 1) != (3 + offset)){
      returnValue = 0;
    }
    else if (dl1size == 64*1024 && (configurationDimsAsInts[14] + 1) != (4 + offset)){
      returnValue = 0;
    }
    unsigned int il1size = getil1size(configuration);
    switch(1 << configurationDimsAsInts[9]){
      case 1: offset = 0;
        break;
      case 2: offset = 1;
        break;
      case 4: offset = 2;
        break;
    }
    if (il1size < 8*1024 || il1size > 64*1024){
      returnValue = 0;
    }
    else if (il1size == 8*1024 && (configurationDimsAsInts[15] + 1) != (1 + offset)){
      returnValue = 0;
    } else if (il1size == 16*1024 && (configurationDimsAsInts[15] + 1) != (2 + offset)){
      returnValue = 0;
    }
    else if (il1size == 32*1024 && (configurationDimsAsInts[15] + 1) != (3 + offset)){
      returnValue = 0;
    }
    else if (il1size == 64*1024 && (configurationDimsAsInts[15] + 1) != (4 + offset)){
      returnValue = 0;
    }
    // The ul2 sizes and ul2 latencies are linked as follows
    unsigned int l2size = getl2size(configuration);
    switch(1 << configurationDimsAsInts[12]){
      case 1: offset = -2;
        break;
      case 2: offset = -1;
        break;
      case 4: offset = 0;
        break;
      case 8: offset = 1;
        break;
    }
    if (l2size < 128*1024 || l2size > 2048*1024){
      returnValue = 0;
    }
    else if (l2size == 128*1024 && (configurationDimsAsInts[16] + 5) != (7 + offset)){
      returnValue = 0;
    } else if (l2size == 256*1024 && (configurationDimsAsInts[16] + 5) != (8 + offset)){
      returnValue = 0;
    }
    else if (l2size == 512*1024 && (configurationDimsAsInts[16] + 5) != (9 + offset)){
      returnValue = 0;
    }
    else if (l2size == 1024*1024 && (configurationDimsAsInts[16] + 5) != (10 + offset)){
      returnValue = 0;
    }
    else if (l2size == 2048*1024 && (configurationDimsAsInts[16] + 5) != (11 + offset)){
      returnValue = 0;
    }
  } else {
    returnValue=0;
  }
  return returnValue;
}




/*
 * Given the current best known configuration, the current configuration, and the globally visible map of all previously investigated configurations, suggest a previously unexplored design point. You will only be allowed to investigate 1000 design points in a particular run, so choose wisely.
 */
std::string YourProposalFunction(std::string currentconfiguration, std::string bestEXECconfiguration, std::string bestEDPconfiguration, int optimizeforEXEC, int optimizeforEDP){
  std::string nextconfiguration=GLOB_baseline;
  /*
   * REPLACE THE BELOW CODE WITH YOUR PROPOSAL FUNCTION
   *
   * The proposal function below is extremely unintelligent and
   * will produce configurations that, while properly formatted, violate specified project constraints
   */    
  
  // produces an essentially random proposal
  std::stringstream ss;
  int configurationDimsAsInts[18] = {0};
  int offset = 0;
  unsigned int dl1size = 0;
  unsigned int il1size = 0;
  unsigned int l2size = 0;
  if (optimizeforEDP){
    for(int dim = 0; dim<17; ++dim){
      switch(dim){
        case 0:
          configurationDimsAsInts[0] = rand()%3;
          ss << configurationDimsAsInts[0] << " ";
          break;
        case 1:
          configurationDimsAsInts[1] = rand()%2;
          ss << configurationDimsAsInts[1] << " ";
          break;
        case 2:
          configurationDimsAsInts[2] = rand()%2;
          ss << configurationDimsAsInts[2] << " ";
          break;
        case 3:
          configurationDimsAsInts[3] = rand()%4 + 1;
          ss << configurationDimsAsInts[3] << " ";
          break;
        case 4:
          configurationDimsAsInts[4] = rand()%4;
          ss << configurationDimsAsInts[4] << " ";
          break;
        case 5:
          configurationDimsAsInts[5] = rand()%2;
          ss << configurationDimsAsInts[5] << " ";
          break;
        case 6:
          switch(configurationDimsAsInts[0]){
            case 0:
              configurationDimsAsInts[6] = rand()%6 + 3;
              break;
            case 1:
              configurationDimsAsInts[6] = rand()%6 + 2;
              break;
            case 2:
              configurationDimsAsInts[6] = rand()%6 + 1;
              break;
          }
          ss << configurationDimsAsInts[6] << " ";
          break;
        case 7:
          switch(8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[6])){
            case 2048:
              configurationDimsAsInts[7] = 2;
              break;
            case 4096:
              configurationDimsAsInts[7] = rand()%2+1;
              break;
            case 32768:
              configurationDimsAsInts[7] = rand()%2;
              break;
            case 65536:
              configurationDimsAsInts[7] = 0;
              break;
            default: 
              configurationDimsAsInts[7] = rand()%3;
          }
          ss << configurationDimsAsInts[7] << " ";
          break;
        case 8:
          switch(configurationDimsAsInts[0]){
            case 0:
              configurationDimsAsInts[8] = rand()%6 + 3;
              break;
            case 1:
              configurationDimsAsInts[8] = rand()%6 + 2;
              break;
            case 2:
              configurationDimsAsInts[8] = rand()%6 + 1;
              break;
          }
          ss << configurationDimsAsInts[8] << " ";
          break;
        case 9:
          switch(8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[7])){
            case 2048:
              configurationDimsAsInts[9] = 2;
              break;
            case 4096:
              configurationDimsAsInts[9] = rand()%2+1;
              break;
            case 32768:
              configurationDimsAsInts[9] = rand()%2;
              break;
            case 65536:
              configurationDimsAsInts[9] = 0;
              break;
            default: 
              configurationDimsAsInts[9] = rand()%3;
          }
          ss << configurationDimsAsInts[9] << " ";
          break;
        case 10:
          configurationDimsAsInts[10] = rand()%8 + 2;
          ss << configurationDimsAsInts[10] << " ";
          break;
        case 11:
          configurationDimsAsInts[11] = configurationDimsAsInts[0];
          ss << configurationDimsAsInts[11] << " ";
          break;
        case 12:
          configurationDimsAsInts[12] = rand()%5;
          ss << configurationDimsAsInts[12] << " ";
          break;
        case 13:
          configurationDimsAsInts[13] = 2;
          ss << configurationDimsAsInts[13] << " ";
          break;
        case 14:
          dl1size = 8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[6])*(1 << configurationDimsAsInts[7]);
          switch(1 << configurationDimsAsInts[7]){
            case 1: offset = 0;
              break;
            case 2: offset = 1;
              break;
            case 4: offset = 2;
              break;
          }
          if (dl1size == 8*1024){
            configurationDimsAsInts[14] = offset;
          } else if (dl1size == 16*1024){
            configurationDimsAsInts[14] = 1 + offset;
          }
          else if (dl1size == 32*1024){
            configurationDimsAsInts[14] = 2 + offset;
          }
          else if (dl1size == 64*1024){
            configurationDimsAsInts[14] = 3 + offset;
          }
          ss << configurationDimsAsInts[14] << " ";
          break;
        case 15:
          il1size = 8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[8])*(1 << configurationDimsAsInts[9]);
          switch(1 << configurationDimsAsInts[9]){
            case 1: offset = 0;
              break;
            case 2: offset = 1;
              break;
            case 4: offset = 2;
              break;
          }
          if (il1size == 8*1024){
            configurationDimsAsInts[15] = offset;
          } else if (il1size == 16*1024){
            configurationDimsAsInts[15] = 1 + offset;
          }
          else if (il1size == 32*1024){
            configurationDimsAsInts[15] = 2 + offset;
          }
          else if (il1size == 64*1024){
            configurationDimsAsInts[15] = 3 + offset;
          }
          ss << configurationDimsAsInts[15] << " ";
          break;
        case 16:
          l2size = (256 << configurationDimsAsInts[10])*(16 << configurationDimsAsInts[11])*(1 << configurationDimsAsInts[12]);
          switch(1 << configurationDimsAsInts[12]){
            case 1: offset = -2;
              break;
            case 2: offset = -1;
              break;
            case 4: offset = 0;
              break;
            case 8: offset = 1;
              break;
            case 16: offset = 2;
              break;
          }
          if (l2size == 128*1024){
            configurationDimsAsInts[16] = 2 + offset;
          } else if (l2size == 256*1024){
            configurationDimsAsInts[16] = 3 + offset;
          }
          else if (l2size == 512*1024){
            configurationDimsAsInts[16] = 4 + offset;
          }
          else if (l2size == 1024*1024){
            configurationDimsAsInts[16] = 5 + offset;
          }
          else if (l2size == 2048*1024){
            configurationDimsAsInts[16] = 6 + offset;
          }
          else{
            configurationDimsAsInts[16] = 0;
          }
          ss << configurationDimsAsInts[16] << " ";
          break;
        }
    } 
    ss << rand() % GLOB_dimensioncardinality[17];
    nextconfiguration=ss.str();
    ss.str("");  
  } else{
    for(int dim = 0; dim<17; ++dim){
      switch(dim){
        case 0:
          configurationDimsAsInts[0] = 2+rand()%2;
          ss << configurationDimsAsInts[0] << " ";
          break;
        case 1:
          configurationDimsAsInts[1] = rand()%2;
          ss << configurationDimsAsInts[1] << " ";
          break;
        case 2:
          configurationDimsAsInts[2] = 1;
          ss << configurationDimsAsInts[2] << " ";
          break;
        case 3:
          configurationDimsAsInts[3] = rand()%4 + 2;
          ss << configurationDimsAsInts[3] << " ";
          break;
        case 4:
          configurationDimsAsInts[4] = rand()%2 + 2;
          ss << configurationDimsAsInts[4] << " ";
          break;
        case 5:
          configurationDimsAsInts[5] = rand()%2;
          ss << configurationDimsAsInts[5] << " ";
          break;
        case 6:
          switch(configurationDimsAsInts[0]){
            case 2:
              configurationDimsAsInts[6] = rand()%6 + 1;
              break;
            case 3:
              configurationDimsAsInts[6] = rand()%6;
              break;
          }
          ss << configurationDimsAsInts[6] << " ";
          break;
        case 7:
          switch(8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[6])){
            case 2*1024:
              configurationDimsAsInts[7] = 2;
              break;
            case 4*1024:
              configurationDimsAsInts[7] = 1+rand()%2;
              break;
            case 32*1024:
              configurationDimsAsInts[7] = rand()%2;
              break;
            case 64*1024:
              configurationDimsAsInts[7] = 0;
              break;
            default: 
              configurationDimsAsInts[7] = rand()%3;
          }
          ss << configurationDimsAsInts[7] << " ";
          break;
        case 8:
          switch(configurationDimsAsInts[0]){
            case 2:
              configurationDimsAsInts[8] = rand()%6 + 1;
              break;
            case 3:
              configurationDimsAsInts[8] = rand()%6;
              break;
          }
          ss << configurationDimsAsInts[8] << " ";
          break;
        case 9:
          switch(8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[7])){
            case 2*1024:
              configurationDimsAsInts[9] = 2;
              break;
            case 4*1024:
              configurationDimsAsInts[9] = 1+rand()%2;
              break;
            case 32*1024:
              configurationDimsAsInts[9] = rand()%2;
              break;
            case 64*1024:
              configurationDimsAsInts[9] = 0;
              break;
            default: 
              configurationDimsAsInts[9] = rand()%3;
          }
          ss << configurationDimsAsInts[9] << " ";
          break;
        case 10:
          configurationDimsAsInts[10] = rand()%8 + 2;
          ss << configurationDimsAsInts[10] << " ";
          break;
        case 11:
          configurationDimsAsInts[11] = configurationDimsAsInts[0];
          ss << configurationDimsAsInts[11] << " ";
          break;
        case 12:
          configurationDimsAsInts[12] = rand()%5;
          ss << configurationDimsAsInts[12] << " ";
          break;
        case 13:
          configurationDimsAsInts[13] = rand()%3 + 2;
          ss << configurationDimsAsInts[13] << " ";
          break;
        case 14:
          dl1size = 8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[6])*(1 << configurationDimsAsInts[7]);
          switch(1 << configurationDimsAsInts[7]){
            case 1: offset = 0;
              break;
            case 2: offset = 1;
              break;
            case 4: offset = 2;
              break;
          }
          if (dl1size == 8*1024){
            configurationDimsAsInts[14] = offset;
          } else if (dl1size == 16*1024){
            configurationDimsAsInts[14] = 1 + offset;
          }
          else if (dl1size == 32*1024){
            configurationDimsAsInts[14] = 2 + offset;
          }
          else if (dl1size == 64*1024){
            configurationDimsAsInts[14] = 3 + offset;
          }
          ss << configurationDimsAsInts[14] << " ";
          break;
        case 15:
          il1size = 8*(1 << configurationDimsAsInts[0])*(32 << configurationDimsAsInts[8])*(1 << configurationDimsAsInts[9]);
          switch(1 << configurationDimsAsInts[9]){
            case 1: offset = 0;
              break;
            case 2: offset = 1;
              break;
            case 4: offset = 2;
              break;
          }
          if (il1size == 8*1024){
            configurationDimsAsInts[15] = offset;
          } else if (il1size == 16*1024){
            configurationDimsAsInts[15] = 1 + offset;
          }
          else if (il1size == 32*1024){
            configurationDimsAsInts[15] = 2 + offset;
          }
          else if (il1size == 64*1024){
            configurationDimsAsInts[15] = 3 + offset;
          }
          ss << configurationDimsAsInts[15] << " ";
          break;
        case 16:
          l2size = (256 << configurationDimsAsInts[10])*(16 << configurationDimsAsInts[11])*(1 << configurationDimsAsInts[12]);
          switch(1 << configurationDimsAsInts[12]){
            case 1: offset = -2;
              break;
            case 2: offset = -1;
              break;
            case 4: offset = 0;
              break;
            case 8: offset = 1;
              break;
            case 16: offset = 2;
              break;
          }
          if (l2size == 128*1024){
            configurationDimsAsInts[16] = 2 + offset;
          } else if (l2size == 256*1024){
            configurationDimsAsInts[16] = 3 + offset;
          }
          else if (l2size == 512*1024){
            configurationDimsAsInts[16] = 4 + offset;
          }
          else if (l2size == 1024*1024){
            configurationDimsAsInts[16] = 5 + offset;
          }
          else if (l2size == 2048*1024){
            configurationDimsAsInts[16] = 6 + offset;
          }
          else{
            configurationDimsAsInts[16] = 0;
          }
          ss << configurationDimsAsInts[16] << " ";
          break;
        }
    } 
    int numbers[] = {0, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    ss << numbers[rand() % size];
    nextconfiguration=ss.str();
    ss.str("");  
  }

  // std::cout << GLOB_baseline.size() << std::endl;
  // std::cout << nextconfiguration.size() << std::endl;
  return nextconfiguration;
}

