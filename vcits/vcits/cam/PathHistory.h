/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/cdd_ts102894_2/ITS-Container.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cam -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CAM`
 */

#ifndef	_PathHistory_H_
#define	_PathHistory_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PathPoint;

/* PathHistory */
typedef struct PathHistory {
	A_SEQUENCE_OF(struct PathPoint) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PathHistory_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PathHistory;
extern asn_SET_OF_specifics_t asn_SPC_PathHistory_specs_1;
extern asn_TYPE_member_t asn_MBR_PathHistory_1[1];
extern asn_per_constraints_t asn_PER_type_PathHistory_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _PathHistory_H_ */
#include <asn_internal.h>
