/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#include "Mask.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "LinuxCompat.h"
#include <inttypes.h>

#include "dbgmem.h"

//Initialize static variable chipSubRegion in Mask class
Region Mask::chipSubRegion = {0,0,0,0,0};

Mask::Mask(int _w, int _h)
{
  isHex = false;
	w = (int32_t) _w;
	h = (int32_t) _h;
	xOffset = 0;
	yOffset = 0;
	mask = (uint16_t *)malloc(w*h*sizeof(uint16_t));
	// memset interprets value as unsigned char only;
	// only good for zeroing an array.
	memset(mask, MaskNone, w*h*sizeof(uint16_t));
	// Initialize the array values
	for (int i = 0; i < (w*h); i++)
	{
		mask[i] = MaskEmpty;
	}
}

Mask::Mask(Mask *origmask)
{
  mask = NULL;
	Init(origmask);
}

Mask::Mask(const char *fileName, bool fillMask) {
  //Note, fillMask is optional argument w/ default of true.
  FILE *in = fopen(fileName, "rb");
  assert(in);
  isHex = false;
  int32_t r,c;
  int elements_read = fread(&r, sizeof(r), 1, in);
  assert(elements_read == 1);
  elements_read = fread(&c, sizeof(c), 1, in);
  assert(elements_read == 1);
  h = r;
  w = c;
  xOffset = 0;
  yOffset = 0;
  int nelements = r*c;
  int nbytes = nelements*sizeof(uint16_t);
  if(fillMask) {
	mask = (uint16_t *)malloc(nbytes);
	elements_read = fread(mask, nbytes, 1, in);
	assert(elements_read == 1);
	fclose(in);
  } else {
	mask = NULL;
  }
}

Mask::~Mask()
{
  if(mask!=NULL) {
	free(mask);
  }
}

void Mask::Init(int _w, int _h)
{
  isHex = false;
  Init(_w,_h,MaskEmpty);
}

void Mask::Init(int _w, int _h, MaskType these)
{
  isHex = false;
	w = (int32_t) _w;
	h = (int32_t) _h;
    xOffset = 0;
    yOffset = 0;
	if (mask != NULL) {
	  free(mask);
	}
	mask = (uint16_t *)malloc(w*h*sizeof(uint16_t));
	// memset interprets value as unsigned char only;
	// only good for zeroing an array.
	memset(mask, MaskNone, w*h*sizeof(uint16_t));
	// Initialize the array values
	for (int i = 0; i < (w*h); i++)
	{
		mask[i] = these;
	}
}

void Mask::Init(Mask *origmask)
{
  isHex = false;
	w = origmask->W();
	h = origmask->H();
    xOffset = origmask->Xoffset();
    yOffset = origmask->Yoffset();
	if (mask != NULL) {
	  free(mask);
	}
	mask = (unsigned short *)malloc(w*h*sizeof(uint16_t));
	memcpy(mask, origmask->GetMask(), w*h*sizeof(uint16_t));
}

void Mask::Copy(Mask *origmask)
{
  if (mask != NULL) {
    free(mask);
    mask=NULL;
  }
  Init(origmask);
}

uint16_t Mask::GetBarcodeId(int x, int y) const {
	//The "mask" values can actually be barcodeIds, so use this method
	//to get it directly.
	assert(x >= 0 && x < w);
	assert(y >= 0 &&  y < h);
	return mask[x+y*w];
}

//
//	NOTE: The default Match method is MATCH_ANY; any bit set in the pattern will
// return true.  MATCH_ALL requires that all bits must be set in the pattern in
// order to return true.  MATCH_ONLY requires that ONLY the specified bits are set.
//
bool Mask::Match(int x, int y, MaskType t, int method) const
{
	
	if (x < 0 || x >= w)
		return false;
	if (y < 0 ||  y >= h)
		return false;
	
	return (Match (x+y*w, t, method));
}

