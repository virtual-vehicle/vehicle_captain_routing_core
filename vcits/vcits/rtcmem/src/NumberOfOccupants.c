/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/cdd_ts102894_2/ITS-Container.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/rtcmem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=RTCMEM`
 */

#include "NumberOfOccupants.h"

int
NumberOfOccupants_constraint(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 127)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

/*
 * This type is implemented using NativeInteger,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_NumberOfOccupants_constr_1 CC_NOTUSED = {
	{ 1, 1 }	/* (0..127) */,
	-1};
static asn_per_constraints_t asn_PER_type_NumberOfOccupants_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  0,  127 }	/* (0..127) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const ber_tlv_tag_t asn_DEF_NumberOfOccupants_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
asn_TYPE_descriptor_t asn_DEF_NumberOfOccupants = {
	"NumberOfOccupants",
	"NumberOfOccupants",
	&asn_OP_NativeInteger,
	asn_DEF_NumberOfOccupants_tags_1,
	sizeof(asn_DEF_NumberOfOccupants_tags_1)
		/sizeof(asn_DEF_NumberOfOccupants_tags_1[0]), /* 1 */
	asn_DEF_NumberOfOccupants_tags_1,	/* Same as above */
	sizeof(asn_DEF_NumberOfOccupants_tags_1)
		/sizeof(asn_DEF_NumberOfOccupants_tags_1[0]), /* 1 */
	{ &asn_OER_type_NumberOfOccupants_constr_1, &asn_PER_type_NumberOfOccupants_constr_1, NumberOfOccupants_constraint },
	0, 0,	/* Defined elsewhere */
	0	/* No specifics */
};

