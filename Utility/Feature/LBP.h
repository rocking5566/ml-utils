
//author: jethro shen jethro@ulsee.compare
#include <cmath>  
#include <fstream>

// 
#define	BOUND(x, lowerbound, upperbound)  { (x) = (x) > (lowerbound) ? (x) : (lowerbound); \
                                            (x) = (x) < (upperbound) ? (x) : (upperbound); };
typedef   unsigned char BYTE;
#define PI 3.1415926535897932
#define POW(nBit)   (1 << (nBit))
#define FREE(ptr) 	{if (NULL!=(ptr)) {delete[] ptr;  ptr=NULL;}}

#define LBP_FEADIMEN		59 // 59 or 256

#define XY_NEIGHBOR_POINTS 8

// uniform pattern for LBP without rotation invariance for neighboring points 8 (only for 8)
// If the number of neighboring points is 4, 16 or other numbers than 8, you need to change this lookup array accordingly.
const int  UniformPattern59[256] = {
	1,   2,   3,   4,   5,   0,   6,   7,   8,   0,   0,   0,   9,   0,  10,  11,
	12,   0,   0,   0,   0,   0,   0,   0,  13,   0,   0,   0,  14,   0,  15,  16,
	17,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	18,   0,   0,   0,   0,   0,   0,   0,  19,   0,   0,   0,  20,   0,  21,  22,
	23,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	24,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	25,   0,   0,   0,   0,   0,   0,   0,  26,   0,   0,   0,  27,   0,  28,  29,
	30,  31,   0,  32,   0,   0,   0,  33,   0,   0,   0,   0,   0,   0,   0,  34,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  35,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  36,
	37,  38,   0,  39,   0,   0,   0,  40,   0,   0,   0,   0,   0,   0,   0,  41,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  42,
	43,  44,   0,  45,   0,   0,   0,  46,   0,   0,   0,   0,   0,   0,   0,  47,
	48,  49,   0,  50,   0,   0,   0,  51,  52,  53,   0,  54,  55,  56,  57,  58
};

// For computing the LBP.
static void CreateLBPImage(BYTE *fg, BYTE *lbpIm, int height, int width,
	int FxRadius, int FyRadius,
	int XYNeighborPoints, int BoderLength, int Bincount,
	bool bBilinearInterpolation, double *Histogram);
static void GetLbpHist(BYTE *lbpim, int height, int width,
	int rx, int ry, int rw, int rh,
	int BoderLength, int Bincount, double *Histogram);