bool Mask::Match(int n, MaskType t, int method) const
{
	if (n < 0 || n >= (w*h))
		return false;
	
	switch (method)
	{
		case MATCH_ANY:
			return ((mask[n] & t ? true : false));
			break;
		case MATCH_ALL:
			return (( (int) (mask[n] & t) == (int) t) ? true : false);
			break;
		case MATCH_ONLY:
			return (( (mask[n] - t) == 0 ) ? true : false);
			break;
		default:
			fprintf (stderr, "Unrecognized MATCH method: %d\n", method);
			assert (0);
			break;
	}
}

// sets the specified type flags for a single well in the mask
void Mask::Set(int x, int y, MaskType type)
{
	if ((x >= 0) && (x < w) && (y >= 0) && (y < h)){
	  mask[x+y*w] |= type;
	}
}

// sets the mask to be a barcode id
void Mask::SetBarcodeId(int x, int y, uint16_t barcodeId)
{
	assert((x >= 0) && (x < w) && (y >= 0) && (y < h));
	mask[x+y*w] = barcodeId;
}

void Mask::AddThese(Mask *fromMask, MaskType these)
{
	int i;
	for(i=0;i<w*h;i++) {
		if ((*fromMask)[i] & these) {
			mask[i] |= these;
		}
	}
}
void Mask::SetThese(Mask *fromMask, MaskType these)
{
	int i;
	for(i=0;i<w*h;i++) {
		if ((*fromMask)[i] & these) {
			mask[i] = these;
		}
	}
}

//
// Returns number of matching beads in the entire mask
int Mask::GetCount(MaskType these) const
{
	int count = 0;
	int i;
	for(i=0;i<w*h;i++) {
		if (mask[i] & these)
			count++;
	}
	return count;
}

//
//	Returns number of matching beads in the specified region
int Mask::GetCount(MaskType these, Region r) const
{
	int count = 0;
	int x;
	int y;
	
	for (y=r.row;y<r.row+r.h;y++)
		for (x=r.col;x<r.col+r.w;x++)
			if (mask[x+y*w] & these)
				count++;
	
	return count;
}

//
//	Returns exactly number of beads with given mask bits set
int Mask::GetCountExact(MaskType val) const
{
	int num = this->w * this->h;
	int count = 0;
	for (int i = 0; i < num; i++) {

		if (this->Match (i, val, MATCH_ALL))
			count++;
	}
	return count;
}

//
//	Writes the entire mask to a text file
//
int Mask::Export(char *fileName, MaskType these) const
{
	// Write a mask to comma-delimited text file
	//	Format (J. Branciforte):
	// Line 1: 0, 0 	- Absolute position of mask region's origin (Upper left corner of region)
	// Line 2: w, h		- width of region and height of region
	// Line 3: 			- Comma delimited mask values for row 1 (starting from [0,0] upper left)
	// Line ...
	// Line 3+h
	//
	int32_t i;
	FILE *fp = NULL;
	uint32_t count = 0;
	
	fopen_s(&fp, fileName, "w");
	if (fp)
	{
		// Header
		fprintf (fp, "%d, %d\n", 0, 0);	//the Mask object has no knowledge of 'origin'
		fprintf (fp, "%d, %d\n", w, h);
		
		// Write out the mask
		for (i = 0; i < (w*h); i++)
		{
			fprintf (fp, "%hu", ((mask[i] & these) ? 1:0));
			if ((i+1) % w == 0)
			{
				fprintf (fp, "\n");
			}
			else
			{
				fprintf (fp, ",");
			}
			if (mask[i] & these)
				count++;
		}
		fclose(fp);
		// DEBUG
		fprintf (stdout, "%s written\n", fileName);
		fprintf (stdout, "%d found (%u total)\n", count, w*h);
		return (0);
	}
	else
	{
		fprintf (stdout, "%s: %s\n", fileName, strerror (errno));
		return (1);
	}
}

