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

#include "../lib/packet.h"

/*
 * Create message and header keys, encrypt header and message
 * and print them.
 */
int create_and_print_message(
		unsigned char * const packet, //needs to be 3 + crypto_aead_chacha20poly1305_NPUBBYTES + crypto_secretbox_NONCEBYTES + message_length + header_length + crypto_secretbox_MACBYTES
		size_t * const packet_length, //output
		const unsigned char packet_type,
		const unsigned char current_protocol_version,
		const unsigned char highest_supported_protocol_version,
		const unsigned char * const message,
		const size_t message_length,
		unsigned char * message_key, //output, crypto_secretbox_KEYBYTES
		const unsigned char * const header,
		const size_t header_length,
		unsigned char * header_key); //output, crypto_secretbox_KEYBYTES
