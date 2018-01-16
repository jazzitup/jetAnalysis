#ifndef JZWEIGHT_H
#define JZWEIGHT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <TROOT.h>

const double JZ1_cs     = 1.2794E+08;
const double JZ1_fltEff = 1.5857E-03;
const double JZ1_wNorm  = 3.428918e+08 ;

const double JZ2_cs     = 1.9648E+07; 
const double JZ2_fltEff = 1.2948E-04 ;
const double JZ2_wNorm  = 4.656080e+06; 

const double JZ3_cs     = 5.7613E+05;
const double JZ3_fltEff = 4.2129E-05;
const double JZ3_wNorm  = 5.805497e+04 ;

const double JZ4_cs     = 4.1522E+04;
const double JZ4_fltEff = 2.8563E-06;
const double JZ4_wNorm  = 7.924295e+02 ;

const double JZ5_cs     = 8.4338E+02;
const double JZ5_fltEff = 5.9854E-07;
const double JZ5_wNorm  = 1.764195e+01;

double perEvtWgtJZ1 = JZ1_cs * JZ1_fltEff / JZ1_wNorm ; 
double perEvtWgtJZ2 = JZ2_cs * JZ2_fltEff / JZ2_wNorm ; 
double perEvtWgtJZ3 = JZ3_cs * JZ3_fltEff / JZ3_wNorm ; 
double perEvtWgtJZ4 = JZ4_cs * JZ4_fltEff / JZ4_wNorm ; 
double perEvtWgtJZ5 = JZ5_cs * JZ5_fltEff / JZ5_wNorm ; 

double hi9EvtWgtJZ2 = perEvtWgtJZ2 / 5856854. ;
double hi9EvtWgtJZ3 = perEvtWgtJZ3 / 5913566. ;
double hi9EvtWgtJZ4 = perEvtWgtJZ4 / 7887243. ;  // 5887243.

#endif 
