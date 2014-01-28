/*
20030606	ljz	Added parameter 'QueryRetrieveLevel' to CFindRSP::Write
20050129	mvh	Added Write with extra vr to CEchoRSP
20070314	mvh	Allow send of 0000,1030 (MoveOriginatorAE) and 0000,1031 (MoveOriginatorMessageID) 
			in CStoreRQ
20100619	bcb	Added virtual destructors  (gcc4.0 Warnings)
20100717	bcb	Merged
 */
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


class	CEchoRQ
	{
	public:
		BOOL	Read ( DICOMCommandObject * );
		BOOL	Write ( PDU_Service * );
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CEchoRQ() {};
#endif
	};

class	CEchoRSP
	{
	public:
		BOOL	Read ( DICOMCommandObject * );
		BOOL	Write ( PDU_Service *, DICOMCommandObject *, UINT16, VR * );
		BOOL	Write ( PDU_Service *, DICOMCommandObject *, UINT16 );
		BOOL	Write ( PDU_Service *, DICOMCommandObject * );
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CEchoRSP() {};
#endif
	};

class	CStoreRQ
	{
	public:
		BOOL	Read (	DICOMCommandObject *,
				PDU_Service *,
				DICOMDataObject * );
		BOOL	Read (	DICOMCommandObject	* );
		BOOL	Write ( PDU_Service * , DICOMDataObject	*, VR *MoveMessageID = NULL, unsigned char *CallingAE = NULL);
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CStoreRQ() {};
#endif
	};

class	CStoreRSP
	{
	public:
		BOOL	Read ( DICOMCommandObject * );
		BOOL	Write ( PDU_Service * , DICOMCommandObject *, UINT16 );
		BOOL	Write ( PDU_Service *, DICOMCommandObject * );
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CStoreRSP() {};
#endif
	};

class	CFindRQ
	{
	public:
		BOOL	Read (	DICOMCommandObject *,
				PDU_Service *,
				DICOMDataObject * );
		BOOL	Read (	DICOMCommandObject	* );
		BOOL	Write ( PDU_Service * , DICOMDataObject	*);
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CFindRQ() {};
#endif
	};

class	CFindRSP
	{
	public:
		BOOL	Read (	DICOMCommandObject *,
				PDU_Service	*,
				DICOMDataObject	* );
		BOOL	Read (	DICOMCommandObject	* );
		BOOL	Write ( PDU_Service *,
				DICOMCommandObject *,
				UINT16,
				DICOMDataObject	*,
				char* QueryRetrieveLevel);
		BOOL	Write ( PDU_Service *,
				DICOMCommandObject *,
				DICOMDataObject *,
				char* QueryRetrieveLevel);
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CFindRSP() {};
#endif
	};

class	CMoveRQ
	{
	public:
		BOOL	Read (	DICOMCommandObject *,
				PDU_Service *,
				DICOMDataObject * );
		BOOL	Read (	DICOMCommandObject	* );
		BOOL	Write ( PDU_Service * , DICOMDataObject	*, BYTE *);
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CMoveRQ() {};
#endif
	};

class	CMoveRSP
	{
	public:
		BOOL	Read (	DICOMCommandObject *,
				PDU_Service	*,
				DICOMDataObject	* );
		BOOL	Read (	DICOMCommandObject * );
		BOOL	Write ( PDU_Service *,
				DICOMCommandObject *,
				UINT16,
				UINT16,
				UINT16,
				UINT16,
				UINT16,
				DICOMDataObject *);
		virtual	BOOL	GetUID ( UID & ) = 0;
#ifdef __GNUC__
		virtual	~CMoveRSP() {};
#endif
	};

