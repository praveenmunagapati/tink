// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TINK_UTIL_TEST_UTIL_H_
#define TINK_UTIL_TEST_UTIL_H_

#include <string>

#include "absl/strings/string_view.h"
#include "cc/aead.h"
#include "cc/hybrid_decrypt.h"
#include "cc/hybrid_encrypt.h"
#include "cc/keyset_handle.h"
#include "cc/mac.h"
#include "cc/util/status.h"
#include "cc/util/statusor.h"
#include "proto/common.pb.h"
#include "proto/ecies_aead_hkdf.pb.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {
namespace test {

// Various utilities for testing.
///////////////////////////////////////////////////////////////////////////////

// Converts a hexadecimal string into a string of bytes.
// Returns a status if the size of the input is odd or if the input contains
// characters that are not hexadecimal.
crypto::tink::util::StatusOr<std::string> HexDecode(
    absl::string_view hex);

// Converts a hexadecimal string into a string of bytes.
// Dies if the input is not a valid hexadecimal string.
std::string HexDecodeOrDie(absl::string_view hex);

// Converts a string of bytes into a hexadecimal string.
std::string HexEncode(absl::string_view bytes);

// Creates a KeysetHandle object for the given 'keyset'.
std::unique_ptr<KeysetHandle> GetKeysetHandle(
    const google::crypto::tink::Keyset& keyset);

// Adds the given 'key' with specified parameters and output_prefix_type=TINK
// to the specified 'keyset'.
void AddTinkKey(
    const std::string& key_type,
    uint32_t key_id,
    const google::protobuf::Message& key,
    google::crypto::tink::KeyStatusType key_status,
    google::crypto::tink::KeyData::KeyMaterialType material_type,
    google::crypto::tink::Keyset* keyset);

// Adds the given 'key' with specified parameters and output_prefix_type=LEGACY
// to the specified 'keyset'.
void AddLegacyKey(
    const std::string& key_type,
    uint32_t key_id,
    const google::protobuf::Message& key,
    google::crypto::tink::KeyStatusType key_status,
    google::crypto::tink::KeyData::KeyMaterialType material_type,
    google::crypto::tink::Keyset* keyset);

// Adds the given 'key' with specified parameters and output_prefix_type=RAW
// to the specified 'keyset'.
void AddRawKey(
    const std::string& key_type,
    uint32_t key_id,
    const google::protobuf::Message& key,
    google::crypto::tink::KeyStatusType key_status,
    google::crypto::tink::KeyData::KeyMaterialType material_type,
    google::crypto::tink::Keyset* keyset);


// Generates a fresh test key for ECIES-AEAD-HKDF for the given curve,
// using AesGcm with the specified key size as AEAD, and HKDF with 'hash_type'.
google::crypto::tink::EciesAeadHkdfPrivateKey GetEciesAesGcmHkdfTestKey(
    google::crypto::tink::EllipticCurveType curve_type,
    google::crypto::tink::EcPointFormat ec_point_format,
    google::crypto::tink::HashType hash_type,
    uint32_t aes_gcm_key_size);

// A dummy implementation of Aead-interface.
// An instance of DummyAead can be identified by a name specified
// as a parameter of the constructor.
class DummyAead : public Aead {
 public:
  DummyAead(absl::string_view aead_name) : aead_name_(aead_name) {}

  // Computes a dummy ciphertext, which is concatenation of provided 'plaintext'
  // with the name of this DummyAead.
  crypto::tink::util::StatusOr<std::string> Encrypt(
      absl::string_view plaintext,
      absl::string_view associated_data) const override {
    return std::string(plaintext.data(), plaintext.size()).append(aead_name_);
  }

  crypto::tink::util::StatusOr<std::string> Decrypt(
      absl::string_view ciphertext,
      absl::string_view associated_data) const override {
    std::string c(ciphertext.data(), ciphertext.size());
    size_t pos = c.rfind(aead_name_);
    if (pos != std::string::npos &&
        ciphertext.length() == (unsigned)(aead_name_.length() + pos)) {
      return c.substr(0, pos);
    }
    return crypto::tink::util::Status(
        crypto::tink::util::error::INVALID_ARGUMENT, "Wrong ciphertext.");
  }

 private:
  std::string aead_name_;
};

// A dummy implementation of HybridEncrypt-interface.
// An instance of DummyHybridEncrypt can be identified by a name specified
// as a parameter of the constructor.
class DummyHybridEncrypt : public HybridEncrypt {
 public:
  DummyHybridEncrypt(absl::string_view hybrid_name)
      : hybrid_name_(hybrid_name) {}

  // Computes a dummy ciphertext, which is concatenation of provided 'plaintext'
  // with the name of this DummyHybridEncrypt.
  crypto::tink::util::StatusOr<std::string> Encrypt(
      absl::string_view plaintext,
      absl::string_view context_info) const override {
    return std::string(plaintext.data(), plaintext.size()).append(hybrid_name_);
  }

 private:
  std::string hybrid_name_;
};

// A dummy implementation of HybridDecrypt-interface.
// An instance of DummyHybridDecrypt can be identified by a name specified
// as a parameter of the constructor.
class DummyHybridDecrypt : public HybridDecrypt {
 public:
  DummyHybridDecrypt(absl::string_view hybrid_name)
      : hybrid_name_(hybrid_name) {}

  // Decrypts a dummy ciphertext, which should be a concatenation
  // of a plaintext with the name of this DummyHybridDecrypt.
  crypto::tink::util::StatusOr<std::string> Decrypt(
      absl::string_view ciphertext,
      absl::string_view context_info) const override {
    std::string c(ciphertext.data(), ciphertext.size());
    size_t pos = c.rfind(hybrid_name_);
    if (pos != std::string::npos &&
        ciphertext.length() == (unsigned)(hybrid_name_.length() + pos)) {
      return c.substr(0, pos);
    }
    return crypto::tink::util::Status(
        crypto::tink::util::error::INVALID_ARGUMENT, "Wrong ciphertext.");
  }

 private:
  std::string hybrid_name_;
};

// A dummy implementation of Mac-interface.
// An instance of DummyMac can be identified by a name specified
// as a parameter of the constructor.
class DummyMac : public Mac {
 public:
  DummyMac(const std::string mac_name) : mac_name_(mac_name) {}

  // Computes a dummy MAC, which is concatenation of provided 'data'
  // with the name of this DummyMac.
  crypto::tink::util::StatusOr<std::string> ComputeMac(
      absl::string_view data) const override {
    return std::string(data.data(), data.size()).append(mac_name_);
  }

  crypto::tink::util::Status VerifyMac(
      absl::string_view mac,
      absl::string_view data) const override {
    if (mac == std::string(data.data(), data.size()).append(mac_name_)) {
      return crypto::tink::util::Status::OK;
    } else {
      return crypto::tink::util::Status(
          crypto::tink::util::error::INVALID_ARGUMENT, "Wrong MAC.");
    }
  }
 private:
  std::string mac_name_;
};


}  // namespace test
}  // namespace tink
}  // namespace crypto

#endif  // TINK_UTIL_TEST_UTIL_H_
