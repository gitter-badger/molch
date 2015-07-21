/* Molch, an implementation of the axolotl ratched based on libsodium
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

#ifndef HKDF_H
#define HKDF_H
/*
 * This function implements HKDF (HMAC based key derivation function)
 * as defined in RFC 5869 using the primitives provided by libsodium.
 */
int hkdf(
        unsigned char* output_key,
        unsigned int output_key_length, //needs to be less than 255 * crypto_auth_KEYBYTES!!!
        unsigned char* salt, //the salt needs to be crypto_auth_KEYBYTES long
        unsigned char* input_key,
        unsigned long long input_key_length,
        unsigned char* info,
        unsigned int info_length);
#endif