//
//	Writes the mask for the given region to a text file
//
int Mask::Export(char *fileName, MaskType these, Region region) const
{
	// Write a mask to comma-delimited text file
	//	Format (J. Branciforte):
	// Line 1: region.row, region.col 	- Absolute position of mask region's origin (Upper left corner of region)
	// Line 2: region.w, region.h	- width of region and height of region
	// Line 3: 						- Comma delimited mask values for row 1 (starting from [0,0] upper left)
	// Line ...
	// Line 3+h
	//
	int y;
	int x;
	uint32_t count = 0;
	int disp;
	
	FILE *fp = NULL;
	
	fopen_s(&fp, fileName, "w");
	if (fp)
	{
		// Header
		fprintf (fp, "%d, %d\n", region.row, region.col);
		fprintf (fp, "%d, %d\n", region.w, region.h);
		
		for (y = region.row; y < (region.row + region.h); y++)
		{
			for (x = region.col; x < (region.col + region.w); x++)
			{
				disp = mask[x + (y * this->w)];
				fprintf (fp, "%hu", ((mask[x + (y * this->w)] & these) ? 1:0));
				if (x+1 < region.col+region.w)
					fprintf (fp, ",");
					
				if (mask[x + (y * this->w)] & these)
					count++;
			}
			fprintf (fp, "\n");
		}

		fclose(fp);
		// DEBUG
		fprintf (stdout, "%s written\n", fileName);
		fprintf (stdout, "%d found (%u total)\n", count, region.w*region.h);
		return (0);
	}
	else
	{
		fprintf (stdout, "%s: %s\n", fileName, strerror (errno));
		return (1);
	}
}

//
// Dump a list of mask positions
//
int Mask::MaskList (char *fileName, MaskType these) const
{
	int i;
	int maxI = this->w * this->h;
	FILE *fp = NULL;
	uint32_t count = 0;
	#define ORIGIN		// Uncomment to generate zero-based location for the region
	
	fopen_s (&fp, fileName, "wb");
	if (!fp)
	{
		fprintf (stdout, "%s: %s\n", fileName, strerror(errno));
		return (1);
	}
	// Write out the mask
	for (i = 0; i < maxI; i++)
	{
		if (mask[i] & these)
		{
			fprintf (fp, "%d %d\n", (i/w), (i%w));
			count++;
		}
	}
	fclose (fp);
	
	// DEBUG
	fprintf (stdout, "%s written\n", fileName);
	fprintf (stdout, "%d found (%u total)\n", count, w*h);
	
	return (0);
}

//
// Dump a list of mask positions for the given region
//
int Mask::MaskList (char *fileName, MaskType these, Region region) const
{
	int x;
	int y;
	uint32_t count = 0;
	//#define ORIGIN		// Uncomment to generate zero-based location for the region
	
	FILE *fp = NULL;
	fopen_s (&fp, fileName, "wb");
	if (!fp)
	{
		fprintf (stdout, "%s: %s\n", fileName, strerror(errno));
		return (1);
	}
	// Write out the mask
	
	for (y = region.row; y < (region.row + region.h); y++)
	{
		for (x = region.col; x < (region.col + region.w); x++)
		{
			if (mask[x + (y * this->w)] & these)
			{
				#ifdef ORIGIN
				fprintf (fp, "%d %d\n", (y - region.row), (x - region.col));
				#else
				fprintf (fp, "%d %d\n", y, x);
				#endif
				count++;
			}
		}
	}
	fclose (fp);
	
	// DEBUG
	fprintf (stdout, "%s written\n", fileName);
	fprintf (stdout, "%d found (%u total)\n", count, region.w*region.h);
	
	return (0);
}


//
// Write the mask values to a binary file.
// Values are unsigned 2 byte integers
// First 8 bytes are 2 unsigned integers containing number of rows, number of columns
//
int Mask::WriteRaw (const char *fileName) const
{
	FILE *fp = NULL;
	fopen_s (&fp, fileName, "wb");
	if (!fp)
	{
		fprintf (stdout, "%s: %s\n", fileName, strerror(errno));
		return (1);
	}
	
	fwrite (&h, sizeof(uint32_t), 1, fp);	// Number of rows
	fwrite (&w, sizeof(uint32_t), 1, fp);	// Number of columns
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			fwrite (&mask[x + (y * this->w)], sizeof(uint16_t), 1, fp);	// Mask values , row-major
	fclose (fp);

	return (0);
}


