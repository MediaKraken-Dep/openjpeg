 /*
 * Copyright (c) 2002-2007, Communications and Remote Sensing Laboratory, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2007, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux and Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * Copyright (c) 2006-2007, Parvatha Elangovan
 * Copyright (c) 2008, Jerome Fimes, Communications & Systemes <jerome.fimes@c-s.fr>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef OPENJPEG_H
#define OPENJPEG_H

#if defined(OPJ_STATIC) || !defined(_WIN32)
	#define OPJ_API
	#define OPJ_CALLCONV
#else
	#define OPJ_CALLCONV __stdcall
	#if defined(OPJ_EXPORTS) || defined(DLL_EXPORT)
		#define OPJ_API __declspec(dllexport)
	#else
		#define OPJ_API __declspec(dllimport)
	#endif /* OPJ_EXPORTS || DLL_EXPORT */
#endif /* !OPJ_STATIC || !_WIN32 */

#ifndef __cplusplus
	#if defined(HAVE_STDBOOL_H)
		#include <stdbool.h>
	#else
		#if !defined(bool)
			#define	bool	int
		#endif
		#if !defined(true)
			#define true	1
		#endif
		#if !defined(false)
			#define	false	0
		#endif
	#endif
#endif /* __cplusplus */
typedef unsigned int	OPJ_UINT32;
typedef int		OPJ_INT32;	
typedef unsigned short	OPJ_UINT16;	
typedef short		OPJ_INT16;	
typedef char		OPJ_CHAR;
typedef unsigned char	OPJ_BYTE;
typedef unsigned int	OPJ_SIZE_T;
typedef double		OPJ_FLOAT64;
typedef float		OPJ_FLOAT32;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	typedef __int64		OPJ_INT64;
#else
	typedef long long	OPJ_INT64;
#endif

#define OPENJPEG_VERSION "2.0.0"
/* 
==========================================================
   Compiler directives
==========================================================
*/
#include <stdio.h>





/* 
==========================================================
   Useful constant definitions
==========================================================
*/

#define OPJ_PATH_LEN					4096 /**< Maximum allowed size for filenames */
#define J2K_MAXRLVLS					33					/**< Number of maximum resolution level authorized */
#define J2K_MAXBANDS					(3*J2K_MAXRLVLS-2)	/**< Number of maximum sub-band linked to number of resolution level */
#define J2K_DEFAULT_NB_SEGS				10
#define J2K_STREAM_CHUNK_SIZE			0x100000 /** 1 mega by default */
#define J2K_DEFAULT_HEADER_SIZE			1000
#define J2K_MCC_DEFAULT_NB_RECORDS		10
#define J2K_MCT_DEFAULT_NB_RECORDS		10

/* UniPG>> */
#define JPWL_MAX_NO_TILESPECS	16 /**< Maximum number of tile parts expected by JPWL: increase at your will */
#define JPWL_MAX_NO_PACKSPECS	16 /**< Maximum number of packet parts expected by JPWL: increase at your will */
#define JPWL_MAX_NO_MARKERS	512 /**< Maximum number of JPWL markers: increase at your will */
#define JPWL_PRIVATEINDEX_NAME "jpwl_index_privatefilename" /**< index file name used when JPWL is on */
#define JPWL_EXPECTED_COMPONENTS 3 /**< Expect this number of components, so you'll find better the first EPB */
#define JPWL_MAXIMUM_TILES 8192 /**< Expect this maximum number of tiles, to avoid some crashes */
#define JPWL_MAXIMUM_HAMMING 2 /**< Expect this maximum number of bit errors in marker id's */
#define JPWL_MAXIMUM_EPB_ROOM 65450 /**< Expect this maximum number of bytes for composition of EPBs */
/* <<UniPG */

/* 
==========================================================
   enum definitions
==========================================================
*/
/** 
Rsiz Capabilities
*/
typedef enum RSIZ_CAPABILITIES {
	STD_RSIZ = 0,		/** Standard JPEG2000 profile*/
	CINEMA2K = 3,		/** Profile name for a 2K image*/
	CINEMA4K = 4,		/** Profile name for a 4K image*/
	MCT = 0x8100
} OPJ_RSIZ_CAPABILITIES;

/** 
Digital cinema operation mode 
*/
typedef enum CINEMA_MODE {
	OFF = 0,					/** Not Digital Cinema*/
	CINEMA2K_24 = 1,	/** 2K Digital Cinema at 24 fps*/
	CINEMA2K_48 = 2,	/** 2K Digital Cinema at 48 fps*/
	CINEMA4K_24 = 3		/** 4K Digital Cinema at 24 fps*/
}OPJ_CINEMA_MODE;

/** 
Progression order 
*/
typedef enum PROG_ORDER {
	PROG_UNKNOWN = -1,	/**< place-holder */
	LRCP = 0,		/**< layer-resolution-component-precinct order */
	RLCP = 1,		/**< resolution-layer-component-precinct order */
	RPCL = 2,		/**< resolution-precinct-component-layer order */
	PCRL = 3,		/**< precinct-component-resolution-layer order */
	CPRL = 4		/**< component-precinct-resolution-layer order */
} OPJ_PROG_ORDER;

