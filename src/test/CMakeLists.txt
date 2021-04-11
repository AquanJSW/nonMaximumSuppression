add_executable(test_1d test_1d.cpp)
target_link_libraries(test_1d PRIVATE nms_1d_fast nms_1d)

enable_testing()
function(test_1d target seed length range_start range_end enable_fast neighbors)
    if(${enable_fast})
        add_test(NAME 1D_S${seed}L${length}R${range_start}_${range_end}N${neighbors}F
                COMMAND ${target} -s ${seed} -l ${length} -r ${range_start},${range_end} -fn ${neighbors})
    else()
        add_test(NAME 1D_S${seed}L${length}R${range_start}_${range_end}N${neighbors}
                COMMAND ${target} -s ${seed} -l ${length} -r ${range_start},${range_end} -n ${neighbors})
    endif()
endfunction()

test_1d(test_1d 0 100 0 100 0 5)
test_1d(test_1d 0 100 0 100 1 5)
