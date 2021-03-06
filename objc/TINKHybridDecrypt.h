/**
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **************************************************************************
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The protocol for hybrid decryption.
 *
 * Implementations of this protocol are secure against adaptive chosen ciphertext attacks. In
 * addition to @c ciphertext the encryption takes an extra parameter @c contextInfo, which usually
 * is public data implicit from the context, but should be bound to the resulting ciphertext: upon
 * decryption the ciphertext allows for checking the integrity of @c contextInfo (but there are no
 * guarantees with regard to secrecy or authenticity of @c contextInfo).
 *
 * @c contextInfo can be empty or nil, but to ensure the correct decryption of the ciphertext the
 * same value must be provided as was used during encryption operation.
 *
 * A concrete instantiation of this interface can implement the binding of @c contextInfo to the
 * ciphertext in various ways, for example:
 *
 * - Use @c contextInfo as "associated data"-input for the employed AEAD symmetric encryption
 *   (https://tools.ietf.org/html/rfc5116).
 * - Use @c contextInfo as "CtxInfo"-input for HKDF (if the implementation uses HKDF as key
 *   derivation function: https://tools.ietf.org/html/rfc5869).
 */
@protocol TINKHybridDecrypt <NSObject>

/* Decrypts @c ciphertext verifying the integrity of @c contextInfo. */
- (nullable NSData *)decrypt:(NSData *)ciphertext
             withContextInfo:(nullable NSData *)contextInfo
                       error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
