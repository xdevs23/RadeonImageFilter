﻿/*****************************************************************************\
*
*  Module Name    RadeonImageFilters.h
*  Project        RadeonImageFilters
*
*  Description    Radeon Image Filters Interface header
*
*  Copyright 2019 Advanced Micro Devices, Inc.
*
*  All rights reserved. This notice is intended as a precaution against
*  inadvertent publication and does not imply publication or any waiver
*  of confidentiality. The year included in the foregoing notice is the
*  year of creation of the work.
*
\*****************************************************************************/
/** @file */

#pragma once

#ifndef __RADEONIMAGEFILTERS_H
#define __RADEONIMAGEFILTERS_H


#if !RIF_STATIC_LIBRARY
#if defined(WIN32) || defined(_WIN32)
   #ifdef EXPORT_API
      #define RIF_API_ENTRY __declspec(dllexport)
   #else
      #define RIF_API_ENTRY __declspec(dllimport)
#endif
#elif defined(__GNUC__)
   #ifdef EXPORT_API
      #define RIF_API_ENTRY __attribute__((visibility ("default")))
   #else
      #define RIF_API_ENTRY
   #endif
#endif
#else
#define RIF_API_ENTRY
#endif

#if defined(__GNUC__) || defined(__clang__)
#define RIF_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define RIF_DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement deprecated for this compiler")
#define RIF_DEPRECATED
#endif

#if defined(__APPLE__)
#include "stddef.h"
#include <stdint.h>
#elif defined(__cplusplus)
#include "cstddef"
#include <cstdint>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define RIF_VERSION_MAJOR 1
#define RIF_VERSION_MINOR 5
#define RIF_VERSION_REVISION 0
#define RIF_COMMIT_INFO  0x53fccd8

#ifndef RIF_COMMIT_INFO
#define RIF_VERSION_BUILD               0
#else
#define RIF_VERSION_BUILD               RIF_COMMIT_INFO
#endif

#define RIF_MAKE_VERSION(major, minor, revision, build) \
    (((uint64_t)(major) << 58) | ((uint64_t)(minor) << 50) | ((uint64_t)(revision) << 32) | build)

#define RIF_API_VERSION RIF_MAKE_VERSION(RIF_VERSION_MAJOR, RIF_VERSION_MINOR, RIF_VERSION_REVISION, RIF_VERSION_BUILD)

/* rif_status */
#define RIF_SUCCESS 0
#define RIF_ERROR_COMPUTE_API_NOT_SUPPORTED -1
#define RIF_ERROR_OUT_OF_SYSTEM_MEMORY -2
#define RIF_ERROR_OUT_OF_VIDEO_MEMORY -3
#define RIF_ERROR_INVALID_IMAGE -6
#define RIF_ERROR_UNSUPPORTED_IMAGE_FORMAT -8
#define RIF_ERROR_INVALID_GL_TEXTURE -9
#define RIF_ERROR_INVALID_CL_IMAGE -10
#define RIF_ERROR_INVALID_OBJECT -11
#define RIF_ERROR_INVALID_PARAMETER -12
#define RIF_ERROR_INVALID_TAG -13
#define RIF_ERROR_INVALID_CONTEXT -15
#define RIF_ERROR_INVALID_QUEUE -16
#define RIF_ERROR_INVALID_FILTER -17
#define RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME -18
#define RIF_ERROR_UNIMPLEMENTED -19
#define RIF_ERROR_INVALID_API_VERSION -20
#define RIF_ERROR_INTERNAL_ERROR -21
#define RIF_ERROR_IO_ERROR -22
#define RIF_ERROR_INVALID_PARAMETER_TYPE -23
#define RIF_ERROR_UNSUPPORTED -24

/* rif_parameter_type */
#define RIF_PARAMETER_TYPE_FLOAT    0
#define RIF_PARAMETER_TYPE_FLOAT1   0
#define RIF_PARAMETER_TYPE_FLOAT2   1
#define RIF_PARAMETER_TYPE_FLOAT3   2
#define RIF_PARAMETER_TYPE_FLOAT4   3
#define RIF_PARAMETER_TYPE_FLOAT8   4
#define RIF_PARAMETER_TYPE_FLOAT16  5

#define RIF_PARAMETER_TYPE_UINT     6
#define RIF_PARAMETER_TYPE_UINT1    6
#define RIF_PARAMETER_TYPE_UINT2    7
#define RIF_PARAMETER_TYPE_UINT3    8
#define RIF_PARAMETER_TYPE_UINT4    9
#define RIF_PARAMETER_TYPE_UINT8   10
#define RIF_PARAMETER_TYPE_UINT16  11

#define RIF_PARAMETER_TYPE_INT     12
#define RIF_PARAMETER_TYPE_INT1    12
#define RIF_PARAMETER_TYPE_INT2    13
#define RIF_PARAMETER_TYPE_INT3    14
#define RIF_PARAMETER_TYPE_INT4    15
#define RIF_PARAMETER_TYPE_INT8    16
#define RIF_PARAMETER_TYPE_INT16   17

