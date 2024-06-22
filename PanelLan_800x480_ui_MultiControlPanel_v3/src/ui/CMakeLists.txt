SET(SOURCES screens/ui_splash.c
    screens/ui_ScreenWeather.c
    screens/ui_ScreenSwitch_Node1.c
    screens/ui_ScreenSwitch_Node2.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_logo4b_png.c
    images/ui_img_pattern1b1_png.c)

add_library(ui ${SOURCES})
