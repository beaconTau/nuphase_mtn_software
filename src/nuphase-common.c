#include "nuphase-common.h" 
#include <stdio.h> 
#include <time.h> 
#include <stdlib.h> 
#include <sys/stat.h> 



float timespec_difference_float(const struct timespec * a, const struct timespec * b) 
{

  float sec_diff = a->tv_sec - b->tv_sec; 
  float nanosec_diff = a->tv_nsec - b->tv_nsec; 
  return sec_diff + 1e-9 * (nanosec_diff); 
} 


int nuphase_get_cfg_file(char ** name, nuphase_program_t p) 
{
  switch (p) 
  {
    case NUPHASE_STARTUP: 
      asprintf(name, "%s/%s", getenv(CONFIG_DIR_ENV) ?: "." , CONFIG_DIR_STARTUP_NAME); 
    case NUPHASE_HK: 
      asprintf(name, "%s/%s", getenv(CONFIG_DIR_ENV) ?: "." , CONFIG_DIR_HK_NAME); 
    case NUPHASE_ACQ: 
      asprintf(name, "%s/%s", getenv(CONFIG_DIR_ENV) ?: "." , CONFIG_DIR_ACQ_NAME); 
    case NUPHASE_COPY: 
      asprintf(name, "%s/%s", getenv(CONFIG_DIR_ENV) ?: "." , CONFIG_DIR_COPY_NAME); 
    default: 
      return -1; 
  }
  return 0; 
} 

int mkdir_if_needed(const char * path)
{

  struct stat st; 
  if ( stat(path,&st) || ( (st.st_mode & S_IFMT) != S_IFDIR))//not there, try to make it
  {
     return mkdir(path,0666);
  }

  return 0; 

}


