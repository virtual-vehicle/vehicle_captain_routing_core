/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AddGrpC"
 * 	found in "/tmp/gen_env/build/asn1/ISO-TS-19091-addgrp-C-2018-patched.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ssem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SSEM`
 */

#ifndef	_ExceptionalCondition_H_
#define	_ExceptionalCondition_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ExceptionalCondition {
	ExceptionalCondition_unknown	= 0,
	ExceptionalCondition_publicTransportPriority	= 1,
	ExceptionalCondition_emergencyVehiclePriority	= 2,
	ExceptionalCondition_trainPriority	= 3,
	ExceptionalCondition_bridgeOpen	= 4,
	ExceptionalCondition_vehicleHeight	= 5,
	ExceptionalCondition_weather	= 6,
	ExceptionalCondition_trafficJam	= 7,
	ExceptionalCondition_tunnelClosure	= 8,
	ExceptionalCondition_meteringActive	= 9,
	ExceptionalCondition_truckPriority	= 10,
	ExceptionalCondition_bicyclePlatoonPriority	= 11,
	ExceptionalCondition_vehiclePlatoonPriority	= 12
	/*
	 * Enumeration is extensible
	 */
} e_ExceptionalCondition;

/* ExceptionalCondition */
typedef long	 ExceptionalCondition_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ExceptionalCondition_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ExceptionalCondition;
extern const asn_INTEGER_specifics_t asn_SPC_ExceptionalCondition_specs_1;
asn_struct_free_f ExceptionalCondition_free;
asn_struct_print_f ExceptionalCondition_print;
asn_constr_check_f ExceptionalCondition_constraint;
ber_type_decoder_f ExceptionalCondition_decode_ber;
der_type_encoder_f ExceptionalCondition_encode_der;
xer_type_decoder_f ExceptionalCondition_decode_xer;
xer_type_encoder_f ExceptionalCondition_encode_xer;
oer_type_decoder_f ExceptionalCondition_decode_oer;
oer_type_encoder_f ExceptionalCondition_encode_oer;
per_type_decoder_f ExceptionalCondition_decode_uper;
per_type_encoder_f ExceptionalCondition_encode_uper;
per_type_decoder_f ExceptionalCondition_decode_aper;
per_type_encoder_f ExceptionalCondition_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _ExceptionalCondition_H_ */
#include <asn_internal.h>
