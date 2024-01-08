/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "GDD"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/is_ts103301/iso-patched/ISO14823-missing.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ivim -R -no-gen-example -fcompound-names -fno-include-deps -pdu=IVIM`
 */

#include "InternationalSign-numberOfLane.h"

int
InternationalSign_numberOfLane_constraint(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 99)) {
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
static asn_oer_constraints_t asn_OER_type_InternationalSign_numberOfLane_constr_1 CC_NOTUSED = {
	{ 1, 1 }	/* (0..99) */,
	-1};
asn_per_constraints_t asn_PER_type_InternationalSign_numberOfLane_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  0,  99 }	/* (0..99) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const ber_tlv_tag_t asn_DEF_InternationalSign_numberOfLane_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
asn_TYPE_descriptor_t asn_DEF_InternationalSign_numberOfLane = {
	"InternationalSign-numberOfLane",
	"InternationalSign-numberOfLane",
	&asn_OP_NativeInteger,
	asn_DEF_InternationalSign_numberOfLane_tags_1,
	sizeof(asn_DEF_InternationalSign_numberOfLane_tags_1)
		/sizeof(asn_DEF_InternationalSign_numberOfLane_tags_1[0]), /* 1 */
	asn_DEF_InternationalSign_numberOfLane_tags_1,	/* Same as above */
	sizeof(asn_DEF_InternationalSign_numberOfLane_tags_1)
		/sizeof(asn_DEF_InternationalSign_numberOfLane_tags_1[0]), /* 1 */
	{ &asn_OER_type_InternationalSign_numberOfLane_constr_1, &asn_PER_type_InternationalSign_numberOfLane_constr_1, InternationalSign_numberOfLane_constraint },
	0, 0,	/* No members */
	0	/* No specifics */
};

