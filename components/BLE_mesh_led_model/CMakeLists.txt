

idf_component_register(SRCS "BLE_mesh_led_model.c"
                        INCLUDE_DIRS .
                        REQUIRES driver
                        PRIV_REQUIRES BLE_mesh_initializer
)