/**
Supported image color spaces
*/
typedef enum COLOR_SPACE {	
	CLRSPC_UNKNOWN = -1,	/**< not supported by the library */
	CLRSPC_UNSPECIFIED = 0, /**< not specified in the codestream */ 
	CLRSPC_SRGB = 1,		/**< sRGB */
	CLRSPC_GRAY = 2,		/**< grayscale */
	CLRSPC_SYCC = 3			/**< YUV */
} OPJ_COLOR_SPACE;

/**
Supported codec
*/
typedef enum CODEC_FORMAT {
	CODEC_UNKNOWN = -1,	/**< place-holder */
	CODEC_J2K = 0,		/**< JPEG-2000 codestream : read/write */
	CODEC_JPT = 1,		/**< JPT-stream (JPEG 2000, JPIP) : read only */
	CODEC_JP2 = 2		/**< JPEG-2000 file format : read/write */
} OPJ_CODEC_FORMAT;




/* 
==========================================================
   event manager typedef definitions
==========================================================
*/

/**
Callback function prototype for events
@param msg Event message
@param client_data 
*/
typedef void (*opj_msg_callback) (const OPJ_CHAR *msg, void *client_data);




/* 
==========================================================
   codec typedef definitions
==========================================================
*/

/**
Progression order changes
*/
typedef struct opj_poc 
{
	/** Resolution num start, Component num start, given by POC */
	OPJ_UINT32 resno0, compno0;
	/** Layer num end,Resolution num end, Component num end, given by POC */
	OPJ_UINT32 layno1, resno1, compno1;
	/** Layer num start,Precinct num start, Precinct num end */
	OPJ_UINT32 layno0, precno0, precno1;
	/** Progression order enum*/
	OPJ_PROG_ORDER prg1,prg;
	/** Progression order string*/
	OPJ_CHAR progorder[5];
	/** Tile number */
	OPJ_UINT32 tile;
	/** Start and end values for Tile width and height*/
	OPJ_INT32 tx0,tx1,ty0,ty1;
	/** Start value, initialised in pi_initialise_encode*/
	OPJ_UINT32 layS, resS, compS, prcS;
	/** End value, initialised in pi_initialise_encode */
	OPJ_UINT32 layE, resE, compE, prcE;
	/** Start and end values of Tile width and height, initialised in pi_initialise_encode*/
	OPJ_UINT32 txS,txE,tyS,tyE,dx,dy;
	/** Temporary values for Tile parts, initialised in pi_create_encode */
	OPJ_UINT32 lay_t, res_t, comp_t, prc_t,tx0_t,ty0_t;
} opj_poc_t;

