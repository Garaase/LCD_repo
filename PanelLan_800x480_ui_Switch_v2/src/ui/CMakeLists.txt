SET(SOURCES components/ui_comp_button1.c
    components/ui_comp.c
    screens/ui_ScreenSwitchBoard.c
    screens/ui_ScreenChart.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
