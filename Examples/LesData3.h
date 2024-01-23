/**
 *   Enkel verktøykasse for å lese:  tegn og tall.
 *
 *   FULLSTENDIG IDENTISK til 'LesData2.h' bare at adskilt
 *   funksjonenes DEKLARASJON (som er på DENNE filen) og DEFINISJON.
 *
 *   @file     LesData3.H
 *   @author   Frode Haug, NTNU
 */


#ifndef __LESDATA3_H
#define __LESDATA3_H


const int  MAXCHAR = 200;      //  Max.tegn i input-buffer.


char  lesChar(const char* t);
float lesFloat(const char* t, const float min, const float max);
int   lesInt(const char* t, const int min, const int max);

#endif