#define RIF_PARAMETER_TYPE_IMAGE   18
#define RIF_PARAMETER_TYPE_STRING  19
#define RIF_PARAMETER_TYPE_FLOAT_ARRAY  20
#define RIF_PARAMETER_TYPE_UINT_ARRAY   21
#define RIF_PARAMETER_TYPE_INT_ARRAY    22
#define RIF_PARAMETER_TYPE_IMAGE_ARRAY  23
#define RIF_PARAMETER_TYPE_LOCAL_MEMORY 24

/* rif_compute_type */
#define RIF_COMPUTE_TYPE_FLOAT 0x0
#define RIF_COMPUTE_TYPE_FLOAT16 0x1


/* rif_backend_api_type */
#define RIF_BACKEND_API_OPENCL 0
#define RIF_BACKEND_API_METAL 1
#define RIF_BACKEND_API_DIRECTX12 2

/* rif_image_info */
#define RIF_IMAGE_DESC 0x301
#define RIF_IMAGE_DATA_SIZEBYTE 0x302

/* rif_image_format */
/* rif_component_type */
#define RIF_COMPONENT_TYPE_UINT8 0x1
#define RIF_COMPONENT_TYPE_FLOAT16 0x2
#define RIF_COMPONENT_TYPE_FLOAT32 0x3

/* rif_image_map_type */
#define RIF_IMAGE_MAP_READ 0x1
#define RIF_IMAGE_MAP_WRITE 0x2

/*rif_image_filter_type*/
#define RIF_IMAGE_FILTER_NORMALIZATION 0x1
#define RIF_IMAGE_FILTER_GAMMA_CORRECTION 0x2
#define RIF_IMAGE_FILTER_RESAMPLE 0x3
#define RIF_IMAGE_FILTER_RESAMPLE_DYNAMIC 0x24
#define RIF_IMAGE_FILTER_REMAP_RANGE 0x28
//blurring
#define RIF_IMAGE_FILTER_GAUSSIAN_BLUR 0x4
#define RIF_IMAGE_FILTER_MOTION_BLUR 0x1F
// tone mapping filters
#define RIF_IMAGE_FILTER_COLOR_SPACE 0x5
#define RIF_IMAGE_FILTER_HUE_SATURATION 0x6
#define RIF_IMAGE_FILTER_FILMIC_TONEMAP 0x7
#define RIF_IMAGE_FILTER_REINHARD02_TONEMAP 0x8
#define RIF_IMAGE_FILTER_EXPONENTIAL_TONEMAP 0x9
#define RIF_IMAGE_FILTER_LINEAR_TONEMAP 0xA
#define RIF_IMAGE_FILTER_DRAGO_TONEMAP 0xB
//denoising filters
#define RIF_IMAGE_FILTER_BILATERAL_DENOISE 0xC
#define RIF_IMAGE_FILTER_LWR_DENOISE 0xD
#define RIF_IMAGE_FILTER_EAW_DENOISE 0xE
#define RIF_IMAGE_FILTER_MEDIAN_DENOISE 0x1E
//machine learning based denoising filters
#define RIF_IMAGE_FILTER_AI_DENOISE 0x3E
#define RIF_IMAGE_FILTER_AI_UPSCALE 0x3F
#define RIF_CUSTOM_AI_MODEL 0x32
#define RIF_IMAGE_FILTER_OPENIMAGE_DENOISE 0x4E

//Anti-aliasing
#define RIF_IMAGE_FILTER_MLAA 0xF
//edge detection
#define RIF_IMAGE_FILTER_SOBEL 0x10
#define RIF_IMAGE_FILTER_LAPLACE 0x11
#define RIF_IMAGE_FILTER_EMBOSS 0x20
//Blending
#define RIF_IMAGE_FILTER_WEIGHTED_SUM 0x12
#define RIF_IMAGE_FILTER_MULT 0x13
#define RIF_IMAGE_FILTER_SCALAR_MULT 0x31
//enhance
#define RIF_IMAGE_FILTER_SHARPEN 0x14
//other
#define RIF_IMAGE_FILTER_MOTION_BUFFER 0x15
#define RIF_IMAGE_FILTER_TEMPORAL_ACCUMULATOR 0x16
#define RIF_IMAGE_FILTER_SHADOW_CATCHER 0x17
#define RIF_IMAGE_FILTER_USER_DEFINED 0x18
#define RIF_IMAGE_FILTER_DILATE_ERODE 0x1A
#define RIF_IMAGE_FILTER_POSTERIZE 0x1B
#define RIF_IMAGE_FILTER_BLOOM 0x30
#define RIF_IMAGE_FILTER_DEPTH_OF_FIELD 0x33
#define RIF_IMAGE_FILTER_NDC_DEPTH 0x34
#define RIF_IMAGE_FILTER_CONVERT 0x35
#define RIF_IMAGE_FILTER_BGRA_TO_RGBA 0x36
//Noise
#define RIF_IMAGE_FILTER_SPREAD 0x1C
#define RIF_IMAGE_FILTER_RGB_NOISE 0x1D
//Rotate
#define RIF_IMAGE_FILTER_FLIP_VERT 0x21
#define RIF_IMAGE_FILTER_FLIP_HOR 0x22
#define RIF_IMAGE_FILTER_ROTATE 0x23
//More tonemap filters
#define RIF_IMAGE_FILTER_AUTOLINEAR_TONEMAP 0x25
#define RIF_IMAGE_FILTER_MAXWHITE_TONEMAP 0x26
#define RIF_IMAGE_FILTER_PHOTO_LINEAR_TONEMAP 0x27
#define RIF_IMAGE_FILTER_PHOTO_TONEMAP 0x29
#define RIF_IMAGE_FILTER_FILMIC_UNCHARTED_TONEMAP 0x4F

