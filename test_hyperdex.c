// test_hyperdex.c by ziga.zupanec@gmail.com
//

/*
HYPERDATATYPE_STRING			= 8960
HYPERDATATYPE_INT64				= 8961
HYPERDATATYPE_LIST_STRING		= 8976
HYPERDATATYPE_LIST_INT64		= 8977
HYPERDATATYPE_SET_STRING		= 8992
HYPERDATATYPE_SET_INT64			= 8993
HYPERDATATYPE_MAP_STRING_STRING	= 9008
HYPERDATATYPE_MAP_STRING_INT64	= 9009
HYPERDATATYPE_MAP_INT64_STRING	= 9010
HYPERDATATYPE_MAP_INT64_INT64	= 9011
HYPERDATATYPE_GARBAGE			= 9087
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <hyperclient.h>

#define ATT_SIZE 3

// this is based upon python hyperclient
void fill_attrs(struct hyperclient_attribute** attrs)
{
	// c.put('phonebook', 'jsmith1', {'first': 'John', 'last': 'Smith', 'phone': 6075551024})
	const char first[] = "first";
	const char first_val[] = "John";
	size_t first_val_sz = strlen(first_val);
	enum hyperdatatype first_val_type = 8960;	// HYPERDATATYPE_STRING

	const char last[]  = "last";
	const char last_val[] = "Smith";
	size_t last_val_sz = strlen(last_val);
	enum hyperdatatype last_val_type = 8960;	// HYPERDATATYPE_STRING

	const char phone[] = "phone";
	// some voodoo here, forgot how I got that but I believe this is what 6075551024 converts to
	const char phone_val[] = "\x00\x8d\x21\x6a\x01\x00\x00\x00";
	size_t phone_val_sz = 8;
	enum hyperdatatype phone_val_type = 8961;	// HYPERDATATYPE_INT64

	attrs[0] = (struct hyperclient_attribute *)malloc(sizeof(struct hyperclient_attribute) * ATT_SIZE);

	attrs[0][0].attr = first;
	attrs[0][0].value = first_val;
	attrs[0][0].value_sz = first_val_sz;
	attrs[0][0].datatype = first_val_type;

	attrs[0][1].attr = last;
	attrs[0][1].value = last_val;
	attrs[0][1].value_sz = last_val_sz;
	attrs[0][1].datatype = last_val_type;

	attrs[0][2].attr = phone;
	attrs[0][2].value = phone_val;
	attrs[0][2].value_sz = phone_val_sz;
	attrs[0][2].datatype = phone_val_type;
}

int main()
{
	in_port_t port = 1234;
	struct hyperclient* hc;
	
	const char space[] = "phonebook";
	const char key[] = "jsmith1";
	size_t key_sz = 7;
	enum hyperclient_returncode status = 0;
	struct hyperclient_attribute* attrs;

	fill_attrs(&attrs);

	hc = hyperclient_create("127.0.0.1", port);

	hyperclient_put(
		hc,
		space,
		key,
		key_sz,
		attrs,
		ATT_SIZE,
		&status
	);

	printf("status: %d\n", status);

	hyperclient_destroy(hc);
	free(attrs);

	return 0;
}
