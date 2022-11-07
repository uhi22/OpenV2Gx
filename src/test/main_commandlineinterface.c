
/*******************************************************************
 * Command line interface for OpenV2G
 * Maintained in http://github.com/uhi22/OpenV2Gx, a fork of https://github.com/Martin-P/OpenV2G
 *
 ********************************************************************/


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <string.h>

#include "EXITypes.h"

#include "appHandEXIDatatypes.h"
#include "appHandEXIDatatypesEncoder.h"
#include "appHandEXIDatatypesDecoder.h"

/* Activate support for DIN */
#include "dinEXIDatatypes.h"
#if DEPLOY_DIN_CODEC == SUPPORT_YES
#include "dinEXIDatatypesEncoder.h"
#include "dinEXIDatatypesDecoder.h"
#endif /* DEPLOY_DIN_CODEC == SUPPORT_YES */

/* Activate support for XMLDSIG */
#include "xmldsigEXIDatatypes.h"
#if DEPLOY_XMLDSIG_CODEC == SUPPORT_YES
#include "xmldsigEXIDatatypesEncoder.h"
#include "xmldsigEXIDatatypesDecoder.h"
#endif /* DEPLOY_XMLDSIG_CODEC == SUPPORT_YES */

/* Activate support for ISO1 */
#include "iso1EXIDatatypes.h"
#if DEPLOY_ISO1_CODEC == SUPPORT_YES
#include "iso1EXIDatatypesEncoder.h"
#include "iso1EXIDatatypesDecoder.h"
#endif /* DEPLOY_ISO1_CODEC == SUPPORT_YES */

/* Activate support for ISO2 */
#include "iso2EXIDatatypes.h"
#if DEPLOY_ISO2_CODEC == SUPPORT_YES
#include "iso2EXIDatatypesEncoder.h"
#include "iso2EXIDatatypesDecoder.h"
#endif /* DEPLOY_ISO2_CODEC == SUPPORT_YES */

#include "v2gtp.h"

#define BUFFER_SIZE 256
uint8_t buffer1[BUFFER_SIZE];
uint8_t buffer2[BUFFER_SIZE];
bitstream_t global_stream1;
size_t global_pos1;
int g_errn;

#define ERROR_UNEXPECTED_REQUEST_MESSAGE -601
#define ERROR_UNEXPECTED_SESSION_SETUP_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DISCOVERY_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DETAILS_RESP_MESSAGE -603
#define ERROR_UNEXPECTED_PAYMENT_SERVICE_SELECTION_RESP_MESSAGE -604
#define ERROR_UNEXPECTED_PAYMENT_DETAILS_RESP_MESSAGE -605
#define ERROR_UNEXPECTED_AUTHORIZATION_RESP_MESSAGE -606
#define ERROR_UNEXPECTED_CHARGE_PARAMETER_DISCOVERY_RESP_MESSAGE -607
#define ERROR_UNEXPECTED_POWER_DELIVERY_RESP_MESSAGE -608
#define ERROR_UNEXPECTED_CHARGING_STATUS_RESP_MESSAGE -609
#define ERROR_UNEXPECTED_METERING_RECEIPT_RESP_MESSAGE -610
#define ERROR_UNEXPECTED_SESSION_STOP_RESP_MESSAGE -611
#define ERROR_UNEXPECTED_CABLE_CHECK_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_PRE_CHARGE_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_CURRENT_DEMAND_RESP_MESSAGE -613
#define ERROR_UNEXPECTED_WELDING_DETECTION_RESP_MESSAGE -614



static int writeStringToEXIString(char* string, exi_string_character_t* exiString) {
	int pos = 0;
	while(string[pos]!='\0')
	{
		exiString[pos] = string[pos];
		pos++;
	}
	return pos;
}

static void printASCIIString(exi_string_character_t* string, uint16_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%c",(char)string[i]);
	}
	printf("\n");
}


static void printBinaryArray(uint8_t* byte, uint16_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}

static void copyBytes(uint8_t* from, uint16_t len, uint8_t* to) {
	int i;
	for(i=0; i<len; i++) {
		to[i] = from[i];
	}
}

