/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "/tmp/gen_env/build/asn1/ISO19321IVIv2.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ivim -R -no-gen-example -fcompound-names -fno-include-deps -pdu=IVIM`
 */

#ifndef	_AbsolutePosition_H_
#define	_AbsolutePosition_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Latitude.h"
#include "Longitude.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AbsolutePosition */
typedef struct AbsolutePosition {
	Latitude_t	 latitude;
	Longitude_t	 longitude;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AbsolutePosition_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AbsolutePosition;
extern asn_SEQUENCE_specifics_t asn_SPC_AbsolutePosition_specs_1;
extern asn_TYPE_member_t asn_MBR_AbsolutePosition_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _AbsolutePosition_H_ */
#include <asn_internal.h>
