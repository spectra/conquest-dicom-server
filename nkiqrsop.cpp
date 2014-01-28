/*
19990317	ljz	NKI-specific code
19990903	ljz	Implemented NKI MaxRowColumn VR in DCO
19990906	ljz	Improved implementation of MaxRowColumn
19991022	ljz	Changed the root of NKI-made UIDs to the official one supplied by
			Medical Connections(UK): 1.2.826.0.1.3680043.2.135.1066.xxxxxxxxxx
19991122	ljz	Added NKI-CompressionMode 2: safer, with CRC checks
20000131	ljz	Regardless the FileCompressMode in Dicom.ini, always send images
			compressed (mode=2) when communicating with an NKI application.
20001105	mvh	Fixed where malloc and new were mixed (vr->data)
20001106	mvh	Use delete [] operation for vr->Data
20001106	mvh	Temporary fix of BC leak in CompressNKI and DecompressNKI
20001120	mvh	Fix bug - vr->data was reallocated without changing vr->length
20001127	ljz	Fix: Crashes happened when more than one 'ServerChildThread' was
			active. m_pDCO is wrongly shared by all threads !!
20010424	mvh	Plugged in faster and safer decompress
20010426	ljz	Fixed leak when connection is aborted
20010429	mvh	Interleaved CRC computation with compress code (factor 2 faster)
			Added GetADDO to allow read ahead within calling program
20010501	mvh	Merged ljz's change of 20010426                      
20010502	mvh	Added extrabytes pointer to Read and RetrieveOn
20010502	mvh	Added vr(9999,0300)=SliceLimit: send at most so many slices
20010502	mvh	Changed this vr to (9999,0500)=SliceLimit
20011219	ljz	Added extra check in case other manufacturers than NKI use
			VR (0x7fe0, 0x0010), such as ACUSON
20020317	mvh	Replace true by TRUE
20020415	mvh	Added error handling on ProcessDDO
20020429 	mvh	fixed reporting of number of complete slices (now starts with 1)
			return cancel status if C_STORE failed
20020609	mvh	Added compressor modes 3 and 4
20020609	mvh	Added VR (9999,0600): MaxCompressionLevel (default 2)
			Note: This level (max of 4) is also used when downsizing
20020613	ljz	Exported DecompressNKI and CompressNKI
20020619	ljz	Damn! ELSCINT uses (0x7fe0, 0x0010) too (see modification on 20011219)
			Extra check on zero-length pixeldata
20020930	mvh	Fixed SliceLimit VR
20021016	mvh	Removed __BORLANDC__ language construct - to fix downsize with BC55
20021115	mvh	Added Generic style retrieve classes; print error messages from c-move
20030522	ljz	Added function ComputeCRC
20030605	ljz	Fix in DecompressNKI: dgate crashed when DCMTK's 'storescu.exe' wants
			to send an NKIcompressed image to dgate; it refuses to send the pixeldata!
20030701	mvh	QualifyOn now also has compression parameter; transfer syntax work in progress
20030703	mvh	Tested recompress functions
20030704	mvh	Disabled decompression in ProcessDDO for non-nki clients; is done by recompress
			When downsizing use DecompressImage(); also supports JPEG; Removed MaybeRecompress
			Recompression for NKI clients only when downsizing; otherwise as specified in acrnema.map
20030705	mvh	Moved recompression out of ProcessDDO into StandardRetrieveNKI::Read
			Skip recompression to same level as incoming
20030706	mvh	Optional filename parameter for recompress (not used yet); set env for offis tools
20030706	mvh	Attach VRType to PDU's for implicit little endian support
20030709	mvh	Removed DCMDICPATH; is not needed
20030819	mvh	Allow longer filenames
20030905	mvh	Note: recompressfile; DecompressImageFile and CompressJPEGImageFile do not allow spaces in filename
20040401	mvh	Added Changed and ActualMode flags to compress routines; only give compress message if something changed
			Set maxcompression to 4 for NKI send
20040403	mvh	Added own SaveDICOMDataObject as in dgate.cpp
20040406	ljz	Also copy TypeCode in DecompressNKI when converting (0x7fdf, 0x0010) to (0x7fe0, 0x0010)
			Make TypeCode of (0x7fdf, 0x0010) OW instead of OB, because OFFIS refuses to compress OB
20040406	mvh	Always use EXPLICIT syntax for jpeg, fix v2 always use DUMP
			Use -F +ti option for dcmdjpeg for writing to v2: creates raw dump, implicit
			Refuse to jpeg compress V2 files and images != 16 bits; \n is all messages
			Fix error handling of CompressJpegImage
20040530	mvh	Removed unused variable
20040722	mvh	Added "nj" compression: leaves JPEG as is; else MAXNKICOMPRESSION
20041101	ljz	Added built-in JPEG and RLE decompressor
20041102	mvh	Fix problem with external JPEG compression: clear transfer syntax prior 
			to save for OFFIS tools with DICOM_CHAPTER_10_EXPLICIT
20041103	mvh	Added k1,k2,k4,k8 compressors: downsize to 1024,512,256,128 pixels if bigger to start with
20041112	mvh	Called AE SERVER~xx in C-MOVE lets xx override outgoing compression as well 
			(e.g., call CONQUESTSRV1~k4 to always get images downsized to 256x256)
20050102	mvh	Added NOINTJPEG flag to allow compile through total.cxx
20050103	mvh	Changed include file to lower case (for linux)
20050108	mvh	Adapted for linux compile (work in progress)
20050109	mvh	Added configurable TCPIPTimeOut
20050118	mvh	replaced thread local storage under linux with variables in object
20050119	mvh	added rudimentary support to start external (de)compressors under linux
20050121	mvh	Changed filename to lower case
20050122	mvh	Improved external jpeg support under Linux: load dictionary, wait until ready
20050130	mvh	Added To8BitMonochrome and ToGif
20050204	mvh	Small fix in ToGif for non-square images; also interpret RescaleIntercept as float
20050205	mvh	Added counters for compression activity
20050206	mvh	Optimized downsizing: do not decompress if no downsizing to occur
20050206	mvh	Note: replaced thread local storage under linux with variables in object is INCORRECT
			Under linux, the server now can also serve one at a time
			Fix for color to gif; added limited auto scaling in 16 bits to gif
20050211	mvh	Removed need for thread local storage
20051210	mvh	Added "vX" compression (same as as is)
20051217	mvh	Use system() to call on offis apps in linux (now works)
20051217	mvh	Use new VR::ReAlloc method to replace data in VR; fixed 2 float warnings
20051229	mvh	Fixed several leaks in (jpeg)compression code; changed alloc for nki compression
20051230	mvh	Added +sr option to dcmcjpeg: compress without changing rescaleslope/intercept
			This option is required for our viewers: slices must all have same rescale
20060219	mvh	Removed warning in writegif
20060222	mvh	Added extra checks (not on ID strings) to pass as NKI compressed data
20060311	mvh	dcmcjpeg opts string got truncated (thanks Rainer Libowski)
			fixed unused CompressJPEGImageFile (wrong exe called)
			external decompress temporary files now in printer_files (thanks Rainer Libowski)
20060324	mvh	Added StripGroup2 option to recompress; strip group 2 from outgoing c-stores if not compression "as" or "is"
20060328	mvh	Use IsAbstractSyntaxAccepted(iUID) to test if host accepts image
20060402	mvh	Fix crash when recieving or dropping jpeg compressed color images
			Consider not removing transfer syntax (0x0002, 0x0010) prior to dcmdjpeg/dcmcjpeg
			Would fix problem with external decoding color jpeg images
20060402	mvh	Changed IsAbstractSyntaxAccepted(iUID) test back (thanks Andrej Savelov)
20060405	mvh	That was not the problem
20060618	mvh	Tested IsAbstractSyntaxAccepted - seems to work. Removed need for min()
20060619	mvh	Do not remove transfer syntax before decompression (20060402 suggestion)
			Maintain original object when decompression fails, changed wording of message
			Only complain about internal decompressor for jpeg
20070104	mvh	Export automatic SaveDICOMDataObject
20070113	mvh	Never delete transfer syntax (was left in CompressJpegImage, solves coding error in jpeg store)
			Tested with $c server debug command
20070210	mvh	Export MaybeDownsize and check on 0 for passed size
20070307	mvh	Added several debug prints in retrieve, e.g. at bail out because connection dropped
20070308	bcb	removed #include <wait.h> from DARWIN
20070314	mvh	Send 0000,1030 (MoveOriginatorAE) and 0000,1031 (MoveOriginatorMessageID) in SS->Write as result of Move
20070315	mvh	Merged bcb DARWIN stuff; Set TCPIPTimeOut for PDU that moves images
20070316	mvh	Added (color) ToBMP for convert_to_bmp; added level and window to ToGif and ToBMP
20070407	mvh	Use ~p1..9A..Z to override C-MOVE port (adds 1..36 to port number)
20070902	mvh	WriteGif now cpp
20071027	mvh	Added quotes around filenames passed to dcmdjpeg and dcmcjpeg: avoids errors with spaces in paths
20071101	mvh	Enabled JPEG compression and decompression of non-16 bit data
20071104	mvh	Added DecompressNon16BitsJpeg (default TRUE)
20071105	mvh	Restore image when dcmc/djpeg failed to start
20080103	mvh	Added mode 'uj': leave jpeg as is, otherwise uncompress
			Added DecompressImage to recompress()
20080820	mvh	Solaris fix (do not use variable name SS)
20081116	mvh	Adapted for very large objects (use unsigned int for length)
20081201	mvh	Added JPG converter
20081203	mvh	Enabled internal decompressor for color, added frame extraction for jpg etc
			Add frame extraction control = 0x09999,0x0201
20090209	mvh	Added QueryMoveScript callback; removed unused variable
20090325	mvh	Added RetrieveResult converter, impact on performance to be tested
20090412	mvh	Changed jpeg encode_image mode to correct BGR RGB mixup
20090513	mvh	Added modes 's0' to 's9' call script CompressionConverter0 to 9
20090518	mvh	Added modes ka, kb and kc to downsize to 64, 32 and 16
20090921	mvh	Added ExtractFrames
20090927	mvh	Stop jpg compression for PR SR and RT
20091231	bcb	Added HAVE_LIBJPEG (version 6c!) and HAVE_LIBJASPER for external library support (beta for now)
			Changed char* to const char* and cast time_t as int for gcc4.2 warnings
20100111	mvh	Fixed downsize for 32 bits pixel; bcb const; cast of Time() to (int)
20100112	mvh	Merged
20100113	mvh	A few more errors in downsize for 32 bits
20100116	mvh	Fixed DecompressImage compile error if HAVE_LIBJPEG is defined
20100118	mvh	Added one missing else in CompressJPEG2K
20100119	bcb	The else was not really missing; added some const
20100120	mvh	Catch jpeg2000 configuration if HAVE_LIBJASPER not defined
20100121	bcb+mvh	Blocked out old jpeg decompressor if HAVE_LIBJPEG, 
			removed color checks as both decompressors do color now
		mvh	Made lossy to lossless switch a warning not error in CompressImage
			Set mode to '1' instead of 1 after switch
20100122	mvh	Note: the HAVE_LIBJPEG code supresses RLE support
20100122	mvh	Added experimental C-CANCEL support for all C-MOVES
20100123	mvh	Added counters for jpeg2000
20100124	mvh	Added GetNumberOfFrames
20100125	mvh	GetPrivateProfileString -> MyGetPrivateProfileString
20100126	mvh	Include gpps.hpp
20100207	mvh	Fixed ExtractFrame(s) for frames packaged into pixel data without sequences
20100209	mvh	Run RetrieveResult also for non-nki clients
20100210	bcb	Fix memory leak
20100214	mvh	Merged
20100223	bcb	Combined DecompressImage and DecompressImageFile 
			Add FUJI_FIX for evil LittleEndianImplicit jpeg compressed images.
20100224	bcb	Added libopenjpeg to use in place of Jasper, fixed more warnings (-Wall)
20100227	mvh	After 1.4.16alpha3: crash when jpeg compressing RT object
20100330	bcb	Frames to LIBJPEG, JASPER, and OPENJPEG
20100619	bcb	Many fixes for leaks, allow both Jasper and openJPEG as a dicom.ini choice (not finished).
20100703	mvh	Merged; snprintf to _snprintf
20100706	bcb	Merged, replaced _snprintf with memcpy.
20100721	mvh	Merged back; fixed a few ascii to int conversions with atoi
20100723	mvh	Merged bcb fixes in new version of ToJPG
20100728	bcb	Installed RLE support with HAVE_LIBJPEG, used new deivr Get's and ChangeVR's
20100815	mvh	Merged; do not use GETUINT8 for US type; added space =TRUE to setting PixelSpacing
			Simplified DecompressRLE
20100815	mvh	Fixed bug 30 in t=2127: YBR_FULL_422 images not passed to dcmcjpg
20100823	mvh	bcb moved that check to the right place
20100824	mvh	Pass local VariableVRs to script engine
20100826	mvh	bcb fixed lossy jpeg2000 for signed data
20100901	mvh	bcb Added fix for PlanarConfiguration=1 data
20100905	mvh	Removed file functions: now RecompressFile uses Recompress
20100905	mvh	Merged; Added UseBuiltInJPEG flag
20100914	bcb	Fixed RLE decode for frames, added Deplane, DecodePalette for regular and segmented palettes
20100918	mvh	Attempted merged (very difficult as fixes were made in older version)
20100920	bcb	Fixed warnings
20100922	mvh	Merged
20100928	mvh	Fixed ExtractFrame(s) for NKI compressed data
20101003	mvh	Added 9999,0900 script
20101004	mvh	Use updated gif codec; started on animated gif
20101009	mvh	Protected gif coder for out of memory
20101018	mvh	Swap BGR to RGB for ToJPG
20100920	bcb	Fixed j2k decompressing of j2k file instead of just the stream (used by Accusoft Pegasus).
20100923	mvh	ToJPG can be used to create MPG files using external tools
20101116	bcb	Add UL, UB, UI, and UE compression to fix big endian recieve, merged, warnings
20101121	mvh	Merged
20101220	mvh	Fixed color swap for jpg and bmp; fix deplane and depalette are called when needed
20101227	mvh	Fixed 'un' in bcb 'ui' etc code in recompress 
20110106	mvh	Fix ToBMP for linux 64 bits (used long)
20110119	mvh	Use ExtendedPDU_Service to pass scripting state
20110320	mvh	Fix downsize & tojpg  when #bytes in image is odd
			Only apply RescaleIntercept for CT in tojp
20110326	mvh	Increased temp string in linux ExecHidden that caused decompress crash
20110413	mvh	Allow test of jpeg or rle decompression even if no group 0002 data
20110414	mvh	Moved jpeg decompression height errors to SystemDebug
20110419	mvh	normalized line endings; taken out superfluous prints
20110423	mvh	Fixed "UJ" broken when UI etc were introduced
20110502	mvh	always write bitstored 0x0028,0x0101 when writing highbit 0x0028,0x0102
20110904	bcb	Fixed J1 and J2 distiction
20110926	mvh	Added DcmConvertPixelData for tomono and crop
20111010	mvh	Fix in J1 and J2 distiction fix: '2' was not translated into 2 invalidating subs. tests
20111011	mvh	Fix in SaveDicomDataObject (archive): 'cannot rewrite .. in v2 format' led to a double DDO->Free
20111018	mvh	Added TempDir ini file option
20111022	mvh	Added private move command option 0x9999, 0a000 ConquestMoveOriginatorAE; let retrieveconverter work with command
20111113	mvh	Restored the original float DeYBRFULL code; the modified code did not work; read VR again, is used for deplane
20120214	mvh	Allow size==0 in DICOM to image conversion
20120327	mvh	Fix LossyQuality entry in dicom.ini for built-in JPEG compression
20120401	mvh	Fix in print (crashes when modality not passed)
20120402	mvh	Default UseBuiltInJpeg properly to 0
20120624	mvh	Set Header (0028,2110) to 01 after lossy compression
20120624	mvh	Do not modify bitsstored, highbit and numberofbits after compression
20120628	mvh	Some layout of debug prints
20120630	mvh	Reverse .dcm check (dicom if not .V2); 
                        Pass lossy quality to CompressJPEGImage from compression string
20120723	mvh	Fixed 'l' or 'l' to 'l' or 'L' found by bcb
20120918	ljz	Fixed comparison with .v2 in SaveDICOMDataObject()
20121208	mvh	Block deplane if SamplesPerPixel is not 3
20130218	mvh	JPEG compression did not set right sopclass!!!!
20130823	mvh	Fixed lossy jpeg compression for 12 bits data
20130920        ea      Corrected the calculation of new pixel spacing in MaybeDownsize
20131013	mvh	Default UseBuiltInJPEG set to 1; added quality parameter to ToJPG
*/

#define bool BOOL
#define true TRUE
#define false FALSE
#ifndef UNUSED_ARGUMENT
#define UNUSED_ARGUMENT(x) (void)x
#endif

#include "dicom.hpp"
#include "nkiqrsop.hpp"
#include "dgate.hpp"
#include "gpps.hpp"
#include <time.h>

#ifdef HAVE_LIBJPEG
#include <jpeglib.h>
#include <jerror.h>
#include <setjmp.h>
#endif
#ifdef HAVE_LIBJASPER
#include <jasper/jasper.h>
#endif
#ifdef HAVE_LIBOPENJPEG
#include <openjpeg.h>
#endif

// JPEG2000 quality
#ifndef DEFAULT_LOSSY
#define DEFAULT_LOSSY "95"
#endif
#define DEFAULT_LOSSY_INT 95
#define MIN_QUALITY 1

int	TCPIPTimeOut = 300;				// timeout for TCP/IP in seconds

int	NKIPrivateCompress=0;				// counters
int	NKIPrivateDecompress=0;
int	DownSizeImage=0;
int	DecompressJpeg=0;
int	CompressJpeg=0;
int	DecompressJpeg2000=0;
int	CompressJpeg2000=0;
int	DecompressedRLE=0;
int	DePlaned=0;
int	DePaletted=0;
int	RecompressTime=0;

#define MAXNKICOMPRESSION 4

static const unsigned int CRC32_table[256] = {
      0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
      0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
      0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
      0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
      0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
      0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
      0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
      0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
      0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
      0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
      0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
      0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
      0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
      0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
      0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
      0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
      0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
      0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
      0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
      0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
      0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
      0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
      0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
      0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
      0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
      0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
      0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
      0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
      0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
      0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
      0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
      0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
      0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
      0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
      0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
      0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
      0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
      0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
      0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
      0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
      0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
      0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
      0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

#ifdef HAVE_LIBJPEG
extern int gJpegQuality;// The quality of the lossy jpeg or j2k image from dicom.ini.

 /* Here's the extended error handler struct for libjpeg:
    (from jpeg example.c)*/
struct jerror_mgr 
{ 
  struct jpeg_error_mgr pub;	/* "public" fields */
  jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct jerror_mgr * jerror_ptr;

typedef struct 
{ 
  struct jpeg_source_mgr pub;	/* public fields */
} jsource_mgr;

typedef jsource_mgr * jsrc_ptr;
#endif

#ifdef HAVE_J2K
#ifndef HAVE_LIBJPEG// Don't want it twice
extern int gJpegQuality;// The quality of the lossy jpeg or j2k image from dicom.ini.
#endif
#endif
#ifdef HAVE_BOTH_J2KLIBS
extern int gUseOpenJpeg;// If we have both Jasper and OpenJPEG, it lets the dicom.ini choose.
#endif

#define CLRSPC_FAM_UNKNOWN 0
#define CLRSPC_FAM_GRAYSCALE 1
#define CLRSPC_FAM_RGB 2
#define CLRSPC_FAM_YBR_FULL 3
/*Skipped numbers for Jasper */
#define CLRSPC_FAM_YCBCR_ICT 6
#define CLRSPC_FAM_YCBCR_RCT 7
#define CLRSPC_FAM_YCBCR_F422 8
#define CLRSPC_FAM_YCBCR_422 9
#define CLRSPC_FAM_YCBCR_420 10

/* Following function used in 'dgate.cpp' when executing the commandline switch
   '-fa'. This is when a dicomfile has to be stored in the dicomserver.
   The problem is that filenames generated in 'dgatefn.cpp' may be not unique
   if many files are dropped in the dicomserver. The static 'counter' intended
   to solve this problem is reset to zero each time dgate is launched.
   Now this 'counter' is initialized with a CRC of the filename.
*/
unsigned int ComputeCRC(char* pcData, int iNbChars)
{ int		i;
  unsigned int	uiCRC = 0;

  for (i=0; i<iNbChars; i++)
    uiCRC = CRC32_table[(unsigned char)uiCRC ^ (unsigned char)pcData[i]] ^ ((uiCRC >> 8) & 0x00FFFFFF);
  return uiCRC;
}

/* Read and cache UseBuiltInDecompressor and DecompressNon16BitsJpeg variable from dicom.ini 
*/

#ifndef	RootConfig
extern	char	RootConfig[];
#endif
#ifndef	ConfigFile
extern	char	ConfigFile[];
#endif

BOOL UseBuiltInDecompressor(BOOL *DecompressNon16BitsJpeg = NULL)
{ char			RootSC[64];
  char			Temp[128];
  static int		res=-1, dn16=1;

  if (res==-1)
  { MyGetPrivateProfileString ( RootConfig, "MicroPACS", RootConfig,
	  	(char*) RootSC, 64, ConfigFile);

    MyGetPrivateProfileString ( RootSC, "UseBuiltInDecompressor", "1",
		(char*) Temp, 128, ConfigFile);
    res = atoi(Temp);

    MyGetPrivateProfileString ( RootSC, "UseBuiltInJPEG", "1",
		(char*) Temp, 128, ConfigFile);
    res = atoi(Temp);

    MyGetPrivateProfileString ( RootSC, "DecompressNon16BitsJpeg", "1",
		(char*) Temp, 128, ConfigFile);
    dn16 = atoi(Temp);
  }

  if (DecompressNon16BitsJpeg) *DecompressNon16BitsJpeg = dn16;
  return(res);
}

/*******************  NKI specific Retrieve Classes *************************/
int CallImportConverterN(DICOMDataObject *DDO, int N, char *pszModality, char *pszStationName, char *pszSop, char *patid, ExtendedPDU_Service *PDU, char *Storage, char *Script);

StandardRetrieveNKI::StandardRetrieveNKI()
{
}

BOOL	StandardRetrieveNKI	::	Read (
	ExtendedPDU_Service		*PDU,
	DICOMCommandObject		*DCO,
	void				*ExtraBytes)
	{
	UID	MyUID, uid, iUID, AppUID ("1.2.840.10008.3.1.1.1");
	VR	*vr;
	DICOMDataObject	DDO;
	Array < DICOMDataObject *>	ADDO;
	UINT		Index;
	BYTE		IP [ 64 ], lPort [ 64 ], ACRNema [ 17 ], MyACR[17], Compress[64];
	StandardStorage	*SStorage;
	DICOMDataObject	*iDDO;
	ExtendedPDU_Service	NewPDU;
	UINT16		Failed;
	unsigned int iVrSliceLimit = 0xffffffff;
	int		status = 0;
	UID		TrnSyntaxUID;
//	int		ContextID;
	char		*AcceptedCompress, *Compression;
	char		Called[20], Calling[20];
	BOOL		StripGroup2, Cancelled;

	if (DCO)
		{
		vr = DCO->GetVR(0x9999, 0x0500);
		if (vr && vr->Length)iVrSliceLimit = vr->GetUINT();
	  	}

	GetUID(MyUID);

	if( ! PDU )
		return ( FALSE );

	if( ! DCO )
		return ( FALSE );

	vr = DCO->GetVR(0x0000, 0x0002);
	SetUID(uid, vr);
	if (!(MyUID == uid))
		return ( FALSE );

	strcpy(Calling, (char *)(((AAssociateAC *)PDU)->CallingApTitle));
	while (Calling[strlen(Calling)-1]==' ') Calling[strlen(Calling)-1] = 0;

	if (! CMoveRQ :: Read (DCO, PDU, &DDO) )
		{
		SystemDebug.printf("Retrieve: wrong command\n");
		return ( FALSE ); // my SOP, but wrong command
		}

	NewPDU.AttachRTC(&VRType);
	NewPDU.SetTimeOut(TCPIPTimeOut);

	if (! QueryMoveScript (PDU, DCO, &DDO))
		{
		CMoveRSP :: Write (PDU, DCO, 0xc013, 0, 0, 0, 0, NULL );
		SystemDebug.printf("Retrieve: operation blocked by script\n");
		return ( TRUE );
		}

	vr = DCO->GetVR(0x0000, 0x0600);
	if(!vr)
		{
		CMoveRSP :: Write ( PDU, DCO, 0xc001 , 0, 0, 0, 0, NULL );
		SystemDebug.printf("Retrieve: move destination missing\n");
		return ( TRUE );
		}

	memset((void*)ACRNema, 0, 17);
	if(vr->Length > 16)
		vr->Length = 16;
	memcpy((void*)ACRNema, vr->Data, (int) vr->Length);
	if(!vr->Length)
		{
		CMoveRSP :: Write ( PDU, DCO, 0xc002 , 0, 0, 0, 0, NULL );
		SystemDebug.printf("Retrieve: move destination empty\n");
		return ( TRUE );
		}
	if(ACRNema[vr->Length-1]==' ')
		ACRNema[vr->Length-1] = '\0';

	if(!QualifyOn(ACRNema, MyACR, IP, lPort, Compress))
		{
		CMoveRSP :: Write (PDU, DCO, 0xc003, 0, 0, 0, 0, NULL );
		SystemDebug.printf("Retrieve: move destination not allowed or known\n: %s", ACRNema);
		return ( TRUE );
		}
		
	vr = DCO->GetVR(0x9999, 0x0a00);
	if (vr)
		{ 
		strncpy((char *)MyACR, (const char*)vr->Data, vr->Length);
		MyACR[vr->Length] = 0;
		}
	
	if (! SearchOn (&DDO, &ADDO) )//bcb, mvh: fills ADDO, must delete before exit
		{
		CMoveRSP :: Write (PDU, DCO, 0xc004, 0, 0, 0, 0, NULL );
		SystemDebug.printf("Retrieve: move search failed\n");
		return ( TRUE );
		}

	if (iVrSliceLimit < 0xffffffff)
		while (ADDO.GetSize() > iVrSliceLimit)
		{
			delete ADDO.Get(ADDO.GetSize()-1);
			ADDO.RemoveAt(ADDO.GetSize()-1);
		}

	// If the called AE looks like SERVER~j2, then the last 2 characters override the outgoing compression set in ACRNEMA.MAP
	strcpy(Called, (char *)(((AAssociateAC *)PDU)->CalledApTitle));
	while (Called[strlen(Called)-1]==' ') Called[strlen(Called)-1] = 0;
        Compression = strchr(Called, '~');
	if (!Compression) Compression = (char *)Compress; else Compression++;

	// If the called AE looks like SERVER~p2, then the last character overrides the outgoing port set in ACRNEMA.MAP
        if (Compression[0]=='P' || Compression[0]=='p')			// override port
		{
		sprintf((char *)lPort, "%d", atoi((char *)lPort)+Compression[1]-'0');
		Compression= (char *)Compress;				// use default compress
		}

	NewPDU.SetRequestedCompressionType((char *)Compression);	// propose compression type

	NewPDU.SetApplicationContext ( AppUID );
	NewPDU.SetLocalAddress ( MyACR );
	NewPDU.SetRemoteAddress ( ACRNema );
	
	// Add all the Abstract Syntaxs we need

	Index = 0;
	while ( Index < ADDO.GetSize() )
		{
		vr = ADDO.Get ( Index ) -> GetVR(0x0008, 0x0016);
		if(!vr)
			{
			delete ADDO.Get ( Index );
			ADDO.RemoveAt ( Index );
			}
		else
			{
			SetUID ( iUID, vr );
			NewPDU.AddAbstractSyntax ( iUID );
			++Index;
			}
		}

        NewPDU.SetTimeOut(TCPIPTimeOut);

	if (!NewPDU.Connect (IP, lPort))
		{
		CMoveRSP :: Write ( PDU, DCO, 0xc005 , 0, 0, 0, 0, NULL );
		OperatorConsole.printf("Host '%s' did not accept the connection\n", ACRNema);
		while(ADDO.GetSize())//bcb, was leak if fail?
			{
			delete ADDO.Get ( 0 );
			ADDO.RemoveAt ( 0 );
			}
		return ( TRUE );
		}


	Index = 0;
	Failed = 0;
	Cancelled = FALSE;

	while ( Index < ADDO.GetSize() )
		{
		if (Cancelled)
			{
			++Failed;
			delete ADDO.Get(Index);
			++Index;
			continue;
			}
		else
			{
			if (PDU->Link.Poll()) 
			      {
			      OperatorConsole.printf("Recieved cancel request\n", ACRNema);
			      Cancelled = TRUE;
			      }
			}
		
		vr = ADDO.Get ( Index ) -> GetVR(0x0008, 0x0016);
		SetUID ( iUID, vr );

//		ContextID = NewPDU.GetPresentationContextID(iUID);
//		if ( !ContextID )

		if ( !NewPDU.IsAbstractSyntaxAccepted(iUID) )
			{
			++Failed;
			OperatorConsole.printf("Host '%s' will not accept image\n", ACRNema);
			// Remote end did not accept this UID
			}
		else
			{
			AcceptedCompress = NewPDU.GetAcceptedCompressionType(iUID);
			StripGroup2 = memicmp(AcceptedCompress, "as", 2)!=0 && memicmp(AcceptedCompress, "is", 2)!=0;

			if ( !RetrieveOn (ADDO.Get(Index), &iDDO, &SStorage, DCO, &ADDO, ExtraBytes))
				++Failed;
			else
				{
				// non NKI client
			        if (DCO==NULL)
					recompress(&iDDO, AcceptedCompress, "", StripGroup2, PDU);

				// NKI client has 2 vr's to control (re)compression
				// 9999,0600=MaxSupportedCompression (old, nki only)
				// 9999,0700=RequestedCompression (new, nki or jpeg)
			        else
					{
					char mode[16];
					int MaxCompression=4;
					char script[1024];
					script[0]=0;

					// compression from transfer syntax negotiation
					strcpy(mode, AcceptedCompress);

					// optional requested custom compression
					vr = DCO->GetVR(0x9999, 0x0700);
						if (vr)
						{ 
						strncpy(mode, (const char*)vr->Data, vr->Length);
						mode[vr->Length] = 0;
						}

					// optional requested custom script
					vr = DCO->GetVR(0x9999, 0x0900);
						if (vr)
						{ 
						strncpy(script, (const char*)vr->Data, vr->Length);
						script[vr->Length] = 0;
						}

					vr = DCO->GetVR(0x9999, 0x0600);
					if (vr && vr->Length)MaxCompression = vr->GetUINT();
					if (MaxCompression > 4) MaxCompression = 4;

					// limit nki compression to MaxCompression
					if ((mode[0]=='n' || mode[0]=='N') && (mode[1]!='j' && mode[1]!='J'))
						if (atoi(mode+1) > MaxCompression)
							mode[1] = MaxCompression + '0';

					recompress(&iDDO, mode, "", StripGroup2, PDU);

					if (script[0])
						CallImportConverterN(iDDO, -1, NULL, NULL, NULL, NULL, PDU, NULL, script);
					}

				if(!SStorage->Write(&NewPDU, iDDO, DCO->GetVR(0x0000, 0x0110), (unsigned char *)Calling))
					{
					//++Failed;
					// Remote end should accept this image.  if it did
					// not, then just bail out.  Probably means the
					// TCP/IP link has been dropped.
					Failed += (ADDO.GetSize() - Index);

					SystemDebug.printf("Retrieve: remote connection dropped after %d images, %d not sent\n", Index, Failed);

					/* LJ: This also happens when CqDicom has had 'enough'
					   e.g. when retrieving properties. It caused a small
					   leak
					*/
					status = 0xfe00;				// mvh 20020429: return cancel status
					delete iDDO;
					break;
					}
				delete iDDO;
				}
			}

		CMoveRSP :: Write ( PDU,
					DCO,
					0xff00, ADDO.GetSize() - Index - 1,
					(UINT16) Index+1, Failed, 0,			// mvh 20020429: added +1
					ADDO.Get ( Index ));


		delete ADDO.Get(Index);

		++Index;
		}


	CMoveRSP :: Write ( PDU, DCO, status, 0, (UINT16) Index, Failed, 0, NULL );	// mvh 20020429: replaced 0 by status

	// In case we broke out from above..

	while ( Index < ADDO.GetSize() )
		{
		delete ADDO.Get(Index);
		++Index;
		}

	
	return ( TRUE );
	}

BOOL	StandardRetrieveNKI	::	Write (
	PDU_Service		*PDU,
	DICOMDataObject		*DDO,
	BYTE			*ACRNema )
	{
	DICOMCommandObject	*DCO;
	DICOMDataObject		*RDDO;

	if ( ! PDU )
		return ( FALSE );

	if ( ! CMoveRQ :: Write ( PDU, DDO, ACRNema ) )
		return ( FALSE );

	CallBack ( NULL, DDO );

	DCO = new DICOMCommandObject;

	while ( PDU->Read ( DCO ) )
		{
		RDDO = new DICOMDataObject;

		if (! (CMoveRSP :: Read ( DCO, PDU, RDDO) ) )
			{
			return ( FALSE );
			}
		if ( DCO->GetUINT16(0x0000, 0x0800) == 0x0101)
			{
			CallBack ( DCO, NULL );
			delete RDDO;
			if ( DCO->GetUINT16(0x0000, 0x0900) != 0x0000)
				{
				VR *vr;
				while ((vr = DCO->Pop()))
					{
					delete vr;
					}
				delete DCO;
				return ( FALSE );
				}
			delete DCO;
			return ( TRUE );
			}
		CallBack ( DCO, RDDO );
		delete RDDO;
		delete DCO;
		DCO = new DICOMCommandObject;
		}

	delete DCO;
	return ( FALSE );
	}

BOOL	PatientRootRetrieveNKI	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.826.0.1.3680043.2.135.1066.5.1.4.1.2.1.2" );
	return ( TRUE );
	}

BOOL	StudyRootRetrieveNKI	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.826.0.1.3680043.2.135.1066.5.1.4.1.2.2.2" );
	return ( TRUE );
	}

BOOL	PatientStudyOnlyRetrieveNKI	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.826.0.1.3680043.2.135.1066.5.1.4.1.2.3.2" );
	return ( TRUE );
	}

BOOL	PatientRootRetrieveGeneric	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.840.10008.5.1.4.1.2.1.2" );
	return ( TRUE );
	}

BOOL	StudyRootRetrieveGeneric	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.840.10008.5.1.4.1.2.2.2" );
	return ( TRUE );
	}

BOOL	PatientStudyOnlyRetrieveGeneric	::	GetUID ( UID &uid )
	{
	uid.Set ( "1.2.840.10008.5.1.4.1.2.3.2" );
	return ( TRUE );
	}

/************ NKI specific processing of a loaded image *************************/

typedef struct
{
  unsigned int iOrgSize;	/* NOTE: this is the number of short pixels !!!! */
  unsigned int iMode;
  unsigned int iCompressedSize;	/* in bytes, not pixels */
  unsigned int iOrgCRC;
  unsigned int iCompressedCRC;	/* Excluding this header */
} NKI_MODE2;


/* coder for NKI private compressed pixel data VR 0x7fdf,0x0010
   arguments: dest    = (in) points to area where compressed destination data is written (byte)
              src     = (in) points to uncompressed source data (short)
              npixels = (in) number of pixels to compress
              iMode   = (in) type of compression (1 .. 4)

   The return value is the number of bytes in the compressed data (maximal 3*npixels+10, typical 0.52*npixels)

   if iMode == 1 then
   - The first 4 bytes contain the number of short-int pixels
   - The following 4 bytes contain iMode=1
   - The rest is the compressed image

   if iMode == 2 then
   - The first 4 bytes contain the number of short-int pixels
   - The following 4 bytes contain iMode=2
   - The following 4 bytes contain the size of the compressed image (in bytes)
   - The following 4 bytes contain the CRC of the original image
   - The following 4 bytes contain the CRC of the compressed image
   - The rest is the compressed image
   - The compressed size will be even (padded by a zero if necessary).

   if iMode == 3 then
   - The first 4 bytes contain the number of short-int pixels
   - The following 4 bytes contain iMode=3
   - The rest is the compressed image, including 4 bit differences

   if iMode == 4 then
   - The first 4 bytes contain the number of short-int pixels
   - The following 4 bytes contain iMode=4
   - The following 4 bytes contain the size of the compressed image (in bytes)
   - The following 4 bytes contain the CRC of the original image
   - The following 4 bytes contain 0
   - The rest is the compressed image, including 4 bit differences
   - The compressed size will be even (padded by a zero if necessary).
*/

// optimized settings for the 4 bit run compressor (mode 3 and 4)

#define MINZEROS 5		// shortest RLE (2 byte overhead, but breaks 4bit run)
#define MIN4BIT  6		// shortest 4 bit run (6 bytes compressed to 5 bytes)

// This internal routine converts an 8 bit difference string into a 4 bit one
static signed char *recompress4bit(int n, signed char *dest)
{ signed char *p, *q;
  int val;

  n = n & 0xfe;
  dest -= n;
  p = dest;
  val = (((int)p[0])<<4) | (p[1]&15);
  p += 2;
  *dest++ = 0xc0;
  *dest++ = n;
  q = dest++;
  n -= 2;
  while(n>0)
  { *dest++ = (((int)p[0])<<4) | (p[1]&15);
    p += 2;
    n -= 2;
  }
  q[0] = val;

  return dest;
}

int nki_private_compress(signed char  *dest, short int  *src, int npixels, int iMode)
{ unsigned int		iCRC;
  unsigned int		iCRC2;
  register int		val, i, j;
  NKI_MODE2*		pHeader = (NKI_MODE2*)dest;

  NKIPrivateCompress++;

  /* Up till now only Mode=1 .. 4 are supported */
  if ((iMode < 1) || (iMode > 4))
    return 0;

  /* Create the header */
  pHeader->iOrgSize = npixels;
  pHeader->iMode = iMode;
  switch (iMode)
  { case 1:
      dest += 8;
      break;
    case 2:
      dest += sizeof(NKI_MODE2);
      break;
    case 3:
      dest += 8;
      break;
    case 4:
      dest += sizeof(NKI_MODE2);
      break;
  }

  /* Create the compressed image */

  if (iMode == 1)
  { *(short int *)dest = *src; 
    dest+=2;

    npixels--;

    do
    { val = src[1] - src[0];
      src++;
  
      if (val == 0)                            /* run length-encode zero differences */
      { for (i=2;; i++)
        { if (i>=npixels || src[i-1]!=src[-1] || i==256)
          { if (i==2) 
              *dest++=0;
            else      
            { *dest++  =  0x80;
              *dest++  = (i-1);
              npixels -= (i-2);
              src     += (i-2);
            }
            break;
          }
        }
      }    
      else if (val >= -64 && val <= 63)         /* small difference coded as one byte */
      { *dest = val;
        dest++;
      }
      else if (val >= -0x3F00 && val <= 0x3EFF) /* large differences coded as two bytes */
      { dest[0] = (val>>8) ^ 0x40;
        dest[1] = val;
        dest+=2;
      }
      else                                      /* if very large differences code abs val as three bytes */
      { *dest++ = 0x7F;
        *dest++ = src[0]>>8; 
        *dest++ = src[0];
      }
    }
    while (--npixels);
  }

  else if (iMode == 2)
  { iCRC  = 0;
    iCRC2 = 0;

    *(short int *)dest = val = *src; 
    iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char) val    ] ^ ((iCRC2 >> 8));
    iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
    iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) val    ] ^ ((iCRC  >> 8));
    iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(val>>8)] ^ ((iCRC  >> 8));
    dest+=2;
    npixels--;

    do
    { val = src[1] - src[0];
      src++;
      iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) src[0]    ] ^ ((iCRC  >> 8));
      iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(src[0]>>8)] ^ ((iCRC  >> 8));

      if (val == 0)                            /* run length-encode zero differences */
      { for (i=2;; i++)
        { if (i>=npixels || src[i-1]!=src[-1] || i==256)
          { if (i==2) 
            { *dest++=0;
              iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ 0    ] ^ ((iCRC2 >> 8));
            }
            else      
            { *dest++  =  0x80;
              iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ 0x80 ] ^ ((iCRC2 >> 8));
              *dest++  = (i-1);
              iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (i-1)] ^ ((iCRC2 >> 8));
              npixels -= (i-2);

              for (j=0; j<i-2; j++)
              { src++;
                iCRC = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) src[0]    ] ^ ((iCRC  >> 8));
                iCRC = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(src[0]>>8)] ^ ((iCRC  >> 8));
              }
            }
            break;
          }
        }
      }    
      else if (val >= -64 && val <= 63)         /* small difference coded as one byte */
      { *dest = val;
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val     ] ^ ((iCRC2 >> 8));
        dest++;
      }
      else if (val >= -0x3F00 && val <= 0x3EFF) /* large differences coded as two bytes */
      { dest[0] = (val>>8) ^ 0x40;
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)dest[0] ] ^ ((iCRC2 >> 8));
        dest[1] = val;
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val     ] ^ ((iCRC2 >> 8));
        dest+=2;
      }
      else                                      /* if very large differences code abs val as three bytes */
      { dest[0] = 0x7F;
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ 0x7f                   ] ^ ((iCRC2 >> 8));
	val     = src[0];
        dest[1] = val>>8; 
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
        dest[2] = val;
        iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val     ] ^ ((iCRC2 >> 8));
	dest+=3;
      }
    }
    while (--npixels);

    pHeader->iCompressedSize = dest - (signed char*)pHeader - sizeof(NKI_MODE2);

    /* Pad it to get an even length */
    if (pHeader->iCompressedSize & 1)
    { *dest++ = 0;
      iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ 0] ^ ((iCRC2 >> 8));
      pHeader->iCompressedSize++;
    }

    pHeader->iOrgCRC        = iCRC;
    pHeader->iCompressedCRC = iCRC2;
  }

  /* Create the compressed image - compressor with added 4 bit run */
  
  else if (iMode == 3)
  { int n4bit=0;
    *(short int *)dest = *src; 
    dest+=2;
    npixels--;

    do
    { val = src[1] - src[0];
      src++;
  
      if (val == 0)                            	/* run length-encode zero differences */
      { for (i=2;; i++)
        { if (i>=npixels || src[i-1]!=src[-1] || i==256)
          { if (i<=MINZEROS) 		       	/* too short run -> write zeros */
            { for (j=0; j<i-1; j++)
              { *dest++=0;
                n4bit++;

                if(n4bit>=254)			/* maximum length 4 bit run */
                { dest  = recompress4bit(n4bit, dest);
                  n4bit = 0;
                }
              }
            }
            else      
            { if (n4bit>=MIN4BIT)		/* end (and write) 4 bit run */
                dest  = recompress4bit(n4bit, dest);

              n4bit=0;
              *dest++  =  0x80;
              *dest++  = (i-1);
            }

            npixels -= (i-2);
            src     += (i-2);
            break;
          }
        }
      }    
      else if (val >= -63 && val <= 63)         /* small difference coded as one byte */
      { if (val >= -8 && val <= 7)
        { *dest++ = val;
          n4bit++;

          if(n4bit>=254)			/* maximum length 4 bit run */
          { dest  = recompress4bit(n4bit, dest);
            n4bit=0;
          }
        }
        else if(n4bit>=MIN4BIT)			/* end and write 4 bit run */
        { j = val;
          dest  = recompress4bit(n4bit, dest);
          n4bit=0;
          *dest++ = j;
        }
        else
        { *dest++ = val;			/* end 4 bit run */
           n4bit  = 0;
        }
      }
      else if (val >= -0x3F00 && val <= 0x3EFF) /* large differences coded as two bytes */
      { j = val;

        if(n4bit>=MIN4BIT)			/* end (and write) 4 bit run */
          dest  = recompress4bit(n4bit, dest);

        n4bit=0;
        dest[0] = (j>>8) ^ 0x40;
        dest[1] = j;
        dest+=2;
      }
      else                                      /* if very large differences code abs val as three bytes */
      { j = src[0];

        if(n4bit>=MIN4BIT)			/* end (and write) 4 bit run */
          dest  = recompress4bit(n4bit, dest);

        n4bit=0;
        *dest++ = 0x7F;
        *dest++ = j>>8; 
        *dest++ = j;
      }
    }
    while (--npixels);
  }

  /* Create the compressed image - compressor with added 4 bit run and CRC */
  
  else if (iMode == 4)
  { int n4bit=0;
    iCRC  = 0;
    
    *(short int *)dest = val = *src; 
    iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) val    ] ^ ((iCRC  >> 8));
    iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(val>>8)] ^ ((iCRC  >> 8));
    dest+=2;
    npixels--;

    do
    { val = src[1] - src[0];
      src++;
      iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) src[0]    ] ^ ((iCRC  >> 8));
      iCRC  = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(src[0]>>8)] ^ ((iCRC  >> 8));
  
      if (val == 0)                            	/* run length-encode zero differences */
      { for (i=2;; i++)
        { if (i>=npixels || src[i-1]!=src[-1] || i==256)
          { if (i<=MINZEROS) 		       	/* too short run -> write zeros */
            { for (j=0; j<i-1; j++)
              { *dest++=0;
                n4bit++;

                if(n4bit>=254)			/* maximum length 4 bit run */
                { dest  = recompress4bit(n4bit, dest);
                  n4bit = 0;
                }
              }
            }
            else      
            { if (n4bit>=MIN4BIT)		/* end (and write) 4 bit run */
                dest  = recompress4bit(n4bit, dest);

              n4bit=0;
              *dest++  =  0x80;
              *dest++  = (i-1);
            }

            npixels -= (i-2);
            for (j=0; j<i-2; j++)
            { src++;
              iCRC = CRC32_table[(unsigned char)iCRC  ^ (unsigned char) src[0]    ] ^ ((iCRC  >> 8));
              iCRC = CRC32_table[(unsigned char)iCRC  ^ (unsigned char)(src[0]>>8)] ^ ((iCRC  >> 8));
            }
            break;
          }
        }
      }    
      else if (val >= -63 && val <= 63)         /* small difference coded as one byte */
      { if (val >= -8 && val <= 7)
        { *dest++ = val;
          n4bit++;

          if(n4bit>=254)			/* maximum length 4 bit run */
          { dest  = recompress4bit(n4bit, dest);
            n4bit=0;
          }
        }
        else if(n4bit>=MIN4BIT)			/* end and write 4 bit run */
        { j = val;
          dest  = recompress4bit(n4bit, dest);
          n4bit=0;
          *dest++ = j;
        }
        else
        { *dest++ = val;			/* end 4 bit run */
           n4bit  = 0;
        }
      }
      else if (val >= -0x3F00 && val <= 0x3EFF) /* large differences coded as two bytes */
      { j = val;

        if(n4bit>=MIN4BIT)			/* end (and write) 4 bit run */
          dest  = recompress4bit(n4bit, dest);

        n4bit=0;
        dest[0] = (j>>8) ^ 0x40;
        dest[1] = j;
        dest+=2;
      }
      else                                      /* if very large differences code abs val as three bytes */
      { j = src[0];

        if(n4bit>=MIN4BIT)			/* end (and write) 4 bit run */
          dest  = recompress4bit(n4bit, dest);

        n4bit=0;
        *dest++ = 0x7F;
        *dest++ = j>>8; 
        *dest++ = j;
      }
    }
    while (--npixels);

    pHeader->iCompressedSize = dest - (signed char*)pHeader - sizeof(NKI_MODE2);

    /* Pad it to get an even length */
    if (pHeader->iCompressedSize & 1)
    { *dest++ = 0;
      pHeader->iCompressedSize++;
    }

    pHeader->iOrgCRC        = iCRC;
    pHeader->iCompressedCRC = 0;
  }

  return dest - (signed char*)pHeader;
}

int get_nki_private_decompressed_length(signed char *src)
{ int npixels = *(int *)src;
  return 2*npixels;
}

int get_nki_private_compress_mode(signed char *src)
{ int mode = *(int *)(src+4);
  return mode;
}

/* decoder for NKI private compressed pixel data - faster and safe version
   arguments: dest    = (in) points to area where destination data is written (short)
              src     = (in) points compressed source data (byte stream)
              size    = (in) number of bytes source data (safety)

   The return value is the number of pixels that have been processed.
 
   The compressed data looks like:
   (number of pixels)-1 times:
     OR 1 byte   = LL     7  bits signed (difference pixel[1] - pixel[0]);
     OR 2 bytes  = HHLL   15 bits signed (difference pixel[1] - pixel[0]) xored with 0x4000;
     OR 3 bytes  = 7FHHLL 16 bits absolute pixel data if 15 bits difference is exceeded
     OR 2 bytes  = 80NN   run length encode NN zero differences (max 255)
for mode 3 and 4 added:
     OR 2 bytes  = CONN   encode NN 4 bit differences (max 255)

   Performance on typical CT or MRI is >2x compression and a very good speed

   This code is not valid on HIGHENDIAN (high byte first) machines
*/

int nki_private_decompress(short int *dest, signed char *src, int size)
{ int			npixels, retvalue, mode, iMode, val, j;
  NKI_MODE2*		pHeader = (NKI_MODE2*)src;
  unsigned int		iCRC=0, iCRC2=0;
  signed char           *save, *end;

  NKIPrivateDecompress++;

  retvalue = npixels = pHeader->iOrgSize;
  iMode = pHeader->iMode;		// safety: this value is checked in case statement

  if (npixels<1) return 0;		// safety: check for invalid npixels value

  /* Up till now only Mode=1, 2, 3, and 4 are supported */

  switch (iMode)
  { case 1:
      src += 8;				// mode 1 only has 8 bytes header: iOrgSize and iMode
      end  = src + size - 3;		// for overflow check if we are close to end of input buffer
  
      *dest = *(short int *)src;
      src += 2;
      npixels--;

      do
      { if (src > end) 			// check whether the last few messages fit in input buffer
        { if (src<end+3) val = *src;
          else           val = 0;

          if (val >= -64 && val <= 63)      mode = 1;	// 7 bit difference
          else if (val==0x7f)		    mode = 3;	// 16 bit value
          else if ((val&0xff)==0x80)	    mode = 2;	// run length encoding
          else				    mode = 2;

          if (src+mode > end+3) 
            return 0;			// safety: overflow input data
        }
    
        val = *src;

        if (val >= -64 && val <= 63)	// 7 bit difference
        { dest[1] = dest[0] + val;
          dest++;
          src++;
        }
        else if (val==0x7f)		// 16 bit value
        { dest[1] = val = ((int)(((unsigned char *)src)[1])<<8) + ((unsigned char*)src)[2];
          dest++;
          src+=3;
        }
        else if ((val&0xff)==0x80)	// run length encoding
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          if (npixels<=0) return 0;	// safety: overflow output data
          do 
          { dest[1] = dest[0];
            dest++;
          }
          while (--mode);
          src+=2;
        }
        else
        { signed short diff = ((val^0x40)<<8) + (unsigned char)(src[1]);
          dest[1] = dest[0] + diff;	// 15 bit difference
          dest++;
          src+=2;
        }
      }
      while (--npixels);

      break;

    case 2:
      src += sizeof(NKI_MODE2);
      save = src;
      end  = src + pHeader->iCompressedSize - 3;

      if (end > src + size - 3) 
        end = src + size - 3;		// may occur if pHeader is corrupted

      *dest = val = *(short int *)src;
      iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
      iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
      src+=2;
    
      npixels--;
    
      do
      { if (src > end) 			// check whether the last few messages fit in input buffer
        { if (src<end+3) val = *src;
          else           val = 0;

          if (val >= -64 && val <= 63)      mode = 1;	// 7 bit difference
          else if (val==0x7f)		    mode = 3;	// 16 bit value
          else if ((val&0xff)==0x80)	    mode = 2;	// run length encoding
          else				    mode = 2;

          if (src+mode > end+3) 
            break;			// safety: overflow input data
        }

        val = *src;
    
        if (val >= -64 && val <= 63)	// 7 bits difference
        { dest[1] = val = dest[0] + val;
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src++;
        }
        else if (val==0x7f)		// 16 bit value
        { dest[1] = val = ((int)(((unsigned char *)src)[1])<<8) + ((unsigned char*)src)[2];
    
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src+=3;
        }
        else if ((val&0xff)==0x80)	// run length encoding
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          if (npixels<=0) break;	// safety: overflow output data
          do 
          { dest[1] = val = dest[0];
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
            dest++;
          }
          while (--mode);
          src+=2;
        }
        else
        { signed short diff = ((val^0x40)<<8) + ((unsigned char *)src)[1];
          dest[1] = val = dest[0] + diff;	// 15 bit difference
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src+=2;
        }
      }
      while (--npixels);
    
      if (iCRC2 != pHeader->iOrgCRC)	// if error in output CRC:
      { src = save;			// check input CRC
        while (src < end)
        { iCRC = CRC32_table[(unsigned char)iCRC ^ (unsigned char)src[0]] ^ ((iCRC >> 8));
          src++;
        }

        if (iCRC != pHeader->iCompressedCRC)
        { //OperatorConsole.printf("NKI decompression: the file is corrupted\n");
          retvalue=0;
        }
        else
        { //OperatorConsole.printf("NKI private decompression: internal error\n"); 
          retvalue=0; 
        }
      }

      break;

    case 3:
      src += 8;				// mode 3 only has 8 bytes header: iOrgSize and iMode
      end  = src + size - 3;		// for overflow check if we are close to end of input buffer
  
      *dest = *(short int *)src;
      src += 2;
      npixels--;

      do
      { if (src > end) 			// check whether the last few messages fit in input buffer
        { if (src<end+3) val = *src;
          else           val = 0;

          if (val >= -63 && val <= 63)      mode = 1;	// 7 bit difference
          else if (val==0x7f)		    mode = 3;	// 16 bit value
          else if ((val&0xff)==0x80)	    mode = 2;	// run length encoding
          else if ((val&0xff)==0xC0)	    mode = 2;	// 4 bit encoding
          else				    mode = 2;

          if (src+mode > end+3) 
            return 0;			// safety: overflow input data
        }
    
        val = *src;

        if (val >= -63 && val <= 63)	// 7 bit difference
        { dest[1] = dest[0] + val;
          dest++;
          src++;
        }
        else if (val==0x7f)		// 16 bit value
        { dest[1] = val = ((int)(((unsigned char *)src)[1])<<8) + ((unsigned char*)src)[2];
          dest++;
          src+=3;
        }
        else if ((val&0xff)==0x80)	// run length encoding
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          if (npixels<=0) return 0;	// safety: overflow output data
          do 
          { dest[1] = dest[0];
            dest++;
          }
          while (--mode);
          src+=2;
        }
        else if ((val&0xff)==0xC0)	// 4 bit run
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          mode/=2;
          src+=2;
          if (npixels<=0) return 0;	// safety: overflow output data
          do 
          { val = *src++;
            dest[1] = dest[0] + (val>>4);
            dest++;
            if (val&8) val |= 0xfffffff0; else val &= 0x0f;
            dest[1] = dest[0] + val;
            dest++;
          }
          while (--mode);
        }
        else
        { signed short diff = ((val^0x40)<<8) + (unsigned char)(src[1]);
          dest[1] = dest[0] + diff;	// 15 bit difference
          dest++;
          src+=2;
        }
      }
      while (--npixels);

      break;

    case 4:
      src += sizeof(NKI_MODE2);
      save = src;
      end  = src + pHeader->iCompressedSize - 3;
  
      if (end > src + size - 3) 
        end = src + size - 3;		// may occur if pHeader is corrupted

      *dest = val = *(short int *)src;
      iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
      iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
      src += 2;
      npixels--;

      do
      { if (src > end) 			// check whether the last few messages fit in input buffer
        { if (src<end+3) val = *src;
          else           val = 0;

          if (val >= -63 && val <= 63)      mode = 1;	// 7 bit difference
          else if (val==0x7f)		    mode = 3;	// 16 bit value
          else if ((val&0xff)==0x80)	    mode = 2;	// run length encoding
          else if ((val&0xff)==0xC0)	    mode = 2;	// 4 bit encoding
          else				    mode = 2;

          if (src+mode > end+3) 
            return 0;			// safety: overflow input data
        }
    
        val = *src;

        if (val >= -63 && val <= 63)	// 7 bit difference
        { dest[1] = val = dest[0] + val;
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src++;
        }
        else if (val==0x7f)		// 16 bit value
        { dest[1] = val = ((int)(((unsigned char *)src)[1])<<8) + ((unsigned char*)src)[2];
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src+=3;
        }
        else if ((val&0xff)==0x80)	// run length encoding
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          if (npixels<=0) return 0;	// safety: overflow output data
          do 
          { dest[1] = val = dest[0];
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
            dest++;
          }
          while (--mode);
          src+=2;
        }
        else if ((val&0xff)==0xC0)	// 4 bit run
        { mode = ((unsigned char *)src)[1];
          npixels -= mode-1;
          mode/=2;
          src+=2;
          if (npixels<=0) return 0;	// safety: overflow output data
          do 
          { val = *src++;
            dest[1] = j = dest[0] + (val>>4);
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)j] ^ ((iCRC2 >> 8));
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(j>>8)] ^ ((iCRC2 >> 8));
            dest++;
            if (val&8) val |= 0xfffffff0; else val &= 0x0f;
            dest[1] = j = dest[0] + val;
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)j] ^ ((iCRC2 >> 8));
            iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(j>>8)] ^ ((iCRC2 >> 8));
            dest++;
          }
          while (--mode);
        }
        else
        { signed short diff = ((val^0x40)<<8) + (unsigned char)(src[1]);
          dest[1] = val = dest[0] + diff;	// 15 bit difference
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)val] ^ ((iCRC2 >> 8));
          iCRC2 = CRC32_table[(unsigned char)iCRC2 ^ (unsigned char)(val>>8)] ^ ((iCRC2 >> 8));
          dest++;
          src+=2;
        }
      }
      while (--npixels);

      if (iCRC2 != pHeader->iOrgCRC)	// if error in output CRC:
       retvalue=0;

      break;

    default:
      //OperatorConsole.printf("NKI private decompression: unsupported mode\n"); 
      return 0;
  }

  return retvalue;
}

BOOL DecompressNKI(DICOMDataObject* pDDO)
{ VR*		pVR;
  VR*		pNewVR;
  signed char*	pCompressed;
  unsigned int	iDecompressedLength, iCompressedLength;

  pVR = pDDO->GetVR(0x7fdf, 0x0010);
  if (pVR)
  { /* Are the 'normal' pixel-data also present? If so, then 'our' tag is not
       made by us!
    */
    pNewVR = pDDO->GetVR(0x7fe0, 0x0010);
    if (pNewVR)
      return TRUE;

    /* Acuson and Elscint use this tag: test whether we or they made it */
    if ((pVR->Length > 6) &&
        ((strncmp((char*)pVR->Data, "ACUSON", 6) == 0) ||
         (strncmp((char*)pVR->Data, "ELSCIN", 6) == 0)))
      return TRUE;

    /* no data in our tag (always starts with 2 dwords): cannot be compresssed */
    if (pVR->Length<=8)
      return TRUE;

    /* check compression level: if invalid it cannot be our data */
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
    if (pVR->Length>8 && ((unsigned int*)pVR->Data)[1]>MAXNKICOMPRESSION)
#else //Big Endian like Apple power pc
    if (pVR->Length>8 && SwitchEndian(((unsigned int*)pVR->Data)[1])>MAXNKICOMPRESSION)
#endif
      return TRUE;

    /* Decompress it */
    pCompressed         = ((signed char *)(pVR->Data));
    if (!pCompressed)
      return FALSE;
    
    iCompressedLength   = pVR->Length;
    iDecompressedLength = get_nki_private_decompressed_length(pCompressed);
    if (!iDecompressedLength)
      return FALSE;

    pNewVR = new VR(0x7fe0, 0x0010, iDecompressedLength, TRUE);
    if (!pNewVR) 
      return FALSE;

    if (!nki_private_decompress((short *)(pNewVR->Data), pCompressed, iCompressedLength))
    { delete pNewVR;
      return FALSE;
    }

    /* Push the new VR, and delete the old one */
    pDDO->Push(pNewVR);
    pDDO->DeleteVR(pVR);
  }
  return TRUE;
}

BOOL CompressNKI(DICOMDataObject* pDDO, int CompressMode /* = 2 */)
{ VR*		pVR;
  VR*		pNewVR;
  signed char*	pCompressed;
  unsigned int	iCompressedLength;

  /* First check whether the image already contains 0x7fdf, 0x0010.
     If so, compression was already done, or 'our' VR is occupied.
     Also do not compress the 'ugly' variable-length sequence of pixeldata.
  */
  pVR = pDDO->GetVR(0x7fdf, 0x0010);
  if (pVR)
    return TRUE;

  /* Pixeldata present? */
  pVR = pDDO->GetVR(0x7fe0, 0x0010);
  if (pVR && (pVR->Length != 0xffffffff) && (pVR->Length != 0x0))
  { /* Compress it */
    pCompressed = (signed char*) malloc((pVR->Length/2) * 3 + 10);
    if (!pCompressed)
      return FALSE;

    iCompressedLength = nki_private_compress(pCompressed, (short int *)(pVR->Data), pVR->Length/2, CompressMode);
    if (iCompressedLength & 0x01)
      pCompressed[iCompressedLength++] = 0;

    /* Create  a new VR, and delete the old one */
    pNewVR = new VR(0x7fdf, 0x0010, iCompressedLength, pCompressed);
    pNewVR->TypeCode = pVR->TypeCode;
    pDDO->Push(pNewVR);
    pDDO->DeleteVR(pVR);
  }
  return TRUE;
}

/* Get a frame from a multi-frame object */

BOOL ExtractFrame(DICOMDataObject* pDDO, unsigned int Frame)
{// int		rc;
  unsigned int iNbFrames=1;
  VR		*pVR, *vrs;
  Array < DICOMDataObject *> *pADDO;

  iNbFrames = pDDO->Getatoi(0x0028, 0x0008);
  if (iNbFrames<=1 || Frame>=iNbFrames || Frame<0) return FALSE;

  DecompressNKI(pDDO);
  
  /* PixelData */
  pVR = pDDO->GetVR(0x7fe0, 0x0010);
  if (!pVR) return FALSE;

  pADDO = (Array<DICOMDataObject*>*)pVR->SQObjectArray;
  if (pADDO==NULL)
  { unsigned int size = pDDO->GetUINT(0x0028, 0x0010) * pDDO->GetUINT(0x0028, 0x0011) *
		pDDO->GetUINT(0x0028, 0x0002) * pDDO->GetUINT(0x0028, 0x0101) / 8; // Assumes 8 bits byte
    // note: uses bitstored instead of bitsallocated; no problem in practice

    if (size * iNbFrames > pVR->Length) return FALSE;
    
// repackage it crudeley but efficiently (the VR will be deleted shortly after anyway)
    memcpy(pVR->Data, ((BYTE *)pVR->Data) + size*Frame, size);
    pVR->Length = size;
  }
  else
  { if (Frame>=pADDO->GetSize()-1) return FALSE;
    Array < DICOMDataObject * > *SQE = new Array < DICOMDataObject * >;

    DICOMDataObject *D = MakeCopy(pADDO->Get(0));	// basic offset table
    SQE->Add(D);

    vrs = D->GetVR(0xfffe, 0xe000);    	// basic offset table (may be zero length)
    if (vrs->Length) vrs->Length = 4;  	// keep offset to first frame: will now be valid

    D = MakeCopy(pADDO->Get(Frame+1));	// selected frame
    SQE->Add(D);
					// repackage it
    pVR->Reset();// Say goodbye to old data.
    pVR->SQObjectArray = (void*) SQE;// Connect it to the new array.
    // No need to push, already in the dicom object
  }

  /* replace number of frames with 1 */
  pVR = pDDO->GetVR(0x0028, 0x0008);
  if (pVR)
  { pVR->ReAlloc(2);
    memcpy(pVR->Data, "1 ", 2);
  }

  return TRUE;
}

int GetNumberOfFrames(DICOMDataObject* pDDO)
{ int iNbFrames = pDDO->Getatoi(0x0028, 0x0008);
  return iNbFrames;
}

/* Crop frames from a multi-frame object */

BOOL ExtractFrames(DICOMDataObject* pDDO, unsigned int FirstFrame, unsigned int LastFrame, int skip)
{ //int		rc;
  unsigned int	iNbFrames=1, tFrames;
  VR		*pVR, *vrs;
  Array < DICOMDataObject *> *pADDO;

  iNbFrames = pDDO->Getatoi(0x0028, 0x0008);
  if (iNbFrames<=1 || FirstFrame>=iNbFrames || FirstFrame<0) return FALSE;
  if (LastFrame>=iNbFrames || LastFrame<0) LastFrame = iNbFrames-1;
  if (skip<1) skip = 1;
	
  tFrames = (LastFrame - FirstFrame + 1)/skip;// How many do we need?
  if (tFrames>iNbFrames) return FALSE;// More than we have?
  if (tFrames<1) tFrames=1;// Must do at least 1.

  int count=0;

  DecompressNKI(pDDO);

  /* PixelData */
  pVR = pDDO->GetVR(0x7fe0, 0x0010);
  if (!pVR) return FALSE;

  pADDO = (Array<DICOMDataObject*>*)pVR->SQObjectArray;
  if (pADDO==NULL)
  { unsigned int size = pDDO->GetUINT(0x0028, 0x0010) * pDDO->GetUINT(0x0028, 0x0011) *
	       pDDO->GetUINT(0x0028, 0x0002) * pDDO->GetUINT(0x0028, 0x0101) / 8;
    // note: uses bitstored instead of bitsallocated; no problem in practice

#if 1
  // repackage it crudeley but efficiently (the object will soon be sent and destroyed anyway)
    while (FirstFrame <= LastFrame)
    { if (size * FirstFrame > pVR->Length) return FALSE;
      memcpy(((BYTE *)pVR->Data) + count*size, ((BYTE *)pVR->Data) + FirstFrame*size, size);
      FirstFrame += skip;
      count ++;
    }
    pVR->Length = size * count;
#else
    pVR->Length = size * count;*/
    unsigned int tSize = tFrames * size; // How big in the end.
    if (tSize & 01) tSize++;// No odd data!
    if (!(nData = (BYTE *)malloc(tSize))) return FALSE;// our new correctly allocated memory.
    nData[tSize - 1] = 0;//Doesn't hurt.
    while (FirstFrame <= LastFrame)
    { if (size * FirstFrame > tSize)
      {
        free(nData);
        return FALSE;
      }
      memcpy( nData + (count * size), ((BYTE *)pVR->Data) + (FirstFrame * size), size);
      FirstFrame += skip;
      count ++;
    }
    pVR->Reset();// Say goodbye to old data.
    pVR->Data = (void*)nData;// Give it the new data.
    pVR->Length = size;// Tell it how long.
    pVR->ReleaseMemory = TRUE;// Make it responsible for it
#endif
  }
  else
  { if (FirstFrame>=pADDO->GetSize()-1) return FALSE;

    Array < DICOMDataObject * > *SQE = new Array < DICOMDataObject * >;

    DICOMDataObject *D = MakeCopy(pADDO->Get(0));	// basic offset table
    SQE->Add(D);

    vrs = D->GetVR(0xfffe, 0xe000);    	// basic offset table (may be zero length)
    if (vrs->Length) vrs->Length = 0;  	// lose offsets (easier)

    while (FirstFrame <= LastFrame)
    { if (FirstFrame>=pADDO->GetSize()-1) return FALSE;
      D = MakeCopy(pADDO->Get(FirstFrame+1));	// selected frame
      SQE->Add(D);
      FirstFrame += skip;
    }

    // repackage it
    pVR->Reset();// Say goodbye to old data.
    pVR->SQObjectArray = (void*) SQE;// Connect it to the new array.
    // No need to push, already in the dicom object

    count = SQE->GetSize()-1;
  }

// replace number of frames with new count.
  pVR = pDDO->GetVR(0x0028, 0x0008);
/* I have large number of frames, may not work > 99 frames in, < 10 out. bcb
  sprintf((char *)pVR->Data, "%d", count);// trailing 0 overwrite?
  if (((char *)pVR->Data)[pVR->Length-1]==0) ((char *)pVR->Data)[pVR->Length-1] = ' ';
  mvh bcb correct but replaced by something less ugly...
*/
  if (pVR)
  { char str[20];
    sprintf(str, "%d", count);
    pVR->ReAlloc(strlen(str));
    memcpy(pVR->Data, (BYTE *)str, pVR->Length);
    if (((char *)pVR->Data)[pVR->Length-1]==0) ((char *)pVR->Data)[pVR->Length-1] = ' ';
  }

  pVR = new VR(0x200d, 0x3016, 0, (void *)NULL, FALSE);
  if (pVR) pDDO->DeleteVR(pVR);			// (temp) remove philips private pixel data

  return TRUE;
}

/* Downsizing of pixeldata only when VR (0x9999, 0x0200) is present in the
   DicomCommandObject. when VR (0x9999, 0x0201) is present, a single frame is extracted
   NOTE: these VR's are NKI specific.
   Note: changing a VR length leaves some memory unused, but will be freed soon after anyway
*/

int MaybeDownsize(DICOMDataObject* pDDO, DICOMCommandObject* pDCO, int size)
{ int			i, j;
  VR			*pVR1=NULL, *pVR2=NULL;
  unsigned int		iMaxRowsColumns=0;
  unsigned short	iRows, iColumns, iNewRows, iNewColumns, iDownsizeFactor;
  char			s[256];
  char*			pSeparator;
  float			fSpacingX, fSpacingY;
  unsigned int		iImageSize, iNbBytesPerPixel, iNbPixels, iSkip;
  char*			pcSrc;
  char*			pcDest;
  short*		psSrc;
  short*		psDest;
  int*			piSrc;
  int*			piDest;

  if (pDCO)
  { pVR1 = pDCO->GetVR(0x9999, 0x0200);	/* MaxRowsColumns */
    pVR2 = pDCO->GetVR(0x9999, 0x0201);	/* Frame */
  }
  else
    iMaxRowsColumns = size;

  if (pVR1) iMaxRowsColumns = pVR1->GetUINT();

  if (pVR2) ExtractFrame(pDDO, pVR2->GetUINT());

  if (!iMaxRowsColumns)
    return TRUE;			/* Downsizing to zero doesn't make sense */

  /* NumberOfFrames */
  if(pDDO->Getatoi(0x0028, 0x0008) > 1) return FALSE;/* not implemented for multi-frame */

  /* OK. Now check whether all necessary PixelData-info is present in pDDO */
  iRows    = pDDO->GetUINT16(0x0028, 0x0010);
  iColumns = pDDO->GetUINT16(0x0028, 0x0011);
  iNbPixels = iRows * iColumns;

  if ((!iNbPixels) ||				/* Image must make sense */
      ((iRows <= iMaxRowsColumns) &&
       (iColumns <= iMaxRowsColumns)))		/* Image is already 'small' enough */
    return TRUE;

  DownSizeImage++;

  if (iRows >= iColumns)
  { iDownsizeFactor = iRows / iMaxRowsColumns;
    if (iRows % iMaxRowsColumns)
      iDownsizeFactor ++;
  }
  else
  { iDownsizeFactor = iColumns / iMaxRowsColumns;
    if (iColumns % iMaxRowsColumns)
      iDownsizeFactor ++;
  }

  pVR1 = pDDO->GetVR(0x0028, 0x0030);	/* Pixelspacing */
  if (!pVR1)
    return TRUE;
  strncpy(s, (const char*)pVR1->Data, pVR1->Length);
  s[pVR1->Length] = 0;
  fSpacingX = (float)(atof(s));
  pSeparator = strchr(s, '\\');
  if (pSeparator)
    fSpacingY = (float)(atof(pSeparator + 1));
  else
    fSpacingY = fSpacingX;
  
  if (!DecompressNKI(pDDO))		/* Pixeldata must first be decompressed */
    return FALSE;

  pVR1 = pDDO->GetVR(0x7fe0, 0x0010);	/* Pixeldata */
  if (!pVR1)
    return TRUE;
  iImageSize = pVR1->Length;
  if ((iImageSize < iNbPixels) ||
      (iImageSize % iNbPixels > 1))	/* allow 1 byte padding */
    return TRUE;			/* Image doesn't make sense */
  iNbBytesPerPixel = iImageSize / iNbPixels;
  if (iNbBytesPerPixel > 4)
    return TRUE;			/* Image is too beautiful to downsize! */

  /* LETS DO IT !
     The downsized image is stored in the same memory-block as the original one:
     Just be sure to adjust the length-indicator. The image will be (re)compressed anyway
     later on.
  */

  iNewRows    = iRows / iDownsizeFactor;
  if (!iNewRows)
    iNewRows++;
  iNewColumns = iColumns / iDownsizeFactor;
  if (!iNewColumns)
    iNewColumns++;
  switch (iNbBytesPerPixel)
  { case 1:
      pcSrc  = (char*)pVR1->Data;
      pcDest = pcSrc;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc;
	  pcSrc += iDownsizeFactor;
	}
	pcSrc = (char*)pVR1->Data + iDownsizeFactor * iColumns * (i + 1);
      }
      break;
    case 2:
      psSrc  = (short*)pVR1->Data;
      psDest = psSrc;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ *psDest++ = *psSrc;
	  psSrc += iDownsizeFactor;
	}
	psSrc = (short*)pVR1->Data + iDownsizeFactor * iColumns * (i + 1);
      }
      break;
    case 3:
      pcSrc  = (char*)pVR1->Data;
      pcDest = pcSrc;
      iSkip = (iDownsizeFactor - 1) * 3;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  pcSrc += iSkip;
	}
	pcSrc = (char*)pVR1->Data + iDownsizeFactor * 3 * iColumns * (i + 1);
      }
      break;
    case 4:
      piSrc  = (int*)pVR1->Data;
      piDest = piSrc;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ *piDest++ = *piSrc;
	  piSrc += iDownsizeFactor;
	}
	piSrc = (int*)pVR1->Data + iDownsizeFactor * iColumns * (i + 1);
      }
      break;
  }

  /* FINALLY: adjust Rows, Columns, Pixelspacing and (the length of) PixelData */
  pDDO->ChangeVR(0x0028, 0x0010, (UINT16)iNewRows, 'US');
  pDDO->ChangeVR(0x0028, 0x0011, (UINT16)iNewColumns, 'US');

  if (pSeparator)
    sprintf(s, "%g\\%g",  (iColumns*fSpacingY)/iNewColumns, (iRows*fSpacingX)/iNewRows);
  else
    sprintf(s, "%g", (iRows*fSpacingX)/iNewRows);
  pDDO->ChangeVR(0x0028, 0x0030, s, 'DS', TRUE);

  pVR1 = pDDO->GetVR(0x7fe0, 0x0010);	// Pixeldata
  pVR1->Length = iNewRows * iNewColumns * iNbBytesPerPixel;
  return 2;			// Downsizing actually occurred
}

/* Test if downsizing will occur */

static int TestDownsize(DICOMDataObject* pDDO, DICOMCommandObject* pDCO, int size)
{// VR*			pVR;
  unsigned int		iMaxRowsColumns;
  unsigned short	iRows, iColumns;
  int			iNbPixels;

  if (pDCO)
  { iMaxRowsColumns = pDCO->GetUINT(0x9999, 0x0200);

    if (!iMaxRowsColumns)
      return FALSE;			/* Downsizing to zero doesn't make sense */
  }
  else
    iMaxRowsColumns = size;

  /* OK. Now check whether all necessary PixelData-info is present in pDDO */
  iRows =  pDDO->GetUINT16(0x0028, 0x0010);

  iColumns = pDDO->GetUINT16(0x0028, 0x0011);

  iNbPixels = iRows * iColumns;

  if ((!iNbPixels) ||				/* Image must make sense */
      ((iRows <= iMaxRowsColumns) &&
       (iColumns <= iMaxRowsColumns)))		/* Image is already 'small' enough */
    return FALSE;

  return TRUE;				/* image would be downsized */
}

BOOL ProcessDDO(DICOMDataObject** pDDO, DICOMCommandObject* pDCO, ExtendedPDU_Service *PDU)
{ VR  *pVR;
  int dum;
  
  if (pDCO)				// nki clients
  { /* pDCO possibly contains specifications of how the NKI clients
       want the data the be sent/processed. Only downsize is 
       implemented for now.
    */

    pVR = pDCO->GetVR(0x9999, 0x0200);	// MaxRowsColumns
    if (pVR)
    { if (TestDownsize(*pDDO, pDCO, 0))
      { DecompressImage(pDDO, &dum);	// will also decompress JPEG images

        if (!MaybeDownsize(*pDDO, pDCO, 0))  // downsize
          return FALSE;
      }
    }
  }

  // De-compression is left to recompress in StandardRetrieveNKI::Read 
  // but run RetrieveResultConverter if present

  char dest[20];
  memset(dest, 0, 20);
  VR *vr;
  if (pDCO) 
  { vr = pDCO->GetVR(0x0000, 0x0600);
    if (vr) memcpy(dest, (char *)(vr->Data), vr->Length);
  }
  while (strlen(dest)>0 && dest[strlen(dest)-1]==' ') dest[strlen(dest)-1] = 0;

//  CallImportConverterN(*pDDO, 1300, NULL, dest, NULL, NULL, "calling", "called", NULL, NULL, VariableVRs);
  CallImportConverterN(*pDDO, 1300, NULL, dest, NULL, NULL, PDU, NULL, NULL);
  return TRUE;
}

/*************************************************************************************************/

static void RgbToMono(unsigned char* pSrc, unsigned char* pDest, int iNbPixels)
{ int	i;

  for (i=0; i<iNbPixels; i++)
    pDest[i] = (pSrc[3*i] + pSrc[3*i+1] + pSrc[3*i+2] + 1)/3;
}

static bool CropImage(unsigned char* pSrc, unsigned char* pDest,
	int iSizeX, int iSizeY, int iPixelSize,
	int iStartX, int iEndX, int iStartY, int iEndY)
{ int	i, iSize;

  if ((iStartX>=iSizeX) || (iEndX>=iSizeX) || (iStartX>iEndX) || (iStartX < 0))
    return false;
  if ((iStartY>=iSizeY) || (iEndX>=iSizeY) || (iStartX>iEndY) || (iStartY < 0))
    return false;

  pSrc  = pSrc + (iStartY*iSizeX + iStartX) * iPixelSize;
  iSize = (iEndX - iStartX + 1) * iPixelSize;
  for (i=iStartY; i<=iEndY; i++)
  { memmove(pDest, pSrc, iSize);
    pSrc  += iSizeX * iPixelSize;
    pDest += iSize;
  }
  return true;
}

#define UNDEFINED_FLOAT	0

void SetStringVR(VR **vr, int g, int e, const char *String);

int DcmConvertPixelData(DICOMDataObject*pDDO, bool bConvertToMono, bool	bCrop,
  			int iStartX, int iEndX, int iStartY, int iEndY,
  			float fPixelSizeX, float fPixelSizeY, float fPixelSizeZ)
{ int			i;
  VR*			pVR;
  char			s[100];
  int			iSizeX, iSizeY, iBitsAllocated;
  int			iNbSamplesPerPixel = 1, iNbFrames = 1;
  int			iSrcSliceSize, iDestSliceSize;
  char			*pSrc, *pDest, *pNextSrc;
  char*			pszGridFrameOffsetVector;

  /* Anything to do? */
  if ((bConvertToMono == false) && (bCrop == false))
    return FALSE;

  if (!pDDO)
    return FALSE;

  /* Get the slice-size */
  pVR = pDDO->GetVR(0x0028,0x0010);		// Rows
  if (pVR)
  { iSizeY = *((short*)pVR->Data);
    pVR = pDDO->GetVR(0x0028,0x0011);		// Columns
    if (pVR)
    { iSizeX = *((short*)pVR->Data);
      pVR = pDDO->GetVR(0x0028,0x0100);		// BitsAllocated
      if (pVR)
      { iBitsAllocated = *((short*)pVR->Data);
	pVR = pDDO->GetVR(0x0028,0x0002);	// SamplesPerPixel
	if (pVR)
	  iNbSamplesPerPixel = *((short*)pVR->Data);
      }
    }
  }
  if (!pVR)
  { return FALSE;
  }
  iSrcSliceSize = iDestSliceSize = iSizeX * iSizeY * iNbSamplesPerPixel * iBitsAllocated / 8;
  if (bCrop)
    iDestSliceSize = (iEndX - iStartX + 1) * (iEndY - iStartY + 1) * iNbSamplesPerPixel * iBitsAllocated / 8;
  if (bConvertToMono)
    iDestSliceSize /= 3;

  /* Check whether ConvertToMonochrome is possible */
  if (bConvertToMono)
  { if ((iNbSamplesPerPixel != 3) || (iBitsAllocated != 8))
    { return FALSE;
    }
    pVR = pDDO->GetVR(0x0028,0x0004);		// PhotometricInterpretation
    if (!pVR)
    { return FALSE;
    }
    if (strncmp((char*)pVR->Data, "RGB", 3) != 0)
    { return FALSE;
    }
    iNbSamplesPerPixel = 1;
  }

  /* Get the pixels */
  pVR = pDDO->GetVR(0x7fe0,0x0010);		// PixelData
  if (!pVR)
  { return FALSE;
  }
  pSrc = (char*)pVR->Data;

  /* Maybe more than one frame */
  pVR = pDDO->GetVR(0x0028,0x0008);		// NumberOfFrames
  if (pVR)
  { strncpy(s, (char*)pVR->Data, pVR->Length);
    s[pVR->Length] = 0;
    iNbFrames = atoi(s);
  }

  /* The main loop */
  pDest = pSrc;
  for (i=0; i<iNbFrames; i++)
  { pNextSrc = pSrc;

    if (bConvertToMono)
    { RgbToMono((unsigned char*)pNextSrc, (unsigned char*)pDest,
	iSizeX * iSizeY);
      pNextSrc = pDest;
    }

    if (bCrop)
    { if (!CropImage((unsigned char*)pNextSrc, (unsigned char*)pDest,
	iSizeX, iSizeY, iNbSamplesPerPixel * iBitsAllocated / 8,
	iStartX, iEndX, iStartY, iEndY))
      { return FALSE;
      }
      pNextSrc = pDest;
    }

    pSrc  += iSrcSliceSize;
    pDest += iDestSliceSize;
  }


  /* Fix the affected VRs */
  pVR = pDDO->GetVR(0x7fe0,0x0010);		// PixelData
  pVR->Length = iNbFrames * iDestSliceSize;
  if (pVR->Length & 0x01) pVR->Length ++;

  if (bCrop)
  { pVR = pDDO->GetVR(0x0028,0x0010);		// Rows
    *(short*)pVR->Data = (iEndY - iStartY + 1);
    pVR = pDDO->GetVR(0x0028,0x0011);		// Columns
    *(short*)pVR->Data = (iEndX - iStartX + 1);
  }

  if (bConvertToMono)
  { pVR = pDDO->GetVR(0x0028,0x0002);		// SamplesPerPixel
    *(short*)pVR->Data = 1;
    pVR = pDDO->GetVR(0x0028,0x0004);		// PhotometricInterpretation
    free(pVR->Data);
    pVR->Data = strdup("MONOCHROME2 ");
    pVR->Length = 12;
  }

  if ((fPixelSizeX != UNDEFINED_FLOAT) && (fPixelSizeY != UNDEFINED_FLOAT))
  { sprintf(s, "%f\\%f", fPixelSizeX, fPixelSizeY);
    // pVR = NewStringVR(0x0028,0x0030, s);	// PixelSpacing
    SetStringVR(&pVR, 0x0008, 0x0030, s); 
    if (pDDO->GetVR(0x0028,0x0030))
      pDDO->ReplaceVR(pVR);
    else
      pDDO->Push(pVR);
  }
  if ((fPixelSizeZ != UNDEFINED_FLOAT) && (iNbFrames > 1))
  { pszGridFrameOffsetVector = (char*)malloc(50000);
    strcpy(pszGridFrameOffsetVector, "0");
    for (i=1; i<iNbFrames; i++)
      sprintf(pszGridFrameOffsetVector + strlen(pszGridFrameOffsetVector), "\\%f", i*fPixelSizeZ);
    // pVR = NewStringVR(0x3004,0x000c, pszGridFrameOffsetVector);	// GridFrameOffsetVector
    SetStringVR(&pVR, 0x3004, 0x000c, pszGridFrameOffsetVector); 
    if (pDDO->GetVR(0x3004,0x000c))
      pDDO->ReplaceVR(pVR);
    else
      pDDO->Push(pVR);
  }

  return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// JPEG and NKI utility compression code
///////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>

// Runs external executable hidden
static BOOL ExecHidden(
	const char	*ProcessBinary,					// name of executable
	const char	*Arg1, const char *Arg2, const char *Arg3, const char *Arg4)	// arguments
	{
	PROCESS_INFORMATION	PINFO;
	STARTUPINFO		SINFO;
	SECURITY_ATTRIBUTES	SA;
	HANDLE			hMap;
	char			CommandLine[1024];

	memset((void*)&SINFO, 0, sizeof(STARTUPINFO));
	SINFO.cb = sizeof(STARTUPINFO);
	SINFO.wShowWindow = SW_HIDE;

	SA.nLength = sizeof (SECURITY_ATTRIBUTES);
	SA.lpSecurityDescriptor = NULL;

	sprintf(CommandLine, "%s %s \"%s\" \"%s\" %s", ProcessBinary, Arg1, Arg2, Arg3, Arg4);
	if(!CreateProcess(ProcessBinary, CommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL /* "DCMDICTPATH=offis.dic\0\0" */, NULL, &SINFO, &PINFO))
		{
		OperatorConsole.printf("***Failed to create process: %s - error %d\n", ProcessBinary, GetLastError());
		return ( FALSE );
		}
	else
		{
	  	WaitForSingleObject(PINFO.hProcess, INFINITE);
		CloseHandle(PINFO.hThread);
		CloseHandle(PINFO.hProcess);
		}

	return ( TRUE );
	}
#else

#ifndef DARWIN
#include <wait.h>
#endif //DARWIN

static BOOL ExecHidden(
	const char	*ProcessBinary,					// name of executable
	const char	*Arg1, const char *Arg2, const char *Arg3, const char *Env)	// arguments
	{
        char line[1024];
        sprintf(line, "export %s;%s %s \"%s\" \"%s\"", Env, ProcessBinary, Arg1, Arg2, Arg3);
        system(line);
        return TRUE;
	}
#endif

// Replaces PDU.SaveDICOMDataObject; automatically detects transfer syntax to use
void SaveDICOMDataObject(char *Filename, DICOMDataObject* pDDO)
	{
	int len, has_dcm_extension=0, UseChapter10=FALSE, bForcedImplicit=FALSE;
	VR *pVR;
	char s[256];
	PDU_Service PDU;

	PDU.AttachRTC(&VRType);

	len = strlen(Filename);
	if (len>3)
		has_dcm_extension = (stricmp(Filename+len-3, ".v2")!=0);

	/* Type of save depends on file name extension is .dcm (UseChapter10) 
	   and on the transfer syntax (not ImplicitLittleEndian, not
	   ExplicitLittleEndian and not ExplicitBigEndian)
	*/
	pVR = pDDO->GetVR(0x0002, 0x0010);	// TransferSyntaxUID
	if (pVR && pVR->Data)
		{
		strncpy(s, (char*)pVR->Data, pVR->Length);
		s[pVR->Length] = 0;
		if ((strcmp(s, "1.2.840.10008.1.2")   != 0) &&
		    (strcmp(s, "1.2.840.10008.1.2.1") != 0) &&
		    (strcmp(s, "1.2.840.10008.1.2.2") != 0))
			{
			if (!has_dcm_extension)
				{
				OperatorConsole.printf("Recompress: cannot rewrite jpeg/rle image in v2 format\n");
				Filename[0]=0;
				pDDO->Reset();
				return;
				}
			UseChapter10 = has_dcm_extension;
			}
		else
			{
			UseChapter10 = has_dcm_extension;
			//bForcedImplicit = TRUE; // 20040406
			}
		}
	else
		UseChapter10 = has_dcm_extension;

	if (!UseChapter10)
		PDU.SaveDICOMDataObject(Filename, ACRNEMA_VR_DUMP, pDDO);
	else if (bForcedImplicit)
	 	PDU.SaveDICOMDataObject(Filename, DICOM_CHAPTER_10_IMPLICIT, pDDO);
	else
	 	PDU.SaveDICOMDataObject(Filename, DICOM_CHAPTER_10_EXPLICIT, pDDO);
	}


/***********************************************************************************/
/*
   Code from CqGlobal.h		(CqDicom.dll)
*/
/***********************************************************************************/

#define DCM_E_OK				0
#define DCM_E_MEMORY				5
#define DCM_E_UNSUPPORTED_COMPRESSION		26
#define DCM_E_UNSUPPORTED_FORMAT		28

typedef struct
{
	char	szModality[16];
	char	szSeriesInstanceUID[256];
	float	fSpacingX;
	float	fSpacingY;
	int	iDimX;
	int	iDimY;
	int	iNbFrames;
	int	iNbTimeSequences;
	char	szPatientPosition[16];
	int	iDataSize;
	BOOL	bNkiCompressed;
	int	iPixelRepresentation;
	int	iBitsStored;
	float	fRescaleIntercept;
	float	fRescaleSlope;
	float	fDoseGridScaling;
	BOOL	bRtImagePosOK;
	float	fRtImagePosX;
	float	fRtImagePosY;
	char	szPhotometricInterpretation[20];
} SLICE_INFO;

SLICE_INFO*	getpSliceInfo(DICOMDataObject* pDDO)
{
	VR		*pVR;
	SLICE_INFO	*pSliceInfo;
	
	if(!(pSliceInfo = (SLICE_INFO*)malloc(sizeof(SLICE_INFO))))return NULL;
	memset(pSliceInfo, 0x00, sizeof(SLICE_INFO));
	
	// Rows
	pSliceInfo->iDimY = pDDO->GetUINT(0x0028, 0x0010);
	if(!pSliceInfo->iDimY)// Zero height.
	{
		free(pSliceInfo);
		return NULL;
	}
	// Columns
	pSliceInfo->iDimX = pDDO->GetUINT(0x0028, 0x0011);
	if(!pSliceInfo->iDimX)	// Zero width.
	{
		free(pSliceInfo);
		return NULL;
	}
	// BitsStored
	pSliceInfo->iBitsStored = pDDO->GetBYTE(0x0028, 0x0101);

	// NumberOfFrames
	pVR = pDDO->GetVR(0x0028, 0x0008);
	if (pVR && pVR->Length)
	{ 
		pSliceInfo->iNbFrames = pVR->Getatoi();
		pSliceInfo->iNbTimeSequences = 1;

		//  NumberOfSlices
		pVR = pDDO->GetVR(0x0054, 0x0081);
		if (pVR)
		{ /* Seems like a 3D time-sequence:
		   - Keep on using the iNbFrames member to designate the number of slices
		   - Use the iNbTimeSequences member for the number of volumes
		   */
			int iNbSlices, iNbVolumes;
			iNbSlices  = pVR->GetUINT();
			if (iNbSlices > 0)
			{ 	iNbVolumes = pSliceInfo->iNbFrames / iNbSlices;
				if (iNbVolumes * iNbSlices == pSliceInfo->iNbFrames)
				{ 
					pSliceInfo->iNbFrames = iNbSlices;
					pSliceInfo->iNbTimeSequences = iNbVolumes;
				}
			}
		}
	}
	// PhotometricInterpretation
	pVR = pDDO->GetVR(0x0028, 0x0004);
	if (pVR && pVR->Length && pVR->Data)
		strncpy(pSliceInfo->szPhotometricInterpretation,
			(char*)pVR->Data, pVR->Length<19 ? pVR->Length : 19);

	return pSliceInfo;
	
}

char * DePlane(char* data, int length)
{
	char *noPlane, *nPtr, *rPtr, *gPtr, *bPtr;

	if((noPlane = (char *) malloc(length)))
		{// Planes are 8 bit RGB (or should be).
		noPlane[length -1] = 0;// Never hurts, maybe an extra 0.
		length /= 3;// Each plane
		nPtr = noPlane;
		rPtr = data;
		gPtr = rPtr + length;
		bPtr = gPtr + length;
		for ( ;length > 0; length-- )
			{
			*nPtr++ = *rPtr++;
			*nPtr++ = *gPtr++;
			*nPtr++ = *bPtr++;
			}
		}
	return noPlane;// Memory error returns null.
}

void DeYBRFULL(char* data, int length)
{
	unsigned char *nPtr;
	int r, g, b;

	length /= 3; // each color
	nPtr = (unsigned char *)data;
	for ( ;length > 0; length-- )
		{

		r = nPtr[0]                           + 1.40200 * (nPtr[2]-128);
		g = nPtr[0] - 0.34414 * (nPtr[1]-128) - 0.71414 * (nPtr[2]-128);
		b = nPtr[0] + 1.77200 * (nPtr[1]-128);
		if (r>255) r=255;
		if (g>255) g=255;
		if (b>255) b=255;
		if (r<0) r=0;
		if (g<0) g=0;
		if (b<0) b=0;
		*nPtr++ = r;
		*nPtr++ = g;
		*nPtr++ = b;

/*		r = ((int)nPtr[0] * 128) + ((int)nPtr[2] * 179) - 22970;
		g = ((int)nPtr[0] * 128) - (44 * (int)nPtr[1]) - (91 * (int)nPtr[2]) - 17338;
		b = ((int)nPtr[0] * 128) + (277 * (int)nPtr[1]) - 29032;
		if(r & 0x8000) *nPtr++ = 0;
		else if(r & 0x4000) *nPtr++ = 255;
		else *nPtr++ = (r >> 6) & 0xFF;
		if(g & 0x8000) *nPtr++ = 0;
		else if(r & 0x4000) *nPtr++ = 255;
		else *nPtr++ = (g >> 6) & 0xFF;
		if(b & 0x8000) *nPtr++ = 0;
		else if(b & 0x4000) *nPtr++ = 255;
		else *nPtr++ = (b >> 6) & 0xFF;
*/
		}
}

static int DecompressRLE(SLICE_INFO* pSliceInfo, VR* pSequence,
			 void** ppResult, unsigned int * piResultSize)
{	int			rc = DCM_E_UNSUPPORTED_COMPRESSION;
    unsigned int    iFrameCnt, storedBitWidth, iDecompressedTotal;
	unsigned int	i, n, iNbRleSegments;
	Array<DICOMDataObject*>	*pADDO;
	DICOMDataObject*	pDDO;
	VR*			pVR;
	char			*pIn, *pOut, *outPtr, *endPtr, *pSeq, **hSeq, *cPtr, *endSeqPtr;
	int*			piHeader;
	unsigned int	iCompressedSize, iDecompressedSize, iNbCompressed, iNbDecompressed;
	char			cCurrent;
	char			*pR, *pG, *pB;
	bool			bIsRGB = false;

// Init stuff
	pOut = NULL;
    pSeq = NULL;
    endPtr = NULL;
    pG = NULL;
    pB = NULL;
    cPtr = NULL;
    iDecompressedSize = 0;
	iNbDecompressed = 0;
    *ppResult = NULL;
    *piResultSize = 0;
// Find out how big the output is.
    if(pSliceInfo->iBitsStored > 8) storedBitWidth = 2;
    else storedBitWidth = 1;
	iDecompressedTotal = pSliceInfo->iDimX * pSliceInfo->iDimY * storedBitWidth;
	if (pSliceInfo->iNbFrames)
		iDecompressedTotal *= pSliceInfo->iNbFrames;
	if (strncmp(pSliceInfo->szPhotometricInterpretation, "RGB", 3) == 0)
		bIsRGB = true;
// Of all color-representations, just support RGB for now.
	if (bIsRGB)
		iDecompressedTotal *= 3;
// Get the data.
    pADDO = (Array<DICOMDataObject*>*)pSequence->SQObjectArray;
// Frames can be RLE segments or sequences.
    for(iFrameCnt = 1; iFrameCnt < pADDO->GetSize(); iFrameCnt++)
    {
        pDDO = pADDO->Get(iFrameCnt);
        pVR  = pDDO->GetVR(0xfffe, 0xe000);
	
	/* The RLE data should start with 16 INT32 (Dicom chapter 5 annex G):
	 - 1st contains how many RLE segments there are (15 max)
	 - 2nd-16th contain offsets of each RLE segment
	 All non-used segments have offset 0 in this small table
	 Since this 16 INT32 header has a size of 64 bytes, the first offset should
	 be 64. All integers are stored in little-endian format.
	 */
	/* Check the header */
        if ((!pVR->Data) || (pVR->Length < 64))
        {
            if(pOut)free(pOut);
            return rc;
        }
        piHeader = (int*)pVR->Data;
#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian
        for(i=0; i<16; i++) piHeader[i] = SwitchEndian(piHeader[i]);
#endif
// How many segments, min 1, max of 15.
        iNbRleSegments = piHeader[0];
        if ((iNbRleSegments < 1) || (iNbRleSegments > 15))
        {
            if(pOut)free(pOut);
            return rc;
        }
// The first offset must be 64, the RLE header length.
        if (piHeader[1] != 64)
        {
            if(pOut)free(pOut);
            return rc;
        }
// Check all segments, each offset must be more than before.
	for (i=2; i<=iNbRleSegments; i++)
		if (piHeader[i] < piHeader[i-1])
        {
            if(pOut)free(pOut);
            return rc;
        }
// All unused segments are zero.
	for (i=iNbRleSegments + 1; i<=15; i++)
		if (piHeader[i] != 0)
        {
            if(pOut)free(pOut);
            return rc;
        }
// OK, it probably is RLE-compressed, time to make memory.
        if(!pOut) // Made already?
        {
            if(iDecompressedTotal & 1) iDecompressedTotal++;
            if(!(pOut = (char*)malloc(iDecompressedTotal)))
                return DCM_E_MEMORY;
            memset(pOut, 0xff, iDecompressedTotal);
            outPtr = pOut;
            endPtr = outPtr + iDecompressedTotal;
        }
        iNbCompressed   = 0;
        iCompressedSize = pVR->Length - 64;// Take out the header
        pIn = ((char*)piHeader) + 64;// Start of the data.
// Create a color buffer if needed.
        if (bIsRGB && storedBitWidth == 1 && iNbRleSegments == 3)
        {
            iDecompressedSize = pSliceInfo->iDimX * pSliceInfo->iDimY * storedBitWidth;
            if( outPtr + (iDecompressedTotal * 3) > endPtr) break; // Should fail?
            if(!(cPtr = (char*)malloc(iDecompressedTotal * 3)))
            {
                if(pOut)free(pOut);
                return DCM_E_MEMORY;
            }
            hSeq = &pR;// Make the handle's pointer valid.
            pR = cPtr;// Copy the pointer to the handle.
            pG = pR + iDecompressedSize;
            pB = pG + iDecompressedSize;
            endSeqPtr = pB + iDecompressedSize;
        }
        else
        {
         hSeq = &outPtr;// Give the pointer to the handle.
         endSeqPtr = endPtr;// End does not incrament.
        }
//	while (iNbDecompressed < iDecompressedSize)
        while (iNbCompressed < iCompressedSize)
        {
            cCurrent = pIn[iNbCompressed++];// Det the count.
            if (cCurrent >= 0)// Positive is a Literal Run.
            {// Check the length in & out?
                cCurrent++;// The real count
                if ((iNbCompressed + (int)cCurrent <= iCompressedSize) && 
                    (*hSeq + cCurrent <= endSeqPtr))
                    { // Good, room to copy
                        memcpy(*hSeq, pIn + iNbCompressed, cCurrent);
                        iNbCompressed   += cCurrent;
                        *hSeq += cCurrent;
                    }
                else // What happened, no room or seq ending 0?
                    break;// Run away!
            }
            else if (cCurrent == -128)break;// Just not allowed, may fail here.
            else// Replicate run.
            { n = ((int)-cCurrent) + 1;
                if (*hSeq + n > endPtr)// Enough room out?
                    break;
                for (i=0; i<n; i++)
                    *((*hSeq)++) = pIn[iNbCompressed];
                iNbCompressed++;
            }
        }
        if (bIsRGB && storedBitWidth == 1 && iNbRleSegments == 3)
        { /* Convert the R, G and B image planes to triplets */
            pR = cPtr;// Reset the red.
            for (i=0; i<iDecompressedSize; i++)// Already devided by 3
            {
                *outPtr++ = *pR++;
                *outPtr++ = *pG++;
                *outPtr++ = *pB++;
            }
            free(cPtr);
            cPtr = NULL;
        }
	}
    *ppResult = pOut;
    *piResultSize = iDecompressedTotal;
	return DCM_E_OK;
}

#if 0
static int DecompressRLE(SLICE_INFO* pSliceInfo, VR* pSequence,
			 void** ppResult, unsigned int * piResultSize)
{	int			rc = DCM_E_UNSUPPORTED_COMPRESSION;
	int			i, n, iNbRleSegments;
	Array<DICOMDataObject*>	*pADDO;
	DICOMDataObject*	pDDO;
	VR*			pVR;
	char			*pIn, *pOut;
	int*			piHeader;
	int			iCompressedSize, iDecompressedSize, iNbCompressed, iNbDecompressed;
	char			cCurrent;
	char			*pR, *pG, *pB;
	bool			bIsRGB = false;
	
	pADDO = (Array<DICOMDataObject*>*)pSequence->SQObjectArray;
	pDDO = pADDO->Get(1);
	pVR  = pDDO->GetVR(0xfffe, 0xe000);
	
	/* The RLE data should start with 16 INT32 (Dicom chapter 5 annex G):
	 - 1st contains how many RLE segments there are (15 max)
	 - 2nd-16th contain offsets of each RLE segment
	 All non-used segments have offset 0 in this small table
	 Since this 16 INT32 header has a size of 64 bytes, the first offset should
	 be 64. All integers are stored in little-endian format.
	 */
	/* Check the header */
	if ((!pVR->Data) || (pVR->Length < 64))
		return rc;

	piHeader = (int*)pVR->Data;
#if NATIVE_ENDIAN != LITTLE_ENDIAN //Big Endian
	for(i=0; i<16; i++) piHeader[i] = SwitchEndian(piHeader[i]);
#endif

	iNbRleSegments = piHeader[0];
	if ((iNbRleSegments < 1) || (iNbRleSegments > 15))
		return rc;

	if (piHeader[1] != 64)
			return rc;
	for (i=2; i<=iNbRleSegments; i++)
		if (piHeader[i] < piHeader[i-1])
			return rc;
	for (i=iNbRleSegments + 1; i<=15; i++)
		if (piHeader[i] != 0)
			return rc;
	
	/* OK, it probably is RLE-compressed */
	
	/* Find out how big the output is */
	iDecompressedSize = pSliceInfo->iDimX * pSliceInfo->iDimY *
	(pSliceInfo->iBitsStored / 8);
	if (pSliceInfo->iNbFrames)
		iDecompressedSize *= pSliceInfo->iNbFrames;
	if (strncmp(pSliceInfo->szPhotometricInterpretation, "RGB", 3) == 0)
		bIsRGB = true;
	/* Of all color-representations, just support RGB for now */
	
	if (bIsRGB)
		iDecompressedSize = iDecompressedSize * 3;
	pOut = (char*)malloc(iDecompressedSize);
	if (!pOut)
		return DCM_E_MEMORY;
	memset(pOut, 0xff, iDecompressedSize);
	
	iNbCompressed   = 0;
	iNbDecompressed = 0;
	iCompressedSize = pVR->Length - 64;
	pIn = ((char*)piHeader) + 64;
	while (iNbDecompressed < iDecompressedSize)
	{ cCurrent = pIn[iNbCompressed++];
		if (cCurrent >= 0)
		{ if ((iNbCompressed + ((int)cCurrent) + 1 <= iCompressedSize) &&
		      (iNbDecompressed + ((int)cCurrent) + 1 <= iDecompressedSize))
		{	memcpy(pOut + iNbDecompressed, pIn + iNbCompressed, ((int)cCurrent) + 1);
			iNbCompressed   += ((int)cCurrent) + 1;
			iNbDecompressed += ((int)cCurrent) + 1;
		}
		else
			break;
		}
		else if (cCurrent == -128)
			iNbCompressed = iNbCompressed;
		else
		{ n = ((int)-cCurrent) + 1;
			if (iNbDecompressed + n > iDecompressedSize)
				break;
			for (i=0; i<n; i++)
				pOut[iNbDecompressed + i] = pIn[iNbCompressed];
			iNbDecompressed += n;
			iNbCompressed++;
		}
	}
	
	if (bIsRGB)
	{ /* Convert the R, G and B image planes to triplets */
		pR = pOut;
		pOut = (char*)malloc(iDecompressedSize);
		if (!pOut)
		{ free(pR);
			return DCM_E_MEMORY;
		}
		pG = pR + iDecompressedSize / 3;
		pB = pG + iDecompressedSize / 3;
		for (i=0; i<iDecompressedSize / 3; i++)
		{ *pOut++ = pR[i];
			*pOut++ = pG[i];
			*pOut++ = pB[i];
		}
		pOut -= iDecompressedSize;
		free(pR);
	}
	
	
	rc = DCM_E_OK;
	
	if (rc == DCM_E_OK)
	{ *ppResult = pOut;
		*piResultSize = iDecompressedSize;
	}
	else
	{ *ppResult = NULL;
		*piResultSize = 0;
	}
	return rc;
}
#endif

// Make a palette color table for a segmented vr, don't forget to free it.
unsigned char * MakeSegTable(VR *pVR, unsigned int tableSize,unsigned int  *bitsWidth)
{
	unsigned char	*table, *table8, *table8Ptr, *inPtr, *endPtr, *tablePtr;
	unsigned int	cnt, cTableSize, step, sEnd, last;
	unsigned int	type, words;
	*bitsWidth = 1;
	
	cTableSize = tableSize * 2;// Ints.
	if(!(table = (unsigned char*)malloc(cTableSize)))
	{
		OperatorConsole.printf( "***[MakeSegTable]: Memory error.\n");
		return(NULL);
	}
	cnt = 0;
	inPtr = (unsigned char *)pVR->Data;
	endPtr = inPtr + pVR->Length;//Min type length.
	while(inPtr < endPtr)
	{
		type = *inPtr++;
		inPtr++;// To next int.
/*#if NATIVE_ENDIAN == LITTLE_ENDIAN
		words = ((UINT16*)pVR->Data)[pos];
#else*/
		words = *inPtr + (*(inPtr + 1) << 8);
		inPtr += 2;// Move char counter over to next int.
//#endif
//printf("%X ", cnt);
		if(cnt + (2 * words) > cTableSize)
		{//Overrun.
			free(table);
			OperatorConsole.printf(
				"***[MakeSegTable]: A count of %d + %d words would overrun %d of output memory.\n",
				cnt, 2 * words, cTableSize);
			return(NULL);
		}
		switch (type)
		{
			case 0://Discrete Segment Type
				if(inPtr + (2 * words) > endPtr)
				{//Overrun.
					free(table);
					OperatorConsole.printf(
					    "***[MakeSegTable]: %d words would overrun %d left of vr input.\n",
						2 * words, endPtr - inPtr);
					return(NULL);
				}
				for(;words > 0; words--)
				{
					table[cnt] = *inPtr++;
					if(table[cnt++] != *inPtr) *bitsWidth = 2;
					table[cnt++] = *inPtr++;
				}
				break;
			case 1://Linear Segment Type
				if(inPtr + 2 > endPtr)
				{//Overrun.
					free(table);
					OperatorConsole.printf(
						"***[MakeSegTable]: 1 word would overrun %d left of vr input.\n",
							       endPtr - inPtr);
				}
				if(cnt < 2)//Not allowed first.
				{
					free(table);
					OperatorConsole.printf( "***[MakeSegTable]: A Linear Segment can not be first.\n");
					return(NULL);
				}
				last = table[cnt - 2] + (table[cnt - 1] << 8);
				sEnd = *inPtr++;
				if(*inPtr != sEnd) *bitsWidth = 2;
				sEnd += ((*inPtr++) << 8);
				step = (sEnd - last)/ words;
				for(;words > 1; words--)
				{
					last += step;
					table[cnt++] = last & 0xFF;
					table[cnt++] = (last & 0xFF00) >> 8;
				}
				table[cnt++] = sEnd & 0xFF;
				table[cnt++] = (sEnd & 0xFF00) >> 8;
//				last = sEnd;
				break;
			case 2:// Indirect Sgment type
#if NATIVE_ENDIAN == LITTLE_ENDIAN
				sEnd = *((UINT*)inPtr);
#else
				sEnd = SwitchEndian(*((UINT*)inPtr));
#endif
				inPtr += 4;
				for(;words > 1; words--)
				{
					table[cnt++] = table[sEnd];
					table[cnt++] = table[sEnd];
				}
				break;
			default:
				OperatorConsole.printf( "***[MakeSegTable]: Opt code wrong or reserved type, %d.\n",type);
				return(NULL);//Opt code wrong or reserved!
				break;
		}
	}
	if(*bitsWidth == 1)
	{
		if(!(table8 = (unsigned char*)malloc(tableSize)))
		{
			free(table);
			OperatorConsole.printf( "***[MakeSegTable]: Memory error.\n");
			return(NULL);
		}
		tablePtr = table;
		table8Ptr = table8;
		for(cnt = 0; cnt < tableSize; cnt++)
		{
			*table8Ptr++ = *tablePtr++;
			tablePtr++;
		}
		return((unsigned char*)table8);
	}
	return((unsigned char*)table);
}

//Will turn any palette into Gray or RGB. The image Pixel Data (7FE0,0010) is decompressed.
bool DecodePalette(DICOMDataObject* pDDO)
{
	VR		*pVR, *vrImage;
	unsigned int	cmpts, inputArrayCnt, outSize, outLen, cnt, byteOffset, tableStep;
	unsigned int	tableSize, outBits, outBitw, allBitw, inBitw, offset, tableMin;
	unsigned char		*rTable, *gTable = NULL, *bTable = NULL, *outPtr, *outImage, *inPtr, *rPtr;
	bool		bSegmented, bLSBzero, bMSBzero;
	DICOMDataObject	*DDO;
	Array<DICOMDataObject *> *arrayImage;
// Init locals
	bSegmented =FALSE;
	inputArrayCnt = 0;
	byteOffset = 0;// Data in lsb.
	tableStep = 1;
	bLSBzero = TRUE;
	bMSBzero = TRUE;
	cmpts = 1;
// Check if its Palette Color
	pVR = pDDO->GetVR(0x0028, 0x0004);
	if(!pVR || pVR->Length != 14 || strncmp( (char *)pVR->Data, "PALETTE COLOR", 13))
	{
		OperatorConsole.printf("***[DecodePalette]: Not Palette Color.\n");
		return(FALSE);
	}
	
	// Check that is decompressed.
	pVR = pDDO->GetVR(0x0002, 0x0010);
	if(!pVR || pVR->Length > 20 || // Longer than 20 is some kind of jpeg or deflated.
	   (pVR->Length == 20 && ((char *)pVR->Data)[18] <= 32))// 1 & 2 are uncompressed LE & BE
	   return(FALSE);
// Check the samples per pixel.
	if(pDDO->GetBYTE(0x0028, 0x0002) != 1)
	{
		OperatorConsole.printf("***[DecodePalette]: Palette color cannot %d samples per pixel.\n",
				       pDDO->GetBYTE(0x0028, 0x0002));
		return(FALSE);
	}
	// If debug > 2, print info.
	if (DebugLevel > 2)
		SystemDebug.printf("Found Palette Color, depalatizing.\n");
// Look for palette stuff
	pVR = pDDO->GetVR(0x0028,0x1100); //The grayscale palette info..
	if(!pVR) pVR = pDDO->GetVR(0x0028,0x1101);//The red palette info..
	if(pVR && pVR->Length == 6)
	{
		tableSize = *(char *)pVR->Data + (((char *)pVR->Data)[1] << 8);
		tableMin = ((char *)pVR->Data)[2] + (((char *)pVR->Data)[3] << 8);
		outBits = ((char *)pVR->Data)[4];// 8 or 16 only allowed. Test?
	}
// Not palette color or Retired Large palette color. (Not supported here)
// I may add here code to fix the Photometric Interpretation.
// It would haxe to check 0x0002,0x0010 and 0x0028,0x0002 and guess.
	else
	{
		OperatorConsole.printf("***[DecodePalette]: No Palette information.\n", cmpts);
		return(FALSE);
	}
// Fix the table size.
	if(tableSize == 0)tableSize = 0x10000;// Fix the 2 byte table size.
// Count the colors.
	pVR = pDDO->GetVR(0x0028,0x1102);//The green palette info..
	if(pVR && pVR->Length == 6)cmpts++;// All are the same.
	pVR = pDDO->GetVR(0x0028,0x1103);//The blue palette info..
	if(pVR && pVR->Length == 6)cmpts++;
// Check for correct components.
	if (cmpts != 1 && cmpts != 3)
	{
		OperatorConsole.printf("***[DecodePalette]: %d components is not supported.\n", cmpts);
		return(FALSE);
	}
// If debug > 3, print info.
	if (DebugLevel > 3)
		SystemDebug.printf("Palette table size = %d, Minimum value = %d in %d bytes.\n",
			tableSize, tableMin, outBits);
// Lets look at the color palette.
	pVR = pDDO->GetVR(0x0028,0x1200); //The grayscale palette.
	if(!pVR) pVR = pDDO->GetVR(0x0028,0x1201);//The red palette.
	if(pVR && pVR->Length)
	{
		rTable = (unsigned char*)pVR->Data;
		if(pVR->TypeCode == 'OB' || outBits <= 8) outBitw = 1;//tableStep = 1.
		else 
		{
            tableStep = 2;
			if(tableSize == pVR->Length) outBitw = 2;
			else outBitw = 1;// tableSize * 2 == pVR->Length, will check later.
		}
// Check the table size.
		if(pVR->Length != tableSize * tableStep / outBitw)
		{
			OperatorConsole.printf(
				"***[DecodePalette]: Palette length should be %d, is %d, %d bits out.\n",
					       tableSize * outBits/8, pVR->Length, outBits);
			return(FALSE);
		}
// Get the  other colors.
		if(cmpts == 3)
		{
			pVR = pDDO->GetVR(0x0028,0x1202);//The green palette.
			if(!pVR || pVR->Length != tableSize * tableStep / outBitw)
			{
				OperatorConsole.printf(
					"***[DecodePalette]: Green palette length is %d, should be %d.\n",
					pVR->Length, tableSize * outBits/8);
				return(FALSE);
			}
			gTable = (unsigned char*)pVR->Data;
			pVR = pDDO->GetVR(0x0028,0x1203);//The blue palette.
			if(!pVR || pVR->Length != tableSize * tableStep / outBitw)
			{
				OperatorConsole.printf(
							"***[DecodePalette]: Blue palette length is %d, should be %d.\n",
							pVR->Length, tableSize * outBits/8);
				return(FALSE);
			}
			bTable = (unsigned char*)pVR->Data;
		}
// If debug > 3, print info.
		if (DebugLevel > 3)
			SystemDebug.printf("%d components in standard palette(s).\n",cmpts);
	}
	else //No gray or red table.
	{// Segmented look up table.
		pVR = pDDO->GetVR(0x0028,0x1220);//The gray segmented palette info..
		if(!pVR )pVR = pDDO->GetVR(0x0028,0x1221);//The red segmented palette info..
		if(!pVR || !pVR->Length)
		{
			OperatorConsole.printf("***[DecodePalette]: No palettes were found\n");
			return(FALSE);
		}
		if(!(rTable = MakeSegTable(pVR, tableSize, &outBitw)))return(FALSE);
		bSegmented = TRUE;
		allBitw = outBitw;
		if( cmpts == 3 )
		{
			if(!(pVR = pDDO->GetVR(0x0028,0x1222)) || !pVR->Length ||
			   !(gTable = MakeSegTable(pVR, tableSize, &outBitw)))
			{
				free(rTable);
				OperatorConsole.printf("***[DecodePalette]: Green palette was not found\n");
				return(FALSE);
			}
			if (allBitw != outBitw)
			{
				free(rTable);
				OperatorConsole.printf(
					"***[DecodePalette]: Green palette bit width does't match the red.\n");
				free(rTable);
				if(gTable)free(gTable);
				return(FALSE);
			}
			if(!(pVR = pDDO->GetVR(0x0028,0x1223)) || !pVR->Length ||
			   !(bTable = MakeSegTable(pVR, tableSize, &outBitw)))
			{
				OperatorConsole.printf("***[DecodePalette]: Blue palette was not found\n");
				return(FALSE);
				free(rTable);
				free(gTable);
				if(bTable)free(bTable);
			}
			if (allBitw != outBitw)
			{
				free(rTable);
				free(gTable);
				free(bTable);
				OperatorConsole.printf(
					"***[DecodePalette]: Blue palettes bit width does't match the red.\n");
				return(FALSE);
			}
		}
		tableStep = outBitw;
// If debug > 3, print info.
		if (DebugLevel > 3)
			SystemDebug.printf("%d components in segmented palette(s).\n",cmpts);
	}
// Look for 8 in 16 with zeros in one byte.
	if(tableStep == 2)
	{
        rPtr = rTable;
		for(cnt = 0; cnt < pVR->Length; cnt += 2)
		{// Look for all zeros
			if(*rPtr++ != 0)bLSBzero = FALSE;
			if(*rPtr++ != 0)bMSBzero = FALSE;
		}
        
		if(bMSBzero == TRUE)
		{
			
			if(bLSBzero == TRUE)
			{
				OperatorConsole.printf("***[DecodePalette]: The whole table is zero.\n");
				if(bSegmented == TRUE)
				{
					free(rTable);
					if(gTable)free(gTable);
					if(bTable)free(bTable);
				}
				return (FALSE);
			}
			byteOffset = 0;//LSB has the data
			outBitw = 1;
		}
		if(bLSBzero == TRUE)
		{
			byteOffset = 1;//MSB has the data
			outBitw = 1;
		}
	}
// Get the input data size.
	if(!(inBitw = pDDO->GetBYTE(0x0028, 0x0101)))inBitw = 8;
	if(inBitw > 8)inBitw = 2;
	else inBitw = 1;
// If debug > 3, print info.
	if (DebugLevel > 3)
	{
		if(outBitw == 2) SystemDebug.printf("Output data is words from \n");
		else
		{
			SystemDebug.printf("Output data is bytes in the \n");
			if(byteOffset == 0)SystemDebug.printf("LSB from \n");
			else SystemDebug.printf("MSB from \n");
		}
		if(inBitw == 1)SystemDebug.printf("8 bits in.\n");
		else SystemDebug.printf("16 bits in.\n");
	}
	// Now for the image data.
	pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
	vrImage = pVR;//Should be done here.
	if(pVR && pVR->Length)
	{
		if(pVR->SQObjectArray)
		{// Can be here for frames.
			arrayImage = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
			while (inputArrayCnt < arrayImage->GetSize())
			{
				DDO = arrayImage->Get(inputArrayCnt++);//Get the array.
				vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
				if(vrImage && vrImage->Length >= 0x10) break;
			}
			if(inputArrayCnt == arrayImage->GetSize())
			{
				OperatorConsole.printf("***[DecodePalette]: Could not find the image data.\n");
				if(bSegmented == TRUE)
				{
					free(rTable);
					if(gTable)free(gTable);
					if(bTable)free(bTable);
				}
				return (FALSE);
			}
		}
	}
// Set the output size
	outLen = outSize = vrImage->Length * cmpts * outBitw;
	inPtr = (unsigned char*)vrImage->Data;
	if(outLen & 1)outLen++;
	if(!(outImage = (unsigned char*)malloc(outLen)))
	{
		OperatorConsole.printf("***[DecodePalette]: Could not allocate %d bytes.\n", outLen);
		if(bSegmented == TRUE)
		{
			free(rTable);
			if(gTable)free(gTable);
			if(bTable)free(bTable);
		}
		return (FALSE);
	}
// Copy the data.
	outPtr = outImage;
//	cmpts--;// Make cmpts into a bool.
	for(cnt = 0; cnt < vrImage->Length; cnt++)
	{
		offset = *inPtr++;// Get the LSB or byte value.
		if(inBitw == 2)
		{
			offset += (*inPtr++ << 8);// Add the MSB if there.
			cnt++;
		}
		if(offset < tableMin) offset = 0;
		else offset -= tableMin;
		if( offset >= tableSize)offset = tableSize - 1;
		offset *= tableStep;// Double for words only.
		offset += byteOffset;// Off set for msb byte.
		*outPtr++ = rTable[offset];
		if(outBitw == 2)*outPtr++ = rTable[offset + 1];//Next value for words.
		if(cmpts == 3)
		{
			*outPtr++ = gTable[offset];
			if(outBitw == 2) *outPtr++ = gTable[offset + 1];//Next value for words.
			*outPtr++ = bTable[offset];
			if(outBitw == 2) *outPtr++ = bTable[offset + 1];//Next value for words.
		}
	}
// Done with the tables, free if ours.
    if(bSegmented == TRUE)
    {
        free(rTable);
        if(gTable)free(gTable);
        if(bTable)free(bTable);
    }
// Fix the last zero if needed.
	if(outSize & 1)outImage[outSize] = 0;
// Change the image data.
	vrImage->Reset(); // Deletes the pixel data
	vrImage->Length = outLen;
	vrImage->Data = outImage;
	if(outBitw == 2) vrImage->TypeCode = 'OW';
	else vrImage->TypeCode = 'OB';
	vrImage->ReleaseMemory = TRUE;//Give the memory to the vr.
// Fix the Photometric Interpretation and Samples per.
	if(cmpts == 1)pDDO->ChangeVR( 0x0028, 0x0004, "MONOCHROME2\0", 'CS');
	else
	{
		pDDO->ChangeVR( 0x0028, 0x0004, "RGB\0", 'CS');
		pDDO->ChangeVR( 0x0028, 0x0002, (UINT16)3, 'US');
	}
// Fix output widths (DecodePalette).
	if(outBitw == 2)
	{
		pDDO->ChangeVR( 0x0028, 0x0100, (BYTE)16, 'US');
		pDDO->ChangeVR( 0x0028, 0x0101, (BYTE)16, 'US');
		pDDO->ChangeVR( 0x0028, 0x0102, (BYTE)15, 'US');
	}
	else
	{
		pDDO->ChangeVR( 0x0028, 0x0100, (BYTE)8, 'US');
		pDDO->ChangeVR( 0x0028, 0x0101, (BYTE)8, 'US');
		pDDO->ChangeVR( 0x0028, 0x0102, (BYTE)7, 'US');
	}
// Delete the no longer needed palette vr's.
// Palette Color Lookup Table Descriptors
	if((pVR = pDDO->GetVR(0x0028,0x1100)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1101)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1102)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1103)) && pVR->Length)pDDO->DeleteVR(pVR);
// Palette Color Lookup Table UID
	if((pVR = pDDO->GetVR(0x0028,0x1199)) && pVR->Length)pDDO->DeleteVR(pVR);
// Regular palette tables
	if((pVR = pDDO->GetVR(0x0028,0x1200)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1201)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1202)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1203)) && pVR->Length)pDDO->DeleteVR(pVR);
// Segmented palette tables
	if((pVR = pDDO->GetVR(0x0028,0x1220)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1221)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1222)) && pVR->Length)pDDO->DeleteVR(pVR);
	if((pVR = pDDO->GetVR(0x0028,0x1223)) && pVR->Length)pDDO->DeleteVR(pVR);
	return(TRUE);
}

#ifndef NOINTJPEG
#ifndef HAVE_LIBJPEG //Not needed for the jpeg library

/***********************************************************************************/
/*
   Code from CqJPEG.cpp			(CqDicom.dll)
*/
/***********************************************************************************/

/* There was no way to incorporate following functions in one file */
extern int DecompressJPEG16(SLICE_INFO* pSliceInfo, VR* pSequence,
	void** ppResult, unsigned int * piResultSize);
extern int DecompressJPEG12(SLICE_INFO* pSliceInfo, VR* pSequence,
	void** ppResult, unsigned int * piResultSize);
extern int DecompressJPEG8(SLICE_INFO* pSliceInfo, VR* pSequence,
	void** ppResult, unsigned int * piResultSize);

/* Forward declaration of RLE decompressor */
static int DecompressRLE(SLICE_INFO* pSliceInfo, VR* pSequence,
	void** ppResult, unsigned int * piResultSize);


#define		Uint8	unsigned char
#define		Uint16	unsigned short
#define		Uint32	unsigned int


/* Following two functions are to find out which version of the ijg libraries
   to use in order to decompress.
*/
static Uint16 readUint16(const Uint8* pData)
{ return (((Uint16)(*pData) << 8) | ((Uint16)(*(pData+1))));
}

static Uint8 scanJpegDataForBitDepth(
  const Uint8 *data,
  const Uint32 fragmentLength)
{
  Uint32 offset = 0;
  while(offset+4 < fragmentLength)
  {
    switch(readUint16(data+offset))
    {
      case 0xffc0: // SOF_0: JPEG baseline
        return data[offset+4];
        /* break; */
      case 0xffc1: // SOF_1: JPEG extended sequential DCT
        return data[offset+4];
        /* break; */
      case 0xffc2: // SOF_2: JPEG progressive DCT
        return data[offset+4];
        /* break; */
      case 0xffc3 : // SOF_3: JPEG lossless sequential
        return data[offset+4];
        /* break; */
      case 0xffc5: // SOF_5: differential (hierarchical) extended sequential, Huffman
        return data[offset+4];
        /* break; */
      case 0xffc6: // SOF_6: differential (hierarchical) progressive, Huffman
        return data[offset+4];
        /* break; */
      case 0xffc7: // SOF_7: differential (hierarchical) lossless, Huffman
        return data[offset+4];
        /* break; */
      case 0xffc8: // Reserved for JPEG extentions
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffc9: // SOF_9: extended sequential, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffca: // SOF_10: progressive, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffcb: // SOF_11: lossless, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffcd: // SOF_13: differential (hierarchical) extended sequential, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffce: // SOF_14: differential (hierarchical) progressive, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffcf: // SOF_15: differential (hierarchical) lossless, arithmetic
        return data[offset+4];
        /* break; */
      case 0xffc4: // DHT
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffcc: // DAC
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffd0: // RST m
      case 0xffd1:
      case 0xffd2:
      case 0xffd3:
      case 0xffd4:
      case 0xffd5:
      case 0xffd6:
      case 0xffd7: 
        offset +=2;
        break;
      case 0xffd8: // SOI
        offset +=2;
        break;
      case 0xffd9: // EOI
        offset +=2;
        break;
      case 0xffda: // SOS
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffdb: // DQT
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffdc: // DNL
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffdd: // DRI
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffde: // DHP
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffdf: // EXP
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xffe0: // APPn
      case 0xffe1:
      case 0xffe2:
      case 0xffe3:
      case 0xffe4:
      case 0xffe5:
      case 0xffe6:
      case 0xffe7:
      case 0xffe8:
      case 0xffe9:
      case 0xffea:
      case 0xffeb:
      case 0xffec:
      case 0xffed:
      case 0xffee:
      case 0xffef: 
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xfff0: // JPGn
      case 0xfff1:
      case 0xfff2:
      case 0xfff3:
      case 0xfff4:
      case 0xfff5:
      case 0xfff6:
      case 0xfff7:
      case 0xfff8:
      case 0xfff9:
      case 0xfffa:
      case 0xfffb:
      case 0xfffc:
      case 0xfffd: 
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xfffe: // COM
        offset += readUint16(data+offset+2)+2;
        break;
      case 0xff01: // TEM
        break;
      default: 
        if ((data[offset]==0xff) && (data[offset+1]>2) && (data[offset+1] <= 0xbf)) // RES reserved markers
        { 
          offset += 2;
        }
        else return 0; // syntax error, stop parsing
        break;
    }
  } // while
  return 0; // no SOF marker found
}


/* This JPEG decompression function accepts a dicom VR with pixeldata-sequence,
   and replaces the sequence by a 'normal' VR.
   returns:
   - DCM_E_UNSUPPORTED_FORMAT when the sequence was not understood
   - DCM_E_UNSUPPORTED_COMPRESSION when the data are not supported by the ijg lib
   - DCM_E_MEMORY when out of memory
   - DCM_E_OK
*/
static int DecompressJPEG(SLICE_INFO* pSliceInfo, VR* pSequence)
{ int				rc = DCM_E_UNSUPPORTED_FORMAT;
  Array<DICOMDataObject*>*	pADDO;
  DICOMDataObject*		pDDO;
  VR*				pVR;
  int				iNbBitsPerSample;
  void*				pResult = NULL;
  unsigned int			iSize = 0;

  /* Is the dicom-sequence OK? */
  pADDO = (Array<DICOMDataObject*>*)pSequence->SQObjectArray;
  if (!pADDO)
    return rc;
  pDDO = pADDO->Get(1);
  if (!pDDO)
    return rc;
  pVR  = pDDO->GetVR(0xfffe, 0xe000);
  if (!pVR)
    return rc;
  if ((!pVR->Data) || (pVR->Length <= 0))
    return rc;

  /* Does ijg support the compression? */
  iNbBitsPerSample = scanJpegDataForBitDepth((unsigned char*)pVR->Data, pVR->Length);
  if ((iNbBitsPerSample <= 0) || (iNbBitsPerSample > 16))
  { /* It is not a supported JPEG image. Maybe it is RLE compressed */
    DecompressedRLE++;
    rc = DecompressRLE(pSliceInfo, pSequence, &pResult, &iSize);
    if (rc != DCM_E_OK)
      return rc;
  }
  else
  { /* Depending on iNbBitsPerSample, a different ijg libs/includes are used */
    DecompressJpeg++;

    if (iNbBitsPerSample > 12)
      rc = DecompressJPEG16(pSliceInfo, pSequence, &pResult, &iSize);
    else if (iNbBitsPerSample > 8)
      rc = DecompressJPEG12(pSliceInfo, pSequence, &pResult, &iSize);
    else
      rc = DecompressJPEG8(pSliceInfo, pSequence, &pResult, &iSize);
  }


  /* When OK, replace the VR */
  if (rc == DCM_E_OK)
  { /* TO DO: add consistency checks iSize <--> DicomTags */
    /* Cleanup the sequence, and make a normal VR */
//    delete[] pADDO;
//    pSequence->SQObjectArray = NULL;
    pSequence->Reset();
    pSequence->Data = pResult;
    pSequence->ReleaseMemory = TRUE;
    if (iSize & 0x01)
    { ((char*)pResult)[iSize] = 0;
      iSize++;
    }
    pSequence->Length = iSize;
  }

  return rc;
}

/***********************************************************************************/
/*
   JPEG decompression interface for dgate
*/
/***********************************************************************************/

static int dcmdjpeg(DICOMDataObject* pDDO)
{
  /* Functions above (from CqDicom.dll) will do the work.
     Here:
     - Get the necessary parameters from pDDO, and put them in SLICE_INFO structure
     - Adjust some dicom-tags
  */
  char		s[100];
  int		rc;
  VR		*pVR;
  SLICE_INFO	*pSliceInfo;

  rc = DCM_E_UNSUPPORTED_FORMAT;
  if(!(pSliceInfo = getpSliceInfo(pDDO))) return rc;
  if(pSliceInfo->iBitsStored == 0) pSliceInfo->iBitsStored = 16; // Default 16 bits

  /* PixelData */
  pVR = pDDO->GetVR(0x7fe0, 0x0010);

  if(pVR)rc = DecompressJPEG(pSliceInfo, pVR); // And RLE

  free(pSliceInfo);
  if (rc != DCM_E_OK)
    return rc;

  /* Some tags need to been changed */

  /*
     The Attribute Lossy Image Compression (0028,2110) conveys that the Image has undergone
     lossy compression. It provides a means to record that the Image has been compressed (at a
     point in its lifetime) with a lossy algorithm and changes have been introduced into the pixel data.
     Once the value has been set to '01', it shall not be reset.
     Note: If an image is compressed with a lossy algorithm, the attribute Lossy Image Compression
     (0028,2110) is set to '01'. Subsequently, if the image is decompressed and transferred in
     uncompressed format, this attribute value remains '01'.
  */

  /* It seems we only have to change the TransferSyntaxUID to LittleEndianExplicit */
  pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.1\0", 'IU');

  return rc;
}

#endif // #ifndef HAVE_LIBJPEG
#endif // #ifndef NOINTJPEG

/***********************************************************************************/
/*

*/
/***********************************************************************************/

// create tempory filename in printer_files directory for (de)compression

static void NewTempFileWExt(char *name, const char *ext)
	{
	int i;
	char name2[70], szTemp[256], szRootSC[256];

	MyGetPrivateProfileString(RootConfig, "MicroPACS", RootConfig, szRootSC, 64, ConfigFile);
  	MyGetPrivateProfileString(szRootSC, "TempDir", "", szTemp, 64, ConfigFile);

        if (szTemp[0]==0)
		{
		name[0]=0;
		GetPhysicalDevice("MAG0", name);
		strcat(name, "printer_files");
		}
	else
		strcpy(name, szTemp);

#ifndef WIN32
	mkdir(name, 0777);
#else
	mkdir(name);
#endif

	i = strlen(name);
	name[i]   = PATHSEPCHAR;
	name[i+1] = 0;

	GenUID(name2);
	strcat(name2, ext);

	strcat(name, name2);
	}

static void NewTempFile(char *name)
	{
	NewTempFileWExt(name, ".dcm");
	}

// Decompress JPEG or NKI coded image file
/*
BOOL
DecompressImageFile(char *file, int *Changed)
	{
	DICOMDataObject		*pDDO;
	PDU_Service		PDU;
//	char			name[1024];
//	VR			*pVR;
//	BOOL			nki, jpeg;
//	char			option[20];
//	int			len;

//	*Changed = 0;

	PDU.AttachRTC(&VRType);

	pDDO = PDU.LoadDICOMDataObject(file);
	if(!pDDO)
		{
		OperatorConsole.printf("***[DecompressImageFile] %s -FAILED: Error on Load\n", file);
		return FALSE;
		}
	if(!DecompressImage(&pDDO, Changed)) return FALSE;
	if(*Changed) SaveDICOMDataObject(file, pDDO);
	delete pDDO;
	return ( TRUE );
		
	}
*/

// Decompress NKI and/or JPEG coded image
BOOL
DecompressImage(DICOMDataObject **pDDO, int *Changed)
	{
	PDU_Service		PDU;
	char			name[1024], name2[1024];
	char			*noPlane;
	VR*			pVR;
	BOOL			nki, jpeg;
	int			rc;
	void*			pResult = NULL;
	unsigned int		iSize = 0;
	SLICE_INFO		*pSliceInfo = NULL;

	*Changed = 0;
	noPlane = NULL;

	PDU.AttachRTC(&VRType);

	// is it nki compressed ?
	nki = ((*pDDO)->GetVR(0x7fdf, 0x0010))!=NULL && ((*pDDO)->GetVR(0x7fe0, 0x0010))==NULL;

	// is it jpeg compressed ?
	pVR = (*pDDO)->GetVR(0x7fe0, 0x10);
	jpeg = (pVR && pVR->SQObjectArray);
#ifdef FUJI_FIX
	// Look for a Jfif header. (LittleEndianImplicit, jpeg compressed, how evil)
	if (!jpeg && pVR && ((unsigned char *)pVR->Data)[0] == 0xFF && ((unsigned char *)pVR->Data)[1] == 0xD8
		&& ((unsigned char*)pVR->Data)[2] == 0xFF && ((unsigned char *)pVR->Data)[3] == 0xE0
		&& ((char*)pVR->Data)[4] == 0x00 && ((char*)pVR->Data)[5] == 0x10
		&& strncmp(&((char *)pVR->Data)[6],"JFIF", 4) == 0)
	{
		jpeg = TRUE;
	}
#endif

	if(jpeg) // or RLE
	{
// distinguish RLE converted from jpeg without TrnSyntaxUID mvh 20110413
	        BOOL isrle = FALSE;
		Array < DICOMDataObject *> *pADDO;
		pVR = (*pDDO)->GetVR(0x7fe0, 0x0010);
		if (pVR && pVR->SQObjectArray)
			{
			pADDO = (Array<DICOMDataObject*>*)pVR->SQObjectArray;
			if (pADDO->GetSize() > 1)
				{
				pVR = pADDO->Get(1)->GetVR(0xfffe, 0xe000);
				if (pVR && pVR->Length>64)
					{
					int *piHeader = (int*)pVR->Data;
					int offs1;
#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian
        				offs1 = SwitchEndian(piHeader[1]);
#else
	        			offs1 = piHeader[1];
#endif
					isrle = offs1==64;
					}
				}
			}
// end distinguish RLE converted from jpeg without TrnSyntaxUID mvh 20110413

		pVR = (*pDDO)->GetVR(0x0002, 0x0010);
		if ((!pVR || (pVR->Length == 20 && ((char*)pVR->Data)[18] == '5')) && isrle) //RLE or no 0x0002, 0x0010
		{
			rc = DCM_E_UNSUPPORTED_FORMAT;

			if((pSliceInfo = getpSliceInfo(*pDDO)))
			{
				if(pSliceInfo->iBitsStored == 0)
					pSliceInfo->iBitsStored = 16; // Default 16 bits

				pVR = (*pDDO)->GetVR(0x7fe0, 0x0010);
				if(pVR) rc = DecompressRLE(pSliceInfo, pVR, &pResult, &iSize);
				free(pSliceInfo);
				if (rc == DCM_E_OK)// RLE decompressed
				{
					// Fix the image
					pVR->Reset();
					pVR->Data = pResult;
					pVR->ReleaseMemory = TRUE;
					if (iSize & 0x01)
					{
						((char*)pResult)[iSize] = 0;
						iSize++;
					}
					pVR->Length = iSize;
					if(!(pVR = (*pDDO)->GetVR(0x0002, 0x0010)))
					{
						pVR = new VR(0x0002, 0x0010, 0, (void *)NULL, FALSE);
						(*pDDO)->Push(pVR);
					}
					pVR->ReAlloc(20);
					memcpy((char *)pVR->Data, "1.2.840.10008.1.2.1\0",20);// LittleEndianExplict
					DecompressedRLE++;
					*Changed = 1;
					jpeg = FALSE;// Check for planes
				}
			}
		}
#ifdef HAVE_J2K // JPEG 2000 stuff
		else if(pVR && pVR->Length == 22 && ((char*)pVR->Data)[20] == '9')//90 or 91 is jpeg 2000.
		{
#ifndef HAVE_BOTH_J2KLIBS
#ifdef HAVE_LIBJASPER
			if(!DecompressJPEG2K(*pDDO))
#endif
#ifdef HAVE_LIBOPENJPEG
			if(!DecompressJPEG2Ko(*pDDO))
#endif
#else //HAVE_BOTH_J2KLIBS
			if(gUseOpenJpeg)
			{
				if(!DecompressJPEG2Ko(*pDDO))
				{
					OperatorConsole.printf("***[DecompressImage]:OpenJPEG failed to decompress JP2000\n");
					delete pDDO;
					return FALSE;
				}
			}
			else if(!DecompressJPEG2K(*pDDO))
#endif
			{
				OperatorConsole.printf("***[DecompressImage]: failed to decompress JP2000\n");
				delete pDDO;
				return ( FALSE );
			}
			DecompressJpeg2000++;
			*Changed = 1;
			return ( TRUE );
		}
#endif //End HAVE_J2K
	}

	if (nki && !jpeg)		// nki compressed
		{
		DecompressNKI(*pDDO);
                *Changed = 1;
		nki = FALSE; 		//Check for planes next
		}
	
	if (!nki && !jpeg) 		// not compressed
		{
		// Check if its Palette Color
		pVR = (*pDDO)->GetVR(0x0028, 0x0004);
		if(pVR && pVR->Length == 14 && strncmp( (char *)pVR->Data, "PALETTE COLOR", 13) == 0)
			{
			DecodePalette(*pDDO);
			DePaletted++;
			// palette is never planar; fix for colorzipped.tar test images
			(*pDDO)->ChangeVR( 0x0028, 0x0006, (UINT8)0, 'US');// Not any more.
			*Changed = 1;
			}

		//Planar check, done after RLE (& deflate?) decompression; only for RGB or YBR
		if((*pDDO)->GetBYTE(0x0028, 0x0006))
		  if((*pDDO)->GetBYTE(0x0028, 0x0002)==3)
			{
			pVR = (*pDDO)->GetVR(0x7fe0, 0x0010);
			if(pVR->Length) noPlane = DePlane((char *)pVR->Data, pVR->Length);
			if(noPlane)
				{
				free(pVR->Data);
				pVR->Data = noPlane;
				(*pDDO)->ChangeVR( 0x0028, 0x0006, (UINT8)0, 'US');// Not any more.
				DePlaned++;
				*Changed = 1;
				}
			}

		// Check if its YBR
		pVR = (*pDDO)->GetVR(0x0028, 0x0004);// Have from above
		if(pVR && pVR->Length == 8 && strncmp( (char *)pVR->Data, "YBR_FULL", 8) == 0)
			{
			pVR = (*pDDO)->GetVR(0x7fe0, 0x0010);
			if(pVR->Length) DeYBRFULL((char *)pVR->Data, pVR->Length);
			(*pDDO)->ChangeVR( 0x0028, 0x0004, "RGB\0", 'CS');
			DePaletted++;
			*Changed = 1;
			}

		return TRUE;
		}

        if(!UseBuiltInDecompressor())
		{
		NewTempFile(name);
		NewTempFile(name2);

		PDU.SaveDICOMDataObject(name, DICOM_CHAPTER_10_EXPLICIT, *pDDO);
		delete *pDDO;
		*pDDO=NULL;

#ifdef WIN32		
		if (!ExecHidden("dcmdjpeg.exe", "-F +ti", name, name2, ""))
#else
		if (!ExecHidden("dcmdjpeg", "-F +ti", name, name2, "DCMDICTPATH=dicom.dic\0"))
#endif
		
			{
			*pDDO = PDU.LoadDICOMDataObject(name);
			unlink(name);
			return FALSE;
			}

		*pDDO = PDU.LoadDICOMDataObject(name2);
		if(!*pDDO)
			{
			OperatorConsole.printf("***[DecompressImage]: Error on load after external decompression, image not decompressed\n");
			*pDDO = PDU.LoadDICOMDataObject(name);	// mvh 20060402: restore original object
			unlink(name);
			//return FALSE;
			return TRUE;
			}

		unlink(name);
		unlink(name2);
	        DecompressJpeg++;
		}
#ifndef NOINTJPEG
	else

#ifdef HAVE_LIBJPEG
	 	{
		if(!DecompressJPEGL(*pDDO))
            		{
			OperatorConsole.printf("***[DecompressImage]: JPEG library decompression error\n");
        	    	return(FALSE);
            		}
	        DecompressJpeg++;
		}
#else
		{
	        if (dcmdjpeg(*pDDO) != DCM_E_OK)
			{
			OperatorConsole.printf("***[DecompressImage]: JPEG decompression error\n");
			return FALSE;
			}
	        DecompressJpeg++;
		}
#endif //HAVE_LIBJPEG #else
#endif

        *Changed = 1;
	return ( TRUE );

	}

/*
// Compress NKI coded image (FileCompressMode must be in [0..4], 0=uncompressed)
BOOL
CompressNKIImageFile(char *file, int lFileCompressMode, int *ActualMode)
	{
	DICOMDataObject		*pDDO;
	PDU_Service		PDU;
	int			dum;

        *ActualMode = -1;

	PDU.AttachRTC(&VRType);

	pDDO = PDU.LoadDICOMDataObject(file);

	if(!pDDO)
		{
		OperatorConsole.printf("***[CompressNKIImageFile] %s -FAILED: Error on Load\n", file);
		return FALSE;
		}

	DecompressImage(&pDDO, &dum);	// make sure it is not NKI or JPEG compressed
        if (dum) *ActualMode = 0;

	if (lFileCompressMode>0 && lFileCompressMode<5)
		if (!CompressNKI(pDDO, lFileCompressMode))
			{ 
			OperatorConsole.printf("***[CompressNKIImageFile]: failed to compress DICOM object %s\n", file);
			delete pDDO;
	        	return FALSE;
			}
	 
	SaveDICOMDataObject(file, pDDO);

	delete pDDO;
        *ActualMode = lFileCompressMode;
	return ( TRUE );
}

// Downsize image (lFileCompressMode must be in ['1','2', '4','8', 'a', 'b', 'c'], '1' = to 1024)
BOOL
DownSizeImageFile(char *file, int lFileCompressMode, int *ActualMode)
	{
	DICOMDataObject		*pDDO;
	PDU_Service		PDU;
	int			dum, rc, size;

        *ActualMode = -1;

	PDU.AttachRTC(&VRType);

	switch(lFileCompressMode)
		{ 
		case '1': size = 1024; break;
		case '2': size =  512; break;
		case '4': size =  256; break;
		case '8': size =  128; break;
		case 'A': case 'a': size =  64; break;
		case 'B': case 'b': size =  32; break;
		case 'C': case 'c': size =  16; break;
                default : size =65536; break;
		}

	pDDO = PDU.LoadDICOMDataObject(file);

	if(!pDDO)
		{
		OperatorConsole.printf("***[CompressNKIImageFile] %s -FAILED: Error on Load\n", file);
		return FALSE;
		}

	if (TestDownsize(pDDO, NULL, size))
		{
		DecompressImage(&pDDO, &dum);	// make sure it is not NKI or JPEG compressed
        	if (dum) *ActualMode = 0;

	        rc = MaybeDownsize(pDDO, NULL, size);

		if (!rc)
			{ 
			OperatorConsole.printf("***[CompressNKIImageFile]: failed to downsize DICOM object %s\n", file);
			delete pDDO;
		       	return FALSE;
			}
	 
		SaveDICOMDataObject(file, pDDO);

		if (rc==2) *ActualMode = lFileCompressMode;
		}

	delete pDDO;
	return ( TRUE );
	}
*/

// Compress JPEG coded image file (lFileCompressMode must be in [0..6], 0=uncompressed)
/*
BOOL
CompressJPEGImageFile(char *file, int lFileCompressMode, int *ActualMode)
	{
	DICOMDataObject		*pDDO;
	PDU_Service		PDU;
	char			name[1024];
	int			dum, len, qual;
	VR*			pVR;

	len = strlen(file);
	if (len>3)
		if (stricmp(file+len-3, ".v2")==0)
			{
			OperatorConsole.printf("[CompressJPEGImageFile]: cannot compress v2 file\n");
			return FALSE;
			}

        *ActualMode = -1;

	if (lFileCompressMode=='0')
		{
		*ActualMode = '0';
		return DecompressImageFile(file, &dum);
		} 

	PDU.AttachRTC(&VRType);

	NewTempFile(name);

	pDDO = PDU.LoadDICOMDataObject(file);
	if(!pDDO)
		{
		OperatorConsole.printf("***[CompressJPEGImageFile] %s -FAILED: Error on Load\n", file);
		return FALSE;
		}

	pVR = pDDO->GetVR(0x0008, 0x0060);
	if (pVR) 
		{
			if (pVR->Length>=2 && (memcmp(pVR->Data, "PR", 2)==0 || 
                                               memcmp(pVR->Data, "SR", 2)==0 ||
                                               memcmp(pVR->Data, "RT", 2)==0))
			{
			OperatorConsole.printf("[CompressJPEGImageFile]: JPEG compression not allowed for PR/SR/RT\n");
			delete pDDO;
	        	return FALSE;
			}
		}
	
	if ((pDDO->GetVR(0x7fdf, 0x0010)) != NULL)
		if (!DecompressNKI(pDDO))
			{
			OperatorConsole.printf("***[CompressJPEGImageFile]: failed to NKI decompress DICOM object %s\n", file);
			delete pDDO;
	        	return FALSE;
			}

#ifdef HAVE_J2K
    	if (lFileCompressMode=='K' || lFileCompressMode=='k' || lFileCompressMode=='L' || lFileCompressMode=='l')
        	{
			if( lFileCompressMode=='L' || lFileCompressMode=='l')qual = 0;
			else qual = 100;
#ifndef HAVE_BOTH_J2KLIBS
#ifdef HAVE_LIBJASPER
			if(!CompressJPEG2K(pDDO,qual))
#endif
#ifdef HAVE_LIBOPENJPEG
			if(!CompressJPEG2Ko(pDDO,qual))
#endif
#else //HAVE_BOTH_J2KLIBS
			if(gUseOpenJpeg)
			{
				if(!CompressJPEG2Ko(pDDO,qual))
				{
					delete pDDO;
					return FALSE;
				}
			}
			else if(!CompressJPEG2K(pDDO,qual))
#endif
			{
				delete pDDO;
				return FALSE;
			}
        	PDU.SaveDICOMDataObject(file, DICOM_CHAPTER_10_IMPLICIT, pDDO);
        	*ActualMode = lFileCompressMode;
        	delete pDDO;
		CompressJpeg2000++;
        	return ( TRUE );
        	}
#else //HAVE_J2K
    	if (lFileCompressMode=='K' || lFileCompressMode=='k' || lFileCompressMode=='L' || lFileCompressMode=='l')
		{
		OperatorConsole.printf("***[CompressJPEGImageFile]: jpeg 2000 not supported\n");
        	return FALSE;
		}
#endif //HAVE_J2K

#ifdef HAVE_LIBJPEG
// Jpeg standard is lossy = 8 or 12 bits.
		if(lFileCompressMode > '2')//Lossy
        		{
        		int BitsAllocated = (pDDO)->GetBYTE(0x0028, 0x0100);
        		if(BitsAllocated > 12)
            			{
            			OperatorConsole.printf(
                		"Warn[CompressJPEGImage]: JPEG changed to lossless (J1) for %d bits data\n",
                		BitsAllocated);
            			lFileCompressMode = '1';//Most likely a store, we can take lossless, so change it.
            			}
        		}
    		if(!CompressJPEGL(pDDO, lFileCompressMode, 0))
        		{
        		delete pDDO;
        		return FALSE;
        		}
    		PDU.SaveDICOMDataObject(file, DICOM_CHAPTER_10_IMPLICIT, pDDO);
		CompressJpeg++;
    		delete pDDO;

#else //No LIBJPEG, do it the old way.

	pVR = pDDO->GetVR(0x0028, 0x0004);
	if (pVR) 
		{
			if (pVR->Length>=12 && (memcmp(pVR->Data, "YBR_FULL_422", 12)==0))
			{
			OperatorConsole.printf("[CompressJPEGImageFile]: JPEG compression not allowed for YBR_FULL_422\n");
			delete pDDO;
	        	return FALSE;
			}
		}

	pVR = pDDO->GetVR(0x0028, 0x0100);
	if (pVR) 
		{
		BOOL DecompressNon16BitsJpeg;
		UseBuiltInDecompressor(&DecompressNon16BitsJpeg);

		int BitsAllocated = *((UINT8 *)pVR->Data);
		if (BitsAllocated!=16 && !DecompressNon16BitsJpeg)
			{
			OperatorConsole.printf("[CompressJPEGImageFile]: JPEG compression only supported for 16 bits data\n");
			delete pDDO;
	        	return FALSE;
			}
		}
	
	switch(lFileCompressMode)
		{
		case '1': strcpy(opts, "+e1 +un +sr"); break;	// default lossless SV1 "1.2.840.10008.1.2.4.70" = jpeg 14 (33%)
		case '2': strcpy(opts, "+el +un +sr"); break;	// 	   lossless SV6 "1.2.840.10008.1.2.4.57" = jpeg 14 (33%)
		case '3': strcpy(opts, "+eb +un +sr"); break;	// baseline   (8 bits ) "1.2.840.10008.1.2.4.50" = jpeg 1  (15%)
		case '4': strcpy(opts, "+ee +un +sr"); break;	// extended   (12 bits) "1.2.840.10008.1.2.4.51" = jpeg 4  (15%)
		case '5': strcpy(opts, "+es +un +sr"); break;	// spectral sel 	"1.2.840.10008.1.2.4.53" = jpeg 8  (15%)
		case '6': strcpy(opts, "+ep +un +sr"); break;	// progressive		"1.2.840.10008.1.2.4.55" = jpeg 12 (14%)

		default:strcpy(opts, "+e1 +un +sr"); break;	// default = lossless SV1
		}
	 
	pVR = pDDO->GetVR(0x7fe0, 0x0010);
	if (pVR)
		pVR->TypeCode = 'OW';

// mvh 20040602: why is this deleted at all?
//	pVR = pDDO->GetVR(0x0002, 0x0010);
//	if (pVR) pDDO->DeleteVR(pVR);

	PDU.SaveDICOMDataObject(name, DICOM_CHAPTER_10_EXPLICIT, pDDO);
	delete pDDO;

#ifdef WIN32		
	if (!ExecHidden("dcmcjpeg.exe", opts, name, file, ""))
#else
	if (!ExecHidden("dcmcjpeg", opts, name, file, "DCMDICTPATH=dicom.dic\0"))
#endif
		{			// if executable fails file did not change
		unlink(name);
		return ( FALSE );
		}

	unlink(name);
	CompressJpeg++;
#endif //HAVE_LIBJPEG #else
        *ActualMode = lFileCompressMode;
	return ( TRUE );
	}
*/

// Compress JPEG coded image (lFileCompressMode must be in [0..6], 0=uncompressed)
// CompressJPEGImage() used in one place later in this file, pDDO already decompressed. BCB
BOOL
CompressJPEGImage(DICOMDataObject **pDDO, int lFileCompressMode, int *ActualMode, int qual)
	{
	PDU_Service		PDU;
	char			name[1024], name2[1024];
	VR*			pVR;
	char			opts[80];

        *ActualMode = -1;

	if (lFileCompressMode=='0')
		{
                *ActualMode = '0';
		// return DecompressImage(pDDO, &dum); BCB
		return TRUE;
		}

	PDU.AttachRTC(&VRType);

	NewTempFile(name);
	NewTempFile(name2);

	pVR = (*pDDO)->GetVR(0x0008, 0x0060);
	if (pVR) 
		{
			if (pVR->Length>=2 && (memcmp(pVR->Data, "PR", 2)==0 || 
                                               memcmp(pVR->Data, "SR", 2)==0 ||
                                               memcmp(pVR->Data, "RT", 2)==0))
			{
			OperatorConsole.printf("[CompressJPEGImage]: JPEG compression not allowed for PR/SR/RT\n");
	        	return FALSE;
			}
		}

	if (((*pDDO)->GetVR(0x7fdf, 0x0010)) != NULL)
		if (!DecompressNKI(*pDDO))
			{
			OperatorConsole.printf("***[CompressJPEGImage]: failed to NKI decompress DICOM object\n");
	        	return FALSE;
			}

#ifdef HAVE_J2K
	if (lFileCompressMode=='K' || lFileCompressMode=='k' || lFileCompressMode=='L' || lFileCompressMode=='l')
		{
		if( lFileCompressMode=='K' || lFileCompressMode=='k') qual = 100;
#ifndef HAVE_BOTH_J2KLIBS
#ifdef HAVE_LIBJASPER
		if(!CompressJPEG2K(*pDDO,qual)) return FALSE;
#endif
#ifdef HAVE_LIBOPENJPEG
		if(!CompressJPEG2Ko(*pDDO,qual)) return FALSE;
#endif
#else //HAVE_BOTH_J2KLIBS
		if(gUseOpenJpeg)
		{
			if(!CompressJPEG2Ko(*pDDO,qual)) return FALSE;
		}
		else if(!CompressJPEG2K(*pDDO,qual)) return FALSE;
#endif
		*ActualMode = lFileCompressMode;
		CompressJpeg2000++;
        	return ( TRUE );
        	}
#else //HAVE_J2K
	if (lFileCompressMode=='K' || lFileCompressMode=='k' || lFileCompressMode=='L' || lFileCompressMode=='l')
		{
		OperatorConsole.printf("***[CompressJPEGImage]: jpeg2000 not supported\n");
         	return FALSE;
		}
#endif //HAVE_J2K

#ifdef HAVE_LIBJPEG
        if(!UseBuiltInDecompressor())
#else
        if(1)
#endif
		{
		pVR = (*pDDO)->GetVR(0x0028, 0x0100);
		if (pVR) 
			{
			BOOL DecompressNon16BitsJpeg;
			UseBuiltInDecompressor(&DecompressNon16BitsJpeg);

			int BitsAllocated = *((UINT8 *)pVR->Data);
			if (BitsAllocated!=16 && !DecompressNon16BitsJpeg)
				{
				OperatorConsole.printf("[CompressJPEGImage]: JPEG compression only supported for 16 bits data\n");
	        		return FALSE;
				}
			}

		pVR = (*pDDO)->GetVR(0x0028, 0x0004);
		if (pVR) 
			{
				if (pVR->Length>=12 && (memcmp(pVR->Data, "YBR_FULL_422", 12)==0))
				{
				OperatorConsole.printf("[CompressJPEGImage]: JPEG compression not allowed for YBR_FULL_422\n");
	        		return FALSE;
				}
			}

		switch(lFileCompressMode)
			{
			case '1': strcpy(opts, "+e1 +un +sr"); break;	// default lossless SV1 "1.2.840.10008.1.2.4.70" = jpeg 14 (33%)
			case '2': strcpy(opts, "+el +un +sr"); break;	// 	   lossless SV6 "1.2.840.10008.1.2.4.57" = jpeg 14 (33%)
			case '3': strcpy(opts, "+eb +un +sr"); break;	// baseline   (8 bits ) "1.2.840.10008.1.2.4.50" = jpeg 1  (15%)
			case '4': strcpy(opts, "+ee +un +sr"); break;	// extended   (12 bits) "1.2.840.10008.1.2.4.51" = jpeg 4  (15%)
			case '5': strcpy(opts, "+es +un +sr"); break;	// spectral sel 	"1.2.840.10008.1.2.4.53" = jpeg 8  (15%)
			case '6': strcpy(opts, "+ep +un +sr"); break;	// progressive		"1.2.840.10008.1.2.4.55" = jpeg 12 (14%)

			default:strcpy(opts, "+e1 +un +sr"); break;	// default = lossless SV1
			}
	 
		pVR = (*pDDO)->GetVR(0x7fe0, 0x0010);
		if (pVR)
		pVR->TypeCode = 'OW';

		PDU.SaveDICOMDataObject(name, DICOM_CHAPTER_10_EXPLICIT, *pDDO);
		delete *pDDO;
		*pDDO = NULL;

#ifdef WIN32		
		if (!ExecHidden("dcmcjpeg.exe", opts, name, name2, ""))
#else
		if (!ExecHidden("dcmcjpeg", opts, name, name2, "DCMDICTPATH=dicom.dic\0"))
#endif
			{
			*pDDO = PDU.LoadDICOMDataObject(name);	// get back original image
			unlink(name);
			return FALSE;
			}

		*pDDO = PDU.LoadDICOMDataObject(name2);
		if(!*pDDO)
			{
			OperatorConsole.printf("***[CompressJPEGImage]: Error on load after: dcmcjpeg %s %s out.dcm)\n", opts, name);
			*pDDO = PDU.LoadDICOMDataObject(name);	// get back original image
			return FALSE;
			}

		unlink(name);
		unlink(name2);
		CompressJpeg++;

	        *ActualMode = lFileCompressMode;
		return ( TRUE );
		}

#ifdef HAVE_LIBJPEG
/* Jpeg standard is lossy = 8 or 12 bits. */
	if(lFileCompressMode > '2')//Lossy
        	{
       		int BitsStored = (*pDDO)->GetBYTE(0x0028, 0x0101);
        	if(BitsStored > 12)
            		{
                	//OperatorConsole.printf(
                    	//"Warn[CompressJPEGImage]: JPEG lossy compression does not support for %d bits data\n",
                    	//BitsAllocated);
            		//return FALSE;//Most likely a c-move, don't know if they can take lossless, so don't compress.

          		OperatorConsole.printf(
                	"Warn[CompressJPEGImage]: JPEG changed to lossless (J1) for %d bits data\n",
                	BitsStored);
            		lFileCompressMode = '1';//Most likely a store, we can take lossless, so change it.
  			}
        	}
    	if(!CompressJPEGL(*pDDO, lFileCompressMode, qual)) return FALSE;
	CompressJpeg++;
#endif //HAVE_LIBJPEG #else
        *ActualMode = lFileCompressMode;
	return ( TRUE );
	}

BOOL recompressFile(char *File, char *Compression, ExtendedPDU_Service *PDU)
	{
//	int 	status = 0;
	BOOL	rc = FALSE;

	if (stricmp(Compression, ""     )==0) return TRUE;
	if (memicmp(Compression, "as", 2)==0) return TRUE;
	if (stricmp(Compression, "is"   )==0) return TRUE;

	if (1)
	{	DICOMDataObject		*pDDO;
		PDU_Service		PDU2;

		PDU2.AttachRTC(&VRType);
		pDDO = PDU2.LoadDICOMDataObject(File);
		if(!pDDO)
			{
			OperatorConsole.printf("***[recompressFile] %s -FAILED: Error on Load\n", File);
			return FALSE;
			}

		if ((rc=recompress(&pDDO, Compression, "", Compression[0]=='n' || Compression[0]=='N', PDU)))
			SaveDICOMDataObject(File, pDDO);
		delete pDDO;
		}

	return rc;
/*
	if      (memicmp(Compression, "un", 2)==0) rc = DecompressImageFile(File, &status);
	else if (memicmp(Compression, "j",  1)==0) rc = CompressJPEGImageFile(File, Compression[1], &status);
	else if (memicmp(Compression, "nj", 2)==0) 
		{
		DICOMDataObject*	pDDO;
		PDU_Service		PDU;
		char s[64];
		VR *vr;

		PDU.AttachRTC(&VRType);
		pDDO = PDU.LoadDICOMDataObject(File);

		s[0] = 0;
		vr = pDDO->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;

		delete pDDO;

		// leave JPEG as is
#ifdef HAVE_J2K // JPEG 2000 stuff
		if (strcmp(s, "1.2.840.10008.1.2.4.91")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.90")==0) return TRUE;
#endif
		if (strcmp(s, "1.2.840.10008.1.2.4.70")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.57")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.50")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.51")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.53")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.55")==0) return TRUE;

		if (!DecompressImageFile(File, &status)) return FALSE;
		rc = CompressNKIImageFile (File, MAXNKICOMPRESSION, &status);
		}
	else if (memicmp(Compression, "uj", 2)==0) 
		{
		DICOMDataObject*	pDDO;
		PDU_Service		PDU;
		char s[64];
		VR *vr;

		PDU.AttachRTC(&VRType);
		pDDO = PDU.LoadDICOMDataObject(File);

		s[0] = 0;
		vr = pDDO->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;

		delete pDDO;

		// leave JPEG as is
#ifdef HAVE_J2K // JPEG 2000 stuff
		if (strcmp(s, "1.2.840.10008.1.2.4.91")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.90")==0) return TRUE;
#endif
		if (strcmp(s, "1.2.840.10008.1.2.4.70")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.57")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.50")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.51")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.53")==0) return TRUE;
		if (strcmp(s, "1.2.840.10008.1.2.4.55")==0) return TRUE;

		rc = DecompressImageFile(File, &status);
		}
	else if (memicmp(Compression, "n",  1)==0) 
		{
		if (!DecompressImageFile(File, &status)) return FALSE;
		if (Compression[1]=='0') rc = TRUE;
		else                     rc = CompressNKIImageFile (File, Compression[1]-'0', &status);
		}
	else if (memicmp(Compression, "k",  1)==0) 
		{
		if (!DecompressImageFile(File, &status)) return FALSE;
		if (Compression[1]=='0') rc = TRUE;
		else                     rc = DownSizeImageFile (File, Compression[1], &status);
		}
	else if (memicmp(Compression, "s",  1)==0) 
		{
		DICOMDataObject		*pDDO;
		PDU_Service		PDU;
//		int			dum;

		PDU.AttachRTC(&VRType);
		pDDO = PDU.LoadDICOMDataObject(File);
		if(!pDDO)
			{
			OperatorConsole.printf("***[recompressFile] %s -FAILED: Error on Load\n", File);
			return FALSE;
			}

		//VR *VariableVRs[3] = {NULL, NULL, NULL};
		CallImportConverterN(pDDO, 1400 + Compression[1] - '0', NULL, NULL, NULL, NULL, 
			"calling", "called", NULL, NULL);

		SaveDICOMDataObject(File, pDDO);
		delete pDDO;
		rc=status=1;
		}
        
        if (rc && status>0)
          OperatorConsole.printf("[recompressFile]: recompressed with mode = %s\n", Compression);

	return rc;
*/
	}
	
static void Strip2(DICOMDataObject *pDDO)
{ 	DICOMObject	DO2;
	VR		*vr;

	while((vr=pDDO->Pop()))
		{
	  	if (vr->Group==2) delete vr;
		else DO2.Push(vr);
		}

	pDDO->Reset();
	while((vr=DO2.Pop())) pDDO->Push(vr);
}

// use Filename to optionally forbid illegal compressions (e.g. nki->.dcm & jpeg->.v2)
BOOL recompress(DICOMDataObject **pDDO, const char *Compression, const char *Filename, BOOL StripGroup2, ExtendedPDU_Service *PDU)
	{
	int 	status = 0;
	BOOL	rc = FALSE, pass, all;
	UNUSED_ARGUMENT(Filename);

	// no strip group 2 for these options!
	if (stricmp(Compression, ""     )==0) return TRUE;
	if (memicmp(Compression, "as", 2)==0) return TRUE;
	if (stricmp(Compression, "is"   )==0) return TRUE;
	if (memicmp(Compression, "v" , 1)==0) return TRUE;

	int t = (int)time(NULL);

	if (memicmp(Compression, "uj",  2)==0) 
		{
		char s[64];
		VR *vr = (*pDDO)->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			{
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;

			// leave JPEG as is
			if ((strcmp(s, "1.2.840.10008.1.2.4.70")==0) ||
#ifdef HAVE_J2K // JPEG 2000 stuff
				(strcmp(s, "1.2.840.10008.1.2.4.90")==0) ||
				(strcmp(s, "1.2.840.10008.1.2.4.91")==0) ||
#endif
			    (strcmp(s, "1.2.840.10008.1.2.4.57")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.50")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.51")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.53")==0) ||
		            (strcmp(s, "1.2.840.10008.1.2.4.55")==0))
			    	{
			    	if (StripGroup2) Strip2(*pDDO);
			    	return TRUE;
			    	}
			}
	
		rc = DecompressImage(pDDO, &status);
		}

	//added uncompressed LittleEndianImplicit, LittleEndianExplicit or BigEndianExplicit. bcb	    
	else if (*Compression == 'u' || *Compression == 'U' )
		{
		char s[64];
		VR *vr = (*pDDO)->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			{
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;
			s[18] = '0';// Used for switch in LittleEndianImplicit.

			// skip recompression to original level, only LittleEndianImplicit is 17 long
			if (strncmp(s, "1.2.840.10008.1.2", 17)==0)
				{
				pass = FALSE;
				all = TRUE;// Stays true for all except default

				switch (s[18])
					{
					case '0': if (Compression[1]=='i'|| Compression[1]=='I') 
							pass = TRUE;
						break;
					case '1': if (Compression[1]=='l'|| Compression[1]=='L') 
							pass = TRUE;
						break;
					case '2': if (Compression[1]=='b'|| Compression[1]=='B') 
							pass = TRUE;
						break;
					default: all = FALSE;// RLE
						break;
					}
				// Test for "un"
				if (all && (Compression[1]=='n' || Compression[1]=='N')) pass = FALSE;

				if((*pDDO)->GetBYTE(0x0028, 0x0006)) pass=FALSE; // deplaning should happen 20101220

				VR *pVR = (*pDDO)->GetVR(0x0028, 0x0004);		 // depalette should happen 20101220
				if(pVR && pVR->Length == 14 && strncmp( (char *)pVR->Data, "PALETTE COLOR", 13) == 0) pass = FALSE;

				if (pass)
					{
					if (StripGroup2) Strip2(*pDDO);
					return TRUE;
					}
				}
			}
		if((rc = DecompressImage(pDDO, &status)))
			{
	// Tell "DCM to VR" what it is.  May want to set "un" to a specific type
			if(Compression[1]=='i'|| Compression[1] == 'I')
				(*pDDO)->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2\0", 'IU');
			if(Compression[1]=='l'|| Compression[1] == 'L')
				(*pDDO)->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.1\0", 'IU');
			if(Compression[1]=='b'|| Compression[1] == 'B')
				(*pDDO)->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.2\0", 'IU');
			}
		}

	else if (memicmp(Compression, "j",  1)==0) 
		{
		char s[64];
		VR *vr = (*pDDO)->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			{
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;

			// skip recompression to original level
			if(strncmp(s,"1.2.840.10008.1.2.4.",20)==0)//Common to all jpeg
				{
				pass = FALSE;
				all = TRUE;// Stays true for all except default
				switch (atoi(s + 20))
					{
					case 50: if (Compression[1]=='3') pass = TRUE;
						break;
					case 51: if (Compression[1]=='4') pass = TRUE;
						break;
					case 53: if (Compression[1]=='5') pass = TRUE;
						break;
					case 55: if (Compression[1]=='6') pass = TRUE;
						break;
					case 57: if (Compression[1]=='2') pass = TRUE;
						break;
					case 70: if (Compression[1]=='1') pass = TRUE;
						break;
#ifdef HAVE_J2K // JPEG 2000 stuff
					case 90: if (Compression[1]=='k' || Compression[1]=='k') pass = TRUE;
						break;
					case 91: if (Compression[1]=='l' || Compression[1]=='L') pass = TRUE;
						break;
#endif
					default: all = FALSE;// What is this, unknown jpeg.
						break;
					}
			// Test for "ja"
				if (all && (Compression[1]=='a' || Compression[1]=='A')) pass = TRUE;
				if (pass)
					{
					if (StripGroup2) Strip2(*pDDO);
					return TRUE;
					}
				}
/* The switch is easier to add ja (all)				
			if ((strcmp(s, "1.2.840.10008.1.2.4.70")==0 && Compression[1]=='1') ||
			    (strcmp(s, "1.2.840.10008.1.2.4.57")==0 && Compression[1]=='2') ||
			    (strcmp(s, "1.2.840.10008.1.2.4.50")==0 && Compression[1]=='3') ||
			    (strcmp(s, "1.2.840.10008.1.2.4.51")==0 && Compression[1]=='4') ||
			    (strcmp(s, "1.2.840.10008.1.2.4.53")==0 && Compression[1]=='5') ||
			    (strcmp(s, "1.2.840.10008.1.2.4.55")==0 && Compression[1]=='6')
#ifdef HAVE_J2K // JPEG 2000 stuff
			 || (strcmp(s, "1.2.840.10008.1.2.4.90")==0 && (Compression[1]=='k' || Compression[1]=='K')) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.91")==0 && (Compression[1]=='l' || Compression[1]=='L'))
#endif
			   )
			    	{
			    	if (StripGroup2) Strip2(*pDDO);
			    	return TRUE;
			    	}*/
				}
	
		int qual = 0; // default as configured in dicom.ini
		if (Compression[2]) qual = atoi(Compression+2);

		if (!DecompressImage(pDDO, &status)) return FALSE;
		rc = CompressJPEGImage(pDDO, Compression[1], &status, qual);
		if (strchr("3456lL", Compression[1]))
		  (*pDDO)->ChangeVR(0x0028, 0x2110, "01", 'CS'); // 20120624: set lossy compression
		}

	else if (memicmp(Compression, "nj",  2)==0) 
		{
		char s[64];
		VR *vr = (*pDDO)->GetVR(0x0002, 0x0010);
		if (vr && vr->Data)
			{
			strncpy(s, (char*)vr->Data, vr->Length); s[vr->Length] = 0;

			// leave JPEG as is
			if ((strcmp(s, "1.2.840.10008.1.2.4.70")==0) ||
#ifdef HAVE_J2K // JPEG 2000 stuff
				(strcmp(s, "1.2.840.10008.1.2.4.90")==0) ||
				(strcmp(s, "1.2.840.10008.1.2.4.91")==0) ||
#endif
			    (strcmp(s, "1.2.840.10008.1.2.4.57")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.50")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.51")==0) ||
			    (strcmp(s, "1.2.840.10008.1.2.4.53")==0) ||
		            (strcmp(s, "1.2.840.10008.1.2.4.55")==0))
			    	{
			    	if (StripGroup2) Strip2(*pDDO);
			    	return TRUE;
			    	}
			}
	
		if (!DecompressImage(pDDO, &status)) return FALSE;
		rc = CompressNKI(*pDDO, MAXNKICOMPRESSION);
		status = rc;
		}

	else if (memicmp(Compression, "n",  1)==0) 
		{
		// skip recompression to original level
		signed char *p;
		VR *vr = (*pDDO)->GetVR(0x7fdf, 0x0010);
		if (vr)
			{
    			p = ((signed char *)(vr->Data));
		    	if (p && get_nki_private_compress_mode(p)==Compression[1]-'0')
			    	{
			    	if (StripGroup2) Strip2(*pDDO);
			    	return TRUE;
			    	}
			}
    
		if (!DecompressImage(pDDO, &status)) return FALSE;

		if (Compression[1]=='0') rc = TRUE;
		else                     
			{
			rc = CompressNKI(*pDDO, Compression[1]-'0');
			status = rc;
			}
		}

	else if (memicmp(Compression, "k",  1)==0) 
		{
		int size;

		switch (Compression[1])
			{ 
			case '1': size = 1024; break;
			case '2': size =  512; break;
			case '4': size =  256; break;
			case '8': size =  128; break;
			case 'A': case 'a': size =  64; break;
			case 'B': case 'b': size =  32; break;
			case 'C': case 'c': size =  16; break;
                	default : size =65536; break;
			}

		if (TestDownsize(*pDDO, NULL, size))
			{
			if (!DecompressImage(pDDO, &status)) return FALSE;

			switch (Compression[1])
				{
				case '1': rc = MaybeDownsize(*pDDO, NULL, 1024); break;
				case '2': rc = MaybeDownsize(*pDDO, NULL, 512); break;
				case '4': rc = MaybeDownsize(*pDDO, NULL, 256); break;
				case '8': rc = MaybeDownsize(*pDDO, NULL, 128); break;
				case 'A': case 'a': rc = MaybeDownsize(*pDDO, NULL, 64); break;
				case 'B': case 'b': rc = MaybeDownsize(*pDDO, NULL, 32); break;
				case 'C': case 'c': rc = MaybeDownsize(*pDDO, NULL, 16); break;
				}
			if (rc==2) status = 1;
			}
		else
			status = 1;
		}

	else if (memicmp(Compression, "s",  1)==0) 
		{
		//CallImportConverterN(*pDDO, 1400 + Compression[1] - '0', NULL, NULL, NULL, NULL, "calling", "called", NULL, NULL, VariableVRs);
		CallImportConverterN(*pDDO, 1400 + Compression[1] - '0', NULL, NULL, NULL, NULL, PDU, NULL, NULL);
		rc = status = 1;
		}

	if (StripGroup2) Strip2(*pDDO);

        if (rc && status>0)
          OperatorConsole.printf("[recompress]: recompressed with mode = %s (strip=%d)\n", Compression, StripGroup2);

	RecompressTime += (int)time(NULL)-t;

	return rc;
	}

///////////////////////////////////////////////////////////////////////////////////////////////
// PDU with dgate compression styles
///////////////////////////////////////////////////////////////////////////////////////////////

BOOL
ExtendedPDU_Service	::	AddTransferSyntaxs(PresentationContext &PresContext)
	{
	UID		uid;
	TransferSyntax	TrnSyntax;

	// as-is not correctly implemented (hard to do, since each image will require other compression)
	// will now tranmsit over ImplicitLittleEndian - OK for NKI clients

	if (memicmp(RequestedCompressionType, "as", 2)==0 || memicmp(RequestedCompressionType, "is", 2)==0)
		{
		OperatorConsole.printf("Warning: use of as is compression for outgoing associations not fully implemented\n");
		}
	// Added uncompressed LittleEndianExplicit. bcb
	if (memicmp(RequestedCompressionType, "ul", 2)==0)
	    {
	    uid.Set("1.2.840.10008.1.2.1"); TrnSyntax.Set(uid);
	    PresContext.AddTransferSyntax(TrnSyntax);
	    }
	// Added uncompressed BigEndianExplicit. bcb
	if (memicmp(RequestedCompressionType, "ub", 2)==0)
	    {
	    uid.Set("1.2.840.10008.1.2.2"); TrnSyntax.Set(uid);
	    PresContext.AddTransferSyntax(TrnSyntax);
	    }
	// Added uncompressed LittleEndianExplicit or BigEndianExplicit. bcb
	if (memicmp(RequestedCompressionType, "ue", 2)==0)
	    {
	    uid.Set("1.2.840.10008.1.2.1"); TrnSyntax.Set(uid);
	    PresContext.AddTransferSyntax(TrnSyntax);
	    uid.Set("1.2.840.10008.1.2.2"); TrnSyntax.Set(uid);
	    PresContext.AddTransferSyntax(TrnSyntax);
	    }
			
	// only jpeg requires other tranmission syntaxes

	if (RequestedCompressionType[0]=='j' || RequestedCompressionType[0]=='J')
		{
		switch(RequestedCompressionType[1])
			{
/*			case '1': // lossless
				  uid.Set("1.2.840.10008.1.2.4.70"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;
*/				 
			// bcb: should not j1 & J2 offer both types of lossless.
			case '1': // lossless
			case '2': // losless sv 6
				  uid.Set("1.2.840.10008.1.2.4.57"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.70"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;

			case '3': // lossy baseline (8bit) + extended(12 bit)
			case '4': uid.Set("1.2.840.10008.1.2.4.51"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.50"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;

			case '5': // spectral selection
				  uid.Set("1.2.840.10008.1.2.4.53"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.51"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.50"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;

			case '6': // progressive
				  uid.Set("1.2.840.10008.1.2.4.55"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.51"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.50"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;

#ifdef HAVE_J2K // JPEG 2000 stuff
			case 'K':
			case 'k': // 2K lossless only
				  uid.Set("1.2.840.10008.1.2.4.90"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;

			case 'L':
			case 'l': // 2K lossy or lossless
				  uid.Set("1.2.840.10008.1.2.4.91"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.90"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;
#endif

			default:  // lossless
			          // bcb added .57 here
				  uid.Set("1.2.840.10008.1.2.4.57"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  uid.Set("1.2.840.10008.1.2.4.70"); TrnSyntax.Set(uid);
				  PresContext.AddTransferSyntax(TrnSyntax);
				  break;
			}
		}

	uid.Set("1.2.840.10008.1.2");		// ImplicitLittleEndian
	TrnSyntax.Set(uid);
	PresContext.AddTransferSyntax(TrnSyntax);

	return ( TRUE );
	}

BOOL
ExtendedPDU_Service	::	SetRequestedCompressionType(const char *type)
	{
	strcpy(RequestedCompressionType, type);
	return ( TRUE );
	}

char*
ExtendedPDU_Service	::	GetAcceptedCompressionType(UID uid)
	{
	UID TrnSyntaxUID;
	int ContextID = GetPresentationContextID(uid);
	char *p;

	if ( !ContextID )
		{
		strcpy(AcceptedCompressionType, "");
		return ( AcceptedCompressionType );
		}

	GetTransferSyntaxUID(ContextID, TrnSyntaxUID);

	if (RequestedCompressionType[0]!='j' && RequestedCompressionType[0]!='J')
		{
		strcpy(AcceptedCompressionType, RequestedCompressionType);
		return ( AcceptedCompressionType );
		}

	p = (char *)TrnSyntaxUID.GetBuffer(1);
	     if (strcmp(p, "1.2.840.10008.1.2.4.70")==0) strcpy(AcceptedCompressionType, "j1");
	else if (strcmp(p, "1.2.840.10008.1.2.4.57")==0) strcpy(AcceptedCompressionType, "j2");
	else if (strcmp(p, "1.2.840.10008.1.2.4.50")==0) strcpy(AcceptedCompressionType, "j3");
	else if (strcmp(p, "1.2.840.10008.1.2.4.51")==0) strcpy(AcceptedCompressionType, "j4");
	else if (strcmp(p, "1.2.840.10008.1.2.4.53")==0) strcpy(AcceptedCompressionType, "j5");
	else if (strcmp(p, "1.2.840.10008.1.2.4.55")==0) strcpy(AcceptedCompressionType, "j6");
#ifdef HAVE_J2K // JPEG 2000 stuff
	else if (strcmp(p, "1.2.840.10008.1.2.4.90")==0) strcpy(AcceptedCompressionType, "jk");
	else if (strcmp(p, "1.2.840.10008.1.2.4.91")==0) strcpy(AcceptedCompressionType, "jl");
#endif
	// Added uncompressed LittleEndianImplicit, LittleEndianExplicit or BigEndianExplicit. bcb
	else if (strcmp(p, "1.2.840.10008.1.2.1")==0) strcpy(AcceptedCompressionType, "ul");
	else if (strcmp(p, "1.2.840.10008.1.2.2")==0) strcpy(AcceptedCompressionType, "ub");
	else if (strcmp(p, "1.2.840.10008.1.2")==0) strcpy(AcceptedCompressionType, "ui");
	else strcpy(AcceptedCompressionType, "un");

	OperatorConsole.printf("Accepted compression: %s\n", AcceptedCompressionType);


	return ( AcceptedCompressionType );
	}


////////////////////////////////////////////////////////////////////////////////////////////

/* Downsize and convert image to 8 bit monochrome or RGB */

static BOOL To8bitMonochromeOrRGB(DICOMDataObject* pDDO, int size, int *Dimx, int *Dimy, unsigned char **out, int RGBout=0, int level=0, int window=0, unsigned int frame=0)
{ int			i, j, dum;
  VR*			pVR;
  unsigned int		iMaxRowsColumns;
  unsigned short	iRows, iColumns, iNewRows, iNewColumns, iDownsizeFactor;
  unsigned int		iImageSize, iNbBytesPerPixel, iNbPixels, iSkip;
  char*			pcSrc;
  unsigned char*	pcDest;
  short*		psSrc;
//  int*			piSrc;//Anything that points to VR->Data should be the same size on all systems. BCB
  INT32*        piSrc;
  int			r, g, b;
  int                   pixeloffset = 0;

  ExtractFrame(pDDO, frame);

  if (size==0) iMaxRowsColumns = 16384;
  else         iMaxRowsColumns = size;

  /* OK. Now check whether all necessary PixelData-info is present in pDDO */
  iRows = pDDO->GetUINT16(0x0028, 0x0010);
  iColumns = pDDO->GetUINT16(0x0028, 0x0011);
  iNbPixels = iRows * iColumns;

  if (!iNbPixels) 			/* Image must make sense */
    return FALSE;

  pVR = pDDO->GetVR(0x0008, 0x0060);	/* Modality */
  if (pVR && pVR->Length==2 && memcmp(pVR->Data, "CT", 2)==0)
  { pVR = pDDO->GetVR(0x0028, 0x1052);	/* RescaleIntercept */
    if ( pVR) pixeloffset = pVR->Getatoi() + 1024;
  }
  
  if (iRows >= iColumns)
  { iDownsizeFactor = iRows / iMaxRowsColumns;
    if (iRows % iMaxRowsColumns)
      iDownsizeFactor ++;
  }
  else
  { iDownsizeFactor = iColumns / iMaxRowsColumns;
    if (iColumns % iMaxRowsColumns)
      iDownsizeFactor ++;
  }

  if (iDownsizeFactor<1) iDownsizeFactor=1;

  if (!DecompressImage(&pDDO, &dum))	/* make sure it is not NKI or JPEG compressed */
    return FALSE;

  pVR = pDDO->GetVR(0x7fe0, 0x0010);	/* Pixeldata */
  if (!pVR)
    return TRUE;
  iImageSize = pVR->Length;

  if ((iImageSize < iNbPixels) ||
      (iImageSize % iNbPixels > 1))	/* allow 1 byte padding */
    return FALSE;			/* Image doesn't make sense */

  iNbBytesPerPixel = iImageSize / iNbPixels;
  if (iNbBytesPerPixel > 4)
    return FALSE;			/* Image is too beautiful to convert! */

  /* LETS DO IT !
     The downsized image is stored in the same memory-block as the original one:
     Just be sure to adjust the length-indicator. The image will be (re)compressed anyway
     later on.
  */

  iNewRows    = iRows / iDownsizeFactor;
  if (!iNewRows)
    iNewRows++;
  iNewColumns = iColumns / iDownsizeFactor;
  if (!iNewColumns)
    iNewColumns++;

  if (RGBout & (iNewColumns&3)!=0) 
    iNewColumns &= 0xfffffffc;	// make multiple of 4 (truncate some columns if needed)

  *Dimy = iNewRows;
  *Dimx = iNewColumns;

  *out = (unsigned char *)malloc(iNewRows * iNewColumns * (RGBout?3:1));
  if (*out==NULL) return FALSE;
  pcDest = *out;

  switch (iNbBytesPerPixel + 10 * RGBout)
  { case 1:
      pcSrc  = (char*)pVR->Data;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc;
	  pcSrc += iDownsizeFactor;
	}
	pcSrc = (char*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);
      }
      break;

    case 2:
    { int max=0;
      psSrc  = (short*)pVR->Data;

      if (window)
      { for (i=0; i<iNewRows; i++)
        { for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
	    psSrc += iDownsizeFactor;
  	  }
	  psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { for (j=0; j<iNewColumns; j++)
  	  { 
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            if (r > max) max=r;
            if (r>2047) r=2047;
            if (r<0)    r=0;
            r = r/8;
            *pcDest++ = r;
  	    psSrc += iDownsizeFactor;
  	  }
  	  psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);
        }
  
        // auto scale if too dark or too bright
  
        if (max < 1024 || max > 4095)
        { int factor = (int)((max / 256.0) + 0.5);
          if (factor==0) factor=1;
  
          pcDest = *out;
          psSrc  = (short*)pVR->Data;
          for (i=0; i<iNewRows; i++)
          { for (j=0; j<iNewColumns; j++)
            {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
              r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
              r = SwitchEndian(*psSrc) + pixeloffset;
#endif
              r = r/factor;
              if (r>255) r=255;
              if (r<0)   r=0;
              *pcDest++ = r;
  	      psSrc += iDownsizeFactor;
    	    }
    	    psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);
          }
        }
      }

      break;
    }

    case 3:
      pcSrc  = (char*)pVR->Data;
      iSkip = (iDownsizeFactor - 1) * 3;
      for (i=0; i<iNewRows; i++)
      { for (j=0; j<iNewColumns; j++)
	{ r = *pcSrc++;
	  g = *pcSrc++;
	  b = *pcSrc++;
          *pcDest++ = (r+g+b)/3;
	  pcSrc += iSkip;
	}
	pcSrc = (char*)pVR->Data + iDownsizeFactor * 3 * iColumns * (i + 1);
      }
      break;

    case 4:
      piSrc  = (INT32*)pVR->Data;//Changed from (int*)
      if (window)
      { for (i=0; i<iNewRows; i++)
        { for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *piSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*piSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
	    piSrc += iDownsizeFactor;
	  }
	  piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);// was (int*)
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            *pcDest++ = (*piSrc + pixeloffset) / 8;
#else //Big Endian like Apple power pc
            *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
#endif
    	    piSrc += iDownsizeFactor;
	  }
	  piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * (i + 1);//Was(int*)
        }
      }
      break;

    case 11:
      for (i=0; i<iNewRows; i++)
      { pcSrc = (char*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);
        for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc;
	  *pcDest++ = *pcSrc;
	  *pcDest++ = *pcSrc;
	  pcSrc += iDownsizeFactor;
	}
      }
      break;

    case 12:
    { int max=0;
      if (window)
      { for (i=0; i<iNewRows; i++)
        { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);
          for (j=0; j<iNewColumns; j++)
            {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
            *pcDest++ = r;
            *pcDest++ = r;
	    psSrc += iDownsizeFactor;
  	  }
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);
          for (j=0; j<iNewColumns; j++)
            {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            if (r > max) max=r;
            if (r>2047) r=2047;
            if (r<0)    r=0;
            r = r/8;
            *pcDest++ = r;
            *pcDest++ = r;
            *pcDest++ = r;
  	    psSrc += iDownsizeFactor;
  	  }
        }
  
        // auto scale if too dark or too bright
  
        if (max < 1024 || max > 4095)
        { int factor = (int)((max / 256.0) + 0.5);
          if (factor==0) factor=1;
  
          pcDest = *out;
          for (i=0; i<iNewRows; i++)
          { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);
            for (j=0; j<iNewColumns; j++)
              {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
              r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
              r = SwitchEndian(*psSrc) + pixeloffset;
#endif
              r = r/factor;
              if (r>255) r=255;
              if (r<0)   r=0;
              *pcDest++ = r;
              *pcDest++ = r;
              *pcDest++ = r;
  	      psSrc += iDownsizeFactor;
    	    }
          }
        }
      }

      break;
    }

    case 13:
      iSkip = (iDownsizeFactor - 1) * 3;
      for (i=0; i<iNewRows; i++)
      { pcSrc = (char*)pVR->Data + iDownsizeFactor * 3 * iColumns * (iNewRows-1-i);
        for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  pcSrc += iSkip;
	}
      }
      break;

    case 14:
      if (window)
      { for (i=0; i<iNewRows; i++)
        { piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);//Was (int*)
          for (j=0; j<iNewColumns; j++)
           {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *piSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*piSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
  	    *pcDest++ = r;
	    *pcDest++ = r;
	    piSrc += iDownsizeFactor;
	  }
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);//Was (int*)
          for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            *pcDest++ = (*piSrc + pixeloffset) / 8;
  	    *pcDest++ = (*piSrc + pixeloffset) / 8;
	    *pcDest++ = (*piSrc + pixeloffset) / 8;
#else //Big Endian like Apple power pc
            *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
  	    *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
	    *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
#endif
	    piSrc += iDownsizeFactor;
	  }
        }
      }
      break;

    case 21:
      for (i=0; i<iNewRows; i++)
      { pcSrc = (char*)pVR->Data + iDownsizeFactor * iColumns * i;
        for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc;
	  *pcDest++ = *pcSrc;
	  *pcDest++ = *pcSrc;
	  pcSrc += iDownsizeFactor;
	}
      }
      break;

    case 22:
    { int max=0;
      if (window)
      { for (i=0; i<iNewRows; i++)
        { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * i;
          for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
            *pcDest++ = r;
            *pcDest++ = r;
	    psSrc += iDownsizeFactor;
  	  }
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * i;
          for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*psSrc) + pixeloffset;
#endif
            if (r > max) max=r;
            if (r>2047) r=2047;
            if (r<0)    r=0;
            r = r/8;
            *pcDest++ = r;
            *pcDest++ = r;
            *pcDest++ = r;
  	    psSrc += iDownsizeFactor;
  	  }
        }
  
        // auto scale if too dark or too bright
  
        if (max < 1024 || max > 4095)
        { int factor = (int)((max / 256.0) + 0.5);
          if (factor==0) factor=1;
  
          pcDest = *out;
          for (i=0; i<iNewRows; i++)
          { psSrc = (short*)pVR->Data + iDownsizeFactor * iColumns * i;
            for (j=0; j<iNewColumns; j++)
            {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
              r = *psSrc + pixeloffset;
#else //Big Endian like Apple power pc
              r = SwitchEndian(*psSrc) + pixeloffset;
#endif
              r = r/factor;
              if (r>255) r=255;
              if (r<0)   r=0;
              *pcDest++ = r;
              *pcDest++ = r;
              *pcDest++ = r;
  	      psSrc += iDownsizeFactor;
    	    }
          }
        }
      }

      break;
    }

    case 23:
      iSkip = (iDownsizeFactor - 1) * 3;
      for (i=0; i<iNewRows; i++)
      { pcSrc = (char*)pVR->Data + iDownsizeFactor * 3 * iColumns * i;
        for (j=0; j<iNewColumns; j++)
	{ *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  *pcDest++ = *pcSrc++;
	  pcSrc += iSkip;
	}
      }
      break;

    case 24:
      if (window)
      { for (i=0; i<iNewRows; i++)
        { piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * i;//Was (int*)
          for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            r = *piSrc + pixeloffset;
#else //Big Endian like Apple power pc
            r = SwitchEndian(*piSrc) + pixeloffset;
#endif
            r = 255 * (r - level + window/2) / window;
            if (r>255) r=255;
            if (r<0)   r=0;
            *pcDest++ = r;
  	    *pcDest++ = r;
	    *pcDest++ = r;
	    piSrc += iDownsizeFactor;
	  }
        }
      }
      else
      { for (i=0; i<iNewRows; i++)
        { piSrc = (INT32*)pVR->Data + iDownsizeFactor * iColumns * (iNewRows-1-i);//Was (int*)
          for (j=0; j<iNewColumns; j++)
          {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
            *pcDest++ = (*piSrc + pixeloffset) / 8;
  	    *pcDest++ = (*piSrc + pixeloffset) / 8;
	    *pcDest++ = (*piSrc + pixeloffset) / 8;
#else //Big Endian like Apple power pc
            *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
  	    *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
	    *pcDest++ = (SwitchEndian(*piSrc) + pixeloffset) / 8;
#endif
	    piSrc += iDownsizeFactor;
	  }
        }
      }
      break;
  }

  return TRUE;
}

int WriteGIF(FILE *fp, unsigned char *pic, int ptype, int w, int h, 
                       unsigned char *rmap, unsigned char *gmap, unsigned char *bmap,
                       int numcols, int colorstyle, const char *comment);

#ifndef hasColorStyleType
#define hasColorStyleType 1
enum ColorStyleType {csGlobalPalette, csLocalPalette};
#endif

int WriteGIFHeader(FILE *fp, int w, int h, BYTE *rmap, BYTE *gmap, BYTE *bmap,
             int numcols, ColorStyleType colorstyle, char *comment);

int WriteGIFFrame(FILE *fp, BYTE *p, int w, int h,
                  BYTE *rmap, BYTE *gmap, BYTE *bmap,
                  int numcols,
                  int frames, int time, ColorStyleType colorstyle);

BOOL ToGif(DICOMDataObject* pDDO, char *filename, int size, int append, int level, int window, unsigned int frame)
{ int dimx, dimy;
  unsigned char *out;
  FILE *f;
  unsigned char lut[256];
  int i;
  int Ratefps;

  for(i=0; i<256; i++) lut[i]=i;

  if (append) f = fopen(filename, "ab");
  else        f = fopen(filename, "wb");
  if (!f)
    return FALSE;

  // create animated GIF here
  if (frame>10000 && GetNumberOfFrames(pDDO)>1)
  { DICOMDataObject *DDO2 = MakeCopy(pDDO);
    To8bitMonochromeOrRGB(DDO2, size, &dimx, &dimy, &out, 0, level, window, 0);
    WriteGIFHeader(f, dimx, dimy, lut, lut, lut, 256, csLocalPalette, "NETSCAPE2.0");
    delete DDO2;
    
    for (i=0; i<GetNumberOfFrames(pDDO); i++)
    { if (i>0)
      { DDO2 = MakeCopy(pDDO);
        To8bitMonochromeOrRGB(DDO2, size, &dimx, &dimy, &out, 0, level, window, i);
        delete DDO2;
      }

      Ratefps = (frame % 100);
      if (Ratefps==0) Ratefps=1;
      if (out) WriteGIFFrame (f, out, dimx, dimy, lut, lut, lut, 256, 1, 100/Ratefps, csLocalPalette);
      free(out);
    }

    fputc(0x3b, f);                    /* Write GIF file terminator */
    fclose(f);
    return TRUE;
  }

  // create static GIF here
  if (To8bitMonochromeOrRGB(pDDO, size, &dimx, &dimy, &out, 0, level, window, frame))
  { WriteGIF(f, out, 0, dimx, dimy, lut, lut, lut, 256, 0, "ConquestDICOMServer");
    free(out);
    fclose(f);
    return TRUE;
  }

  return FALSE;
}

#pragma pack(1)
typedef struct  
{       char	bfType1;		/* Must be 'B' */
        char	bfType2;		/* Must be 'M' */
        int	bfSize;			/* Size of the file */
        short	bfReserved1;		/* Must be 0 */
        short	bfReserved2;		/* Must be 0 */
        int	bfOffBits;		/* Offset of the ImageBits */

	int	biSize;			/* size of all biXX (40) */
	int	biWidth;
	int	biHeight;
	short	biPlanes;
	short	biBitCount;
	int	biCompression;
	int	biSizeImage;
	int	biXPelsPerMeter;
	int	biYPelsPerMeter;
	int	biClrUsed;
	int	biClrImportant;
} BMP_HEADER;	/* 24BITS */
#pragma pack()

BOOL ToBMP(DICOMDataObject* pDDO, char *filename, int size, int append, int level, int window, unsigned int frame)
{ int dimx, dimy;
  unsigned char *out, c;
  FILE *f;
  int i, t;
  int iDataSize;
  BMP_HEADER bmp;

  if (To8bitMonochromeOrRGB(pDDO, size, &dimx, &dimy, &out, 1, level, window, frame))
  { iDataSize = dimx*dimy*3;	// must be multiple of 4: OK because above routine made dimx multiple of 4

    // swap RGB to BGR
    t = dimx * dimy;
    for (i=0; i<t; i++) {c=out[i*3]; out[i*3]=out[i*3+2]; out[i*3+2]=c; }

    memset((void*)&bmp, 0, sizeof(BMP_HEADER));
    bmp.bfType1 = 'B';
    bmp.bfType2 = 'M';
    bmp.bfSize = iDataSize + sizeof(BMP_HEADER);
    bmp.bfOffBits = sizeof(BMP_HEADER);

    bmp.biSize = 40;
    bmp.biWidth = dimx;
    bmp.biHeight = dimy;
    bmp.biPlanes = 1;
    bmp.biBitCount = 24;
    bmp.biSizeImage = iDataSize;
    bmp.biXPelsPerMeter = 0x0ece;
    bmp.biYPelsPerMeter = 0x0ece;

    if (append) f = fopen(filename, "ab");
    else        f = fopen(filename, "wb");
    if (!f)
    { free(out);
      return FALSE;
    }

    fwrite((void*)&bmp, sizeof(BMP_HEADER), 1, f);
    fwrite(out,         dimx*dimy*3,        1, f);
    
    free(out);
    fclose(f);
    return TRUE;
  }

  return FALSE;
}

#ifdef HAVE_LIBJPEG //The jpeg common stuff.
/* This is a replacement for the libjpeg message printer that normally
*  goes to stderr. */
METHODDEF(void)
joutput_message (j_common_ptr cinfo)
{ 
  char buffer[JMSG_LENGTH_MAX];

  /* Create the message */
  (*cinfo->err->format_message) (cinfo, buffer);

  OperatorConsole.printf("***[JPEG Library]: %s\n", buffer);
}

/* This is a replacement for the libjpeg error handler that normally
*  halts the program. */
METHODDEF(void)
jerror_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  jerror_ptr jerr = (jerror_ptr) cinfo->err;

  /* Always display the message */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(jerr->setjmp_buffer, 1);
}

/* Just for routines we do not need or use. */
METHODDEF(void)
jdoes_nothing (j_decompress_ptr cinfo)
{
/* Nothing */
  UNUSED_ARGUMENT(cinfo);
  return;
}
#else// Use jpeg_encoder.cpp
UINT32 encode_image (UINT8 *input_ptr, UINT8 *output_ptr, UINT32 quality_factor, UINT32 image_format, UINT32 image_width, UINT32 image_height);
#endif

BOOL ToJPG(DICOMDataObject* pDDO, char *filename, int size, int append, int level, int window, unsigned int frame, int quality)
{ int 			dimx, dimy;
  unsigned char 	*out, c;
  FILE 			*f;
  int 			i, Ratefps;
#ifdef HAVE_LIBJPEG
  struct                jpeg_compress_struct cinfo;
  unsigned int          rowWidth;
  struct jerror_mgr     jerr;
  register JSAMPROW     row_pointer;
#endif

  if (frame>10000 && GetNumberOfFrames(pDDO)>1)
  { char file[256], file2[256];
    DICOMDataObject *DDO2 = MakeCopy(pDDO);
    NewTempFile(file);
    for (i=0; i<GetNumberOfFrames(pDDO); i++)
    { sprintf(file2, "%s.%05d", file, i);
      ToJPG(DDO2, file2, size, 0, level, window, i, quality);
      delete DDO2;
    }
    
    Ratefps = (frame % 100);
    if (Ratefps==0) Ratefps=1;

    // to convert a row of jpeg images to mpeg2 using mjpegtools:
// jpeg2yuv -f 25 -I p -j dgate%03d.jpg | mpeg2enc -f 3 -b 1500 -o mpegfile.m2v
//          rate  progr files                      mpg2  bitrate   file
    sprintf(file2, "jpeg2yuv -f %d -I p -j %s%%05d | mpeg2enc -f 3 -b 1500 -o %s", Ratefps, file, filename);
    system(file2);

    for (i=0; i<GetNumberOfFrames(pDDO); i++)
    { sprintf(file2, "%s.%05d", file, i);
      unlink(file2);
    }
    return TRUE;
  }

  if (To8bitMonochromeOrRGB(pDDO, size, &dimx, &dimy, &out, 2, level, window, frame))
  { if (append) f = fopen(filename, "ab");
    else        f = fopen(filename, "wb");
    if (!f)
    { free(out);
      return FALSE;
    }
#ifdef HAVE_LIBJPEG

// Init the default handler.
    cinfo.err = jpeg_std_error(&jerr.pub);
// change the error exit so libjpeg can't kill us.
    jerr.pub.error_exit = jerror_exit;
// Use our methode for outputting messages.
    jerr.pub.output_message = joutput_message;
    if (setjmp(jerr.setjmp_buffer))
    {
/* If we get here, the JPEG code has signaled an error.
 * We need to clean up the JPEG object and return. */
      jpeg_destroy_compress(&cinfo);
      if(f != NULL)
      {
        fclose(f);
        if (!append)unlink(filename);
        free(out);
      }
      return (FALSE);
    }
//Look for multi-byte version 6c (63) from www.bitsltd.net
    jpeg_CreateCompress(&cinfo, 63, (size_t) sizeof(struct jpeg_compress_struct));
// Color space must be set before a call to jpeg_set_defaults.
    cinfo.in_color_space = JCS_RGB; //To8bitMonochromeOrRGB is set for rgb, gray could be faster.
    jpeg_set_defaults(&cinfo);
// Get all the image size stuff.
    cinfo.image_height =  dimy;
    cinfo.image_width =  dimx;
    cinfo.num_components = 3;
    cinfo.input_components = cinfo.num_components;
    cinfo.data_precision = 8;
    cinfo.data_precision_other = cinfo.data_precision;
    jpeg_set_quality(&cinfo, 95, true);//100 is silly in lossy and the same as 95.
    cinfo.jpeg_color_space = cinfo.in_color_space;
    jpeg_default_colorspace(&cinfo);
// Set where to put it.
    jpeg_stdio_dest(&cinfo, f);
    rowWidth =  cinfo.image_width * cinfo.num_components;
    jpeg_start_compress(&cinfo, TRUE);
    while (cinfo.next_scanline < cinfo.image_height)
    {
      row_pointer = &(((JSAMPROW)out)[cinfo.next_scanline * rowWidth]);
      jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }
// If here, finished the compression.
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
#else // Old way.
    unsigned char *output = (UINT8 *)malloc(dimx * dimy * 3);
    UINT32 len;
    len = encode_image (out, output, 256, 14, dimx, dimy);
    fwrite (output, 1, len, f);
    free(output);
#endif
    free(out);
    fclose(f);
    return TRUE;
  }

  return FALSE;
}

#ifdef HAVE_LIBJPEG
/* This routine will take all of the listed color spaces in 08_03 of the standard
*  in little endian, uncompressed format and convert it to YBR_FULL and than compress
*  it to jpeg.  YBR_FULL is the IJG standard for the Jpeg-6b library used everywhere.
*  I did not use the Jpeg-6b version because it had to be compiled for 8, 12 or 16
*  only.  So I wrote Jpeg-6c that can change bit width on the fly.  You can get it here:
*  http://www.bitsltd.net/Software/Software-Repository/index.php
*  I included spectral sel "1.2.840.10008.1.2.4.53" and progressive
*  "1.2.840.10008.1.2.4.55", but both are obsolete and maybe I should remove them.
*  jpegQuality is meaningless for lossless and  0 for use "LossyQuality" in dicom.ini.
*  Maybe one day all of the format decoding should be moved into it's own routine.
*  If I have made some mistakes (most likely) you can contact me bruce.barton
*  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
*  the image that didn't work. */

BOOL CompressJPEGL(DICOMDataObject* pDDO, int comp, int jpegQuality)
{
  Array < DICOMDataObject* >	*ArrayPtr, *ArrayImage;
  DICOMDataObject		*DDO;
  VR				*pVR, *vrImage, *vrs;
  char				*colorASC, name[256], charY, charCb, charCr, *inData;
  FILE				*fp;
  BOOL				oddRow, buffer, progressive;
  UINT8				colorType;
  UINT16			frames;
  register unsigned int		rowWidth;
  register int			outInt, outInt1;
  size_t			fileLength, readLength;
  int				err, t;
  unsigned int			currFrame, frameSize, inputArrayCnt;
  unsigned int			byteWidthIn, byteWidth;
  register JSAMPROW		jbuffer, jbuffer_ptr, row_pointer[3];
  JSAMPARRAY			jarray;
  struct jpeg_compress_struct	cinfo;
  struct jerror_mgr		jerr;
  JDIMENSION			width, byteCnt;

// If debug > 0, get start time.
	t=0;
  if (DebugLevel > 0)t = (unsigned int)time(NULL);
  if (DebugLevel > 1) SystemDebug.printf("JPEG compress started.\n");
// Are there frames?
  currFrame = 0;
  inputArrayCnt = 0;
// Look for the frames vr.
  if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1; // de.
// Check and set the quality for lossy.
  if(jpegQuality < MIN_QUALITY)// Set to 0 to use dicom.ini value. 
  {
    jpegQuality = gJpegQuality;//Use the default or dicom.ini value.
  }
 
  if(jpegQuality > 100) jpegQuality = 100;
// Init the default handler.
  cinfo.err = jpeg_std_error(&jerr.pub);
// change the error exit so libjpeg can't kill us.
  jerr.pub.error_exit = jerror_exit;
// Use our methode for outputting messages.
  jerr.pub.output_message = joutput_message;
    
  fp = NULL;
  if (setjmp(jerr.setjmp_buffer))
  {
/* If we get here, the JPEG code has signaled an error.
 * We need to clean up the JPEG object and return. */
    jpeg_destroy_compress(&cinfo);
    if(fp != NULL)
    {
      fclose(fp);
      unlink(name);
    }
    return (FALSE);
  }

/* Look for multi-byte version 6c (63) from www.bitsltd.net */
  jpeg_CreateCompress(&cinfo, 63,
            (size_t) sizeof(struct jpeg_compress_struct));
/* Color space must be set before a call to jpeg_set_defaults. */
  cinfo.in_color_space = JCS_RGB; //Default,just a guess
  jpeg_set_defaults(&cinfo);

/* Get all the image size stuff. */
// Get the Rows VR and check size
  if(!(cinfo.image_height = (JDIMENSION)pDDO->GetUINT(0x0028, 0x0010)))
  {
    SystemDebug.printf("***[CompressJPEGL]: failed to get image height.\n");
    jpeg_destroy_compress(&cinfo);
    return(FALSE);
  }
  if(cinfo.image_height > JPEG_MAX_DIMENSION)
  {
    OperatorConsole.printf("***[CompressJPEGL]: %d too high for the jpeg standard.\n",
        cinfo.image_height);
    jpeg_destroy_compress(&cinfo);
    return(FALSE);
  }

 // Get the Columns VR and check size.
  if(!(cinfo.image_width = (JDIMENSION)pDDO->GetUINT(0x0028, 0x0011)))
  {
    OperatorConsole.printf("***[CompressJPEGL]: failed to get image width.\n");
    jpeg_destroy_compress(&cinfo);
    return(FALSE);
  }
  if(cinfo.image_width > JPEG_MAX_DIMENSION)
  {
    OperatorConsole.printf("***[CompressJPEGL]: %d too wide for the jpeg standard.\n",
        cinfo.image_width);
    jpeg_destroy_compress(&cinfo);
    return(FALSE);
  }
// Get the number of samples per pixel VR.
  if(!(cinfo.num_components = pDDO->GetBYTE(0x0028, 0x0002)))
    cinfo.num_components = 1;  // Gray default.
  cinfo.input_components = cinfo.num_components;
// Get the number of bits allocated.
  if(!(cinfo.data_precision_other = pDDO->GetBYTE(0x0028, 0x0100)))
    cinfo.data_precision_other = 8; // 8 bit default.
// Get the number of bits stored.
  if(!(cinfo.data_precision = pDDO->GetBYTE(0x0028, 0x0101)))
    cinfo.data_precision = 8; // 8 bit default.
//  if(cinfo.data_precision > cinfo.data_precision_other)
//	cinfo.data_precision_other = cinfo.data_precision; /* the bigger one. */
  if(cinfo.data_precision_other != 8 && cinfo.data_precision_other != 12
	&& cinfo.data_precision_other != 16)
  {
	jpeg_destroy_compress(&cinfo);
	OperatorConsole.printf("***[CompressJPEGL]: Unsuported allocated bit width: %d.\n",
						   cinfo.data_precision_other);
	return(FALSE);
  }
  byteWidthIn = 1;
  if(cinfo.data_precision_other > 8) byteWidthIn = 2;
  byteWidth = 1;
  if(cinfo.data_precision > 8) byteWidth = 2;
// Set the size of each image
  frameSize = cinfo.image_width * cinfo.image_height * cinfo.num_components *  byteWidthIn;
  buffer =  FALSE;
// Set the defaults.
  colorASC = NULL;//Default gray.
  cinfo.in_color_space = JCS_GRAYSCALE;
  colorType = CLRSPC_FAM_GRAYSCALE;
  switch(cinfo.num_components)
  {
	case 1:// Leave the defaults.
		break;
	case 3:
		pVR = pDDO->GetVR(0x0028, 0x0004); // Get the color profile.
		if(pVR && pVR->Length > 2) colorASC = (char *)pVR->Data; //Might be YBR.
        cinfo.in_color_space = JCS_RGB;// Default color space.
        colorType = CLRSPC_FAM_RGB;
		break;
	default:
		jpeg_destroy_compress(&cinfo);
		OperatorConsole.printf("***[CompressJPEGL]: Unsuported number of components: %d.\n",
            cinfo.num_components );
		return(FALSE);
  }
// Other color types can be added.
  if (colorType == CLRSPC_FAM_GRAYSCALE)
  {// Leave defaults
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
	if(cinfo.data_precision_other == 12) // Byte fix time
#else//Big Endian like Apple power pc.
	if(byteWidthIn == 2) // Byte swap time
#endif //Big Endian
	buffer = TRUE;
  }
  else if (cinfo.in_color_space == JCS_RGB &&
    (colorASC == NULL || strncmp(colorASC, "RGB",3)==0))
  {// Any problems should pick here.  Leave color defaults.
// Planar configuration
    if(pDDO->GetBYTE(0x0028, 0x0006) == 1) buffer = TRUE;
  }
  else if (pVR->Length > 6 && strncmp(colorASC, "YBR_",4)==0)
  {
	if(strncmp(&colorASC[4], "ICT", 3)==0 || strncmp(&colorASC[4], "RCT", 3)==0)
	{
	  OperatorConsole.printf
          ("Warn[CompressJPEGL]: Uncompressed colorspace can not be YBR_ICT or YBR_RCT. Trying RGB\n");
	  cinfo.in_color_space = JCS_RGB;
	  colorType = CLRSPC_FAM_RGB;
	}
	else if (pVR->Length > 7 && strncmp(&colorASC[4], "FULL", 4)==0)//YBR_FULL(_422)
	{
	  cinfo.in_color_space = JCS_YCbCr;
	  buffer = TRUE;
	  if(pVR->Length > 11 && (strncmp(&colorASC[8], "_422", 4)==0))//YBR_FULL_422
          colorType = CLRSPC_FAM_YCBCR_F422;
	  else // YBR_FULL
          colorType = CLRSPC_FAM_YBR_FULL;
	}
	else if (pVR->Length > 14 && strncmp(&colorASC[4], "PARTIAL_42", 10)==0)//YBR_PARTIAL_42x
	{
	  cinfo.in_color_space = JCS_YCbCr;
	  buffer = TRUE;
	  if(colorASC[14] == '0')colorType = CLRSPC_FAM_YCBCR_420;
	  else colorType = CLRSPC_FAM_YCBCR_422;
	}
  } // End if YBR_
  else
  {
    if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
    {
	  OperatorConsole.printf(
        "***[CompressJPEGL]: Unknown or unsuported color space %s.\n",colorASC);
      free(colorASC);
    }
    else OperatorConsole.printf(
           "***[CompressJPEGL]: Unknown or unsuported color space record.\n");
	jpeg_destroy_compress(&cinfo);
    return(FALSE);
  }

// Get the data.
  pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
  vrImage = pVR;// Will test for null later.
  ArrayImage = NULL;// For warning.
  if(pVR && pVR->Length && pVR->SQObjectArray)
  {//This should not be for uncompressed.
	ArrayImage = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
	while (inputArrayCnt < ArrayImage->GetSize())
	{
	  DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
	  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data.
	  if(vrImage && vrImage->Length >= frameSize)
	  {
		OperatorConsole.printf("Warn[CompressJPEGL]:Raw image data in an encapsulation array.\n");
		break;
	  }
	}
  }
  if(!vrImage || vrImage->Length < frameSize)// Have enough data for at least 1 frame?
  {
	OperatorConsole.printf("***[CompressJPEGL]: Could not find the image data.\n");
	jpeg_destroy_compress(&cinfo);
	return (FALSE);
  }
// Use a temp file to hold the data, easier to get the compressed size(s)
  NewTempFileWExt(name, ".jpg");
  if((fp = fopen(name, "wb+")) == NULL )
  {
	OperatorConsole.printf("***[CompressJPEGL]: Could not open file %s for write.\n", name);
	jpeg_destroy_compress(&cinfo);
	return (FALSE);
  }
  jarray = &jbuffer;
  jbuffer = NULL; // Default is no buffer.
// Any compression errors from here on are handled by jerror_exit.

/* Check to see if we need a buffer, data in planes or 12 bits storage.
*  We will let libjpeg allocate it, so if any errors it will go away. */
  if(buffer) jarray = (cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_PERMANENT,
		(JDIMENSION)( cinfo.image_width * cinfo.input_components
		* byteWidthIn ) + 6, 1);//Add a little extra.
  jbuffer = *jarray;//jarray is an array of rows. We use just one.

  progressive = FALSE;
  switch(comp)
  {
	case '2':// lossless SV6 "1.2.840.10008.1.2.4.57" = jpeg 14 (33%)
		jpegQuality = 100;
		if(cinfo.data_precision > 8)cinfo.lossless = TRUE;
		comp = 2;
		break;
	case '3':// baseline   (8 bits ) "1.2.840.10008.1.2.4.50" = jpeg 1  (15%)
	case '4':// extended   (12 bits) "1.2.840.10008.1.2.4.51" = jpeg2, 4  (15%)
		if(cinfo.data_precision <= 12)// Else fall though 5 and 6 to 1.
		{
		  if(cinfo.data_precision > 8)
		  {
			cinfo.data_precision = 12;
			jpeg_set_quality(&cinfo, jpegQuality, false);
			comp = 4;
		  }
		  else
		  {
			cinfo.data_precision = 8;
			jpeg_set_quality(&cinfo, jpegQuality, true);
			comp = 3;
		  }
		  break;
		}
	case '5': // spectral sel 	"1.2.840.10008.1.2.4.53" = jpeg 8  (15%) Obsolete!
	case '6': // progressive		"1.2.840.10008.1.2.4.55" = jpeg 12 (14%) Obsolete!
		if(cinfo.data_precision <= 12)// Else fall though.
		{
		  progressive = TRUE;
		  if(cinfo.data_precision > 8)
		  {
			cinfo.data_precision = 12;
			comp = 6;
		  }
		  else
		  {
			cinfo.data_precision = 8;
			comp = 5;
		  }
		  jpeg_set_quality(&cinfo, jpegQuality, false);
		  jpeg_simple_progression(&cinfo);
		  break;
		}
	default: //default lossless SV1 "1.2.840.10008.1.2.4.70" = jpeg 14 (33%)
//16 bit jpeg id always lossless.
	  comp = 1;
	  jpegQuality = 100;
	  if(cinfo.data_precision > 8)cinfo.lossless = TRUE;// Tell 8 bit after colorspace
  }
// Setup for compress.
  cinfo.jpeg_color_space = cinfo.in_color_space;
  jpeg_default_colorspace(&cinfo);
// lossless must be set after colorspace, but color space need to know lossless if not 8 bits.
  if(comp <= 2)// Lossless J1 or J2.
  {
	cinfo.lossless = TRUE;
	cinfo.lossless_scaling = FALSE;
	if(comp == 2)jpeg_simple_lossless(&cinfo, 6, 0);//(J2)Predictor = 6, point_transform = 0
	else jpeg_simple_lossless(&cinfo, 1, 0);//(J1)Predictor = 1, point_transform = 0
  }
//  Set the obsolete progressive if called for.
  if(progressive)jpeg_simple_progression(&cinfo);
// Print out some info for debug.
  if (DebugLevel > 2)
  {
	if(cinfo.lossless)SystemDebug.printf("JPEG Lossless\n");
	else SystemDebug.printf("JPEG Lossy Quality = %d\n", jpegQuality);
	if (DebugLevel > 3)
	{
	  if(progressive)SystemDebug.printf(", progressive\n");
	  if(!buffer)SystemDebug.printf(", unbuffered data\n");
	  else SystemDebug.printf(", buffered data\n");
	}
	SystemDebug.printf(
	  ", H = %d, W = %d, Bits = %d in %d, Frames = %d, \n",
	   cinfo.image_width, cinfo.image_height, cinfo.data_precision,
	   cinfo.data_precision_other, frames);
    if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
    {
      SystemDebug.printf("color = %s\n", colorASC);
      free(colorASC);
    }
    else SystemDebug.printf("Unknown color space record.\n");
  }
// Create the encapsulation array.
  ArrayPtr = new Array < DICOMDataObject * >;
// The first blank object.
  DDO = new DICOMDataObject;
  vrs = new VR(0xfffe, 0xe000, 0, (void *)NULL, FALSE);
  DDO->Push(vrs);
  ArrayPtr->Add(DDO);
// Start the frames loop
  while(TRUE)
  {
//Start of the frame
	if( inputArrayCnt == 0)
	{
	  inData = (char *)vrImage->Data + (currFrame * frameSize);
	  if((++currFrame * frameSize) > vrImage->Length)
	  {
	    OperatorConsole.printf(
		  "Warn[CompressJPEGL]: Ran out of image data on frame %d of %d.\n", ++currFrame, frames);
	    break;
	  }
	}
	else inData = (char *)vrImage->Data;// input array, a strange world.
// Set where to put it.
	jpeg_stdio_dest(&cinfo, fp);
// Get the library ready for data.
    jpeg_start_compress(&cinfo, TRUE);
/* To send the data there are many routines used.  It is done this way for speed rather than code size.
*  I try to not have any 'if' statements in the loops.  */
    if(!buffer)// Easy way, just send.
    {
      rowWidth =  cinfo.image_width * cinfo.num_components *  byteWidthIn;
      while (cinfo.next_scanline < cinfo.image_height)
      {
        row_pointer[0] = &(((JSAMPROW)inData)[cinfo.next_scanline * rowWidth]);
        jpeg_write_scanlines(&cinfo, &row_pointer[0], 1);
      }
    }
    else // Buffered, copy time.
    {
      row_pointer[0] = (JSAMPROW)inData;
        
      switch (colorType)
            {
            case JCS_GRAYSCALE:
#if NATIVE_ENDIAN == BIG_ENDIAN // Big Endian like Apple power pc
                if(cinfo.data_precision_other == 16) // 16 Bits, byte swap time.
                    {
                    while (cinfo.next_scanline < cinfo.image_height)
                        {
                        jbuffer_ptr =jbuffer;
                        for(byteCnt = 0;byteCnt < cinfo.image_width; byteCnt++)
                            {
                            *jbuffer_ptr++ = row_pointer[0][1];
                            *jbuffer_ptr++ = *row_pointer[0]++;
                            row_pointer[0]++;
                            }
                        while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                        }
                    }
                else //Buffer, no planes == 12 Bits allocated.
                    {
#endif
    // Each loop gets two words.
                    cinfo.data_precision_other = 16;
                    oddRow =  FALSE;
                    if(cinfo.image_width & 1) oddRow = TRUE;
                    rowWidth =  cinfo.image_width >> 1;
                    if(oddRow) rowWidth++;// Get the odd bit.
                    while (cinfo.next_scanline < cinfo.image_height)
                        {
                        jbuffer_ptr =jbuffer;
                        for(byteCnt = 0;byteCnt < rowWidth; byteCnt++)
                            {
#if NATIVE_ENDIAN == BIG_ENDIAN // Big Endian like Apple power pc
                            *jbuffer_ptr = (row_pointer[0][1] && 0xF0) >> 4;
                            *jbuffer_ptr++ |= (*row_pointer[0] && 0x0F) << 4;
                            *jbuffer_ptr++ = (*row_pointer[0]++ && 0xF0) >> 4;
                            *jbuffer_ptr++ = row_pointer[0][1];
                            *jbuffer_ptr++ = (*row_pointer[0]++) && 0x0F;
                            row_pointer[0]++;
#else //Little Endian
                            *jbuffer_ptr++ = (*row_pointer[0] && 0xF0) >> 4;
                            *jbuffer_ptr = (*row_pointer[0]++ && 0x0F) << 4;
                            *jbuffer_ptr++ |= (*row_pointer[0] && 0xF0) >> 4;
                            *jbuffer_ptr++ = (*row_pointer[0]++) && 0x0F;
                            *jbuffer_ptr++ = *row_pointer[0]++;
#endif //Little Endian
                            }                
                        while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                        if(oddRow && (cinfo.next_scanline < cinfo.image_height))
                            {
                            jbuffer_ptr -= 2; //Back up over the second half of the odd.
                            for(byteCnt = 0; byteCnt < 2; byteCnt++)
                                jbuffer[byteCnt] = *jbuffer_ptr++;
                            jbuffer_ptr = jbuffer + 2;//Reset the buffer pointer.
                            for(byteCnt = 2 ;byteCnt < rowWidth; byteCnt++)
                                {
#if NATIVE_ENDIAN == BIG_ENDIAN // Big Endian like Apple power pc
                                *jbuffer_ptr++ = row_pointer[0][1];
                                *jbuffer_ptr++ = (*row_pointer[0]++) && 0x0F;
                                row_pointer[0]++;
                                *jbuffer_ptr = (row_pointer[0][1] && 0xF0) >> 4;
                                *jbuffer_ptr++ |= (*row_pointer[0] && 0x0F) << 4;
                                *jbuffer_ptr++ = (*row_pointer[0]++ && 0xF0) >> 4;
#else //Little Endian
                                *jbuffer_ptr++ = (*row_pointer[0]++) && 0x0F;
                                *jbuffer_ptr++ = *row_pointer[0]++;
                                *jbuffer_ptr++ = (*row_pointer[0] && 0xF0) >> 4;
                                *jbuffer_ptr = (*row_pointer[0]++ && 0x0F) << 4;
                                *jbuffer_ptr++ |= (*row_pointer[0] && 0xF0) >> 4;
#endif //Little Endian
                                }                
                            while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                            }
                        }
#if NATIVE_ENDIAN == BIG_ENDIAN // Big Endian like Apple power pc
                    } // 16 bit else in BIG_ENDIAN
#endif
                break;
            case JCS_RGB:// 8 bit, Planes.  Regular RGB has no buffer.
            case JCS_YCbCr:
                row_pointer[1] = row_pointer[0] + (cinfo.image_width * cinfo.image_height);
                row_pointer[2] = row_pointer[1] + (cinfo.image_width * cinfo.image_height);
                while (cinfo.next_scanline < cinfo.image_height)
                    {
                    jbuffer_ptr = jbuffer;
                    for(byteCnt = 0;byteCnt < cinfo.image_width; byteCnt ++)
                        {
                        *jbuffer_ptr++ = *row_pointer[0]++;
                        *jbuffer_ptr++ = *row_pointer[1]++;
                        *jbuffer_ptr++ = *row_pointer[2]++;
                        }                
                    while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                    }
                break;
            case CLRSPC_FAM_YCBCR_F422: // Convert to "YBR_FULL"
                width = cinfo.image_width > 1; // Done at the Cr,Cb width.
                while (cinfo.next_scanline < cinfo.image_height)
                    {
                    jbuffer_ptr = jbuffer;
                    for(byteCnt = 0;byteCnt < width; byteCnt ++)
                        {
                        *jbuffer_ptr++ = *row_pointer[0]++;//Y1
                        charY = *row_pointer[0]++;//Y2
                        *jbuffer_ptr++ = charCb = *row_pointer[0]++;// Get the colors twice
                        *jbuffer_ptr++ = charCr = *row_pointer[0]++;
                        *jbuffer_ptr++ = charY;
                        *jbuffer_ptr++ = charCb;
                        *jbuffer_ptr++ = charCr;
                        }                
                    while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                    }
                break;
            case CLRSPC_FAM_YCBCR_422:
                width = cinfo.image_width > 1; // Done at the Cr,Cb width.
                while (cinfo.next_scanline < cinfo.image_height)
                    {
                    jbuffer_ptr = jbuffer;
                    for(byteCnt = 0;byteCnt < width; byteCnt ++)
                        {
/* For Y the ratio is 256 / 220 (1.1636) and  for color 256 / 225 (1.1378).
*  Note: All values are multiplied by 1024 or 1 << 7.
*  Yo = 1.1636(Yi - 16)  == Yo = 1.1636Yi - 18.204 ==
*  Yo = [149Yi - 2330]/128 */
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y1
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y2
/*  Cxo = 1.1378(Cxi - 16)  == Cxo = 1.1378Cxi - 18.205 ==
*  Cxo = [73Cxi - 1152]/64 */
                        outInt1 = (((int)(*row_pointer[0]++)) * 73)
                            - 1152;//Cb
                        if(outInt1 & 0x8000) charCb = 0;// Neg not allowed here.
                        else if(outInt1 & 0x4000)charCb = 0xFF;// Over flow.
                        else charCb = (char)((outInt >> 6) & 0xFF);
                        outInt1 = ((((int)(*row_pointer[0]++)) >> 21) * 2440246)
                            - 37129657;//Cr
                        if(outInt1 & 0x8000) charCr = 0;// Neg not allowed here.
                        else if(outInt1 & 0x4000)charCr = 0xFF;// Over flow.
                        else charCr = (char)((outInt >> 6) & 0xFF);
                        *jbuffer_ptr++ = charCr;
// Put Y2 and Cb, Cr again.
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
                        *jbuffer_ptr++ = charCb;
                        *jbuffer_ptr++ = charCr;
                        }                
                    while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                    }
                break;
            case CLRSPC_FAM_YCBCR_420:
                width = cinfo.image_width > 1; // Done at the Cr,Cb width.
                while (cinfo.next_scanline < cinfo.image_height)
                    {
                    jbuffer_ptr = jbuffer;
                    row_pointer[1] = row_pointer[0];// Set last row
                    for(byteCnt = 0;byteCnt < width; byteCnt ++)// First row with color
                        {
/* For Y the ratio is 256 / 220 (1.1636) and  for color 256 / 225 (1.1378).
*  Note: All values are multiplied by 1024 or 1 << 7.
*  Yo = 1.1636(Yi - 16)  == Yo = 1.1636Yi - 18.204 ==
*  Yo = [149Yi - 2330]/128 */
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y1
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
/*  Cxo = 1.1378(Cxi - 16)  == Cxo = 1.1378Cxi - 18.205 ==
*  Cxo = [73Cxi - 1152]/64 */
                        outInt1 = (((int)(*row_pointer[0]++)) * 73)
                            - 1152;//Cb
                        if(outInt1 & 0x8000) charCb = 0;// Neg not allowed here.
                        else if(outInt1 & 0x4000)charCb = 0xFF;// Over flow.
                        else charCb = (char)((outInt >> 6) & 0xFF);
                        *jbuffer_ptr++ = charCb;
                        outInt1 = (((int)(*row_pointer[0]++)) * 73)
                            - 1152;//Cr
                        if(outInt1 & 0x8000) charCr = 0;// Neg not allowed here.
                        else if(outInt1 & 0x4000)charCr = 0xFF;// Over flow.
                        else charCr = (char)((outInt >> 6) & 0xFF);
                        *jbuffer_ptr++ = charCr;
// Put Y2 and Cb, Cr again.
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y2
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
                        *jbuffer_ptr++ = charCb;
                        *jbuffer_ptr++ = charCr;
                        }                
                    while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                    jbuffer_ptr = jbuffer;
                    for(byteCnt = 0;byteCnt < width; byteCnt ++)// 2nd row without color.
                        {
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y1
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
                        *jbuffer_ptr++;// Reusing the buffer let us skip over
                        *jbuffer_ptr++;// the old values and use them again.
                        outInt = (((int)(*row_pointer[0]++)) * 149)
                            - 2330;//Y2
                        if(outInt & 0x10000)*jbuffer_ptr++ = 0;// Neg not allowed here.
                        else if(outInt & 0x8000)*jbuffer_ptr++ = 0xFF;// Over flow.
                        else *jbuffer_ptr++ = (char)((outInt >> 7) & 0xFF);
                        *jbuffer_ptr++;// Reusing the buffer let us skip over
                        *jbuffer_ptr++;// the old values and use them again.
                        }                
                    while( 1 != jpeg_write_scanlines(&cinfo, jarray, 1));// Not 1, try again.
                    }
                break;
            default:// Should never get here!  Do nothing
                break;
			}
    }

// If here, finished the compression.
    jpeg_finish_compress(&cinfo);
// Time to handle errors on our own again, the file is still open and cinfo still exists.
	if(!fp)
	{
      OperatorConsole.printf("***[CompressJPEGL]: jpeglib distroyed file %s\n", name);
	  jpeg_destroy_compress(&cinfo);
      return ( FALSE );
	}
	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);
	if(-1 == (signed int)fileLength)
	{
      OperatorConsole.printf("***[CompressJPEGL]: Could not get file size for %s\n", name);
      fclose(fp);
      unlink(name);
	  jpeg_destroy_compress(&cinfo);
      return ( FALSE );
    }
    rewind(fp);

// Jpeg is encapsulated, make a new vr to encapsulate.
    vrs = new VR(0xfffe, 0xe000, 0, (void *)NULL, FALSE);
    if(!vrs->ReAlloc(fileLength))//Odd file length, ReAlloc will make it even.
    {
      OperatorConsole.printf("***[CompressJPEGL]: Failed to allocate memory.\n");
      fclose(fp);
      unlink(name);
	  jpeg_destroy_compress(&cinfo);
      return ( FALSE );
    }
//Zero the added byte, never hurts before the read.
	((BYTE *)vrs->Data)[(vrs->Length) - 1] = 0;
//Read the image data.
    readLength = fread(vrs->Data,1,fileLength,fp);
    if(readLength == 0)
    {
      err = ferror(fp);
      if(err) OperatorConsole.printf("***[CompressJPEGL]: File read error %d on %s.\n",err,name);
      else    OperatorConsole.printf("***[CompressJPEGL]: No compressed image data (0 length read).\n");
      fclose(fp);
      unlink(name);
	  jpeg_destroy_compress(&cinfo);
	  return ( FALSE );
    }
    if(readLength != fileLength)
    {
	  OperatorConsole.printf("Warn[CompressJPEGL]: Only read %d bytes of %d of the jpeg2k file:%s, will try to save\n",
         readLength, fileLength, name);
    }
	fclose(fp);//File done
// Encapsulate an image object.       
	DDO = new DICOMDataObject;        
	DDO->Push(vrs);
	ArrayPtr->Add(DDO);
	if(currFrame >= frames)break;//Finished while(TRUE) loop
//Still here, setup for the next frame
	if((fp = fopen(name, "wb+")) == NULL )//Clear the file.
	{
	  OperatorConsole.printf("***[CompressJPEGL]: Could not open file %s for write of frame %d.\n", name, currFrame + 1);
	  jpeg_destroy_compress(&cinfo);
	  return (FALSE);
	}
// Deal with silly input arrays
	if(inputArrayCnt > 0)
	{
// All in one array would be nice.
	  if((++currFrame * frameSize) > vrImage->Length)
	  {// Look for the next array
		while (inputArrayCnt < ArrayImage->GetSize())
		{
		  DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
		  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
		  if(vrImage && vrImage->Length >= frameSize) break;// Found next one, break inner loop.
		}
	  }
	  if(!vrImage || vrImage->Length < frameSize) break;// Not enough data for at least 1 frame.
	}
  }//End of while(TRUE), go back for the next frame.
  unlink(name);//Done with the file.
// All frames compressed, done with cinfo.
  jpeg_destroy_compress(&cinfo);
// Should we kill it and keep the uncompressed data?
  if(currFrame < frames) OperatorConsole.printf(
		"Warn[CompressJPEGL]: Only %d of %d frames saved.\n",currFrame, frames);
// The end object.
  DDO = new DICOMDataObject;
  vrs = new VR(0xfffe, 0xe0dd, 0, (void *)NULL, FALSE);
  DDO->Push(vrs);
  ArrayPtr->Add(DDO);
//  vrs = new VR(0x7fe0, 0x0010, 0, (void *)NULL, FALSE);
  pVR->Reset();//Clear the old image data including arrays.
  pVR->SQObjectArray = ArrayPtr;// Replace the data
  if(byteWidth > 1)pVR->TypeCode ='OW';
  else pVR->TypeCode ='OB';
// Change the transfer syntax to JPEG!
// Change the dicom parameters

// Fix the bits allocated.
  // 20120624: do not change highbit and bitsstored
  //if(byteWidth == 1)pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
  //else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

//Change the transfer syntax to JPEG!  Many choices, do it old way.
  pVR = pDDO->GetVR( 0x0002, 0x0010 );
  if(pVR)
  {
	if(pVR->Length != 22)pVR->ReAlloc(22);
  }
  else 
  {
	pVR = new VR( 0x0002, 0x0010, 22, TRUE);
    pVR->TypeCode = 'IU';
	pDDO->Push(pVR);
  }
  memcpy((char *)pVR->Data, "1.2.840.10008.1.2.4.", 20);
  switch(comp) // here was a big bug, used e.g. '2' instead of 2
  {
	case 2: memcpy(&((char *)pVR->Data)[20], "57", 2);//Lossless J2, SV6
		  break;
	case 3: memcpy(&((char *)pVR->Data)[20], "50", 2);//Lossy baseline (8 bits)
        	  break;
	case 4: memcpy(&((char *)pVR->Data)[20], "51", 2);//Lossy extended (12 bits)
		  break;
	case 5: memcpy(&((char *)pVR->Data)[20], "53", 2);// Obsolete! Progressive (8 bits)
		  break;
	case 6: memcpy(&((char *)pVR->Data)[20], "55", 2);// Obsolete! Progressive (12 bits)
		  break;
	default:  memcpy(&((char *)pVR->Data)[20], "70", 2);//Lossless J1, SV1
  }
//Change the Photometric Interpretation if needed.
  if(colorType >= CLRSPC_FAM_YCBCR_422)//Color
  {
// Reset the plane's VR, if there.
    pVR = pDDO->GetVR(0x0028, 0x0006);
    if(pVR && pVR->Length && *(char *)(pVR->Data) == 1) *(char *)(pVR->Data = 0);
// Set the color profile
    pDDO->ChangeVR( 0x0028, 0x0004, "YBR_FULL\0", 'CS');// Jpeg standard
  }
  if (DebugLevel > 0)
		SystemDebug.printf("JPEG compress time %u seconds.\n", (unsigned int)time(NULL) - t);
  return (TRUE);
}

/* This is a replacement for the get more data for the buffer routine.
*  Because it is passed the whole image, it should never ask for more. */
METHODDEF(boolean)
jfill_input_buffer (j_decompress_ptr cinfo)
{
/* Passed libjpeg the whole image, there is no more data, error exit */
  OperatorConsole.printf("***[LIBJPEG]: Ran out of data in image.\n");
  ERREXIT(cinfo, JERR_INPUT_EOF);

  return TRUE;
}

/* This was taken directly from the library with the error message changed. */
METHODDEF(void)
jskip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
  jpeg_source_mgr *src = cinfo->src;

  /* Just a dumb implementation for now.  Could use fseek() except
   * it doesn't work on pipes.  Not clear that being smart is worth
   * any trouble anyway --- large skips are infrequent.
   */
  if (num_bytes > 0)
  if (num_bytes > (long) src->bytes_in_buffer)
  {
    OperatorConsole.printf("***[LIBJPEG]: Tried to skip past the end of the image.\n");
    ERREXIT(cinfo, JERR_INPUT_EOF);
  }
  src->next_input_byte += (size_t) num_bytes;
  src->bytes_in_buffer -= (size_t) num_bytes;
}

/* This routine will take in a jpeg image and convert it to little endian, uncompressed,
*  RGB or YBR_FULL format.  RGB and YBR_FULL is the IJG standard output for the Jpeg-6b
*  library used everywhere.  As stated before, I did not use the Jpeg-6b version because
*  it had to be compiled for 8, 12 or 16 only.  So I wrote Jpeg-6c that can change bit
*  width on the fly.  You can get it here:
*  http://www.bitsltd.net/Software/Software-Repository/index.php
*  If I have made some mistakes (most likely) you can contact me bruce.barton
*  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
*  the image that didn't work. */
BOOL DecompressJPEGL(DICOMDataObject* pDDO)
{
  Array < DICOMDataObject	*>	*ArrayPtr;
  DICOMDataObject             *DDO;
  VR                          *pVR, *vrImage;
  char                        *uncompImagPtr, *uncompImageBptr;
  char                        *outImageBptr;
  UINT16                      frames;
  unsigned int                outBytes, currFrame, currSQObject;
  size_t                      imageLen;
  BOOL                        color, leExplict;
  int                         t;
// libjpeg stuff
  JSAMPARRAY16                    outBuffer;
  JDIMENSION                      num_scanlines, row, rowWidth, pixcnt;
  struct jpeg_decompress_struct   cinfo;
  struct jerror_mgr               jerr;
	
// If debug > 0, get start time.
  t = 0;
  if (DebugLevel > 0)t = (unsigned int)time(NULL);
  if (DebugLevel > 1) SystemDebug.printf("JPEG decompress started.\n");
  leExplict = TRUE; // Only changed by FUJI_FIX
  uncompImagPtr = NULL;//Output data memory.
  color = FALSE;
// Are there frames?
  if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1;
  currFrame = 0;
// Get the encapsulated data, unless Fuji.
  pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
  if(!pVR)
  {
	OperatorConsole.printf("***[DecompressJPEGL]: No image VR\n");
	return (FALSE);
  }
  currSQObject = 0;// Init now for no warning later.
  vrImage = pVR;// Init now for no warning later, will use if Fuji fix.
  ArrayPtr = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
  if(ArrayPtr)
  {
	while(TRUE)
	{
	  if( currSQObject >= ArrayPtr->GetSize())
	  {
		OperatorConsole.printf("***[DecompressJPEGL]: No jpeg data found\n");
		return (FALSE);
	  }
	  DDO = ArrayPtr->Get(currSQObject );//Get the array.
	  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
//Look for size and jpeg SOI marker 
	  if((vrImage->Length) && ((unsigned char *)vrImage->Data)[0] == 0xFF &&
			   ((unsigned char *)vrImage->Data)[1] == 0xD8)break;
	  currSQObject++;
	}
  }
  else
  {
#ifdef FUJI_FIX
// Look for a Jfif header. (LittleEndianImplicit, jpeg compressed,not encapsulated, how evil)
	  if (((unsigned char *)pVR->Data)[0] == 0xFF && ((unsigned char *)pVR->Data)[1] == 0xD8 && ((unsigned char *)pVR->Data)[2] == 0xFF
		&& ((unsigned char *)pVR->Data)[3] == 0xE0 && ((char *)pVR->Data)[4] == 0x00 && ((char *)pVR->Data)[5] == 0x10
		&& strncmp(&(((char *)pVR->Data)[6]),"JFIF", 4) == 0)
	  {
		SystemDebug.printf("Warn[DecompressJPEGL]: Applying Fuji Fix\n");
		leExplict = FALSE;
	  }
	  else
	  {
#else
		OperatorConsole.printf("***[DecompressJPEGL]: No image VR array\n");
		return (FALSE);
#endif
#ifdef FUJI_FIX
	  }
#endif
  }
// Init the default handler
  cinfo.err = jpeg_std_error(&jerr.pub);
// change the error exit so libjpeg can't kill us
  jerr.pub.error_exit = jerror_exit;
// Use our methode for outputting messages.
  jerr.pub.output_message = joutput_message;
    
  if (setjmp(jerr.setjmp_buffer))
  {
// If we get here, the JPEG code has signaled an error.
// We need to clean up the JPEG object and return.
	jpeg_destroy_decompress(&cinfo);
	if(uncompImagPtr != NULL) free(uncompImagPtr);
	return (FALSE);
  }

// Look for multi-byte version 6c (63) from www.bitsltd.net
  jpeg_CreateDecompress(&cinfo, 63,
		(size_t) sizeof(struct jpeg_decompress_struct));
// Set the source
  cinfo.src = (struct jpeg_source_mgr *)
      (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo, JPOOL_PERMANENT,
			sizeof(struct jpeg_source_mgr));
  cinfo.src->init_source = jdoes_nothing;
  cinfo.src->skip_input_data = jskip_input_data;
  cinfo.src->resync_to_restart = jpeg_resync_to_restart; // use default method
  cinfo.src->term_source = jdoes_nothing; /* term_source does nothing
// Pass the whole image, so this is an error that should not happen. */
  cinfo.src->fill_input_buffer = jfill_input_buffer;
// Get data for the first or only frame
  cinfo.src->bytes_in_buffer = vrImage->Length; // forces fill_input_buffer on first read
  cinfo.src->next_input_byte = (JOCTET *)vrImage->Data; // Image buffer
// find out what we have.
  jpeg_read_header(&cinfo, TRUE);
// Set all of the cinfo information.
  jpeg_calc_output_dimensions(&cinfo);
// The default is 8 bits, set it to the image size.
  cinfo.data_precision_other =cinfo.data_precision;
  if (cinfo.out_color_components != 1)
  {
	if(cinfo.out_color_components!=3)
	{
	  OperatorConsole.printf(
          "***[DecompressJPEGL]: Not grayscale, RGB or YCbCr. Number of components = %d\n",
          cinfo.out_color_components);
	  jpeg_destroy_decompress(&cinfo);
	  return (FALSE);
	}
	color = TRUE;
  }
// Time to make an output image buffer.
  if(cinfo.data_precision_other > 8) outBytes = 2;
  else outBytes = 1;
  rowWidth =  cinfo.output_width * cinfo.output_components * outBytes;
  imageLen = rowWidth * cinfo.output_height * frames;
  if ( imageLen & 1 ) imageLen++;//Odd length, make it even.
  if(!(uncompImagPtr = (char*)malloc(imageLen)))
  {
	OperatorConsole.printf(
        "***[DecompressJPEGL]: Could not allocate decompressed image memory.\n");
	jpeg_destroy_decompress(&cinfo);
	return (FALSE);
  }
  uncompImagPtr[imageLen - 1] = 0; // In the case of an odd length.
  outImageBptr = uncompImagPtr;
/*  The size of a pixel is JSAMPLE16, 16 bits, no matter what the size of the original data.
    This is done because the size of the data in the jpeg image is not known to the library until 
    jpeg_read_header(). So if the buffer is 8 bit, the library will create an internal 16 bit
    buffer to hold the image data and copy it to the smaller buffer wasting time. 
    So just make a 16 bit buffer array now the height of DCTSIZE (jpeg standard = 8). */
  outBuffer = (JSAMPARRAY16)(*cinfo.mem->alloc_sarray)
	((j_common_ptr) &cinfo,  JPOOL_PERMANENT,//JPOOL_IMAGE,
      (JDIMENSION) cinfo.output_width * cinfo.output_components
        * sizeof(JSAMPLE16), (JDIMENSION) cinfo.rec_outbuf_height);
  if(!outBuffer)
  {
	OperatorConsole.printf(
        "***[DecompressJPEGL]: Libjpeg could not allocate image buffer memory.\n");
	jpeg_destroy_decompress(&cinfo);
	return (FALSE);
  }
// Start the frames loop.
  while(TRUE)
  {
// The library will convert the internal YCbCr to RGB.
  if (color) cinfo.out_color_space = JCS_RGB;
  else cinfo.out_color_space = JCS_GRAYSCALE;
// Ready to decompress 
	jpeg_start_decompress(&cinfo);
// Tell libjpeg we will use a 16 bit buffer
	cinfo.buffer_size_char = FALSE;
// Never scale.
	cinfo.shft = 0;
// read the Image loop
	while (cinfo.output_scanline < cinfo.output_height)
	{
	  num_scanlines = jpeg_read_scanlines(&cinfo,(JSAMPARRAY) outBuffer, 
			(JDIMENSION) cinfo.rec_outbuf_height);
	  for(row = 0; row < num_scanlines; row++)
	  {
		uncompImageBptr = (char *)outBuffer[row];
		if (outBytes == 1)// char
		{
		  for( pixcnt = 0; pixcnt < rowWidth;  pixcnt++)
		  {
#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian like PPC
			uncompImageBptr++;
#endif
			*outImageBptr++ = *uncompImageBptr++;
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
			uncompImageBptr++;
#endif
		  }
		}
		else //words
		{ /* Row with is 2 x, MSB, LSB */
		  for( pixcnt = 0; pixcnt < rowWidth;  pixcnt++)
		  {
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
			*outImageBptr++ = *uncompImageBptr++;
	#else //Big Endian like PPC
			*outImageBptr++ = uncompImageBptr[1];
			*outImageBptr++ = *uncompImageBptr++;
			uncompImageBptr++;
			pixcnt++;
	#endif
		  }
		}
	  }
	}
	jpeg_finish_decompress(&cinfo);
// check for the end
	if( ++currFrame >= frames )break;
// More images to read
	while(++currSQObject <= ArrayPtr->GetSize())
	{
	  DDO = ArrayPtr->Get(currSQObject);//Get the array.
	  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
//Look for size and jpeg SOI marker 
	  if(vrImage->Length && ((unsigned char *)vrImage->Data)[0] == 0xFF &&
			  ((unsigned char *)vrImage->Data)[1] == 0xD8)break;
	}
	if( currSQObject >= ArrayPtr->GetSize() )break;//Should not happen!
// OK, have another image now, reset decompressor
// Get data for next frame
	cinfo.src->bytes_in_buffer = vrImage->Length; // forces fill_input_buffer on first read
	cinfo.src->next_input_byte = (JOCTET *)vrImage->Data; // Image buffer
// Read the new header, nothing should change (should we check?)
	jpeg_read_header(&cinfo, TRUE);
// The default is 8 bits, set it back to the image size.
	cinfo.data_precision_other =cinfo.data_precision;
  }// Loop back to jpeg_start_decompress (while(TRUE))
  if(currFrame < frames)OperatorConsole.printf(
	"Warn[DecompressJPEGL]: Found %d of %d frames.\n",currFrame, frames);
// Should have image(s) here, time to save it.
  pVR->Reset();// Remove old data.
  if(outBytes == 2) pVR->TypeCode ='OW';
  else pVR->TypeCode ='OB';
// Set it to the image data.
  pVR->Data = uncompImagPtr;
// Tell it how long.
  pVR->Length = imageLen;
// Give it responsible for it.
  pVR->ReleaseMemory = TRUE;
//  pDDO->DeleteVR(pVR);// replace the pixel data: corrupts LastVRG
//  pDDO->Push(vrs);
// Set the number of bits allocated.

  // Need to fix Philips Gyroscan that stores 8 in 16 (now 8 in 8).
  // 20120624: do not change highbit and bitsstored
  //if(cinfo.data_precision <= 8) pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
  //  else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

// Should not be needed, but never hurts.
// mvh, 20110502: DecompressJPEGL either not write 0x0101 (bitstored), or write both 0x0101 and 0x0102 (bitsstored/highbit)
// mvh, 20110502: need to write highbit for consistency if writing bitstored

  // 20120624: do not change highbit and bitsstored
  //pDDO->ChangeVR( 0x0028, 0x0101, (UINT8)cinfo.data_precision, 'US');
  //pDDO->ChangeVR( 0x0028, 0x0102, (UINT8)(cinfo.data_precision-1), 'US');

// Done with libjpeg
  jpeg_destroy_decompress(&cinfo);
//Change the Photometric Interpretation.
  if(color)
  {
//Set Planes value if needed, do  not create if not there.
    pVR = pDDO->GetVR(0x0028, 0x0006);
    if(pVR && pVR->Length && *(char *)pVR->Data == 1)
      *(char *)pVR->Data = 0;
//Change the Photometric Interpretation.
    pDDO->ChangeVR( 0x0028, 0x0004, "RGB\0", 'CS');
  }
//Change the transfer syntax to LittleEndianExplict!
  if(leExplict)// Only false for FUJI_FIX w/ Fuji Image
    pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.1\0", 'IU');
// If debug > 0, print decompress time.
  if (DebugLevel > 0)
    SystemDebug.printf("JPEG decompress time %u seconds.\n", (unsigned int)time(NULL) - t);
// Done!          
  return(TRUE);
}
#endif//End HAVE_LIBJPEG
#ifdef HAVE_LIBJASPER
/* This routine will take all of the listed color spaces in 08_03 of the standard
*  in little endian, uncompressed format and  compress it to jpeg2000 in whatever
*  format it came in.  I don't know if dicom viewers can support this.  It uses the
*  Jasper library by Michael D. Adams from the Department of Electrical and
*  Computer Engineering at the University of Victoria.  You can get it here:
*  http://www.ece.uvic.ca/~mdadams/jasper/
*  You can also get it here with a few minor changes to use the my Jpeg-6c
*  library, but none of the changes are used by dgate: 
*  http://www.bitsltd.net/Software/Software-Repository/index.php
*  Jasper can compress anything, with any size for each plane, but the standard only
*  allows YBR_RCT lossless and YBR_ICT lossy.  So if a YBR come in, it is lossy, and
*  RGB is lossless.  If this is a problem I can  add a forced change in colorspace.
*  If I have made some mistakes (most likely), you can contact me bruce.barton
*  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
*  the image that didn't work. */
BOOL CompressJPEG2K(DICOMDataObject* pDDO, int j2kQuality)
{
  Array < DICOMDataObject	*>	*ArrayPtr, *ArrayImage;
  DICOMDataObject             *DDO;
  VR                          *pVR, *vrImage, *vrs;
  jas_stream_t                *out;
  jas_image_t                 *image;
  jas_image_cmpt_t            *cmpt;
  jas_image_coord_t           byteCnt, rowCnt, size;
  FILE                        *fp;
  UINT8                       bitwa, prec, colorTypeIn, sgnd;
  UINT16                      cmptno;
  char                        *colorASC, name[256], *brcrBuffer, *bufferPtr;
  char                        *colorBuffer_ptr[3], *colorBuffer[3];
  char                        *buffer_ptr, option[20];
  int                         fileLength, lengthRead, tempInt, err;
  unsigned int				  currFrame, frames, t, inputArrayCnt, byteWidthIn, byteWidth;
  BOOL                        planes, buffers;
    
// If debug > 0, get start time and set the level.
  t = 0;
  if (DebugLevel > 0)
  {
	t = (unsigned int)time(NULL);
	jas_setdbglevel(DebugLevel);
  }
  if (DebugLevel > 1) SystemDebug.printf("Jasper compress started.\n");
  buffers = FALSE;
  inputArrayCnt = 0;
// Uninitialized warnings.
  ArrayImage = NULL;
  brcrBuffer = NULL;
  cmpt = NULL;
// Check and set the quality for lossy.
  if(j2kQuality < MIN_QUALITY)// Set to 0 to use dicom.ini value. 
  {
	j2kQuality = gJpegQuality;//Use the default or dicom.ini value.
  }
  if(j2kQuality > 100) j2kQuality = 100;
// Init the jasper library.
  if(jas_init())
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Cannot init the jasper library\n");
	return (FALSE);
  }
	/* Created from jas_image_create and jas_image_create0.
*  It was done so the buffers are not allocated if not needed. */
  if (!(image = (jas_image_t *)malloc(sizeof(jas_image_t)))) 
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Could not allocate an image structure.\n");
	return (FALSE);
  }
// Set the some defaults for the outer box.
  image->tlx_ = 0;
  image->tly_ = 0;
  image->clrspc_ = JAS_CLRSPC_UNKNOWN;
  image->numcmpts_ = 0;//Set later
// Get the number of samples per pixel VR.
  if(!(image->maxcmpts_ = pDDO->GetBYTE(0x0028, 0x0002))) image->maxcmpts_ = 1;
// Are there frames?
  if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1;
  currFrame = 0;
// Get the Rows VR and check size
  if(!(image->bry_ = pDDO->GetUINT(0x0028, 0x0010)))
  {
	SystemDebug.printf("***[CompressJPEG2K]: Failed to get image height.\n");
	free(image);
	return(FALSE);
  }
// Get the Columns VR and check size.
  if(!(image->brx_ = pDDO->GetUINT(0x0028, 0x0011)))
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Failed to get image width.\n");
	free(image);
	return(FALSE);
  }
  byteWidth = 1;
  byteWidthIn = 1;
  if(!(bitwa = pDDO->GetBYTE(0x0028, 0x0100)))bitwa = 8; // 8 bit default.
  if(!(prec = pDDO->GetBYTE(0x0028, 0x0101)))prec = bitwa; // the default.
  if(prec > bitwa)bitwa = prec;// the bigger one.
  if(prec > 8)byteWidth = 2;// Will fix 8 in 16 with a buffer.
  if(bitwa > 8)byteWidthIn = 2;
// Check if we can do it
  if(bitwa != 8 && bitwa != 12  && bitwa != 16)
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Unsuported allocated bit width: %d.\n", bitwa);
	free(image);
	return(FALSE);
  }
// Checked if the data is signed,
  if(!(sgnd = pDDO->GetBYTE(0x0028, 0x0103)))sgnd = 0;
// Set the image or buffer size
  size = image->brx_ * image->bry_ * byteWidth;
// Planar configuration default.
  planes = FALSE;
// Sort colors.
  colorTypeIn = image->clrspc_ = JAS_CLRSPC_FAM_GRAY;// The default
  colorASC = NULL;
  if(image->maxcmpts_ == 1)
  {
	planes = TRUE;//Just 1 plane.
  }
  else if(image->maxcmpts_ == 3)
  {
    pVR = pDDO->GetVR(0x0028, 0x0004); // Get the color profile
	if(pVR && pVR->Length > 2) colorASC = (char *)pVR->Data;
// Look for the color type
	if(colorASC == NULL || strncmp(colorASC, "RGB",3)==0)// RGB
	{// Only RGB can be in planes or R,G,B format, check.
	  if(pDDO->GetBYTE(0x0028, 0x0006)) planes = TRUE;; // Check planes.
/*	  pVR = pDDO->GetVR(0x0028, 0x0006); // Get the plane's VR.
	  if(pVR && pVR->Length && (*(char *)(pVR->Data) == 1)) planes = TRUE;*/
	  colorTypeIn = image->clrspc_ = JAS_CLRSPC_FAM_RGB;
	}
	else if (pVR->Length > 6 && strncmp(colorASC, "YBR_",4)==0)
	{
	  image->clrspc_ = JAS_CLRSPC_FAM_YCBCR;
	  if ((strncmp(&colorASC[4], "ICT",3)==0)  || (strncmp(&colorASC[4], "RCT",3)==0))
	  {
		OperatorConsole.printf
             ("Warn[CompressJPEG2K]: Uncompressed colorspace can not be YBR_ICT or YBR_RCT. Trying RGB\n");
		colorTypeIn = image->clrspc_ = JAS_CLRSPC_FAM_RGB;
	    planes = FALSE;
	  }
	  if (pVR->Length > 7 && strncmp(&colorASC[4], "FULL",4)==0)// YBR_FULL(_422)
	  {
		if (pVR->Length > 11 && strncmp(&colorASC[8], "_422",4)==0)// YBR_FULL_422
		{
		  colorTypeIn = CLRSPC_FAM_YCBCR_F422;
		  planes = FALSE;
		}
		else// YBR_FULL
		{
		  colorTypeIn = JAS_CLRSPC_FAM_YCBCR;
		  planes = TRUE;
		}
	  }
	  if (pVR->Length > 14 && strncmp(&colorASC[4], "PARTIAL_42",10)==0)// YBR_PARTIAL_42x
	  {
		planes = FALSE;
		if(colorASC[14] == '0')colorTypeIn = CLRSPC_FAM_YCBCR_420;
		else colorTypeIn = CLRSPC_FAM_YCBCR_422;
	  }
	}// End of YBR_
// Add more colors here.
	else
	{
      if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
      {
	    OperatorConsole.printf(
          "***[CompressJPEGL]: Unknown or unsuported color space %s.\n",colorASC);
        free(colorASC);
      }
      else OperatorConsole.printf(
             "***[CompressJPEGL]: Unknown or unsuported color space record.\n");
	  free(image);
      return (FALSE);
    }
  }//image->maxcmpts_ == 3
  else
  {
    OperatorConsole.printf("***[CompressJPEG2K]: Unsupported number of components %d.\n",image->maxcmpts_);
    free(image);
    return (FALSE);
  }
// Get the data.
  pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
  vrImage = pVR;
  if(pVR && pVR->Length)
  {
    if(pVR->SQObjectArray)
    {//This should not be for uncompressed.
       ArrayImage = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
       while (inputArrayCnt < ArrayImage->GetSize())
	  {
          DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
          vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data.
          if(vrImage && vrImage->Length >= 
            (unsigned int)(image->brx_ * image->bry_ * byteWidthIn * image->maxcmpts_)) break;
	  }
    }
  }
// Check for a least one frame.
  if(!vrImage || vrImage->Length < (unsigned int)(size * image->maxcmpts_))
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Could not find the image data.\n");
	free(image);
	return (FALSE);
  }
  buffer_ptr = (char *)vrImage->Data;
/*#if NATIVE_ENDIAN == LITTLE_ENDIAN // Little Endian
    if((planes || (image->maxcmpts_ == 1)) && ((bitwa == 8) || (bitwa == 16)))
#else // Big Endian like Apple power pc*/
  if((planes || (image->maxcmpts_ == 1)) && (bitwa == 8))
//#endif
  {// No need for buffers, just pointers
	for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
	{
	  colorBuffer[cmptno] = buffer_ptr + (size * cmptno) ;
	  colorBuffer_ptr[cmptno] = colorBuffer[cmptno];
	}
  }
  else// Buffers are needed.
  {
	for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
	{
	  if(!(colorBuffer[cmptno] = (char *)malloc(size)))
	  {
		OperatorConsole.printf(
				"***[CompressJPEG2K]: Could not allocate a %d byte image buffer #%d.\n",
				size, cmptno);
		while(cmptno > 0) free(colorBuffer[--cmptno]);
		free(image);
		return (FALSE);
	  }
	  colorBuffer_ptr[cmptno] = colorBuffer[cmptno];
	}
	if(colorTypeIn == CLRSPC_FAM_YCBCR_420)
	{
	  if(!(brcrBuffer = (char *)malloc(image->brx_)))
	  {
		OperatorConsole.printf(
					"***[CompressJPEG2K]: Could not allocate a %d byte image 420 buffer.\n",
					image->brx_);
		while(cmptno > 0) free(colorBuffer[--cmptno]);
		free(image);
		return (FALSE);
	  }
	}
	buffers = TRUE;
  }
// Allocate memory for the per-component pointer table.
  if (!(image->cmpts_ = ((jas_image_cmpt_t **)jas_malloc(image->maxcmpts_ *
		sizeof(jas_image_cmpt_t *)))))
  {
	OperatorConsole.printf("***[CompressJPEG2K]: Could not create component pointers.\n");
	if(buffers)
	{
	  for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
	  {
		if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		colorBuffer[cmptno] =NULL;
	  }
	  if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	}
	free(image);
	return (FALSE);
  }
// Initialize in case of failure so jas_image_destroy can be used.
  for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
        image->cmpts_[cmptno] = 0;
  image->inmem_ = TRUE;
  image->cmprof_ = 0;
// Allocate memory for the per-component information and init.
  for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
  {
	if (!(cmpt = (jas_image_cmpt_t *)jas_malloc(sizeof(jas_image_cmpt_t))))
	{
	  jas_image_destroy(image);
	  OperatorConsole.printf("***[CompressJPEG2K]: Could not create empty components.\n");
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->maxcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
			colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  return (FALSE);
	}
	image->cmpts_[cmptno] =cmpt;
	cmpt->type_ = JAS_IMAGE_CT_UNKNOWN;//Set next.
	cmpt->tlx_ = 0;
	cmpt->tly_ = 0;
	cmpt->hstep_ = 1;
	cmpt->vstep_ = 1;
	cmpt->width_ = image->brx_;
	cmpt->height_ = image->bry_;
	cmpt->prec_ = prec;
	cmpt->sgnd_ = sgnd;
	cmpt->stream_ = 0;
	cmpt->cps_ = byteWidth;
	if(!(cmpt->stream_ = jas_stream_memopen( colorBuffer[cmptno], size)))
	{
	  jas_free(cmpt);
	  jas_image_destroy(image);
	  OperatorConsole.printf("***[CompressJPEG2K]: Jasper could not open the memory as stream.\n");
	  if(buffers)
	  {
		for (; cmptno < image->maxcmpts_; ++cmptno)// From curr # forward
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  return (FALSE);
	}
	++(image->numcmpts_);
  }
// Now set the color type
  switch (image->clrspc_)
  {
	case JAS_CLRSPC_FAM_GRAY:
		jas_image_setclrspc(image, JAS_CLRSPC_SGRAY);
		jas_image_setcmpttype(image, 0, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_GRAY_Y));
		break;
	case JAS_CLRSPC_FAM_RGB:
		jas_image_setclrspc(image, JAS_CLRSPC_SRGB);
		jas_image_setcmpttype(image, 0,
								JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R));
		jas_image_setcmpttype(image, 1,
								JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G));
		jas_image_setcmpttype(image, 2,
								  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B));
		break;
	default:
		jas_image_setclrspc(image, JAS_CLRSPC_SYCBCR);
		jas_image_setcmpttype(image, 0,
								JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_Y));
		jas_image_setcmpttype(image, 1,
								JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_CB));
		image->cmpts_[1]->sgnd_ = TRUE;
		jas_image_setcmpttype(image, 2,
								JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_CR));
		image->cmpts_[2]->sgnd_ = TRUE;
  }
// Lossy (ICT) or lossless (RCT)?
  if((j2kQuality < 100) || (image->clrspc_ == JAS_CLRSPC_FAM_YCBCR))
  {
	if(j2kQuality >= 100)j2kQuality = 95;
	memcpy(option, "mode=real rate=0.", 17);
	option[17] = (j2kQuality / 10) + '0';//ICT j2kQuality msb
	option[18] = (j2kQuality % 10) + '0';//ICT j2kQuality lsb
	option[19] = 0;//end the string.
	if (DebugLevel > 2)SystemDebug.printf("JPEG2K Lossy Quality = %d\n", j2kQuality);
  }
  else
  {
	memcpy(option, "mode=int\0", 9);//RCT
	if (DebugLevel > 2)SystemDebug.printf("JPEG2K Lossless\n");
  }
// Use a temp file to hold the data, easier to get the compressed size.
  NewTempFileWExt(name, ".j2k");
// Print out some more info for debug.
  if (DebugLevel > 2)
  {
	if (DebugLevel > 3)
	{
	  if(!buffers)SystemDebug.printf(", unbuffered data\n");
	  else SystemDebug.printf(", buffered data\n");
	  if(planes)SystemDebug.printf(", planes\n");
	}
	SystemDebug.printf(
	  ", H = %d, W = %d, Bits = %d in %d, Frames = %d, \n",
	  image->brx_, image->brx_, prec, bitwa, frames);
    if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
    {
      SystemDebug.printf("color = %s\n", colorASC);
      free(colorASC);
    }
    else SystemDebug.printf("Unknown color space record.\n");
  }
// Create the encapsulation array.
  ArrayPtr = new Array < DICOMDataObject * >;
// The first blank object.
  DDO = new DICOMDataObject;
  vrs = new VR(0xfffe, 0xe000, 0, (void *)NULL, FALSE);
  DDO->Push(vrs);
  ArrayPtr->Add(DDO);	
// Frames loop.
  while(TRUE)
  {
	if(buffers)
	{
// Now to fill the buffers.
	switch(colorTypeIn)
	  {
		case JAS_CLRSPC_FAM_GRAY://12 or 12,16 bits here
/* For sone reason jasper wants the data in big endian on both a LE and BE system.
*  There may be an option switch for this, but I just swpped endian. */
			if(bitwa == 16) // 16 Bits, byte swap time.
			{
			  if(prec > 8) //Just swap.
			  {
				for(byteCnt = 0; byteCnt < size; byteCnt++)
				{
				  byteCnt++;// 2 bytes per pixel.
				  *colorBuffer_ptr[0]++ = buffer_ptr[1];
				  *colorBuffer_ptr[0]++ = *buffer_ptr++;
				  buffer_ptr++;
			    }
			    break;
			  }
			  for(byteCnt = 0; byteCnt < size; byteCnt++)//Only need 8.
			  {
				*colorBuffer_ptr[0]++ = *buffer_ptr++;
				buffer_ptr++;// Skip the zero byte.
			  }
			  break;
			}
			else
			  for(byteCnt = 0; byteCnt < size; byteCnt++)//12 bit
			  {
				colorBuffer_ptr[0][1] = (*buffer_ptr & 0xF0) >> 4;//8-11
				*colorBuffer_ptr[0] = (*buffer_ptr++ & 0x0F) << 4;//4-7
				*colorBuffer_ptr[0]++ |= (*buffer_ptr & 0xF0) >> 4;//0-3
				colorBuffer_ptr[0]++;
				byteCnt++;
				if(byteCnt >= size)break;
				colorBuffer_ptr[0][1] = *buffer_ptr++ & 0x0F;//8-11
				byteCnt++; 
				*colorBuffer_ptr[0]++ = *buffer_ptr++;//0-7
				colorBuffer_ptr[0]++;
				byteCnt++;
			  }
			  break;
		case JAS_CLRSPC_FAM_RGB:
		  for(byteCnt = 0; byteCnt < size; byteCnt++)
		  {
			*(colorBuffer_ptr[0])++ = *buffer_ptr++;
			*(colorBuffer_ptr[1])++ = *buffer_ptr++;
			*(colorBuffer_ptr[2])++ = *buffer_ptr++;
		  }
		  break;
		case CLRSPC_FAM_YCBCR_F422://Y1Y2CbCr
		  for(byteCnt = 0; byteCnt < size; byteCnt++)
		  {
			byteCnt++;// 2 Ys per pixel.
			*colorBuffer_ptr[0]++ = *buffer_ptr++;
			*colorBuffer_ptr[0]++ = *buffer_ptr++;
			*colorBuffer_ptr[1]++ = *buffer_ptr;
			*colorBuffer_ptr[1]++ = *buffer_ptr++;
			*colorBuffer_ptr[2]++ = *buffer_ptr;
			*colorBuffer_ptr[2]++ = *buffer_ptr++;
		  }
		  break;
		case CLRSPC_FAM_YCBCR_422://Y1Y2CbCr
		  for(byteCnt = 0; byteCnt < size; byteCnt++)
		  {
			  byteCnt++;// 2 Ys per pass.
/* For Y the ratio is 256 / 220 (1.1636) and  for color 256 / 225 (1.1378).
*  Note: All values are multiplied by 1024 or 1 << 7.
*  Yo = 1.1636(Yi - 16)  == Yo = 1.1636Yi - 18.204 ==
*  Yo = [149Yi - 2330]/128 */
			  tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1
			  buffer_ptr++;
			  if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
			  else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
			  else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
			  tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y2
			  buffer_ptr++;
			  if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
			  else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
			  else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
/*  Cxo = 1.1378(Cxi - 16)  == Cxo = 1.1378Cxi - 18.205 ==
*  Cxo = [73Cxi - 1152]/64 */
			  tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
			  buffer_ptr++;
			  if(tempInt & 0x8000)
			  {
				*colorBuffer_ptr[1]++ = 0;//Negitive
				*colorBuffer_ptr[1]++ = 0;//Negitive
			  }
			  else if(tempInt & 0x4000)
			  {
				*colorBuffer_ptr[1]++ = 0xFF;//Over
				*colorBuffer_ptr[1]++ = 0xFF;//Over
			  }
			  else
			  {
				*colorBuffer_ptr[1] = (char)((tempInt >> 6) & 0xFF);
				*colorBuffer_ptr[1]++ = *colorBuffer_ptr[1];
				*colorBuffer_ptr[1]++;
			  }
			  tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
			  buffer_ptr++;
			  if(tempInt & 0x8000)
			  {
				*colorBuffer_ptr[2]++ = 0;//Negitive
				*colorBuffer_ptr[2]++ = 0;//Negitive
			  }
			  else if(tempInt & 0x4000)
			  {
				*colorBuffer_ptr[2]++ = 0xFF;//Over
				*colorBuffer_ptr[2]++ = 0xFF;//Over
			  }
			  else
			  {
				*colorBuffer_ptr[2] = (char)((tempInt >> 6) & 0xFF);
				*colorBuffer_ptr[2]++ = *colorBuffer_ptr[1];
				*colorBuffer_ptr[2]++;
			  }
			}
			break;
// What a strange standard. See page 323 of 08_03pu.pdf.
		case CLRSPC_FAM_YCBCR_420://Y1CrCbY2Y3CrCbY4-Y1Y2Y3Y4?
			for(rowCnt = 0; rowCnt < image->bry_; rowCnt++)// 8 bit only.
			{
			  rowCnt++;// 2 Ys per vertical pass.
			  bufferPtr = brcrBuffer;
			  for(byteCnt = 0; byteCnt < image->brx_; byteCnt++)
			  {
				byteCnt++;// 2 Ys per horizantal pass.
				tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
				buffer_ptr++;
				if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
				else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
				else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
				tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
				buffer_ptr++;
				if(tempInt & 0x8000)
				{
				  *bufferPtr++ = 0;//Next time negitive = 0
				  *colorBuffer_ptr[1]++ = 0;//Negitive
				  *colorBuffer_ptr[1]++ = 0;//Negitive
				}
				else if(tempInt & 0x4000)
				{
				  *bufferPtr++ = 0xFF;//Next time over = 255
				  *colorBuffer_ptr[1]++ = 0xFF;//Over
				  *colorBuffer_ptr[1]++ = 0xFF;//Over
				}
				else
				{
				  *bufferPtr = (char)((tempInt >> 6) & 0xFF);
				  *colorBuffer_ptr[1]++ = *bufferPtr;
				  *colorBuffer_ptr[1]++ = *bufferPtr++;
				}
				tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
				buffer_ptr++;
				if(tempInt & 0x8000)
				{
				  *bufferPtr++ = 0;//Next time negitive = 0
				  *colorBuffer_ptr[2]++ = 0;//Negitive
				  *colorBuffer_ptr[2]++ = 0;//Negitive
				}
				else if(tempInt & 0x4000)
				{
				  *bufferPtr++ = 0xFF;//Next time over = 255
				  *colorBuffer_ptr[2]++ = 0xFF;//Over
				  *colorBuffer_ptr[2]++ = 0xFF;//Over
				}
				else
				{
				  *bufferPtr = (char)((tempInt >> 6) & 0xFF);
				  *colorBuffer_ptr[2]++ = *bufferPtr;
				  *colorBuffer_ptr[2]++ = *bufferPtr++;
				}
			}
			bufferPtr = brcrBuffer;
			for(byteCnt = 0; byteCnt < image->brx_; byteCnt++)
			{
			  byteCnt++;// 2 Ys per horizantal pass.
			  tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
			  buffer_ptr++;
			  if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
			  else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
			  else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
			  tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
			  buffer_ptr++;
			  if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
			  else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
			  else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
			  *colorBuffer_ptr[1]++ = *bufferPtr;
			  *colorBuffer_ptr[1]++ = *bufferPtr++;
			  *colorBuffer_ptr[2]++ = *bufferPtr;
			  *colorBuffer_ptr[2]++ = *bufferPtr++;
			}
		  }
		  break;
		}// End of the switch
	  }// End of buffers.
// Open the temp file to hold put data.
	if (!(out = jas_stream_fopen(name, "w+b")))
	{
	  jas_image_destroy(image);
	  OperatorConsole.printf("***[CompressJPEG2K]: Jasper could not open the file: %s.\n", name);
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  return (FALSE);
	}
// Time to compress.
    if(jpc_encode(image, out, option))
	{
	  jas_stream_close(out);
	  unlink(name);
	  jas_image_destroy(image);
	  OperatorConsole.printf("***[CompressJPEG2K]: Jasper could not encode the image.\n");
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  return (FALSE);
	}
    jas_stream_close(out);// Jasper is done with the file.
// Lets get the data.
    fp = fopen(name, "rb");
	if(!fp)
	{
	  jas_image_destroy(image);
	  OperatorConsole.printf("***[CompressJPEG2K]: Could open the Jasper output file %s.\n",name);
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  return ( FALSE );
	}
	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);
	if(fileLength == -1 || fileLength == 0)
	{
	  if(fileLength == 0)
		OperatorConsole.printf("***[CompressJPEG2K]: File %s has a zero length\n", name);
	  else
	  	OperatorConsole.printf("***[CompressJPEG2K]: Could not get file size for %s\n", name);
	  jas_image_destroy(image);
	  fclose(fp);
	  unlink(name);
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  return ( FALSE );
	}
	rewind(fp);
// Jpeg2k is encapsulated, make a new vr to encapsulate.
    vrs = new VR(0xfffe, 0xe000, fileLength, TRUE);
	if(!vrs)
	{
	  OperatorConsole.printf("***[CompressJPEG2K]: Failed to allocate memory.\n");
	  fclose(fp);
	  unlink(name);
	  jas_image_destroy(image);
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  return ( FALSE );
	}
//If odd data length, zero the added byte.
	if ( fileLength & 1  ) ((BYTE *)vrs->Data)[fileLength] = 0;
//Change the Image data.
    lengthRead = fread(vrs->Data,1,fileLength,fp);
    if(lengthRead <= 0)
	{
	  err = ferror(fp);
	  if(err) OperatorConsole.printf("***[CompressJPEG2K]: File read error %d on %s.\n",err,name);
	  else OperatorConsole.printf("***[CompressJPEG2K]: No compressed image data (0 length read).\n");
	  fclose(fp);
	  unlink(name);
	  jas_image_destroy(image);
	  if(buffers)
	  {
		for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
		{
		  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
		  colorBuffer[cmptno] = NULL;
		}
		if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
	  }
	  while(ArrayPtr->GetSize())
	  {
		delete ArrayPtr->Get(0);
		ArrayPtr->RemoveAt(0);
	  }
	  delete ArrayPtr;
	  delete vrs;
	  return ( FALSE );
	}
	if(  lengthRead != fileLength)// Already checked for - 1.
        {
		OperatorConsole.printf("warn[CompressJPEG2K]: Only read %d bytes of %d of the jpeg2k file:%s, will try to save\n",
            vrs->Length, fileLength, name);
        }
	fclose(fp);
	unlink(name);
// Save the image object.
	DDO = new DICOMDataObject;        
	DDO->Push(vrs);
	ArrayPtr->Add(DDO);
	if(++currFrame >= frames)break;//Done with all of the frames.
//Out of data?
// Deal with silly input arrays
	if(inputArrayCnt > 0  && (size * image->numcmpts_ * currFrame) < vrImage->Length)
	{// Look for the next array.
	  while (inputArrayCnt < ArrayImage->GetSize())
	  {
		DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
		vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
// If found next one, break inner loop.
		if(vrImage && vrImage->Length >= (unsigned int)(size * image->numcmpts_)) break;
	  }
	  if(!vrImage || vrImage->Length < (unsigned int)(size * image->numcmpts_)) break;// Not enough data for at least 1 frame.
	  buffer_ptr = (char *)vrImage->Data; // Piont at the new buffer.
	}
// No silly arrays ( or a least one big file in the array).
	else
	{
	  if(!buffers) buffer_ptr += (size * image->numcmpts_);//next plane or gray.
	  if((unsigned int)(buffer_ptr - (char *)vrImage->Data + (size * image->numcmpts_))
		   > vrImage->Length)break;
	}
	for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
	{
	  if(buffers)
	  {// Reset the buffers and streams.
		jas_stream_rewind( image->cmpts_[cmptno]->stream_ );
		colorBuffer_ptr[cmptno] = colorBuffer[cmptno];// Reset the buffers.
	  }
	  else
	  {// Close and reopen the streams at the new locations.
		jas_stream_close( image->cmpts_[cmptno]->stream_);
		image->cmpts_[cmptno]->stream_ = NULL;
		if(!(cmpt->stream_ = jas_stream_memopen( buffer_ptr + (size * cmptno),size )))
		  {
			  jas_image_destroy(image);
			  OperatorConsole.printf("***[CompressJPEG2K]: Jasper could not open the memory as stream.\n");
			  if(buffers) if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
			  return (FALSE);
		  }
	  }
	}
  }//Back for the next frame, end of while(TRUE)
// Should we kill it and keep the uncompressed data?
  if(currFrame < frames) OperatorConsole.printf(
		"Warn[CompressJPEG2K]: Only %d of %d frames saved.\n",currFrame, frames);
// If buffers were made, free them.
  if(buffers)
  {
	for (cmptno = 0; cmptno < image->numcmpts_; ++cmptno)
	{
	  if(colorBuffer[cmptno]) free(colorBuffer[cmptno]);
	  colorBuffer[cmptno] = NULL;
	}
	if(colorTypeIn == CLRSPC_FAM_YCBCR_420)if(brcrBuffer)free(brcrBuffer);
  }
// The end object.
  DDO = new DICOMDataObject;
  vrs = new VR(0xfffe, 0xe0dd, 0, (void *)NULL, FALSE);
  DDO->Push(vrs);
  ArrayPtr->Add(DDO);
//  vrs = new VR(0x7fe0, 0x0010, 0, (void *)NULL, FALSE);
  pVR->Reset();//Clear the old image data including arrays.
  pVR->SQObjectArray = ArrayPtr;// Replace the data
  pVR->TypeCode ='OW';
//  pVR->Length = 0xFFFFFFFF;
// Change the dicom parameters
  if(image->numcmpts_ > 1)
  {
// Reset the plane's VR, if there.
    pVR = pDDO->GetVR(0x0028, 0x0006);
    if(pVR && pVR->Length && *(char *)pVR->Data == 1) *(char *)pVR->Data = 0;
// Set the color profile
    if(j2kQuality < 100)
      pDDO->ChangeVR( 0x0028, 0x0004, "YBR_ICT\0", 'CS');
    else pDDO->ChangeVR( 0x0028, 0x0004, "YBR_RCT\0", 'CS');
  }
// Fix the bits allocated.
  // 20120624: do not change highbit and bitsstored
  //if(byteWidth == 1)pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
  //else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

  //Change the transfer syntax to JPEG2K!
  if(j2kQuality < 100)
    pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.4.91\0", 'IU');
  else pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.4.90\0", 'IU');
// Done with Jasper.
  jas_image_destroy(image);
// If debug > 0, print when finished
  if (DebugLevel > 0)
	SystemDebug.printf("Jasper compress time %u seconds.\n", (unsigned int)time(NULL) - t);
  return (TRUE);
}

/* This routine will take in a jpeg2000 image and convert it to little endian, uncompressed,
*  RGB or grayscale.  It uses the Jasper library by Michael D. Adams from the
*  Department of Electrical and Computer Engineering at the University of Victoria.
*  You can get it here:
*  http://www.ece.uvic.ca/~mdadams/jasper/
*  You can also get it here with a few minor changes to use the my Jpeg-6c
*  library, but none of the changes are used by dgate: 
*  http://www.bitsltd.net/Software/Software-Repository/index.php
*  Jasper can compress anything, with any size for each plane.  So that means any
*  of the color spaces and formats can be in it.  The dicom standard removes the header
*  and color box infromation and sends just the data stream.  The standard states only
*  MONO1,2 PALETTE_COLOR YBR_RCT and YBR_ICT can be use.  For the color space and
*  image format, I have to trust jasper.
*  If I have made some mistakes (most likely), you can contact me bruce.barton
*  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
*  the image that didn't work. */
BOOL DecompressJPEG2K(DICOMDataObject* pDDO)
{
  Array < DICOMDataObject	*>	*ArrayPtr;
  DICOMDataObject				*DDO;
  VR							*pVR,p, *vrImage;
  unsigned char					*streamData;
#ifdef NOVARAD_FIX
  void							*fixPtr;
  unsigned char					*fix1Ptr, *fix2Ptr;
#endif
  char							*outData;
  unsigned int					frames;
  unsigned int					currFrame, currSQObject;
  jas_stream_t					*jas_in, *jas_out[4];
  jas_image_t					*decompImage;
//  jas_image_cmpt_t            *imageComp;
  char							*out_ptr;
  unsigned int					i, cps_jas, t;
  UINT8							numcmpts, prec;
//  UINT16                      bitwa, bitws,;
  UINT32						stream_len, instream_len, total_len;

// If debug > 1, get start time and set the level.
  t=0;
  if (DebugLevel > 0)
  {
	t = (unsigned int)time(NULL);
	jas_setdbglevel(DebugLevel);
  }
  if (DebugLevel > 3) SystemDebug.printf("Jasper decompress started.\n");
// Init the jasper library.
  if(jas_init())
  {
	OperatorConsole.printf("***[DecompressJPEG2K]: cannot init the jasper library\n");
	return (FALSE);
  }
  if (DebugLevel > 3) SystemDebug.printf("Jasper library init completed.\n");
// Uninitialized warnings.
  prec = 8;
  outData = NULL;
  out_ptr = NULL;
  total_len = 0;
  cps_jas = 1;
  stream_len = 0;
// Get the number of samples per pixel VR.
  if(!(numcmpts = pDDO->GetBYTE(0x0028, 0x0002))) numcmpts = 1;// Gray default.
// Are there frames?
  currFrame = 0;
  if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1;
// Get the encapsulated data.
  pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
  if(!pVR)
  {
	OperatorConsole.printf("***[DecompressJPEG2K]: No image VR\n");
	return (FALSE);
  }
  currSQObject = 0;// Init now for no warning later.
  if(pVR->SQObjectArray)
  {
	ArrayPtr = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
	while(TRUE)
	{
	  if( currSQObject >= ArrayPtr->GetSize())
	  {
		OperatorConsole.printf("***[DecompressJPEG2K]: No j2k data found\n");
		return (FALSE);
	  }
	  DDO = ArrayPtr->Get(currSQObject);//Get the last array.
	  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
//Look for size and j2k marker or jp2 file header.
	  if(vrImage->Length)
	  {
		streamData = (unsigned char *)vrImage->Data;
		instream_len = vrImage->Length;
		if( *streamData == 0xFF) break; //Jpeg stream.
		if( *streamData == 0x00 && streamData[1] == 0x00 && streamData[2] == 0x00
		  && streamData[3] == 0x0C && streamData[4] == 0x6A && streamData[5] == 0x50)
		{ //Wow, a j2k file header, dicom is normally just the stream.
		  streamData += 6;
		  instream_len -= 6;
		  for(i = 0; i < 512; i++)// I just picked 512.
		  { // Look for stream header.
			if(*streamData == 0xFF && streamData[1] == 0x4F)break;
			streamData++;
			instream_len--;
		  }
		  if( i < 512 )break;// Found the stream.
		}
	  }
	  currSQObject++;
	}
  }
  else
  {
	OperatorConsole.printf("***[DecompressJPEG2K]: No image in encapsulation arrray\n");
	return (FALSE);
  }
// Start the frames loop.
  while(TRUE)
  {
// Fix the stream length.
	if(streamData[instream_len - 1] == 0) instream_len--;
#ifdef NOVARAD_FIX
// Put the end of file back if not present.
	if ((streamData[instream_len - 2] != 0xFF)
	  || (streamData[instream_len - 1] != 0xD9))
	{
	  if(!(fixPtr = malloc(vrImage->Length + 2)))
	  {
		OperatorConsole.printf("***[DecompressJPEG2K]: Can not create memory fix buffer.\n");
		return (FALSE);
	  }
	  fix1Ptr = (unsigned char*)fixPtr;
	  fix2Ptr = (unsigned char*)vrImage->Data;
	  for( i = instream_len; i > 0; --i ) *fix1Ptr++ = *fix2Ptr++;
	  *fix1Ptr++ = 0xFF;
	  *fix1Ptr++ = 0xD9;
	  if(instream_len & 1 ) *fix1Ptr = 0;
	  free(vrImage->Data);
	  vrImage->Data = fixPtr;
	  vrImage->Length += 2;
	  streamData = (unsigned char*)vrImage->Data;
	  instream_len = vrImage->Length;
	  if(DebugLevel > 0)SystemDebug.printf("Warn[DecompressJPEG2K]: Novarad fix, EOC marker added.\n");
	}
#endif
// Open the memory as a stream.
    if(!(jas_in = jas_stream_memopen((char*)streamData, instream_len)))
	{
	  OperatorConsole.printf("***[DecompressJPEG2K]: cannot open jpeg 2K data\n");
	  return (FALSE);
	}
// Decopress the stream.
    if (!(decompImage = jpc_decode(jas_in, NULL)))
	{
	  OperatorConsole.printf("***[DecompressJPEG2K]: cannot decode the jpeg 2K code stream\n");
	  jas_stream_close(jas_in);
	  return ( FALSE );
	}
    jas_stream_close(jas_in);
// Do this the first time only.
	if(!currFrame)
	{
// Check for color.
      if(numcmpts > 1)
	  {
	    if((numcmpts != 3) || (decompImage->numcmpts_ != 3))
	    {
		   OperatorConsole.printf(
		  	  "***[DecompressJPEG2K]: Should be 3 colors, DICOM: %d ,J2K: %d \n",
			  numcmpts , decompImage->numcmpts_);
		  jas_image_destroy(decompImage);
		  return ( FALSE );
	    }
	  }
// Get the total uncompressed length and rewind all streams and get pointers.
	  stream_len = 0;
      for ( i = 0; i < numcmpts ; i++ )
	  {
        jas_out[i] = decompImage->cmpts_[i]->stream_;
        jas_stream_rewind(jas_out[i]);
        stream_len += jas_stream_length(jas_out[i]);
	  }
	  total_len = stream_len * frames;
	  prec = decompImage->cmpts_[0]->prec_;//Save for outside loop
//    bits_jas = jas_image_cmptprec(decompImage, 0);
//    signed_jas = jas_image_cmptsgnd(decompImage, 0);
      cps_jas = decompImage->cmpts_[0]->cps_;// Bytes or words.
// Allocate the bigger uncompressed and unencapsulated image.
      if (( total_len & 1) != 0 ) total_len++;//Odd length, make it even.
	  if (DebugLevel > 3)SystemDebug.printf(
		"Info[DecompressJPEG2K] stream_len = %d, frames = %d, total_len = %d, prec = %d,cps_jas = %d.\n",
		stream_len,frames,total_len,prec,cps_jas);
      if(!(outData = (char *)malloc(total_len)))
	  {
        OperatorConsole.printf(
			"***[DecompressJPEG2K]: Failed to allocate %d bytes of memory.\n", total_len);
        jas_image_destroy(decompImage);
        return ( FALSE );
	  }
      outData[total_len -1] = 0;// Dosen't hurt.        
      out_ptr = outData;
	}// end currFrame = 0.
	else
	{//Not first, just rewind streams
	  for ( i = 0; i < numcmpts ; i++ )
	  {
		jas_out[i] = decompImage->cmpts_[i]->stream_;
		jas_stream_rewind(jas_out[i]);
	  }
	}
//Image copy loops.
    if( numcmpts == 1)
	{
// Again, for some reason, Jasper outputs big endian.  There may be a switch.
//#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian like Apple power pc
	  if(cps_jas == 2)
	  {
		for(i = 0; i < stream_len; i++)
		{
		  out_ptr[1] = jas_stream_getc(jas_out[0]);
		  *out_ptr++ = jas_stream_getc(jas_out[0]);
		  out_ptr++;
		  i++;
		}
	  }
	  else
//#endif //Big Endian
		for(i = 0; i < stream_len; i++)
		  *out_ptr++ = jas_stream_getc(jas_out[0]);
	}
	else //RGB
	{
	  stream_len = jas_stream_length(jas_out[0]);
	  for(i = 0; i < stream_len; i++)
	  {
		*out_ptr++ = jas_stream_getc(jas_out[0]);
		*out_ptr++ = jas_stream_getc(jas_out[1]);
		*out_ptr++ = jas_stream_getc(jas_out[2]);
	  }
	}
	jas_image_destroy(decompImage);//Done with the image.
// check for the end
	if(++currFrame >= frames)break;
	// More images to read
	while(++currSQObject < ArrayPtr->GetSize())
	{
	  DDO = ArrayPtr->Get(currSQObject);//Get the array.
	  vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
//Look for size and j2k marker or jp2 file header.
	  if(vrImage->Length)
	  {
		streamData = (unsigned char *)vrImage->Data;
		instream_len = vrImage->Length;
		if( *streamData == 0xFF) break; //Jpeg stream.
		if( *streamData == 0x00 && streamData[1] == 0x00 && streamData[2] == 0x00
		  && streamData[3] == 0x0C && streamData[4] == 0x6A && streamData[5] == 0x50)
		{ //Wow, a j2k file header again, dicom is normally just the stream.
		  streamData += 6;
		  instream_len -= 6;
		  for(i = 0; i < 512; i++)// I just picked 512.
		  { // Look for stream header.
			if(*streamData == 0xFF && streamData[1] == 0x4F)break;
			streamData++;
			instream_len--;
		  }
		  if( i < 512 )break;// Found the stream.
		}
	  }
	}
	if( currSQObject >= ArrayPtr->GetSize() )break;//Should not happen!
// Loop back to open the memory as a stream.    
  }//End of the frames loop
  if(currFrame < frames)OperatorConsole.printf(
	"Warn[DecompressJPEG2K]: Found %d of %d frames.\n",currFrame, frames);
// Change the image vr to the bigger uncompressed and unencapsulated image.
  pVR->Reset();// Delete the old data including the array.
  pVR->Length = total_len;
  pVR->Data = outData;// The new uncompressed data.
  pVR->ReleaseMemory = TRUE;//Give the memory to the vr.
// Set the image type.
  if(cps_jas == 1)// 8 bits
  {
	pVR->TypeCode ='OB';
  }
  else
  {
	pVR->TypeCode ='OW';
  }
//  pDDO->DeleteVR(pVR);// replace the pixel data
//  pDDO->Push(vrs);
// Set color stuff if needed.
  if( numcmpts > 1)//color.
  {
    pDDO->ChangeVR( 0x0028, 0x0004, "RGB\0", 'CS');
/*	pVR = pDDO->GetVR( 0x0028, 0x0004 );
	if(pVR)
	{
	  if (pVR->Length != 4) pVR->ReAlloc(4);
	}
	else
	{
      pVR = new VR(0x0028, 0x0004, 4, TRUE);
	  pDDO->Push(pVR);
	}
    memcpy((char *)pVR->Data, "RGB\0",4);*/
// Optional planar configuration.
	pVR = pDDO->GetVR(0x0028, 0x0006); // Fix the planes VR if there.
	if(pVR && pVR->Length && *(char *)(pVR->Data) == 1)
    {
      *(UINT16 *)pVR->Data = 0;
    }
  }

// Set the number of bits allocated.
  // 20120624: do not change highbit and bitsstored
    //if(cps_jas == 1) pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
    //else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

// DecompressJPEG2K: Set the number of bits stored.
// mvh 20110502: write highbit for consistency
  // 20120624: do not change highbit and bitsstored
  // pDDO->ChangeVR( 0x0028, 0x0101, (UINT8)prec,     'US');
  // pDDO->ChangeVR( 0x0028, 0x0102, (UINT8)(prec-1), 'US');

//Change the transfer syntax to LittleEndianExplict!
  pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.1\0", 'IU');
// If debug > 1, print when finished
  if (DebugLevel > 0)
	SystemDebug.printf("Jasper decompress time %u seconds.\n", (unsigned int)time(NULL) - t);
  return (TRUE);
}
#endif //End for LIBJASPER

#ifdef HAVE_LIBOPENJPEG
/* Error and message callback does not use the FILE* client object. */
void error_callback(const char *msg, void *client_data)
{
	UNUSED_ARGUMENT(client_data);
	OperatorConsole.printf("***[Libopenjpeg(J2k)]: %s\n", msg);
}

/* Warning callback expecting a FILE* client object. */
void warning_callback(const char *msg, void *client_data)
{
	UNUSED_ARGUMENT(client_data);
	OperatorConsole.printf("Warn[Libopenjpeg(J2k)]: %s\n", msg);
}

/* Debug callback expecting no client object. */
void info_callback(const char *msg, void *client_data)
{
	UNUSED_ARGUMENT(client_data);
	if(DebugLevel > 1)SystemDebug.printf("Info[Libopenjpeg(J2k)]: %s\n", msg);
}

/* This routine will take all of the listed color spaces in 08_03 of the standard
 *  in little endian, uncompressed format and  compress it to jpeg2000 in whatever
 *  format it came in.  I don't know if dicom viewers can support this. It uses the 
 *  openjpeg library from Communications and Remote Sensing Lab (TELE) in the
 *  Universitait Catholique de Louvain (UCL), and CNES with the support of the CS company,
 *  version 1.3.  You can get it here:
 *  http://code.google.com/p/openjpeg/downloads/list
 *  The library was built with USE_JPWL defined.
 *  OpenJPEG can compress anything, with any size for each plane, but the standard only
 *  allows YBR_RCT lossless and YBR_ICT lossy.  So if a YBR come in, it is lossy, and
 *  RGB is lossless.  If this is a problem I can  add a forced change in colorspace.
 *  If I have made some mistakes (most likely), you can contact me bruce.barton
 *  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
 *  the image that didn't work. */
BOOL CompressJPEG2Ko(DICOMDataObject* pDDO, int j2kQuality)
{
	Array < DICOMDataObject	*>	*ArrayPtr, *ArrayImage;
	DICOMDataObject			*DDO;
	VR				*pVR, *vrImage, *vrs;
	int				colorTypeIn, codestream_length;
	UINT8				bitwa, prec, sgnd;
	INT32				rowCnt, byteCnt, imgSize;
	char				*colorASC;
	register char			*brcrBuffer, *buffer_ptr, *bufferPtr, *bufferg_ptr, *bufferb_ptr;
	register unsigned int		mask;
	register int			*colorBuffer_ptr[3];
	int				*colorBuffer[3], tempInt;
	unsigned int			currFrame, frames, i, t, inputArrayCnt, byteWidthIn, byteWidth;
	BOOL				planes;
// OpenJPEG Stuff
	opj_cparameters_t		parameters;	// compression parameters.
	opj_event_mgr_t			event_mgr;	// event manager.
	opj_cio_t*			cio;
	opj_cinfo_t*			cinfo;
	opj_image_t			*image = NULL;
	opj_image_comp_t		*comp;
	const char			comment[] = "Created by OpenJPEG with JPWL version ";
	const size_t			clen =	strlen(comment);
	const char			*version = opj_version();

// If debug > 0, get start time and set the level.
	t=0;
	if (DebugLevel > 0) t = (unsigned int)time(NULL);
	if (DebugLevel > 1) SystemDebug.printf("openJPEG compress started.\n");
// Uninitialized warnings.
	ArrayImage = NULL;
	i = 0;
// Check and set the quality for lossy.
	if(j2kQuality < MIN_QUALITY)// Set to 0 to use dicom.ini value. 
	{
		j2kQuality = gJpegQuality;//Use the default or dicom.ini value.
	}
	if(j2kQuality > 100) j2kQuality = 100;
// Create an image    
	if(!(image = (opj_image_t*)calloc(1, sizeof(opj_image_t))))
	{
        OperatorConsole.printf("***[CompressJPEG2K]: Could not allocate an image structure.\n");
        return (FALSE);
	}
// Set image offset
	image->x0 = 0;
	image->y0 = 0;
// How many colors
	if(!(image->numcomps = pDDO->GetBYTE(0x0028, 0x0002))) image->numcomps = 1;// Gray default.
// Decide if MCT should be used.
	parameters.tcp_mct = image->numcomps == 3 ? 1 : 0;
// Are there frames?
  if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1;
	currFrame = 0;
// Get the Rows VR and check size
	if(!(image->y1 = pDDO->GetUINT(0x0028, 0x0010)))
	{
		free(image);
		SystemDebug.printf("***[CompressJPEG2K]: Failed to get image height.\n");
		return(FALSE);
	}
	if(!(image->x1 = pDDO->GetUINT(0x0028, 0x0011)))
	{
		free(image);
		OperatorConsole.printf("***[CompressJPEG2K]: Failed to get image width.\n");
		return(FALSE);
	}
	imgSize = image->x1 * image->y1;
	
	if(!(bitwa = pDDO->GetBYTE(0x0028, 0x0100)))bitwa = 8; // 8 bit default.
	if(!(prec = pDDO->GetBYTE(0x0028, 0x0101)))prec = bitwa; //the default.
	if(prec > bitwa)bitwa = prec; // the bigger one.
	byteWidthIn = 1;
	byteWidth = 1;
	if(bitwa > 8)byteWidthIn = 2;
	if(prec > 8)byteWidth = 2;
	if(bitwa != 8 && bitwa != 12  && bitwa != 16)
	{
		free(image);
		OperatorConsole.printf("***[CompressJPEG2K]: Unsuported allocated bit width: %d.\n", bitwa);
		return(FALSE);
	}    
// Checked if the data is signed,
	if(!(sgnd = pDDO->GetBYTE(0x0028, 0x0103)))sgnd = 0;
// Planar configuration default.
	planes = FALSE;
//Sort colors.
	colorTypeIn = image->color_space = CLRSPC_GRAY;// Set the default.
    colorASC = NULL;
	if(image->numcomps == 3)
	{
        pVR = pDDO->GetVR(0x0028, 0x0004); // Get the color profile
		if(pVR && pVR->Length > 2)colorASC = (char *)pVR->Data;
// Look for the color type
		if(colorASC == NULL || strncmp(colorASC, "RGB",3)==0)// RGB
		{// Only RGB can be in planes or R,G,B format, check.
			if(pDDO->GetBYTE(0x0028, 0x0006)) planes = TRUE; // Check planes.
/*			pVR = pDDO->GetVR(0x0028, 0x0006); // Get the plane's VR.
			if(pVR && pVR->Length && (*(char *)(pVR->Data) == 1)) planes = TRUE;*/
			colorTypeIn = image->color_space = CLRSPC_SRGB;
		}
		else if ( pVR->Length > 6 && strncmp(colorASC, "YBR_",4) == 0 )
		{
			image->color_space = CLRSPC_SYCC;
			if ((strncmp(colorASC+4, "ICT",3)==0)  || (strncmp(colorASC+4, "RCT",3)==0))
			{//Some decompressor forgot to change it.
				OperatorConsole.printf
				("Warn[CompressJPEG2K]: Uncompressed colorspace can not be YBR_ICT or YBR_RCT. Trying RGB\n");
				colorTypeIn = image->color_space = CLRSPC_SRGB;
			}
			else if (pVR->Length > 7 && strncmp(colorASC+4, "FULL",4)==0)// YBR_FULL(_422)
			{
				if (pVR->Length > 11 && strncmp(colorASC+8, "_422",4)==0)// YBR_FULL_422
				{
					colorTypeIn = CLRSPC_FAM_YCBCR_F422;
				}
				else// YBR_FULL
				{//Change color in to use planes, the compressor knows what it is.
					colorTypeIn = CLRSPC_SRGB;
					planes = TRUE;
				}
			}
			else if (pVR->Length > 14 && strncmp(&colorASC[4], "PARTIAL_42",10)==0)// YBR_PARTIAL_42x
			{
				if(colorASC[14] == '2')colorTypeIn = CLRSPC_FAM_YCBCR_422;
				else colorTypeIn = CLRSPC_FAM_YCBCR_420;
			}
		}// End of YBR_
// Add more colors here.
		else
        {
            if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
            {
                OperatorConsole.printf(
                    "***[CompressJPEGL]: Unknown or unsuported color space %s.\n",colorASC);
                free(colorASC);
            }
            else OperatorConsole.printf(
                "***[CompressJPEGL]: Unknown or unsuported color space record.\n");
			free(image);
			return (FALSE);
		}//End of while color profile
	}//image->numcomps == 3
	else if(image->numcomps != 1 )// Must be gray or error.
	{
		OperatorConsole.printf("***[CompressJPEG2K]: Unsupported number of components %d.\n",
			image->numcomps);
		free(image);
		return (FALSE);
	}
// Get the data.
	inputArrayCnt = 0;
	pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
	vrImage = pVR;//Should be done here.
	if(pVR && pVR->Length)
	{
		if(pVR->SQObjectArray)
		{// Should not be here for uncompressed.
			ArrayImage = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
			while (inputArrayCnt < ArrayImage->GetSize())
			{
				DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
				vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
				if(vrImage && vrImage->Length >= (unsigned int)(imgSize *image->numcomps * byteWidthIn)) break;
			}
			if(inputArrayCnt == ArrayImage->GetSize())
			{
				free(image);
				OperatorConsole.printf("***[CompressJPEG2K]: Could not find the image data.\n");
				return (FALSE);
			}
		}
	}
// Check for a least one frame.
	if(!vrImage || vrImage->Length < (unsigned int)(imgSize *image->numcomps * byteWidthIn))
	{
		free(image);
		OperatorConsole.printf("***[CompressJPEG2K]: Could not find the image data.\n");
		return (FALSE);
	}
//Create comment for codestream.
	if(!(parameters.cp_comment = (char*)malloc(clen+strlen(version)+1)))
	{
		free(image);
		OperatorConsole.printf("***[CompressJPEG2K]: Could allocate the coment buffer.\n");
		return (FALSE);
	}
	memcpy(parameters.cp_comment, comment, clen);
	memcpy(&parameters.cp_comment[clen], version, strlen(version));
	parameters.cp_comment[+strlen(version)] = 0;
// Buffers are always needed for ints.
	for (tempInt = 0; tempInt < image->numcomps; tempInt++)
	{
		if(!(colorBuffer[tempInt] = (int *)malloc(imgSize  * sizeof(int))))
		{
			free(image);
			free(parameters.cp_comment);
			parameters.cp_comment = NULL;
			OperatorConsole.printf(
						"***[CompressJPEG2K]: Could not allocate a %d int image buffer #%d.\n",
						imgSize, tempInt);
			while(i > 0) free(colorBuffer[--tempInt]);
			return (FALSE);
		}
		colorBuffer_ptr[tempInt] = (int *)colorBuffer[tempInt];
	}
	buffer_ptr = (char *)vrImage->Data;
//Almost never used (planes)
	bufferg_ptr = buffer_ptr + imgSize;
	bufferb_ptr = bufferg_ptr + imgSize;
// Now for some more openJPEG.
// Created from image_to_j2k.c and convert.c.
// configure the event callbacks.
	memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;
// set encoding parameters values.
	opj_set_default_encoder_parameters(&parameters);
	if(j2kQuality < 100)parameters.tcp_rates[0] = 100/j2kQuality;
	else parameters.tcp_rates[0] = 0;// MOD antonin : losslessbug
	parameters.tcp_numlayers++;
	parameters.cp_disto_alloc = 1;
// Lossy (ICT) or lossless (RCT)?
    if((j2kQuality < 100) || (image->color_space == CLRSPC_SYCC)) parameters.irreversible = 1;//ICT
// allocate memory for the per-component information.
	if(!(image->comps = (opj_image_comp_t*)calloc(image->numcomps,sizeof(opj_image_comp_t))))
	{
		for(tempInt = 0; tempInt < image->numcomps; tempInt++)
		{
			if(colorBuffer[tempInt])
			{
				free(colorBuffer[tempInt]);
				colorBuffer[tempInt] = NULL;
			}
		}
		free(image);
		free(parameters.cp_comment);
		parameters.cp_comment = NULL;
		OperatorConsole.printf("***[CompressJPEG2K]: Could not create empty components.\n");
		return FALSE;
	}
// Create the individual image components.
	for(tempInt = 0; tempInt < image->numcomps; tempInt++)
	{
		comp = &image->comps[tempInt];
		comp->dx = parameters.subsampling_dx;
		comp->dy = parameters.subsampling_dy;
		comp->w = image->x1;
		comp->h = image->y1;
		comp->x0 = 0;
		comp->y0 = 0;
		comp->prec = prec;
		comp->bpp = prec;
		comp->sgnd = sgnd;
// From now, forward, opj_image_destroy(image) will free the buffers.
		comp->data = (int*)colorBuffer[tempInt];
	}
	// Print out some more info for debug.
	if (DebugLevel > 2)
	{
		if(parameters.irreversible == 0) SystemDebug.printf("JPEG2K Lossless\n");
		else SystemDebug.printf("JPEG2K Lossy Quality = %d\n", j2kQuality);
		SystemDebug.printf(", H = %d, W = %d, Bits = %d in %d, Frames = %d\n",
					image->x1, image->y1, prec, bitwa, frames);
        if((colorASC = pDDO->GetCString(0x0028, 0x0004)))
        {
            SystemDebug.printf("color = %s\n", colorASC);
            free(colorASC);
        }
        else SystemDebug.printf("Unknown color space record.\n");
	}
// Create the encapsulation array.
	ArrayPtr = new Array < DICOMDataObject * >;
// The first blank object.
	DDO = new DICOMDataObject;
	vrs = new VR(0xfffe, 0xe000, 0, (void *)NULL, FALSE);
	DDO->Push(vrs);
	ArrayPtr->Add(DDO);
// Now to fill the buffers.
	mask = ((1 << prec) - 1);
// Frames loop.
	while(TRUE)
	{
// Get a J2K compressor handle.
		cinfo = opj_create_compress(CODEC_J2K);
//Catch events using our callbacks and give a local context.
		opj_set_event_mgr((opj_common_ptr)cinfo, &event_mgr, stderr);
// Setup the encoder parameters using the current image and user parameters.
		opj_setup_encoder(cinfo, &parameters, image);
// Open a byte stream for writing.
		if(!(cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0)))
		{
			OperatorConsole.printf("***[CompressJPEG2K]: Failed to allocate output stream memory.\n");
			opj_destroy_compress(cinfo);
			opj_image_destroy(image);
			free(parameters.cp_comment);
			parameters.cp_comment = NULL;
			return ( FALSE );
		}
		switch(colorTypeIn)
		{
			case CLRSPC_GRAY://12 or 12,16 bits here
				if(bitwa == 8) // 8 Bits, char to int.
				{
					for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
					{
						*colorBuffer_ptr[0]++ = ((int)*buffer_ptr & mask);
						buffer_ptr++;
					}
					break;
				}
				if(bitwa == 16)
				{
					if(prec > 8)//Byte swap
					{
						for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
						{
							*colorBuffer_ptr[0] = ((int)*buffer_ptr & 0xFF);
							buffer_ptr++;
							*colorBuffer_ptr[0]++ |= (((int)*buffer_ptr & 0xFF) << 8) & mask;
							buffer_ptr++;
						}
						break;
					}
					for(byteCnt = 0; byteCnt < imgSize; byteCnt++)// 8 in 16.
					{
						*colorBuffer_ptr[0] = ((int)*buffer_ptr  & mask);
						buffer_ptr++;
						buffer_ptr++;
					}
					break;
				}
				for(byteCnt = 0; byteCnt < imgSize; byteCnt++)// 12 bits allocated
				{
					*colorBuffer_ptr[0] = (((int)*buffer_ptr & 0xFF) << 4) & mask;//4-11
					buffer_ptr++;
					*colorBuffer_ptr[0]++ |= (((int)*buffer_ptr & 0x0F) << 4);// 0-3
					byteCnt++;
					if(byteCnt >= imgSize)break;
					*colorBuffer_ptr[0] = (((int)*buffer_ptr & 0x0F) << 8) & mask;//8-11
					buffer_ptr++;
					*colorBuffer_ptr[0]++ = (int)*buffer_ptr & 0xFF;//0-7
					buffer_ptr++;
				}
				break;
			case CLRSPC_SRGB:// or YBR_FULL
				if(planes)
				{
					for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
					{
						*(colorBuffer_ptr[0])++ = (int)*buffer_ptr & mask;
						buffer_ptr++;
						*(colorBuffer_ptr[1])++ = (int)*bufferg_ptr & mask;
						bufferg_ptr++;
						*(colorBuffer_ptr[2])++ = (int)*bufferb_ptr & mask;
						bufferb_ptr++;
					}
					break;
				}
				for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
				{
					*(colorBuffer_ptr[0])++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
					*(colorBuffer_ptr[1])++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
					*(colorBuffer_ptr[2])++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
				}
				break;
			case CLRSPC_FAM_YCBCR_F422://Y1Y2CbCr
				for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
				{
					byteCnt++;// 2 Ys per pass.
					*colorBuffer_ptr[0]++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
					*colorBuffer_ptr[0]++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
					*colorBuffer_ptr[1]++ = (int)*buffer_ptr & mask;
					*colorBuffer_ptr[1]++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
					*colorBuffer_ptr[2]++ = (int)*buffer_ptr & mask;
					*colorBuffer_ptr[2]++ = (int)*buffer_ptr & mask;
					buffer_ptr++;
				}
				break;
			case CLRSPC_FAM_YCBCR_422://Y1Y2CbCr
				for(byteCnt = 0; byteCnt < imgSize; byteCnt++)
				{
					byteCnt++;// 2 Ys per pass.
					/* For Y the ratio is 256 / 220 (1.1636) and  for color 256 / 225 (1.1378).
					 *  Note: All values are multiplied by 1024 or 1 << 7.
					 *  Yo = 1.1636(Yi - 16)  == Yo = 1.1636Yi - 18.204 ==
					 *  Yo = [149Yi - 2330]/128 */
					tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1
					buffer_ptr++;
					if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
					else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
					else *colorBuffer_ptr[0]++ = ((tempInt >> 7) & 0xFF);
					tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y2
					buffer_ptr++;
					if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
					else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
					else *colorBuffer_ptr[0]++ = ((tempInt >> 7) & 0xFF);
					/*  Cxo = 1.1378(Cxi - 16)  == Cxo = 1.1378Cxi - 18.205 ==
					 *  Cxo = [73Cxi - 1152]/64 */
					tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
					buffer_ptr++;
					if(tempInt & 0x8000)
					{
						*colorBuffer_ptr[1]++ = 0;//Negitive
						*colorBuffer_ptr[1]++ = 0;//Negitive
					}
					else if(tempInt & 0x4000)
					{
						*colorBuffer_ptr[1]++ = 0xFF;//Over
						*colorBuffer_ptr[1]++ = 0xFF;//Over
					}
					else
					{
						*colorBuffer_ptr[1]++ = ((tempInt >> 6) & 0xFF);
						*colorBuffer_ptr[1]++ = ((tempInt >> 6) & 0xFF);
					}
					tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
					buffer_ptr++;
					if(tempInt & 0x8000)
					{
						*colorBuffer_ptr[2]++ = 0;//Negitive
						*colorBuffer_ptr[2]++ = 0;//Negitive
					}
					else if(tempInt & 0x4000)
					{
						*colorBuffer_ptr[2]++ = 0xFF;//Over
						*colorBuffer_ptr[2]++ = 0xFF;//Over
					}
					else
					{
						*colorBuffer_ptr[2]++ = ((tempInt >> 6) & 0xFF);
						*colorBuffer_ptr[2]++ = ((tempInt >> 6) & 0xFF);
						*colorBuffer_ptr[2]++;
					}
				}
				break;
				/* What a strange standard. See page 323 of 08_03pu.pdf. */
			case CLRSPC_FAM_YCBCR_420://Y1CrCbY2Y3CrCbY4-Y1Y2Y3Y4?
				brcrBuffer = (char *)malloc(image->x1);
				for(rowCnt = 0; rowCnt < image->y1; rowCnt++)// 8 bit only.
				{
					rowCnt++;
					bufferPtr = brcrBuffer;
					for(byteCnt = 0; byteCnt < image->x1; byteCnt++)
					{
						byteCnt++;// 2 Ys per horizantal pass.
						tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
						buffer_ptr++;
						if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
						else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
						else *colorBuffer_ptr[0]++ = ((tempInt >> 7) & 0xFF);
						tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
						buffer_ptr++;
						if(tempInt & 0x8000)
						{
							*bufferPtr++ = 0;//Next time negitive = 0
							*colorBuffer_ptr[1]++ = 0;//Negitive
							*colorBuffer_ptr[1]++ = 0;//Negitive
						}
						else if(tempInt & 0x4000)
						{
							*bufferPtr++ = 0xFF;//Next time over = 255
							*colorBuffer_ptr[1]++ = 0xFF;//Over
							*colorBuffer_ptr[1]++ = 0xFF;//Over
						}
						else
						{
							*bufferPtr = (char)((tempInt >> 6) & 0xFF);
							*colorBuffer_ptr[1]++ = (int)*bufferPtr & 0xFF;
							*colorBuffer_ptr[1]++ = (int)*bufferPtr & 0xFF;
							bufferPtr++;
						}
						tempInt = (((int)*buffer_ptr) * 73) - 1152;//Cb
						buffer_ptr++;
						if(tempInt & 0x8000)
						{
							*bufferPtr++ = 0;//Next time negitive = 0
							*colorBuffer_ptr[2]++ = 0;//Negitive
							*colorBuffer_ptr[2]++ = 0;//Negitive
						}
						else if(tempInt & 0x4000)
						{
							*bufferPtr++ = 0xFF;//Next time over = 255
							*colorBuffer_ptr[2]++ = 0xFF;//Over
							*colorBuffer_ptr[2]++ = 0xFF;//Over
						}
						else
						{
							*bufferPtr = (char)((tempInt >> 6) & 0xFF);
							*colorBuffer_ptr[2]++ = (int)*bufferPtr & 0xFF;
							*colorBuffer_ptr[2]++ = (int)*bufferPtr & 0xFF;
							bufferPtr++;
						}
					}
					bufferPtr = brcrBuffer;
					for(byteCnt = 0; byteCnt < image->x1; byteCnt++)
					{
						byteCnt++;// 2 Ys per horizantal pass.
						tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
						buffer_ptr++;
						if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
						else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
						else *colorBuffer_ptr[0]++ = ((tempInt >> 7) & 0xFF);
						tempInt = (((int)*buffer_ptr) * 149) - 2330;//Y1, Y3, ...
						buffer_ptr++;
						if(tempInt & 0x10000)*colorBuffer_ptr[0]++ = 0;// Neg not allowed here.
						else if(tempInt & 0x8000)*colorBuffer_ptr[0]++ = 0xFF;// Over flow.
						else *colorBuffer_ptr[0]++ = (char)((tempInt >> 7) & 0xFF);
						*colorBuffer_ptr[1]++ = (int)*bufferPtr & 0xFF;
						*colorBuffer_ptr[1]++ = (int)*bufferPtr & 0xFF;
						bufferPtr++;
						*colorBuffer_ptr[2]++ = (int)*bufferPtr & 0xFF;
						*colorBuffer_ptr[2]++ = (int)*bufferPtr & 0xFF;
						bufferPtr++;
					}
				}
				free(brcrBuffer);
				break;
		}// End of the colorType switch.
// encode the image.
		if(!(opj_encode(cinfo, cio, image, NULL)))
		{
			OperatorConsole.printf("***[CompressJPEG2K]: OpenJpeg could not encode the image.\n");
			while(ArrayPtr->GetSize())
			{
				delete ArrayPtr->Get(0);
				ArrayPtr->RemoveAt(0);
			}
			delete ArrayPtr;
			opj_destroy_compress(cinfo);
			opj_image_destroy(image);
			opj_cio_close(cio);
			free(parameters.cp_comment);
			parameters.cp_comment = NULL;
			return FALSE;
		}
		opj_destroy_compress(cinfo);//Done with cinfo.
		codestream_length = cio_tell(cio);
// Jpeg2k is encapsulated, make a new vr to encapsulate.
		vrs = new VR(0xfffe, 0xe000, (UINT32)codestream_length, TRUE);
		if(!vrs)
		{
			OperatorConsole.printf("***[CompressJPEG2K]: Failed to allocate memory.\n");
			while(ArrayPtr->GetSize())
			{
				delete ArrayPtr->Get(0);
				ArrayPtr->RemoveAt(0);
			}
			delete ArrayPtr;
			opj_image_destroy(image);
			opj_cio_close(cio);
			free(parameters.cp_comment);
			parameters.cp_comment = NULL;
			return ( FALSE );
		}
//If odd data length, zero the added byte.
		if ( codestream_length & 1  ) ((BYTE *)vrs->Data)[codestream_length] = 0;
// Copy the Image data.
		brcrBuffer = (char *)vrs->Data;
		bufferPtr = (char *)cio->buffer;
		for(i = codestream_length; i > 0; --i) *brcrBuffer++ = *bufferPtr++;
// Done with the code stream and cinfo.
		opj_cio_close(cio);
// Save the image object. */        
		DDO = new DICOMDataObject;        
		DDO->Push(vrs);
		ArrayPtr->Add(DDO);
//Out of data?
		if(++currFrame >= frames)break;//Done with all of the frames.
// Deal with silly input arrays
		if(inputArrayCnt > 0  && (unsigned int)(imgSize *image->numcomps * byteWidthIn) < vrImage->Length)
		{// Look for the next array.
			while (inputArrayCnt < ArrayImage->GetSize())
			{
				DDO = ArrayImage->Get(inputArrayCnt++);//Get the array.
				vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
// If found next one, break inner loop.
				if(vrImage && vrImage->Length >= (unsigned int)(imgSize *image->numcomps * byteWidthIn)) break;
			}
// Not enough data for at least 1 frame, end frames loop.
			if(!vrImage || vrImage->Length < (unsigned int)(imgSize *image->numcomps * byteWidthIn)) break;
			buffer_ptr = (char *)vrImage->Data; // Point at the new buffer.
		}
// No silly arrays ( or a least one big file in the array).
		else
		{
			if((unsigned int)(buffer_ptr - (char *)vrImage->Data + imgSize)
			   > vrImage->Length)break; //Out of data?
		}
// Reset the buffers.
		for( tempInt = 0; tempInt < image->numcomps; tempInt++)
			colorBuffer_ptr[tempInt] = (int *)colorBuffer[tempInt];
		if(planes)//Jump the next 2 planes.
		{
			buffer_ptr = bufferb_ptr;
			bufferg_ptr = buffer_ptr + imgSize;
			bufferb_ptr = bufferg_ptr + imgSize;
		}
	}//Back for the next frame, end of while(TRUE)
//Done with the comments.
	free(parameters.cp_comment);
	parameters.cp_comment = NULL;
// Should we kill it and keep the uncompressed data?
	if(currFrame < frames) OperatorConsole.printf(
		"Warn[CompressJPEG2K]: Only %d of %d frames saved.\n",currFrame, frames);
// Finish encapsulating.
    DDO = new DICOMDataObject;
    vrs = new VR(0xfffe, 0xe0dd, 0, (void *)NULL, FALSE);
    DDO->Push(vrs);
    ArrayPtr->Add(DDO);
// Attach the array to the vr.
    pVR->Reset(); // Deletes the pixel data
    pVR->SQObjectArray = ArrayPtr;
    pVR->TypeCode ='OW';
   // mvh: should not be needed - pDDO->Length = 0xFFFFFFFF;
// Change the dicom parameters.
	if(image->numcomps == 3)
	{
// Reset the plane's VR, if there.
        pVR = pDDO->GetVR(0x0028, 0x0006);
        if(pVR && pVR->Length && *(char *)(pVR->Data) == 1) *(char *)(pVR->Data = 0);
// Set the color profile
        if((j2kQuality < 100) || (image->color_space == CLRSPC_SYCC))
            pDDO->ChangeVR( 0x0028, 0x0004, "YBR_ICT\0", 'CS');
        else pDDO->ChangeVR( 0x0028, 0x0004, "YBR_RCT\0", 'CS');
/*		pVR = pDDO->GetVR(0x0028, 0x0004);		if(pVR)
		{
			pVR->Length = 8;
			if(pVR->ReAlloc(pVR->Length))
			{
				if((j2kQuality < 100) || (image->color_space == CLRSPC_SYCC))
					memcpy(pVR->Data, "YBR_ICT\0",8);
				else memcpy(pVR->Data, "YBR_RCT\0",8);
			}
		}*/
	}
// Fix the bits allocated.
  // 20120624: do not change highbit and bitsstored
    //if(byteWidth == 1)pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
    //else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

//Change the transfer syntax to JPEG2K!
    if((j2kQuality < 100) || (image->color_space == CLRSPC_SYCC))
        pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.4.91\0", 'IU');
    else pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.4.90\0", 'IU');
// At last, done with the image.
	opj_image_destroy(image);
// If debug > 0, print when finished
	if (DebugLevel > 0)
		SystemDebug.printf("OpenJPEG compress time %u seconds.\n", (unsigned int)time(NULL) - t);
    return (TRUE);
}

/* This routine will take in a jpeg2000 image and convert it to little endian, uncompressed,
 *  RGB or grayscale.  It uses the openjpeg library from Communications and Remote Sensing Lab (TELE)
 *  in the Universitait Catholique de Louvain (UCL), and CNES with the support of the CS company.
 *  You can get it here:
 *  http://code.google.com/p/openjpeg/downloads/list
 *  The library was built with USE_JPWL defined.
 *  JPEG200 can compress almost anything, with any size for each plane.  So that means any
 *  of the color spaces and formats can be in it.  The dicom standard removes the header
 *  and color box infromation and sends just the data stream.  The standard states only
 *  MONO1,2 PALETTE_COLOR YBR_RCT and YBR_ICT can be use.  For the color space and
 *  image format, I have to trust libopenjpeg.
 *  If I have made some mistakes (most likely) you can contact me bruce.barton
 *  (the mail symbol goes here) bitsltd.net.  Let me know where I can find a sample of
 *  the image that didn't work. */
BOOL DecompressJPEG2Ko(DICOMDataObject* pDDO)
{
    Array < DICOMDataObject	*>	*ArrayPtr;
    DICOMDataObject             *DDO;
    VR                          *pVR, *vrImage;
    register unsigned char      *outc_ptr;
    register UINT16				*out16_ptr;
	unsigned char				*streamData;
#ifdef NOVARAD_FIX
    void			*fixPtr;
    unsigned char		*fix1Ptr, *fix2Ptr;
#endif
    unsigned char		*outData;
    UINT16			frames;
    unsigned int                i, t;
    register int		*jpc_out[3], mask;
    int				bytes_jpc, prec_jpc;
    unsigned int		currFrame, currSQObject;
    UINT8			numcmpts;
    //    UINT16		bitwa, bitws,;
    UINT32			stream_len, instream_len, total_len;
    //	bool						bResult;
#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian like Apple power pc
    register int		masked;
#endif //Big Endian
// openJPEG stuff.
    opj_dparameters_t		parameters;	// decompression parameters.
    opj_image_t			*decompImage = NULL;
    opj_event_mgr_t		event_mgr;		// event manager.
    opj_dinfo_t			*dinfo = NULL;	// handle to a decompressor.
    opj_cio_t			*cio = NULL;
	
// If debug > 0, get start time.
	t = 0;
	if (DebugLevel > 0)t = (unsigned int)time(NULL);
	if (DebugLevel > 1) SystemDebug.printf("openJPEG decompress started.\n");
// Init some variables	
	outData = NULL;
// Uninitialized warnings.
	outc_ptr = NULL;
	out16_ptr = NULL;
	mask = 0;
	bytes_jpc = 1;
	prec_jpc = 8;
	total_len = 0;
	stream_len = 0;
// Get the number of samples per pixel VR.
    if(!(numcmpts = pDDO->GetBYTE(0x0028, 0x0002))) numcmpts = 1;// Gray default.
// Are there frames?
    if(!(frames = pDDO->Getatoi(0x0028, 0x0008))) frames = 1;
    currFrame = 0;
// Get the encapsulated data.
    pVR = pDDO->GetVR(0x7fe0, 0x0010); // Get the Image VR.
	if(!pVR)
	{
        OperatorConsole.printf("***[DecompressJPEG2K]: No image VR\n");
        return (FALSE);
	}
	currSQObject = 0;// Init now for no warning later.
	if(pVR->SQObjectArray)
	{
		ArrayPtr = (Array<DICOMDataObject *> *) pVR->SQObjectArray;
		while(TRUE)
		{
			if( currSQObject >= ArrayPtr->GetSize())
			{
				OperatorConsole.printf("***[DecompressJPEG2K]: No j2k data found\n");
				return (FALSE);
			}
			DDO = ArrayPtr->Get(currSQObject );//Get the array.
			vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
			//Look for size and j2k marker or jp2 file header.
			if(vrImage->Length)
			{
				streamData = (unsigned char *)vrImage->Data;
				instream_len = vrImage->Length;
				if( *streamData == 0xFF) break; //Jpeg stream.
				if( *streamData == 0x00 && streamData[1] == 0x00 && streamData[2] == 0x00
				   && streamData[3] == 0x0C && streamData[4] == 0x6A && streamData[5] == 0x50)
				{ //Wow, a j2k file header, dicom is normally just the stream.
					streamData += 6;
					instream_len -= 6;
					for(i = 0; i < 512; i++)// I just picked 512.
					{ // Look for stream header.
						if(*streamData == 0xFF && streamData[1] == 0x4F)break;
						streamData++;
						instream_len--;
					}
					if( i < 512 )break;// Found the stream.
				}
			}
			currSQObject++;
		}
	}
	else
	{
		OperatorConsole.printf("***[DecompressJPEG2K]: No image in encapsulation arrray\n");
		return (FALSE);
	}
// configure the event callbacks.
	memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;
// set decoding parameters to default values.
	opj_set_default_decoder_parameters(&parameters);
// set decoding parameter format to stream.
	parameters.decod_format = CODEC_J2K;
// Start the frames loop.
	while(TRUE)
	{
		// Fix the stream length.
		if(streamData[instream_len - 1] == 0) instream_len--;
#ifdef NOVARAD_FIX
		// Put the end of file back if not present.
		if ((streamData[instream_len - 2] != 0xFF)
			|| (streamData[instream_len - 1] != 0xD9))
		{
			if(!(fixPtr = malloc(vrImage->Length + 2)))
			{
				OperatorConsole.printf("***[DecompressJPEG2K]: Can not create memory fix buffer.\n");
				return (FALSE);
			}
			fix1Ptr = (unsigned char*)fixPtr;
			fix2Ptr = (unsigned char*)vrImage->Data;
			for( i = instream_len; i > 0; --i ) *fix1Ptr++ = *fix2Ptr++;
			*fix1Ptr++ = 0xFF;
			*fix1Ptr++ = 0xD9;
			if(instream_len & 1 ) *fix1Ptr = 0;
			free(vrImage->Data);
			vrImage->Data = fixPtr;
			vrImage->Length += 2;
			streamData = (unsigned char*)vrImage->Data;
			instream_len = vrImage->Length;
			if(DebugLevel > 0)SystemDebug.printf("Warn[DecompressJPEG2K]: Novarad fix, EOC marker added.\n");
		}
#endif
		// get a decoder handle.
		dinfo = opj_create_decompress(CODEC_J2K);//Bad openjpeg, can't be reused!
// catch events using our callbacks and give a local context.
		opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);
// setup the decoder decoding parameters using user parameters.
		opj_setup_decoder(dinfo, &parameters);
// Open the memory as a stream.    
		if(!(cio = opj_cio_open((opj_common_ptr)dinfo, streamData, instream_len)))
		{
			opj_destroy_decompress(dinfo);
			OperatorConsole.printf("***[DecompressJPEG2K]: cannot open jpeg 2K data\n");
			return (FALSE);
		}
// decode the stream and fill the image structure
		decompImage = opj_decode(dinfo, cio);
// Check the image
		if (!decompImage)
		{
			OperatorConsole.printf("***[DecompressJPEG2K]: Jpeg 2K code stream decode did not create an image\n");
			opj_destroy_decompress(dinfo);
			opj_cio_close(cio);
			return FALSE;
		}
// close the byte stream
		opj_cio_close(cio);	   
// Do this the first time only
		if(!currFrame)
		{//Make the buffer.
// Check for color.
			if(numcmpts > 1)
			{
				if((numcmpts != 3) || (decompImage->numcomps != 3))
				{
					OperatorConsole.printf(
						"***[DecompressJPEG2K]: Should be 3 colors, DICOM: %d ,J2K: %d \n",
						numcmpts , decompImage->numcomps);
					opj_image_destroy(decompImage);
					return ( FALSE );
				}
			}
// Get the total uncompressed length.
			prec_jpc =decompImage->comps[0].prec;//Need it at the end
			bytes_jpc = ((prec_jpc -1) / 8) + 1;// Bytes or words.
			total_len = decompImage->comps[0].w * decompImage->comps[0].h
						* bytes_jpc * numcmpts * frames;
			if (( total_len & 1) != 0 ) total_len++;
			if(!(outData = (unsigned char *)malloc(total_len)))
			{
				OperatorConsole.printf(
					"***[DecompressJPEG2K]: Failed to allocate %d bytes of memory.\n", total_len);
				opj_image_destroy(decompImage);
				return ( FALSE );
			}
			outData[total_len -1] = 0;// Dosen't hurt.
			outc_ptr = outData;
			out16_ptr = (UINT16 *)outData;
// The same for all images
			mask = (1 << prec_jpc) - 1;
			stream_len = (decompImage->comps[0].w * decompImage->comps[0].h);
		}//End of make the data buffer
//Get the data pointer(s)
		for ( i = 0; i < numcmpts ; i++ )
		{
			jpc_out[i] = decompImage->comps[i].data;
		}
// Image copy loops, open JPEG outputs ints.
		if( numcmpts == 1)
		{
			if(bytes_jpc == 2)
			{
				for(i = 0; i < stream_len; i++)
				{
#if NATIVE_ENDIAN == BIG_ENDIAN //Big Endian like Apple power pc
					masked = (UINT16)(*jpc_out[0]++ & mask);
					*outc_ptr++ = (char)(masked & 0xFF);
					*outc_ptr++ = (char)((masked >> 8) & 0xFF);
#else //Little Endian
					*out16_ptr++ = (UINT16)(*jpc_out[0]++ & mask);
#endif //Big Endian
				}
				
			}
			else
				for(i = 0; i < stream_len; i++)
					*outc_ptr++ = (unsigned char)(*jpc_out[0]++ & mask);
		}
		else //RGB
		{
			for(i = 0; i < stream_len; i++)
			{
				*outc_ptr++ = (unsigned char)(*jpc_out[0]++ & mask);
				*outc_ptr++ = (unsigned char)(*jpc_out[1]++ & mask);
				*outc_ptr++ = (unsigned char)(*jpc_out[2]++ & mask);
	    
			}
	}
// Done with libopenjpeg for this loop.
	opj_destroy_decompress(dinfo);
	opj_image_destroy(decompImage);
// check for the end
	if(++currFrame >= frames)break;
// More images to read
	while(++currSQObject < ArrayPtr->GetSize())
	{
	    DDO = ArrayPtr->Get(currSQObject);//Get the array.
	    vrImage = DDO->GetVR(0xfffe, 0xe000);//Get the data
		//Look for size and j2k marker or jp2 file header.
		if(vrImage->Length)
		{
			streamData = (unsigned char *)vrImage->Data;
			instream_len = vrImage->Length;
			if( *streamData == 0xFF) break; //Jpeg stream.
			if( *streamData == 0x00 && streamData[1] == 0x00 && streamData[2] == 0x00
			   && streamData[3] == 0x0C && streamData[4] == 0x6A && streamData[5] == 0x50)
			{ //Wow, a j2k file header again, dicom is normally just the stream.
				streamData += 6;
				instream_len -= 6;
				for(i = 0; i < 512; i++)// I just picked 512.
				{ // Look for stream header.
					if(*streamData == 0xFF && streamData[1] == 0x4F)break;
					streamData++;
					instream_len--;
				}
				if( i < 512 )break;// Found the stream.
			}
		}
	}
	if( currSQObject >= ArrayPtr->GetSize() )break;//Should not happen!
// Loop back to open the memory as a stream.    
    }//End of the frames loop
// Done with libjpeg.
//	if(dinfo) opj_destroy_decompress(dinfo);
    if(currFrame < frames)OperatorConsole.printf(
	"Warn[DecompressJPEG2K]: Found %d of %d frames.\n",currFrame, frames);
// Change the image vr to the bigger uncompressed and unencapsulated image.
    pVR->Reset(); // Deletes the pixel data
    pVR->Length = total_len;
    pVR->Data = outData;
    pVR->ReleaseMemory = TRUE;//Give the memory to the vr.
// Set the image type.
    if(bytes_jpc == 1)// 8 bits
    {
        pVR->TypeCode ='OB';
    }
    else
    {
        pVR->TypeCode ='OW';
    }
	
// The color stuff
    if(numcmpts    > 1)
    {
//Set Planes value if needed, do  not create if not there.
	pVR = pDDO->GetVR(0x0028, 0x0006);
	if(pVR && pVR->Length && *(char *)pVR->Data == 1)
            *(char *)pVR->Data = 0;
//Change the Photometric Interpretation.
        pDDO->ChangeVR( 0x0028, 0x0004, "RGB\0", 'CS');
    }
// Set the number of bits allocated.
  // 20120624: do not change highbit and bitsstored
  //  if(bytes_jpc == 1) pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)8, 'US');
  //  else pDDO->ChangeVR( 0x0028, 0x0100, (UINT8)16, 'US');

// mvh 20110502: DecompressJPEG2Ko: write highbit for consistency
  // 20120624: do not change highbit and bitsstored
   //pDDO->ChangeVR( 0x0028, 0x0101, (UINT8)prec_jpc,     'US');// Set the number of bits stored.
   //pDDO->ChangeVR( 0x0028, 0x0102, (UINT8)(prec_jpc-1), 'US');// Set high bit.

//Change the transfer syntax to LittleEndianExplict!
    pDDO->ChangeVR( 0x0002, 0x0010, "1.2.840.10008.1.2.1\0", 'IU');
// If debug > 0, print decompress time.
    if (DebugLevel > 0)
	SystemDebug.printf("OpenJPEG decompress time %u seconds.\n", (unsigned int)time(NULL) - t);
    return (TRUE);
}
#endif //End for libopenjpeg

