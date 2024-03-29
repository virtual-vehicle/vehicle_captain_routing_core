/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CPM-PDU-Descriptions"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/experimental/CPM-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cpm -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CPM`
 */

#ifndef	_CpmParameters_H_
#define	_CpmParameters_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CpmManagementContainer.h"
#include "NumberOfPerceivedObjects.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct StationDataContainer;
struct SensorInformationContainer;
struct PerceivedObjectContainer;
struct FreeSpaceAddendumContainer;

/* CpmParameters */
typedef struct CpmParameters {
	CpmManagementContainer_t	 managementContainer;
	struct StationDataContainer	*stationDataContainer;	/* OPTIONAL */
	struct SensorInformationContainer	*sensorInformationContainer;	/* OPTIONAL */
	struct PerceivedObjectContainer	*perceivedObjectContainer;	/* OPTIONAL */
	struct FreeSpaceAddendumContainer	*freeSpaceAddendumContainer;	/* OPTIONAL */
	NumberOfPerceivedObjects_t	 numberOfPerceivedObjects;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CpmParameters_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CpmParameters;
extern asn_SEQUENCE_specifics_t asn_SPC_CpmParameters_specs_1;
extern asn_TYPE_member_t asn_MBR_CpmParameters_1[6];

#ifdef __cplusplus
}
#endif

#endif	/* _CpmParameters_H_ */
#include <asn_internal.h>