//Depth of field kernel size parameter values
#define RIF_DEPTH_OF_FIELD_FILTER_KERNEL_SIZE_SMALL 0x0u
#define RIF_DEPTH_OF_FIELD_FILTER_KERNEL_SIZE_MEDIUM 0x1u
#define RIF_DEPTH_OF_FIELD_FILTER_KERNEL_SIZE_LARGE 0x2u
#define RIF_DEPTH_OF_FIELD_FILTER_KERNEL_SIZE_VERY_LARGE 0x3u

/*rif_image_filter_interpolation_operator*/
#define RIF_IMAGE_INTERPOLATION_NEAREST 0x0
#define RIF_IMAGE_INTERPOLATION_BILINEAR 0x1
#define RIF_IMAGE_INTERPOLATION_BICUBIC 0x2
#define RIF_IMAGE_INTERPOLATION_LANCZOS 0x3
#define RIF_IMAGE_INTERPOLATION_LANCZOS4 0x4
#define RIF_IMAGE_INTERPOLATION_LANCZOS6 0x5
#define RIF_IMAGE_INTERPOLATION_LANCZOS12 0x6
#define RIF_IMAGE_INTERPOLATION_LANCZOS3 0x7
#define RIF_IMAGE_INTERPOLATION_KAISER 0x8
#define RIF_IMAGE_INTERPOLATION_BLACKMAN 0x9
#define RIF_IMAGE_INTERPOLATION_GAUSS 0xA
#define RIF_IMAGE_INTERPOLATION_BOX 0xB
#define RIF_IMAGE_INTERPOLATION_TENT 0xC
#define RIF_IMAGE_INTERPOLATION_BELL 0xD
#define RIF_IMAGE_INTERPOLATION_BSPLINE 0xE
#define RIF_IMAGE_INTERPOLATION_QUADRATIC_INTERP 0xF
#define RIF_IMAGE_INTERPOLATION_QUADRATIC_APPROX 0x10
#define RIF_IMAGE_INTERPOLATION_QUADRATIC_MIX 0x11
#define RIF_IMAGE_INTERPOLATION_MITCHELL 0x12
#define RIF_IMAGE_INTERPOLATION_CATMULL 0x13

/* rif_image_filter_info */
#define RIF_IMAGE_FILTER_TYPE 0x0
#define RIF_IMAGE_FILTER_PARAMETER_COUNT 0x1
#define RIF_IMAGE_FILTER_DESCRIPTION 0x2

/* rif_parameter_info */
#define RIF_PARAMETER_NAME_STRING 0x1202
#define RIF_PARAMETER_TYPE 0x1203
#define RIF_PARAMETER_DESCRIPTION 0x1204
#define RIF_PARAMETER_VALUE 0x1205

/*rif_color_space*/
#define RIF_COLOR_SPACE_SRGB 0x1
#define RIF_COLOR_SPACE_ADOBE_RGB 0x2
#define RIF_COLOR_SPACE_REC2020 0x3
#define RIF_COLOR_SPACE_DCIP3 0x4

/* rif_bool */
#define RIF_FALSE 0
#define RIF_TRUE 1

/* rif_context_info */
#define RIF_CONTEXT_KERNELS_SOURCE_DIR 0x1
#define RIF_CONTEXT_KERNELS_CACHE_DIR 0x2

#define RIF_AI_UPSCALE_MODE_GOOD_2X 0x1
#define RIF_AI_UPSCALE_MODE_BEST_2X 0x2
#define RIF_AI_UPSCALE_MODE_FAST_2X 0x3

