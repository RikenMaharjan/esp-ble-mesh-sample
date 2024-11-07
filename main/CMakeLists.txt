# Include all source files
file(GLOB_RECURSE config_src "*.c")

idf_component_register(SRCS  "${config_src}"
                    INCLUDE_DIRS "."
                    REQUIRES    nvs_flash BLE_mesh_initializer BLE_mesh_led_model)
