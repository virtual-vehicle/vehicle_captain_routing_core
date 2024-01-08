/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VC-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/custom/VC-Container-PDU-Descriptions.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/vccontainer -R -no-gen-example -fcompound-names -fno-include-deps -pdu=RawRxMessage -pdu=RawTxMessage`
 */

#ifndef	_DecapStatus_H_
#define	_DecapStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DecapStatus {
	DecapStatus_none	= 0,
	DecapStatus_invalid_fmt	= 1,
	DecapStatus_verified_pkt	= 2,
	DecapStatus_unverifiable_pkt	= 3
} e_DecapStatus;

/* DecapStatus */
typedef long	 DecapStatus_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_DecapStatus_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_DecapStatus;
extern const asn_INTEGER_specifics_t asn_SPC_DecapStatus_specs_1;
asn_struct_free_f DecapStatus_free;
asn_struct_print_f DecapStatus_print;
asn_constr_check_f DecapStatus_constraint;
ber_type_decoder_f DecapStatus_decode_ber;
der_type_encoder_f DecapStatus_encode_der;
xer_type_decoder_f DecapStatus_decode_xer;
xer_type_encoder_f DecapStatus_encode_xer;
oer_type_decoder_f DecapStatus_decode_oer;
oer_type_encoder_f DecapStatus_encode_oer;
per_type_decoder_f DecapStatus_decode_uper;
per_type_encoder_f DecapStatus_encode_uper;
per_type_decoder_f DecapStatus_decode_aper;
per_type_encoder_f DecapStatus_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _DecapStatus_H_ */
#include <asn_internal.h>