/* Library types */
/* This is going to be moved to rif_platform.h or similar */
typedef char rif_char;
typedef unsigned char rif_uchar;
typedef int rif_int;
typedef unsigned int rif_uint;
typedef long int rif_long;
typedef long unsigned int rif_ulong;
typedef short int rif_short;
typedef short unsigned int rif_ushort;
typedef float rif_float;
typedef double rif_double;
typedef long long int rif_longlong;
typedef int64_t rif_int64;
typedef uint64_t rif_uint64;
typedef int rif_bool;
typedef rif_uint rif_bitfield;
typedef struct rif_context_t { void*_; } *rif_context;
typedef struct rif_command_queue_t { void*_; } *rif_command_queue;
typedef struct rif_image_t { void*_; } *rif_image;
typedef struct rif_image_filter_t { void*_; } *rif_image_filter;
typedef rif_uint rif_image_type;
typedef rif_uint rif_backend_api_type;
typedef rif_bitfield rif_creation_flags;
typedef rif_uint rif_context_info;
typedef rif_uint rif_image_info;
typedef rif_uint rif_parameter_info;
typedef rif_uint rif_parameter_type;
typedef rif_uint rif_component_type;
typedef rif_uint rif_image_filter_type;
typedef rif_uint rif_image_filter_info;
typedef rif_uint rif_image_map_type;
typedef rif_uint rif_color_space;
typedef rif_uint rif_interpolation_operator;
typedef rif_uint rif_environment_override;
typedef rif_uint rif_compute_type;

typedef void* rif_exec_command_queue_callback(void*);

struct _rif_image_desc
{
    rif_uint image_width;
    rif_uint image_height;
    rif_uint image_depth;
    rif_uint image_row_pitch;   // row size in bytes
    rif_uint image_slice_pitch; // slice size in bytes

    /*!     num_components   components
    *       1                   grey
    *       2                   grey, alpha
    *       3                   red, green, blue
    *       4                   red, green, blue, alpha
    */
    rif_uint num_components;
    rif_component_type type;
};

typedef struct _rif_image_desc rif_image_desc;

struct _rif_render_statistics
{
    rif_longlong gpumem_usage;
    rif_longlong gpumem_total;
    rif_longlong gpumem_max_allocation;
};

typedef struct _rif_render_statistics rif_render_statistics;

// context

/*!
* \brief rifGetDeviceCount
* Gets the devices count for the selected backend API.
*
* \param[in] backend_api_type — defines the backend API (OpenCL, CPU).
* \param[out] deviceCount — the count of devices available for the selected backend API.
* \return RIF_SUCCESS — if the rif_image_filter object is created successfully.
* \return RIF_ERROR_INVALID_PARAMETER — if \p deviceCount is nullptr.
*/
extern RIF_API_ENTRY rif_int rifGetDeviceCount(rif_backend_api_type backend_api_type, rif_int* deviceCount);

/*!
* \brief rifCreateContext
* Creates the new rif_context object associated with device \p device_id.
*
* \param api_version — the current RadeonImageFilters version.
* \param backend_api_type — defines the backend API.
* \param device_id — the ID of the selected device.
* \param cache_path — the path to directory which will contain prebuilded binaries.
* \param out_context — the pointer to rif_context object which will be created if the function performs successfully.
* \return RIF_SUCCESS — if the rif_image_filter object is created successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_API_VERSION — if API version is unsupported.
* \return RIF_ERROR_INVALID_PARAMETER — if \p out_context is nullptr.
* \return RIF_ERROR_INVALID_CONTEXT — if context creation failed.
* \return RIF_ERROR_INTERNAL_ERROR — if an internal error in RadeonImageFiflters occurs. In such case, please send a bug report to this email address AMDRadeonProDeveloper@amd.com
*/
extern RIF_API_ENTRY rif_int rifCreateContext(rif_uint64 api_version, rif_backend_api_type backend_api_type,
rif_int device_id, rif_char const * cache_path, rif_context * out_context);

/*!
* \brief rifGetDeviceInfo
* Gets the description of the device.
*
* \param[in] context — a valid rif_context object.
* \param[out] name — the rif_char string which receives device name — it needs to be a 128 char array.
* \param[out] vendor — the rif_char string which receives vendor name — it needs to be a 128 char array.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_PARAMETER — if \p name or \p vendor is nullptr.
* \return RIF_ERROR_INVALID_CONTEXT — if getting of the device info failed.
*/
extern RIF_API_ENTRY rif_int rifContextGetDeviceInfo(rif_context context, rif_char name[128], rif_char vendor[128]);

// images

/*!
* \brief rifContextCreateImage
* Creates the new rif_image object with defined by \p image_desc format associated with rif_context.
*
* \param[in] context — a valid rif_context object.
* \param[in] image_desc — the description of image size and image pixels format.
* \param[out] out_image — the pointer to rif_image object which will be created if the function performs successfully.
* \param[in] data the pointer to host data storage.
* \return RIF_SUCCESS — if the rif_image object is created successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if \p out_image is nullptr.
* \return RIF_ERROR_UNSUPPORTED_IMAGE_FORMAT — if image format defined by \p image_desc is currently unsupported.
*/
extern RIF_API_ENTRY rif_int rifContextCreateImage(rif_context context, rif_image_desc const * image_desc, void const * data, rif_image * out_image);

