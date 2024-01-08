/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CPM-PDU-Descriptions"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/experimental/CPM-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cpm -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CPM`
 */

#ifndef	_AreaEllipse_H_
#define	_AreaEllipse_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SemiRangeLength.h"
#include "WGS84AngleValue.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct OffsetPoint;

/* AreaEllipse */
typedef struct AreaEllipse {
	struct OffsetPoint	*nodeCenterPoint;	/* OPTIONAL */
	SemiRangeLength_t	 semiMinorRangeLength;
	SemiRangeLength_t	 semiMajorRangeLength;
	WGS84AngleValue_t	 semiMajorRangeOrientation;
	SemiRangeLength_t	*semiHeight;	/* OPTIONAL */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AreaEllipse_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AreaEllipse;
extern asn_SEQUENCE_specifics_t asn_SPC_AreaEllipse_specs_1;
extern asn_TYPE_member_t asn_MBR_AreaEllipse_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _AreaEllipse_H_ */
#include <asn_internal.h>