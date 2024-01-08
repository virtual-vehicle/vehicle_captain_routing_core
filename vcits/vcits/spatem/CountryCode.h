/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AVIAEINumberingAndDataStructures"
 * 	found in "/tmp/gen_env/build/asn1/ISO14816_AVIAEINumberingAndDataStructures.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/spatem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SPATEM`
 */

#ifndef	_CountryCode_H_
#define	_CountryCode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CountryCode */
typedef BIT_STRING_t	 CountryCode_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_CountryCode_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_CountryCode;
asn_struct_free_f CountryCode_free;
asn_struct_print_f CountryCode_print;
asn_constr_check_f CountryCode_constraint;
ber_type_decoder_f CountryCode_decode_ber;
der_type_encoder_f CountryCode_encode_der;
xer_type_decoder_f CountryCode_decode_xer;
xer_type_encoder_f CountryCode_encode_xer;
oer_type_decoder_f CountryCode_decode_oer;
oer_type_encoder_f CountryCode_encode_oer;
per_type_decoder_f CountryCode_decode_uper;
per_type_encoder_f CountryCode_encode_uper;
per_type_decoder_f CountryCode_decode_aper;
per_type_encoder_f CountryCode_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _CountryCode_H_ */
#include <asn_internal.h>
