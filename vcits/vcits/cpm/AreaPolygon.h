/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CPM-PDU-Descriptions"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/experimental/CPM-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cpm -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CPM`
 */

#ifndef	_AreaPolygon_H_
#define	_AreaPolygon_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PolyPointList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AreaPolygon */
typedef struct AreaPolygon {
	PolyPointList_t	 polyPointList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AreaPolygon_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AreaPolygon;
extern asn_SEQUENCE_specifics_t asn_SPC_AreaPolygon_specs_1;
extern asn_TYPE_member_t asn_MBR_AreaPolygon_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _AreaPolygon_H_ */
#include <asn_internal.h>
