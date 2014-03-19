/****************************************************************************
          Copyright (C) 1995, University of California, Davis

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND THE UNIVERSITY
          OF CALIFORNIA DOES NOT MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          owned by the University of California, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include this copyright notice.
****************************************************************************/

/***************************************************************************
 *
 * University of California, Davis
 * UCDMC DICOM Network Transport Libraries
 * Version 0.1 Beta
 *
 * Technical Contact: mhoskin@ucdavis.edu
 *
 ***************************************************************************/

/* bcb 20100619: Fix gcc4 warnings and improve speed.
   mvh 20100717: Merged
   mvh 20140309: Default AAbort source to 0 (service-user initiated abort)
*/

#	include	"dicom.hpp"


/************************************************************************
 *
 * AAssociateRJ Packet
 *
 ************************************************************************/

AAssociateRJ	::	AAssociateRJ()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x03),
Reserved1(0),
Length(0),
Reserved2(0),
Result(1),
Source(3),
Reason(1) {}
#else
	{
	ItemType = 0x03;
	Reserved1 = 0;
	Reserved2 = 0;
	Result = 1;
	Source = 3;
	Reason = 1;
	}
#endif

AAssociateRJ	::	AAssociateRJ(BYTE Res, BYTE S, BYTE Re)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x03),
Reserved1(0),
Length(0),
Reserved2(0),
Result(Res),
Source(S),
Reason(Re) {}
#else
{
	ItemType = 0x03;
	Reserved1 = 0;
	Reserved2 = 0;
	Result = Res;
	Source = S;
	Reason = Re;
	}
#endif

AAssociateRJ	::	~AAssociateRJ()
	{
	// nothing, everything should self-destruct nicely
	}


BOOL	AAssociateRJ	::	Write(Buffer	&Link)
	{
	Size();
	Link << ItemType; //Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT32));
	Link << Reserved2;			//Link.Write((BYTE *) &Reserved2, sizeof(UINT16));
	Link << Result;
	Link << Source;
	Link << Reason;
	Link.Flush();
	return ( TRUE );
	}

BOOL	AAssociateRJ	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return(this->ReadDynamic(Link));
	}

BOOL	AAssociateRJ	::	ReadDynamic(Buffer	&Link)
	{
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT32));
	Link >>	Reserved2;			//Link.Read((BYTE *) &Reserved2, sizeof(UINT16));
	Link >> Result;
	Link >> Source;
	Link >> Reason;

	return (TRUE);
	}

UINT32	AAssociateRJ	::	Size()
	{
	Length = 4;
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT32) );
	}


/************************************************************************
 *
 * AReleaseRQ Packet
 *
 ************************************************************************/

AReleaseRQ	::	AReleaseRQ()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x05),
Reserved1(0),
Length(0),
Reserved2(0) {}
#else
	{
	ItemType = 0x05;
	Reserved1 = 0;
	Reserved2 = 0;
	}
#endif

AReleaseRQ	::	~AReleaseRQ()
	{
	// nothing, everything should self-destruct nicely
	}


BOOL	AReleaseRQ	::	Write(Buffer	&Link)
	{
	Size();
	Link << ItemType; //Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT32));
	Link << Reserved2;			//Link.Write((BYTE *) &Reserved2, sizeof(UINT16));
	Link.Flush();
	return ( TRUE );
	}

BOOL	AReleaseRQ	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return(this->ReadDynamic(Link));
	}

BOOL	AReleaseRQ	::	ReadDynamic(Buffer	&Link)
	{
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT32));
	Link >>	Reserved2;			//Link.Read((BYTE *) &Reserved2, sizeof(UINT16));
	return (TRUE);
	}

UINT32	AReleaseRQ	::	Size()
	{
	Length = 4;
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT32) );
	}

/************************************************************************
 *
 * AReleaseRP Packet
 *
 ************************************************************************/

AReleaseRP	::	AReleaseRP()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x06),
Reserved1(0),
Length(0),
Reserved2(0) {}
#else
	{
	ItemType = 0x06;
	Reserved1 = 0;
	Reserved2 = 0;
	}
#endif

AReleaseRP	::	~AReleaseRP()
	{
	// nothing, everything should self-destruct nicely
	}


BOOL	AReleaseRP	::	Write(Buffer	&Link)
	{
	Size();
	Link << ItemType; //Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT32));
	Link << Reserved2;			//Link.Write((BYTE *) &Reserved2, sizeof(UINT16));
	Link.Flush();
	return ( TRUE );
	}

BOOL	AReleaseRP	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return(this->ReadDynamic(Link));
	}

BOOL	AReleaseRP	::	ReadDynamic(Buffer	&Link)
	{
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT32));
	Link >>	Reserved2;			//Link.Read((BYTE *) &Reserved2, sizeof(UINT16));
	return (TRUE);
	}

UINT32	AReleaseRP	::	Size()
	{
	Length = 4;
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT32) );
	}

/************************************************************************
 *
 * AAbortRQ Packet
 *
 ************************************************************************/

AAbortRQ	::	AAbortRQ()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x07),
Reserved1(0),
Length(0),
Reserved2(0),
Reserved3(0),
Source(0),
Reason(1) {}
#else
	{
	ItemType = 0x07;
	Reserved1 = 0;
	Reserved2 = 0;
	Reserved3 = 0;
	Source = 0;
	Reason = 1;
	}
#endif

AAbortRQ	::	AAbortRQ(BYTE S, BYTE Re)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x03),
Reserved1(0),
Length(0),
Reserved2(0),
Reserved3(0),
Source(S),
Reason(Re) {}
#else
	{
	ItemType = 0x03;
	Reserved1 = 0;
	Reserved2 = 0;
	Reserved3 = 0;
	Source = S;
	Reason = Re;
	}
#endif

AAbortRQ	::	~AAbortRQ()
	{
	// nothing, everything should self-destruct nicely
	}


BOOL	AAbortRQ	::	Write(Buffer	&Link)
	{
	Size();
	Link << ItemType; //Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT32));
	Link << Reserved2;			//Link.Write((BYTE *) &Reserved2, sizeof(UINT16));
	Link << Reserved3;
	Link << Source;
	Link << Reason;
	Link.Flush();
	return ( TRUE );
	}

BOOL	AAbortRQ	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return(this->ReadDynamic(Link));
	}

BOOL	AAbortRQ	::	ReadDynamic(Buffer	&Link)
	{
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT32));
	Link >>	Reserved2;			//Link.Read((BYTE *) &Reserved2, sizeof(UINT16));
	Link >> Reserved3;
	Link >> Source;
	Link >> Reason;

	return ( TRUE );
	}

UINT32	AAbortRQ	::	Size()
	{
	Length = 4;
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT32) );
	}