//
//	Replaces existing mask dimensions and values with values from binary mask file
// Read the mask values from a binary file.
// Values are unsigned 2 byte integers
// First 4 bytes are unsigned integer containing number of mask elements in file.
//
int Mask::SetMask(const char *fileName)
{	
	uint32_t row;
	uint32_t col;
	
	FILE *fp = NULL;
	fopen_s (&fp, fileName, "rb");
	if (!fp)
	{
		fprintf (stderr, "%s: %s\n", fileName, strerror(errno));
		return (1);
	}
	
	//Read the row and column info from file
	int elements_read = fread (&row, sizeof(uint32_t),1,fp);
    assert(elements_read == 1);
	elements_read = fread (&col, sizeof(uint32_t),1,fp);
    assert(elements_read == 1);
	
	if (Mask::chipSubRegion.w == 0 && Mask::chipSubRegion.h == 0) {
	  //read entire file into mask
	  w = col;
	  h = row;
	  xOffset = 0;
	  yOffset = 0;
	} else {
	  //chipsubregion defined; only load subregion
	  w = Mask::chipSubRegion.w;
	  h = Mask::chipSubRegion.h;
	  xOffset = Mask::chipSubRegion.col;
	  yOffset = Mask::chipSubRegion.row;
	}
	
	if (mask)
		free(mask);
	mask = (uint16_t *) malloc (w*h*sizeof(uint16_t));
	memset (mask, 0 , w*h*sizeof(uint16_t));
	for (int y = yOffset; y < h; y++) {
		for (int x = xOffset; x < w; x++) {
			elements_read = fread (&mask[x + (y * this->w)], sizeof(uint16_t), 1, fp);
            assert(elements_read == 1);
        }
    }
	
	fclose (fp);
	return (0);
}

