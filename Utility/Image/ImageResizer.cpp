#include "ImageResizer.h"

#define MAX_SCALED_WIDTH 5000

ImageResizer::ImageResizer()
{

}

ImageResizer::~ImageResizer()
{

}

void ImageResizer::_resizeBilinear_8u1ch(PARAM_IN const unsigned char* const srcImgData,
    PARAM_IN const int srcImgWidth,
    PARAM_IN const int srcImgHeight,
    PARAM_IN const int srcImgWidthstep,
    PARAM_OUT unsigned char* const dstImgData,
    PARAM_IN const int dstImgWidth,
    PARAM_IN const int dstImgHeight,
    PARAM_IN const int dstImgWidthstep)
{
    if ((0 == srcImgWidth) || (0 == srcImgHeight) || (0 == dstImgWidth) || (0 == dstImgHeight))
    {
        return;
    }

    long xrIntFloat_16 = ((srcImgWidth) << 16) / dstImgWidth + 1;
    long yrIntFloat_16 = ((srcImgHeight) << 16) / dstImgHeight + 1;
    const long csDErrorX = -(1 << 15) + (xrIntFloat_16 >> 1);
    const long csDErrorY = -(1 << 15) + (yrIntFloat_16 >> 1);

    const int dst_width = dstImgWidth;

    long border_y0 = -csDErrorY / yrIntFloat_16 + 1;                          // y0+y*yr>=0; y0=csDErrorY => y>=-csDErrorY/yr
    if (border_y0 >= dstImgHeight) border_y0 = dstImgHeight;
    long border_x0 = -csDErrorX / xrIntFloat_16 + 1;
    if (border_x0 >= dstImgWidth) border_x0 = dstImgWidth;
    long border_y1 = (((srcImgHeight - 2) << 16) - csDErrorY) / yrIntFloat_16 + 1; 	//y0+y*yr<=(height-2) => y<=(height-2-csDErrorY)/yr
    if (border_y1 < border_y0) border_y1 = border_y0;
    long border_x1 = (((srcImgWidth) << 16) - csDErrorX) / xrIntFloat_16 + 1;
    if (border_x1 < border_x0) border_x1 = border_x0;

    unsigned char * pDstLine = (unsigned char *)dstImgData;
    long Src_byte_width = srcImgWidthstep;
    long srcy_16 = csDErrorY;
    int x, y;
    long srcx_16;

    for (y = 0; y < border_y0; ++y)
    {
        srcx_16 = csDErrorX;

        for (x = 0; x < dst_width; ++x)
        {
            BilinearBorder(srcImgWidth, srcImgHeight, srcImgData, srcImgWidthstep, srcx_16, srcy_16, &pDstLine[x]); //border
            srcx_16 += xrIntFloat_16;
        }

        srcy_16 += yrIntFloat_16;
        pDstLine += dstImgWidthstep;
    }

    for (y = border_y0; y < border_y1; ++y)
    {
        srcx_16 = csDErrorX;

        for (x = 0; x < border_x0; ++x)
        {
            BilinearBorder(srcImgWidth, srcImgHeight, srcImgData, srcImgWidthstep, srcx_16, srcy_16, &pDstLine[x]);//border
            srcx_16 += xrIntFloat_16;
        }

        {
            unsigned long v_8 = (srcy_16 & 0xFFFF) >> 8;
            unsigned char* PSrcLineColor = (unsigned char*)(srcImgData + Src_byte_width*(srcy_16 >> 16));
            for (long x = border_x0; x < border_x1; ++x)
            {
                unsigned char* PColor0 = &PSrcLineColor[srcx_16 >> 16];
                unsigned char* PColor1 = (unsigned char*)(PColor0 + Src_byte_width);
                BilinearFast(PColor0, PColor1, (srcx_16 & 0xFFFF) >> 8, v_8, &pDstLine[x]);
                srcx_16 += xrIntFloat_16;
            }
        }

        for (x = border_x1; x < dst_width; ++x)
        {
            BilinearBorder(srcImgWidth, srcImgHeight, srcImgData, srcImgWidthstep, srcx_16, srcy_16, &pDstLine[x]);//border
            srcx_16 += xrIntFloat_16;
        }

        srcy_16 += yrIntFloat_16;
        pDstLine += dstImgWidthstep;
    }

    for (y = border_y1; y < dstImgHeight; ++y)
    {
        srcx_16 = csDErrorX;

        for (x = 0; x < dst_width; ++x)
        {
            BilinearBorder(srcImgWidth, srcImgHeight, srcImgData, srcImgWidthstep, srcx_16, srcy_16, &pDstLine[x]); //border
            srcx_16 += xrIntFloat_16;
        }

        srcy_16 += yrIntFloat_16;
        pDstLine += dstImgWidthstep;
    }
}

unsigned char ImageResizer::Pixels(PARAM_IN const unsigned char* const imgData,
    PARAM_IN const int imgWidthstep,
    PARAM_IN const long x,
    PARAM_IN const long y)
{
    return ((unsigned char*)(imgData + imgWidthstep*y))[x];
}

unsigned char ImageResizer::PixelsBound(PARAM_IN const int width,
    PARAM_IN const int height,
    PARAM_IN const unsigned char* const imgData,
    PARAM_IN const int imgWidthstep,
    PARAM_IN long x,
    PARAM_IN long y)
{
    if (x < 0)
    {
        x = 0;
    }
    else if (x >= width)
    {
        x = width - 1;
    }
    if (y < 0)
    {
        y = 0;
    }
    else if (y >= height)
    {
        y = height - 1;
    }
    unsigned char result = Pixels(imgData, imgWidthstep, x, y);
    return result;
}

void ImageResizer::BilinearFast(PARAM_IN const unsigned char* const PColor0,
    PARAM_IN const unsigned char* const PColor1,
    PARAM_IN const unsigned long u_8,
    PARAM_IN const unsigned long v_8,
    PARAM_OUT unsigned char* const result)
{
    unsigned long pm3_16 = u_8*v_8;
    unsigned long pm2_16 = (u_8 << 8) - pm3_16;
    unsigned long pm1_16 = (v_8 << 8) - pm3_16;
    unsigned long pm0_16 = (1 << 16) - pm1_16 - pm2_16 - pm3_16;

    *result = (unsigned char)((pm0_16*PColor0[0] + pm2_16*PColor0[1] + pm1_16*PColor1[0] + pm3_16*PColor1[1]) >> 16);
}

void ImageResizer::BilinearBorder(PARAM_IN const int width,
    PARAM_IN const int height,
    PARAM_IN const unsigned char* const imgData,
    PARAM_IN const int imgWidthstep,
    PARAM_IN const long x_16,
    PARAM_IN const long y_16,
    PARAM_OUT unsigned char* const result)
{
    long x = (x_16 >> 16);
    long y = (y_16 >> 16);
    unsigned long u_16 = ((unsigned short)(x_16));
    unsigned long v_16 = ((unsigned short)(y_16));

    unsigned char pixel[4];

    pixel[0] = PixelsBound(width, height, imgData, imgWidthstep, x, y);
    pixel[1] = PixelsBound(width, height, imgData, imgWidthstep, x + 1, y);
    pixel[2] = PixelsBound(width, height, imgData, imgWidthstep, x, y + 1);
    pixel[3] = PixelsBound(width, height, imgData, imgWidthstep, x + 1, y + 1);

    BilinearFast(&pixel[0], &pixel[2], u_16 >> 8, v_16 >> 8, result);
}
