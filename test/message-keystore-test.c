/* Molch, an implementation of the axolotl ratchet based on libsodium
 *  Copyright (C) 2015  Max Bruckner (FSMaxB)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <assert.h>

#include "../lib/message-keystore.h"
#include "utils.h"
#include "common.h"


int main(void) {
	sodium_init();

	//buffer for message keys
	unsigned char message_key[crypto_secretbox_KEYBYTES];

	//initialise message keystore
	message_keystore keystore = message_keystore_init();
	assert(keystore.length == 0);
	assert(keystore.head == NULL);
	assert(keystore.tail == NULL);

	int status;

	//add keys to the keystore
	unsigned int i;
	for (i = 0; i < 6; i++) {
		//create new key
		randombytes_buf(message_key, sizeof(message_key));

		//print the new key
		printf("New message key No. %u:\n", i);
		print_hex(message_key, sizeof(message_key), 30);
		putchar('\n');

		//add key to the keystore
		status = message_keystore_add(&keystore, message_key);
		sodium_memzero(message_key, sizeof(message_key));
		if (status != 0) {
			fprintf(stderr, "ERROR: Failed to add key to keystore. (%i)\n", status);
			message_keystore_clear(&keystore);
			return EXIT_FAILURE;
		}

		print_message_keystore(&keystore);

		assert(keystore.length == (i + 1));
	}

	//remove key from the head
	printf("Remove head!\n");
	message_keystore_remove(&keystore, keystore.head);
	assert(keystore.length == (i - 1));
	print_message_keystore(&keystore);

	//remove key from the tail
	printf("Remove Tail:\n");
	message_keystore_remove(&keystore, keystore.tail);
	assert(keystore.length == (i - 2));
	print_message_keystore(&keystore);

	//remove from inside
	printf("Remove from inside:\n");
	message_keystore_remove(&keystore, keystore.head->next);
	assert(keystore.length == (i - 3));
	print_message_keystore(&keystore);

	//clear the keystore
	printf("Clear the keystore:\n");
	message_keystore_clear(&keystore);
	assert(keystore.length == 0);
	assert(keystore.head == NULL);
	assert(keystore.tail == NULL);
	print_message_keystore(&keystore);
	return EXIT_SUCCESS;
}