/*!
* \brief rifImageGetInfo
* Gets the image info.
*
* \param[in] image — a valid rif_image object.
* \param[in] image_info — image info type.
* \param[in] size — maximum size of image info which can be stored in \p data.
* \param[out] data — the pointer to memory in which image info will be stored.
* \param[out] size_ret — the size of the data stored in \p data.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_IMAGE — if \p image is not a valid rif_image.
* \return RIF_ERROR_INVALID_PARAMETER — if \p size_ret or data is nullptr or if size is less than requested image info.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if requested image_info type is not supported.
*/
extern RIF_API_ENTRY rif_int rifImageGetInfo(rif_image image, rif_image_info image_info, size_t size, void * data, size_t * size_ret);

/*!
* \brief rifImageMap
*  Maps the rif_image pixels data into the host address space and returns a pointer to this mapped region.
*
* \param[in] image — a valid rif_image object.
* \param[in] map_type — not used at the moment.
* \param[out] data — a pointer to the mapped data if the function is executed successfully.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_IMAGE — if \p image is not a valid rif_image.
* \return RIF_ERROR_INVALID_PARAMETER — if \p data is nullptr.
* \RIF_ERRO—_INTERNAL_ERROR — if an internal RadeonImageFiflters error occurs. If such an error occurs, Please send a bug report to this email address: AMDRadeonProDeveloper@amd.com.
*/
extern RIF_API_ENTRY rif_int rifImageMap(rif_image image, rif_image_map_type map_type, void** data);

/*!
* \brief rifImageUnmap
*  Unmaps previously mapped rif_image data.
*
* \param[in] image — a valid rif_image object.
* \param[out] ptr — a pointer to the previously mapped data.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_IMAGE — if \p image is not a valid rif_image.
* \return RIF_ERROR_INVALID_PARAMETER — if \p ptr is nullptr.
* \RIF_ERROR_INTERNAL_ERROR — if an internal RadeonImageFiflters error occurs. Sends a bug report if such an error occurs.
*/
extern RIF_API_ENTRY rif_int rifImageUnmap(rif_image image, void* ptr);

// command queue

/*!
* \brief rifContextCreateCommandQueue
* Creates the new command_queue object associated with context \p context.
*
* \param[in] context — a valid rif_context object.
* \param[out] command_queue — the pointer to rif_command_queue object which will be created if function performs successfully.
* \return RIF_SUCCESS — if the command_queue object is created successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if \p command_queue is nullptr.
*/
extern RIF_API_ENTRY rif_int rifContextCreateCommandQueue(rif_context context, rif_command_queue* command_queue);

/*!
* \brief rifContextCreateCommandQueue
* Creates the new command_queue object associated with context \p context.
*
* \param[in] context — a valid rif_context object.
* \param[in] command_queue — the pointer to rif_command_queue object which will be created if the function performs successfully.
* \param[in] executionFinishedCallbackFunction — the user callback function which will be called when command queue will be executed.
* executionFinishedCallbackFunction can be a nullptr.
* \param[in] data — the user data which will be passed to executionFinishedCallbackFunction.
* \param[out] time — if not nullptr, will activate profiling and will store execution time. Must be initialized to 0 by user.
* \return RIF_SUCCESS — if the command queue is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context object.
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
* \return RIF_ERROR_INTERNAL_ERROR — if an internal RadeonImageFiflters error occurs. Sends a bug report if such an error occurs.
*/
extern RIF_API_ENTRY rif_int rifContextExecuteCommandQueue(rif_context context, rif_command_queue command_queue,
   rif_exec_command_queue_callback executionFinishedCallbackFunction, void *data, float* time);

// image filters

/*!
* \brief rifContextCreateImageFilter
* Creates the new image filter of type \p type associated with context \p context.
*
* \param[in] context — a valid rif_context object.
* \param[in] type — the filter type that defines the conversion to be performed. For example, RIF_IMAGE_FILTER_TONE_MAP.
* or RIF_IMAGE_FILTER_GAMMA_CORRECTION. Each type of filter corresponds to a set of parameters with a certain string names and certain data types.
* \param[out] out_effect — the pointer to rif_image_filter object which will be created if function performs successfully.
* \return RIF_SUCCESS — if the rif_image_filter object is created successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if \p out_effect is nullptr
* \return RIF_ERROR_UNIMPLEMENTED — if filter with type \p type is not implemented at the moment.
* \return RIF_ERROR_UNSUPPORTED — if filter with type \p type is not supported.
*/
extern RIF_API_ENTRY rif_int rifContextCreateImageFilter(rif_context context, rif_image_filter_type type, rif_image_filter * out_effect);

/*!
* \brief rifCommandQueueAttachImageFilter
* Attaches the filter \p image_filter to command queue \p command_queue and set the input and output rif_image object of the filter.
*
* \param[in] command_queue — a valid rif_command_queue object.
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] input_image — a valid rif_image object.
* \param[in] output_image — a valid rif_image object.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter object.
* \return RIF_ERROR_INVALID_IMAGE — if \p input_image or \p output_image is not a valid rif_image object.
* \return RIF_ERROR_INTERNAL_ERROR — if an internal RadeonImageFiflters error occurs. Sends a bug report if such an error occurs.
*/
extern RIF_API_ENTRY rif_int rifCommandQueueAttachImageFilter(rif_command_queue command_queue, rif_image_filter image_filter,
 rif_image input_image, rif_image output_image);