/**
Compression parameters
*/
typedef struct opj_cparameters {
	/** size of tile: tile_size_on = false (not in argument) or = true (in argument) */
	bool tile_size_on;
	/** XTOsiz */
	int cp_tx0;
	/** YTOsiz */
	int cp_ty0;
	/** XTsiz */
	int cp_tdx;
	/** YTsiz */
	int cp_tdy;
	/** allocation by rate/distortion */
	int cp_disto_alloc;
	/** allocation by fixed layer */
	int cp_fixed_alloc;
	/** add fixed_quality */
	int cp_fixed_quality;
	/** fixed layer */
	int *cp_matrice;
	/** comment for coding */
	char *cp_comment;
	/** csty : coding style */
	int csty;
	/** progression order (default LRCP) */
	OPJ_PROG_ORDER prog_order;
	/** progression order changes */
	opj_poc_t POC[32];
	/** number of progression order changes (POC), default to 0 */
	int numpocs;
	/** number of layers */
	int tcp_numlayers;
	/** rates of layers */
	float tcp_rates[100];
	/** different psnr for successive layers */
	float tcp_distoratio[100];
	/** number of resolutions */
	int numresolution;
	/** initial code block width, default to 64 */
 	int cblockw_init;
	/** initial code block height, default to 64 */
	int cblockh_init;
	/** mode switch (cblk_style) */
	int mode;
	/** 1 : use the irreversible DWT 9-7, 0 : use lossless compression (default) */
	int irreversible;
	/** region of interest: affected component in [0..3], -1 means no ROI */
	int roi_compno;
	/** region of interest: upshift value */
	int roi_shift;
	/* number of precinct size specifications */
	int res_spec;
	/** initial precinct width */
	int prcw_init[J2K_MAXRLVLS];
	/** initial precinct height */
	int prch_init[J2K_MAXRLVLS];

	/**@name command line encoder parameters (not used inside the library) */
	/*@{*/
	/** input file name */
	char infile[OPJ_PATH_LEN];
	/** output file name */
	char outfile[OPJ_PATH_LEN];
	/** DEPRECATED. Index generation is now handeld with the opj_encode_with_info() function. Set to NULL */
	int index_on;
	/** DEPRECATED. Index generation is now handeld with the opj_encode_with_info() function. Set to NULL */
	char index[OPJ_PATH_LEN];
	/** subimage encoding: origin image offset in x direction */
	int image_offset_x0;
	/** subimage encoding: origin image offset in y direction */
	int image_offset_y0;
	/** subsampling value for dx */
	int subsampling_dx;
	/** subsampling value for dy */
	int subsampling_dy;
	/** input file format 0: PGX, 1: PxM, 2: BMP 3:TIF*/
	int decod_format;
	/** output file format 0: J2K, 1: JP2, 2: JPT */
	int cod_format;
	/*@}*/

/* UniPG>> */
	/**@name JPWL encoding parameters */
	/*@{*/
	/** enables writing of EPC in MH, thus activating JPWL */
	bool jpwl_epc_on;
	/** error protection method for MH (0,1,16,32,37-128) */
	int jpwl_hprot_MH;
	/** tile number of header protection specification (>=0) */
	int jpwl_hprot_TPH_tileno[JPWL_MAX_NO_TILESPECS];
	/** error protection methods for TPHs (0,1,16,32,37-128) */
	int jpwl_hprot_TPH[JPWL_MAX_NO_TILESPECS];
	/** tile number of packet protection specification (>=0) */
	int jpwl_pprot_tileno[JPWL_MAX_NO_PACKSPECS];
	/** packet number of packet protection specification (>=0) */
	int jpwl_pprot_packno[JPWL_MAX_NO_PACKSPECS];
	/** error protection methods for packets (0,1,16,32,37-128) */
	int jpwl_pprot[JPWL_MAX_NO_PACKSPECS];
	/** enables writing of ESD, (0=no/1/2 bytes) */
	int jpwl_sens_size;
	/** sensitivity addressing size (0=auto/2/4 bytes) */
	int jpwl_sens_addr;
	/** sensitivity range (0-3) */
	int jpwl_sens_range;
	/** sensitivity method for MH (-1=no,0-7) */
	int jpwl_sens_MH;
	/** tile number of sensitivity specification (>=0) */
	int jpwl_sens_TPH_tileno[JPWL_MAX_NO_TILESPECS];
	/** sensitivity methods for TPHs (-1=no,0-7) */
	int jpwl_sens_TPH[JPWL_MAX_NO_TILESPECS];
	/*@}*/
/* <<UniPG */

	/** Digital Cinema compliance 0-not compliant, 1-compliant*/
	OPJ_CINEMA_MODE cp_cinema;
	/** Maximum rate for each component. If == 0, component size limitation is not considered */
	int max_comp_size;
	/** Profile name*/
	OPJ_RSIZ_CAPABILITIES cp_rsiz;
	/** Tile part generation*/
	char tp_on;
	/** Flag for Tile part generation*/
	char tp_flag;
	/** MCT (multiple component transform) */
	char tcp_mct;
	/** Naive implementation of MCT restricted to a single reversible array based encoding without offset concerning all the components. */
	void * mct_data;

} opj_cparameters_t;

/**
Decompression parameters
*/
typedef struct opj_dparameters {
	/** 
	Set the number of highest resolution levels to be discarded. 
	The image resolution is effectively divided by 2 to the power of the number of discarded levels. 
	The reduce factor is limited by the smallest total number of decomposition levels among tiles.
	if != 0, then original dimension divided by 2^(reduce); 
	if == 0 or not used, image is decoded to the full resolution 
	*/
	int cp_reduce;
	/** 
	Set the maximum number of quality layers to decode. 
	If there are less quality layers than the specified number, all the quality layers are decoded.
	if != 0, then only the first "layer" layers are decoded; 
	if == 0 or not used, all the quality layers are decoded 
	*/
	int cp_layer;

	/**
	 * Restrictive decoding parameters.
	 */
	OPJ_INT32 m_decode_start_x;
	OPJ_INT32 m_decode_start_y ;
	OPJ_INT32 m_decode_end_x ;
	OPJ_INT32 m_decode_end_y ;

	/**@name command line encoder parameters (not used inside the library) */
	/*@{*/
	/** input file name */
	char infile[OPJ_PATH_LEN];
	/** output file name */
	char outfile[OPJ_PATH_LEN];
	/** input file format 0: J2K, 1: JP2, 2: JPT */
	int decod_format;
	/** output file format 0: PGX, 1: PxM, 2: BMP */
	int cod_format;
	/*@}*/

/* UniPG>> */
	/**@name JPWL decoding parameters */
	/*@{*/
	/** activates the JPWL correction capabilities */
	bool jpwl_correct;
	/** expected number of components */
	int jpwl_exp_comps;
	/** maximum number of tiles */
	int jpwl_max_tiles;
	
	/** use restrictive decoding ? */
	OPJ_UINT32 m_use_restrict_decode : 1;
	/*@}*/
/* <<UniPG */

} opj_dparameters_t;

