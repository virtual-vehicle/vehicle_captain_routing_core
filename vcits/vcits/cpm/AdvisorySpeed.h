/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "/tmp/gen_env/build/asn1/ISO-TS-19091-addgrp-C-2018-patched.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cpm -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CPM`
 */

#ifndef	_AdvisorySpeed_H_
#define	_AdvisorySpeed_H_


#include <asn_application.h>

/* Including external dependencies */
#include "AdvisorySpeedType.h"
#include "SpeedAdvice.h"
#include "SpeedConfidenceDSRC.h"
#include "ZoneLength.h"
#include "RestrictionClassID.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Reg_AdvisorySpeed;

/* AdvisorySpeed */
typedef struct AdvisorySpeed {
	AdvisorySpeedType_t	 type;
	SpeedAdvice_t	*speed;	/* OPTIONAL */
	SpeedConfidenceDSRC_t	*confidence;	/* OPTIONAL */
	ZoneLength_t	*distance;	/* OPTIONAL */
	RestrictionClassID_t	*Class;	/* OPTIONAL */
	struct AdvisorySpeed__regional {
		A_SEQUENCE_OF(struct Reg_AdvisorySpeed) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *regional;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AdvisorySpeed_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AdvisorySpeed;
extern asn_SEQUENCE_specifics_t asn_SPC_AdvisorySpeed_specs_1;
extern asn_TYPE_member_t asn_MBR_AdvisorySpeed_1[6];

#ifdef __cplusplus
}
#endif

#endif	/* _AdvisorySpeed_H_ */
#include <asn_internal.h>