// =====================================================================================================//
static void CreateLBPImage(BYTE *fg, BYTE *lbpIm, int height, int width,
	int FxRadius, int FyRadius,
	int XYNeighborPoints, int BoderLength, int Bincount,
	bool bBilinearInterpolation, double *Histogram)
{
	int i, j;
	int xc = 0, yc = 0, ycw = 0;
	BYTE CenterByte;
	BYTE CurrentByte;
	int BasicLBP = 0;
	int FeaBin = 0;
	int p;
	int X, Y, Z;
	float x1, y1, z1;
	float u, v;
	int ltx, lty;
	int lbx, lby;
	int	rtx, rty;
	int rbx, rby;
		
	int yc_add_width;// = yc * width;

	// 20170711, Brown: To speed performance
	float two_PI = 2 * PI;
	const float TO_SPEED = two_PI / XY_NEIGHBOR_POINTS;

	float cos_table[XY_NEIGHBOR_POINTS] = { 0.0f };
	float sin_table[XY_NEIGHBOR_POINTS] = { 0.0f };
	for (int i = 0; i < XY_NEIGHBOR_POINTS; i++)
	{
		cos_table[i] = FxRadius * std::cos(TO_SPEED * i);
		sin_table[i] = FyRadius * std::sin(TO_SPEED * i);
	}

	if (false == bBilinearInterpolation)
	{

		for (yc = BoderLength; yc < height - BoderLength; yc++)
		{
			ycw = yc*width;
			for (xc = BoderLength; xc < width - BoderLength; xc++)
			{
				CenterByte = *(fg + ycw + xc);
				BasicLBP = 0;	FeaBin = 0;

				// In XY plane
				for (p = 0; p < XYNeighborPoints; p++)
				{
					//X = int(xc + FxRadius * cos((2 * PI * p) / XYNeighborPoints) + 0.5);
					//Y = int(yc - FyRadius * sin((2 * PI * p) / XYNeighborPoints) + 0.5);
					X = int(xc + cos_table[p] + 0.5);
					Y = int(yc - sin_table[p] + 0.5);
					BOUND(X, 0, width - 1); BOUND(Y, 0, height - 1);
					CurrentByte = *(fg + Y * width + X);//fg[i][Y][X];
					if (CurrentByte >= CenterByte) BasicLBP += POW(FeaBin);
					FeaBin++;
				}

				//     if "Bincount" is "0", it means basic LBP will be computed 
				//         and "UniformPattern59" does not work in this case. 
				//     Otherwise it should be the number of the uniform patterns, 
				//         then "UniformPattern59" keeps the lookup-table of the 
				//         basic LBP and unifrom LBP.
				if (Bincount == 0) {
					Histogram[BasicLBP]++;
					lbpIm[ycw + xc] = BasicLBP;
				}
				else { // uniform patterns
					Histogram[UniformPattern59[BasicLBP]]++;
					lbpIm[ycw + xc] = UniformPattern59[BasicLBP];
				}

			}//for(xc = BoderLength; xc < width - BoderLength; xc++)
		}//for(yc = BoderLength; yc < height - BoderLength; yc++)

	} // if (true == bUniformPattern) 

	else
	{
		
		for (yc = BoderLength; yc < height - BoderLength; yc++)
		{
			yc_add_width = yc * width;
			for (xc = BoderLength; xc < width - BoderLength; xc++)
			{
				CenterByte = *(fg + yc_add_width + xc);
				BasicLBP = 0;	FeaBin = 0;

				// In XY plane
				for (p = 0; p < XYNeighborPoints; p++)
				{
					//		bilinear interpolation
					//x1 = float(xc + FxRadius * cos((two_PI * p) / XYNeighborPoints));
					//y1 = float(yc - FyRadius * sin((two_PI * p) / XYNeighborPoints));
					x1 = float(xc + cos_table[p]);
					y1 = float(yc - sin_table[p]);
					
					u = x1 - (int)(x1);
					v = y1 - (int)(y1);
					ltx = (int)(floor(x1)); lty = (int)(floor(y1));
					lbx = (int)(floor(x1)); lby = (int)(ceil(y1));
					rtx = (int)(ceil(x1)); rty = (int)(floor(y1));
					rbx = (int)(ceil(x1)); rby = (int)(ceil(y1));
					// values of neighbors that do not fall exactly on pixels are estimated
					// by bilinear interpolation of four corner points near to it.

					BYTE va = *(fg + lty*width + ltx);
					BYTE vb = *(fg + lby*width + lbx);
					BYTE vc = *(fg + rty*width + rtx);
					BYTE vd = *(fg + rby*width + rbx);

					CurrentByte = (BYTE)(va * (1 - u) * (1 - v) + \
						vb * (1 - u) * v + \
						vc * u * (1 - v) + \
						vd  * u * v);
					if (CurrentByte >= CenterByte) BasicLBP += POW(FeaBin);
					FeaBin++;

				}


				//     if "Bincount" is "0", it means basic LBP will be computed 
				//         and "UniformPattern59" does not work in this case. 
				//     Otherwise it should be the number of the uniform patterns, 
				//         then "UniformPattern59" keeps the lookup-table of the 
				//         basic LBP and unifrom LBP.
				//if (Bincount == 0) {
				//	Histogram[BasicLBP]++;
				//	lbpIm[ycw + xc] = BasicLBP;
				//}
				//else { // uniform patterns
				//	Histogram[UniformPattern59[BasicLBP]]++;
					lbpIm[ycw + xc] = UniformPattern59[BasicLBP];
				//}

			}//for(xc = BoderLength; xc < width - BoderLength; xc++)
		}//for(yc = BoderLength; yc < height - BoderLength; yc++)

	} // if (true == bUniformPattern) 

	  //-------------  Normalization ----------------------------//
	  // Normaliztion
	//int Total = 0;

	//for (i = 0; i < Bincount; i++)
	//	Total += int(Histogram[i]);
	//for (i = 0; i < Bincount; i++)
	//{
	//	Histogram[i] /= Total;
	//}
	//-------------  Normalization ----------------------------//

}

static void GetLbpHist(BYTE *lbpim, int height, int width,
	int rx, int ry, int rw, int rh,
	int BoderLength, int Bincount, double *Histogram)
{
	int i, j, ii, sx, ex, sy, ey;
	//BYTE CenterByte;	

	memset(Histogram, 0, sizeof(float)*Bincount);
	if (rx<0 || ry<0 || rw<1 || rh<1 || height<5 || width<5 || (rx + rw) >= width || (ry + rh) >= height)
		return;

	sx = rx;
	sy = ry;
	ex = rx + rw;
	ey = ry + rh;

	sx = (sx<BoderLength) ? BoderLength : sx;
	sy = (sy<BoderLength) ? BoderLength : sy;
	ex = (ex>(width - BoderLength)) ? (width - BoderLength) : ex;
	ey = (ey>(height - BoderLength)) ? (height - BoderLength) : ey;

	// Get LBP patterns values from input image
	for (i = sy; i < ey; i++) {
		ii = i*width;
		for (j = sx; j < ex; j++) {
			//CenterByte = *( lbpim + ii + j );				
			Histogram[*(lbpim + ii + j)]++;
		}
	}

	//// Normaliztion
	//j = 0; // Total		
	//for(i = 0; i < Bincount; i++){  
	//	j += int (Histogram[i]);
	//}
	//for(i = 0; i < Bincount; i++){
	//	Histogram[i] /= j;   	
	//}		
}
// =====================================================================================================//
// =====================================================================================================//

