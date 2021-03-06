cmake_minimum_required (VERSION 2.6)

add_library(utils utils)

add_library(common common)
target_link_libraries(common utils)

add_library(packet-test-lib packet-test-lib)
target_link_libraries(packet-test-lib molch utils)

set(tests hkdf-test
          diffie-hellman-test
          triple-diffie-hellman-test
          chain-key-derivation-test
          message-key-derivation-test
          root-chain-and-header-key-derivation-test
          initial-root-chain-and-header-key-derivation-test
          packet-get-metadata-test
          packet-decrypt-header-test
          packet-decrypt-message-test
          packet-decrypt-test
          header-test
          header-and-message-keystore-test
          ratchet-test
          buffer-test)

foreach(test ${tests})
    add_executable(${test} ${test})
    target_link_libraries(${test} molch utils common packet-test-lib)
    add_test(${test} "./${test}")
    if(NOT ("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND"))
        add_test("${test}-valgrind" ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} "./${test}")
    endif(NOT ("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND"))
endforeach(test)