/*!
* \brief rifCommandQueueAttachImageFilterRect
* Attaches the filter \p image_filter to command queue \p command_queue and set the rectangle to be processed, input and output rif_image object of the filter.
*
* \param[in] command_queue — a valid rif_command_queue object.
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] input_image — a valid rif_image object.
* \param[in] output_image — a valid rif_image object.
* \param[in] x — X coordinate of the left most pixel of the rectangle to be processed. Must be a multiple of 8.
* \param[in] y — Y coordinate of the top most pixel of the rectangle to be processed. Must be a multiple of 8.
* \param[in] w — width of the rectangle to be processed. Must be a multiple of 8.
* \param[in] h — height of the rectangle to be processed. Must be a multiple of 8.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter object.
* \return RIF_ERROR_INVALID_IMAGE — if \p input_image or \p output_image is not a valid rif_image object.
* \return RIF_ERROR_INTERNAL_ERROR — if an internal RadeonImageFiflters error occurs. Sends a bug report if such an error occurs.
* \return RIF_ERROR_INVALID_PARAMETER — if either x, y, w, or h is not a multiple of 8.
*/
extern RIF_API_ENTRY rif_int rifCommandQueueAttachImageFilterRect(rif_command_queue command_queue, rif_image_filter image_filter,
   rif_image input_image, rif_image output_image, rif_uint x, rif_uint y, rif_uint w, rif_uint h);

/*!
* \brief rifCommandQueueDetachImageFilter
* Detaches the filter \p image_filter from command queue \p command_queue.
*
* \param[in] command_queue — a valid rif_command_queue object.
* \param[in] image_filter — a valid rif_image_filter object.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter object.
* \return RIF_ERROR_INVALID_PARAMETER — if \p image_filter is not attached to \p command_queue.
*/
extern RIF_API_ENTRY rif_int rifCommandQueueDetachImageFilter(rif_command_queue command_queue, rif_image_filter image_filter);