/**
 * J2k codec.
 */
typedef void * opj_codec_t;


/* 
==========================================================
   I/O stream typedef definitions
==========================================================
*/

/*
 * Stream open flags.
 */
/** The stream was opened for reading. */
#define OPJ_STREAM_READ	0x0001
/** The stream was opened for writing. */
#define OPJ_STREAM_WRITE 0x0002


typedef OPJ_UINT32 (* opj_stream_read_fn) (void * p_buffer, OPJ_UINT32 p_nb_bytes, void * p_user_data) ;
typedef OPJ_UINT32 (* opj_stream_write_fn) (void * p_buffer, OPJ_UINT32 p_nb_bytes, void * p_user_data) ;
typedef OPJ_SIZE_T (* opj_stream_skip_fn) (OPJ_SIZE_T p_nb_bytes, void * p_user_data) ;
typedef bool (* opj_stream_seek_fn) (OPJ_SIZE_T p_nb_bytes, void * p_user_data) ;


typedef void * opj_stream_t;

/* 
==========================================================
   image typedef definitions
==========================================================
*/

/**
Defines a single image component
*/
typedef struct opj_image_comp {
	/** XRsiz: horizontal separation of a sample of ith component with respect to the reference grid */
	OPJ_UINT32 dx;
	/** YRsiz: vertical separation of a sample of ith component with respect to the reference grid */
	OPJ_UINT32 dy;
	/** data width */
	OPJ_UINT32 w;
	/** data height */
	OPJ_UINT32 h;
	/** x component offset compared to the whole image */
	OPJ_INT32 x0;
	/** y component offset compared to the whole image */
	OPJ_INT32 y0;
	/** precision */
	OPJ_UINT32 prec;
	/** number of decoded resolution */
	OPJ_UINT32 resno_decoded;
	/** number of division by 2 of the out image compared to the original size of image */
	OPJ_UINT32 factor;
	/** image component data */
	int *data;
	/** signed (1) / unsigned (0) */
	OPJ_UINT32 sgnd : 1;
	
} opj_image_comp_t;

/** 
Defines image data and characteristics
*/
typedef struct opj_image 
{
	/** XOsiz: horizontal offset from the origin of the reference grid to the left side of the image area */
	OPJ_INT32 x0;
	/** YOsiz: vertical offset from the origin of the reference grid to the top side of the image area */
	OPJ_INT32 y0;
	/** Xsiz: width of the reference grid */
	OPJ_INT32 x1;
	/** Ysiz: height of the reference grid */
	OPJ_INT32 y1;
	/** number of components in the image */
	OPJ_UINT32 numcomps;
	/** color space: sRGB, Greyscale or YUV */
	OPJ_COLOR_SPACE color_space;
	/** image components */
	opj_image_comp_t *comps;
} opj_image_t;

/**
Component parameters structure used by the opj_image_create function
*/
typedef struct opj_image_comptparm {
	/** XRsiz: horizontal separation of a sample of ith component with respect to the reference grid */
	unsigned int dx;
	/** YRsiz: vertical separation of a sample of ith component with respect to the reference grid */
	unsigned int dy;
	/** data width */
	unsigned int w;
	/** data height */
	unsigned int h;
	/** x component offset compared to the whole image */
	int x0;
	/** y component offset compared to the whole image */
	int y0;
	/** precision */
	int prec;
	/** image depth in bits */
	int bpp;
	/** signed (1) / unsigned (0) */
	int sgnd;
} opj_image_cmptparm_t;

/* 
==========================================================
   Information on the JPEG 2000 codestream
==========================================================
*/

/**
Index structure : Information concerning a packet inside tile
*/
typedef struct opj_packet_info {
	/** packet start position (including SOP marker if it exists) */
	int start_pos;
	/** end of packet header position (including EPH marker if it exists)*/
	int end_ph_pos;
	/** packet end position */
	int end_pos;
	/** packet distorsion */
	double disto;
} opj_packet_info_t;

/**
Index structure : Information concerning tile-parts
*/
typedef struct opj_tp_info {
	/** start position of tile part */
	int tp_start_pos;
	/** end position of tile part header */
	int tp_end_header;
	/** end position of tile part */
	int tp_end_pos;
	/** start packet of tile part */
	int tp_start_pack;
	/** number of packets of tile part */
	int tp_numpacks;
} opj_tp_info_t;

/**
Index structure : information regarding tiles 
*/
typedef struct opj_tile_info {
	/** value of thresh for each layer by tile cfr. Marcela   */
	double *thresh;
	/** number of tile */
	int tileno;
	/** start position */
	int start_pos;
	/** end position of the header */
	int end_header;
	/** end position */
	int end_pos;
	/** precinct number for each resolution level (width) */
	int pw[33];
	/** precinct number for each resolution level (height) */
	int ph[33];
	/** precinct size (in power of 2), in X for each resolution level */
	int pdx[33];
	/** precinct size (in power of 2), in Y for each resolution level */
	int pdy[33];
	/** information concerning packets inside tile */
	opj_packet_info_t *packet;
	/** add fixed_quality */
	int numpix;
	/** add fixed_quality */
	double distotile;
	/** number of tile parts */
	int num_tps;
	/** information concerning tile parts */
	opj_tp_info_t *tp;
} opj_tile_info_t;

