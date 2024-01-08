/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CPM-PDU-Descriptions"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/experimental/CPM-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/cpm -R -no-gen-example -fcompound-names -fno-include-deps -pdu=CPM`
 */

#include "PerceivedObjectContainerSegmentInfo.h"

asn_TYPE_member_t asn_MBR_PerceivedObjectContainerSegmentInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PerceivedObjectContainerSegmentInfo, totalMsgSegments),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SegmentCount,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"totalMsgSegments"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PerceivedObjectContainerSegmentInfo, thisSegmentNum),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SegmentCount,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"thisSegmentNum"
		},
};
static const ber_tlv_tag_t asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PerceivedObjectContainerSegmentInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* totalMsgSegments */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* thisSegmentNum */
};
asn_SEQUENCE_specifics_t asn_SPC_PerceivedObjectContainerSegmentInfo_specs_1 = {
	sizeof(struct PerceivedObjectContainerSegmentInfo),
	offsetof(struct PerceivedObjectContainerSegmentInfo, _asn_ctx),
	asn_MAP_PerceivedObjectContainerSegmentInfo_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PerceivedObjectContainerSegmentInfo = {
	"PerceivedObjectContainerSegmentInfo",
	"PerceivedObjectContainerSegmentInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1,
	sizeof(asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1)
		/sizeof(asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1[0]), /* 1 */
	asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1)
		/sizeof(asn_DEF_PerceivedObjectContainerSegmentInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PerceivedObjectContainerSegmentInfo_1,
	2,	/* Elements count */
	&asn_SPC_PerceivedObjectContainerSegmentInfo_specs_1	/* Additional specs */
};

