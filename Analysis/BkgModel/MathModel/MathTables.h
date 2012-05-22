/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
/*
 * MathTables.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Mark Beauchemin
 */

#ifndef MATHTABLES_H
#define MATHTABLES_H


// Keep annoying tables in someplace readable


static const float ErfApproxArray[] ={
0.000000,
0.011283,
0.022565,
0.033841,
0.045111,
0.056372,
0.067622,
0.078858,
0.090078,
0.101281,
0.112463,
0.123623,
0.134758,
0.145867,
0.156947,
0.167996,
0.179012,
0.189992,
0.200936,
0.211840,
0.222703,
0.233522,
0.244296,
0.255023,
0.265700,
0.276326,
0.286900,
0.297418,
0.307880,
0.318283,
0.328627,
0.338908,
0.349126,
0.359279,
0.369365,
0.379382,
0.389330,
0.399206,
0.409009,
0.418739,
0.428392,
0.437969,
0.447468,
0.456887,
0.466225,
0.475482,
0.484655,
0.493745,
0.502750,
0.511668,
0.520500,
0.529244,
0.537899,
0.546464,
0.554939,
0.563323,
0.571616,
0.579816,
0.587923,
0.595936,
0.603856,
0.611681,
0.619411,
0.627046,
0.634586,
0.642029,
0.649377,
0.656628,
0.663782,
0.670840,
0.677801,
0.684666,
0.691433,
0.698104,
0.704678,
0.711156,
0.717537,
0.723822,
0.730010,
0.736103,
0.742101,
0.748003,
0.753811,
0.759524,
0.765143,
0.770668,
0.776100,
0.781440,
0.786687,
0.791843,
0.796908,
0.801883,
0.806768,
0.811564,
0.816271,
0.820891,
0.825424,
0.829870,
0.834232,
0.838508,
0.842701,
0.846810,
0.850838,
0.854784,
0.858650,
0.862436,
0.866144,
0.869773,
0.873326,
0.876803,
0.880205,
0.883533,
0.886788,
0.889971,
0.893082,
0.896124,
0.899096,
0.902000,
0.904837,
0.907608,
0.910314,
0.912956,
0.915534,
0.918050,
0.920505,
0.922900,
0.925236,
0.927514,
0.929734,
0.931899,
0.934008,
0.936063,
0.938065,
0.940015,
0.941914,
0.943762,
0.945561,
0.947312,
0.949016,
0.950673,
0.952285,
0.953852,
0.955376,
0.956857,
0.958297,
0.959695,
0.961054,
0.962373,
0.963654,
0.964898,
0.966105,
0.967277,
0.968413,
0.969516,
0.970586,
0.971623,
0.972628,
0.973603,
0.974547,
0.975462,
0.976348,
0.977207,
0.978038,
0.978843,
0.979622,
0.980376,
0.981105,
0.981810,
0.982493,
0.983153,
0.983790,
0.984407,
0.985003,
0.985578,
0.986135,
0.986672,
0.987190,
0.987691,
0.988174,
0.988641,
0.989091,
0.989525,
0.989943,
0.990347,
0.990736,
0.991111,
0.991472,
0.991821,
0.992156,
0.992479,
0.992790,
0.993090,
0.993378,
0.993656,
0.993923,
0.994179,
0.994426,
0.994664,
0.994892,
0.995111,
0.995322,
0.995525,
0.995719,
0.995906,
0.996086,
0.996258,
0.996423,
0.996582,
0.996734,
0.996880,
0.997021,
0.997155,
0.997284,
0.997407,
0.997525,
0.997639,
0.997747,
0.997851,
0.997951,
0.998046,
0.998137,
0.998224,
0.998308,
0.998388,
0.998464,
0.998537,
0.998607,
0.998674,
0.998738,
0.998799,
0.998857,
0.998912,
0.998966,
0.999016,
0.999065,
0.999111,
0.999155,
0.999197,
0.999237,
0.999275,
0.999311,
0.999346,
0.999379,
0.999411,
0.999441,
0.999469,
0.999497,
0.999523,
0.999547,
0.999571,
0.999593,
0.999614,
0.999635,
0.999654,
0.999672,
0.999689,
0.999706,
0.999722,
0.999736,
0.999751,
0.999764,
0.999777,
0.999789,
0.999800,
0.999811,
0.999822,
0.999831,
0.999841,
0.999849,
0.999858,
0.999866,
0.999873,
0.999880,
0.999887,
0.999893,
0.999899,
0.999905,
0.999910,
0.999916,
0.999920,
0.999925,
0.999929,
0.999933,
0.999937,
0.999941,
0.999944,
0.999948,
0.999951,
0.999954,
0.999956,
0.999959,
0.999961,
0.999964,
0.999966,
0.999968,
0.999970,
0.999972,
0.999973,
0.999975,
0.999976,
0.999978
};

