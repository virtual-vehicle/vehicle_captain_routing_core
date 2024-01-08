/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "/tmp/gen_env/build/asn1/ISO-TS-19091-addgrp-C-2018-patched.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/srem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SREM`
 */

#ifndef	_SpeedandHeadingandThrottleConfidence_H_
#define	_SpeedandHeadingandThrottleConfidence_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HeadingConfidenceDSRC.h"
#include "SpeedConfidenceDSRC.h"
#include "ThrottleConfidence.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SpeedandHeadingandThrottleConfidence */
typedef struct SpeedandHeadingandThrottleConfidence {
	HeadingConfidenceDSRC_t	 heading;
	SpeedConfidenceDSRC_t	 speed;
	ThrottleConfidence_t	 throttle;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SpeedandHeadingandThrottleConfidence_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SpeedandHeadingandThrottleConfidence;
extern asn_SEQUENCE_specifics_t asn_SPC_SpeedandHeadingandThrottleConfidence_specs_1;
extern asn_TYPE_member_t asn_MBR_SpeedandHeadingandThrottleConfidence_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _SpeedandHeadingandThrottleConfidence_H_ */
#include <asn_internal.h>