/* UniPG>> */
/**
Marker structure
*/
typedef struct opj_marker_info_t {
	/** marker type */
	unsigned short int type;
	/** position in codestream */
	int pos;
	/** length, marker val included */
	int len;
} opj_marker_info_t;
/* <<UniPG */

/**
Index structure of the codestream
*/
typedef struct opj_codestream_info {
	/** maximum distortion reduction on the whole image (add for Marcela) */
	double D_max;
	/** packet number */
	int packno;
	/** writing the packet in the index with t2_encode_packets */
	int index_write;
	/** image width */
	int image_w;
	/** image height */
	int image_h;
	/** progression order */
	OPJ_PROG_ORDER prog;
	/** tile size in x */
	int tile_x;
	/** tile size in y */
	int tile_y;
	/** */
	int tile_Ox;
	/** */
	int tile_Oy;
	/** number of tiles in X */
	int tw;
	/** number of tiles in Y */
	int th;
	/** component numbers */
	int numcomps;
	/** number of layer */
	int numlayers;
	/** number of decomposition for each component */
	int *numdecompos;
/* UniPG>> */
	/** number of markers */
	int marknum;
	/** list of markers */
	opj_marker_info_t *marker;
	/** actual size of markers array */
	int maxmarknum;
/* <<UniPG */
	/** main header position */
	int main_head_start;
	/** main header position */
	int main_head_end;
	/** codestream's size */
	int codestream_size;
	/** information regarding tiles inside image */
	opj_tile_info_t *tile;
} opj_codestream_info_t;

