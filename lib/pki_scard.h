/* vi: set sw=4 ts=4:
 *
 * Copyright (C) 2001 - 2007 Christian Hohnstaedt.
 *
 * All rights reserved.
 */

#ifndef PKI_SCARD_H
#define PKI_SCARD_H

#include <qstring.h>
#include <openssl/pem.h>
#include <openssl/evp.h>

#include "pkcs11.h"
#include "pki_key.h"

class pki_scard: public pki_key
{
	protected:
		QString card_serial;
		QString card_manufacturer;
		QString bit_length;
		QString card_label;
		QString slot_label;
		QString object_id;
		QList<CK_MECHANISM_TYPE> mech_list;
		void init(void);
		static ENGINE *p11_engine;

	public:
		pki_scard(const QString name);
		virtual ~pki_scard();
		static QPixmap *icon[1];
		void load_token(pkcs11 &p11, CK_OBJECT_HANDLE object);
		static bool init_p11engine(QString file, bool silent);
		int prepare_card() const;
		void fromData(const unsigned char *p, db_header_t *head);
		unsigned char *toData(int *size);
		bool isPubKey() const;
		QString getTypeString(void);
		QString getManufacturer() const { return card_manufacturer; }
		QString getSerial() const { return card_serial; }
		QString getLabel() const { return slot_label; }
		QString getId() const { return object_id; }
		QString getCardLabel() const { return card_label; }
		EVP_PKEY *decryptKey() const;
		QString length();
		QString scardLogin(pkcs11 &p11, bool so, bool force=false)const;
		void changePin();
		void initPin();
		void changeSoPin();
		int verify();
		bool isScard();
		QVariant getIcon();
		QList<CK_MECHANISM_TYPE> getMech_list() { return mech_list; };
		void setMech_list(QList<CK_MECHANISM_TYPE> ml) { mech_list = ml; };
		QList<int> possibleHashNids();
};

#endif