int Mask::DumpStats (Region region, char *fileName, bool showWashouts) const
{
	int x;
	int y;
	int maskempty           = 0;
	int maskbead            = 0;
	int masklive            = 0;
	int maskdud             = 0;
	int maskambiguous       = 0;
	int masktf              = 0;
	int masklib             = 0;
	int maskpinned          = 0;
	int maskignore          = 0;
	int maskwashout         = 0;
	int maskexclude         = 0;
	int washoutdud          = 0;
	int washoutambiguous    = 0;
	int washoutlive         = 0;
	int washouttf           = 0;
	int washoutlib          = 0;
	int tfFilteredShort       = 0;
	int tfFilteredBadKey      = 0;
	int tfFilteredBadPPF      = 0;
	int tfFilteredBadResidual = 0;
	int tfValidatedBeads       = 0;
	int libFilteredShort       = 0;
	int libFilteredBadKey      = 0;
	int libFilteredBadPPF      = 0;
	int libFilteredBadResidual = 0;
	int libValidatedBeads      = 0;
	FILE *fp = NULL;
	
    fopen_s(&fp, fileName, "wb");
	if (!fp)
	{
		fprintf (stderr, "%s: %s\n", fileName, strerror(errno));
		return (1);
	}
	
	for (y = region.row; y < (region.row + region.h); y++)
	{
		for (x = region.col; x < (region.col + region.w); x++)
		{
			int iWell = x+y*w;

			maskempty           += (Match(iWell,MaskEmpty) ? 1:0);
			maskbead            += (Match(iWell,MaskBead) ? 1:0);
			masklive            += (Match(iWell,MaskLive) ? 1:0);
			maskdud             += (Match(iWell,MaskDud) ? 1:0);
			maskambiguous       += (Match(iWell,MaskAmbiguous) ? 1:0);
			masktf              += (Match(iWell,MaskTF) ? 1:0);
			masklib             += (Match(iWell,MaskLib) ? 1:0);
			maskpinned          += (Match(iWell,MaskPinned) ? 1:0);
			maskignore          += (Match(iWell,MaskIgnore) ? 1:0);
			maskexclude         += (Match(iWell,MaskExclude) ? 1:0);

	                if(Match(iWell, MaskTF)) {
				tfFilteredShort        += Match(iWell, MaskFilteredShort)       ? 1 : 0;
				tfFilteredBadKey       += Match(iWell, MaskFilteredBadKey)      ? 1 : 0;
				tfFilteredBadPPF       += Match(iWell, MaskFilteredBadPPF)      ? 1 : 0;
				tfFilteredBadResidual  += Match(iWell, MaskFilteredBadResidual) ? 1 : 0;
				tfValidatedBeads       += Match(iWell, MaskKeypass)             ? 1 : 0;
	                }
			
	                if(Match(iWell, MaskLib)) {
				libFilteredShort       += Match(iWell, MaskFilteredShort)       ? 1 : 0;
				libFilteredBadKey      += Match(iWell, MaskFilteredBadKey)      ? 1 : 0;
				libFilteredBadPPF      += Match(iWell, MaskFilteredBadPPF)      ? 1 : 0;
				libFilteredBadResidual += Match(iWell, MaskFilteredBadResidual) ? 1 : 0;
				libValidatedBeads      += Match(iWell, MaskKeypass)             ? 1 : 0;
	                }
			
			if (showWashouts && Match(x+y*w,MaskWashout)) {
				
				maskwashout++;
				washoutdud			+= (Match(x+y*w,MaskDud) ? 1:0);
				washoutambiguous	+= (Match(x+y*w,MaskAmbiguous) ? 1:0);
				washoutlive			+= (Match(x+y*w,MaskLive) ? 1:0);
				washouttf			+= (Match(x+y*w,MaskTF) ? 1:0);
				washoutlib			+= (Match(x+y*w,MaskLib) ? 1:0);
			}
		}
	}
	// add section 'global' to make parsing easier
	fprintf (fp, "[global]\n");

	fprintf (fp, "Start Row = %d\n", region.row);
	fprintf (fp, "Start Column = %d\n", region.col);
	fprintf (fp, "Width = %d\n", region.w);
	fprintf (fp, "Height = %d\n", region.h);
	fprintf (fp, "Total Wells = %d\n", region.w * region.h);
	fprintf (fp, "Excluded Wells = %d\n", maskexclude);
	fprintf (fp, "Empty Wells = %d\n", maskempty);
	fprintf (fp, "Pinned Wells = %d\n", maskpinned);
	fprintf (fp, "Ignored Wells = %d\n", maskignore);
	fprintf (fp, "Bead Wells = %d\n", maskbead);
	fprintf (fp, "Dud Beads = %d\n", maskdud);
	fprintf (fp, "Ambiguous Beads = %d\n", maskambiguous);
	fprintf (fp, "Live Beads = %d\n", masklive);
	fprintf (fp, "Test Fragment Beads = %d\n", masktf);
	fprintf (fp, "Library Beads = %d\n", masklib);
        if(maskbead - masktf > 0)
	  fprintf (fp, "Percent Template-Positive Library Beads = %1.2f\n", 100 * (double) (masklib / double(maskbead - masktf)));
	else
	  fprintf (fp, "Percent Template-Positive Library Beads = NA\n");
	if (showWashouts) {
		fprintf (fp, "Washout Wells = %d\n", maskwashout);
		fprintf (fp, "Washout Dud = %d\n", washoutdud);
		fprintf (fp, "Washout Ambiguous = %d\n", washoutambiguous);
		fprintf (fp, "Washout Live = %d\n", washoutlive);
		fprintf (fp, "Washout Test Fragment = %d\n", washouttf);
		fprintf (fp, "Washout Library = %d\n", washoutlib);
	}
	fprintf (fp, "TF Filtered Beads (read too short) = %d\n",          tfFilteredShort);
	fprintf (fp, "TF Filtered Beads (fail keypass) = %d\n",            tfFilteredBadKey);
	fprintf (fp, "TF Filtered Beads (too many positive flows) = %d\n", tfFilteredBadPPF);
	fprintf (fp, "TF Filtered Beads (poor signal fit) = %d\n",         tfFilteredBadResidual);
	fprintf (fp, "TF Validated Beads = %d\n",                          tfValidatedBeads);
	fprintf (fp, "Lib Filtered Beads (read too short) = %d\n",          libFilteredShort);
	fprintf (fp, "Lib Filtered Beads (fail keypass) = %d\n",            libFilteredBadKey);
	fprintf (fp, "Lib Filtered Beads (too many positive flows) = %d\n", libFilteredBadPPF);
	fprintf (fp, "Lib Filtered Beads (poor signal fit) = %d\n",         libFilteredBadResidual);
	fprintf (fp, "Lib Validated Beads = %d\n",                          libValidatedBeads);
	fclose (fp);
	return (0);
}

