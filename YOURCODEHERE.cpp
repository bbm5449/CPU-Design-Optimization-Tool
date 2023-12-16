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

using namespace std;


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
    unsigned int il1blocksize = 8 * configurationDimsAsInts[0];
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
      cout << "fail" << endl;
      cout << "offset: " << offset << endl;
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
  
  produces an essentially random proposal
  std::stringstream ss;
  for(int dim = 0; dim<17; ++dim){
    ss << rand()%GLOB_dimensioncardinality[dim] << " ";
  } 
  ss << rand()%GLOB_dimensioncardinality[17];
  nextconfiguration=ss.str();
  ss.str("");    
  std::cout << nextconfiguration << std::endl;
  return nextconfiguration;
}

