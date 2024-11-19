set(srcs "main.c")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS  "."
                    REQUIRES    nvs_flash BLE_mesh_initializer BLE_mesh_led_model BLE_mesh_bme280_vendor_model                
)
