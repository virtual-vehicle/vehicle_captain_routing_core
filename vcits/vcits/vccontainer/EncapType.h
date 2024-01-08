/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VC-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/custom/VC-Container-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/vccontainer -R -no-gen-example -fcompound-names -fno-include-deps -pdu=RawRxMessage -pdu=RawTxMessage`
 */

#ifndef	_EncapType_H_
#define	_EncapType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EncapType {
	EncapType_unsecure	= 0,
	EncapType_signed	= 1
} e_EncapType;

/* EncapType */
typedef long	 EncapType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_EncapType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_EncapType;
extern const asn_INTEGER_specifics_t asn_SPC_EncapType_specs_1;
asn_struct_free_f EncapType_free;
asn_struct_print_f EncapType_print;
asn_constr_check_f EncapType_constraint;
ber_type_decoder_f EncapType_decode_ber;
der_type_encoder_f EncapType_encode_der;
xer_type_decoder_f EncapType_decode_xer;
xer_type_encoder_f EncapType_encode_xer;
oer_type_decoder_f EncapType_decode_oer;
oer_type_encoder_f EncapType_encode_oer;
per_type_decoder_f EncapType_decode_uper;
per_type_encoder_f EncapType_encode_uper;
per_type_decoder_f EncapType_decode_aper;
per_type_encoder_f EncapType_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _EncapType_H_ */
#include <asn_internal.h>