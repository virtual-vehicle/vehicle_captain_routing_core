/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "EfcDsrcApplication"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/is_ts103301/iso-patched/ISO14906(2018)EfcDsrcApplicationv6-patched.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ivim -R -no-gen-example -fcompound-names -fno-include-deps -pdu=IVIM`
 */

#include "EfcDsrcApplication_TrailerCharacteristics.h"

static asn_TYPE_member_t asn_MBR_EfcDsrcApplication_TrailerCharacteristics_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct EfcDsrcApplication_TrailerCharacteristics, trailerDetails),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TrailerDetails,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"trailerDetails"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EfcDsrcApplication_TrailerCharacteristics, trailerMaxLadenWeight),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Int2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"trailerMaxLadenWeight"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct EfcDsrcApplication_TrailerCharacteristics, trailerWeightUnladen),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Int2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"trailerWeightUnladen"
		},
};
static const ber_tlv_tag_t asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_EfcDsrcApplication_TrailerCharacteristics_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* trailerDetails */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* trailerMaxLadenWeight */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* trailerWeightUnladen */
};
static asn_SEQUENCE_specifics_t asn_SPC_EfcDsrcApplication_TrailerCharacteristics_specs_1 = {
	sizeof(struct EfcDsrcApplication_TrailerCharacteristics),
	offsetof(struct EfcDsrcApplication_TrailerCharacteristics, _asn_ctx),
	asn_MAP_EfcDsrcApplication_TrailerCharacteristics_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_EfcDsrcApplication_TrailerCharacteristics = {
	"TrailerCharacteristics",
	"TrailerCharacteristics",
	&asn_OP_SEQUENCE,
	asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1,
	sizeof(asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1)
		/sizeof(asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1[0]), /* 1 */
	asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1,	/* Same as above */
	sizeof(asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1)
		/sizeof(asn_DEF_EfcDsrcApplication_TrailerCharacteristics_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_EfcDsrcApplication_TrailerCharacteristics_1,
	3,	/* Elements count */
	&asn_SPC_EfcDsrcApplication_TrailerCharacteristics_specs_1	/* Additional specs */
};

