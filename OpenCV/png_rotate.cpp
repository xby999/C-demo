#include <iostream>
#include <png.h>

void rotatePngImage(const char* inputFilePath, const char* outputFilePath)
{
    FILE* inputFile = fopen(inputFilePath, "rb");
    if (!inputFile)
    {
        std::cout << "无法打开输入文件" << std::endl;
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png)
    {
        std::cout << "无法创建PNG读取结构" << std::endl;
        fclose(inputFile);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        std::cout << "无法创建PNG信息结构" << std::endl;
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(inputFile);
        return;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        std::cout << "PNG读取错误" << std::endl;
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(inputFile);
        return;
    }

    png_init_io(png, inputFile);
    png_read_info(png, info);

    png_uint_32 width = png_get_image_width(png, info);
    png_uint_32 height = png_get_image_height(png, info);
    png_byte colorType = png_get_color_type(png, info);
    png_byte bitDepth = png_get_bit_depth(png, info);

    // 读取PNG图像的像素数据
    png_bytep* rowPointers = new png_bytep[height];
    for (png_uint_32 y = 0; y < height; ++y)
    {
        rowPointers[y] = new png_byte[png_get_rowbytes(png, info)];
    }
    png_read_image(png, rowPointers);

    // 创建旋转后的图像像素数据
    png_bytep* rotatedRowPointers = new png_bytep[width];
    for (png_uint_32 x = 0; x < width; ++x)
    {
        rotatedRowPointers[x] = new png_byte[height * png_get_channels(png, info)];
    }

    // 执行逆时针旋转90度
    for (png_uint_32 y = 0; y < height; ++y)
    {
        for (png_uint_32 x = 0; x < width; ++x)
        {
            png_bytep pixel = &(rowPointers[y][x * png_get_channels(png, info)]);
            png_bytep rotatedPixel = &(rotatedRowPointers[x][(height - y - 1) * png_get_channels(png, info)]);
            for (int i = 0; i < png_get_channels(png, info); ++i)
            {
                rotatedPixel[i] = pixel[i];
            }
        }
    }

    // 创建旋转后的PNG写入结构
    FILE* outputFile = fopen(outputFilePath, "wb");
    if (!outputFile)
    {
        std::cout << "无法创建输出文件" << std::endl;
        for (png_uint_32 x = 0; x < width; ++x)
        {
            delete[] rotatedRowPointers[x];
        }
        delete[] rotatedRowPointers;
        for (png_uint_32 y = 0; y < height; ++y)
        {
            delete[] rowPointers[y];
        }
        delete[] rowPointers;
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(inputFile);
        return;
    }

    png_structp outputPng = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!outputPng)
    {
        std::cout << "无法创建PNG写入结构" << std::endl;
        for (png_uint_32 x = 0; x < width; ++x)
        {
            delete[] rotatedRowPointers[x];
        }
        delete[] rotatedRowPointers;
        for (png_uint_32 y = 0; y < height; ++y)
        {
            delete[] rowPointers[y];
        }
        delete[] rowPointers;
        fclose(outputFile);
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(inputFile);
        return;
    }

    png_infop outputInfo = png_create_info_struct(outputPng);
    if (!outputInfo)
    {
        std::cout << "无法创建PNG输出信息结构" << std::endl;
        for (png_uint_32 x = 0; x < width; ++x)
        {
            delete[] rotatedRowPointers[x];
        }
        delete[] rotatedRowPointers;
        for (png_uint_32 y = 0; y < height; ++y)
        {
            delete[] rowPointers[y];
        }
        delete[] rowPointers;
        png_destroy_write_struct(&outputPng, nullptr);
        fclose(outputFile);
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(inputFile);
        return;
    }

    if (setjmp(png_jmpbuf(outputPng)))
    {
        std::cout << "PNG写入错误" << std::endl;
        for (png_uint_32 x = 0; x < width; ++x)
        {
            delete[] rotatedRowPointers[x];
        }
        delete[] rotatedRowPointers;
        for (png_uint_32 y = 0; y < height; ++y)
        {
            delete[] rowPointers[y];
        }
        delete[] rowPointers;
        png_destroy_write_struct(&outputPng, &outputInfo);
        fclose(outputFile);
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(inputFile);
        return;
    }

    png_init_io(outputPng, outputFile);
    png_set_IHDR(outputPng, outputInfo, height, width, bitDepth, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(outputPng, outputInfo);

    // 写入旋转后的PNG图像
    png_write_image(outputPng, rotatedRowPointers);
    png_write_end(outputPng, nullptr);

    // 释放内存和关闭文件
    for (png_uint_32 x = 0; x < width; ++x)
    {
        delete[] rotatedRowPointers[x];
    }
    delete[] rotatedRowPointers;
    for (png_uint_32 y = 0; y < height; ++y)
    {
        delete[] rowPointers[y];
    }
    delete[] rowPointers;
    png_destroy_write_struct(&outputPng, &outputInfo);
    fclose(outputFile);
    png_destroy_read_struct(&png, &info, nullptr);
    fclose(inputFile);
}

int main()
{
    const char* inputFilePath = "input.png";
    const char* outputFilePath = "output.png";

    rotatePngImage(inputFilePath, outputFilePath);

    return 0;
}
