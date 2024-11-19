


idf_component_register(SRCS "BLE_mesh_bme280_vendor_model.c" "bmp280.c"
                        INCLUDE_DIRS .
                        REQUIRES    esp_driver_i2c 
                                    BLE_mesh_initializer
)

