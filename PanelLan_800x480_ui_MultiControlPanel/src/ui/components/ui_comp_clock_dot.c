// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: Smart_Gadget

#include "../ui.h"


// COMPONENT Clock Dot

lv_obj_t * ui_Clock_Dot_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Clock_Dot;
    cui_Clock_Dot = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Clock_Dot, 6);
    lv_obj_set_height(cui_Clock_Dot, 6);
    lv_obj_set_x(cui_Clock_Dot, -10);
    lv_obj_set_y(cui_Clock_Dot, 50);
    lv_obj_set_align(cui_Clock_Dot, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(cui_Clock_Dot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(cui_Clock_Dot, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_Clock_Dot, lv_color_hex(0xB3B4E5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Clock_Dot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CLOCK_DOT_NUM);
    children[UI_COMP_CLOCK_DOT_CLOCK_DOT] = cui_Clock_Dot;
    lv_obj_add_event_cb(cui_Clock_Dot, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Clock_Dot, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Clock_Dot_create_hook(cui_Clock_Dot);
    return cui_Clock_Dot;
}