/* prepare an empty stream */
static void prepareGlobalStream(void) {
	global_stream1.size = BUFFER_SIZE;
	global_stream1.data = buffer1;
	global_stream1.pos = &global_pos1;	
	*(global_stream1.pos) = 0; /* start adding data at position 0 */	
}

/* print the global stream on the console output */
void printGlobalStream(void) {
	int i;
	if (g_errn!=0) {
		printf("encoding failed %d\n", errn);
	} else {
		printf("encoder produced "); 
		for (i=0; i<*global_stream1.pos; i++) {
			printf("%02x", global_stream1.data[i]);
		}
		printf("\n");
	}	
}

#define SCHEMA_APP_HANDSHAKE 0
#define SCHEMA_DIN 1
#define SCHEMA_ISO1 2
#define SCHEMA_ISO2 3
#define DIR_ENCODING 0
#define DIR_DECODING 1


static void encodeSupportedAppProtocolResponse(void) {
	/* The :supportedAppProtocolRes contains only two fields:
	    ResponseCode
		SchemaID (optional) It is not clear, in which cases the SchemaID can be left empty. Maybe if the list has only one enty. Or
		maybe always, to just select the first entry. */
  struct appHandEXIDocument applHandshake;		
  init_appHandEXIDocument(&applHandshake);
  applHandshake.supportedAppProtocolRes_isUsed = 1u;
  applHandshake.supportedAppProtocolRes.ResponseCode = appHandresponseCodeType_OK_SuccessfulNegotiation;
  applHandshake.supportedAppProtocolRes.SchemaID = 1; /* todo: fill with one of the SchemaIDs of the request. The Ioniq uses schema 1 as one-and-only. */
  applHandshake.supportedAppProtocolRes.SchemaID_isUsed = 1u; /* todo: shall we try without SchemaID? */

  prepareGlobalStream();
  g_errn = encode_appHandExiDocument(&global_stream1, &applHandshake);
  printGlobalStream();
}

static void testEncodeSessionSetupResponse(void) {
	struct dinEXIDocument dinDoc;
	dinDoc.V2G_Message_isUsed = 1u;
	/* generate an unique sessionID */
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	dinDoc.V2G_Message.Header.SessionID.bytes[0] = 1;
	dinDoc.V2G_Message.Header.SessionID.bytes[1] = 2;
	dinDoc.V2G_Message.Header.SessionID.bytes[2] = 3;
	dinDoc.V2G_Message.Header.SessionID.bytes[3] = 4;
	dinDoc.V2G_Message.Header.SessionID.bytes[4] = 5;
	dinDoc.V2G_Message.Header.SessionID.bytes[5] = 6;
	dinDoc.V2G_Message.Header.SessionID.bytes[6] = 7;
	dinDoc.V2G_Message.Header.SessionID.bytes[7] = 8;
	dinDoc.V2G_Message.Header.SessionID.bytesLen = 8;
	/* Prepare data for EV */
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.SessionSetupRes_isUsed = 1u;
	init_dinSessionSetupResType(&dinDoc.V2G_Message.Body.SessionSetupRes);
	dinDoc.V2G_Message.Body.SessionSetupRes.ResponseCode = dinresponseCodeType_OK;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.characters[0] = 0;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.characters[1] = 20;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen = 2;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSETimeStamp_isUsed = 0u;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSETimeStamp = 123456789;
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
}

/* Converting parameters to an EXI stream */
static int runTheEncoder(char* parameterStream) {
  printf("encoderTest\n");
  /* ED1 for Encode DIN session setup response */
  /* xxxx */
  testEncodeSessionSetupResponse();
  return 0;
}

