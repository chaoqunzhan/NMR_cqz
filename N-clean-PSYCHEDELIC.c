#ifndef LINT
static char SCCSid[] = "@(#)s2pul.c 19.1 01/13/06 Copyright (c) 1991-1996 Varian Assoc.,Inc. All Rights Reserved";
#endif

/*  s2pul - standard two-pulse sequence */

#include <standard.h>


static int phs1[8] = {0,2,0,2,1,3,1,3},
	   phs2[8] = {0,0,2,2,1,1,3,3},
	   phs3[8] = {1,3,1,3,0,2,0,2},
	   phs4[8] = {0,0,2,2,1,1,3,3},
	   phs5[8] = {0,2,0,2,1,3,1,3},

	   phs6[8] = {0,2,0,2,1,3,1,3},
	   phs7[8] = {0,0,2,2,1,1,3,3},
	   phs8[8] = {0,2,0,2,1,3,1,3};

pulsesequence()
{
double selpwr,selpw,seltof,Gz,G1,inhz,inhz1,selpw1,selpwr1,ptof,ppwr,ppw,deta,cpw,cpwr,cpw0,cpwr0;char   selpat[MAXSTR],selpat1[MAXSTR],ppat1[MAXSTR],ppat2[MAXSTR],ppat0[MAXSTR];

selpwr = getval("selpwr");
selpw  = getval("selpw");
selpwr1 = getval("selpwr1");
selpw1  = getval("selpw1");
cpw0 = getval("cpw0");
cpwr0 = getval("cpwr0");
cpw = getval("cpw");
cpwr = getval("cpwr");
seltof = getval("seltof");
ptof = getval("ptof");
ppw  = getval("ppw");
ppwr  = getval("ppwr");

G1     = getval("G1");
Gz     = getval("Gz");
inhz   = getval("inhz");
inhz1   = getval("inhz1");


getstr("selpat",selpat);
getstr("selpat1",selpat1);
getstr("ppat0",ppat0);
getstr("ppat1",ppat1);	
getstr("ppat2",ppat2);

	
assign(ct,v17);
settable(t1,8,phs1);
settable(t2,8,phs2);
settable(t3,8,phs3);
settable(t4,8,phs4);
settable(t5,8,phs5);
settable(t6,8,phs6);
settable(t7,8,phs7);
settable(t8,8,phs8);
getelem(t1,v17,v1);
getelem(t2,v17,v2);
getelem(t3,v17,v3);
getelem(t4,v17,v4);
getelem(t5,v17,v5);
getelem(t6,v17,v6);
getelem(t7,v17,v7);
getelem(t8,v17,v8);
assign(v8,oph);


/* equilibrium period */
status(A); 
delay(d1);
/* equilibrium period */

 

/* --- polarization transfer --- */
status(B);
delay(5e-6);
obsoffset(seltof);
obspower(selpwr1);
shaped_pulse(selpat1,selpw1,v1,rof1,rof1);	//first selective 90 pulse 
delay(5e-6);

delay(deta/2);



delay(5e-6);
rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);
obsoffset(tof);
obspower(tpwr);
rgpulse(2*pw,v2,rof1,rof1);	//second 180 pulse
delay(5e-6);
rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);

delay(deta/2);

delay(5e-6);
obsoffset(tof);
obspower(tpwr);
rgpulse(pw,v3,rof1,rof1);	//third 90 pulse 
delay(5e-6);

delay(deta/2);

delay(5e-6);
rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);
obsoffset(tof);
obspower(tpwr);
rgpulse(2*pw,v4,rof1,rof1);	//fourth 180 pulse 
delay(5e-6);
rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);

delay(deta/2);
/* --- polarization transfer --- */





/* --- z-filter-chirp --- */
status(C);
delay(5e-6);
obsoffset(tof);
obspower(tpwr);
rgpulse(pw,v5,rof1,rof1);	//first 180 pulse for z-filter
delay(5e-6);

rgradient('z',G1);
delay(5e-6);
obsoffset(tof);obspower(cpwr0);
obspwrf(4095);
shaped_pulse(ppat0,cpw0,0,rof1,rof1);   //chirp for z-filter
delay(5e-6);
rgradient('z',0);

delay(5e-6);
obsoffset(tof);
obspower(tpwr);
rgpulse(pw,v6,rof1,rof1);	//second 180 pulse for z-filter
delay(5e-6);
/* --- z-filter-chirp --- */




/* --- PSYCHEDELIC --- */
status(D);

delay(5e-6);
obsoffset(seltof);
obspower(selpwr);
shaped_pulse(selpat,selpw,v7,rof1,rof1);
obsoffset(tof);
obspower(tpwr);
delay(5e-6);

delay(d2/2);

delay(5e-6);
rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);



rgradient('z',Gz);
obsoffset(tof);obspower(cpwr);
obspwrf(4095);
delay(5e-6);
shaped_pulse(ppat1,cpw,v7,rof1,rof2);
delay(5e-6);
shaped_pulse(ppat2,cpw,v7,rof1,rof2);
delay(5e-6);
obspwrf(4096);
rgradient('z',0);                             


delay(5e-6);
obsoffset(seltof);
obspower(selpwr);
shaped_pulse(selpat,selpw,v7,rof1,rof1);
obsoffset(tof);
obspower(tpwr);
delay(5e-6);


rgradient('z',inhz);
delay(1e-3);
rgradient('z',0);
delay(5e-6);

delay(d2/2);
delay(5e-6);
obsoffset(tof);
obspower(tpwr);
/* --- PSYCHEDELIC --- */
}
