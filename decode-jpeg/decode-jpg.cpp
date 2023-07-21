#include <fstream>
#include <turbojpeg.h>
#include <sys/types.h>
#include <malloc.h>
#include <sys/stat.h> 
#include <sys/time.h>

unsigned long long GetTime( void )
{
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);

    return tv.tv_sec * 1000000ULL + tv.tv_usec;
}
int tjpeg2yuv(unsigned char* jpeg_buffer, int jpeg_size, unsigned char** yuv_buffer, int* yuv_size, int* yuv_type)
{
    tjhandle handle = NULL;
    int width, height, subsample, colorspace;
    int flags = 0;
    int padding = 4; //1 or 4 is ok
    int ret = 0;
    unsigned long long t1 = GetTime();
    handle = tjInitDecompress();
    tjDecompressHeader3(handle, jpeg_buffer, jpeg_size, &width, &height, &subsample, &colorspace);

    printf("w: %d h: %d subsample: %d color: %d\n", width, height, subsample, colorspace);

    flags |= 0;

    *yuv_type = subsample;
    *yuv_size = tjBufSizeYUV2(width, padding, height, subsample);
    *yuv_buffer =(unsigned char *)malloc(*yuv_size);
    if (*yuv_buffer == NULL)
    {
        printf("malloc buffer for rgb failed.\n");
        return -1;
    }
    ret = tjDecompressToYUV2(handle, jpeg_buffer, jpeg_size, *yuv_buffer, width,
                             padding, height, flags);
    if (ret < 0)
    {
        printf("compress to jpeg failed: %s\n", tjGetErrorStr());
    }
    tjDestroy(handle);

    return ret;
}

int main(int argc, char* argv[]) {
    printf("================= Decode JPEG to YUV =================\n");
    char *inJpegName3 = "input.jpg";
    FILE *jpegFile = fopen(inJpegName3, "rb");

    struct stat statbuf;
    stat(inJpegName3, &statbuf);
    int fileLen=statbuf.st_size;
    printf("fileLength2: %d\n", fileLen);

    uint8_t *jpegData = (uint8_t *)malloc(fileLen);
    fread(jpegData, fileLen, 1, jpegFile);
    fclose(jpegFile);

    uint8_t *yuvData;
    int yuvSize;
    int yuvType;
    unsigned long long t1 = GetTime();
    tjpeg2yuv(jpegData, fileLen, &yuvData, &yuvSize, &yuvType);
    unsigned long long t2 = GetTime();
	printf("run time of resize: %llu microseconds for 1 frame \n", t2-t1);

    printf("size: %d; type: %d\n", yuvSize, yuvType);

    char *yuvSuffix;
    if(yuvType == TJSAMP_444) {
        yuvSuffix = ".yuv444";
    } else if(yuvType == TJSAMP_422) {
        yuvSuffix = ".yuv422";
    } else if(yuvType == TJSAMP_420) {
        yuvSuffix = ".yuv420";
    } else if(yuvType == TJSAMP_GRAY) {
        yuvSuffix = ".yuv-gray";
    } else if(yuvType == TJSAMP_440) {
        yuvSuffix = ".yuv440";
    } else if(yuvType == TJSAMP_411) {
        yuvSuffix = ".yuv411";
    } else {
        printf("Unsupported type!");
        return -1;
    }
    printf("yuv samp: %s\n", yuvSuffix);

    char yuvFileName[100];
    sprintf(yuvFileName, "input%s", yuvSuffix);
    FILE *yuvFile = fopen(yuvFileName, "wb");
    fwrite(yuvData, yuvSize, 1, yuvFile);

    free(jpegData);
    free(yuvData);
    fflush(yuvFile);
    fclose(yuvFile);
    printf("=============== Decode JPEG to YUV ===============\n\n");
}