/** Converting EXI stream to parameters  */
static int runTheDecoder(char* parameterStream) {
	int i;
	struct appHandEXIDocument exiDocAppHand;
	struct dinEXIDocument exiDocDin;
	struct iso1EXIDocument exiDocIso1;
	struct iso2EXIDocument exiDocIso2;	
	int errn = 0;
	int numBytes;
	char strOneByteHex[3];
	int schema;

	if (strlen(parameterStream)<3) {
		printf("parameter too short\n");
		return -1;
	}
	/* The second character selects the schema. */
	/* The OpenV2G supports 4 different decoders:
	    decode_appHandExiDocument
		decode_iso1ExiDocument
		decode_iso2ExiDocument
		decode_dinExiDocument
		The caller needs to choose, depending on its context-knowledge, the correct decoder.
		The first step in a session is always to use the decode_appHandExiDocument for finding out, which specification/decoder
		is used in the next steps. */
	if (parameterStream[1]=='H') {
		schema = SCHEMA_APP_HANDSHAKE;
	} else if (parameterStream[1]=='D') {
		schema = SCHEMA_DIN;
	} else if (parameterStream[1]=='1') {
		schema = SCHEMA_ISO1;
	} else if (parameterStream[1]=='2') {
		schema = SCHEMA_ISO2;
	} else {
		printf("The second character of the parameter must be H for applicationHandshake, D for DIN, 1 for ISO1 or 2 for ISO2.\n");
		schema = -1;
	}
	global_stream1.size = BUFFER_SIZE;
	global_stream1.data = buffer1;
	global_stream1.pos = &global_pos1;
	//printf("decoderTest for %s\n", parameterStream);
	numBytes=strlen(parameterStream)/2;
	global_pos1 = 0;
	printf("numBytes %d\n", numBytes);
	strOneByteHex[2]=0;
	/* convert the hex stream into array of bytes: */
	for (i=1; i<numBytes; i++) { /* starting at 1, means the first two characters (the direction-and-schema-selectors) are jumped-over. */
		strOneByteHex[0] = parameterStream[2*i];
		strOneByteHex[1] = parameterStream[2*i+1];
		buffer1[global_pos1++] = strtol(strOneByteHex, NULL, 16);
	}
	/*
	printf("size = %d\n", global_stream1.size);
	printf("pos  = %d\n", *(global_stream1.pos));
	for (i=0; i<(*global_stream1.pos); i++) {
		printf("%02x ", global_stream1.data[i]);
	}
	printf("\n");
	*/
	
	*(global_stream1.pos) = 0; /* the decoder shall start at the byte 0 */
	errn = 0;
	switch (schema) {
		case SCHEMA_APP_HANDSHAKE:
			errn = decode_appHandExiDocument(&global_stream1, &exiDocAppHand);
			break;
		case SCHEMA_DIN:
			errn = decode_dinExiDocument(&global_stream1, &exiDocDin);
			break;
		case SCHEMA_ISO1:
			errn = decode_iso1ExiDocument(&global_stream1, &exiDocIso1);
			break;
		case SCHEMA_ISO2:
			errn = decode_iso2ExiDocument(&global_stream1, &exiDocIso2);
			break;
			
	}
	if(errn) {
			/* an error occured */
			printf("decoderTest error%d\n", errn);
			return errn;
	}		

	if (schema == SCHEMA_APP_HANDSHAKE) {
		printf("EVSE side: List of application handshake protocols of the EV \n");
		for(i=0;i<exiDocAppHand.supportedAppProtocolReq.AppProtocol.arrayLen;i++) {
			printf("\tProtocol entry #=%d\n",(i+1));
			printf("\t\tProtocolNamespace=");
			printASCIIString(exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].ProtocolNamespace.characters, exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].ProtocolNamespace.charactersLen);
			printf("\t\tVersion=%d.%d\n", exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMajor, exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMinor);
			printf("\t\tSchemaID=%d\n", exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].SchemaID);
			printf("\t\tPriority=%d\n", exiDocAppHand.supportedAppProtocolReq.AppProtocol.array[i].Priority);
		}
	} else {
		printf("Schema not implemented.\n");
	}
	return errn;
}

/* The entry point */
int main_commandline(int argc, char *argv[]) {
	if (argc>=2) {
		printf("OpenV2G will process %s\n", argv[1]);
		/* The first char of the parameter decides over Encoding or Decoding. */
		if (argv[1][0]=='E') {
			runTheEncoder(argv[1]);
			return 0;
		} else if (argv[1][0]=='D') {
			runTheDecoder(argv[1]);
			return 0;
		} else {
			printf("The first character of the parameter must be D for decoding or E for encoding.\n");
			return -1;
		}
	}
	printf("OpenV2G: Error: To few parameters.\n");
	return -1;
}