#ifdef __cplusplus
extern "C" {
#endif


/* 
==========================================================
   openjpeg version
==========================================================
*/

OPJ_API const OPJ_CHAR * OPJ_CALLCONV opj_version(void);

/* 
==========================================================
   image functions definitions
==========================================================
*/

/**
Create an image
@param numcmpts number of components
@param cmptparms components parameters
@param clrspc image color space
@return returns a new image structure if successful, returns NULL otherwise
*/
OPJ_API opj_image_t* OPJ_CALLCONV opj_image_create(OPJ_UINT32 numcmpts, opj_image_cmptparm_t *cmptparms, OPJ_COLOR_SPACE clrspc);

/**
 * Creates an image without allocating memory for the image (used in the new version of the library).
 * 
 * @param	p_num_cmpts			the number of components
 * @param	p_cmpt_parms		the components parameters
 * @param	p_clr_spc			the image color space
 * 
 * @return	a new image structure if successful, NULL otherwise.
*/
OPJ_API opj_image_t* OPJ_CALLCONV opj_image_tile_create(OPJ_UINT32 numcmpts, opj_image_cmptparm_t *cmptparms, OPJ_COLOR_SPACE clrspc);

/**
Deallocate any resources associated with an image
@param image image to be destroyed
*/
OPJ_API void OPJ_CALLCONV opj_image_destroy(opj_image_t *image);

/* 
==========================================================
   stream functions definitions
==========================================================
*/

/**
 * Creates an abstract stream. This function does nothing except allocating memory and initializing the abstract stream.
 *
 * @param	l_is_reader		if set to true then the stream will be an input stream, an output stream else.
 * 
 * @return	a stream object.
*/
OPJ_API opj_stream_t* OPJ_CALLCONV opj_stream_default_create(bool p_is_input);
OPJ_API opj_stream_t* OPJ_CALLCONV opj_stream_create(OPJ_UINT32 p_size,bool p_is_input);

/**
 * Destroys a stream created by opj_create_stream. This function does NOT close the abstract stream. If needed the user must 
 * close its own implementation of the stream.
 * 
 * @param	p_stream	the stream to destroy.
 */
OPJ_API void OPJ_CALLCONV opj_stream_destroy(opj_stream_t* p_stream);

/**
 * Sets the given function to be used as a read function.
 * @param		p_stream	the stream to modify
 * @param		p_function	the function to use a read function.
*/
OPJ_API void OPJ_CALLCONV opj_stream_set_read_function(opj_stream_t* p_stream, opj_stream_read_fn p_function);

/**
 * Sets the given function to be used as a write function.
 * @param		p_stream	the stream to modify
 * @param		p_function	the function to use a write function.
*/
OPJ_API void OPJ_CALLCONV opj_stream_set_write_function(opj_stream_t* p_stream, opj_stream_write_fn p_function);

/**
 * Sets the given function to be used as a skip function.
 * @param		p_stream	the stream to modify
 * @param		p_function	the function to use a skip function.
*/
OPJ_API void OPJ_CALLCONV opj_stream_set_skip_function(opj_stream_t* p_stream, opj_stream_skip_fn p_function);

/**
 * Sets the given function to be used as a seek function, the stream is then seekable.
 * @param		p_stream	the stream to modify
 * @param		p_function	the function to use a skip function.
*/
OPJ_API void OPJ_CALLCONV opj_stream_set_seek_function(opj_stream_t* p_stream, opj_stream_seek_fn p_function);


/**
 * Sets the given data to be used as a user data for the stream.
 * @param		p_stream	the stream to modify
 * @param		p_data		the data to set.
*/
OPJ_API void OPJ_CALLCONV opj_stream_set_user_data (opj_stream_t* p_stream, void * p_data);

/**
 * Helper function.
 * Sets the stream to be a file stream. The FILE must have been open previously.
 * @param		p_stream	the stream to modify
 * @param		p_file		handler to an already open file.
*/
OPJ_API opj_stream_t* OPJ_CALLCONV opj_stream_create_default_file_stream (FILE * p_file,bool p_is_read_stream);
OPJ_API opj_stream_t* OPJ_CALLCONV opj_stream_create_file_stream (FILE * p_file,OPJ_UINT32 p_buffer_size, bool p_is_read_stream);



/* 
==========================================================
   event manager functions definitions
==========================================================
*/
OPJ_API bool OPJ_CALLCONV opj_set_info_handler(opj_codec_t * p_codec, opj_msg_callback p_callback,void * p_user_data);
OPJ_API bool OPJ_CALLCONV opj_set_warning_handler(opj_codec_t * p_codec, opj_msg_callback p_callback,void * p_user_data);
OPJ_API bool OPJ_CALLCONV opj_set_error_handler(opj_codec_t * p_codec, opj_msg_callback p_callback,void * p_user_data);



/* 
==========================================================
   codec functions definitions
==========================================================
*/
/**
Creates a J2K/JPT/JP2 decompression structure
@param format Decoder to select
@return Returns a handle to a decompressor if successful, returns NULL otherwise
*/
OPJ_API opj_codec_t* OPJ_CALLCONV opj_create_decompress(OPJ_CODEC_FORMAT format);

/**
Set decoding parameters to default values
@param parameters Decompression parameters
*/
OPJ_API void OPJ_CALLCONV opj_set_default_decoder_parameters(opj_dparameters_t *parameters);

#ifdef USE_OPJ_DEPRECATED
#ifdef _MSC_VER
#pragma message ( "warning, opj_setup_decoder is deprecated")
#else
#warning "warning, opj_setup_decoder is deprecated"
#endif
/**
Setup the decoder decoding parameters using user parameters.
Decoding parameters are returned in j2k->cp. 
@param dinfo decompressor handle
@param parameters decompression parameters
*/
OPJ_API bool OPJ_CALLCONV opj_setup_decoder(opj_codec_t *dinfo, opj_dparameters_t *parameters);
#endif

/**
Decode an image from a JPEG-2000 codestream 
@param dinfo decompressor handle
@param cio Input buffer stream
@return Returns a decoded image if successful, returns NULL otherwise
*/
OPJ_API opj_image_t* OPJ_CALLCONV opj_decode(opj_codec_t *p_decompressor, opj_stream_t * cio);

/**
 * Writes a tile with the given data.
 * 
 * @param	p_compressor		the jpeg2000 codec.
 * @param	p_tile_index		the index of the tile to write. At the moment, the tiles must be written from 0 to n-1 in sequence.
 * @param	p_data				pointer to the data to write. Data is arranged in sequence, data_comp0, then data_comp1, then ... NO INTERLEAVING should be set.
 * @param	p_data_size			this value os used to make sure the data being written is correct. The size must be equal to the sum for each component of tile_width * tile_height * component_size. component_size can be 1,2 or 4 bytes,
 *								depending on the precision of the given component.
 * @param	p_stream			the stream to write data to.
 * 
 * @return	true if the data could be written.
 */
OPJ_API bool OPJ_CALLCONV opj_write_tile (
					 opj_codec_t *p_codec,
					 OPJ_UINT32 p_tile_index,
					 OPJ_BYTE * p_data,
					 OPJ_UINT32 p_data_size,
					 opj_stream_t *p_stream
					);

/**
 * Reads a tile header. This function is compulsory and allows one to know the size of the tile thta will be decoded.
 * The user may need to refer to the image got by opj_read_header to understand the size being taken by the tile.
 *
 * @param	p_codec			the jpeg2000 codec.
 * @param	p_tile_index	pointer to a value that will hold the index of the tile being decoded, in case of success.
 * @param	p_data_size		pointer to a value that will hold the maximum size of the decoded data, in case of success. In case
 *							of truncated codestreams, the actual number of bytes decoded may be lower. The computation of the size is the same
 *							as depicted in opj_write_tile.
 * @param	p_tile_x0		pointer to a value that will hold the x0 pos of the tile (in the image).
 * @param	p_tile_y0		pointer to a value that will hold the y0 pos of the tile (in the image).
 * @param	p_tile_x1		pointer to a value that will hold the x1 pos of the tile (in the image).
 * @param	p_tile_y1		pointer to a value that will hold the y1 pos of the tile (in the image).
 * @param	p_nb_comps		pointer to a value that will hold the number of components in the tile.
 * @param	p_should_go_on	pointer to a boolean that will hold the fact that the decoding should go on. In case the
 *							codestream is over at the time of the call, the value will be set to false. The user should then stop
 *							the decoding.
 * @param	p_stream		the stream to decode.
 * @return	true			if the tile header could be decoded. In case the decoding should end, the returned value is still true.
 *							returning false may be the result of a shortage of memory or an internal error.
 */				
OPJ_API bool OPJ_CALLCONV opj_read_tile_header(
					opj_codec_t *p_codec,
					OPJ_UINT32 * p_tile_index,
					OPJ_UINT32 * p_data_size,
					OPJ_INT32 * p_tile_x0,
					OPJ_INT32 * p_tile_y0,
					OPJ_INT32 * p_tile_x1,
					OPJ_INT32 * p_tile_y1,
					OPJ_UINT32 * p_nb_comps,
					bool * p_should_go_on,
					opj_stream_t * p_stream);


/**
 * Reads a tile data. This function is compulsory and allows one to decode tile data. opj_read_tile_header should be called before.
 * The user may need to refer to the image got by opj_read_header to understand the size being taken by the tile.
 *
 * @param	p_codec			the jpeg2000 codec.
 * @param	p_tile_index	the index of the tile being decoded, this should be the value set by opj_read_tile_header.
 * @param	p_data			pointer to a memory block that will hold the decoded data.
 * @param	p_data_size		size of p_data. p_data_size should be bigger or equal to the value set by opj_read_tile_header.
 * @param	p_stream		the stream to decode.
 *
 * @return	true			if the data could be decoded.
 */				
OPJ_API bool OPJ_CALLCONV opj_decode_tile_data(
					opj_codec_t *p_codec,
					OPJ_UINT32 p_tile_index,
					OPJ_BYTE * p_data,
					OPJ_UINT32 p_data_size,
					opj_stream_t *p_stream
					);

/**
 * Sets the given area to be decoded. This function should be called right after opj_read_header and before any tile header reading.
 * 
 * @param	p_codec			the jpeg2000 codec.
 * @param	p_start_x		the left position of the rectangle to decode (in image coordinates).
 * @param	p_end_x			the right position of the rectangle to decode (in image coordinates).
 * @param	p_start_y		the up position of the rectangle to decode (in image coordinates).
 * @param	p_end_y			the bottom position of the rectangle to decode (in image coordinates).
 *
 * @return	true			if the area could be set.
 */				
OPJ_API bool OPJ_CALLCONV opj_set_decode_area(
					opj_codec_t *p_codec,
					OPJ_INT32 p_start_x,
					OPJ_INT32 p_start_y,
					OPJ_INT32 p_end_x,
					OPJ_INT32 p_end_y
					);


/**
Decode an image from a JPEG-2000 codestream and extract the codestream information
@param dinfo decompressor handle
@param cio Input buffer stream
@param cstr_info Codestream information structure if needed afterwards, NULL otherwise
@return Returns a decoded image if successful, returns NULL otherwise
*/
//OPJ_API opj_image_t* OPJ_CALLCONV opj_decode_with_info(opj_dinfo_t *dinfo, opj_stream_t cio, opj_codestream_info_t *cstr_info);
/**
Creates a J2K/JP2 compression structure
@param format Coder to select
@return Returns a handle to a compressor if successful, returns NULL otherwise
*/
OPJ_API opj_codec_t* OPJ_CALLCONV opj_create_compress(OPJ_CODEC_FORMAT format);

/**
Destroy a decompressor handle
@param dinfo decompressor handle to destroy
*/
OPJ_API void OPJ_CALLCONV opj_destroy_codec(opj_codec_t * p_codec);

/**
Set encoding parameters to default values, that means : 
<ul>
<li>Lossless
<li>1 tile
<li>Size of precinct : 2^15 x 2^15 (means 1 precinct)
<li>Size of code-block : 64 x 64
<li>Number of resolutions: 6
<li>No SOP marker in the codestream
<li>No EPH marker in the codestream
<li>No sub-sampling in x or y direction
<li>No mode switch activated
<li>Progression order: LRCP
<li>No index file
<li>No ROI upshifted
<li>No offset of the origin of the image
<li>No offset of the origin of the tiles
<li>Reversible DWT 5-3
</ul>
@param parameters Compression parameters
*/
OPJ_API void OPJ_CALLCONV opj_set_default_encoder_parameters(opj_cparameters_t *parameters);

/**
 * Sets the MCT matrix to use.
 * 
 * @param	parameters		the parameters to change.
 * @param	pEncodingMatrix	the encoding matrix.
 * @param	p_dc_shift		the dc shift coefficients to use.
 * @param	pNbComp			the number of components of the image.
 *
 * @return	true if the parameters could be set.
 */
OPJ_API bool OPJ_CALLCONV opj_set_MCT(opj_cparameters_t *parameters,OPJ_FLOAT32 * pEncodingMatrix,OPJ_INT32 * p_dc_shift,OPJ_UINT32 pNbComp);

/**
 * Restricts the decoding to the given image area.
 * 
 * @param	parameters		the parameters to update.
 * @param	p_start_x		the starting x position of the area to decode.
 * @param	p_start_y		the starting y position of the area to decode.
 * @param	p_end_x			the x end position of the area to decode. 
 * @param	p_end_x			the y end position of the area to decode.
 */
OPJ_API bool OPJ_CALLCONV opj_restrict_decoding (opj_dparameters_t *parameters,OPJ_INT32 p_start_x,OPJ_INT32 p_start_y,OPJ_INT32 p_end_x,OPJ_INT32 p_end_y);

#ifdef USE_OPJ_DEPRECATED
#ifdef _MSC_VER
#pragma message ("warning, opj_setup_encoder is deprecated")
#else
#warning "warning, opj_setup_encoder is deprecated"
#endif
/**
Setup the encoder parameters using the current image and using user parameters. 
@param cinfo Compressor handle
@param parameters Compression parameters
@param image Input filled image
*/
OPJ_API bool OPJ_CALLCONV opj_setup_encoder(opj_codec_t *cinfo, opj_cparameters_t *parameters, opj_image_t *image);
#endif

/**
 * Decodes an image header.
 * 
 * @param	p_codec			codec to use to decode the image.
 * @param	p_image			pointer to a previously created image.
 * @param	p_tile_x0		pointer to a value that will hold the reference point x0 of the tiling grid.
 * @param	p_tile_y0		pointer to a value that will hold the reference point y0 of the tiling grid.
 * @param	p_tile_width	pointer to a value that will hold the size in x of a tile in the grid.
 * @param	p_tile_height	pointer to a value that will hold the size in y of a tile in the grid.
 * @param	p_nb_tiles_x	pointer to a value that will hold the number of tiles in the x direction.
 * @param	p_nb_tiles_y	pointer to a value that will hold the number of tiles in the y direction.
 */
OPJ_API bool OPJ_CALLCONV opj_read_header (
										opj_codec_t *p_codec,
										opj_image_t ** p_image,
										OPJ_INT32 * p_tile_x0,
										OPJ_INT32 * p_tile_y0,
										OPJ_UINT32 * p_tile_width,
										OPJ_UINT32 * p_tile_height,
										OPJ_UINT32 * p_nb_tiles_x,
										OPJ_UINT32 * p_nb_tiles_y,
										opj_stream_t *p_cio);


OPJ_API bool OPJ_CALLCONV opj_end_decompress (opj_codec_t *p_codec,opj_stream_t *p_cio);
/**
Encode an image into a JPEG-2000 codestream
@param cinfo compressor handle
@param cio Output buffer stream
@param image Image to encode
@param index Depreacted -> Set to NULL. To extract index, used opj_encode_wci()
@return Returns true if successful, returns false otherwise
*/
OPJ_API bool OPJ_CALLCONV opj_encode(opj_codec_t *cinfo, opj_stream_t * cio);

OPJ_API bool OPJ_CALLCONV opj_start_compress (opj_codec_t *p_codec,opj_image_t * p_image,opj_stream_t *p_cio);

OPJ_API bool OPJ_CALLCONV opj_end_compress (opj_codec_t *p_codec,opj_stream_t *p_cio);
/**
Encode an image into a JPEG-2000 codestream and extract the codestream information
@param cinfo compressor handle
@param cio Output buffer stream
@param image Image to encode
@param cstr_info Codestream information structure if needed afterwards, NULL otherwise
@return Returns true if successful, returns false otherwise
*/
//OPJ_API bool OPJ_CALLCONV opj_encode_with_info(opj_cinfo_t *cinfo, opj_stream_t cio, opj_image_t *image, opj_codestream_info_t *cstr_info);
/**
Destroy Codestream information after compression or decompression
@param cstr_info Codestream information structure
*/
OPJ_API void OPJ_CALLCONV opj_destroy_cstr_info(opj_codestream_info_t *cstr_info);

//==============================================================================
//==============================================================================
/** profiling part */
#ifdef _PROFILE
void _ProfInit(void);
void _ProfPrint(void);
#define PROFINIT() _ProfInit();
#define PROFSAVE(file) _ProfSave(file);
#define PROFPRINT() _ProfPrint();
#else
#define PROFINIT()
#define PROFSAVE(file)
#define PROFPRINT() 
#endif // !_PROFILE

#ifdef __cplusplus
}
#endif

#endif /* OPENJPEG_H */


