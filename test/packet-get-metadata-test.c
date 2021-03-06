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

#include "../lib/packet.h"
#include "utils.h"
#include "packet-test-lib.h"

int main(void) {
	sodium_init();

	//generate keys and message
	unsigned char header_key[crypto_aead_chacha20poly1305_KEYBYTES];
	unsigned char message_key[crypto_secretbox_KEYBYTES];
	unsigned char message[] = "Hello world!\n";
	unsigned char header[] = {0x01, 0x02, 0x03, 0x04};
	unsigned char packet[3 + crypto_aead_chacha20poly1305_NPUBBYTES + crypto_aead_chacha20poly1305_ABYTES + crypto_secretbox_NONCEBYTES + sizeof(message) + sizeof(header) + crypto_secretbox_MACBYTES + 255];
	const unsigned char packet_type = 1;
	printf("Packet type: %02x\n", packet_type);
	const unsigned char current_protocol_version = 2;
	printf("Current protocol version: %02x\n", current_protocol_version);
	const unsigned char highest_supported_protocol_version = 3;
	printf("Highest supported protocol version: %02x\n", highest_supported_protocol_version);
	putchar('\n');
	size_t packet_length;
	int status = create_and_print_message(
			packet,
			&packet_length,
			packet_type,
			current_protocol_version,
			highest_supported_protocol_version,
			message,
			sizeof(message),
			message_key,
			header,
			sizeof(header),
			header_key);
	sodium_memzero(header_key, sizeof(header_key));
	sodium_memzero(header, sizeof(header));
	sodium_memzero(message_key, sizeof(message_key));
	sodium_memzero(message, sizeof(message));
	if (status != 0) {
		return status;
	}

	//now extract the metadata
	unsigned char extracted_packet_type;
	unsigned char extracted_current_protocol_version;
	unsigned char extracted_highest_supported_protocol_version;
	unsigned char extracted_header_length;
	status = packet_get_metadata_without_verification(
			packet,
			packet_length,
			&extracted_packet_type,
			&extracted_current_protocol_version,
			&extracted_highest_supported_protocol_version,
			&extracted_header_length);
	if (status != 0) {
		fprintf(stderr, "ERROR: Couldn't extract metadata from the packet. (%i)\n", status);
		return status;
	}

	if (packet_type != extracted_packet_type) {
		fprintf(stderr, "ERROR: Extracted packet type doesn't match (%i)!\n", extracted_packet_type);
		return EXIT_FAILURE;
	}
	printf("Packet type matches!\n");

	if (current_protocol_version != extracted_current_protocol_version) {
		fprintf(stderr, "ERROR: Extracted current protocol version doesn't match (%i)!\n", extracted_current_protocol_version);
		return EXIT_FAILURE;
	}
	printf("Current protocol version matches!\n");

	if (highest_supported_protocol_version != extracted_highest_supported_protocol_version) {
		fprintf(stderr, "ERROR: Extracted highest supported protocol version doesn't match (%i)!\n", extracted_highest_supported_protocol_version);
		return EXIT_FAILURE;
	}
	printf("Highest supoorted protocol version matches (%i)!\n", extracted_highest_supported_protocol_version);

	if (sizeof(header) != extracted_header_length) {
		fprintf(stderr, "ERROR: Extracted header length doesn't match (%i)!\n", extracted_header_length);
		return EXIT_FAILURE;
	}
	printf("Header length matches!\n");

	return EXIT_SUCCESS;
}