int Mask::Crop(int32_t width, int32_t height, int32_t top, int32_t left) {
  assert(this->mask);
  const int32_t SIZE = width*height;
  assert(SIZE);
  assert(top >= 0 && top+height <= this->h);
  assert(left >= 0 && left+width <= this->w);
  uint16_t *cropped = new uint16_t[SIZE];
  uint16_t *ptr = cropped;
  for (int32_t r = top; r < top+height; r++) {
    uint16_t *src = mask + r*w + left;
    for (int32_t c = 0; c < width; c++, ++ptr, ++src) {
      *ptr = *src;
    }
  }
  free(mask);
  mask = cropped;
  w = width;
  h = height;
  return SIZE;
}

void Mask::validateMask () const
{
	// Should be exclusive: MaskBead and MaskEmpty and MaskExclude
	// Should be exclusive: MaskLive and MaskDud and MaskAmbiguous
	// Should be exclusive: MaskTF and MaskLib
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			assert (!(Match (x,y,MaskBead) && Match (x,y,MaskEmpty)));
			assert (!(Match (x,y,MaskBead) && Match (x,y,MaskExclude)));
			assert (!(Match (x,y,MaskEmpty) && Match (x,y,MaskExclude)));
			assert (!(Match (x,y,MaskTF) && Match (x,y,MaskLib)));
			assert (!(Match (x,y,MaskLive) && Match (x,y,MaskDud)));
			assert (!(Match (x,y,MaskLive) && Match (x,y,MaskAmbiguous)));
			assert (!(Match (x,y,MaskDud) && Match (x,y,MaskAmbiguous)));
		}
	}
	return;
}

//
//	mark every pixel OUTSIDE the region-of-interest with MaskExclude
//
void Mask::MarkCrop (Region region, MaskType these)
{
	//---	Mark all wells outside region with MaskType these
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			if (y < region.row){
				mask[x+y*w] = these;
			}
			else if (y > (region.row + region.h)){
				mask[x+y*w] = these;
			}
			else {
				if (x < region.col) {
					mask[x+y*w] = these;
				}
				else if (x > (region.col + region.w)) {
					mask[x+y*w] = these;
				}
				else {
					// This is the central region of interest zone.
				}
			}
		}
	}
}

//
//	mark every pixel INSIDE the region-of-interest with MaskExclude
//
void Mask::MarkRegion (Region region, MaskType these)
{
	//---	Mark all wells inside region with MaskType these
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			if (x >= (region.col) && x < (region.col + region.w)) {
				if (y >= (region.row) && y < (region.row + region.h)) {
					mask[x+y*w] = these;
				}
			}
		}
	}
}