/*!
* \brief rifImageFilterSetParameter1u
* Used to set the unsigned integer parameter value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new unsigned integer parameter value.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type unsigned int.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter1u(rif_image_filter image_filter, rif_char const * name, rif_uint x);

/*!
* \brief rifImageFilterSetParameter2u
* Used to set the two-component unsigned integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new unsigned integer x value of the vector parameter \p name.
* \param[in] y — new unsigned integer y value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type two-component unsigned int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter2u(rif_image_filter image_filter, rif_char const * name, rif_uint x, rif_uint y);

/*!
* \brief rifImageFilterSetParameter3u
* Used to set the tree-component unsigned integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new unsigned integer x value of the vector parameter \p name.
* \param[in] y — new unsigned integer y value of the vector parameter \p name.
* \param[in] z — new unsigned integer z value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type tree-component unsigned int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter3u(rif_image_filter image_filter, rif_char const * name, rif_uint x, rif_uint y, rif_uint z);

/*!
* \brief rifImageFilterSetParameter4u
* Used to set the four-component unsigned integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new unsigned integer x value of the vector parameter \p name.
* \param[in] y — new unsigned integer y value of the vector parameter \p name.
* \param[in] z — new unsigned integer z value of the vector parameter \p name.
* \param[in] w — new unsigned integer w value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type four-component unsigned int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter4u(rif_image_filter image_filter, rif_char const * name, rif_uint x, rif_uint y, rif_uint z, rif_uint w);

/*!
* \brief rifImageFilterSetParameter8u
* Used to set the unsigned int 16-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 8 unsigned int values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is of type 8-component unsigned int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter8u(rif_image_filter image_filter, rif_char const * name, rif_uint * val);

/*!
* \brief rifImageFilterSetParameter16u
* Used to set the unsigned int 16-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 16 unsigned int values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is of type 16-component unsigned int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter16u(rif_image_filter image_filter, rif_char const * name, rif_uint * val);

/*!
* \brief rifImageFilterSetParameter1i
* Used to set the integer parameter value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new integer parameter value.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type int.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter1i(rif_image_filter image_filter, rif_char const * name, rif_int x);

/*!
* \brief rifImageFilterSetParameter2i
* Used to set the two-component integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new integer x value of the vector parameter \p name.
* \param[in] y — new integer y value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type unsigned int.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter2i(rif_image_filter image_filter, rif_char const * name, rif_int x, rif_int y);

/*!
* \brief rifImageFilterSetParameter3i
* Used to set the tree-component integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new integer x value of the vector parameter \p name.
* \param[in] y — new integer y value of the vector parameter \p name.
* \param[in] z — new integer z value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type tree-component int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter3i(rif_image_filter image_filter, rif_char const * name, rif_int x, rif_int y, rif_int z);

/*!
* \brief rifImageFilterSetParameter4i
* Used to set the four-component unsigned integer vector parameter for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new integer x value of the vector parameter \p name.
* \param[in] y — new integer y value of the vector parameter \p name.
* \param[in] z — new integer z value of the vector parameter \p name.
* \param[in] w — new integer w value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type four-component int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter4i(rif_image_filter image_filter, rif_char const * name, rif_int x, rif_int y, rif_int z, rif_int w);

/*!
* \brief rifImageFilterSetParameter8i
* Used to set the int 16-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 8 int values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is of type 8-component int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter8i(rif_image_filter image_filter, rif_char const * name, rif_int * val);

/*!
* \brief rifImageFilterSetParameter16i
* Used to set the int 16-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 16 int values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is of type 16-component int vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter16i(rif_image_filter image_filter, rif_char const * name, rif_int * val);

/*!
* \brief rifImageFilterSetParameter1f
* Used to set the float parameter value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new float parameter value.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type float.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter1f(rif_image_filter image_filter, rif_char const * name, rif_float x);

/*!
* \brief rifImageFilterSetParameter2f
* Used to set the float two-component value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new float parameter value.
* \param[in] y — new float parameter value.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type two-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter2f(rif_image_filter image_filter, rif_char const * name, rif_float x, rif_float y);

/*!
* \brief rifImageFilterSetParameter3f
* Used to set the float three-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new float x value of the vector parameter \p name.
* \param[in] y — new float y value of the vector parameter \p name.
* \param[in] z — new float z value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type three-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter3f(rif_image_filter image_filter, rif_char const * name, rif_float x, rif_float y, rif_float z);

/*!
* \brief rifImageFilterSetParameter4f
* Used to set the float four-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] x — new float x value of the vector parameter \p name.
* \param[in] y — new float y value of the vector parameter \p name.
* \param[in] z — new float z value of the vector parameter \p name.
* \param[in] w — new float w value of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type four-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter4f(rif_image_filter image_filter, rif_char const * name, rif_float x, rif_float y, rif_float z, rif_float w);

/*!
* \brief rifImageFilterSetParameter8f
* Used to set the float 8-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 8 floats values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type 8-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter8f(rif_image_filter image_filter, rif_char const * name, rif_float * val);

/*!
* \brief rifImageFilterSetParameter16f
* Used to set the float 16-component vector parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — array with 16 floats values of the vector parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type 16-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameter16f(rif_image_filter image_filter, rif_char const * name, rif_float * val);

/*!
* \brief rifImageFilterSetParameterString
* Used to set string parameter value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] val — string value \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type four-component float vector.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameterString(rif_image_filter image_filter, rif_char const * name, rif_char const * val);

/*!
* \brief rifImageFilterSetParameterImage
* Used to set the image parameter value for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] img — the new image value of the image parameter \p name.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type image.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameterImage(rif_image_filter image_filter, rif_char const * name, rif_image img);

/*!
* \brief rifImageFilterClearParameterImage
* Used to clear the image parameter with name \p name. Can't be used to clear input\output images.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be set to null.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterClearParameterImage(rif_image_filter image_filter, rif_char const * name);

/*!
* \brief rifImageFilterSetParameterFloatArray
* Used to set the float array parameters values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] arr — the array of float values.
* \param[in] num — the size of array.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type float array.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameterFloatArray(rif_image_filter image_filter, rif_char const * name, rif_float* arr,
  rif_uint num);

/*!
* \brief rifImageFilterSetParameterImageArray
* Used to set the array of images parameter values for a specified by \p name parameter of the filter.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] name — the name of the filter parameter which value will be changed.
* \param[in] arr — the array of images.
* \param[in] num — the size of array.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_FILTER_ARGUMENT_NAME — if parameter with name \p name is not associated with this type of filter.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter parameter \p name is not of type image array.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetParameterImageArray(rif_image_filter image_filter, rif_char const * name, rif_image* arr,
  rif_uint num);

/*!
* \brief rifImageFilterSetComputeType
* Used to set filter calculations precision
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] compute_type — computation type, float16 or float32.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \see rifContextCreateImageFilter
*/
extern RIF_API_ENTRY rif_int rifImageFilterSetComputeType(rif_image_filter image_filter, rif_compute_type compute_type);

/*!
* \brief rifImageFilterGetInfo
* Gets the filter info.
*
* \param[in] image_filter — a valid rif_image_filter object.
* \param[in] filter_info — filter info type.
* \param[in] size — maximum size of filter info which can be stored in \p data.
* \param[out] data — the pointer to memory in which filter info will be stored.
* \param[out] size_ret — the size of the data stored in \p data.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_PARAMETER — if \p size_ret is nullptr or if size_net is less than the requested image info.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if filter_info type is not supported.
*/
extern RIF_API_ENTRY rif_int rifImageFilterGetInfo(rif_image_filter image_filter, rif_image_filter_info filter_info, size_t size, void * data, size_t * size_ret);

