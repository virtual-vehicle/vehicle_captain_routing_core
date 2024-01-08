/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "EfcDsrcApplication"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/is_ts103301/iso-patched/ISO14906(2018)EfcDsrcApplicationv6-patched.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ivim -R -no-gen-example -fcompound-names -fno-include-deps -pdu=IVIM`
 */

#include "ReceiptOBUId.h"

/*
 * This type is implemented using OCTET_STRING,
 * so here we adjust the DEF accordingly.
 */
static const ber_tlv_tag_t asn_DEF_ReceiptOBUId_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ReceiptOBUId = {
	"ReceiptOBUId",
	"ReceiptOBUId",
	&asn_OP_OCTET_STRING,
	asn_DEF_ReceiptOBUId_tags_1,
	sizeof(asn_DEF_ReceiptOBUId_tags_1)
		/sizeof(asn_DEF_ReceiptOBUId_tags_1[0]), /* 1 */
	asn_DEF_ReceiptOBUId_tags_1,	/* Same as above */
	sizeof(asn_DEF_ReceiptOBUId_tags_1)
		/sizeof(asn_DEF_ReceiptOBUId_tags_1[0]), /* 1 */
	{ 0, 0, OCTET_STRING_constraint },
	0, 0,	/* No members */
	&asn_SPC_OCTET_STRING_specs	/* Additional specs */
};

