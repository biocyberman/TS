/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#ifndef SINGLEFLOWFIT_H
#define SINGLEFLOWFIT_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "BkgMagicDefines.h"
#include "BkgFitMatrixPacker.h"  // this is a bad way of making sure LAPACK is here
#include "MathOptim.h"
#include "DiffEqModel.h"
#include "MultiFlowModel.h"
#include "Utils.h"
#include "BeadParams.h"
#include "BeadTracker.h"
#include "RegionParams.h"
#include "RegionTracker.h"
#include "EmphasisVector.h"
// this is a bit kludgey, but to make things easy, the single-flow lev mar fitter
// uses struct bead_params and struct reg_params...so this include needs to be below
// those definitions

#define AMPLITUDE 0
#define KMULT 1

#include "BkgModSingleFlowFit.h"
#include "ProjectionSearchFit.h"



class single_flow_optimizer
{
  public:
    PoissonCDFApproxMemo *math_poiss;
    // object used to fit a single well's data in a single flow
    BkgModSingleFlowFit *oneFlowFit;
    //BkgModSingleFlowFitKrate *oneFlowFitKrate;
    BkgModSingleFlowFit *oneFlowFitKrate;
    
   ProjectionSearchOneFlow *ProjectionFit;

   
    // keep these around to avoid allocating when I need to talk to the above objects
    float max_param[2];
    float min_param[2];
    float val_param[2];

    
    float decision_threshold;
    bool var_kmult_only;

    bool use_fval_cache;

    bool fit_alt;
    int cur_hits;
    
    single_flow_optimizer();
    ~single_flow_optimizer();
    void SetUpperLimitAmplFit(float AmplLim,float krateLim);
    void SetLowerLimitAmplFit(float AmplLim,float krateLim);
    void AllocLevMar(TimeCompression &time_c, PoissonCDFApproxMemo *math_poiss, float damp_kmult, bool var_kmult_only, float kmult_low_limit, float kmult_hi_limit);
    void Delete();

    // picks from the below options
    void FitOneFlow (int fnum, float *evect, bead_params *p,  error_track *err_t, float *signal_corrected, int NucID, float *lnucRise, int l_i_start,
                                        flow_buffer_info &my_flow, TimeCompression &time_c, EmphasisClass &emphasis_data,RegionTracker &my_regions);
    // my different optimizers
    void FitKrateOneFlow(int fnum, float *evect, 
                                            bead_params *p, error_track *err_t, float *signal_corrected, int NucID, float *lnucRise, 
                                            int l_i_start, flow_buffer_info &my_flow, TimeCompression &time_c,
                                            EmphasisClass &emphasis_data,RegionTracker &my_regions);
                                            
    void FitThisOneFlow(int fnum, float *evect, bead_params *p,  error_track *err_t, float *signal_corrected, int NucID, float *lnucRise, int l_i_start,
                                           flow_buffer_info &my_flow, TimeCompression &time_c, EmphasisClass &emphasis_data,RegionTracker &my_regions);

                                    
    void FitProjection(int fnum, float *evect, bead_params *p,  error_track *err_t, float *signal_corrected, int NucID, float *lnucRise, int l_i_start,
                                           flow_buffer_info &my_flow, TimeCompression &time_c, EmphasisClass &emphasis_data,RegionTracker &my_regions);
                                           
    void FillDecisionThreshold(float nuc_threshold);
    
                                      
    void SetProjectionSearchEnable(bool enable)
    {
        use_projection_search_ampl_fit = enable;
    }

    void   SetRetryLimit(int _retry_limit)
    {
        retry_limit = _retry_limit;
    }

  protected:
    bool use_projection_search_ampl_fit;
    int retry_limit;

};



#endif // SINGLEFLOWFIT_H