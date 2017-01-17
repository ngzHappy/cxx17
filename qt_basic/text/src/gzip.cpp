﻿#include "../gzip.hpp"
#include "../private_qt3rd_base_library/zlib/zlib.h"
#include <QtCore/qbytearray.h>
#include <type_traits>

#define GZIP_WINDOWS_BIT (15 + 16)
#define GZIP_CHUNK_SIZE (32 * 1024)

namespace _gzip {

namespace {
/**
 * @brief Compresses the given buffer using the standard GZIP algorithm
 * @param input The buffer to be compressed
 * @param output The result of the compression
 * @param level The compression level to be used (@c 0 = no compression, @c 9 = max, @c -1 = default)
 * @return @c true if the compression was successful, @c false otherwise
 */
bool QCompressor_gzipCompress(
        const char * input_begin,
        const char * input_end,
        QByteArray &output,
        int level) {
    auto input_length=input_end-input_begin;
    static_assert(std::is_signed<decltype(input_length)>::value,"core error???");

    // Prepare output
    output.clear();

    // Is there something to do?
    if (input_length>0) {
        // Declare vars
        int flush=0;

        // Prepare deflater status
        z_stream strm;
        strm.zalloc=Z_NULL;
        strm.zfree=Z_NULL;
        strm.opaque=Z_NULL;
        strm.avail_in=0;
        strm.next_in=Z_NULL;

        // Initialize deflater
        int ret=deflateInit2(&strm,qMax(-1,qMin(9,level)),Z_DEFLATED,GZIP_WINDOWS_BIT,8,Z_DEFAULT_STRATEGY);

        if (ret!=Z_OK)
            return(false);

        // Prepare output
        output.clear();

        // Extract pointer to input data
        const char *input_data=input_begin;
        auto input_data_left=input_length;

        // Compress data until available
        do {
            // Determine current chunk size
            int chunk_size=qMin(GZIP_CHUNK_SIZE,input_data_left);

            // Set deflater references
            strm.next_in=(unsigned char*)input_data;
            strm.avail_in=chunk_size;

            // Update interval variables
            input_data+=chunk_size;
            input_data_left-=chunk_size;

            // Determine if it is the last chunk
            flush=(input_data_left<=0?Z_FINISH:Z_NO_FLUSH);

            // Deflate chunk and cumulate output
            do {

                // Declare vars
                char out[GZIP_CHUNK_SIZE];

                // Set deflater references
                strm.next_out=(unsigned char*)out;
                strm.avail_out=GZIP_CHUNK_SIZE;

                // Try to deflate chunk
                ret=deflate(&strm,flush);

                // Check errors
                if (ret==Z_STREAM_ERROR) {
                    // Clean-up
                    deflateEnd(&strm);

                    // Return
                    return(false);
                }

                // Determine compressed size
                int have=(GZIP_CHUNK_SIZE-strm.avail_out);

                // Cumulate result
                if (have>0)
                    output.append((char*)out,have);

            } while (strm.avail_out==0);

        } while (flush!=Z_FINISH);

        // Clean-up
        (void)deflateEnd(&strm);

        // Return
        return(ret==Z_STREAM_END);
    }
    else
        return(true);
}

/**
 * @brief Decompresses the given buffer using the standard GZIP algorithm
 * @param input The buffer to be decompressed
 * @param output The result of the decompression
 * @return @c true if the decompression was successfull, @c false otherwise
 */
bool QCompressor_gzipDecompress(
        const char * input_begin,
        const char * input_end,
        QByteArray &output) {
    auto input_length=input_end-input_begin;
    static_assert(std::is_signed<decltype(input_length)>::value,"core error???");

    // Prepare output
    output.clear();

    // Is there something to do?
    if (input_length>0) {
        // Prepare inflater status
        z_stream strm;
        strm.zalloc=Z_NULL;
        strm.zfree=Z_NULL;
        strm.opaque=Z_NULL;
        strm.avail_in=0;
        strm.next_in=Z_NULL;

        // Initialize inflater
        int ret=inflateInit2(&strm,GZIP_WINDOWS_BIT);

        if (ret!=Z_OK)
            return(false);

        // Extract pointer to input data
        const char *input_data=input_begin;
        auto input_data_left=input_length;

        // Decompress data until available
        do {
            // Determine current chunk size
            int chunk_size=qMin(GZIP_CHUNK_SIZE,input_data_left);

            // Check for termination
            if (chunk_size<=0)
                break;

            // Set inflater references
            strm.next_in=(unsigned char*)input_data;
            strm.avail_in=chunk_size;

            // Update interval variables
            input_data+=chunk_size;
            input_data_left-=chunk_size;

            // Inflate chunk and cumulate output
            do {

                // Declare vars
                char out[GZIP_CHUNK_SIZE];

                // Set inflater references
                strm.next_out=(unsigned char*)out;
                strm.avail_out=GZIP_CHUNK_SIZE;

                // Try to inflate chunk
                ret=inflate(&strm,Z_NO_FLUSH);

                switch (ret) {
                    case Z_NEED_DICT:
                        ret=Z_DATA_ERROR;
                    case Z_DATA_ERROR:
                    case Z_MEM_ERROR:
                    case Z_STREAM_ERROR:
                        // Clean-up
                        inflateEnd(&strm);

                        // Return
                        return(false);
                }

                // Determine decompressed size
                int have=(GZIP_CHUNK_SIZE-strm.avail_out);

                // Cumulate result
                if (have>0)
                    output.append((char*)out,have);

            } while (strm.avail_out==0);

        } while (ret!=Z_STREAM_END);

        // Clean-up
        inflateEnd(&strm);

        // Return
        return (ret==Z_STREAM_END);
    }
    else
        return(true);
}

}/*namespace*/

}/*namespace _gzip*/

namespace text {

QByteArray gzip(const char*a,const char*b) {
    QByteArray varAns;
    if (_gzip::QCompressor_gzipCompress(a,b,varAns,-1)) {
        return std::move(varAns);
    }
    return{};
}

QByteArray ungzip(const char *a,const char *b) {
    QByteArray varAns;
    if (_gzip::QCompressor_gzipDecompress(a,b,varAns)) {
        return std::move(varAns);
    }
    return{};
}

}/*namespace text*/

/*
 * endl of the file
*/


