# Unity sources
file(GLOB UNITY_SOURCES "Unity/*.c")

# All test_*.c files in tests/
file(GLOB TEST_SOURCES "*.c")
list(REMOVE_ITEM TEST_SOURCES ${UNITY_SOURCES})  # exclude Unity sources

foreach(TEST_FILE ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_FILE} ${UNITY_SOURCES})
	target_compile_definitions(${TEST_NAME} PRIVATE UNITY_INCLUDE_DOUBLE)
	target_link_libraries(${TEST_NAME} PRIVATE MyLibrary)
	add_test(NAME ${TEST_NAME} COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:${TEST_NAME}>)
endforeach()

