/******************************************************
 * This is the main file for the mips ArchC model     *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 

const char *project_name="mips";
const char *project_file="mips.ac";
const char *archc_version="2.2";
const char *archc_options="-abi ";

#include  <iostream>
#include  <systemc.h>
#include  "ac_stats_base.H"
#include  "mips.H"


#include  "ac_tlm_mem.h"
#include  "ac_tlm_router.h"
#include  "ac_tlm_fpu.h"

using user::ac_tlm_mem;
using user::ac_tlm_router;
using user::ac_tlm_fpu;

int sc_main(int ac, char *av[])
{

  FILE *parameterFile;
  printf("av[1] = %s\n", av[1]);
  parameterFile = fopen(av[1], "r");
  
  int nproc;
  fscanf(parameterFile, " %d", &nproc);
  printf("number of processors: %d\n", nproc);

  
  char outputFileName[30];
  fscanf(parameterFile, " %s", outputFileName);
  printf("outputFile: %s\n", outputFileName);
  

  int numberOfSamples;
  fscanf(parameterFile, " %d", &numberOfSamples);
  printf("number of samples: %d\n", numberOfSamples);
  
  int preset;
  fscanf(parameterFile, " %d", &preset);
  printf("preset: %d\n", preset);
  
  
  //!  ISA simulator
  mips mips_proc1("mips");

  mips *mips_proc2, *mips_proc3, *mips_proc4;
  if(nproc > 1){
    mips_proc2 = new mips("mips2");
  }
  if(nproc > 2){
    mips_proc3 = new mips("mips3");
    mips_proc4 = new mips("mips4");
  }
  
  
  ac_tlm_mem mem("mem", 100*1024*1024);
  ac_tlm_router router("router");
  ac_tlm_fpu fpu("fpu");

  router.MEM_port(mem.target_export);
  router.FPU_port(fpu.target_export);

  mips_proc1.DM_port(router.target_export);
  if(nproc > 1){
    mips_proc2->DM_port(router.target_export);
  }
  if(nproc > 2){
    mips_proc3->DM_port(router.target_export);
    mips_proc4->DM_port(router.target_export);
  }
  
  

#ifdef AC_DEBUG
  ac_trace("mips_proc1.trace");
#endif 

  int ac1 = 6;
  char strNProc[10];
  sprintf(strNProc, "%d", nproc);

  char strNumberOfSamples[10];
  sprintf(strNumberOfSamples, "%d", numberOfSamples);
  
  char strPreset[10];
  sprintf(strPreset, "%d", preset);

  
  /*char *av1[] = {"mips.x", "--load=mandel.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av2[] = {"mips.x", "--load=mandel.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av3[] = {"mips.x", "--load=mandel.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av4[] = {"mips.x", "--load=mandel.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};*/

  char *av1[] = {"mips.x", "--load=mandel_hard.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av2[] = {"mips.x", "--load=mandel_hard.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av3[] = {"mips.x", "--load=mandel_hard.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};
  char *av4[] = {"mips.x", "--load=mandel_hard.mips", outputFileName, strNumberOfSamples, strPreset, strNProc};

  
  mips_proc1.init(ac1, av1);
  mips_proc1.set_instr_batch_size(1);
  if(nproc > 1){
     mips_proc2->init(ac1, av2);
     mips_proc2->set_instr_batch_size(1);
  }
  if(nproc > 2){
    mips_proc3->init(ac1, av3);
    mips_proc3->set_instr_batch_size(1);
    mips_proc4->init(ac1, av4);
    mips_proc4->set_instr_batch_size(1);
  }
  
  cerr << endl;

  sc_start();

  mips_proc1.PrintStat();
  if(nproc > 1){
    mips_proc2->PrintStat();
  }
  if(nproc > 2){
    mips_proc3->PrintStat();
    mips_proc4->PrintStat();
  }
  
  cerr << endl;
  
  fpu.print_counters(nproc);

#ifdef AC_STATS
  ac_stats_base::print_all_stats(std::cerr);
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  int ret = mips_proc1.ac_exit_status;
  ret += (nproc > 1) ? mips_proc2->ac_exit_status : 0;
  ret += (nproc > 2) ? mips_proc3->ac_exit_status + mips_proc4->ac_exit_status : 0;
  return ret;
}
