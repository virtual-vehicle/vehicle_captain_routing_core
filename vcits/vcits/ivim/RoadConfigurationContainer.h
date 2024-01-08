/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "/tmp/gen_env/build/asn1/ISO19321IVIv2.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ivim -R -no-gen-example -fcompound-names -fno-include-deps -pdu=IVIM`
 */

#ifndef	_RoadConfigurationContainer_H_
#define	_RoadConfigurationContainer_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RccPart;

/* RoadConfigurationContainer */
typedef struct RoadConfigurationContainer {
	A_SEQUENCE_OF(struct RccPart) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RoadConfigurationContainer_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RoadConfigurationContainer;
extern asn_SET_OF_specifics_t asn_SPC_RoadConfigurationContainer_specs_1;
extern asn_TYPE_member_t asn_MBR_RoadConfigurationContainer_1[1];
extern asn_per_constraints_t asn_PER_type_RoadConfigurationContainer_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _RoadConfigurationContainer_H_ */
#include <asn_internal.h>