//
//	crop one or more regions from whole chip area.  all wells outside cropped regions
//	are overwritten with MaskExclude.
//
void Mask::CropRegions (Region *regions, int numRegions, MaskType these)
{
	assert (numRegions > 0);
	//fprintf (stderr, "DEBUG: numRegions is %d\n", numRegions);

	//---	For every well location, is it within any cropped region?
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			bool outsider = true;	//default: all points are outside cropped regions
			for (int r = 0; r < numRegions; r++) {
				if (x >= regions[r].col && x < (regions[r].col + regions[r].w)) {
					if (y >= regions[r].row && y < (regions[r].row + regions[r].h)) {
						outsider = false;	// point lies inside cropped region
					}
				}
			}
			if (outsider)
				mask[x+y*w] = these;
		}
	}
}
/*
void Mask::OnlySomeWells(std::vector<int> mWellIdx)
{
  // keep all empties
  // keep all reportables
    for (int y=0; y<h; y++){
      for (int x=0; x<w; x++){
        if (mask[x+y*w]!=MaskEmpty & !binary_search(mWellIdx.begin(),mWellIdx.end(),x+y*w)){
          mask[x+y*w]=MaskExclude;
        }
      }
    }
}*/

void Mask::GetNeighbors (int row, int col, std::vector<int> &wells) const
{
  bool hex = isHexPack();
  if (hex) {
    GetHexNeighbors(row, col, wells);
  }
  else {
    GetSquareNeigbors(row, col, wells);
  }
}

void Mask::AddNeighbor(int row, int col, int rOff, int cOff, std::vector<int> &wells) const
{
  int r = row + rOff;
  int c = col + cOff;
  if (r >= 0 && r < h && c >= 0 && c < w) {
    wells.push_back(ToIndex(r,c));
  }
  else {
    wells.push_back(-1);
  }
}

void Mask::GetHexNeighbors(int row, int col, std::vector<int> &wells) const
{
  wells.resize(0);
  wells.reserve(6);
  if (row % 2 == 0) {
    AddNeighbor(row, col, -1, -1, wells);
    AddNeighbor(row, col,  0, -1, wells);
    AddNeighbor(row, col,  1, -1, wells);
    AddNeighbor(row, col,  1,  0, wells);
    AddNeighbor(row, col,  0,  1, wells);
    AddNeighbor(row, col, -1,  0, wells);
  }
  else {
    AddNeighbor(row, col, -1,  0, wells);
    AddNeighbor(row, col,  0, -1, wells);
    AddNeighbor(row, col,  1,  0, wells);
    AddNeighbor(row, col,  1,  1, wells);
    AddNeighbor(row, col,  0,  1, wells);
    AddNeighbor(row, col, -1,  1, wells);
  }
}
		  
void Mask::GetSquareNeigbors(int row, int col, std::vector<int> &wells) const
{
  wells.resize(0);
  wells.reserve(8);
  AddNeighbor(row, col, -1, -1, wells);
  AddNeighbor(row, col, 0, -1, wells);
  AddNeighbor(row, col, 1, -1, wells);
  AddNeighbor(row, col, 1, 0, wells);
  AddNeighbor(row, col, 1, 1, wells);
  AddNeighbor(row, col, 0, 1, wells);
  AddNeighbor(row, col, -1, 1, wells);
  AddNeighbor(row, col, -1, 0, wells);
}


void Mask::CalculateLiveNeighbors()
{
  std::vector<int> wells;
  if (numLiveNeighbors.size() != (size_t)w*h) {
    numLiveNeighbors.resize(w*h, 0);
  }
  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      GetNeighbors(row, col, wells);
      int idx = ToIndex(row, col);
      numLiveNeighbors[idx] = 0;
      for (size_t wIx = 0; wIx < wells.size(); wIx++) {
	if (wells[wIx] >= 0 && Match(wells[wIx], MaskLive)) {
	  numLiveNeighbors[idx]++;
	}
      }
    }
  }
}

int Mask::GetNumLiveNeighbors(int row, int col)
{
  assert(!numLiveNeighbors.empty());
  return (int)numLiveNeighbors[ToIndex(row,col)];
}