#if 0
double ErfAprox(double a)
{
  double rc;
  unsigned int index;

//  a = 100;
  if(a >= 0)
    index = (int)a*100;
  else
    index = (int)(-a*100);

  if(index >= (sizeof(ErfApproxArray)/sizeof(double)))
    index = (sizeof(ErfApproxArray)/sizeof(double))-1;

  rc = ErfApproxArray[index];

  if(a < 0)
    rc = -rc;

  return rc;
}
#endif

static const float Exp2ApproxArray[] =
{
  1.000000,0.999900,0.999600,0.999100,0.998401,0.997503,0.996406,0.995112,
  0.993620,0.991933,0.990050,0.987973,0.985703,0.983242,0.980591,0.977751,
  0.974725,0.971514,0.968119,0.964544,0.960789,0.956858,0.952753,0.948475,
  0.944027,0.939413,0.934634,0.929694,0.924595,0.919339,0.913931,0.908373,
  0.902668,0.896820,0.890831,0.884706,0.878447,0.872057,0.865541,0.858902,
  0.852144,0.845269,0.838283,0.831187,0.823987,0.816686,0.809288,0.801797,
  0.794216,0.786549,0.778801,0.770974,0.763074,0.755104,0.747067,0.738968,
  0.730811,0.722600,0.714337,0.706028,0.697676,0.689285,0.680859,0.672401,
  0.663916,0.655406,0.646876,0.638330,0.629770,0.621201,0.612626,0.604049,
  0.595473,0.586900,0.578336,0.569783,0.561244,0.552722,0.544221,0.535743,
  0.527292,0.518871,0.510482,0.502128,0.493812,0.485537,0.477305,0.469118,
  0.460980,0.452893,0.444858,0.436879,0.428956,0.421094,0.413292,0.405555,
  0.397882,0.390276,0.382740,0.375274,0.367879,0.360559,0.353313,0.346144,
  0.339053,0.332040,0.325107,0.318256,0.311486,0.304800,0.298197,0.291679,
  0.285247,0.278901,0.272641,0.266468,0.260383,0.254387,0.248478,0.242659,
  0.236928,0.231286,0.225734,0.220270,0.214896,0.209611,0.204416,0.199309,
  0.194291,0.189361,0.184520,0.179766,0.175100,0.170520,0.166028,0.161621,
  0.157300,0.153064,0.148912,0.144844,0.140858,0.136955,0.133134,0.129393,
  0.125732,0.122151,0.118647,0.115221,0.111872,0.108598,0.105399,0.102274,
  0.099222,0.096241,0.093331,0.090491,0.087720,0.085017,0.082381,0.079811,
  0.077305,0.074863,0.072483,0.070165,0.067908,0.065710,0.063571,0.061489,
  0.059463,0.057493,0.055576,0.053713,0.051902,0.050142,0.048432,0.046771,
  0.045157,0.043591,0.042071,0.040595,0.039164,0.037775,0.036429,0.035123,
  0.033857,0.032631,0.031442,0.030291,0.029176,0.028097,0.027052,0.026041,
  0.025062,0.024116,0.023200,0.022315,0.021459,0.020632,0.019833,0.019061,
  0.018316,0.017596,0.016901,0.016230,0.015583,0.014958,0.014356,0.013775,
  0.013215,0.012675,0.012155,0.011654,0.011171,0.010707,0.010259,0.009828,
  0.009414,0.009015,0.008631,0.008262,0.007907,0.007566,0.007238,0.006923,
  0.006620,0.006330,0.006051,0.005783,0.005525,0.005279,0.005042,0.004815,
  0.004597,0.004388,0.004188,0.003996,0.003812,0.003636,0.003467,0.003306,
  0.003151,0.003003,0.002862,0.002726,0.002596,0.002473,0.002354,0.002241,
  0.002133,0.002029,0.001930,0.001836,0.001746,0.001660,0.001578,0.001500,
  0.001425,0.001354,0.001286,0.001221,0.001159,0.001100,0.001044,0.000991,
  0.000940,0.000892,0.000845,0.000802,0.000760,0.000720,0.000682,0.000646,
  0.000612,0.000580,0.000549,0.000520,0.000492,0.000465,0.000440,0.000416,
  0.000394,0.000372,0.000352,0.000332,0.000314,0.000297,0.000280,0.000265,
  0.000250,0.000236,0.000223,0.000210,0.000198,0.000187,0.000176,0.000166,
  0.000157,0.000148,0.000139,0.000131,0.000123,0.000116,0.000109,0.000103,
  0.000097,0.000091,0.000086,0.000081,0.000076,0.000071,0.000067,0.000063,
  0.000059,0.000056,0.000052,0.000049,0.000046,0.000043,0.000041,0.000038,
  0.000036,0.000033,0.000031,0.000029,0.000028,0.000026,0.000024,0.000023,
  0.000021,0.000020,0.000019,0.000017,0.000016,0.000015,0.000014,0.000013,
  0.000013,0.000012,0.000011,0.000010,0.000010,0.000009,0.000008,0.000008,
  0.000007,0.000007,0.000006,0.000006,0.000006,0.000005,0.000005,0.000004,
  0.000004,0.000004,0.000004,0.000003,0.000003,0.000003,0.000003,0.000003,
  0.000002,0.000002,0.000002,0.000002,0.000002,0.000002,0.000002,0.000001,
  0.000001,0.000001,0.000001,0.000001,0.000001,0.000001,0.000001,0.000001,
  0.000001,0.000001,0.000001,0.000001,0.000001,0.000000,0.000000,0.000000,
  0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
  0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
  0.000000
};


