cmake_minimum_required(VERSION 3.17)
project(compiler_principle_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

enable_testing()

# Ex1: Identifiers Counter

add_executable(test_identifiers_counter test/testIdentifiersCounter.cpp)

set(IDENTIFIERS_COUNTER_CASES 1_Compare 2_Reverse 3_Chaos 4_Gcd 5_Unknown 6_Add 7_SortThree 8_Triangle 9_FullWidthSymbol)

foreach (case ${IDENTIFIERS_COUNTER_CASES})
    add_test(
            NAME identifiers_counter__${case}
            WORKING_DIRECTORY ../test
            COMMAND bash -c "set -o pipefail; \
            ( ( $<TARGET_FILE:test_identifiers_counter> Cases/${case}/${case}.in; true ) 2>&3 \
              | tee /dev/stderr | diff -ibBa - Cases/${case}/identifiers_counter.out >/dev/null) 3>&1 \
            | tee /dev/stderr | diff -ibBa - Cases/${case}/identifiers_counter.err >/dev/null"
    )
    set_tests_properties(identifiers_counter__${case} PROPERTIES LABELS identifiers_counter)
endforeach ()

# Ex2: Lexical Analyzer

add_executable(test_lexical_analyzer test/testLexicalAnalyzer.cpp)

set(LEXICAL_ANALYZER_CASES 1_Compare 2_Reverse 3_Chaos 4_Gcd 5_Unknown 6_Add 7_SortThree 8_Triangle 9_FullWidthSymbol)

foreach (case ${LEXICAL_ANALYZER_CASES})
    add_test(
            NAME lexical_analyzer__${case}
            WORKING_DIRECTORY ../test
            COMMAND bash -c "set -o pipefail; \
            ( ( $<TARGET_FILE:test_lexical_analyzer> Cases/${case}/${case}.in; true ) 2>&3 \
              | tee /dev/stderr | diff -ibBa - Cases/${case}/lexical_analyzer.out >/dev/null) 3>&1 1>&2 \
            | tee /dev/stderr | diff -ibBa - Cases/${case}/lexical_analyzer.err >/dev/null"
    )
    set_tests_properties(lexical_analyzer__${case} PROPERTIES LABELS lexical_analyzer)
endforeach ()