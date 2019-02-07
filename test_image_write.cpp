#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int CHANNELS = 3; // 3 rgb, 4 rgba
int W = 32; // width
int H = 32; // height

void stbi_wfunc(void *context, void *data, int size) { 
    // context is really a FILE * in my case
    printf("wfunc: %d\n",size);
    fwrite(data, size, 1, (FILE*)context);
}

void pr(char * data, int size) {
    for (int i=0;i<size;i++) {
        printf("%u",(unsigned char)data[i]);
    }
    printf("\n");
}

void set_pixel(char * data, int row, int col, int r, int g, int b) {
    // row * WIDTH * CHANNELS will get you to the correct row of pixels
    // col * CHANNELS will get you to the correct set of triple pixels
    // RGB,0,1,2
    data[(row*W*CHANNELS)+(col*CHANNELS)+0] = r;
    data[(row*W*CHANNELS)+(col*CHANNELS)+1] = g;
    data[(row*W*CHANNELS)+(col*CHANNELS)+2] = b;
}

void test1() {
    FILE * outf = fopen("test.png","w");
    char * data = (char*)malloc(W*H*CHANNELS);
    for (int i=0;i<W;i++) {
        set_pixel(data,15,i,255,0,0);
        set_pixel(data,16,i,0,255,0);
        set_pixel(data,17,i,0,0,255);
    }
    //pr(data,W*H*CHANNELS);

    stbi_write_png_to_func(stbi_wfunc,
        outf, // context - sneaky passing FILE * here
        W,H, // width and height
        CHANNELS, // number of data channels 3==RGB, 4==RGBA, 1 is mono
        data,W*CHANNELS);
    fclose(outf);
    free(data);
}

void test2() {
    char data[W*H*CHANNELS];
    const char * filename = "test2.png";
    for (int i=0;i<W;i++) {
        set_pixel(data,0,i,255,0,0);
        set_pixel(data,2,i,0,255,0);
        set_pixel(data,4,i,0,0,255);
    }
    stbi_write_png(filename,W,H,CHANNELS,data,W*CHANNELS);
}

int main() {
    test1();
    test2();

    return 0;
}