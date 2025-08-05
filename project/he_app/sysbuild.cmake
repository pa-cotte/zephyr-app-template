set(HP_APP hp_app)
set(HP_APP_SRC_DIR ./../../project/hp_app)
ExternalZephyrProject_Add(APPLICATION ${HP_APP} SOURCE_DIR ${HP_APP_SRC_DIR} BOARD alif_e7_dk/ae722f80f55d5xx/rtss_hp)
