
file(GLOB_RECURSE config_src "*.c")

idf_component_register(SRCS "BLE_mesh_led_model.c" "${config_src}"
                        INCLUDE_DIRS "."
                        REQUIRES driver
                        PRIV_REQUIRES BLE_mesh_initializer
)