static const float ExpApproxArray[]={
1.000000000,0.990049834,0.980198673,0.970445534,0.960789439,0.951229425,0.941764534,0.932393820,
0.923116346,0.913931185,0.904837418,0.895834135,0.886920437,0.878095431,0.869358235,0.860707976,
0.852143789,0.843664817,0.835270211,0.826959134,0.818730753,0.810584246,0.802518798,0.794533603,
0.786627861,0.778800783,0.771051586,0.763379494,0.755783741,0.748263568,0.740818221,0.733446956,
0.726149037,0.718923733,0.711770323,0.704688090,0.697676326,0.690734331,0.683861409,0.677056874,
0.670320046,0.663650250,0.657046820,0.650509095,0.644036421,0.637628152,0.631283646,0.625002268,
0.618783392,0.612626394,0.606530660,0.600495579,0.594520548,0.588604970,0.582748252,0.576949810,
0.571209064,0.565525439,0.559898367,0.554327285,0.548811636,0.543350869,0.537944438,0.532591801,
0.527292424,0.522045777,0.516851334,0.511708578,0.506616992,0.501576069,0.496585304,0.491644197,
0.486752256,0.481908990,0.477113916,0.472366553,0.467666427,0.463013068,0.458406011,0.453844795,
0.449328964,0.444858066,0.440431655,0.436049286,0.431710523,0.427414932,0.423162082,0.418951549,
0.414782912,0.410655753,0.406569660,0.402524224,0.398519041,0.394553710,0.390627835,0.386741023,
0.382892886,0.379083038,0.375311099,0.371576691,0.367879441,0.364218980,0.360594940,0.357006961,
0.353454682,0.349937749,0.346455810,0.343008517,0.339595526,0.336216494,0.332871084,0.329558961,
0.326279795,0.323033256,0.319819022,0.316636769,0.313486181,0.310366941,0.307278739,0.304221264,
0.301194212,0.298197279,0.295230167,0.292292578,0.289384218,0.286504797,0.283654026,0.280831622,
0.278037300,0.275270783,0.272531793,0.269820056,0.267135302,0.264477261,0.261845669,0.259240261,
0.256660777,0.254106960,0.251578553,0.249075305,0.246596964,0.244143283,0.241714017,0.239308922,
0.236927759,0.234570288,0.232236275,0.229925485,0.227637688,0.225372656,0.223130160,0.220909978,
0.218711887,0.216535667,0.214381101,0.212247974,0.210136071,0.208045182,0.205975098,0.203925612,
0.201896518,0.199887614,0.197898699,0.195929574,0.193980042,0.192049909,0.190138980,0.188247066,
0.186373976,0.184519524,0.182683524,0.180865793,0.179066148,0.177284410,0.175520401,0.173773943,
0.172044864,0.170332989,0.168638147,0.166960170,0.165298888,0.163654137,0.162025751,0.160413568,
0.158817426,0.157237166,0.155672630,0.154123662,0.152590106,0.151071809,0.149568619,0.148080387,
0.146606962,0.145148198,0.143703950,0.142274072,0.140858421,0.139456856,0.138069237,0.136695425,
0.135335283,0.133988675,0.132655465,0.131335521,0.130028711,0.128734904,0.127453970,0.126185782,
0.124930212,0.123687136,0.122456428,0.121237966,0.120031629,0.118837294,0.117654843,0.116484158,
0.115325121,0.114177617,0.113041531,0.111916749,0.110803158,0.109700649,0.108609109,0.107528430,
0.106458504,0.105399225,0.104350485,0.103312180,0.102284207,0.101266462,0.100258844,0.099261252,
0.098273586,0.097295747,0.096327638,0.095369162,0.094420223,0.093480726,0.092550578,0.091629684,
0.090717953,0.089815295,0.088921617,0.088036833,0.087160851,0.086293586,0.085434951,0.084584859,
0.083743226,0.082909967,0.082084999,0.081268239,0.080459607,0.079659020,0.078866400,0.078081666,
0.077304740,0.076535545,0.075774004,0.075020040,0.074273578,0.073534544,0.072802863,0.072078462,
0.071361270,0.070651213,0.069948222,0.069252225,0.068563154,0.067880939,0.067205513,0.066536807,
0.065874754,0.065219290,0.064570347,0.063927861,0.063291768,0.062662005,0.062038507,0.061421214,
0.060810063,0.060204992,0.059605943,0.059012854,0.058425666,0.057844321,0.057268760,0.056698927,
0.056134763,0.055576213,0.055023220,0.054475730,0.053933687,0.053397038,0.052865729,0.052339706,
0.051818917,0.051303310,0.050792834,0.050287437,0.049787068,0.049291679,0.048801218,0.048315638,
0.047834889,0.047358924,0.046887695,0.046421155,0.045959257,0.045501954,0.045049202,0.044600955,
0.044157168,0.043717797,0.043282798,0.042852127,0.042425741,0.042003598,0.041585655,0.041171871,
0.040762204,0.040356613,0.039955058,0.039557499,0.039163895,0.038774208,0.038388398,0.038006427,
0.037628257,0.037253849,0.036883167,0.036516174,0.036152832,0.035793105,0.035436958,0.035084354,
0.034735259,0.034389637,0.034047455,0.033708677,0.033373270,0.033041200,0.032712435,0.032386941,
0.032064685,0.031745636,0.031429762,0.031117031,0.030807411,0.030500872,0.030197383,0.029896914,
0.029599435,0.029304916,0.029013327,0.028724640,0.028438825,0.028155854,0.027875698,0.027598330,
0.027323722,0.027051847,0.026782676,0.026516184,0.026252344,0.025991129,0.025732513,0.025476470,
0.025222975,0.024972002,0.024723526,0.024477523,0.024233968,0.023992836,0.023754103,0.023517746,
0.023283740,0.023052063,0.022822691,0.022595602,0.022370772,0.022148179,0.021927801,0.021709616,
0.021493601,0.021279736,0.021068000,0.020858369,0.020650825,0.020445346,0.020241911,0.020040501,
0.019841095,0.019643673,0.019448215,0.019254702,0.019063114,0.018873433,0.018685639,0.018499714,
0.018315639,0.018133395,0.017952965,0.017774330,0.017597472,0.017422375,0.017249019,0.017077389,
0.016907466,0.016739234,0.016572675,0.016407775,0.016244514,0.016082879,0.015922852,0.015764416,
0.015607558,0.015452260,0.015298508,0.015146285,0.014995577,0.014846368,0.014698645,0.014552391,
0.014407592,0.014264234,0.014122302,0.013981783,0.013842662,0.013704925,0.013568559,0.013433550,
0.013299884,0.013167547,0.013036528,0.012906813,0.012778388,0.012651241,0.012525359,0.012400729,
0.012277340,0.012155178,0.012034232,0.011914490,0.011795939,0.011678567,0.011562363,0.011447316,
0.011333413,0.011220644,0.011108997,0.010998460,0.010889024,0.010780676,0.010673407,0.010567204,
0.010462059,0.010357960,0.010254896,0.010152858,0.010051836,0.009951818,0.009852796,0.009754759,
0.009657698,0.009561602,0.009466462,0.009372270,0.009279014,0.009186686,0.009095277,0.009004778,
0.008915179,0.008826471,0.008738646,0.008651695,0.008565609,0.008480380,0.008395999,0.008312457,
0.008229747,0.008147860,0.008066787,0.007986521,0.007907054,0.007828378,0.007750484,0.007673365,
0.007597014,0.007521422,0.007446583,0.007372488,0.007299131,0.007226503,0.007154598,0.007083409,
0.007012928,0.006943148,0.006874063,0.006805664,0.006737947,0.006670903,0.006604527,0.006538811,
0.006473748,0.006409333,0.006345560,0.006282420,0.006219909,0.006158020,0.006096747,0.006036083,
0.005976023,0.005916560,0.005857690,0.005799405,0.005741700,0.005684569,0.005628006,0.005572007,
0.005516564,0.005461674,0.005407329,0.005353525,0.005300257,0.005247518,0.005195305,0.005143611,
0.005092431,0.005041760,0.004991594,0.004941927,0.004892754,0.004844070,0.004795871,0.004748151,
0.004700906,0.004654131,0.004607822,0.004561973,0.004516581,0.004471640,0.004427147,0.004383096,
0.004339483,0.004296305,0.004253556,0.004211232,0.004169330,0.004127844,0.004086771,0.004046107,
0.004005848,0.003965989,0.003926527,0.003887457,0.003848776,0.003810480,0.003772566,0.003735028,
0.003697864,0.003661069,0.003624641,0.003588575,0.003552868,0.003517517,0.003482517,0.003447865,
0.003413558,0.003379593,0.003345965,0.003312673,0.003279711,0.003247077,0.003214768,0.003182781,
0.003151112,0.003119758,0.003088715,0.003057982,0.003027555,0.002997430,0.002967605,0.002938077,
0.002908843,0.002879899,0.002851244,0.002822873,0.002794785,0.002766977,0.002739445,0.002712187,
0.002685200,0.002658482,0.002632030,0.002605841,0.002579912,0.002554241,0.002528826,0.002503664,
0.002478752,0.002454088,0.002429670,0.002405494,0.002381559,0.002357862,0.002334401,0.002311173,
0.002288177,0.002265409,0.002242868,0.002220551,0.002198456,0.002176581,0.002154924,0.002133482,
0.002112253,0.002091236,0.002070428,0.002049827,0.002029431,0.002009237,0.001989245,0.001969452,
0.001949856,0.001930454,0.001911246,0.001892229,0.001873401,0.001854760,0.001836305,0.001818033,
0.001799944,0.001782034,0.001764302,0.001746747,0.001729367,0.001712159,0.001695123,0.001678256,
0.001661557,0.001645025,0.001628656,0.001612451,0.001596407,0.001580522,0.001564796,0.001549226,
0.001533811,0.001518549,0.001503439,0.001488480,0.001473669,0.001459006,0.001444488,0.001430116,
0.001415886,0.001401797,0.001387849,0.001374040,0.001360368,0.001346832,0.001333431,0.001320163,
0.001307027,0.001294022,0.001281146,0.001268399,0.001255778,0.001243283,0.001230912,0.001218664,
0.001206538,0.001194533,0.001182647,0.001170880,0.001159229,0.001147695,0.001136275,0.001124969,
0.001113775,0.001102693,0.001091721,0.001080858,0.001070103,0.001059456,0.001048914,0.001038477,
0.001028144,0.001017914,0.001007785,0.000997758,0.000987830,0.000978001,0.000968270,0.000958635,
0.000949097,0.000939653,0.000930303,0.000921047,0.000911882,0.000902809,0.000893825,0.000884932,
0.000876127,0.000867409,0.000858778,0.000850233,0.000841773,0.000833397,0.000825105,0.000816895,
0.000808767,0.000800719,0.000792752,0.000784864,0.000777055,0.000769323,0.000761668,0.000754089,
0.000746586,0.000739157,0.000731802,0.000724521,0.000717312,0.000710174,0.000703108,0.000696112,
0.000689186,0.000682328,0.000675539,0.000668817,0.000662162,0.000655574,0.000649051,0.000642592,
0.000636198,0.000629868,0.000623601,0.000617396,0.000611253,0.000605171,0.000599149,0.000593188,
0.000587285,0.000581442,0.000575656,0.000569928,0.000564257,0.000558643,0.000553084,0.000547581,
0.000542133,0.000536738,0.000531398,0.000526110,0.000520875,0.000515692,0.000510561,0.000505481,
0.000500451,0.000495472,0.000490542,0.000485661,0.000480828,0.000476044,0.000471307,0.000466618,
0.000461975,0.000457378,0.000452827,0.000448321,0.000443861,0.000439444,0.000435072,0.000430743,
0.000426457,0.000422213,0.000418012,0.000413853,0.000409735,0.000405658,0.000401622,0.000397625,
0.000393669,0.000389752,0.000385874,0.000382034,0.000378233,0.000374470,0.000370744,0.000367055,
0.000363402,0.000359786,0.000356206,0.000352662,0.000349153,0.000345679,0.000342239,0.000338834,
0.000335463,0.000332125,0.000328820,0.000325548,0.000322309,0.000319102,0.000315927,0.000312783,
0.000309671,0.000306590,0.000303539,0.000300519,0.000297529,0.000294568,0.000291637,0.000288735,
0.000285862,0.000283018,0.000280202,0.000277414,0.000274654,0.000271921,0.000269215,0.000266536,
0.000263884,0.000261259,0.000258659,0.000256085,0.000253537,0.000251014,0.000248517,0.000246044,
0.000243596,0.000241172,0.000238772,0.000236397,0.000234044,0.000231716,0.000229410,0.000227127,
0.000224867,0.000222630,0.000220415,0.000218221,0.000216050,0.000213900,0.000211772,0.000209665,
0.000207579,0.000205513,0.000203468,0.000201444,0.000199439,0.000197455,0.000195490,0.000193545,
0.000191619,0.000189713,0.000187825,0.000185956,0.000184106,0.000182274,0.000180460,0.000178665,
0.000176887,0.000175127,0.000173384,0.000171659,0.000169951,0.000168260,0.000166586,0.000164928,
0.000163287,0.000161662,0.000160054,0.000158461,0.000156885,0.000155324,0.000153778,0.000152248,
0.000150733,0.000149233,0.000147748,0.000146278,0.000144823,0.000143382,0.000141955,0.000140543,
0.000139144,0.000137760,0.000136389,0.000135032,0.000133688,0.000132358,0.000131041,0.000129737,
0.000128446,0.000127168,0.000125903,0.000124650,0.000123410,0.000122182,0.000120966,0.000119762,
0.000118571,0.000117391,0.000116223,0.000115067,0.000113922,0.000112788,0.000111666,0.000110555,
0.000109455,0.000108366,0.000107287,0.000106220,0.000105163,0.000104117,0.000103081,0.000102055,
0.000101039,0.000100034,0.000099039,0.000098053,0.000097078,0.000096112,0.000095155,0.000094209,
0.000093271,0.000092343,0.000091424,0.000090515,0.000089614,0.000088722,0.000087839,0.000086965,
0.000086100,0.000085243,0.000084395,0.000083555,0.000082724,0.000081901,0.000081086,0.000080279,
0.000079480,0.000078690,0.000077907,0.000077131,0.000076364,0.000075604,0.000074852,0.000074107,
0.000073370,0.000072640,0.000071917,0.000071201,0.000070493,0.000069791,0.000069097,0.000068409,
0.000067729,0.000067055,0.000066388,0.000065727,0.000065073,0.000064426,0.000063785,0.000063150,
0.000062522,0.000061899,0.000061283,0.000060674,0.000060070,0.000059472,0.000058881,0.000058295,
0.000057715,0.000057140,0.000056572,0.000056009,0.000055452,0.000054900,0.000054354,0.000053813,
0.000053277,0.000052747,0.000052222,0.000051703,0.000051188,0.000050679,0.000050175,0.000049675,
0.000049181,0.000048692,0.000048207,0.000047728,0.000047253,0.000046783,0.000046317,0.000045856,
0.000045400,0.000044948,0.000044501,0.000044058,0.000043620,0.000043186,0.000042756,0.000042331,
0.000041909,0.000041492,0.000041080,0.000040671,0.000040266,0.000039865,0.000039469,0.000039076,
0.000038687,0.000038302,0.000037921,0.000037544,0.000037170,0.000036800,0.000036434,0.000036072,
0.000035713,0.000035358,0.000035006,0.000034657,0.000034313,0.000033971,0.000033633,0.000033298,
0.000032967,0.000032639,0.000032314,0.000031993,0.000031674,0.000031359,0.000031047,0.000030738,
0.000030432,0.000030130,0.000029830,0.000029533,0.000029239,0.000028948,0.000028660,0.000028375,
0.000028093,0.000027813,0.000027536,0.000027262,0.000026991,0.000026723,0.000026457,0.000026193,
0.000025933,0.000025675,0.000025419,0.000025166,0.000024916,0.000024668,0.000024423,0.000024180,
0.000023939,0.000023701,0.000023465,0.000023232,0.000023000,0.000022772,0.000022545,0.000022321,
0.000022099,0.000021879,0.000021661,0.000021445,0.000021232,0.000021021,0.000020812,0.000020605,
0.000020400,0.000020197,0.000019996,0.000019797,0.000019600,0.000019405,0.000019212,0.000019020,
0.000018831,0.000018644,0.000018458,0.000018275,0.000018093,0.000017913,0.000017734,0.000017558,
0.000017383,0.000017210,0.000017039,0.000016870,0.000016702,0.000016536,0.000016371,0.000016208,
0.000016047,0.000015887,0.000015729,0.000015573,0.000015418,0.000015264,0.000015112,0.000014962,
0.000014813,0.000014666,0.000014520,0.000014375,0.000014232,0.000014091,0.000013950,0.000013812,
0.000013674,0.000013538,0.000013403,0.000013270,0.000013138,0.000013007,0.000012878,0.000012750,
0.000012623,0.000012497,0.000012373,0.000012250,0.000012128,0.000012007,0.000011888,0.000011769,
0.000011652,0.000011536,0.000011422,0.000011308,0.000011195,0.000011084,0.000010974,0.000010865,
0.000010757,0.000010649,0.000010544,0.000010439,0.000010335,0.000010232,0.000010130,0.000010029,
0.000009930,0.000009831,0.000009733,0.000009636,0.000009540,0.000009445,0.000009351,0.000009258,
0.000009166,0.000009075,0.000008985,0.000008895,0.000008807,0.000008719,0.000008632,0.000008546,
0.000008461,0.000008377,0.000008294,0.000008211,0.000008130,0.000008049,0.000007969,0.000007889,
0.000007811,0.000007733,0.000007656,0.000007580,0.000007505,0.000007430,0.000007356,0.000007283,
0.000007210,0.000007139,0.000007068,0.000006997,0.000006928,0.000006859,0.000006790,0.000006723,
0.000006656,0.000006590,0.000006524,0.000006459,0.000006395,0.000006331,0.000006268,0.000006206,
0.000006144,0.000006083,0.000006023,0.000005963,0.000005903,0.000005845,0.000005786,0.000005729,
0.000005672,0.000005615,0.000005560,0.000005504,0.000005449,0.000005395,0.000005342,0.000005288,
0.000005236,0.000005184,0.000005132,0.000005081,0.000005030,0.000004980,0.000004931,0.000004882,
0.000004833,0.000004785,0.000004738,0.000004690,0.000004644,0.000004597,0.000004552,0.000004506,
0.000004462,0.000004417,0.000004373,0.000004330,0.000004287,0.000004244,0.000004202,0.000004160,
0.000004119,0.000004078,0.000004037,0.000003997,0.000003957,0.000003918,0.000003879,0.000003840,
0.000003802,0.000003764,0.000003727,0.000003690,0.000003653,0.000003617,0.000003581,0.000003545,
0.000003510,0.000003475,0.000003440,0.000003406,0.000003372,0.000003338,0.000003305,0.000003272,
0.000003240,0.000003208,0.000003176,0.000003144,0.000003113,0.000003082,0.000003051,0.000003021,
0.000002991,0.000002961,0.000002931,0.000002902,0.000002873,0.000002845,0.000002817,0.000002789,
0.000002761,0.000002733,0.000002706,0.000002679,0.000002653,0.000002626,0.000002600,0.000002574,
0.000002549,0.000002523,0.000002498,0.000002473,0.000002449,0.000002424,0.000002400,0.000002376,
0.000002353,0.000002329,0.000002306,0.000002283,0.000002260,0.000002238,0.000002216,0.000002194,
0.000002172,0.000002150,0.000002129,0.000002108,0.000002087,0.000002066,0.000002045,0.000002025,
0.000002005,0.000001985,0.000001965,0.000001945,0.000001926,0.000001907,0.000001888,0.000001869,
0.000001851,0.000001832,0.000001814,0.000001796,0.000001778,0.000001760,0.000001743,0.000001725,
0.000001708,0.000001691,0.000001674,0.000001658,0.000001641,0.000001625,0.000001609,0.000001593,
0.000001577,0.000001561,0.000001546,0.000001530,0.000001515,0.000001500,0.000001485,0.000001470,
0.000001456,0.000001441,0.000001427,0.000001413,0.000001399,0.000001385,0.000001371,0.000001357,
0.000001344,0.000001330,0.000001317,0.000001304,0.000001291,0.000001278,0.000001266,0.000001253,
0.000001240,0.000001228,0.000001216,0.000001204,0.000001192,0.000001180,0.000001168,0.000001157,
0.000001145,0.000001134,0.000001122,0.000001111,0.000001100,0.000001089,0.000001078,0.000001068,
0.000001057,0.000001047,0.000001036,0.000001026,0.000001016,0.000001006,0.000000996,0.000000986,
0.000000976,0.000000966,0.000000956,0.000000947,0.000000938,0.000000928,0.000000919,0.000000910,
0.000000901,0.000000892,0.000000883,0.000000874,0.000000865,0.000000857,0.000000848,0.000000840,
0.000000832,0.000000823,0.000000815,0.000000807,0.000000799,0.000000791,0.000000783,0.000000775,
0.000000768,0.000000760,0.000000752,0.000000745,0.000000737,0.000000730,0.000000723,0.000000716,
0.000000709,0.000000702,0.000000695,0.000000688,0.000000681,0.000000674,0.000000667,0.000000661,
0.000000654,0.000000648,0.000000641,0.000000635,0.000000628,0.000000622,0.000000616,0.000000610,
0.000000604,0.000000598,0.000000592,0.000000586,0.000000580,0.000000574,0.000000569,0.000000563,
0.000000557,0.000000552,0.000000546,0.000000541,0.000000536,0.000000530,0.000000525,0.000000520,
0.000000515,0.000000509,0.000000504,0.000000499,0.000000494,0.000000489,0.000000485,0.000000480,
0.000000475,0.000000470,0.000000466,0.000000461,0.000000456,0.000000452,0.000000447,0.000000443,
0.000000438,0.000000434,0.000000430,0.000000426,0.000000421,0.000000417,0.000000413,0.000000409,
0.000000405,0.000000401,0.000000397,0.000000393,0.000000389,0.000000385,0.000000381,0.000000377,
0.000000374,0.000000370,0.000000366,0.000000363,0.000000359,0.000000355,0.000000352,0.000000348,
0.000000345,0.000000341,0.000000338,0.000000335,0.000000331,0.000000328,0.000000325,0.000000322,
0.000000318,0.000000315,0.000000312,0.000000309,0.000000306,0.000000303,0.000000300,0.000000297,
0.000000294,0.000000291,0.000000288,0.000000285,0.000000282,0.000000280,0.000000277,0.000000274,
0.000000271,0.000000269,0.000000266,0.000000263,0.000000261,0.000000258,0.000000256,0.000000253,
0.000000250,0.000000248,0.000000245,0.000000243,0.000000241,0.000000238,0.000000236,0.000000234,
0.000000231,0.000000229,0.000000227,0.000000224,0.000000222,0.000000220,0.000000218,0.000000216,
0.000000213,0.000000211,0.000000209,0.000000207,0.000000205,0.000000203,0.000000201,0.000000199,
0.000000197,0.000000195,0.000000193,0.000000191,0.000000189,0.000000187,0.000000186,0.000000184,
0.000000182,0.000000180,0.000000178,0.000000176,0.000000175,0.000000173,0.000000171,0.000000170,
0.000000168,0.000000166,0.000000165,0.000000163,0.000000161,0.000000160,0.000000158,0.000000157,
0.000000155,0.000000153,0.000000152,0.000000150,0.000000149,0.000000147,0.000000146,0.000000144,
0.000000143,0.000000142,0.000000140,0.000000139,0.000000137,0.000000136,0.000000135,0.000000133,
0.000000132,0.000000131,0.000000129,0.000000128,0.000000127,0.000000126,0.000000124,0.000000123,
0.000000122,0.000000121,0.000000119,0.000000118,0.000000117,0.000000116,0.000000115,0.000000114,
0.000000113,0.000000111,0.000000110,0.000000109,0.000000108,0.000000107,0.000000106,0.000000105,
0.000000104,0.000000103,0.000000102,0.000000101,0.000000100,0.000000099,0.000000098,0.000000097,
0.000000096,0.000000095,0.000000094,0.000000093,0.000000092,0.000000091,0.000000090,0.000000089,
0.000000089,0.000000088,0.000000087,0.000000086,0.000000085,0.000000084,0.000000083,0.000000083,
0.000000082,0.000000081,0.000000080,0.000000079,0.000000079,0.000000078,0.000000077,0.000000076,
0.000000075,0.000000075,0.000000074,0.000000073,0.000000072,0.000000072,0.000000071,0.000000070,
0.000000070,0.000000069,0.000000068,0.000000068,0.000000067,0.000000066,0.000000066,0.000000065,
0.000000064,0.000000064,0.000000063,0.000000062,0.000000062,0.000000061,0.000000061,0.000000060,
0.000000059,0.000000059,0.000000058,0.000000058,0.000000057,0.000000056,0.000000056,0.000000055,
0.000000055,0.000000054,0.000000054,0.000000053,0.000000053,0.000000052,0.000000052,0.000000051,
0.000000051,0.000000050,0.000000050,0.000000049,0.000000049,0.000000048,0.000000048,0.000000047,
0.000000047,0.000000046,0.000000046,0.000000045,0.000000045,0.000000044,0.000000044,0.000000044,
0.000000043,0.000000043,0.000000042,0.000000042,0.000000041,0.000000041,0.000000041,0.000000040,
0.000000040,0.000000039,0.000000039,0.000000039,0.000000038,0.000000038,0.000000037,0.000000037,
0.000000037,0.000000036,0.000000036,0.000000036,0.000000035,0.000000035,0.000000035,0.000000034,
0.000000034,0.000000034,0.000000033,0.000000033,0.000000033,0.000000032,0.000000032,0.000000032,
0.000000031,0.000000031,0.000000031,0.000000030,0.000000030,0.000000030,0.000000029,0.000000029,
0.000000029,0.000000029,0.000000028,0.000000028,0.000000028,0.000000027,0.000000027,0.000000027,
0.000000027,0.000000026,0.000000026,0.000000026,0.000000026,0.000000025,0.000000025,0.000000025,
0.000000025,0.000000024,0.000000024,0.000000024,0.000000024,0.000000023,0.000000023,0.000000023,
0.000000023,0.000000022,0.000000022,0.000000022,0.000000022,0.000000022,0.000000021,0.000000021,
0.000000021,0.000000021,0.000000021,0.000000020,0.000000020,0.000000020,0.000000020,0.000000020,
0.000000019,0.000000019,0.000000019,0.000000019,0.000000019,0.000000018,0.000000018,0.000000018,
0.000000018,0.000000018,0.000000018,0.000000017,0.000000017,0.000000017,0.000000017,0.000000017,
0.000000016,0.000000016,0.000000016,0.000000016,0.000000016,0.000000016,0.000000016,0.000000015,
0.000000015,0.000000015,0.000000015,0.000000015,0.000000015,0.000000014,0.000000014,0.000000014,
0.000000014,0.000000014,0.000000014,0.000000014,0.000000014,0.000000013,0.000000013,0.000000013,
0.000000013,0.000000013,0.000000013,0.000000013,0.000000012,0.000000012,0.000000012,0.000000012,
0.000000012,0.000000012,0.000000012,0.000000012,0.000000012,0.000000011,0.000000011,0.000000011,
0.000000011,0.000000011,0.000000011,0.000000011,0.000000011,0.000000011,0.000000010,0.000000010,
0.000000010,0.000000010,0.000000010,0.000000010,0.000000010,0.000000010,0.000000010,0.000000010,
0.000000009,0.000000009,0.000000009,0.000000009,0.000000009,0.000000009,0.000000009,0.000000009,
0.000000009,0.000000009,0.000000009,0.000000008,0.000000008,0.000000008,0.000000008,0.000000008,
0.000000008,0.000000008,0.000000008,0.000000008,0.000000008,0.000000008,0.000000008,0.000000007,
0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,
0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,0.000000007,0.000000006,0.000000006,
0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,
0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,0.000000006,0.000000005,0.000000005,
0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,
0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,0.000000005,
0.000000005,0.000000005,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,
0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,
0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,0.000000004,
0.000000004,0.000000004,0.000000004,0.000000004,0.000000003,0.000000003,0.000000003,0.000000003,
0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,
0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,
0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,
0.000000003,0.000000003,0.000000003,0.000000003,0.000000003,0.000000002,0.000000002,0.000000002,
0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,
0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,0.000000002,
0.000000002
};

#endif // MATHTABLES_H