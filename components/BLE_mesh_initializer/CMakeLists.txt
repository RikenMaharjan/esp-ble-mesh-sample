
file(GLOB_RECURSE config_src "*.c")

idf_component_register(SRCS "BLE_mesh_prov_indicator.c" "${config_src}"
                        INCLUDE_DIRS "."
                        REQUIRES bt example_init driver
)