/*!
* \brief rifParameterGetInfo
* Gets the image filter parameter info.
*
* \param[in] image_filter — a valid image_filter object.
* \param[in] paramIdx — image filter parameter index.
* \param[in] param_info — parameter info type.
* \param[in] size — maximum size of parameter info which can be stored in \p data.
* \param[out] data — the pointer to memory in which parameter info will be stored.
* \param[out] size_ret — the size of the data stored in \p data.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_FILTER — if \p image_filter is not a valid rif_image_filter.
* \return RIF_ERROR_INVALID_PARAMETER — if \p size_ret is nullptr or if size_net is less than the requested image info.
* \return RIF_ERROR_INVALID_PARAMETER_TYPE — if param_info type is not supported.
*/
extern RIF_API_ENTRY rif_int rifParameterGetInfo(rif_image_filter image_filter, rif_uint paramIdx,
 rif_parameter_info param_info, size_t size, void * data, size_t * size_ret);

// general object functions

/*!
* \brief rifObjectDelete
* Deletes previously created rif_object.
*
* \param[in] obj a valid previously created rif_object.
* \return RIF_ERROR_INVALID_PARAMETER — if \p obj is not a valid previously created rif_object.
*/
extern RIF_API_ENTRY rif_int rifObjectDelete(void * obj);

// Kernels directory API

// Directory with OpenCL/Metal kernels might be changed and requested with functions declared below.
// It might also be changed with environment variable RIF_KERNELS_DIR.
// Kernels directory value proirity (low -> high): default -> external -> environment.
// Use rifSetKernelsDir(context, path_to_kernels) to set external value.
// Use rifSetKernelsDir(context, NULL) to unset external value, and fallback to default value.

/*!
* \brief rifGetKernelsDir
* RIF_DEPRECATED function. Uses rifContextGetInfo with context_info = RIF_CONTEXT_KERNELS_SOURCE_DIR
*
* Gets kernels directory.
*
* \param[in] context — a valid rif_context object.
* \param[out] kernels_dir — memory pointer to write kernels directory to.
* \param[out] size_ret — the size of the data stored in \p kernels_dir (includes \0 at the end).
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if \p kernels_dir and \p size_ret are both NULL.
*/
RIF_DEPRECATED extern RIF_API_ENTRY rif_int rifGetKernelsDir(rif_context context, rif_char * kernels_dir, size_t * size_ret);

/*!
* \brief rifSetKernelsDir
* RIF_DEPRECATED function. Use rifContextSetInfo with context_info = RIF_CONTEXT_KERNELS_SOURCE_DIR
*
* Sets kernels directory.
*
* \param[in] context — a valid rif_context object.
* \param[in] kernels_dir — memory pointer with kernels directory path, or NULL to use default path.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_IO_ERROR — if \p kernels_dir is not accesible.
*/
RIF_DEPRECATED extern RIF_API_ENTRY rif_int rifSetKernelsDir(rif_context context, rif_char const * kernels_dir);

/*!
* \brief rifContextGetInfo
*
* Gets context information.
*
* \param[in] context — a valid rif_context object.
* \param[in] context_info — context info to be requested.
* \param[in] size — size of memory allocated for requested context info (incl. terminating zero for strings).
* \param[out] data — memory pointer to write requested info to.
* \param[out] size_ret — the size of the data stored in \p data
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if \p data and \p size_ret are both NULL, or value of \p context_info is invalid, or \p size bytes in not enough to store requested info.
*/
extern RIF_API_ENTRY rif_int rifContextGetInfo(rif_context context, rif_context_info context_info, size_t size, void * data, size_t * size_ret);

/*!
* \brief rifContextSetInfo
*
* Sets context information.
*
* \param[in] context — a valid rif_context object.
* \param[in] context_info — context info to be written.
* \param[out] data — memory pointer to write requested info to.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_CONTEXT — if \p context is not a valid rif_context.
* \return RIF_ERROR_INVALID_PARAMETER — if is value of \p context_info is invalid.
*/
extern RIF_API_ENTRY rif_int rifContextSetInfo(rif_context context, rif_context_info context_info, const void * data);

/*!
* \brief rifFlushQueue
* Flushes the queue
*
* \param[in] command_queue — a valid rif_command_queue object.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
*/
extern RIF_API_ENTRY rif_int rifFlushQueue(rif_command_queue command_queue);

/*!
* \brief rifSyncronizeQueue
* Syncronizes the queue.
*
* \param[in] command_queue — a valid rif_command_queue object.
* \return RIF_SUCCESS — if the function is executed successfully. Otherwise, it returns one of the following errors:
* \return RIF_ERROR_INVALID_QUEUE — if \p command_queue is not a valid rif_command_queue object.
*/
extern RIF_API_ENTRY rif_int rifSyncronizeQueue(rif_command_queue command_queue);

extern RIF_API_ENTRY const char* rifGetErrorCodeDescription(rif_int error);

extern RIF_API_ENTRY const char* rifGetErrorCodeString(rif_int error);

#ifdef __cplusplus
}
#endif

#endif  /*__RADEONIMAGEFILTERS_H  */
