// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_ScreenChart_screen_init(void)
{
    ui_ScreenChart = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenChart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Chart1 = lv_chart_create(ui_ScreenChart);
    lv_obj_set_width(ui_Chart1, 300);
    lv_obj_set_height(ui_Chart1, 150);
    lv_obj_set_x(ui_Chart1, 190);
    lv_obj_set_y(ui_Chart1, -100);
    lv_obj_set_align(ui_Chart1, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart1, LV_CHART_TYPE_LINE);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_chart_series_t * ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x808080),
                                                                 LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart1_series_1_array[] = { 0, 10, 20, 40, 80, 80, 40, 20, 10, 0 };
    lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_series_1_array);



    ui_Panel1 = lv_obj_create(ui_ScreenChart);
    lv_obj_set_width(ui_Panel1, 300);
    lv_obj_set_height(ui_Panel1, 150);
    lv_obj_set_x(ui_Panel1, -200);
    lv_obj_set_y(ui_Panel1, -100);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Chart2 = lv_chart_create(ui_ScreenChart);
    lv_obj_set_width(ui_Chart2, 300);
    lv_obj_set_height(ui_Chart2, 150);
    lv_obj_set_x(ui_Chart2, 190);
    lv_obj_set_y(ui_Chart2, 120);
    lv_obj_set_align(ui_Chart2, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart2, LV_CHART_TYPE_LINE);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_chart_series_t * ui_Chart2_series_1 = lv_chart_add_series(ui_Chart2, lv_color_hex(0x808080),
                                                                 LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart2_series_1_array[] = { 0, 10, 20, 40, 80, 80, 40, 20, 10, 0 };
    lv_chart_set_ext_y_array(ui_Chart2, ui_Chart2_series_1, ui_Chart2_series_1_array);



    ui_Panel2 = lv_obj_create(ui_ScreenChart);
    lv_obj_set_width(ui_Panel2, 300);
    lv_obj_set_height(ui_Panel2, 150);
    lv_obj_set_x(ui_Panel2, -200);
    lv_obj_set_y(ui_Panel2, 120);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_ScreenChart);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, -210);
    lv_obj_set_y(ui_Label6, -100);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "0.00");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_ScreenChart);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, -175);
    lv_obj_set_y(ui_Label7, -100);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "V");
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_ScreenChart);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, -210);
    lv_obj_set_y(ui_Label8, 120);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "0.00");
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_ScreenChart);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, -175);
    lv_obj_set_y(ui_Label9, 120);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "A");
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ScreenChart, ui_event_ScreenChart, LV_EVENT_ALL, NULL);

}