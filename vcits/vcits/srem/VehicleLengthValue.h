/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "/tmp/gen_env/../vehicle_captain_its_asn1_specifications/etsi/cdd_ts102894_2/ITS-Container.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/srem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SREM`
 */

#ifndef	_VehicleLengthValue_H_
#define	_VehicleLengthValue_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum VehicleLengthValue {
	VehicleLengthValue_tenCentimeters	= 1,
	VehicleLengthValue_outOfRange	= 1022,
	VehicleLengthValue_unavailable	= 1023
} e_VehicleLengthValue;

/* VehicleLengthValue */
typedef long	 VehicleLengthValue_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_VehicleLengthValue_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_VehicleLengthValue;
asn_struct_free_f VehicleLengthValue_free;
asn_struct_print_f VehicleLengthValue_print;
asn_constr_check_f VehicleLengthValue_constraint;
ber_type_decoder_f VehicleLengthValue_decode_ber;
der_type_encoder_f VehicleLengthValue_encode_der;
xer_type_decoder_f VehicleLengthValue_decode_xer;
xer_type_encoder_f VehicleLengthValue_encode_xer;
oer_type_decoder_f VehicleLengthValue_decode_oer;
oer_type_encoder_f VehicleLengthValue_encode_oer;
per_type_decoder_f VehicleLengthValue_decode_uper;
per_type_encoder_f VehicleLengthValue_encode_uper;
per_type_decoder_f VehicleLengthValue_decode_aper;
per_type_encoder_f VehicleLengthValue_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleLengthValue_H_ */
#include <asn_internal.h>
