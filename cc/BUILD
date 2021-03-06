package(default_visibility = ["//tools/build_defs:internal_pkg"])

licenses(["notice"])  # Apache 2.0

# public libraries

cc_library(
    name = "cc",
    hdrs = [
        "aead.h",
        "aead_config.h",
        "aead_factory.h",
        "binary_keyset_reader.h",
        "catalogue.h",
        "config.h",
        "hybrid_decrypt.h",
        "hybrid_decrypt_config.h",
        "hybrid_decrypt_factory.h",
        "hybrid_encrypt.h",
        "hybrid_encrypt_config.h",
        "hybrid_encrypt_factory.h",
        "json_keyset_reader.h",
        "key_manager.h",
        "keyset_handle.h",
        "keyset_reader.h",
        "mac.h",
        "mac_config.h",
        "mac_factory.h",
        "public_key_sign.h",
        "public_key_verify.h",
        "registry.h",
        "tink_config.h",
    ],
    deps = [
        ":aead",
        ":binary_keyset_reader",
        ":json_keyset_reader",
        ":key_manager",
        ":keyset_handle",
        ":keyset_reader",
        ":mac",
        ":primitive_set",
        ":registry",
        "//cc/aead:aead_config",
        "//cc/aead:aead_factory",
        "//cc/config:tink_config",
        "//cc/hybrid:hybrid_decrypt_config",
        "//cc/hybrid:hybrid_decrypt_factory",
        "//cc/hybrid:hybrid_encrypt_config",
        "//cc/hybrid:hybrid_encrypt_factory",
        "//cc/mac:mac_config",
        "//cc/mac:mac_factory",
        "//cc/util:errors",
        "//cc/util:status",
        "//cc/util:statusor",
        "//cc/util:validation",
        "//proto:config_cc_proto",
        "//proto:tink_cc_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "aead",
    hdrs = ["aead.h"],
    deps = [
        "//cc/util:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "hybrid_decrypt",
    hdrs = ["hybrid_decrypt.h"],
    deps = [
        "//cc/util:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "hybrid_encrypt",
    hdrs = ["hybrid_encrypt.h"],
    deps = [
        "//cc/util:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "mac",
    hdrs = ["mac.h"],
    deps = [
        "//cc/util:status",
        "//cc/util:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "keyset_reader",
    hdrs = ["keyset_reader.h"],
    deps = [
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
    ],
)

cc_library(
    name = "binary_keyset_reader",
    srcs = ["core/binary_keyset_reader.cc"],
    hdrs = ["binary_keyset_reader.h"],
    deps = [
        ":keyset_reader",
        "//cc/util:errors",
        "//cc/util:ptr_util",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "json_keyset_reader",
    srcs = ["core/json_keyset_reader.cc"],
    hdrs = ["json_keyset_reader.h"],
    deps = [
        ":keyset_reader",
        "//cc/util:errors",
        "//cc/util:ptr_util",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "catalogue",
    hdrs = ["catalogue.h"],
    deps = [
        ":key_manager",
        "//cc/util:statusor",
    ],
)

cc_library(
    name = "config",
    srcs = ["core/config.cc"],
    hdrs = ["config.h"],
    deps = [
        ":aead",
        ":catalogue",
        ":hybrid_decrypt",
        ":hybrid_encrypt",
        ":key_manager",
        ":mac",
        ":registry",
        "//cc/util:errors",
        "//cc/util:status",
        "//cc/util:statusor",
        "//proto:config_cc_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "crypto_format",
    srcs = ["core/crypto_format.cc"],
    hdrs = ["crypto_format.h"],
    deps = [
        "//cc/util:errors",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
    ],
)

cc_library(
    name = "primitive_set",
    srcs = ["primitive_set.h"],
    hdrs = ["primitive_set.h"],
    deps = [
        ":crypto_format",
        "//cc/util:errors",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
    ],
)

cc_library(
    name = "registry",
    srcs = ["core/registry.cc"],
    hdrs = ["registry.h"],
    deps = [
        ":catalogue",
        ":key_manager",
        ":keyset_handle",
        ":primitive_set",
        "//cc/util:errors",
        "//cc/util:status",
        "//cc/util:statusor",
        "//cc/util:validation",
        "//proto:tink_cc_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "keyset_handle",
    srcs = ["core/keyset_handle.cc"],
    hdrs = ["keyset_handle.h"],
    deps = [
        ":aead",
        ":keyset_reader",
        "//cc/util:errors",
        "//cc/util:ptr_util",
        "//proto:tink_cc_proto",
    ],
)

cc_library(
    name = "cleartext_keyset_handle",
    srcs = ["core/cleartext_keyset_handle.cc"],
    hdrs = ["cleartext_keyset_handle.h"],
    deps = [
        ":keyset_handle",
        "//cc/util:errors",
        "//cc/util:ptr_util",
        "//cc/util:status",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
    ],
)

cc_library(
    name = "key_manager",
    srcs = ["key_manager.h"],
    hdrs = ["key_manager.h"],
    deps = [
        "//cc/util:errors",
        "//cc/util:status",
        "//cc/util:statusor",
        "//proto:tink_cc_proto",
        "@com_google_absl//absl/strings",
        "@com_google_protobuf//:protobuf_lite",
    ],
)

# tests

cc_test(
    name = "registry_test",
    size = "small",
    srcs = ["core/registry_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":aead",
        ":catalogue",
        ":crypto_format",
        ":registry",
        "//cc/aead:aead_catalogue",
        "//cc/aead:aes_gcm_key_manager",
        "//cc/util:status",
        "//cc/util:statusor",
        "//cc/util:test_util",
        "//proto:aes_ctr_hmac_aead_cc_proto",
        "//proto:aes_gcm_cc_proto",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "binary_keyset_reader_test",
    size = "small",
    srcs = ["core/binary_keyset_reader_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":binary_keyset_reader",
        "//cc/util:test_util",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "json_keyset_reader_test",
    size = "small",
    srcs = ["core/json_keyset_reader_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":json_keyset_reader",
        "//cc/util:test_util",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "config_test",
    size = "small",
    srcs = ["core/config_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":config",
        ":mac",
        "//proto:config_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "crypto_format_test",
    size = "small",
    srcs = ["core/crypto_format_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":crypto_format",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "keyset_handle_test",
    size = "small",
    srcs = ["core/keyset_handle_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":binary_keyset_reader",
        ":json_keyset_reader",
        ":keyset_handle",
        "//cc/util:test_util",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "cleartext_keyset_handle_test",
    size = "small",
    srcs = ["core/cleartext_keyset_handle_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":binary_keyset_reader",
        ":cleartext_keyset_handle",
        ":keyset_handle",
        ":keyset_reader",
        "//cc/util:test_util",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "primitive_set_test",
    size = "small",
    srcs = ["core/primitive_set_test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":crypto_format",
        ":mac",
        ":primitive_set",
        "//cc/util:test_util",
        "//proto:tink_cc_proto",
        "@com_google_googletest//:gtest_main",
        "@com_google_protobuf//:protobuf_lite",
    ],
)
