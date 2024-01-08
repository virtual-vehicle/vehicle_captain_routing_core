/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/cdd_ts102894_2/ITS-Container.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/srem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SREM`
 */

#ifndef	_RequestResponseIndication_H_
#define	_RequestResponseIndication_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RequestResponseIndication {
	RequestResponseIndication_request	= 0,
	RequestResponseIndication_response	= 1
} e_RequestResponseIndication;

/* RequestResponseIndication */
typedef long	 RequestResponseIndication_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RequestResponseIndication;
asn_struct_free_f RequestResponseIndication_free;
asn_struct_print_f RequestResponseIndication_print;
asn_constr_check_f RequestResponseIndication_constraint;
ber_type_decoder_f RequestResponseIndication_decode_ber;
der_type_encoder_f RequestResponseIndication_encode_der;
xer_type_decoder_f RequestResponseIndication_decode_xer;
xer_type_encoder_f RequestResponseIndication_encode_xer;
oer_type_decoder_f RequestResponseIndication_decode_oer;
oer_type_encoder_f RequestResponseIndication_encode_oer;
per_type_decoder_f RequestResponseIndication_decode_uper;
per_type_encoder_f RequestResponseIndication_encode_uper;
per_type_decoder_f RequestResponseIndication_decode_aper;
per_type_encoder_f RequestResponseIndication_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _RequestResponseIndication_H_ */
#include <asn_internal.h>
