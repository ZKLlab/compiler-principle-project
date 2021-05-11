cmake_minimum_required(VERSION 3.17)
project(compiler_principle_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
aux_source_directory("src/MyCompiler" SRC)
aux_source_directory("src/MyCompiler/Util" SRC)
add_library(MyCompiler STATIC ${SRC})
link_libraries(MyCompiler)

add_executable(test_identifiers_counter test/testIdentifiersCounter.cpp)
add_executable(test_lexical_analyzer test/testLexicalAnalyzer.cpp)
add_executable(test_recursive_descent_parser test/testRecursiveDescentParser.cpp)
add_executable(test_table_driven_parser test/testTableDrivenParser.cpp)
add_executable(test_rd_exp_parser test/testRdExpParser.cpp)
add_executable(test_rd_cond_parser test/testRdCondParser.cpp)
add_executable(test_rd_exp_sdt test/testRdExpSdt.cpp)
add_executable(test_ir_generation test/testIrGeneration.cpp)

enable_testing()

set(LABELS identifiers_counter
        lexical_analyzer
        recursive_descent_parser table_driven_parser rd_exp_parser rd_cond_parser
        rd_exp_sdt
        ir_generation)
set(CASES 1_Compare 2_Reverse 3_Chaos 4_Gcd 5_Unknown 6_Add 7_SortThree 8_Triangle 9_FullWidthSymbol
        10_Compare_Fix 11_Reverse_Fix 12_Expressions 13_Conditions
        14_Calculator 15_ExpressionsWithVars)

foreach (label ${LABELS})
    foreach (case ${CASES})
        if (EXISTS "${CMAKE_SOURCE_DIR}/test/Cases/${case}/${case}.in"
                AND EXISTS "${CMAKE_SOURCE_DIR}/test/Cases/${case}/${label}.out"
                AND EXISTS "${CMAKE_SOURCE_DIR}/test/Cases/${case}/${label}.err")
            add_test(
                    NAME ${label}__${case}
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test/Cases/${case}"
                    COMMAND bash -c "set -o pipefail && ( ( ( \"$<TARGET_FILE:test_${label}>\" ${case}.in || true ) 2>&3 \
| \"${CMAKE_COMMAND}\" -E compare_files --ignore-eol <( tee /dev/stderr ) ${label}.out 2>&5 ) 2>&4 3>&1 \
| \"${CMAKE_COMMAND}\" -E compare_files --ignore-eol <( tee /dev/stderr ) ${label}.err ) 4>&1 5>&2"
            )
            set_tests_properties(${label}__${case} PROPERTIES LABELS ${label})
            set_tests_properties(${label}__${case} PROPERTIES TIMEOUT 5)
        endif ()
    endforeach ()
endforeach ()