/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AVIAEINumberingAndDataStructures"
 * 	found in "/tmp/gen_env/build/asn1/ISO14816_AVIAEINumberingAndDataStructures.asn"
 * 	`asn1c -D /tmp/gen_env/vcits/ssem -R -no-gen-example -fcompound-names -fno-include-deps -pdu=SSEM`
 */

#ifndef	_CS1_H_
#define	_CS1_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CountryCode.h"
#include "IssuerIdentifier.h"
#include "ServiceNumber.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CS1 */
typedef struct CS1 {
	CountryCode_t	 countryCode;
	IssuerIdentifier_t	 issuerIdentifier;
	ServiceNumber_t	 serviceNumber;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CS1_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CS1;

#ifdef __cplusplus
}
#endif

#endif	/* _CS1_H_ */
#include <asn_internal.h>
