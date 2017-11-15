#ifndef _IMAGE_RESIZER_H_
#define _IMAGE_RESIZER_H_

#define PARAM_IN
#define PARAM_OUT

class ImageResizer
{
public:
    ImageResizer();
    ~ImageResizer();

    void _resizeBilinear_8u1ch(PARAM_IN const unsigned char* const srcImgData,
        PARAM_IN const int srcImgWidth,
        PARAM_IN const int srcImgHeight,
        PARAM_IN const int srcImgWidthstep,
        PARAM_OUT unsigned char* const dstImgData,
        PARAM_IN const int dstImgWidth,
        PARAM_IN const int dstImgHeight,
        PARAM_IN const int dstImgWidthstep);

private:

    void BilinearBorder(PARAM_IN const int width,
        PARAM_IN const int height,
        PARAM_IN const unsigned char* const imgData,
        PARAM_IN const int imgWidthstep,
        PARAM_IN const long x_16,
        PARAM_IN const long y_16,
        PARAM_OUT unsigned char* const result);

    void BilinearFast(PARAM_IN const unsigned char* const PColor0,
        PARAM_IN const unsigned char* const PColor1,
        PARAM_IN const unsigned long u_8,
        PARAM_IN const unsigned long v_8,
        PARAM_OUT unsigned char* const result);

    unsigned char PixelsBound(PARAM_IN const int width,
        PARAM_IN const int height,
        PARAM_IN const unsigned char* const imgData,
        PARAM_IN const int imgWidthstep,
        PARAM_IN long x,
        PARAM_IN long y);

    unsigned char Pixels(PARAM_IN const unsigned char* const imgData,
        PARAM_IN const int imgWidthstep,
        PARAM_IN const long x,
        PARAM_IN const long y);
};

#endif // _IMAGE_RESIZER_H_
